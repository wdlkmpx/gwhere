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
#include "gwfilesystem.h"

#include <sys/types.h> /* lseek read open */
#include <sys/stat.h> /* open */
#include <unistd.h> /* lseek read close */
#include <string.h> /* strncmp */
#include <fcntl.h> /* open */


gint gw_fs_get_type ( const gchar *fs, gchar **fs_type)
{
	gint result = -1;
#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
	guint errmode;
	char type_buf[1024];
	DWORD max_file_len;
	DWORD system_flags;
#ifdef GW_DEBUG_MODE
	LPVOID msg = NULL;
#endif
	const gchar *fs_port = NULL;
#endif


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL)
	{
#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
		if ( (GetVersion ( ) >= 0x80000000) && (strncmp ( fs, "\\\\.\\", 4) == 0) )
		{
			fs_port = &fs[4];
		}
		else
		{
			fs_port = fs;
		}

		errmode = SetErrorMode ( SEM_FAILCRITICALERRORS);

		if ( GetVolumeInformation ( fs_port, NULL, 0, NULL, &max_file_len, &system_flags, type_buf, sizeof ( type_buf)) )
		{
			*fs_type = g_strdup ( type_buf);
			g_strdown ( *fs_type);
			result = 0;
		}
		else
		{
#ifdef GW_DEBUG_TOOLS_COMPONENT
			FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError ( ), 0, (LPTSTR) &msg, 0, NULL );
			g_print ( "*** GW - %s (%d) :: %s() : an win32 error occured, %s (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, GetLastError ( ));
			LocalFree( msg );
#endif
		}

		SetErrorMode ( errmode);
#else
		if ( gw_fs_is_iso9660 ( fs) )
		{
			*fs_type = g_strdup ( "iso9660");
		}
		else { if ( gw_fs_is_fat12 ( fs) )
		{
			*fs_type = g_strdup ( "fat12");
		}
		else { if ( gw_fs_is_fat16 ( fs) )
		{
			*fs_type = g_strdup ( "fat16");
		}
		else { if ( gw_fs_is_fat32 ( fs) )
		{
			*fs_type = g_strdup ( "fat32");
		}}}}
#endif
	}

	return result;
}


gint gw_fs_get_volume_name ( const gchar *fs, gchar **fs_volume_name)
{
	gint result = -1;
#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
	guint errmode;
	char vol_buf[1024];
	DWORD max_file_len;
	DWORD system_flags;
#ifdef GW_DEBUG_MODE
	LPVOID msg = NULL;
#endif
	const gchar *fs_port = NULL;
#endif

#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL)
	{
#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
		if ( (GetVersion ( ) >= 0x80000000) && (strncmp ( fs, "\\\\.\\", 4) == 0) )
		{
			fs_port = &fs[4];
		}
		else
		{
			fs_port = fs;
		}

		errmode = SetErrorMode ( SEM_FAILCRITICALERRORS);

		if ( GetVolumeInformation ( fs_port, vol_buf, sizeof ( vol_buf), NULL, &max_file_len, &system_flags, NULL, 0) )
		{
			*fs_volume_name = g_strdup ( vol_buf);
			result = 0;
		}
		else
		{
#ifdef GW_DEBUG_TOOLS_COMPONENT
			FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError ( ), 0, (LPTSTR) &msg, 0, NULL );
			g_print ( "*** GW - %s (%d) :: %s() : an win32 error occured, %s (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, GetLastError ( ));
			LocalFree( msg );
#endif
		}

		SetErrorMode ( errmode);
#else
		if ( gw_fs_is_iso9660 ( fs) )
		{
			*fs_volume_name = gw_fs_iso9660_get_volume_name ( fs);
		}
		else { if ( gw_fs_is_fat12 ( fs) )
		{
			*fs_volume_name = gw_fs_fat12_get_volume_name ( fs);
		}
		else { if ( gw_fs_is_fat16 ( fs) )
		{
			*fs_volume_name = gw_fs_fat16_get_volume_name ( fs);
		}
		else { if ( gw_fs_is_fat32 ( fs) )
		{
			*fs_volume_name = gw_fs_fat32_get_volume_name ( fs);
		}}}}

		result = 0;
#endif
	}

	return result;
}


