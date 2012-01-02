// file      : odb/relational/oracle/common.cxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v3; see accompanying LICENSE file

#include <cassert>

#include <odb/relational/oracle/common.hxx>

using namespace std;

namespace relational
{
  namespace oracle
  {
    //
    // member_base
    //

    void member_base::
    traverse (semantics::data_member& m)
    {
      if (transient (m))
        return;

      string var;

      if (!var_override_.empty ())
        var = var_override_;
      else
      {
        string const& name (m.name ());
        var = name + (name[name.size () - 1] == '_' ? "" : "_");
      }

      bool cq (type_override_ != 0 ? false : const_type (m.type ()));
      semantics::type& t (type_override_ != 0 ? *type_override_ : utype (m));

      semantics::type* cont;
      if (semantics::class_* c = composite_wrapper (t))
      {
        // If t is a wrapper, pass the wrapped type. Also pass the
        // original, wrapper type.
        //
        member_info mi (m,
                        *c,
                        (wrapper (t) ? &t : 0),
                        cq,
                        var,
                        fq_type_override_);
        if (pre (mi))
        {
          traverse_composite (mi);
          post (mi);
        }
      }
      // This cannot be a container if we have a type override.
      //
      else if (type_override_ == 0 && (cont = context::container (m)))
      {
        // The same unwrapping logic as for composite values.
        //
        member_info mi (m,
                        *cont,
                        (wrapper (t) ? &t : 0),
                        cq,
                        var,
                        fq_type_override_);
        if (pre (mi))
        {
          traverse_container (mi);
          post (mi);
        }
      }
      else
      {
        sql_type const& st (column_sql_type (m, key_prefix_));

        if (semantics::class_* c = object_pointer (t))
        {
          member_info mi (m,
                          utype (*id_member (*c)),
                          0,
                          cq,
                          var,
                          fq_type_override_);
          mi.st = &st;
          if (pre (mi))
          {
            traverse_object_pointer (mi);
            post (mi);
          }
        }
        else
        {
          member_info mi (m, t, 0, cq, var, fq_type_override_);
          mi.st = &st;
          if (pre (mi))
          {
            traverse_simple (mi);
            post (mi);
          }
        }
      }
    }

    void member_base::
    traverse_simple (member_info& mi)
    {
      switch (mi.st->type)
      {
        // Numeric types.
        //
      case sql_type::NUMBER:
        {
          const sql_type& st (*mi.st);

          if (st.range)
          {
            unsigned short r (st.range_value);

            if (!st.scale)
            {
              if (r <= 10)
                traverse_int32 (mi);
              // Only OCI versions 11.2 and later support insertion and
              // extraction into a 64 bit integer.
              //
              else if (
                (options.oracle_client_version () >= oracle_version (11, 2)) &&
                (r <= 19 || (r == 20 && unsigned_integer (mi.t))))
                traverse_int64 (mi);
              else
                traverse_big_int (mi);
            }
            else
            {
              // We can calculate the decimal exponent of the normalised
              // floating point equivalent of the fixed point number using
              // e = r - s, where r is the range, s is the scale, and e the
              // exponent. We can then use this to determine whether or not a
              // value of Oracle SQL type NUMBER can be completely stored in
              // the native floating point type.
              //

              // The maximum decimal precision of a float is 7 significant
              // digits. The minimum and maximum decimal exponents
              // representable by a float are -37 and 38 respectively.
              //
              if (r <= 7)
              {
                int e = r - st.scale_value;

                if (e >= -37 && e <= 38)
                  traverse_float (mi);
                else
                  traverse_double (mi);
              }

              // The maximum decimal precision of a double is 15 significant
              // digits. The minimum and maximum decimal exponent representable
              // by a double exceeds that of the Oracle NUMBER type.
              //
              else if (r <= 15)
                traverse_double (mi);
              else
                traverse_big_float (mi);
            }
          }
          else
            // If there is not range, then this is a floating-point number.
            //
            traverse_double (mi);

          break;
        }
      case sql_type::FLOAT:
        {
          // We map FLOAT types based exclusively on their binary precision
          // seeing that in 99% of cases it is the precision that is the
          // limiting factor and not the exponent.
          //
          if (mi.st->range_value <= 24)
            traverse_float (mi);
          else if (mi.st->range_value <= 53)
            traverse_double (mi);
          else
            traverse_big_float (mi);

          break;
        }
      case sql_type::BINARY_FLOAT:
        {
          traverse_float (mi);
          break;
        }
      case sql_type::BINARY_DOUBLE:
        {
          traverse_double (mi);
          break;
        }
        // Data-time types.
        //
      case sql_type::DATE:
        {
          traverse_date (mi);
          break;
        }
      case sql_type::TIMESTAMP:
        {
          traverse_timestamp (mi);
          break;
        }
      case sql_type::INTERVAL_YM:
        {
          traverse_interval_ym (mi);
          break;

        }
      case sql_type::INTERVAL_DS:
        {
          traverse_interval_ds (mi);
          break;
        }
        // String and binary types.
        //
      case sql_type::CHAR:
      case sql_type::NCHAR:
      case sql_type::VARCHAR2:
      case sql_type::NVARCHAR2:
      case sql_type::RAW:
        {
          traverse_string (mi);
          break;
        }
      case sql_type::BLOB:
      case sql_type::CLOB:
      case sql_type::NCLOB:
        {
          traverse_lob (mi);
          break;
        }
      case sql_type::invalid:
        {
          assert (false);
          break;
        }
      }
    }

