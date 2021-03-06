## DO NOT EDIT! GENERATED AUTOMATICALLY!
## Process this file with automake to produce Makefile.in.
# Copyright (C) 2002-2011 Free Software Foundation, Inc.
#
# This file is free software, distributed under the terms of the GNU
# General Public License.  As a special exception to the GNU General
# Public License, this file may be distributed as part of a program
# that contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
# Reproduce by: gnulib-tool --import --dir=. --lib=libgnu --source-base=gl --m4-base=gl/m4 --doc-base=doc --tests-base=gl/tests --aux-dir=build-aux --with-tests --lgpl --no-conditional-dependencies --libtool --macro-prefix=gl --no-vc-files autobuild byteswap check-version crypto/des crypto/md4 inline maintainer-makefile manywarnings strverscmp unistd warnings

AUTOMAKE_OPTIONS = 1.5 gnits

SUBDIRS =
noinst_HEADERS =
noinst_LIBRARIES =
noinst_LTLIBRARIES =
EXTRA_DIST =
BUILT_SOURCES =
SUFFIXES =
MOSTLYCLEANFILES = core *.stackdump
MOSTLYCLEANDIRS =
CLEANFILES =
DISTCLEANFILES =
MAINTAINERCLEANFILES =
SUBDIRS += tests
EXTRA_DIST += m4/gnulib-cache.m4

AM_CPPFLAGS =
AM_CFLAGS =

noinst_LTLIBRARIES += libgnu.la

libgnu_la_SOURCES =
libgnu_la_LIBADD = $(gl_LTLIBOBJS)
libgnu_la_DEPENDENCIES = $(gl_LTLIBOBJS)
EXTRA_libgnu_la_SOURCES =
libgnu_la_LDFLAGS = $(AM_LDFLAGS)
libgnu_la_LDFLAGS += -no-undefined

## begin gnulib module arg-nonnull

# The BUILT_SOURCES created by this Makefile snippet are not used via #include
# statements but through direct file reference. Therefore this snippet must be
# present in all Makefile.am that need it. This is ensured by the applicability
# 'all' defined above.

BUILT_SOURCES += arg-nonnull.h
# The arg-nonnull.h that gets inserted into generated .h files is the same as
# build-aux/arg-nonnull.h, except that it has the copyright header cut off.
arg-nonnull.h: $(top_srcdir)/build-aux/arg-nonnull.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	sed -n -e '/GL_ARG_NONNULL/,$$p' \
	  < $(top_srcdir)/build-aux/arg-nonnull.h \
	  > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += arg-nonnull.h arg-nonnull.h-t

ARG_NONNULL_H=arg-nonnull.h

EXTRA_DIST += $(top_srcdir)/build-aux/arg-nonnull.h

## end   gnulib module arg-nonnull

## begin gnulib module byteswap

BUILT_SOURCES += $(BYTESWAP_H)

# We need the following in order to create <byteswap.h> when the system
# doesn't have one.
if GL_GENERATE_BYTESWAP_H
byteswap.h: byteswap.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  cat $(srcdir)/byteswap.in.h; \
	} > $@-t && \
	mv -f $@-t $@
else
byteswap.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += byteswap.h byteswap.h-t

EXTRA_DIST += byteswap.in.h

## end   gnulib module byteswap

## begin gnulib module c++defs

# The BUILT_SOURCES created by this Makefile snippet are not used via #include
# statements but through direct file reference. Therefore this snippet must be
# present in all Makefile.am that need it. This is ensured by the applicability
# 'all' defined above.

BUILT_SOURCES += c++defs.h
# The c++defs.h that gets inserted into generated .h files is the same as
# build-aux/c++defs.h, except that it has the copyright header cut off.
c++defs.h: $(top_srcdir)/build-aux/c++defs.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	sed -n -e '/_GL_CXXDEFS/,$$p' \
	  < $(top_srcdir)/build-aux/c++defs.h \
	  > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += c++defs.h c++defs.h-t

CXXDEFS_H=c++defs.h

EXTRA_DIST += $(top_srcdir)/build-aux/c++defs.h

