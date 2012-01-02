// file      : odb/sqlite/exceptions.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_SQLITE_EXCEPTIONS_HXX
#define ODB_SQLITE_EXCEPTIONS_HXX

#include <odb/pre.hxx>

#include <string>

#include <odb/exceptions.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/details/export.hxx>

namespace odb
{
  namespace sqlite
  {
    struct LIBODB_SQLITE_EXPORT database_exception: odb::database_exception
    {
      database_exception (int error,
                          int extended_error,
                          const std::string& message);

      ~database_exception () throw ();

      int
      error () const
      {
        return error_;
      }

      int
      extended_error () const
      {
        return extended_error_;
      }

      const std::string&
      message () const
      {
        return message_;
      }

      virtual const char*
      what () const throw ();

    private:
      int error_;
      int extended_error_;
      std::string message_;
      std::string what_;
    };

    struct LIBODB_SQLITE_EXPORT cli_exception: odb::exception
    {
      cli_exception (const std::string& what);
      ~cli_exception () throw ();

      virtual const char*
      what () const throw ();

    private:
      std::string what_;
    };
  }
}

#include <odb/post.hxx>

#endif // ODB_SQLITE_EXCEPTIONS_HXX
