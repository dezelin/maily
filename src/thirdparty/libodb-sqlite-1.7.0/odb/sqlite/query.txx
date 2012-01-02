// file      : odb/sqlite/query.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

namespace odb
{
  namespace sqlite
  {
    // query
    //

    template <database_type_id ID>
    query::
    query (const query_column<bool, ID>& c)
        : parameters_ (new (details::shared) query_params)
    {
      // Cannot use IS TRUE here since database type can be a non-
      // integral type.
      //
      append (c.table (), c.column ());
      append ("=");
      append<bool, ID> (val_bind<bool> (true));
    }

    // query_column
    //
    template <typename T, database_type_id ID>
    query query_column<T, ID>::
    in (const T& v1, const T& v2) const
    {
      query q (table_, column_);
      q += "IN (";
      q.append<T, ID> (val_bind<T> (v1));
      q += ",";
      q.append<T, ID> (val_bind<T> (v2));
      q += ")";
      return q;
    }

    template <typename T, database_type_id ID>
    query query_column<T, ID>::
    in (const T& v1, const T& v2, const T& v3) const
    {
      query q (table_, column_);
      q += "IN (";
      q.append<T, ID> (val_bind<T> (v1));
      q += ",";
      q.append<T, ID> (val_bind<T> (v2));
      q += ",";
      q.append<T, ID> (val_bind<T> (v3));
      q += ")";
      return q;
    }

    template <typename T, database_type_id ID>
    query query_column<T, ID>::
    in (const T& v1, const T& v2, const T& v3, const T& v4) const
    {
      query q (table_, column_);
      q += "IN (";
      q.append<T, ID> (val_bind<T> (v1));
      q += ",";
      q.append<T, ID> (val_bind<T> (v2));
      q += ",";
      q.append<T, ID> (val_bind<T> (v3));
      q += ",";
      q.append<T, ID> (val_bind<T> (v4));
      q += ")";
      return q;
    }

    template <typename T, database_type_id ID>
    query query_column<T, ID>::
    in (const T& v1, const T& v2, const T& v3, const T& v4, const T& v5) const
    {
      query q (table_, column_);
      q += "IN (";
      q.append<T, ID> (val_bind<T> (v1));
      q += ",";
      q.append<T, ID> (val_bind<T> (v2));
      q += ",";
      q.append<T, ID> (val_bind<T> (v3));
      q += ",";
      q.append<T, ID> (val_bind<T> (v4));
      q += ",";
      q.append<T, ID> (val_bind<T> (v5));
      q += ")";
      return q;
    }

    template <typename T, database_type_id ID>
    template <typename I>
    query query_column<T, ID>::
    in_range (I begin, I end) const
    {
      query q (table_, column_);
      q += "IN (";

      for (I i (begin); i != end; ++i)
      {
        if (i != begin)
          q += ",";

        q.append<T, ID> (val_bind<T> (*i));
      }
      q += ")";
      return q;
    }
  }
}
