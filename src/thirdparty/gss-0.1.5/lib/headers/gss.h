/* gss.h --- Header file for GSSLib.                                  -*- c -*-
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009  Simon Josefsson
 *
 * This file is part of the Generic Security Service (GSS).
 *
 * GSS is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * GSS is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GSS; if not, see http://www.gnu.org/licenses or write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef _GSS_H
#define _GSS_H

# ifdef __cplusplus
extern "C" {
# endif

  /**
   * GSS_VERSION
   *
   * Pre-processor symbol with a string that describe the header file
   * version number.  Used together with gss_check_version() to verify
   * header file and run-time library consistency.
   */
# define GSS_VERSION "0.1.5"

  /**
   * GSS_VERSION_MAJOR
   *
   * Pre-processor symbol with a decimal value that describe the major
   * level of the header file version number.  For example, when the
   * header version is 1.2.3 this symbol will be 1.
   *
   * Since: 0.1.0
   */
# define GSS_VERSION_MAJOR 0

  /**
   * GSS_VERSION_MINOR
   *
   * Pre-processor symbol with a decimal value that describe the minor
   * level of the header file version number.  For example, when the
   * header version is 1.2.3 this symbol will be 2.
   *
   * Since: 0.1.0
   */
# define GSS_VERSION_MINOR 1

  /**
   * GSS_VERSION_PATCH
   *
   * Pre-processor symbol with a decimal value that describe the patch
   * level of the header file version number.  For example, when the
   * header version is 1.2.3 this symbol will be 3.
   *
   * Since: 0.1.0
   */
# define GSS_VERSION_PATCH 5

  /**
   * GSS_VERSION_NUMBER
   *
   * Pre-processor symbol with a hexadecimal value describing the
   * header file version number.  For example, when the header version
   * is 1.2.3 this symbol will have the value 0x010203.
   *
   * Since: 0.1.0
   */
# define GSS_VERSION_NUMBER 0x000105

# include <gss/api.h>
# include <gss/ext.h>
# include <gss/krb5.h>
# include <gss/krb5-ext.h>

# ifdef __cplusplus
}
# endif

#endif /* _GSS_H */
