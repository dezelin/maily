// file      : odb/semantics/class.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v3; see accompanying LICENSE file

#include <odb/gcc.hxx> // TYPE_HAS_DEFAULT_CONSTRUCTOR

#include <cutl/compiler/type-info.hxx>
#include <odb/semantics/class.hxx>

namespace semantics
{
  inherits::
  inherits (access_type access, bool virt)
      : virt_ (virt), access_ (access)
  {
  }

  class_::
  class_ (path const& file, size_t line, size_t column, tree tn)
      : node (file, line, column, tn)
  {
  }

  bool class_::
  default_ctor () const
  {
    return TYPE_HAS_DEFAULT_CONSTRUCTOR (tree_node ());
  }

  bool class_::
  complete () const
  {
    return COMPLETE_TYPE_P (tree_node ());
  }

  bool class_::
  abstract () const
  {
    return CLASSTYPE_PURE_VIRTUALS (tree_node ());
  }

  // type info
  //
  namespace
  {
    struct init
    {
      init ()
      {
        using compiler::type_info;

        // inherits
        //
        {
          type_info ti (typeid (inherits));
          ti.add_base (typeid (edge));
          insert (ti);
        }

        // class_
        //
        {
          type_info ti (typeid (class_));
          ti.add_base (typeid (type));
          ti.add_base (typeid (scope));
          insert (ti);
        }
      }
    } init_;
  }
}
