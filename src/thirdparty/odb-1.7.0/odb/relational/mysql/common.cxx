// file      : odb/relational/mysql/common.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v3; see accompanying LICENSE file

#include <cassert>

#include <odb/relational/mysql/common.hxx>

using namespace std;

namespace relational
{
  namespace mysql
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
        // Integral types.
        //
      case sql_type::TINYINT:
      case sql_type::SMALLINT:
      case sql_type::MEDIUMINT:
      case sql_type::INT:
      case sql_type::BIGINT:
        {
          traverse_integer (mi);
          break;
        }

        // Float types.
        //
      case sql_type::FLOAT:
      case sql_type::DOUBLE:
        {
          traverse_float (mi);
          break;
        }
      case sql_type::DECIMAL:
        {
          traverse_decimal (mi);
          break;
        }

        // Data-time types.
        //
      case sql_type::DATE:
      case sql_type::TIME:
      case sql_type::DATETIME:
      case sql_type::TIMESTAMP:
      case sql_type::YEAR:
        {
          traverse_date_time (mi);
          break;
        }

        // String and binary types.
        //
      case sql_type::CHAR:
      case sql_type::VARCHAR:
      case sql_type::TINYTEXT:
      case sql_type::TEXT:
      case sql_type::MEDIUMTEXT:
      case sql_type::LONGTEXT:
        {
          // For string types the limit is in characters rather
          // than in bytes. The fixed-length pre-allocated buffer
          // optimization can only be used for 1-byte encodings.
          // To support this we will need the character encoding
          // in sql_type.
          //
          traverse_long_string (mi);
          break;
        }
      case sql_type::BINARY:
      case sql_type::TINYBLOB:
        {
          // BINARY's range is always 255 or less from MySQL 5.0.3.
          // TINYBLOB can only store up to 255 bytes.
          //
          traverse_short_string (mi);
          break;
        }
      case sql_type::VARBINARY:
      case sql_type::BLOB:
      case sql_type::MEDIUMBLOB:
      case sql_type::LONGBLOB:
        {
          if (mi.st->range && mi.st->range_value <= 255)
            traverse_short_string (mi);
          else
            traverse_long_string (mi);

          break;
        }

        // Other types.
        //
      case sql_type::BIT:
        {
          traverse_bit (mi);
          break;
        }
      case sql_type::ENUM:
        {
          traverse_enum (mi);
          break;
        }
      case sql_type::SET:
        {
          traverse_set (mi);
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

    namespace
    {
      const char* integer_types[] =
      {
        "char",
        "short",
        "int",
        "int",
        "long long"
      };

      const char* float_types[] =
      {
        "float",
        "double"
      };
    }

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
    traverse_integer (member_info& mi)
    {
      if (mi.st->unsign)
        type_ = "unsigned ";
      else if (mi.st->type == sql_type::TINYINT)
        type_ = "signed ";

      type_ += integer_types[mi.st->type - sql_type::TINYINT];
    }

    void member_image_type::
    traverse_float (member_info& mi)
    {
      type_ = float_types[mi.st->type - sql_type::FLOAT];
    }

    void member_image_type::
    traverse_decimal (member_info&)
    {
      type_ = "details::buffer";
    }

    void member_image_type::
    traverse_date_time (member_info& mi)
    {
      if (mi.st->type == sql_type::YEAR)
        type_ = "short";
      else
        type_ = "MYSQL_TIME";
    }

    void member_image_type::
    traverse_string (member_info&)
    {
      type_ = "details::buffer";
    }

    void member_image_type::
    traverse_bit (member_info&)
    {
      type_ = "unsigned char*";
    }

    void member_image_type::
    traverse_enum (member_info& mi)
    {
      // Represented as either integer or string.
      //
      type_ = "mysql::value_traits< " + mi.fq_type () +
        ", mysql::id_enum >::image_type";
    }

    void member_image_type::
    traverse_set (member_info&)
    {
      // Represented as string.
      //
      type_ = "details::buffer";
    }

    //
    // member_database_type
    //

    namespace
    {
      const char* integer_database_id[] =
      {
        "id_tiny",
        "id_utiny",
        "id_short",
        "id_ushort",
        "id_long",   // INT24
        "id_ulong",  // INT24 UNSIGNED
        "id_long",
        "id_ulong",
        "id_longlong",
        "id_ulonglong"
      };

      const char* float_database_id[] =
      {
        "id_float",
        "id_double"
      };

      const char* date_time_database_id[] =
      {
        "id_date",
        "id_time",
        "id_datetime",
        "id_timestamp",
        "id_year"
      };

      const char* char_bin_database_id[] =
      {
        "id_string", // CHAR
        "id_blob",   // BINARY,
        "id_string", // VARCHAR
        "id_blob",   // VARBINARY
        "id_string", // TINYTEXT
        "id_blob",   // TINYBLOB
        "id_string", // TEXT
        "id_blob",   // BLOB
        "id_string", // MEDIUMTEXT
        "id_blob",   // MEDIUMBLOB
        "id_string", // LONGTEXT
        "id_blob"    // LONGBLOB
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
    traverse_integer (member_info& mi)
    {
      size_t i (
        (mi.st->type - sql_type::TINYINT) * 2 + (mi.st->unsign ? 1 : 0));
      type_id_ = string ("mysql::") + integer_database_id[i];
    }

    void member_database_type_id::
    traverse_float (member_info& mi)
    {
      type_id_ = string ("mysql::") +
        float_database_id[mi.st->type - sql_type::FLOAT];
    }

    void member_database_type_id::
    traverse_decimal (member_info&)
    {
      type_id_ = "mysql::id_decimal";
    }

    void member_database_type_id::
    traverse_date_time (member_info& mi)
    {
      type_id_ = string ("mysql::") +
        date_time_database_id[mi.st->type - sql_type::DATE];
    }

    void member_database_type_id::
    traverse_string (member_info& mi)
    {
      type_id_ = string ("mysql::") +
        char_bin_database_id[mi.st->type - sql_type::CHAR];
    }

    void member_database_type_id::
    traverse_bit (member_info&)
    {
      type_id_ = "mysql::id_bit";
    }

    void member_database_type_id::
    traverse_enum (member_info&)
    {
      type_id_ = "mysql::id_enum";
    }

    void member_database_type_id::
    traverse_set (member_info&)
    {
      type_id_ = "mysql::id_set";
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
