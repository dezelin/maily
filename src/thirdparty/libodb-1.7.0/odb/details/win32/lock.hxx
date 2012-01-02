// file      : odb/details/win32/lock.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_DETAILS_WIN32_LOCK_HXX
#define ODB_DETAILS_WIN32_LOCK_HXX

#include <odb/pre.hxx>

#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  undef WIN32_LEAN_AND_MEAN
#else
#  include <windows.h>
#endif

namespace odb
{
  namespace details
  {
    // Critical section lock. Not exported; for internal use only.
    //
    struct win32_lock
    {
      win32_lock (CRITICAL_SECTION& cs)
          : cs_ (&cs)
      {
        EnterCriticalSection (cs_);
      }

      ~win32_lock ()
      {
        if (cs_ != 0)
          LeaveCriticalSection (cs_);
      }

      void
      unlock ()
      {
        if (cs_ != 0)
        {
          LeaveCriticalSection (cs_);
          cs_ = 0;
        }
      }

    private:
      CRITICAL_SECTION* cs_;
    };
  }
}

#include <odb/post.hxx>

#endif // ODB_DETAILS_WIN32_LOCK_HXX
