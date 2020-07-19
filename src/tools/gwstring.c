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
#include "gwstring.h"

#include <time.h> /* asctime */
#include <string.h> /* strcmp strlen memmove strstr strncmp strerror memcpy */
#include <ctype.h> /* isspace*/
#include <regex.h> /* regcomp regexec */
#include <stdlib.h> /* abs */


#ifndef strsep
char *strsep ( char **stringp, const char *delim)
{
	char *res = NULL;


	if ( !stringp || !*stringp || !**stringp )
	{
		return (char*)0;
	}

	res = *stringp;

	while ( **stringp && !strchr ( delim, **stringp) )
	{
		(*stringp)++;
	}

	if(**stringp)
	{
		**stringp = '\0';
		(*stringp)++;
	}

	return res;
}
#endif  /* strsep */


unsigned long int gw_ntohl ( unsigned long int in)
{
	unsigned char a[4], t;


	memcpy ( a, &in, 4);

	t = a[3];
	a[3] = a[0];
	a[0] = t;

	t = a[2];
	a[2] = a[1];
	a[1] = t;

	memcpy ( &in, a, 4);

	return in;
}


gchar * gw_l_byte_to_str_format ( long size )
{
	long double n = size * 1.0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return gw_ld_byte_to_str_format ( n);
}


gchar * gw_ul_byte_to_str_format ( unsigned long size )
{
	long double n = size * 1.0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return gw_ld_byte_to_str_format ( n);
}


gchar * gw_ui64_byte_to_str_format ( guint64 size )
{
	long double n = size * 1.0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return gw_ld_byte_to_str_format ( n);
}


gchar * gw_d_byte_to_str_format ( gdouble size )
{
	long double n = size * 1.0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return gw_ld_byte_to_str_format ( n);
}


gchar * gw_ld_byte_to_str_format ( long double n)
{
	long double m = n * 1.0;
	gint i = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	while ( (m = (m / 1024.0)) >= 1 )
	{
		i++;
	}

	switch ( i)
	{
		case 0 :	return g_strdup_printf ( _( "%.0f bytes"), (double)n);

				break;

		case 1 :	return g_strdup_printf ( _( "%.2f Kb"), (double)(n / 1024));

				break;

		case 2 :	return g_strdup_printf ( _( "%.2f Mb"), (double)(n / 1048576));

				break;

		case 3 :	return g_strdup_printf ( _( "%.2f Gb"), (double)(n / 1073741824));

				break;

		case 4 :	m = n / 1073741824;
				return g_strdup_printf ( _( "%.2f Tb"), (double)( m / 1024));

				break;

		case 5 :	m = n / 1073741824;
				return g_strdup_printf ( _( "%.2f Pb"), (double)( m / 1048576));

				break;

		case 6 :	m = n / 1073741824;
				return g_strdup_printf ( _( "%.2f Hb"), (double)( m / 1073741824));

				break;

		case 7 :	m = n / 1073741824;
				m = m / 1073741824;
				return g_strdup_printf ( _( "%.2f Ib"), (double)( m / 1024));

				break;

		default :	m = n / 1073741824;
				m = m / 1073741824;
				return g_strdup_printf ( _( "%.2f Ib"), (double)( m / 1024));

				break;
	}
}