gint gw_fs_get_serial_number ( const gchar *fs, gchar **fs_serial_number)
{
	gint result = -1;
#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
	guint errmode;
	char vol_buf[1024];
	DWORD serial_number;
	DWORD max_file_len;
	DWORD system_flags;
#ifdef GW_DEBUG_MODE
	LPVOID msg = NULL;
#endif
	const gchar *fs_port = NULL;
#endif


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL)
	{
#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
		if ( (GetVersion ( ) >= 0x80000000) && (strncmp ( fs, "\\\\.\\", 4) == 0) )
		{
			fs_port = &fs[4];
		}
		else
		{
			fs_port = fs;
		}

		errmode = SetErrorMode ( SEM_FAILCRITICALERRORS);

		if ( GetVolumeInformation ( fs_port, vol_buf, sizeof ( vol_buf), &serial_number, &max_file_len, &system_flags, NULL, 0) )
		{
			*fs_serial_number = g_strdup_printf ( "%u", (unsigned int)serial_number);
			result = 0;
		}
		else
		{
#ifdef GW_DEBUG_TOOLS_COMPONENT
			FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError ( ), 0, (LPTSTR) &msg, 0, NULL );
			g_print ( "*** GW - %s (%d) :: %s() : an win32 error occured, %s (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, GetLastError ( ));
			LocalFree( msg );
#endif
		}

		SetErrorMode ( errmode);
#else
		if ( gw_fs_is_iso9660 ( fs) )
		{
			*fs_serial_number = gw_fs_iso9660_get_serial_number ( fs);
		}
		else { if ( gw_fs_is_fat12 ( fs) )
		{
			*fs_serial_number = gw_fs_fat12_get_serial_number ( fs);
		}
		else { if ( gw_fs_is_fat16 ( fs) )
		{
			*fs_serial_number = gw_fs_fat16_get_serial_number ( fs);
		}
		else { if ( gw_fs_is_fat32 ( fs) )
		{
			*fs_serial_number = gw_fs_fat32_get_serial_number ( fs);
		}}}}

		result = 0;
#endif
	}

	return result;
}


gint gw_fs_read_data ( const gchar *fs, gint seek, gint len, gchar *data)
{
	guint fic;
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		if ( ( fic = open ( fs, O_RDONLY ) ) != -1 )
		{
			if ( lseek ( fic, seek, SEEK_SET) != -1 )
			{
				if ( read ( fic, data, len) != -1 )
				{
					data[len] = '\0';
					result = 0;

#ifdef GW_DEBUG_TOOLS_COMPONENT
					g_print ( "*** GW - %s (%d) :: %s() : data=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, data);
#endif

				}
			}

			close ( fic);
		}
	}

	return result;
}


gint gw_fs_contain_data ( const gchar *fs, gint seek, gint len, const gchar *data)
{
	gchar buf[len + 1];
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		if ( gw_fs_read_data ( fs, seek, len, buf) != -1 )
		{
			if ( strncmp ( buf, data, len) == 0)
			{
				result = 0;
			}
		}
	}	

	return result;
}



gboolean gw_fs_is_fat12 ( const gchar *fs)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		/* Note that file system identifer size is 8 bytes but "FAT12" size is 5. */
		if ( gw_fs_contain_data ( fs, 54, 5, "FAT12") == 0)
		{
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_fs_is_fat16 ( const gchar *fs)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		/* Note that file system identifer size is 8 bytes but "FAT16" size is 5. */
		if ( gw_fs_contain_data ( fs, 54, 5, "FAT16") == 0)
		{
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_fs_is_fat32 ( const gchar *fs)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		/* Note that file system identifer size is 8 bytes but "FAT32" size is 5. */
		if ( gw_fs_contain_data ( fs, 82, 5, "FAT32") == 0)
		{
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_fs_is_iso9660 ( const gchar *fs)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		/* TO VALIDATE : some CD-ROM haven't "ISO 9660" tag. */
		/*if ( gw_fs_contain_data ( fs, 33350, 8, "ISO 9660") == 0)*/
		if ( gw_fs_contain_data ( fs, 32769, 5, "CD001") == 0)
		{
			result = TRUE;
		}
	}

	return result;
}


gchar * gw_fs_fat12_get_volume_name ( const gchar *fs)
{
	gint seek = 43;
	gint len = 11;
	gchar *buf = NULL;
	gchar *volume_name = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		buf = (gchar *)g_malloc ( len + 1);

		if ( gw_fs_read_data ( fs, seek, len, buf) != -1 )
		{
			/* Checks if there is a label name */
			if ( (strncmp ( buf, "NO NAME", 7) == 0) || (strncmp ( buf, " ",1) == 0))
			{
				g_free ( buf);
			}
			else
			{
				/* Removes all spaces (at the begin and the end of the label */
				volume_name = g_strstrip ( buf);
			}
		}
	}

	return volume_name;
}


gchar * gw_fs_fat16_get_volume_name ( const gchar *fs)
{
	gint seek = 43;
	gint len = 11;
	gchar *buf = NULL;
	gchar *volume_name = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		buf = (gchar *)g_malloc ( len + 1);

		if ( gw_fs_read_data ( fs, seek, len, buf) != -1 )
		{
			/* Checks if there is a label name */
			if ( (strncmp ( buf, "NO NAME", 7) == 0) || (strncmp ( buf, " ",1) == 0))
			{
				g_free ( buf);
			}
			else
			{
				/* Removes all spaces (at the begin and the end of the label */
				volume_name = g_strstrip ( buf);
			}
		}
	}	

	return volume_name;
}


