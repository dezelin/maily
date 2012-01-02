// file      : odb/std-set-traits.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_STD_SET_TRAITS_HXX
#define ODB_STD_SET_TRAITS_HXX

#include <odb/pre.hxx>

#include <set>

#include <odb/container-traits.hxx>

namespace odb
{
  template <typename V, typename C, typename A>
  class access::container_traits<std::set<V, C, A> >
  {
  public:
    static container_kind const kind = ck_set;

    typedef std::set<V, C, A> container_type;
    typedef V value_type;

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

  // C++-03 does not guarantee insertion order of equal values but C++-0x
  // changes that. The current implementation in the generated code does
  // not guarantee this either.
  //
  template <typename V, typename C, typename A>
  class access::container_traits<std::multiset<V, C, A> >
  {
  public:
    static container_kind const kind = ck_multiset;

    typedef std::multiset<V, C, A> container_type;
    typedef V value_type;

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

#endif // ODB_STD_SET_TRAITS_HXX
