// file      : odb/sqlite/result.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_SQLITE_RESULT_HXX
#define ODB_SQLITE_RESULT_HXX

#include <odb/pre.hxx>

#include <odb/traits.hxx>
#include <odb/result.hxx>

#include <odb/details/shared-ptr.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/forward.hxx> // query, query_params
#include <odb/sqlite/statement.hxx>

#include <odb/sqlite/details/export.hxx>

namespace odb
{
  namespace sqlite
  {
    class LIBODB_SQLITE_EXPORT result_impl_base
    {
    public:
      result_impl_base (const query&, details::shared_ptr<select_statement>);

    protected:
      // We need to hold on to the query parameters because SQLite uses
      // the parameter buffers to find each next row.
      //
      details::shared_ptr<query_params> params_;
      details::shared_ptr<select_statement> statement_;
    };
  }
}

#include <odb/post.hxx>

#endif // ODB_SQLITE_RESULT_HXX

// Include result specializations so that the user code only needs
// to include this header.
//

#include <odb/sqlite/object-result.hxx>
#include <odb/sqlite/view-result.hxx>
