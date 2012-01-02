// file      : odb/statement.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_STATEMENT_HXX
#define ODB_STATEMENT_HXX

#include <odb/pre.hxx>

#include <odb/forward.hxx>

#include <odb/details/export.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  class LIBODB_EXPORT statement: public details::shared_base
  {
  public:
    virtual
    ~statement () = 0;

    statement () {}

  private:
    statement (const statement&);
    statement& operator= (const statement&);

  public:
    virtual const char*
    text () const = 0;
  };
}

#include <odb/post.hxx>

#endif // ODB_MYSQL_STATEMENT_HXX
