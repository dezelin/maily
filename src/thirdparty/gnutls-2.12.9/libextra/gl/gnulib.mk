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
# Reproduce by: gnulib-tool --import --dir=. --local-dir=gl/override --lib=libxgnu --source-base=gl --m4-base=gl/m4 --doc-base=doc --tests-base=gl/tests --aux-dir=build-aux --avoid=dummy --avoid=stdint --makefile-name=gnulib.mk --libtool --macro-prefix=xgl --no-vc-files crypto/hmac-md5 crypto/md5 extensions havelib lib-msvc-compat lib-symbol-versions


MOSTLYCLEANFILES += core *.stackdump

noinst_LTLIBRARIES += libxgnu.la

libxgnu_la_SOURCES =
libxgnu_la_LIBADD = $(xgl_LTLIBOBJS)
libxgnu_la_DEPENDENCIES = $(xgl_LTLIBOBJS)
EXTRA_libxgnu_la_SOURCES =
libxgnu_la_LDFLAGS = $(AM_LDFLAGS)
libxgnu_la_LDFLAGS += -no-undefined

## begin gnulib module crypto/hmac-md5


EXTRA_DIST += hmac-md5.c hmac.h

EXTRA_libxgnu_la_SOURCES += hmac-md5.c

## end   gnulib module crypto/hmac-md5

## begin gnulib module crypto/md5


EXTRA_DIST += md5.c md5.h

EXTRA_libxgnu_la_SOURCES += md5.c

## end   gnulib module crypto/md5

## begin gnulib module havelib


EXTRA_DIST += $(top_srcdir)/build-aux/config.rpath

## end   gnulib module havelib

## begin gnulib module memxor


EXTRA_DIST += memxor.c memxor.h

EXTRA_libxgnu_la_SOURCES += memxor.c

## end   gnulib module memxor


mostlyclean-local: mostlyclean-generic
	@for dir in '' $(MOSTLYCLEANDIRS); do \
	  if test -n "$$dir" && test -d $$dir; then \
	    echo "rmdir $$dir"; rmdir $$dir; \
	  fi; \
	done; \
	: