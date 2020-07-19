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
#include "gwfile.h"

#include <stdio.h> /* perror */
#include <sys/types.h> /* mkdir */

#if defined ( OS_WIN32)
#include <sys/stat.h> /* open */
#endif

#include <fcntl.h> /* open mkdir */
#include <string.h> /* strcmp strcpy malloc strchr strrchr */
#include <sys/stat.h> /* stat */
#include <unistd.h> /* close read write stat mkdir */
#include <stdlib.h> /* malloc on Cygwin */
#include <errno.h> /* errno */


int gw_file_copy ( const gchar *source, const gchar *dest)
{
	int src,dst,n;
	gchar buffer[512];


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ( src = open ( source, O_RDONLY) ) == -1 )
	{
		perror ( "source");

		return -1;
	}

	if ( ( dst = open ( dest, O_WRONLY|O_TRUNC|O_CREAT, 0666) ) == -1 )
	{
		perror ( "destination");
		close ( src);

		return -1;
	}

	while ( ( n = read ( src, buffer, 512) ) > 0 )
	{
		if ( n != write ( dst, buffer, n) )
		{
			return -1;
		}
	}

	if ( n < 0 )
	{
		return -1;
	}

	close ( src);
	close ( dst);

	return 0;
}


gchar * gw_file_read_until_c ( int fic, gchar c, int len)
{
	gchar temp[2], tmp[(len==-1?MAX_LINE:len)];
	gchar *buf;
	int i = 0, n;
gchar *tmp_tmp=NULL,*tmp2 = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( len == -1 )
	{
		tmp2 = (gchar*)g_malloc0 ( MAX_LINE);
		i = 0;

		while ( (n = read ( fic, temp, 1)) > 0 )
		{
			if ( (i+1)%MAX_LINE == 0 )
			{
				tmp_tmp = (gchar*)g_realloc ( tmp2, i + MAX_LINE);
				tmp2 = tmp_tmp;
			}

			if ( temp[0] == c)
			{
				return tmp2;
			}

			tmp2[i++] = temp[0];
		}

		if ( tmp2 != NULL )
		{
			g_free ( tmp2);
			tmp2 = NULL;
		}
	}
	else
	{
	temp[1] = '\0';

	while ( ( n = read ( fic, temp, 1) ) > 0 )
	{
		if ( temp[0] == c )
		{
			if ( ( buf = (gchar*)g_malloc0 ( 2)) == NULL )
			{
				perror ( "g_malloc0");

				return NULL;
			}

			strcpy ( buf, "");

			return buf;
		}

		tmp[i++] = temp[0];

		while ( temp[0] != c )
		{
			if ( ( n = read ( fic, temp, 1) ) == 0)
			{
				return NULL;
			}

			tmp[i++] = temp[0];
		}

		tmp[--i] = '\0';

		if ( ( buf = (gchar*)g_malloc0 ( i + 1) ) == NULL )
		{
			perror ( "g_malloc0");

			return NULL;
		}

		strcpy ( buf, tmp);

		return buf;
	}
	}

	return NULL;
}


gchar * gw_zfile_read_until_c ( gzFile fic, gchar c, int len)
{
	char temp[2], tmp[len];
	char *buf;
	int i = 0, n;
#ifdef GW_DEBUG_TOOLS_COMPONENT
	unsigned int zlen = len;
#endif


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : reads %d characters\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, zlen);
#endif
	temp[1] = '\0';

/*	while ( ( temp[0] = gzgetc ( fic) ) != -1 )*/
	while ( (( n = gzread ( fic, &temp[0], 1) ) != -1) && ( n == 1 ))
	{
#ifdef GW_DEBUG_TOOLS_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : %c\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, temp[0]);
#endif
		if ( temp[0] == c )
		{
			if ( ( buf = (gchar*)g_malloc0 ( 2)) == NULL )
			{
				perror ( "g_malloc0");

				return NULL;
			}

			strcpy ( buf, "");

			return buf;
		}

		tmp[i++] = temp[0];

		while ( temp[0] != c )
		{
#ifdef GW_DEBUG_TOOLS_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : %c\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, temp[0]);
#endif
/*			if ( ( temp[0] = gzgetc ( fic) ) == -1)*/
			if ( (( n = gzread ( fic, &temp[0], sizeof ( temp[0])) ) == -1)  && ( n == 0 ))
			{
				return NULL;
			}

			tmp[i++] = temp[0];
		}

		tmp[--i] = '\0';
/*		tmp[i] = '\0';*/

		if ( ( buf = (gchar*)g_malloc0 ( i + 1) ) == NULL )
		{
			perror ( "g_malloc0");

			return NULL;
		}

		strcpy ( buf, tmp);

		return buf;
	}

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : reading is done (n=%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, n);
#endif

	return NULL;
}