## end   gnulib module c++defs

## begin gnulib module check-version

libgnu_la_SOURCES += check-version.c

EXTRA_DIST += check-version.h

## end   gnulib module check-version

## begin gnulib module crypto/des

libgnu_la_SOURCES += des.c

EXTRA_DIST += des.h

## end   gnulib module crypto/des

## begin gnulib module crypto/md4

libgnu_la_SOURCES += md4.c

EXTRA_DIST += md4.h

## end   gnulib module crypto/md4

## begin gnulib module gnumakefile

distclean-local: clean-GNUmakefile
clean-GNUmakefile:
	test x'$(VPATH)' != x && rm -f $(top_builddir)/GNUmakefile || :

EXTRA_DIST += $(top_srcdir)/GNUmakefile

## end   gnulib module gnumakefile

## begin gnulib module maintainer-makefile

EXTRA_DIST += $(top_srcdir)/maint.mk

## end   gnulib module maintainer-makefile

## begin gnulib module stdbool

BUILT_SOURCES += $(STDBOOL_H)

# We need the following in order to create <stdbool.h> when the system
# doesn't have one that works.
if GL_GENERATE_STDBOOL_H
stdbool.h: stdbool.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's/@''HAVE__BOOL''@/$(HAVE__BOOL)/g' < $(srcdir)/stdbool.in.h; \
	} > $@-t && \
	mv $@-t $@
else
stdbool.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += stdbool.h stdbool.h-t

EXTRA_DIST += stdbool.in.h

## end   gnulib module stdbool

## begin gnulib module stddef

BUILT_SOURCES += $(STDDEF_H)

# We need the following in order to create <stddef.h> when the system
# doesn't have one that works with the given compiler.
if GL_GENERATE_STDDEF_H
stddef.h: stddef.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */' && \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_STDDEF_H''@|$(NEXT_STDDEF_H)|g' \
	      -e 's|@''HAVE_WCHAR_T''@|$(HAVE_WCHAR_T)|g' \
	      -e 's|@''REPLACE_NULL''@|$(REPLACE_NULL)|g' \
	      < $(srcdir)/stddef.in.h; \
	} > $@-t && \
	mv $@-t $@
else
stddef.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += stddef.h stddef.h-t

EXTRA_DIST += stddef.in.h

## end   gnulib module stddef

## begin gnulib module stdint

BUILT_SOURCES += $(STDINT_H)

# We need the following in order to create <stdint.h> when the system
# doesn't have one that works with the given compiler.
if GL_GENERATE_STDINT_H
stdint.h: stdint.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's/@''HAVE_STDINT_H''@/$(HAVE_STDINT_H)/g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_STDINT_H''@|$(NEXT_STDINT_H)|g' \
	      -e 's/@''HAVE_SYS_TYPES_H''@/$(HAVE_SYS_TYPES_H)/g' \
	      -e 's/@''HAVE_INTTYPES_H''@/$(HAVE_INTTYPES_H)/g' \
	      -e 's/@''HAVE_SYS_INTTYPES_H''@/$(HAVE_SYS_INTTYPES_H)/g' \
	      -e 's/@''HAVE_SYS_BITYPES_H''@/$(HAVE_SYS_BITYPES_H)/g' \
	      -e 's/@''HAVE_WCHAR_H''@/$(HAVE_WCHAR_H)/g' \
	      -e 's/@''HAVE_LONG_LONG_INT''@/$(HAVE_LONG_LONG_INT)/g' \
	      -e 's/@''HAVE_UNSIGNED_LONG_LONG_INT''@/$(HAVE_UNSIGNED_LONG_LONG_INT)/g' \
	      -e 's/@''APPLE_UNIVERSAL_BUILD''@/$(APPLE_UNIVERSAL_BUILD)/g' \
	      -e 's/@''BITSIZEOF_PTRDIFF_T''@/$(BITSIZEOF_PTRDIFF_T)/g' \
	      -e 's/@''PTRDIFF_T_SUFFIX''@/$(PTRDIFF_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_SIG_ATOMIC_T''@/$(BITSIZEOF_SIG_ATOMIC_T)/g' \
	      -e 's/@''HAVE_SIGNED_SIG_ATOMIC_T''@/$(HAVE_SIGNED_SIG_ATOMIC_T)/g' \
	      -e 's/@''SIG_ATOMIC_T_SUFFIX''@/$(SIG_ATOMIC_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_SIZE_T''@/$(BITSIZEOF_SIZE_T)/g' \
	      -e 's/@''SIZE_T_SUFFIX''@/$(SIZE_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_WCHAR_T''@/$(BITSIZEOF_WCHAR_T)/g' \
	      -e 's/@''HAVE_SIGNED_WCHAR_T''@/$(HAVE_SIGNED_WCHAR_T)/g' \
	      -e 's/@''WCHAR_T_SUFFIX''@/$(WCHAR_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_WINT_T''@/$(BITSIZEOF_WINT_T)/g' \
	      -e 's/@''HAVE_SIGNED_WINT_T''@/$(HAVE_SIGNED_WINT_T)/g' \
	      -e 's/@''WINT_T_SUFFIX''@/$(WINT_T_SUFFIX)/g' \
	      < $(srcdir)/stdint.in.h; \
	} > $@-t && \
	mv $@-t $@
