// file      : odb/sqlite/sqlite-types.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_SQLITE_SQLITE_TYPES_HXX
#define ODB_SQLITE_SQLITE_TYPES_HXX

#include <odb/pre.hxx>

#include <cstddef>  // std::size_t

namespace odb
{
  namespace sqlite
  {
    // The SQLite parameter/result binding. This data structures is modelled
    // after MYSQL_BIND from MySQL.
    //
    struct bind
    {
      enum buffer_type
      {
        integer, // Buffer is long long; size, capacity, truncated are unused.
        real,    // Buffer is double; size, capacity, truncated are unused.
        text,    // Buffer is a char array.
        blob     // Buffer is a char array.
      };

      buffer_type type;
      void* buffer;
      std::size_t* size;
      std::size_t capacity;
      bool* is_null;
      bool* truncated;
    };
  }
}

#include <odb/post.hxx>

#endif // ODB_SQLITE_SQLITE_TYPES_HXX