gchar * gw_file_readline_sb ( FILE *fic, GWStringBuffer **sb) {
	gchar buf[MAX_LINE+1];
	gchar *line = NULL;
	gchar *ret = NULL;
	gulong sb_size = 0;
	gulong sb_len = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	memset(buf,'\0',MAX_LINE+1);
	if ( *sb == NULL ) {
		*sb = gw_string_buffer_new ( );
		gw_string_buffer_resize ( *sb, MAX_LINE);
	}

	line = gw_string_buffer_get_str(*sb);
	gw_string_buffer_delete_all ( *sb);
	sb_size = gw_string_buffer_get_size ( *sb);
	line = gw_string_buffer_get_str(*sb);

	do {
		memset(buf,'\0',MAX_LINE+1);
		ret = fgets ( buf, MAX_LINE, fic);
		gw_string_buffer_append_str ( *sb, buf, strlen(buf));
		line = gw_string_buffer_get_str ( *sb);
		sb_len = strlen ( line);
	} while ( (ret != NULL) && (sb_len != 0) && ((line)[sb_len - 1] != '\n'));

	if ( sb_len > 0 ) {
		/* In order to eraze the final '\n' character. */
		line[sb_len - 1] = '\0';
		memset(&line[sb_len-1],'\0',(gw_string_buffer_get_size ( *sb)-sb_len+1));
	}

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : current_line=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, line);
#endif

	if ( ret==NULL) {
		line = NULL;
#ifdef GW_DEBUG_TOOLS_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : END_OF_FILE\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return line;
}


gchar * gw_file_readline ( int fic, gchar *buf, int len)
{
#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	buf = gw_file_read_until_c ( fic, '\n', len);

	return buf;
}


gchar * gw_zfile_readline_sb ( gzFile fic, GWStringBuffer **sb)
{
	gchar buf[MAX_LINE+1];
	gchar *line = NULL;
	int ret = 0;
	gulong sb_size = 0;
	gulong sb_len = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	memset(buf,'\0',MAX_LINE+1);
	if ( *sb == NULL )
	{
		*sb = gw_string_buffer_new ( );
		gw_string_buffer_resize ( *sb, MAX_LINE);
	}

	line = gw_string_buffer_get_str(*sb);
	gw_string_buffer_delete_all ( *sb);
	sb_size = gw_string_buffer_get_size ( *sb);
	line = gw_string_buffer_get_str(*sb);

	do
	{
		memset(buf,'\0',MAX_LINE+1);
		ret = (int)gzgets ( fic, buf, MAX_LINE);
		gw_string_buffer_append_str ( *sb, buf, strlen(buf));
		line = gw_string_buffer_get_str ( *sb);
		sb_len = strlen ( line);
	} while ( (ret != Z_NULL) && (sb_len != 0) && ((line)[sb_len - 1] != '\n'));

	if ( sb_len > 0 )
	{
		/* In order to eraze the final '\n' character. */
		line[sb_len - 1] = '\0';
		memset(&line[sb_len-1],'\0',(gw_string_buffer_get_size ( *sb)-sb_len+1));
	}

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : current_line=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, line);
#endif

	if ( ret==Z_NULL) {
		line = NULL;
#ifdef GW_DEBUG_TOOLS_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : END_OF_FILE\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return line;
}


gchar * gw_zfile_readline ( gzFile fic, gchar **buf, int len)
{
	int slen;
	int size = sizeof ( gchar) * (MAX_LINE + 1);
	gchar *tmp_buf = NULL;
#ifdef GW_DEBUG_TOOLS_COMPONENT
	int zerr;
#endif


	if ( len == -1)
	{
		*buf = (gchar*)g_malloc ( size);
	}
	else
	{
		memset ( *buf, '\0', len);
	}

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : len=%d (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, len, (len==-1?MAX_LINE:len));
#endif

	if ( gzgets ( fic, *buf, (len==-1?MAX_LINE:len)) == Z_NULL )
	{
		slen = strlen ( *buf);
#ifdef GW_DEBUG_TOOLS_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : error during gzgets (error=%s), current zbuffer=%s \tlength=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, gzerror(fic,&zerr), *buf, slen);
		g_print ( "*** GW - %s (%d) :: %s() : error_code=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, zerr);
#endif

	if ( len == -1 )
	{
			g_free ( *buf);
			*buf = NULL;
	}

		return NULL;
	}

	slen = strlen ( *buf);

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : current zbuffer=%s \tlength=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, *buf, slen);
#endif

	if ( len == -1 )
	{
		while ( (slen != 0) && ((*buf)[slen - 1] != '\n') )
		{
			size += sizeof ( gchar) * MAX_LINE;
#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : new size is %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, size);
#endif

			tmp_buf = (gchar*)g_realloc ( *buf, size);
			*buf = tmp_buf;

#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : reallocated\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
			if ( gzgets ( fic, &((*buf)[slen]), MAX_LINE) == Z_NULL )
			{
#ifdef GW_DEBUG_TOOLS_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : error during gzgets (error=%s), current zbuffer=%s \tlength=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, gzerror(fic,&zerr), *buf, slen);
				g_print ( "*** GW - %s (%d) :: %s() : error_code=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, zerr);
#endif

				g_free ( *buf);
				*buf = NULL;

				return NULL;
			}

			slen = strlen ( *buf);
#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : current zbuffer=%s \tlength=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, *buf, slen);
#endif
		}
	}

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : final zbuffer=%s \tlength=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, *buf, slen);
#endif

	if ( (slen == 0) && ((*buf)[slen - 1] != '\n') )
	{
		if ( len == -1 )
		{
			g_free ( *buf);
			*buf = NULL;
		}

		return NULL;
	}

	(*buf)[slen - 1] = '\0';

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : new zbuffer=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, *buf);
#endif

	return *buf;
}


