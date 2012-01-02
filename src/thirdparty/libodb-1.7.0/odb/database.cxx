// file      : odb/database.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#include <odb/database.hxx>

namespace odb
{
  database::
  ~database ()
  {
  }

  unsigned long long database::
  execute (const char* st, std::size_t n)
  {
    if (!transaction::has_current ())
      throw not_in_transaction ();

    connection_type& c (transaction::current ().connection ());
    return c.execute (st, n);
  }
}
