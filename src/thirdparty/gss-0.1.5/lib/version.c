/* version.c --- Version handling.
 * Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2010  Simon Josefsson
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

#include "internal.h"

#include <string.h> /* for strverscmp */

/**
 * gss_check_version:
 * @req_version: version string to compare with, or NULL
 *
 * Check that the version of the library is at minimum the one
 * given as a string in @req_version.
 *
 * WARNING: This function is a GNU GSS specific extension, and is not
 * part of the official GSS API.
 *
 * Return value: The actual version string of the library; NULL if the
 *   condition is not met.  If %NULL is passed to this function no
 *   check is done and only the version string is returned.
 **/
const char *
gss_check_version (const char *req_version)
{
  if (!req_version || strverscmp (req_version, PACKAGE_VERSION) <= 0)
    return PACKAGE_VERSION;

  return NULL;
}
