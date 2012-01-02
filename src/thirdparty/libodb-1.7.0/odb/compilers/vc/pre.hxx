// file      : odb/compilers/vc/pre.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

// These warnings had to be disabled "for good".
//
//#pragma warning (disable:4250) // inherits via dominance
//#pragma warning (disable:4661) // no definition for explicit instantiation


// Push warning state.
//
#pragma warning (push, 3)


// Disabled warnings.
//
#pragma warning (disable:4068) // unknown pragma
#pragma warning (disable:4251) // needs to have DLL-interface
#pragma warning (disable:4290) // exception specification ignored
#pragma warning (disable:4355) // passing 'this' to a member
#pragma warning (disable:4800) // forcing value to bool

//#pragma warning (disable:4275) // non dll-interface base
//#pragma warning (disable:4224) // nonstandard extension  (/Za option)

// Elevated warnings.
//
#pragma warning (2:4239) // standard doesn't allow this conversion