gchar * gw_fs_fat32_get_volume_name ( const gchar *fs)
{
	gint seek = 71;
	gint len = 11;
	gchar *buf = NULL;
	gchar *volume_name = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		buf = (gchar *)g_malloc ( len + 1);

		if ( gw_fs_read_data ( fs, seek, len, buf) != -1 )
		{
			/* Checks if there is a label name */
			if ( (strncmp ( buf, "NO NAME", 7) == 0) || (strncmp ( buf, " ",1) == 0))
			{
				g_free ( buf);
			}
			else
			{
				/* Removes all spaces (at the begin and the end of the label */
				volume_name = g_strstrip ( buf);
			}
		}
	}

	return volume_name;
}


gchar * gw_fs_iso9660_get_volume_name ( const gchar *fs)
{
	gint seek = 32808;
	gint len = 32;
	gchar *buf = NULL;
	gchar *volume_name = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		buf = (gchar *)g_malloc ( len + 1);

		if ( gw_fs_read_data ( fs, seek, len, buf) != -1 )
		{
#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : data=%s length=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, buf, strlen ( buf));
#endif

			/* Checks if there is a label name */
			if ( (strncmp ( buf, "NO NAME", 7) == 0) || (strncmp ( buf, " ",1) == 0))
			{
				g_free ( buf);
			}
			else
			{
				/* Removes all spaces (at the begin and the end of the label */
				volume_name = g_strstrip ( buf);

#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : data=%s length=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, volume_name, strlen ( volume_name));
#endif

			}
		}
	}

	return volume_name;
}


gchar * gw_fs_fat12_get_serial_number ( const gchar *fs)
{
	gint seek = 39;
	gint len = 4;
	gchar *buf = NULL;
	gchar *serial_number = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		buf = (gchar *)g_malloc ( len + 1);

		if ( gw_fs_read_data ( fs, seek, len, buf) != -1 )
		{
			/* Checks if there is a serial number */
			if ( (strncmp ( buf, " ",1) == 0) || (strlen ( buf) != len) )
			{
				g_free ( buf);
			}
			else
			{
				/* Removes all spaces (at the begin and the end of the serial number) */
				serial_number = g_strstrip ( buf);
			}
		}
	}	

	return serial_number;
}


gchar * gw_fs_fat16_get_serial_number ( const gchar *fs)
{
	gint seek = 39;
	gint len = 4;
	gchar *buf = NULL;
	gchar *serial_number = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		buf = (gchar *)g_malloc ( len + 1);

		if ( gw_fs_read_data ( fs, seek, len, buf) != -1 )
		{
			/* Checks if there is a serial number */
			if ( (strncmp ( buf, " ",1) == 0) || (strlen ( buf) != len) )
			{
				g_free ( buf);
			}
			else
			{
				/* Removes all spaces (at the begin and the end of the serial number) */
				serial_number = g_strstrip ( buf);
			}
		}
	}	

	return serial_number;
}


gchar * gw_fs_fat32_get_serial_number ( const gchar *fs)
{
	gint seek = 67;
	gint len = 4;
	gchar *buf = NULL;
	gchar *serial_number = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		buf = (gchar *)g_malloc ( len + 1);

		if ( gw_fs_read_data ( fs, seek, len, buf) != -1 )
		{
			/* Checks if there is a serial number */
			if ( (strncmp ( buf, " ",1) == 0) || (strlen ( buf) != len) )
			{
				g_free ( buf);
			}
			else
			{
				/* Removes all spaces (at the begin and the end of the serial number) */
				serial_number = g_strstrip ( buf);
			}
		}
	}	

	return serial_number;
}


gchar * gw_fs_iso9660_get_serial_number ( const gchar *fs)
{
	/* FIX BUG : Where is the serial number on ISO 9660? */
	gint seek = 0;
	gint len = 0;
	gchar *buf = NULL;
	gchar *serial_number = NULL;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		buf = (gchar *)g_malloc ( len + 1);

		if ( gw_fs_read_data ( fs, seek, len, buf) != -1 )
		{
			/* Checks if there is a serial number */
			if ( (strncmp ( buf, " ",1) == 0) || (strlen ( buf) != len) )
			{
				g_free ( buf);
			}
			else
			{
				/* Removes all spaces (at the begin and the end of the serial number) */
				serial_number = g_strstrip ( buf);
			}
		}
	}	

	return serial_number;
}
