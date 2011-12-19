/* ext.c --- Implementation of GSS specific extensions.
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2009, 2010  Simon Josefsson
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

/**
 * gss_oid_equal:
 * @first_oid: (Object ID, read) First Object identifier.
 * @second_oid: (Object ID, read) First Object identifier.
 *
 * Compare two OIDs for equality.  The comparison is "deep", i.e., the
 * actual byte sequences of the OIDs are compared instead of just the
 * pointer equality.
 *
 * WARNING: This function is a GNU GSS specific extension, and is not
 * part of the official GSS API.
 *
 * Return value: Returns boolean value true when the two OIDs are
 *   equal, otherwise false.
 **/
int
gss_oid_equal (gss_OID first_oid, gss_OID second_oid)
{

  return first_oid && second_oid &&
    first_oid->length == second_oid->length &&
    memcmp (first_oid->elements, second_oid->elements,
	    second_oid->length) == 0;
}

/**
 * gss_copy_oid:
 * @minor_status: (integer, modify) Mechanism specific status code.
 * @src_oid: (Object ID, read) The object identifier to copy.
 * @dest_oid: (Object ID, modify) The resultant copy of @src_oid.
 *   Storage associated with this name must be freed by the
 *   application, but gss_release_oid() cannot be used generally as it
 *   deallocate the oid structure itself too (use
 *   gss_duplicate_oid() if you don't want this problem.)
 *
 * Make an exact copy of the given OID, that shares no memory areas
 * with the original.
 *
 * WARNING: This function is a GNU GSS specific extension, and is not
 * part of the official GSS API.
 *
 * Return value:
 *
 * `GSS_S_COMPLETE`: Successful completion.
 **/
OM_uint32
gss_copy_oid (OM_uint32 * minor_status,
	      const gss_OID src_oid, gss_OID dest_oid)
{
  if (minor_status)
    *minor_status = 0;

  if (!src_oid)
    return GSS_S_FAILURE | GSS_S_CALL_INACCESSIBLE_READ;

  if (src_oid->length == 0 || src_oid->elements == NULL)
    return GSS_S_FAILURE | GSS_S_CALL_BAD_STRUCTURE;

  dest_oid->length = src_oid->length;
  dest_oid->elements = malloc (src_oid->length);
  if (!dest_oid->elements)
    {
      if (minor_status)
	*minor_status = ENOMEM;
      return GSS_S_FAILURE;
    }
  memcpy (dest_oid->elements, src_oid->elements, src_oid->length);

  return GSS_S_COMPLETE;
}

/**
 * gss_duplicate_oid:
 * @minor_status: (integer, modify) Mechanism specific status code.
 * @src_oid: (Object ID, read) The object identifier to duplicate.
 * @dest_oid: (Object ID, modify) The resultant copy of @src_oid.
 *   Storage associated with this name must be freed by the
 *   application, by calling gss_release_oid().
 *
 * Allocate a new OID and make it an exact copy of the given OID, that
 * shares no memory areas with the original.
 *
 * WARNING: This function is a GNU GSS specific extension, and is not
 * part of the official GSS API.
 *
 * Return value:
 *
 * `GSS_S_COMPLETE`: Successful completion.
 **/
OM_uint32
gss_duplicate_oid (OM_uint32 * minor_status,
		   const gss_OID src_oid, gss_OID * dest_oid)
{
  /* This function is not part of the official GSS API */

  OM_uint32 maj_stat;

  if (minor_status)
    *minor_status = 0;

  if (!src_oid)
    return GSS_S_FAILURE | GSS_S_CALL_INACCESSIBLE_READ;

  if (src_oid->length == 0 || src_oid->elements == NULL)
    return GSS_S_FAILURE | GSS_S_CALL_BAD_STRUCTURE;

  *dest_oid = malloc (sizeof (**dest_oid));
  if (!*dest_oid)
    {
      if (minor_status)
	*minor_status = ENOMEM;
      return GSS_S_FAILURE;
    }

  maj_stat = gss_copy_oid (minor_status, src_oid, *dest_oid);
  if (GSS_ERROR (maj_stat))
    {
      free (*dest_oid);
      return maj_stat;
    }

  return GSS_S_COMPLETE;
}

/**
 * gss_userok:
 * @name: (gss_name_t, read) Name to be compared.
 * @username: Zero terminated string with username.
 *
 * Compare the username against the output from gss_export_name()
 * invoked on @name, after removing the leading OID.  This answers the
 * question whether the particular mechanism would authenticate them
 * as the same principal
 *
 * WARNING: This function is a GNU GSS specific extension, and is not
 * part of the official GSS API.
 *
 * Return value: Returns 0 if the names match, non-0 otherwise.
 **/
int
gss_userok (const gss_name_t name, const char *username)
{
  /* FIXME: Call gss_export_name, then remove OID. */
  return name->length == strlen (username) &&
    memcmp (name->value, username, name->length) == 0;
}
