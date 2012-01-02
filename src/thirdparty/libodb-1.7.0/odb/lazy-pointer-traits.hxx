// file      : odb/lazy-pointer-traits.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_LAZY_POINTER_TRAITS_HXX
#define ODB_LAZY_POINTER_TRAITS_HXX

#include <odb/pre.hxx>

#include <odb/pointer-traits.hxx>
#include <odb/lazy-ptr.hxx>

namespace odb
{
  template <typename T>
  class pointer_traits< lazy_ptr<T> >
  {
  public:
    static const pointer_kind kind = pk_raw;
    static const bool lazy = true;

    typedef T element_type;
    typedef lazy_ptr<element_type> pointer_type;
    typedef element_type* eager_pointer_type;

    static bool
    null_ptr (const pointer_type& p)
    {
      return !p;
    }

    template <class O /* = T */>
    static typename object_traits<O>::id_type
    object_id (const pointer_type& p)
    {
      return p.object_id<O> ();
    }
  };

  template <typename T>
  class pointer_traits< lazy_auto_ptr<T> >
  {
  public:
    static const pointer_kind kind = pk_unique;
    static const bool lazy = true;

    typedef T element_type;
    typedef lazy_auto_ptr<element_type> pointer_type;
    typedef std::auto_ptr<element_type> eager_pointer_type;

    static bool
    null_ptr (const pointer_type& p)
    {
      return !p;
    }

    template <class O /* = T */>
    static typename object_traits<O>::id_type
    object_id (const pointer_type& p)
    {
      return p.object_id<O> ();
    }
  };
}

#include <odb/post.hxx>

#endif // ODB_LAZY_POINTER_TRAITS_HXX
