# DO NOT EDIT! GENERATED AUTOMATICALLY!
# Copyright (C) 2002-2011 Free Software Foundation, Inc.
#
# This file is free software, distributed under the terms of the GNU
# General Public License.  As a special exception to the GNU General
# Public License, this file may be distributed as part of a program
# that contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
#
# This file represents the compiled summary of the specification in
# gnulib-cache.m4. It lists the computed macro invocations that need
# to be invoked from configure.ac.
# In projects that use version control, this file can be treated like
# other built files.


# This macro should be invoked from ./configure.ac, in the section
# "Checks for programs", right after AC_PROG_CC, and certainly before
# any checks for libraries, header files, types and library functions.
AC_DEFUN([xgl_EARLY],
[
  m4_pattern_forbid([^gl_[A-Z]])dnl the gnulib macro namespace
  m4_pattern_allow([^gl_ES$])dnl a valid locale name
  m4_pattern_allow([^gl_LIBOBJS$])dnl a variable
  m4_pattern_allow([^gl_LTLIBOBJS$])dnl a variable
  AC_REQUIRE([AC_PROG_RANLIB])
  # Code from module crypto/hmac-md5:
  # Code from module crypto/md5:
  # Code from module extensions:
  AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])
  # Code from module havelib:
  # Code from module lib-msvc-compat:
  # Code from module lib-symbol-versions:
  # Code from module memxor:
])

# This macro should be invoked from ./configure.ac, in the section
# "Check for header files, types and library functions".
AC_DEFUN([xgl_INIT],
[
  AM_CONDITIONAL([GL_COND_LIBTOOL], [true])
  gl_cond_libtool=true
  gl_m4_base='gl/m4'
  m4_pushdef([AC_LIBOBJ], m4_defn([xgl_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([xgl_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([xgl_LIBSOURCES]))
  m4_pushdef([xgl_LIBSOURCES_LIST], [])
  m4_pushdef([xgl_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='gl'
  # Code from module crypto/hmac-md5:
  gl_HMAC_MD5
  # Code from module crypto/md5:
  gl_MD5
  # Code from module extensions:
  # Code from module havelib:
  # Code from module lib-msvc-compat:
  gl_LD_OUTPUT_DEF
  # Code from module lib-symbol-versions:
  gl_LD_VERSION_SCRIPT
  # Code from module memxor:
  gl_MEMXOR
  # End of code from modules
  m4_ifval(xgl_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([xgl_LIBSOURCES_DIR])[ ||
      for gl_file in ]xgl_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([xgl_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([xgl_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([xgl_LIBSOURCES_DIR])
  m4_popdef([xgl_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    xgl_libobjs=
    xgl_ltlibobjs=
    if test -n "$xgl_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $xgl_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        xgl_libobjs="$xgl_libobjs $i.$ac_objext"
        xgl_ltlibobjs="$xgl_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([xgl_LIBOBJS], [$xgl_libobjs])
    AC_SUBST([xgl_LTLIBOBJS], [$xgl_ltlibobjs])
  ])
  gltests_libdeps=
  gltests_ltlibdeps=
  m4_pushdef([AC_LIBOBJ], m4_defn([xgltests_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([xgltests_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([xgltests_LIBSOURCES]))
  m4_pushdef([xgltests_LIBSOURCES_LIST], [])
  m4_pushdef([xgltests_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='gl/tests'
changequote(,)dnl
  xgltests_WITNESS=IN_`echo "${PACKAGE-$PACKAGE_TARNAME}" | LC_ALL=C tr abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ | LC_ALL=C sed -e 's/[^A-Z0-9_]/_/g'`_GNULIB_TESTS
changequote([, ])dnl
  AC_SUBST([xgltests_WITNESS])
  gl_module_indicator_condition=$xgltests_WITNESS
  m4_pushdef([gl_MODULE_INDICATOR_CONDITION], [$gl_module_indicator_condition])
  m4_popdef([gl_MODULE_INDICATOR_CONDITION])
  m4_ifval(xgltests_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([xgltests_LIBSOURCES_DIR])[ ||
      for gl_file in ]xgltests_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([xgltests_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([xgltests_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([xgltests_LIBSOURCES_DIR])
  m4_popdef([xgltests_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    xgltests_libobjs=
    xgltests_ltlibobjs=
    if test -n "$xgltests_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $xgltests_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        xgltests_libobjs="$xgltests_libobjs $i.$ac_objext"
        xgltests_ltlibobjs="$xgltests_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([xgltests_LIBOBJS], [$xgltests_libobjs])
    AC_SUBST([xgltests_LTLIBOBJS], [$xgltests_ltlibobjs])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into xgl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([xgl_LIBOBJ], [
  AS_LITERAL_IF([$1], [xgl_LIBSOURCES([$1.c])])dnl
  xgl_LIBOBJS="$xgl_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into xgl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([xgl_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [xgl_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([xgl_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([xgl_LIBSOURCES_DIR], [gl])
      m4_append([xgl_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into xgltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([xgltests_LIBOBJ], [
  AS_LITERAL_IF([$1], [xgltests_LIBSOURCES([$1.c])])dnl
  xgltests_LIBOBJS="$xgltests_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into xgltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([xgltests_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [xgltests_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([xgltests_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([xgltests_LIBSOURCES_DIR], [gl/tests])
      m4_append([xgltests_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# This macro records the list of files which have been installed by
# gnulib-tool and may be removed by future gnulib-tool invocations.
AC_DEFUN([xgl_FILE_LIST], [
  build-aux/config.rpath
  lib/hmac-md5.c
  lib/hmac.h
  lib/md5.c
  lib/md5.h
  lib/memxor.c
  lib/memxor.h
  m4/00gnulib.m4
  m4/extensions.m4
  m4/gnulib-common.m4
  m4/hmac-md5.m4
  m4/ld-output-def.m4
  m4/ld-version-script.m4
  m4/lib-ld.m4
  m4/lib-link.m4
  m4/lib-prefix.m4
  m4/md5.m4
  m4/memxor.m4
])