long double gw_str_format_to_ld ( gchar * nb)
{
	long double n;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( nb[strlen ( nb) -2] == ' ')
	{
		/* Size in byte */
		return g_strtod ( nb, NULL);
	}
	else { if ( nb[strlen ( nb) -2] == 'K')
	{
		/* Size in kilo byte */
		n = 1024 * g_strtod ( nb, NULL);

		return n;
	}
	else { if ( nb[strlen ( nb) -2] == 'M')
	{
		/* Size in mega byte */
		n = 1048576 * g_strtod ( nb, NULL);

		return n;
	}
	else { if ( nb[strlen ( nb) -2] == 'G')
	{
		/* Size in giga byte */
		n = 1073741824 * g_strtod ( nb, NULL);

		return n;
	}
	else { if ( nb[strlen ( nb) -2] == 'T')
	{
		/* Size in tera byte */
		n = 1024;
		n = n * 1073741824;
		n = n * g_strtod ( nb, NULL);

		return n;
	}
	else { if ( nb[strlen ( nb) -2] == 'P')
	{
		/* Size in penta byte */
		n = 1048576;
		n = n * 1073741824;
		n = n * g_strtod ( nb, NULL);

		return n;
	}
	else { if ( nb[strlen ( nb) -2] == 'H')
	{
		/* Size in hexa byte */
		n = 1024 * g_strtod ( nb, NULL);

		return n;
	}
	else { if ( nb[strlen ( nb) -2] == 'I')
	{
		/* Size in iota byte */
		n = 1073741824;
		n = n * 1073741824;
		n = n * g_strtod ( nb, NULL);

		return n;
	}}}}}}}}

	return 0;
}


gchar * gw_tm_to_str_format ( struct tm* p)
{
        gchar * date = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
        g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

        if ( p != NULL )
        {
#ifdef __DEPRECATED__
		/* The code has changed to fix untranslated date under win32. */
                date = asctime ( p);

                if ( date != NULL )
                {
                	/* Add this code for unhoped end character on win32. */
                        if ( isprint ( date[strlen ( date)-1]) == 0)
                        {
                                date[strlen ( date)-1]='\0';
                        }
                }
#else
		if ( (date = (gchar*)g_malloc ( sizeof ( gchar) * 20)) != NULL )
		{
			strftime ( date, 20, "%d/%m/%Y %H:%M:%S", p);
		}
#endif
        }

        return date;
}


gchar * gw_str_to_file ( gchar *str)
{
	gchar *txt = NULL;
	gchar *cti[3] = {"\n", ":", NULL};
	gchar *cto[3] = {"\\n", "\\#", NULL};


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : string=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, str);
#endif

	if ( str != NULL )
	{
		txt = gw_str_replace_strv ( str, cti, cto);
	}

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : encoded string=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, txt);
#endif

	return txt;
}


gchar * gw_str_to_file_strb ( const gchar *pattern, GWStringBuffer *buf)
{
	gchar *q = NULL;
	gchar *result = NULL;
	gint nb = 0;
	gchar *chr1 = NULL, *chr2 = NULL;

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : string to encode=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, pattern);
#endif

	if ( (pattern != NULL) && (strlen(pattern) > 0) )
	{
		q = (gchar*)pattern;
		while ( q[0] != '\0' )
		{
			if ( (q[0] == '\n') || (q[0] == ':') )
			{
				nb++;
			}
			q++;
		}
		/*
		q = (gchar*)pattern;
		while ( (q = strchr ( q, '\n')) != NULL ){nb++;q++;}
		q = (gchar*)pattern;
		while ( (q = strchr ( q, ':')) != NULL ){nb++;q++;}
		*/

		gw_string_buffer_resize ( buf, strlen ( pattern) + nb);
		gw_string_buffer_set_str ( buf, (gchar*)pattern, strlen ( pattern));

		if ( nb > 0 )
		{
			/* Warning this algorythm is optimized but it is very dangerous!! */
			result = gw_string_buffer_get_str ( buf);
			q = result;
			chr1 = strchr ( q, '\n');
			chr2 = strchr ( q, ':');
			while ( chr1 != NULL || chr2 != NULL )
			{
				if ( (chr1 != NULL ) && ((chr2 == NULL ) || (chr1 < chr2)) )
				{
					q = chr1;
					gw_string_buffer_replace_chr ( buf, 'n', q - result);
					gw_string_buffer_insert_str ( buf, "\\", q - result, 1);
					q++;
					chr1 = strchr ( q, '\n');
					if ( chr2 != NULL) {
						chr2++;
					}
				}
				else
				{
					q = chr2;
					gw_string_buffer_replace_chr ( buf, '#', q - result);
					gw_string_buffer_insert_str ( buf, "\\", q - result, 1);
					q++;
					chr2 = strchr ( q, ':');
					if ( chr1 != NULL) {
						chr1++;
					}
				}
			}
		}
	}
	else
	{
		gw_string_buffer_set_str ( buf, (gchar*)pattern, 0);
	}

	result = gw_string_buffer_get_str ( buf);

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : encoded string=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, result);
#endif

	return result;
}


