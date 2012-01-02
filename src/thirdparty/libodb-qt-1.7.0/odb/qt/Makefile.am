# file      : odb/qt/Makefile.am
# author    : Constantin Michael <constantin@codesynthesis.com>
# copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
# license   : GNU GPL v2; see accompanying LICENSE file

lib_LTLIBRARIES = libodb-qt.la
libodb_qt_la_SOURCES = date-time/exceptions.cxx

odbqtincludedir = $(includedir)/odb/qt/
nobase_odbqtinclude_HEADERS = smart-ptr/lazy-ptr.txx smart-ptr/lazy-ptr.hxx smart-ptr/pointer-traits.hxx smart-ptr/lazy-ptr.ixx smart-ptr/wrapper-traits.hxx smart-ptr/lazy-pointer-traits.hxx lazy-ptr.hxx exception.hxx date-time/mysql/default-mapping.hxx date-time/mysql/qtime-traits.hxx date-time/mysql/qdate-traits.hxx date-time/mysql/qdate-time-traits.hxx date-time/sqlite/default-mapping.hxx date-time/sqlite/qtime-traits.hxx date-time/sqlite/qdate-traits.hxx date-time/sqlite/qdate-time-traits.hxx date-time/oracle/default-mapping.hxx date-time/oracle/qtime-traits.hxx date-time/oracle/qdate-traits.hxx date-time/oracle/qdate-time-traits.hxx date-time/pgsql/default-mapping.hxx date-time/pgsql/qtime-traits.hxx date-time/pgsql/qdate-traits.hxx date-time/pgsql/qdate-time-traits.hxx date-time/exceptions.hxx basic/mysql/default-mapping.hxx basic/mysql/qstring-traits.hxx basic/mysql/qbyte-array-traits.hxx basic/sqlite/default-mapping.hxx basic/sqlite/qstring-traits.hxx basic/sqlite/qbyte-array-traits.hxx basic/oracle/default-mapping.hxx basic/oracle/qstring-traits.hxx basic/oracle/qbyte-array-traits.hxx basic/pgsql/default-mapping.hxx basic/pgsql/qstring-traits.hxx basic/pgsql/qbyte-array-traits.hxx containers/qvector-traits.hxx containers/qlist-traits.hxx containers/qhash-traits.hxx containers/qmap-traits.hxx containers/qset-traits.hxx containers/qlinked-list-traits.hxx details/export.hxx details/config.hxx version.hxx date-time-oracle.options basic-sqlite.options containers.options basic-mysql.options basic-pgsql.options date-time-pgsql.options version.options smart-ptr.options date-time-mysql.options basic-oracle.options date-time-sqlite.options
nobase_nodist_odbqtinclude_HEADERS = details/config.h

EXTRA_DIST = libodb-qt-vc9.vcproj libodb-qt-vc10.vcxproj libodb-qt-vc10.vcxproj.filters

AM_CPPFLAGS= -I'$(top_builddir)' -I'$(top_srcdir)' -DLIBODB_QT_DYNAMIC_LIB
AM_LDFLAGS = -release 1.7 -no-undefined