else
stdint.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += stdint.h stdint.h-t

EXTRA_DIST += stdint.in.h

## end   gnulib module stdint

## begin gnulib module string

BUILT_SOURCES += string.h

# We need the following in order to create <string.h> when the system
# doesn't have one that works with the given compiler.
string.h: string.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(ARG_NONNULL_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */' && \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_STRING_H''@|$(NEXT_STRING_H)|g' \
	      -e 's/@''GNULIB_MBSLEN''@/$(GNULIB_MBSLEN)/g' \
	      -e 's/@''GNULIB_MBSNLEN''@/$(GNULIB_MBSNLEN)/g' \
	      -e 's/@''GNULIB_MBSCHR''@/$(GNULIB_MBSCHR)/g' \
	      -e 's/@''GNULIB_MBSRCHR''@/$(GNULIB_MBSRCHR)/g' \
	      -e 's/@''GNULIB_MBSSTR''@/$(GNULIB_MBSSTR)/g' \
	      -e 's/@''GNULIB_MBSCASECMP''@/$(GNULIB_MBSCASECMP)/g' \
	      -e 's/@''GNULIB_MBSNCASECMP''@/$(GNULIB_MBSNCASECMP)/g' \
	      -e 's/@''GNULIB_MBSPCASECMP''@/$(GNULIB_MBSPCASECMP)/g' \
	      -e 's/@''GNULIB_MBSCASESTR''@/$(GNULIB_MBSCASESTR)/g' \
	      -e 's/@''GNULIB_MBSCSPN''@/$(GNULIB_MBSCSPN)/g' \
	      -e 's/@''GNULIB_MBSPBRK''@/$(GNULIB_MBSPBRK)/g' \
	      -e 's/@''GNULIB_MBSSPN''@/$(GNULIB_MBSSPN)/g' \
	      -e 's/@''GNULIB_MBSSEP''@/$(GNULIB_MBSSEP)/g' \
	      -e 's/@''GNULIB_MBSTOK_R''@/$(GNULIB_MBSTOK_R)/g' \
	      -e 's/@''GNULIB_MEMCHR''@/$(GNULIB_MEMCHR)/g' \
	      -e 's/@''GNULIB_MEMMEM''@/$(GNULIB_MEMMEM)/g' \
	      -e 's/@''GNULIB_MEMPCPY''@/$(GNULIB_MEMPCPY)/g' \
	      -e 's/@''GNULIB_MEMRCHR''@/$(GNULIB_MEMRCHR)/g' \
	      -e 's/@''GNULIB_RAWMEMCHR''@/$(GNULIB_RAWMEMCHR)/g' \
	      -e 's/@''GNULIB_STPCPY''@/$(GNULIB_STPCPY)/g' \
	      -e 's/@''GNULIB_STPNCPY''@/$(GNULIB_STPNCPY)/g' \
	      -e 's/@''GNULIB_STRCHRNUL''@/$(GNULIB_STRCHRNUL)/g' \
	      -e 's/@''GNULIB_STRDUP''@/$(GNULIB_STRDUP)/g' \
	      -e 's/@''GNULIB_STRNCAT''@/$(GNULIB_STRNCAT)/g' \
	      -e 's/@''GNULIB_STRNDUP''@/$(GNULIB_STRNDUP)/g' \
	      -e 's/@''GNULIB_STRNLEN''@/$(GNULIB_STRNLEN)/g' \
	      -e 's/@''GNULIB_STRPBRK''@/$(GNULIB_STRPBRK)/g' \
	      -e 's/@''GNULIB_STRSEP''@/$(GNULIB_STRSEP)/g' \
	      -e 's/@''GNULIB_STRSTR''@/$(GNULIB_STRSTR)/g' \
	      -e 's/@''GNULIB_STRCASESTR''@/$(GNULIB_STRCASESTR)/g' \
	      -e 's/@''GNULIB_STRTOK_R''@/$(GNULIB_STRTOK_R)/g' \
	      -e 's/@''GNULIB_STRERROR''@/$(GNULIB_STRERROR)/g' \
	      -e 's/@''GNULIB_STRERROR_R''@/$(GNULIB_STRERROR_R)/g' \
	      -e 's/@''GNULIB_STRSIGNAL''@/$(GNULIB_STRSIGNAL)/g' \
	      -e 's/@''GNULIB_STRVERSCMP''@/$(GNULIB_STRVERSCMP)/g' \
	      < $(srcdir)/string.in.h | \
	  sed -e 's|@''HAVE_MBSLEN''@|$(HAVE_MBSLEN)|g' \
	      -e 's|@''HAVE_MEMCHR''@|$(HAVE_MEMCHR)|g' \
	      -e 's|@''HAVE_DECL_MEMMEM''@|$(HAVE_DECL_MEMMEM)|g' \
	      -e 's|@''HAVE_MEMPCPY''@|$(HAVE_MEMPCPY)|g' \
	      -e 's|@''HAVE_DECL_MEMRCHR''@|$(HAVE_DECL_MEMRCHR)|g' \
	      -e 's|@''HAVE_RAWMEMCHR''@|$(HAVE_RAWMEMCHR)|g' \
	      -e 's|@''HAVE_STPCPY''@|$(HAVE_STPCPY)|g' \
	      -e 's|@''HAVE_STPNCPY''@|$(HAVE_STPNCPY)|g' \
	      -e 's|@''HAVE_STRCHRNUL''@|$(HAVE_STRCHRNUL)|g' \
	      -e 's|@''HAVE_DECL_STRDUP''@|$(HAVE_DECL_STRDUP)|g' \
	      -e 's|@''HAVE_DECL_STRNDUP''@|$(HAVE_DECL_STRNDUP)|g' \
	      -e 's|@''HAVE_DECL_STRNLEN''@|$(HAVE_DECL_STRNLEN)|g' \
	      -e 's|@''HAVE_STRPBRK''@|$(HAVE_STRPBRK)|g' \
	      -e 's|@''HAVE_STRSEP''@|$(HAVE_STRSEP)|g' \
	      -e 's|@''HAVE_STRCASESTR''@|$(HAVE_STRCASESTR)|g' \
	      -e 's|@''HAVE_DECL_STRTOK_R''@|$(HAVE_DECL_STRTOK_R)|g' \
	      -e 's|@''HAVE_DECL_STRERROR_R''@|$(HAVE_DECL_STRERROR_R)|g' \
	      -e 's|@''HAVE_DECL_STRSIGNAL''@|$(HAVE_DECL_STRSIGNAL)|g' \
	      -e 's|@''HAVE_STRVERSCMP''@|$(HAVE_STRVERSCMP)|g' \
	      -e 's|@''REPLACE_STPNCPY''@|$(REPLACE_STPNCPY)|g' \
	      -e 's|@''REPLACE_MEMCHR''@|$(REPLACE_MEMCHR)|g' \
	      -e 's|@''REPLACE_MEMMEM''@|$(REPLACE_MEMMEM)|g' \
	      -e 's|@''REPLACE_STRCASESTR''@|$(REPLACE_STRCASESTR)|g' \
	      -e 's|@''REPLACE_STRCHRNUL''@|$(REPLACE_STRCHRNUL)|g' \
	      -e 's|@''REPLACE_STRDUP''@|$(REPLACE_STRDUP)|g' \
	      -e 's|@''REPLACE_STRSTR''@|$(REPLACE_STRSTR)|g' \
	      -e 's|@''REPLACE_STRERROR''@|$(REPLACE_STRERROR)|g' \
	      -e 's|@''REPLACE_STRERROR_R''@|$(REPLACE_STRERROR_R)|g' \
	      -e 's|@''REPLACE_STRNCAT''@|$(REPLACE_STRNCAT)|g' \
	      -e 's|@''REPLACE_STRNDUP''@|$(REPLACE_STRNDUP)|g' \
	      -e 's|@''REPLACE_STRNLEN''@|$(REPLACE_STRNLEN)|g' \
	      -e 's|@''REPLACE_STRSIGNAL''@|$(REPLACE_STRSIGNAL)|g' \
	      -e 's|@''REPLACE_STRTOK_R''@|$(REPLACE_STRTOK_R)|g' \
	      -e 's|@''UNDEFINE_STRTOK_R''@|$(UNDEFINE_STRTOK_R)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)'; \
	      < $(srcdir)/string.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += string.h string.h-t

EXTRA_DIST += string.in.h

## end   gnulib module string

## begin gnulib module strverscmp


EXTRA_DIST += strverscmp.c

EXTRA_libgnu_la_SOURCES += strverscmp.c

## end   gnulib module strverscmp

## begin gnulib module unistd

BUILT_SOURCES += unistd.h

# We need the following in order to create an empty placeholder for
# <unistd.h> when the system doesn't have one.
unistd.h: unistd.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(ARG_NONNULL_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's|@''HAVE_UNISTD_H''@|$(HAVE_UNISTD_H)|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_UNISTD_H''@|$(NEXT_UNISTD_H)|g' \
	      -e 's/@''GNULIB_CHOWN''@/$(GNULIB_CHOWN)/g' \
	      -e 's/@''GNULIB_CLOSE''@/$(GNULIB_CLOSE)/g' \
	      -e 's/@''GNULIB_DUP2''@/$(GNULIB_DUP2)/g' \
	      -e 's/@''GNULIB_DUP3''@/$(GNULIB_DUP3)/g' \
	      -e 's/@''GNULIB_ENVIRON''@/$(GNULIB_ENVIRON)/g' \
	      -e 's/@''GNULIB_EUIDACCESS''@/$(GNULIB_EUIDACCESS)/g' \
	      -e 's/@''GNULIB_FACCESSAT''@/$(GNULIB_FACCESSAT)/g' \
	      -e 's/@''GNULIB_FCHDIR''@/$(GNULIB_FCHDIR)/g' \
	      -e 's/@''GNULIB_FCHOWNAT''@/$(GNULIB_FCHOWNAT)/g' \
	      -e 's/@''GNULIB_FSYNC''@/$(GNULIB_FSYNC)/g' \
	      -e 's/@''GNULIB_FTRUNCATE''@/$(GNULIB_FTRUNCATE)/g' \
	      -e 's/@''GNULIB_GETCWD''@/$(GNULIB_GETCWD)/g' \
	      -e 's/@''GNULIB_GETDOMAINNAME''@/$(GNULIB_GETDOMAINNAME)/g' \
	      -e 's/@''GNULIB_GETDTABLESIZE''@/$(GNULIB_GETDTABLESIZE)/g' \
	      -e 's/@''GNULIB_GETGROUPS''@/$(GNULIB_GETGROUPS)/g' \
	      -e 's/@''GNULIB_GETHOSTNAME''@/$(GNULIB_GETHOSTNAME)/g' \
	      -e 's/@''GNULIB_GETLOGIN''@/$(GNULIB_GETLOGIN)/g' \
	      -e 's/@''GNULIB_GETLOGIN_R''@/$(GNULIB_GETLOGIN_R)/g' \
	      -e 's/@''GNULIB_GETPAGESIZE''@/$(GNULIB_GETPAGESIZE)/g' \
	      -e 's/@''GNULIB_GETUSERSHELL''@/$(GNULIB_GETUSERSHELL)/g' \
	      -e 's/@''GNULIB_GROUP_MEMBER''@/$(GNULIB_GROUP_MEMBER)/g' \
	      -e 's/@''GNULIB_LCHOWN''@/$(GNULIB_LCHOWN)/g' \
	      -e 's/@''GNULIB_LINK''@/$(GNULIB_LINK)/g' \
	      -e 's/@''GNULIB_LINKAT''@/$(GNULIB_LINKAT)/g' \
	      -e 's/@''GNULIB_LSEEK''@/$(GNULIB_LSEEK)/g' \
	      -e 's/@''GNULIB_PIPE''@/$(GNULIB_PIPE)/g' \
	      -e 's/@''GNULIB_PIPE2''@/$(GNULIB_PIPE2)/g' \
	      -e 's/@''GNULIB_PREAD''@/$(GNULIB_PREAD)/g' \
	      -e 's/@''GNULIB_PWRITE''@/$(GNULIB_PWRITE)/g' \
	      -e 's/@''GNULIB_READ''@/$(GNULIB_READ)/g' \
	      -e 's/@''GNULIB_READLINK''@/$(GNULIB_READLINK)/g' \
	      -e 's/@''GNULIB_READLINKAT''@/$(GNULIB_READLINKAT)/g' \
	      -e 's/@''GNULIB_RMDIR''@/$(GNULIB_RMDIR)/g' \
	      -e 's/@''GNULIB_SLEEP''@/$(GNULIB_SLEEP)/g' \
	      -e 's/@''GNULIB_SYMLINK''@/$(GNULIB_SYMLINK)/g' \
	      -e 's/@''GNULIB_SYMLINKAT''@/$(GNULIB_SYMLINKAT)/g' \
	      -e 's/@''GNULIB_TTYNAME_R''@/$(GNULIB_TTYNAME_R)/g' \
	      -e 's/@''GNULIB_UNISTD_H_GETOPT''@/$(GNULIB_UNISTD_H_GETOPT)/g' \
	      -e 's/@''GNULIB_UNISTD_H_NONBLOCKING''@/$(GNULIB_UNISTD_H_NONBLOCKING)/g' \
	      -e 's/@''GNULIB_UNISTD_H_SIGPIPE''@/$(GNULIB_UNISTD_H_SIGPIPE)/g' \
	      -e 's/@''GNULIB_UNLINK''@/$(GNULIB_UNLINK)/g' \
	      -e 's/@''GNULIB_UNLINKAT''@/$(GNULIB_UNLINKAT)/g' \
	      -e 's/@''GNULIB_USLEEP''@/$(GNULIB_USLEEP)/g' \
	      -e 's/@''GNULIB_WRITE''@/$(GNULIB_WRITE)/g' \
	      < $(srcdir)/unistd.in.h | \
	  sed -e 's|@''HAVE_CHOWN''@|$(HAVE_CHOWN)|g' \
	      -e 's|@''HAVE_DUP2''@|$(HAVE_DUP2)|g' \
	      -e 's|@''HAVE_DUP3''@|$(HAVE_DUP3)|g' \
	      -e 's|@''HAVE_EUIDACCESS''@|$(HAVE_EUIDACCESS)|g' \
	      -e 's|@''HAVE_FACCESSAT''@|$(HAVE_FACCESSAT)|g' \
	      -e 's|@''HAVE_FCHDIR''@|$(HAVE_FCHDIR)|g' \
	      -e 's|@''HAVE_FCHOWNAT''@|$(HAVE_FCHOWNAT)|g' \
	      -e 's|@''HAVE_FSYNC''@|$(HAVE_FSYNC)|g' \
	      -e 's|@''HAVE_FTRUNCATE''@|$(HAVE_FTRUNCATE)|g' \
	      -e 's|@''HAVE_GETDTABLESIZE''@|$(HAVE_GETDTABLESIZE)|g' \
	      -e 's|@''HAVE_GETGROUPS''@|$(HAVE_GETGROUPS)|g' \
	      -e 's|@''HAVE_GETHOSTNAME''@|$(HAVE_GETHOSTNAME)|g' \
	      -e 's|@''HAVE_GETLOGIN''@|$(HAVE_GETLOGIN)|g' \
	      -e 's|@''HAVE_GETPAGESIZE''@|$(HAVE_GETPAGESIZE)|g' \
	      -e 's|@''HAVE_GROUP_MEMBER''@|$(HAVE_GROUP_MEMBER)|g' \
	      -e 's|@''HAVE_LCHOWN''@|$(HAVE_LCHOWN)|g' \
	      -e 's|@''HAVE_LINK''@|$(HAVE_LINK)|g' \
	      -e 's|@''HAVE_LINKAT''@|$(HAVE_LINKAT)|g' \
	      -e 's|@''HAVE_PIPE''@|$(HAVE_PIPE)|g' \
	      -e 's|@''HAVE_PIPE2''@|$(HAVE_PIPE2)|g' \
	      -e 's|@''HAVE_PREAD''@|$(HAVE_PREAD)|g' \
	      -e 's|@''HAVE_PWRITE''@|$(HAVE_PWRITE)|g' \
	      -e 's|@''HAVE_READLINK''@|$(HAVE_READLINK)|g' \
	      -e 's|@''HAVE_READLINKAT''@|$(HAVE_READLINKAT)|g' \
	      -e 's|@''HAVE_SLEEP''@|$(HAVE_SLEEP)|g' \
	      -e 's|@''HAVE_SYMLINK''@|$(HAVE_SYMLINK)|g' \
	      -e 's|@''HAVE_SYMLINKAT''@|$(HAVE_SYMLINKAT)|g' \
	      -e 's|@''HAVE_UNLINKAT''@|$(HAVE_UNLINKAT)|g' \
	      -e 's|@''HAVE_USLEEP''@|$(HAVE_USLEEP)|g' \
	      -e 's|@''HAVE_DECL_ENVIRON''@|$(HAVE_DECL_ENVIRON)|g' \
	      -e 's|@''HAVE_DECL_FCHDIR''@|$(HAVE_DECL_FCHDIR)|g' \
	      -e 's|@''HAVE_DECL_GETDOMAINNAME''@|$(HAVE_DECL_GETDOMAINNAME)|g' \
	      -e 's|@''HAVE_DECL_GETLOGIN_R''@|$(HAVE_DECL_GETLOGIN_R)|g' \
	      -e 's|@''HAVE_DECL_GETPAGESIZE''@|$(HAVE_DECL_GETPAGESIZE)|g' \
	      -e 's|@''HAVE_DECL_GETUSERSHELL''@|$(HAVE_DECL_GETUSERSHELL)|g' \
	      -e 's|@''HAVE_DECL_TTYNAME_R''@|$(HAVE_DECL_TTYNAME_R)|g' \
	      -e 's|@''HAVE_OS_H''@|$(HAVE_OS_H)|g' \
	      -e 's|@''HAVE_SYS_PARAM_H''@|$(HAVE_SYS_PARAM_H)|g' \
	  | \
	  sed -e 's|@''REPLACE_CHOWN''@|$(REPLACE_CHOWN)|g' \
	      -e 's|@''REPLACE_CLOSE''@|$(REPLACE_CLOSE)|g' \
	      -e 's|@''REPLACE_DUP''@|$(REPLACE_DUP)|g' \
	      -e 's|@''REPLACE_DUP2''@|$(REPLACE_DUP2)|g' \
	      -e 's|@''REPLACE_FCHOWNAT''@|$(REPLACE_FCHOWNAT)|g' \
	      -e 's|@''REPLACE_GETCWD''@|$(REPLACE_GETCWD)|g' \
	      -e 's|@''REPLACE_GETDOMAINNAME''@|$(REPLACE_GETDOMAINNAME)|g' \
	      -e 's|@''REPLACE_GETLOGIN_R''@|$(REPLACE_GETLOGIN_R)|g' \
	      -e 's|@''REPLACE_GETGROUPS''@|$(REPLACE_GETGROUPS)|g' \
	      -e 's|@''REPLACE_GETPAGESIZE''@|$(REPLACE_GETPAGESIZE)|g' \
	      -e 's|@''REPLACE_LCHOWN''@|$(REPLACE_LCHOWN)|g' \
	      -e 's|@''REPLACE_LINK''@|$(REPLACE_LINK)|g' \
	      -e 's|@''REPLACE_LINKAT''@|$(REPLACE_LINKAT)|g' \
	      -e 's|@''REPLACE_LSEEK''@|$(REPLACE_LSEEK)|g' \
	      -e 's|@''REPLACE_PREAD''@|$(REPLACE_PREAD)|g' \
	      -e 's|@''REPLACE_PWRITE''@|$(REPLACE_PWRITE)|g' \
	      -e 's|@''REPLACE_READ''@|$(REPLACE_READ)|g' \
	      -e 's|@''REPLACE_READLINK''@|$(REPLACE_READLINK)|g' \
	      -e 's|@''REPLACE_RMDIR''@|$(REPLACE_RMDIR)|g' \
	      -e 's|@''REPLACE_SLEEP''@|$(REPLACE_SLEEP)|g' \
	      -e 's|@''REPLACE_SYMLINK''@|$(REPLACE_SYMLINK)|g' \
	      -e 's|@''REPLACE_TTYNAME_R''@|$(REPLACE_TTYNAME_R)|g' \
	      -e 's|@''REPLACE_UNLINK''@|$(REPLACE_UNLINK)|g' \
	      -e 's|@''REPLACE_UNLINKAT''@|$(REPLACE_UNLINKAT)|g' \
	      -e 's|@''REPLACE_USLEEP''@|$(REPLACE_USLEEP)|g' \
	      -e 's|@''REPLACE_WRITE''@|$(REPLACE_WRITE)|g' \
	      -e 's|@''UNISTD_H_HAVE_WINSOCK2_H''@|$(UNISTD_H_HAVE_WINSOCK2_H)|g' \
	      -e 's|@''UNISTD_H_HAVE_WINSOCK2_H_AND_USE_SOCKETS''@|$(UNISTD_H_HAVE_WINSOCK2_H_AND_USE_SOCKETS)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)'; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += unistd.h unistd.h-t

EXTRA_DIST += unistd.in.h

## end   gnulib module unistd

## begin gnulib module useless-if-before-free


EXTRA_DIST += $(top_srcdir)/build-aux/useless-if-before-free

## end   gnulib module useless-if-before-free

## begin gnulib module vc-list-files


EXTRA_DIST += $(top_srcdir)/build-aux/vc-list-files

## end   gnulib module vc-list-files

## begin gnulib module warn-on-use

BUILT_SOURCES += warn-on-use.h
# The warn-on-use.h that gets inserted into generated .h files is the same as
# build-aux/warn-on-use.h, except that it has the copyright header cut off.
warn-on-use.h: $(top_srcdir)/build-aux/warn-on-use.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	sed -n -e '/^.ifndef/,$$p' \
	  < $(top_srcdir)/build-aux/warn-on-use.h \
	  > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += warn-on-use.h warn-on-use.h-t

WARN_ON_USE_H=warn-on-use.h

EXTRA_DIST += $(top_srcdir)/build-aux/warn-on-use.h

## end   gnulib module warn-on-use


mostlyclean-local: mostlyclean-generic
	@for dir in '' $(MOSTLYCLEANDIRS); do \
	  if test -n "$$dir" && test -d $$dir; then \
	    echo "rmdir $$dir"; rmdir $$dir; \
	  fi; \
	done; \
	:
