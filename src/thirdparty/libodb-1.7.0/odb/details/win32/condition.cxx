// file      : odb/details/win32/condition.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#include <odb/details/win32/condition.hxx>
#include <odb/details/win32/exceptions.hxx>

namespace odb
{
  namespace details
  {
    void condition::
    signal ()
    {
      mutex_.lock ();

      if (waiters_ > signals_)
      {
        if (signals_++ == 0)
        {
          if (SetEvent (event_) == 0)
            throw win32_exception ();
        }
      }

      mutex_.unlock ();
    }

    void condition::
    wait ()
    {
      // When we enter this functions the mutex is locked. When we
      // return from this function the mutex must be locked.
      //
      waiters_++;
      mutex_.unlock ();

      if (WaitForSingleObject (event_, INFINITE) != 0)
        throw win32_exception ();

      mutex_.lock ();
      waiters_--;
      signals_--;

      if (signals_ > 0)
      {
        // Wake up the next thread.
        //
        if (SetEvent (event_) == 0)
          throw win32_exception ();
      }
    }
  }
}