gchar * gw_file_to_str ( gchar *desc)
{
	gchar **buf = NULL;
	gchar *txt = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : decode string=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, desc);
#endif

	if ( desc != NULL )
	{
		txt = g_strdup ( desc);
		buf = g_strsplit ( txt, "\\n", 0);

		if ( buf != NULL )
		{
			g_free ( txt);
			txt = g_strjoinv ( "\n", buf);

			g_strfreev ( buf);
			buf = NULL;

			buf = g_strsplit ( txt, "\\#", 0);

			if ( buf != NULL )
			{
				g_free ( txt);
				txt = g_strjoinv ( ":", buf);

				g_strfreev ( buf);
				buf = NULL;
			}
		}
	}


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : decoded string=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, txt);
#endif

	return txt;
}


gchar * gw_str_replace_str ( gchar *pattern, gchar *src, gchar *dst)
{
	gint srclen = 0, dstlen = 0;
	gchar *p, *q, *qq, *pp;
	gchar *result = NULL;
	gint nb = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pattern != NULL )
	{
		/* Counts the number of string token to replace. */
		q = pattern;
		while ( (q = strstr ( q, src)) != NULL )
		{
			nb++;
			q++;
		}

		/* If there is string token to replace only duplicates the string. */
		if ( nb != 0 ) {
			/* Allocates the needed memory by the new string. */
			srclen = strlen ( src);
			dstlen = strlen ( dst);
			if ( (result = (gchar *)g_malloc ( strlen ( pattern) + (nb * (dstlen - srclen)) + 1)) != NULL )
			{
				qq = result;
				q = pattern;

				/* Copies the string and replaces all src string tokens by dst string tokens. */
				while ( (p = strstr ( q, src)) != NULL )
				{
					pp = qq + (p - q);
					memcpy ( qq, q, p - q);
					memcpy ( pp, dst, dstlen);
					q = p + srclen;
					qq = pp + dstlen;
				}

				memcpy ( qq, q, strlen ( pattern) - (q - pattern));
				*((qq + strlen ( pattern)) - (q - pattern)) = '\0';
			}
		}
	}

	return result;
}


gchar * gw_str_replace_strv ( gchar *pattern, gchar **src, gchar **dst)
{
	gchar *tmp = NULL, *result = NULL;
	gboolean modified = FALSE;
	gint i = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pattern != NULL )
	{
		tmp = pattern;

		/* Tries to replace all string token couples. */
		while ( ( src[i] != NULL ) || ( dst[i] != NULL ) )
		{
			if ( (result = gw_str_replace_str ( tmp, src[i], dst[i])) != NULL )
			{
				/* If it is not modified, it is the original string pattern. */
				if ( modified == TRUE )
				{
					g_free ( tmp);
				}
				tmp = result;

				/* Indicates that the string was modified. */
				modified = TRUE;
			}

			i++;
		}

		if ( modified == TRUE )
		{
			/* If it is was modified gets the new pattern. */
			result = tmp;
		}
	}


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() before=%s after=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, pattern, result);
#endif

	return result;
}


gchar * gw_str_blob_to_regex ( gchar *blob)
{
	/* Warning : the order of convert_table_in/out is important!! */
	gchar *regex = NULL;
	gchar *convert_table_in[17] = {"\\", ".", "*", "?", "^", "$", "|", "(", ")", "[", "]", "{", "{", "+", "?", ",", NULL};
	gchar *convert_table_out[17] = {"\\\\","\\.",".*",".","\\^","\\$","\\|","\\(","\\)","\\[","\\[","\\}","\\}","\\+","\\?","\\,", NULL};


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( blob != NULL )
	{
		if ( ( regex = gw_str_replace_strv ( blob, convert_table_in, convert_table_out)) == NULL )
		{
			regex = g_strdup ( blob);
		}
	}

	return regex;
}


