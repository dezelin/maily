// file      : odb/details/win32/tls-init.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_DETAILS_WIN32_TLS_INIT_HXX
#define ODB_DETAILS_WIN32_TLS_INIT_HXX

#include <odb/pre.hxx>

namespace odb
{
  namespace details
  {
    void
    tls_process_start ();

    void
    tls_process_end (bool safe);

    void
    tls_thread_end ();
  }
}

#include <odb/post.hxx>

#endif // ODB_DETAILS_WIN32_TLS_INIT_HXX
