/*  GWhere.
 *  Copyright (C) 2003 by Sébastien LECACHEUR
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


gchar ** gw_str_split ( gchar *str);


//#define __DEBUG__ 1

char * g_module_check_init ( void)
{
#ifdef __DEBUG__
	printf ( "DESCRIPT.ION module is loading...\n");
#endif

	return NULL;
}


const char * plugin_get_author ( void)
{
	return "Sébastien LECACHEUR";
}


const char * plugin_get_info ( void)
{
	return "This plugin allow to extract current folder's files informations from DESCRIPT.ION file.";
}


const char * plugin_get_version ( void)
{
	return "1.0.0";
}


const char * plugin_get_help ( void)
{
	return NULL;
}


const char * plugin_get_allowed_name ( void)
{
	return "DESCRIPT.ION";
}


char *** plugin_get_files_descr ( const char *filepath, const char *mode)
{
	/* A possible improvment is to use StringBuffer to read the file and generate
	   description without reading the file in one time and without using
	   g_strsplit() function. */
	char ***descr = NULL;
	FILE *file = NULL;
	char buff[512];
	char *file_content = NULL;
	char *file_content_tmp = NULL;
	char **lines;
	int size = 0;
	int nb_lines = 0;
	int i = 0, j = 0;


#ifdef __DEBUG__
	g_print ("current file is %s\n", filepath);
#endif

	if ( filepath != NULL )
	{
		if ( (file = fopen ( filepath, "rb")) != NULL )
		{
			while ( fgets ( buff, 512, file) != NULL)
			{
				gw_str_delete_char ( buff, '\r');
				size += sizeof ( char) * (strlen ( buff)<511?strlen ( buff):511);
				file_content_tmp = realloc ( file_content, size + 1);
				if ( file_content == NULL )
				{
					if ( file_content_tmp != NULL )
					{
						file_content_tmp[0] = '\0';
					}
				}

				if ( file_content_tmp != NULL )
				{
					file_content = file_content_tmp;
				}
				else
				{
					free ( file_content);
					file_content = NULL;
					break;
				}

				memcpy ( &(file_content[strlen(file_content)]), buff, (strlen ( buff)<511?strlen ( buff):511)+1);
			}

			fclose ( file);
		}

		if ( file_content != NULL )
		{
			lines = g_strsplit ( file_content, "\n", -1);

			if ( lines != NULL)
                        {
                                for ( i = 0; lines[i] != NULL; i++)
                                {
#ifdef __DEBUG__
					g_print("current_line[%d]=%s\n",i,lines[i]);
#endif

                                        if ( (strchr ( lines[i], ' ' ) != NULL) || (strchr ( lines[i], '\t' ) != NULL) )
                                        {
                                                nb_lines++;
                                        }
                                }

#ifdef __DEBUG__
				g_print("nb_descr=%d\n",nb_lines);
#endif

                                descr = (gchar***)g_malloc0 ( sizeof ( gchar **) * (nb_lines+1));
                                for ( i = 0; i <= nb_lines; i++) descr[i] = NULL;

                                for ( i = 0; lines[i] != NULL; i++)
                                {
					/* This followinf code is deprecated because g_strsplit() has not the same
					   behavior between GTK+ 1.2 and GTK+ 2.0 or GNU/Linux and Win32.
                                        if ( strchr ( lines[i], ' ' ) != NULL )
                                        {
                                                descr[j] = NULL;
                                                descr[j] = g_strsplit ( lines[i], " " , 2);
                                                gw_str_trim ( descr[j][1]);
                                                j++;
                                        }
                                        else if ( strchr ( lines[i], '\t' ) != NULL )
                                        {
                                                descr[j] = NULL;
                                                descr[j] = g_strsplit ( lines[i], "\t" , 2);
                                                gw_str_trim ( descr[j][1]);
                                                j++;
                                        }
					*/

					descr[j] = gw_str_split ( lines[i]);
					if (descr[j] != NULL) j++;

#ifdef __DEBUG__
					g_print("current descr nb=%d/%d\n",j,i);
					if ( descr[j-1] != NULL ) {
						g_print("file=%s\n",descr[j-1][0]);
						g_print("descr=%s\n",descr[j-1][1]);
					} else {
						g_print("descr[%d] is NULL\n",j-1);
					}
#endif

                                        g_free ( lines[i]);
                                }

                                descr[nb_lines] = NULL;
                                g_free ( lines);
                        }

			free ( file_content);
		}
	}

	return descr;
}


void g_module_unload ( void)
{
#ifdef __DEBUG__
	printf ( "DESCRIPT.ION module is unloading...\n");
#endif
}


gchar ** gw_str_split ( gchar *str) {
	gint start_file = 0;
	gint end_file = 0;
	gint start_descr = 0;
	gint end_descr = 0;
	gint descr_pos = 0;
	gchar *file_name = NULL;
	gchar *file_descr = NULL;
	gchar **descr = NULL;
	
	
	if ( str != NULL ) {
		/* Search the begin of the file name. */
		while ( (isspace(str[start_file])==1) && (str[start_file]!='\0')) {
			start_file++;
		}

#ifdef __DEBUG__
		g_print("File name starts at %d\n",start_file);
#endif

		if ( str[start_file]!='\0') {
			/* The begin of file name was founded. */
			end_file = start_file+1;

			/* Search the end of the file name. */
			while ( (isspace(str[end_file])==0) && (str[end_file]!='\0')) {
				end_file++;
			}

#ifdef __DEBUG__
			g_print("File name ends at %d\n",end_file);
#endif

			if ( str[end_file]!='\0') {
				/* The end of file name was founded. */
				start_descr = end_file+1;

				/* Search the begin of the file description. */
				while ( (isspace(str[start_descr])!=0) && (str[start_descr]!='\0')) {
					start_descr++;
				}
		
#ifdef __DEBUG__
				g_print("File description starts at %d\n",start_descr);
#endif

				if ( str[start_descr]!='\0') {
					/* The begin of file description was founded. */
		
					end_descr = start_descr+1;
					descr_pos = end_descr;

					/* Search the end of the file descrption. */
					while ( str[descr_pos]!='\0') {
						if ( isspace(str[descr_pos])==0 ) {
							/* A new character is founded in the description. */
							end_descr = descr_pos;
						}
						descr_pos++;
					}

#ifdef __DEBUG__
					g_print("File description ends at %d\n",end_descr);
#endif
				} else {
					/* There is only file name. */
				}
			} else {
				/* There is only file name. */
			}
		} else {
			/* There is no file name. */
		}

		if ( end_descr != 0 ) {
			file_name = (gchar*)g_malloc0(sizeof(gchar)*(end_file-start_file+1));
			file_descr = (gchar*)g_malloc0(sizeof(gchar)*(end_descr-start_descr+2));
			memcpy(file_name,&str[start_file],end_file-start_file);
			str[end_file-start_file]='\0';
			memcpy(file_descr,&str[start_descr],end_descr-start_descr+1);
			str[end_descr-start_descr+1]='\0';
			descr = (gchar**)g_malloc0(sizeof(gchar*)*3);
			descr[0] = file_name;
			descr[1] = file_descr;
			descr[2] = NULL; // to use g_strfreev() after

#ifdef __DEBUG__
		g_print("File description is %s for %s\n", descr[1],descr[0]);
#endif
		} else {
			/* Do not generate any file description. */
		}
	}

	return descr;
}