gchar ** gw_str_key_words_to_regex ( gchar *key_words)
{
	gchar **words = NULL;
	gchar *regex_build = NULL;
	int i = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( key_words != NULL )
	{
		gw_strdel_chrsry ( key_words, ' ');
		gw_str_trim ( key_words);
		words = g_strsplit ( key_words, " ", 0);

		if ( words != NULL )
		{
			for ( i = 0; words[i] != NULL; i++)
			{
				regex_build = g_strconcat ( ".*", words[i], ".*", NULL);
				g_free ( words[i]);
				words[i] = regex_build;
#ifdef GW_DEBUG_TOOLS_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : an new pattern search is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, words[i]);
#endif
			}
		}
	}

	return words;
}


gint gw_strcmp_strblob ( gchar *str, gchar *blob, gboolean case_sensitive)
{
	gchar *tmp_str = NULL;
	gchar *tmp_blob = NULL;
	gchar *keep_str = NULL;
	gchar **words = NULL;
	gchar *tmp = NULL;
	gint i;
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ( str != NULL ) || ( blob != NULL ) )
	{
		tmp_str = keep_str = g_strdup ( str);
		tmp_blob = g_strdup ( blob);

		if ( case_sensitive )
		{
			g_strdown ( tmp_str);
                		g_strdown ( tmp_blob);
		}

		words = g_strsplit ( tmp_blob, "*", 0);

		for ( i = 0; words[i] != NULL; i++)
		{
			if ( (tmp = strstr ( tmp_str, words[i])) != NULL )
			{
				tmp_str = tmp;

				if ( words[i + 1] == NULL )
				{
					if ( tmp_blob[strlen ( tmp_blob) - 1] != '*' )
					{
						if ( strlen ( words[i]) != strlen ( tmp_str))
						{
							tmp_str = NULL;

							break;
						}
					}
				}
			}
			else
			{
				tmp_str = NULL;

				break;
			}
		}

		if ( tmp_str != NULL )
		{
			if ( strcmp ( words[0], "" ) != 0)
			{
				if ( strncmp ( keep_str, words[0], strlen ( words[0])) == 0 )
				{
					result = 0;
				}
			}
			else { if ( strcmp ( words[0], "" ) == 0)
			{
				result = 0;
			}}
		}

		if ( keep_str != NULL )
		{
			g_free ( keep_str);
		}

		if ( tmp_blob != NULL )
		{
			g_free ( tmp_blob);
		}

		if ( words != NULL )
		{
			g_strfreev ( words);
		}
	}

