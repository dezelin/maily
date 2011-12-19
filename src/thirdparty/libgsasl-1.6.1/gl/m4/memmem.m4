# memmem.m4 serial 20
dnl Copyright (C) 2002, 2003, 2004, 2007, 2008, 2009, 2010 Free Software
dnl Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl Check that memmem is present.
AC_DEFUN([gl_FUNC_MEMMEM_SIMPLE],
[
  dnl Persuade glibc <string.h> to declare memmem().
  AC_REQUIRE([AC_USE_SYSTEM_EXTENSIONS])

  AC_REQUIRE([gl_HEADER_STRING_H_DEFAULTS])
  AC_REPLACE_FUNCS([memmem])
  AC_CHECK_DECLS_ONCE([memmem])
  if test $ac_cv_have_decl_memmem = no; then
    HAVE_DECL_MEMMEM=0
  else
    dnl Detect http://sourceware.org/bugzilla/show_bug.cgi?id=12092.
    AC_CACHE_CHECK([whether memmem works],
      [gl_cv_func_memmem_works_always],
      [AC_RUN_IFELSE([AC_LANG_PROGRAM([[
#include <string.h> /* for memmem */
#define P "_EF_BF_BD"
#define HAYSTACK "F_BD_CE_BD" P P P P "_C3_88_20" P P P "_C3_A7_20" P
#define NEEDLE P P P P P
]], [[return !!memmem (HAYSTACK, strlen (HAYSTACK), NEEDLE, strlen (NEEDLE));
    ]])],
        [gl_cv_func_memmem_works_always=yes],
        [gl_cv_func_memmem_works_always=no],
        [dnl glibc 2.12 and cygwin 1.7.7 have a known bug.  Assume that it
         dnl works on all other platforms, even if it is not linear.
         AC_EGREP_CPP([Lucky user],
           [
#ifdef __GNU_LIBRARY__
 #include <features.h>
 #if ((__GLIBC__ == 2 && __GLIBC_MINOR__ > 12) || (__GLIBC__ > 2)) \
     && !defined __UCLIBC__
  Lucky user
 #endif
#elif defined __CYGWIN__
 #include <cygwin/version.h>
 #if CYGWIN_VERSION_DLL_COMBINED > CYGWIN_VERSION_DLL_MAKE_COMBINED (1007, 7)
  Lucky user
 #endif
#else
  Lucky user
#endif
           ],
           [gl_cv_func_memmem_works_always=yes],
           [gl_cv_func_memmem_works_always="guessing no"])
        ])
      ])
    if test "$gl_cv_func_memmem_works_always" != yes; then
      REPLACE_MEMMEM=1
      AC_LIBOBJ([memmem])
    fi
  fi
  gl_PREREQ_MEMMEM
]) # gl_FUNC_MEMMEM_SIMPLE

dnl Additionally, check that memmem is efficient and handles empty needles.
AC_DEFUN([gl_FUNC_MEMMEM],
[
  AC_REQUIRE([gl_FUNC_MEMMEM_SIMPLE])
  if test $HAVE_DECL_MEMMEM = 1 && test $REPLACE_MEMMEM = 0; then
    AC_CACHE_CHECK([whether memmem works in linear time],
      [gl_cv_func_memmem_works_fast],
      [AC_RUN_IFELSE([AC_LANG_PROGRAM([[
#include <signal.h> /* for signal */
#include <string.h> /* for memmem */
#include <stdlib.h> /* for malloc */
#include <unistd.h> /* for alarm */
static void quit (int sig) { exit (sig + 128); }
]], [[
    int result = 0;
    size_t m = 1000000;
    char *haystack = (char *) malloc (2 * m + 1);
    char *needle = (char *) malloc (m + 1);
    /* Failure to compile this test due to missing alarm is okay,
       since all such platforms (mingw) also lack memmem.  */
    signal (SIGALRM, quit);
    alarm (5);
    /* Check for quadratic performance.  */
    if (haystack && needle)
      {
        memset (haystack, 'A', 2 * m);
        haystack[2 * m] = 'B';
        memset (needle, 'A', m);
        needle[m] = 'B';
        if (!memmem (haystack, 2 * m + 1, needle, m + 1))
          result |= 1;
      }
    /* Check for empty needle behavior.  */
    if (!memmem ("a", 1, 0, 0))
      result |= 2;
    return result;
    ]])],
        [gl_cv_func_memmem_works_fast=yes], [gl_cv_func_memmem_works_fast=no],
        [dnl Only glibc > 2.12 and cygwin > 1.7.7 are known to have a
         dnl bug-free memmem that works in linear time.
         AC_EGREP_CPP([Lucky user],
           [
#include <features.h>
#ifdef __GNU_LIBRARY__
 #if ((__GLIBC__ == 2 && __GLIBC_MINOR__ > 12) || (__GLIBC__ > 2)) \
     && !defined __UCLIBC__
  Lucky user
 #endif
#endif
#ifdef __CYGWIN__
 #include <cygwin/version.h>
 #if CYGWIN_VERSION_DLL_COMBINED > CYGWIN_VERSION_DLL_MAKE_COMBINED (1007, 7)
  Lucky user
 #endif
#endif
           ],
           [gl_cv_func_memmem_works_fast=yes],
           [gl_cv_func_memmem_works_fast="guessing no"])
        ])
      ])
    if test "$gl_cv_func_memmem_works_fast" != yes; then
      REPLACE_MEMMEM=1
      AC_LIBOBJ([memmem])
    fi
  fi
]) # gl_FUNC_MEMMEM

# Prerequisites of lib/memmem.c.
AC_DEFUN([gl_PREREQ_MEMMEM], [:])
