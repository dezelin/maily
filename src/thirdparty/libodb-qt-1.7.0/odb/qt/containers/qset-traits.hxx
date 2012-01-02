// file      : odb/qt/containers/qset-traits.hxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_QT_CONTAINER_QSET_TRAITS_HXX
#define ODB_QT_CONTAINER_QSET_TRAITS_HXX

#include <odb/pre.hxx>

#include <QtCore/QSet>

#include <odb/container-traits.hxx>

namespace odb
{
  template <typename T>
  class access::container_traits<QSet<T> >
  {
  public:
    static const container_kind kind = ck_set;

    typedef QSet<T> container_type;
    typedef T value_type;

    typedef set_functions<value_type> functions;

  public:
    static void
    persist (const container_type& c, const functions& f)
    {
      for (typename container_type::const_iterator i (c.begin ()),
             e (c.end ()); i != e; ++i)
        f.insert_one (*i);
    }

    static void
    load (container_type& c, bool more, const functions& f)
    {
      c.clear ();

      while (more)
      {
        value_type v;
        more = f.load_all (v);
        c.insert (v);
      }
    }

    static void
    update (const container_type& c, const functions& f)
    {
      f.delete_all ();

      for (typename container_type::const_iterator i (c.begin ()),
             e (c.end ()); i != e; ++i)
        f.insert_one (*i);
    }

    static void
    erase (const functions& f)
    {
      f.delete_all ();
    }
  };
}

#include <odb/post.hxx>

#endif // ODB_QT_CONTAINER_QSET_TRAITS_HXX
