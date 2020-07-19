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


char * g_module_check_init ( void)
{
#ifdef __DEBUG__
	printf ( "FILE_ID.DIZ module is loading...\n");
#endif

	return NULL;
}


const char * plugin_get_author ( void)
{
	return "Sébastien LECACHEUR";
}


const char * plugin_get_info ( void)
{
	return "This plugin allow to extract parent folder informations from FILE_ID.DIZ file.";
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
	return "FILE_ID.DIZ";
}


char * plugin_get_parent_descr ( const char *filepath, const char *mode)
{
	char *descr = NULL;
	FILE *file = NULL;
	char buff[512];
	char *file_content = NULL;
	char *file_content_tmp = NULL;
	int size = 0;


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
			descr = file_content;
		}
	}

	return descr;
}


void g_module_unload ( void)
{
#ifdef __DEBUG__
	printf ( "FILE_ID.DIZ module is unloading...\n");
#endif
}
