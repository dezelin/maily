// file      : odb/semantics/relational/column.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v3; see accompanying LICENSE file

#include <cutl/compiler/type-info.hxx>

#include <odb/semantics/relational/column.hxx>

namespace semantics
{
  namespace relational
  {
    // type info
    //
    namespace
    {
      struct init
      {
        init ()
        {
          using compiler::type_info;

          // column
          //
          {
            type_info ti (typeid (column));
            ti.add_base (typeid (nameable));
            insert (ti);
          }
        }
      } init_;
    }
  }
}
