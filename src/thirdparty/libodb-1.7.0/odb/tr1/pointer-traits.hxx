// file      : odb/tr1/pointer-traits.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_TR1_POINTER_TRAITS_HXX
#define ODB_TR1_POINTER_TRAITS_HXX

#include <odb/pre.hxx>

//
// This header assumes that the necessary TR1 header has already
// been included.
//

#include <odb/pointer-traits.hxx>
#include <odb/details/meta/remove-const.hxx>

namespace odb
{
  // Specialization for std::tr1::shared_ptr.
  //
  template <typename T>
  class pointer_traits<std::tr1::shared_ptr<T> >
  {
  public:
    static const pointer_kind kind = pk_shared;
    static const bool lazy = false;

    typedef T element_type;
    typedef std::tr1::shared_ptr<element_type> pointer_type;
    typedef std::tr1::shared_ptr<const element_type> const_pointer_type;
    typedef typename odb::details::meta::remove_const<element_type>::result
    unrestricted_element_type;
    typedef std::tr1::shared_ptr<unrestricted_element_type>
    unrestricted_pointer_type;
    typedef smart_ptr_guard<pointer_type> guard;

    static element_type*
    get_ptr (const pointer_type& p)
    {
      return p.get ();
    }

    static element_type&
    get_ref (const pointer_type& p)
    {
      return *p;
    }

    static bool
    null_ptr (const pointer_type& p)
    {
      return !p;
    }

    static unrestricted_pointer_type
    cast (const pointer_type& p)
    {
      return std::tr1::const_pointer_cast<unrestricted_element_type> (p);
    }

  public:
    static void*
    allocate (std::size_t n)
    {
      return operator new (n);
    }

    static void
    free (void* p)
    {
      operator delete (p);
    }
  };

  // Specialization for std::tr1::weak_ptr.
  //
  template <typename T>
  class pointer_traits<std::tr1::weak_ptr<T> >
  {
  public:
    static const pointer_kind kind = pk_weak;
    static const bool lazy = false;

    typedef T element_type;
    typedef std::tr1::weak_ptr<element_type> pointer_type;
    typedef std::tr1::shared_ptr<element_type> strong_pointer_type;

    static strong_pointer_type
    lock (const pointer_type& p)
    {
      return p.lock ();
    }
  };
}

#include <odb/post.hxx>

#endif // ODB_TR1_POINTER_TRAITS_HXX
