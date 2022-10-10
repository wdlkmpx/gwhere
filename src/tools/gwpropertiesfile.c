/*  GWhere.
 *  Copyright (C) 2000  Sébastien LECACHEUR
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include "../gwsupport.h"
#include "gwpropertiesfile.h"

#include <sys/types.h> /* open */
#include <sys/stat.h> /* open */
#include <fcntl.h> /* open */
#include <string.h> /* strncmp strlen */

#include "gwstring.h" /* gw_str_delete_char */
#include "gwfile.h" /* gw_file_read_line */


gint gw_properties_file_read_variable_value ( const gchar *name, const gchar *var, gchar **value)
{
	gint pf;
	gint result = -1;
	gchar *line = NULL;
	gchar **parsed_line = NULL;
#ifdef GW_DEBUG_TOOLS_COMPONENT
	gint i;
#endif


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ( pf = open ( name, O_RDONLY) ) != -1 )
	{
		while ( ((line = gw_file_readline ( pf, line, -1)) != NULL) && (result != 0))
		{
#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : read line=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, line);
#endif

			parsed_line = g_strsplit ( line, "=", 1);

#ifdef GW_DEBUG_TOOLS_COMPONENT
			i = 0;

			while ( parsed_line[i] != NULL )
			{
				g_print ( "*** GW - %s (%d) :: %s() : splitted line[%d]=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i, parsed_line[i]);
				i++;
			}
#endif

			/* Removes all beginning and ending white spaces. */
			g_strstrip ( parsed_line[0]);

			/* Checks if it's the exact variable name (with size and characters. */
			if ( (strlen ( parsed_line[0]) == strlen ( var)) && strncmp ( var, parsed_line[0], strlen ( var)) == 0 )
			{
				if ( parsed_line[1] != NULL )
				{
					/* Removes all beginning and ending white spaces. */
					g_strstrip ( parsed_line[1]);
					*value = g_strdup ( parsed_line[1]);

					/* Frees the value if contains no characters and values to NULL. */
					if ( strlen ( *value) == 0 )
					{
						g_free ( *value);
						*value = NULL;
					}
				}
				else
				{
					*value = NULL;
				}

				result = 0;
			}


			if ( parsed_line != NULL )
			{
				g_strfreev ( parsed_line);
				parsed_line = NULL;
			}

			if ( line != NULL )
			{
				g_free ( line);
				line = NULL;
			}
		}

		if ( line != NULL )
		{
			g_free ( line);
			line = NULL;
		}

		close ( pf);
	}

	return result;
}


gint gw_properties_file_load_all_settings ( const gchar *name, GWSettings **settings)
{
	gint pf;
	gint result = -1;
	gchar *line = NULL;
	gchar **parsed_line = NULL;
#ifdef GW_DEBUG_TOOLS_COMPONENT
	gint i;
#endif


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ( pf = open ( name, O_RDONLY) ) != -1 )
	{
		while ( ((line = gw_file_readline ( pf, line, -1)) != NULL))
		{
			if ( *settings == NULL )
			{
				/* Allocates a new GWSettings. */
				*settings = gw_settings_new ( );
			}

#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : read line=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, line);
#endif

			parsed_line = g_strsplit ( line, "=", 2);

#ifdef GW_DEBUG_TOOLS_COMPONENT
			i = 0;

			while ( parsed_line[i] != NULL )
			{
				g_print ( "*** GW - %s (%d) :: %s() : splitted line[%d]=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i, parsed_line[i]);
				i++;
			}
#endif

			if ( parsed_line[0] != NULL )
			{
				/* Removes all beginning and ending white spaces. */
				g_strstrip ( parsed_line[0]);

				/* Removes all '\r' in the string, due to a bug with empty line on Cygwin OS. */
				gw_str_delete_char ( parsed_line[0], '\r');

				if ( strlen ( parsed_line[0]) != 0 )
				{
					if ( parsed_line[1] != NULL )
					{
						g_strstrip ( parsed_line[1]);

						if ( strlen ( parsed_line[1]) == 0 )
						{
							g_free ( parsed_line[1]);

							parsed_line[1] = NULL;
						}
					}

					gw_settings_add_pair ( *settings, g_strdup ( parsed_line[0]), g_strdup ( parsed_line[1]));

					result = 0;
				}
			}


			if ( parsed_line != NULL )
			{
				g_strfreev ( parsed_line);
				parsed_line = NULL;
			}

			if ( line != NULL )
			{
				g_free ( line);
				line = NULL;
			}
		}

		if ( line != NULL )
		{
			g_free ( line);
			line = NULL;
		}

		close ( pf);
	}

	return result;
}



gint gw_properties_file_save_all_settings ( const gchar *name, GWSettings **settings, const gchar *mode)
{
	gint pf;
	gint result = -1;
	gchar *file = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( *settings != NULL )
	{
#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : openning file... (%s)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, name);
#endif

		if ( ( pf = open ( name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR) ) != -1 )
		{
#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : file opened (%s)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, name);
#endif

			file = g_strdup ( "");
			gw_settings_to_file ( *settings, &file);

#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : writing file...\n%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, file);
#endif

			if ( strlen ( file) == write ( pf, file, strlen ( file)))
			{
				/* Not frees GWSettings at time : may be with mode parameter. */
				/* gw_settings_free ( *settings);
				*/
#ifdef GW_DEBUG_TOOLS_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : file written (%s)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, name);
#endif

				result = 0;
			}

			if ( file != NULL )
			{
				g_free ( file);
				file = NULL;
			}

			close ( pf);
		}
	}

	return result;
}
