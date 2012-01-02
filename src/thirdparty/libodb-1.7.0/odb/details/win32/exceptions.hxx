// file      : odb/details/win32/exceptions.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_DETAILS_WIN32_EXCEPTIONS_HXX
#define ODB_DETAILS_WIN32_EXCEPTIONS_HXX

#include <odb/pre.hxx>

#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  undef WIN32_LEAN_AND_MEAN
#else
#  include <windows.h>
#endif

#include <odb/details/export.hxx>
#include <odb/details/exception.hxx>

namespace odb
{
  namespace details
  {
    struct LIBODB_EXPORT win32_exception: details::exception
    {
      win32_exception () : code_ (GetLastError ()) {}
      win32_exception (DWORD code) : code_ (code) {}

      DWORD
      code () const {return code_;}

      virtual const char*
      what () const throw ();

    private:
      DWORD code_;
    };
  }
}

#include <odb/post.hxx>

#endif // ODB_DETAILS_WIN32_EXCEPTIONS_HXX
