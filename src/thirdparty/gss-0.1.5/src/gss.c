/* gss.c --- Command line tool for GSS.
 * Copyright (C) 2004, 2005, 2006, 2007, 2008, 2009, 2010  Simon Josefsson
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

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* For gettext. */
#include <locale.h>
#include <gettext.h>
#define _(String) gettext (String)

/* Get GSS header. */
#include <gss.h>

/* Command line parameter parser via gengetopt. */
#include "gss_cmd.h"

/* Gnulib utils. */
#include "progname.h"
#include "version-etc.h"

const char version_etc_copyright[] =
  /* Do *not* mark this string for translation.  %s is a copyright
     symbol suitable for this locale, and %d is the copyright
     year.  */
  "Copyright %s %d Simon Josefsson.";

/* This feature is available in gcc versions 2.5 and later.  */
#if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 5)
# define GSS_ATTR_NO_RETRUN
#else
# define GSS_ATTR_NO_RETRUN __attribute__ ((__noreturn__))
#endif

static void
usage (int status) GSS_ATTR_NO_RETRUN;

static void
usage (int status)
{
  if (status != EXIT_SUCCESS)
    fprintf (stderr, _("Try `%s --help' for more information.\n"),
	     program_name);
  else
    {
      printf (_("\
Usage: %s OPTIONS...\n\
"), program_name);
      fputs (_("\
Command line interface to GSS, used to explain error codes.\n\
\n\
"), stdout);
      fputs (_("\
Mandatory arguments to long options are mandatory for short options too.\n\
"), stdout);
      fputs (_("\
  -h, --help        Print help and exit\n\
  -V, --version     Print version and exit\n\
  -m, --major=LONG  Describe a `major status' error code vaue in plain text.\n\
  -q, --quiet       Silent operation  (default=off)\n\
"), stdout);
      emit_bug_reporting_address ();
    }
  exit (status);
}

int
main (int argc, char *argv[])
{
  struct gengetopt_args_info args;
  gss_buffer_desc status_string;
  OM_uint32 message_context = 0;
  OM_uint32 maj = 0, min;
  int rc = 0;
  size_t i;

  setlocale (LC_ALL, "");
  set_program_name (argv[0]);
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  if (cmdline_parser (argc, argv, &args) != 0)
    return 1;

  if (args.version_given)
    {
      version_etc (stdout, "gss", PACKAGE_NAME, VERSION,
		   "Simon Josefsson", (char *) NULL);
      return EXIT_SUCCESS;
    }

  if (args.help_given || !args.major_given)
    usage (EXIT_SUCCESS);

  if (!args.quiet_given)
    {
      printf (_("GSS-API major status code %ld (0x%lx).\n\n"),
	      args.major_arg, args.major_arg);

      printf (_("   MSB                               "
		"                                  LSB\n"
		"   +-----------------+---------------"
		"--+---------------------------------+\n"
		"   |  Calling Error  |  Routine Error"
		"  |       Supplementary Info        |\n   | "));
      for (i = 0; i < 8; i++)
	printf ("%ld ", (args.major_arg >> (31 - i)) & 1);
      printf ("| ");
      for (i = 0; i < 8; i++)
	printf ("%ld ", (args.major_arg >> (23 - i)) & 1);
      printf ("| ");
      for (i = 0; i < 16; i++)
	printf ("%ld ", (args.major_arg >> (15 - i)) & 1);
      printf (_("|\n"
		"   +-----------------+---------------"
		"--+---------------------------------+\n"
		"Bit 31            24  23            1"
		"6  15                             0\n\n"));
    }

  if (GSS_ROUTINE_ERROR (args.major_arg))
    {
      if (!args.quiet_given)
	printf (_("Masked routine error %ld (0x%lx) shifted "
		  "into %ld (0x%lx):\n"),
		GSS_ROUTINE_ERROR (args.major_arg),
		GSS_ROUTINE_ERROR (args.major_arg),
		GSS_ROUTINE_ERROR (args.
				   major_arg) >> GSS_C_ROUTINE_ERROR_OFFSET,
		GSS_ROUTINE_ERROR (args.
				   major_arg) >> GSS_C_ROUTINE_ERROR_OFFSET);

      message_context = 0;
      do
	{
	  maj = gss_display_status (&min, GSS_ROUTINE_ERROR (args.major_arg),
				    GSS_C_GSS_CODE, GSS_C_NO_OID,
				    &message_context, &status_string);
	  if (GSS_ERROR (maj))
	    {
	      fprintf (stderr, _("%s: displaying status code failed\n"),
		       argv[0]);
	      rc = 1;
	      break;
	    }

	  printf ("%.*s\n", (int) status_string.length,
		  (char *) status_string.value);

	  gss_release_buffer (&min, &status_string);
	}
      while (message_context);

      if (!args.quiet_given)
	printf ("\n");
    }

  if (GSS_CALLING_ERROR (args.major_arg))
    {
      if (!args.quiet_given)
	printf
	  (_("Masked calling error %ld (0x%lx) shifted into %ld (0x%lx):\n"),
	   GSS_CALLING_ERROR (args.major_arg),
	   GSS_CALLING_ERROR (args.major_arg),
	   GSS_CALLING_ERROR (args.major_arg) >> GSS_C_CALLING_ERROR_OFFSET,
	   GSS_CALLING_ERROR (args.major_arg) >> GSS_C_CALLING_ERROR_OFFSET);

      message_context = 0;
      do
	{
	  maj = gss_display_status (&min, GSS_CALLING_ERROR (args.major_arg),
				    GSS_C_GSS_CODE, GSS_C_NO_OID,
				    &message_context, &status_string);
	  if (GSS_ERROR (maj))
	    {
	      fprintf (stderr, _("%s: displaying status code failed\n"),
		       argv[0]);
	      rc = 1;
	      break;
	    }

	  printf ("%.*s\n", (int) status_string.length,
		  (char *) status_string.value);

	  gss_release_buffer (&min, &status_string);
	}
      while (message_context);

      if (!args.quiet_given)
	printf ("\n");
    }

  if (GSS_SUPPLEMENTARY_INFO (args.major_arg))
    {
      if (!args.quiet_given)
	printf (_("Masked supplementary info %ld (0x%lx) shifted "
		  "into %ld (0x%lx):\n"),
		GSS_SUPPLEMENTARY_INFO (args.major_arg),
		GSS_SUPPLEMENTARY_INFO (args.major_arg),
		GSS_SUPPLEMENTARY_INFO (args.major_arg) >>
		GSS_C_SUPPLEMENTARY_OFFSET,
		GSS_SUPPLEMENTARY_INFO (args.major_arg) >>
		GSS_C_SUPPLEMENTARY_OFFSET);

      message_context = 0;
      do
	{
	  maj = gss_display_status (&min,
				    GSS_SUPPLEMENTARY_INFO (args.major_arg),
				    GSS_C_GSS_CODE, GSS_C_NO_OID,
				    &message_context, &status_string);
	  if (GSS_ERROR (maj))
	    {
	      fprintf (stderr, _("%s: displaying status code failed\n"),
		       argv[0]);
	      rc = 1;
	      break;
	    }

	  printf ("%.*s\n", (int) status_string.length,
		  (char *) status_string.value);

	  gss_release_buffer (&min, &status_string);
	}
      while (message_context);

      if (!args.quiet_given)
	printf ("\n");
    }

  if (args.major_arg == GSS_S_COMPLETE)
    printf (_("No error\n"));

  return rc;
}
