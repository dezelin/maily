// file      : odb/qt/details/config.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_QT_DETAILS_CONFIG_HXX
#define ODB_QT_DETAILS_CONFIG_HXX

// no pre

#ifdef _MSC_VER
#elif defined(ODB_COMPILER)
#  define LIBODB_QT_STATIC_LIB
#else
#  include <odb/qt/details/config.h>
#endif

// no post

#endif // ODB_QT_DETAILS_CONFIG_HXX
