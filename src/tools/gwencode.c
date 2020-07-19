/*  GWhere
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
#include "gwencode.h"

#include <stdio.h> /* fopen fread fprintf fclose */


#define ENCODE_BASE_64(a) (((a)>=0 && (a)<=25)?((a)+'A'):(((a)>=26 && (a)<=51)?((a)-26+'a'):(((a)>=52 && (a)<=61)?((a)-52+'0'):(((a)==62)?('+'):(((a)==63)?('/'):('='))))))


#define DECODE_BASE_64(a) ((a>='A'&& a<='Z')?(a-65):((a>='a' && a<='z')?(a-71):((a>='0' && a<='9')?(a+4):((a=='+')?(62):((a=='/')?(63):(0))))))


#define DECODE_BASE_64_ISEND(a) if ( a == '=' ) break;


gint gw_encode_file_base64 ( gchar *src, gchar *dst)
{
	FILE *f, *g;
	unsigned char buff[3];
	int i = 0;
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( src != NULL && dst != NULL )
	{
		if ( !(f = fopen ( src, "r")))
		{
			// May be used for default source
			//f = stdin ;

			if ( !(g = fopen ( dst, "w")))
			{
				// May be used for default destination
				//g = stdout;

				buff[0] = buff[1] = buff[2] = 0;

				while ( (i = fread ( buff, 1, 3, f)) > 0 )
				{
					fprintf ( g, "%c", ENCODE_BASE_64 ( buff[0] >> 2));
					fprintf ( g, "%c", ENCODE_BASE_64 ( ((buff[0] & 0x3) << 4) | buff[1] >> 4 ) );

					if ( i > 1 )
					{
						fprintf ( g, "%c",ENCODE_BASE_64 ( ((buff[1] & 0xF) << 2) | buff[2] >> 6 ) );

						if ( i > 2 )
						{
							fprintf ( g, "%c", ENCODE_BASE_64 ( buff[2] & 0x3F ) );
						}
						else
						{
							fprintf ( g, "=");
						}
					}
					else
					{
						fprintf ( g, "==");
					}

					buff[0] = buff[1] = buff[2] = 0;
				}

				result = 0;

				fclose ( g);
			}

			fclose ( f);
		}
	}

	return result;
}


gint gw_decode_file_base64 ( gchar *src, gchar *dst)
{
	FILE *f, *g;
	unsigned char buff[4];
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( src != NULL && dst != NULL )
	{
		if ( !(f = fopen ( src, "r")))
		{
			// May be used for default source
			//f = stdin;

			if ( !(g = fopen ( dst, "w")))
			{
				// May be used for default destination
				//g = stdout;

				while ( fread ( buff, 1, 4, f) == 4 )
				{
					fprintf ( g, "%c", (DECODE_BASE_64 ( buff[0]) << 2) | (DECODE_BASE_64 ( buff[1]) >> 4 & 0x3));
					DECODE_BASE_64_ISEND ( buff[2])
					fprintf ( g, "%c", (DECODE_BASE_64 ( buff[1]) << 4) | (DECODE_BASE_64 ( buff[2]) >> 2 & 0xF));
					DECODE_BASE_64_ISEND ( buff[3])
					fprintf ( g, "%c", (DECODE_BASE_64 ( buff[2]) << 6) | (DECODE_BASE_64 ( buff[3]) & 0x3F));
				}

				result = 0;

				fclose ( g);
			}

			fclose ( f);
		}
	}

	return result;
}
