// file      : odb/details/posix/tls.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

namespace odb
{
  namespace details
  {
    template <typename T>
    inline tls<T>::
    tls ()
    {
    }

    template <typename T>
    inline tls<T*>::
    tls ()
    {
    }
  }
}