    //
    // member_image_type
    //

    member_image_type::
    member_image_type (semantics::type* type,
                       string const& fq_type,
                       string const& key_prefix)
        : relational::member_base (type, fq_type, key_prefix)
    {
    }

    string member_image_type::
    image_type (semantics::data_member& m)
    {
      type_.clear ();
      member_base::traverse (m);
      return type_;
    }

    void member_image_type::
    traverse_composite (member_info& mi)
    {
      type_ = "composite_value_traits< " + mi.fq_type () + " >::image_type";
    }

    void member_image_type::
    traverse_int32 (member_info& mi)
    {
      if (unsigned_integer (mi.t))
        type_ = "unsigned int";
      else
        type_ = "int";
    }

    void member_image_type::
    traverse_int64 (member_info& mi)
    {
      if (unsigned_integer (mi.t))
        type_ = "unsigned long long";
      else
        type_ = "long long";
    }

    void member_image_type::
    traverse_big_int (member_info&)
    {
      type_ = "char*";
    }

    void member_image_type::
    traverse_float (member_info&)
    {
      type_ = "float";
    }

    void member_image_type::
    traverse_double (member_info&)
    {
      type_ = "double";
    }

    void member_image_type::
    traverse_big_float (member_info&)
    {
      type_ = "char*";
    }

    void member_image_type::
    traverse_date (member_info&)
    {
      type_ = "char*";
    }

    void member_image_type::
    traverse_timestamp (member_info&)
    {
      type_ = "oracle::datetime";
    }

    void member_image_type::
    traverse_interval_ym (member_info&)
    {
      type_ = "oracle::interval_ym";
    }

    void member_image_type::
    traverse_interval_ds (member_info&)
    {
      type_ = "oracle::interval_ds";
    }

    void member_image_type::
    traverse_string (member_info&)
    {
      type_ = "char*";
    }

    void member_image_type::
    traverse_lob (member_info&)
    {
      type_ = "oracle::lob_callback";
    }

    //
    // member_database_type
    //

    namespace
    {
      const char* string_bin_database_id[] =
      {
        "id_string",   // CHAR
        "id_nstring",  // NCHAR
        "id_string",   // VARCHAR2
        "id_nstring",  // NVARCHAR2
        "id_raw"       // RAW
      };

      const char* lob_database_id[] =
      {
        "id_blob",
        "id_clob",
        "id_nclob"
      };
   }

    member_database_type_id::
    member_database_type_id (semantics::type* type,
                             string const& fq_type,
                             string const& key_prefix)
        : relational::member_base (type, fq_type, key_prefix)
    {
    }

    string member_database_type_id::
    database_type_id (type& m)
    {
      type_id_.clear ();
      member_base::traverse (m);
      return type_id_;
    }

    void member_database_type_id::
    traverse_composite (member_info&)
    {
      assert (false);
    }

    void member_database_type_id::
    traverse_int32 (member_info&)
    {
      type_id_ = "oracle::id_int32";
    }

    void member_database_type_id::
    traverse_int64 (member_info&)
    {
      type_id_ = "oracle::id_int64";
    }

    void member_database_type_id::
    traverse_big_int (member_info&)
    {
      type_id_ = "oracle::id_big_int";
    }

    void member_database_type_id::
    traverse_float (member_info&)
    {
      type_id_ = "oracle::id_float";
    }

    void member_database_type_id::
    traverse_double (member_info&)
    {
      type_id_ = "oracle::id_double";
    }

    void member_database_type_id::
    traverse_big_float (member_info&)
    {
      type_id_ = "oracle::id_big_float";
    }

    void member_database_type_id::
    traverse_date (member_info&)
    {
      type_id_ = "oracle::id_date";
    }

    void member_database_type_id::
    traverse_timestamp (member_info&)
    {
      type_id_ = "oracle::id_timestamp";
    }

    void member_database_type_id::
    traverse_interval_ym (member_info&)
    {
      type_id_ = "oracle::id_interval_ym";
    }

    void member_database_type_id::
    traverse_interval_ds (member_info&)
    {
      type_id_ = "oracle::id_interval_ds";
    }

    void member_database_type_id::
    traverse_string (member_info& mi)
    {
      type_id_ = string ("oracle::") +
        string_bin_database_id[mi.st->type - sql_type::CHAR];
    }

    void member_database_type_id::
    traverse_lob (member_info& mi)
    {
      type_id_ = string ("oracle::") +
        lob_database_id[mi.st->type - sql_type::BLOB];
    }

    //
    // query_columns
    //

    struct query_columns: relational::query_columns, context
    {
      query_columns (base const& x): base (x) {}

      virtual string
      database_type_id (semantics::data_member& m)
      {
        return member_database_type_id_.database_type_id (m);
      }

    private:
      member_database_type_id member_database_type_id_;
    };
    entry<query_columns> query_columns_;
  }
}
