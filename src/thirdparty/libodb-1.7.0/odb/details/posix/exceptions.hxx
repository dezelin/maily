// file      : odb/details/posix/exceptions.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_DETAILS_POSIX_EXCEPTIONS_HXX
#define ODB_DETAILS_POSIX_EXCEPTIONS_HXX

#include <odb/pre.hxx>

#include <odb/details/export.hxx>
#include <odb/details/exception.hxx>

namespace odb
{
  namespace details
  {
    struct LIBODB_EXPORT posix_exception: details::exception
    {
      posix_exception (int code) : code_ (code) {}

      int
      code () const {return code_;}

      virtual const char*
      what () const throw ();

    private:
      int code_;
    };
  }
}

#include <odb/post.hxx>

#endif // ODB_DETAILS_POSIX_EXCEPTIONS_HXX
