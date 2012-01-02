# file      : odb/sqlite/Makefile.am
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
# license   : GNU GPL v2; see accompanying LICENSE file

lib_LTLIBRARIES = libodb-sqlite.la
libodb_sqlite_la_SOURCES = connection.cxx connection-factory.cxx database.cxx error.cxx exceptions.cxx object-statements.cxx query.cxx query-const-expr.cxx result.cxx statement-cache.cxx statement.cxx statements-base.cxx tracer.cxx traits.cxx transaction.cxx transaction-impl.cxx details/options.cxx

odbsqliteincludedir = $(includedir)/odb/sqlite/
nobase_odbsqliteinclude_HEADERS = auto-handle.hxx binding.hxx connection-factory.hxx connection.hxx container-statements.hxx container-statements.txx database.hxx database.ixx details/config.hxx details/export.hxx details/options.hxx details/options.ixx error.hxx exceptions.hxx forward.hxx object-result.hxx object-result.txx object-statements.hxx object-statements.ixx object-statements.txx query.hxx query.ixx query.txx result.hxx sqlite-types.hxx statement-cache.hxx statement.hxx statements-base.hxx tracer.hxx traits.hxx transaction-impl.hxx transaction-impl.ixx transaction.hxx transaction.ixx version.hxx view-result.hxx view-result.txx view-statements.hxx view-statements.txx
nobase_nodist_odbsqliteinclude_HEADERS = details/config.h

EXTRA_DIST = details/options.cli details/config.h.in libodb-sqlite-vc9.vcproj libodb-sqlite-vc10.vcxproj libodb-sqlite-vc10.vcxproj.filters

AM_CPPFLAGS= -I'$(top_builddir)' -I'$(top_srcdir)' -DLIBODB_SQLITE_DYNAMIC_LIB
AM_LDFLAGS = -release 1.7 -no-undefined