#ifdef GW_DEBUG_TOOLS_COMPONENT
	if ( result == 0 )
	{
		g_print ( "*** GW - %s (%d) :: %s() : %s == %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, str, blob);
	}
	else
	{
		g_print ( "*** GW - %s (%d) :: %s() : %s <> %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, str, blob);
	}
#endif

	return result;
}


gint gw_strcmp_strregex ( gchar *str, gchar *regex, gboolean case_sensitive)
{
        regex_t *r=NULL;
	regex_t real;
        gint cflags;
        gint result = -1;
	r = &real;


#ifdef GW_DEBUG_TOOLS_COMPONENT
        g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( case_sensitive == FALSE )
	{
		cflags = REG_ICASE|REG_NOSUB;
	}
	else
	{
		cflags = 0|REG_NOSUB;
	}

	if ( regcomp ( r, regex, cflags) == 0 )
	{
		if ( regexec ( r, str, 0, NULL, 0) == 0 )
		{
			result = 0;
		}
	}

	regfree ( r);

#ifdef GW_DEBUG_TOOLS_COMPONENT
        if ( result == 0 )
        {
                g_print ( "*** GW - %s (%d) :: %s() : %s == %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, str, regex);
        }
        else
        {
                g_print ( "*** GW - %s (%d) :: %s() : %s <> %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, str, regex);
        }
#endif

        return result;
}


gint gw_strdel_chrsry ( gchar *str, const gchar chr)
{
	/* The index i is the cursor for read and the index j is the cursor for write.
	   This function scan the complet string and read/write each character except
	   if it is equal to the specified character and the following characters is
	   equal this one.
	   The result is the number of deleted characters.
	 */
	gint i = 0;
	gint j = 0;
	gint result = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : the initial string is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, str);
#endif

	if ( str != NULL )
	{
		/* Scan the complet string in order to find all specified doubled characters
		   Reads all characters until the NULL character. */
		while ( str[i] != '\0' )
		{
			/* Check if the current character is equal to the specified character. */
			if ( str[i] == chr )
			{
				/* In the case where the current character is equal to the specified
				   character, check if the following character is equal to the specified
				   character too (in this case the caracter is doubled).
				 */
				if ( str[i] == str[i+1] )
				{
					/* Do not write the character because it is doubled with the following.
					   Only increment the number of deleted characters.
					 */
					result++;
				}
				else
				{
					/* The following character is different from the current character.
					   Must write the character to the new index and after increment the
					   index of the character to write.
					 */
					str[j++] = str[i];
				}
			}
			else
			{
				/* The current character is different from the specified character. Must
				   write the character to the new index and after increment the index of
				   the character to write.
				 */
				str[j++] = str[i];
			}

			/* Increment the index of the current character to read. */
			i++;
		}

		/* Copy the NULL character at the end of the new string (the index of the character
		   to write).
		 */
		str[j] = '\0';
	}

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : the new string is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__,str);
#endif

	return result;
}


gint gw_str_trim_doubled_char ( gchar *str)
{
	char *ptrcar, *ptrsearch, *ptrsrc, *ptrdest;
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( str != NULL )
	{
		ptrcar = str;

		while ( *ptrcar)
		{
			ptrsearch = ptrcar + 1;

			while ( *ptrsearch)
			{
				if ( *ptrsearch == *ptrcar )
				{
					ptrsrc = ptrdest = ptrsearch;
					ptrsrc++;

					while ( *ptrsrc)
					{
						if ( *ptrsrc != *ptrcar )
						{
							*(ptrdest++) = *(ptrsrc++);
						}
						else
						{
							ptrsrc++;
						}
					}

					*ptrdest = '\0';
				}

				ptrsearch++;
			}

			ptrcar++;
		}

		result = 0;
	}

	return result;
}


gint gw_str_trim ( gchar* str)
{
	unsigned long nb_space, size;
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( str != NULL )
	{
		/* Gets the string size */
		size = strlen ( str);

		/* Counts the number of begining white spaces */
		nb_space = 0;

		while ( isspace ( str[nb_space]) && (str[nb_space]))
		{
			nb_space++;
		}

		if ( !str[nb_space])
		{
			/* The string is only white spaces. Returns empty string */
			str[0] = '\0';
		}
		else
		{
			/* Removes all begining white spaces */
			if ( nb_space)
			{
				memmove ( str, str + nb_space, size - nb_space);
				size -= nb_space;
			}

			/* Removes all ending white spaces */
			while ( size && ( isspace ( str[size-1])))
			{
				size--;
			}

			str[size] = '\0';
		}

		result = 0;
	}

	return result;
}


gint gw_str_trim2 ( gchar *str)
{
	gint result = -1;
	gint i = 0, j = 0, end = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( str != NULL )
	{
		/* Counts all spaces. */
		while ( str[i] == ' ')
		{
			i++;
		}

		/* If there are spaces move all characters. */
		if ( i != 0 )
		{
			while ( (str[i] != '\0'))
			{
				str[j] = str[i];
				i++;
				j++;

				if ( str[i] != ' ')
				{
					end = i;
				}
			}
		}
		else
		{
			while ( (str[i] != '\0'))
			{
				if ( str[i] != ' ')
				{
					end = i;
				}

				i++;
			}
		}

		if ( end < i )
		{
			for ( j = (end+1); str[j] != '\0'; j++ )
			{
				str[j] = '\0';
			}
		}
		else if ( i != 0 )
		{
			str[j] = '\0';
		}

		result = 0;
	}

	return result;
}


gint gw_str_trim_left ( gchar *str)
{
	gint result = -1;
	gint i = 0, j = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( str != NULL )
	{
		/* Counts all spaces. */
		while ( str[i] == ' ')
		{
			i++;
		}

		/* If there are spaces move all characters. */
		while ( (str[i] != '\0') && (i != 0))
		{
			str[j] = str[i];
			i++;
			j++;
		}

		if ( i != 0 )
		{
			str[j] = '\0';
		}

		result = 0;
	}

	return result;
}


gint gw_str_trim_right ( gchar *str)
{
	gint result = -1;
	gint i = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( str != NULL )
	{
		i = strlen ( str);

		/* Counts all spaces. */
		while ( (str[i - 1] == ' ') && ( i != 0))
		{
			str[i - 1] = '\0';
			i--;
		}

		result = 0;
	}

	return result;
}


gint gw_str_delete_char ( gchar *str, gchar c)
{
	gint i = 0, j;
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( str != NULL )
	{
		while ( i < strlen ( str))
		{
			if ( str[i] == c )
  			{
  				j = i;

				while ( j < ( strlen ( str)))
				{
					str[j] = str[j + 1];
					j = j + 1;
				}
			}
			else
			{
				i = i + 1;
			}
		}

		result = 0;
	}

	return result;
}


gint gw_str_replace_char ( gchar *string, gchar before, gchar after)
{
	gchar *p = NULL;
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( string != NULL )
	{
		for ( p = string; *p; p++)
		{
			if ( *p == before )
			{
				*p = after;
			}
		}

		result = 0;
	}

	return result;
}


gint gw_str_substr ( const gchar *str, gint begin, gint end, gchar *dest)
{
	gint len = 0;
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( str != NULL )
	{
		len = end + 1 - begin;
		dest[len] = '\0';
		memcpy ( dest, (gchar *)str + begin, len);

		result = len;
	}

	return result;
}


gint gw_str_dupsubstr ( const gchar *str, gint begin, gint end, gchar **dest)
{
	gint len = 0;
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( str != NULL )
	{
		len = end + 1 - begin;

		*dest = (gchar*)g_malloc ( sizeof ( gchar) * (len + 1));

		dest[len] = '\0';
		memcpy ( *dest, (gchar *)str + begin, len);

		result = len;
	}

	return result;
}


gint gw_str_to_lower ( gchar *str)
{
	gint result = -1;
	gint i = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( str != NULL )
	{
		while ( str[i] != '\0' )
		{
			str[i] = tolower ( str[i]);
			i++;
		}

		result = 0;
	}

	return result;
}


gint gw_str_to_upper ( gchar *str)
{
	gint result = -1;
	gint i = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( str != NULL )
	{
		while ( str[i] != '\0' )
		{
			str[i] = toupper ( str[i]);
			i++;
		}

		result = 0;
	}

	return result;
}


gint gw_str_to_ascii ( gchar *str, gint len)
{
	gint result = -1;
	gint i = 0;


	if ( str != NULL)
	{
		while ( ((len >=0) && (i < len)) || ((len == -1) && (str[i] != '\0')))
		{
			if ( isascii ( str[i]) == 0)
			{
				str[i] = ' ';
			}

			i++;
		}

		result = 0;
	}

	return result;
}


gint gintlen ( const gint n)
{
	gint len = 1;
	gdouble quo = 1;
	gdouble result = 1.0;


	if ( n > 9 )
	{
		result = abs ( n / quo);

	while ( result > 1)
	{
		len ++;
		quo = quo * 10;
			result = abs ( n / quo);
	}

	len--;
	}

	return len;
}


gchar * gw_time_to_str ( gulong t, const gchar *format) {
	struct tm *time = NULL;
	gchar *date = NULL;


	if ( t != 0 ) {
		if ( (time = localtime ( &t)) != NULL ) {
			if ( (date = (gchar*)g_malloc ( sizeof ( gchar) * 20)) != NULL ) {
				strftime ( date, 20, format, time);

				return date;
			} else {}
		} else {}
	} else {}

	return NULL;
}


gchar * gw_time_to_str_df ( gulong t) {
	return gw_time_to_str ( t, DATE_FORMAT);
}
