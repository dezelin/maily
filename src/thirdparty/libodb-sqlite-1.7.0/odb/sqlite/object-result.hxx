// file      : odb/sqlite/object-result.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_SQLITE_OBJECT_RESULT_HXX
#define ODB_SQLITE_OBJECT_RESULT_HXX

#include <odb/pre.hxx>

#include <cstddef> // std::size_t

#include <odb/details/shared-ptr.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/forward.hxx> // query, object_statements
#include <odb/sqlite/result.hxx>
#include <odb/sqlite/statement.hxx>

namespace odb
{
  namespace sqlite
  {
    template <typename T>
    class object_result_impl: public odb::object_result_impl<T>,
                              public result_impl_base
    {
    public:
      typedef odb::object_result_impl<T> base_type;

      typedef typename base_type::object_traits object_traits;
      typedef typename base_type::object_type object_type;
      typedef typename base_type::id_type id_type;

      typedef typename base_type::pointer_type pointer_type;
      typedef typename base_type::pointer_traits pointer_traits;

      virtual
      ~object_result_impl ();

      object_result_impl (const query&,
                          details::shared_ptr<select_statement>,
                          object_statements<object_type>&);

      virtual void
      load (object_type&, bool fetch);

      virtual id_type
      load_id ();

      virtual void
      next ();

      virtual void
      cache ();

      virtual std::size_t
      size ();

      using base_type::current;

    private:
      void
      load_image ();

    private:
      object_statements<object_type>& statements_;
    };

    template <typename T>
    class object_result_impl_no_id: public odb::object_result_impl_no_id<T>,
                                    public result_impl_base
    {
    public:
      typedef odb::object_result_impl_no_id<T> base_type;

      typedef typename base_type::object_traits object_traits;
      typedef typename base_type::object_type object_type;

      typedef typename base_type::pointer_type pointer_type;
      typedef typename base_type::pointer_traits pointer_traits;

      virtual
      ~object_result_impl_no_id ();

      object_result_impl_no_id (const query&,
                                details::shared_ptr<select_statement>,
                                object_statements_no_id<object_type>&);

      virtual void
      load (object_type&);

      virtual void
      next ();

      virtual void
      cache ();

      virtual std::size_t
      size ();

      using base_type::current;

    private:
      object_statements_no_id<object_type>& statements_;
    };
  }
}

#include <odb/sqlite/object-result.txx>

#include <odb/post.hxx>

#endif // ODB_SQLITE_OBJECT_RESULT_HXX
