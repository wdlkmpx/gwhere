/*  GWhere.
 *  Copyright (C) 2000  1999 by Balázs Terényi
 *  Modified Sébastien LECACHEUR
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


#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tools/gwtools.h"


//#define __DEBUG__ 1


char * g_module_check_init ( void)
{
#ifdef __DEBUG__
	printf ( "HTML module is loading...\n");
#endif

	return NULL;
}


const char * plugin_get_author ( void)
{
	return "Sébastien LECACHEUR";
}


const char * plugin_get_info ( void)
{
	return "This plugin allow to extract title from HTML file.";
}


const char * plugin_get_version ( void)
{
	return "1.0.0";
}


const char * plugin_get_help ( void)
{
	return NULL;
}


const char * plugin_get_allowed_ext ( void)
{
	return "html|htm";
}


char * plugin_get_file_descr ( const char *filepath, const char *mode)
{
	char *descr = NULL, *tmp_descr = NULL;
	FILE *file = NULL;
	int len;
//	char *title_start = NULL;
//	char *title_end = NULL;
	char buff_original[512]; // The original readed strings
	char buff[512]; // The readed strings to lower
	char databuff[2048]; // The original readed strings after the <title> tag
//	char databuff_lower[2048];
	gboolean found = FALSE;
	gboolean finished = FALSE;
int start = 0, end = 0;
char *current = NULL, *bad = NULL;


#ifdef __DEBUG__
	g_print("File is %s\n",filepath);
#endif

//free(descr);
//free(descr);
//g_print("test\n");
//g_print("segfault%s\n",NULL);

	if ( filepath != NULL )	{
		if ( (file = fopen ( filepath, "rb")) != NULL ) {
			memset ( buff_original, '\0', 512);
			memset ( buff, '\0', 512);
			memset ( databuff, '\0', 2048);

			/* Reads the line or a maximum of 512 characters */
			while ( (!finished) && (fgets ( buff_original, 512, file) != NULL) ) {
#ifdef __DEBUG__
				g_print("line=%s\n", buff_original);
#endif

				strcpy ( buff, buff_original);
				g_strdown ( buff);

				start = 0;
				end = strlen ( buff);
				if (!found) {
					if ( (current = strstr ( buff, "<title>")) != NULL ) {
						start = current - buff + 7;
						found = TRUE;
					} else {
					}
				} else {
				}

				if ( found) {
					if ( (current = strstr ( &buff[start], "</title>")) != NULL ) {
						end = current - buff;
						finished = TRUE;
					} else {
					}
				} else {
				}

				if ( found) {
					strncat ( databuff, &buff_original[start], end - start);
				} else {
				}

				if (!finished) {
				} else {
					if ( (len = strlen ( databuff)) > 0 ) {
						descr = (char*)g_malloc ( len + 1);
						memset ( descr, '\0', len + 1);
						strcpy ( descr, databuff);
						if ( (tmp_descr = gw_str_replace_str ( descr, "\r\n", " ")) != NULL ) {
							g_free ( descr);
							descr = tmp_descr;
							tmp_descr = NULL;
						}
						gw_str_replace_char ( descr, '\n', ' ');
						gw_str_delete_char ( descr, '\t');
						g_strstrip ( descr);
					} else {
					}
				}

				if ( !finished ) {
					/* Cannot find a </title> tag after a </head> or a <body> tag. */
					if ( strstr ( &buff[start], "</head>") != NULL ) {
						finished = TRUE;
					} else if ( strstr ( &buff[start], "<body>") != NULL ) {
						finished = TRUE;
					}
				} else {
					bad = NULL;
					if ( (bad = strstr ( &buff[start], "</head>")) != NULL ) {
					} else if ( (bad = strstr ( &buff[start], "<body>")) != NULL ) {
					}

					if ( (bad != NULL) && (bad < current) ) {
						if ( descr != NULL) {
							g_free ( descr);
							descr = NULL;
						}
					}
				}
			}

			fclose ( file);
		}
	}

#ifdef __DEBUG__
	g_print("descr=%s\n",descr!=NULL?descr:"(null)");
#endif

	return descr;
}


void g_module_unload ( void)
{
#ifdef __DEBUG__
	printf ( "HTML module is unloading...\n");
#endif
}