long gw_file_get_size ( FILE * file)
{
	long pos;
	long len = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( file != NULL )
	{
		pos = ftell ( file);
		fseek ( file, 0L, SEEK_END);
		len = ftell ( file);
		fseek ( file, pos, SEEK_SET);
	}

	return len;
}


int gw_file_exists ( const gchar *pathname)
{
	int result = -1;
	struct stat fd;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : testing if %s exists\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, pathname);
#endif

	if ( pathname != NULL )
	{
		if ( stat ( pathname, &fd) == 0 )
		{
			result = 0;
		}
	}

	return result;
}


gchar * gw_file_get_name ( const gchar *pathname)
{
	gchar * result = NULL;
	gchar * last = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : the file name of %s without path\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, pathname);
#endif

	if ( pathname != NULL )
	{
		last = strrchr ( pathname, G_DIR_SEPARATOR);

		if ( last != NULL )
		{
			result = g_strdup ( last++);
		}
	}

	return result;
}


int gw_file_mkdir ( const gchar *pathname)
{
	int result = -1;
	struct stat fd;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : creating %s if not exists\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, pathname);
#endif

	if ( pathname != NULL )
	{
		if ( stat ( pathname, &fd) == 0 )
		{
			/* The folder already exists. */
			result = 0;
		}
		else
		{
#if defined (OS_WIN32)
			if ( mkdir ( pathname) == 0 )
#else
			if ( mkdir ( pathname, S_IRUSR|S_IWUSR|S_IXUSR) == 0 )
#endif
			{
				result = 0;
			}
			else
			{
				switch ( errno )
				{
					case EEXIST :	result = 0;

							break;

					default :	break;
				}
			}
		}
	}

	return result;
}


int gw_file_mkdirs ( const gchar *pathname)
{
	int result = -1;
	struct stat fd;
	gchar *last = NULL;
	gchar *parent_pathname = NULL;
	int length = 0;
	int i = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : creating %s if not exists\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, pathname);
#endif

	if ( pathname != NULL )
	{
		if ( stat ( pathname, &fd) == 0 )
		{
			/* The folder already exists. */
			result = 0;
		}
		else
		{
#if defined (OS_WIN32)
			if ( mkdir ( pathname) == 0 )
#else
			if ( mkdir ( pathname, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP) == 0 )
#endif
			{
				result = 0;
			}
			else
			{
				switch ( errno )
				{
					case EEXIST :	result = 0;

							break;

					case ENOENT:	/* Must create all folders in the path. */

							last = strrchr ( pathname, G_DIR_SEPARATOR);

							/* Bug to fix : pathname is a const char *, cannot be modified. */
							if ( last[1] == '\0' )
							{
								i = last - pathname;
								while ( (i >= 0) && ( pathname[i] != G_DIR_SEPARATOR) )
								{
									i--;
								}

								if ( i > 0 )
								{
									last = (gchar*)&pathname[i];
								}
								else
								{
									last = NULL;
								}
							}

							if ( last != NULL )
							{
								length = last - pathname;

								parent_pathname = (gchar *)g_malloc0 ( sizeof ( char) * length + 1);
								parent_pathname = strncpy ( parent_pathname, pathname, length);
								parent_pathname[length] = '\0';

								if ( gw_file_mkdirs ( parent_pathname) == 0 )
								{
									if ( gw_file_mkdirs ( pathname) == 0 )
									{
										result = 0;
									}
								}

								g_free ( parent_pathname);
							}

					default :	break;
				}
			}
		}
	}

	return result;
}


int gw_zfile_uncompress ( const gchar *in_filepath, const gchar *out_filepath)
{
	gchar buf[MAX_LINE];
	int len;
	gzFile in = NULL;
	FILE *out = NULL;
	int result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (in = gzopen ( in_filepath, "rb")) != NULL )
	{
		if ( (out = fopen ( out_filepath, "w+")) != NULL )
		{
			for (;;)
			{
				len = gzread ( in, buf, sizeof ( buf));

				if ( len < 0 )
				{
					/*error (gzerror(in, &err))*/;
				}

				if ( len == 0 )
				{
					break;
				}

				if ( (int)fwrite ( buf, 1, (unsigned)len, out) != len)
				{
					/*error("failed fwrite")*/;
				}
			}

			if ( fclose ( out) )
			{
				/*error("failed fclose")*/;
			}

			result = 0;
		}

		if ( gzclose ( in) != Z_OK )
		{
			/*error("failed gzclose")*/;
		}
	}

	return result;
}
