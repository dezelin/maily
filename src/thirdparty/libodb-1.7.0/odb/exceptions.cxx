// file      : odb/exceptions.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#include <sstream>

#include <odb/exceptions.hxx>

using namespace std;

namespace odb
{
  const char* null_pointer::
  what () const throw ()
  {
    return "NULL pointer";
  }

  const char* already_in_transaction::
  what () const throw ()
  {
    return "transaction already in progress in this thread";
  }

  const char* not_in_transaction::
  what () const throw ()
  {
    return "operation can only be performed in transaction";
  }

  const char* transaction_already_finalized::
  what () const throw ()
  {
    return "transaction already committed or rolled back";
  }

  const char* already_in_session::
  what () const throw ()
  {
    return "session already in effect in this thread";
  }

  const char* not_in_session::
  what () const throw ()
  {
    return "session not in effect in this thread";
  }

  const char* deadlock::
  what () const throw ()
  {
    return "transaction aborted due to deadlock";
  }

  const char* connection_lost::
  what () const throw ()
  {
    return "connection to database lost";
  }

  const char* timeout::
  what () const throw ()
  {
    return "database operation timeout";
  }

  const char* object_not_persistent::
  what () const throw ()
  {
    return "object not persistent";
  }

  const char* object_already_persistent::
  what () const throw ()
  {
    return "object already persistent";
  }

  const char* object_changed::
  what () const throw ()
  {
    return "object changed concurrently";
  }

  const char* result_not_cached::
  what () const throw ()
  {
    return "query result is not cached";
  }

  unknown_schema::
  unknown_schema (const std::string& name)
      : name_ (name)
  {
    ostringstream ostr;
    ostr << "unknown database schema '" << name << "'";
    what_ = ostr.str ();
  }

  unknown_schema::
  ~unknown_schema () throw ()
  {
  }

  const char* unknown_schema::
  what () const throw ()
  {
    return what_.c_str ();
  }
}
