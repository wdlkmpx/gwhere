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


/*!
 * @header	gwfilesystem.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a tool component for file system.
 * @discussion	All functions run on GNU/Linux well and should be done with Cygwin.<br><br>
 *		<b>Warning :</b> Functions may failed if the user haven't got good right to open device files.<br><br>
 *
 *		This is an uncomplete list of device file name :<br><br>
 *
 *		<u>On GNU/Linux :</u><br>
 *		Floppy drive : /dev/fd[0-9]<br>
 *		Hard disk : /dev/hd[a-z][0-9]<br>
 *		CD drive : /dev/cdrom[0-9]<br>
 *		Zip drive : /dev/zip[0-9]<br>
 *		SCSI drive : /dev/scd[0-9]<br>
 *		Tape drive : /dev/tape[0-9]<br><br>
 *		
 *		<u>On Cygwin for Windows NT/W2K/XP :</u><br>
 *		Floppy drive : /dev/fd[0-9]<br>
 *		Hard disk : /dev/sd[a-z][0-9] or /dev/sd[0-99]<br>
 *		CD drive : /dev/scd[0-9]<br>
 *		Zip drive : ??<br>
 *		SCSI drive : ??<br>
 *		Tape drive : /dev/[n]st[0-9]<br><br>
 *
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2002/05/19
 * @see		gwsupport.h
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		Zlib Web Site <http://www.zlib.org>
 * @ref		gwfilesystem.c
 * @author	Author <zero@gwhere.org>
 * @author	Luis PARRAVICINI
  */


#ifndef GW_TOOLS_FILE_SYSTEM_H
#define GW_TOOLS_FILE_SYSTEM_H


/*!
 * @function	gw_fs_get_type
 * @abstract	Gets the type of the file system.
 * @discussion	This function gets the type of the file system.<br>
 *		Under MS Windows with NT kernel device name is <i>\\.\[A-Z]:\</i>. Under
 *		MS Windows with Win9x,ME kernel the device name is <i>\\.\[A-Z]:\</i> or
 *		<i>[A-Z]:\</i>.
 * @param	fs		device name of the file system
 * @param	fs_type		a pointer to the store the fs type (Note that must be free with g_free())
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_fs_get_type ( const gchar *fs, gchar **fs_type);


/*!
 * @function	gw_fs_get_volume_name
 * @abstract	Gets the volume name of the file system.
 * @discussion	This function gets the volume name of the file system.<br>
 *		Under MS Windows with NT kernel device name is <i>\\.\[A-Z]:\</i>. Under
 *		MS Windows with Win9x,ME kernel the device name is <i>\\.\[A-Z]:\</i> or
 *		<i>[A-Z]:\</i>.
 * @param	fs		device name of the file system
 * @param	fs_type		a pointer to the store the fs volume name (Note that must be free with g_free())
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_fs_get_volume_name ( const gchar *fs, gchar **fs_volume_name);


/*!
 * @function	gw_fs_get_serial_number
 * @abstract	Gets the serial number of the file system.
 * @discussion	This function gets the serial number of the file system.<br>
 *		Under MS Windows with NT kernel device name is <i>\\.\[A-Z]:\</i>. Under
 *		MS Windows with Win9x,ME kernel the device name is <i>\\.\[A-Z]:\</i> or
 *		<i>[A-Z]:\</i>.
 * @param	fs		device name of the file system
 * @param	fs_type		a pointer to the store the fs serial number (Note that must be free with g_free)
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_fs_get_serial_number ( const gchar *fs, gchar **fs_volume_name);


/*!
 * @function	gw_fs_read_data
 * @abstract	Reads data in the file system.
 * @discussion	This function reads data in the file system.<br>
 * @param	fs		device name of the file system
 * @param	seek		position in file system of data
 * @param	len		length of data
 * @param	data		data (note that data must point to a buffer of sufficient size, size must bigger than len)
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_fs_read_data ( const gchar *fs, gint seek, gint len, gchar *data);


/*!
 * @function	gw_fs_contain_data
 * @abstract	Checks if the file system contains the data.
 * @discussion	This function checks if the file system contains the data..<br>
 * @param	fs		device name of the file system
 * @param	seek		position in file system of data to compare
 * @param	len		length of data the compare
 * @param	data		data (note that data must point to a buffer of sufficient size, size must bigger than len)
 * @result	Returns <i>0</i> if the file system contains the data.<br>
 *		Returns <i>-1</i> if doesn't contain the data or when an error occured.<br>
 */
gint gw_fs_contain_data ( const gchar *fs, gint seek, gint len, const gchar *data);


/*!
 * @function	gw_fs_is_fat12
 * @abstract	Checks if the file system is a FAT12 file system.
 * @discussion	This function checks if the file system is a FAT12 file system.<br>
 * @param	fs		device name of the file system
 * @result	Returns <i>TRUE</i> if it's a FAT 12 file sytem.<br>
 *		Returns <i>FALSE</i> if it's not a FAT 12 file system or when an error occured.<br>
 */
gboolean gw_fs_is_fat12 ( const gchar *fs);


/*!
 * @function	gw_fs_is_fat16
 * @abstract	Checks if the file system is a FAT12 file system.
 * @discussion	This function checks if the file system is a FAT12 file system.<br>
 * @param	fs		device name of the file system
 * @result	Returns <i>TRUE</i> if it's a FAT 12 file sytem.<br>
 *		Returns <i>FALSE</i> if it's not a FAT 12 file system or when an error occured.<br>
 */
gboolean gw_fs_is_fat16 ( const gchar *fs);


/*!
 * @function	gw_fs_is_fat32
 * @abstract	Checks if the file system is a FAT12 file system.
 * @discussion	This function checks if the file system is a FAT12 file system.<br>
 * @param	fs		device name of the file system
 * @result	Returns <i>TRUE</i> if it's a FAT 12 file sytem.<br>
 *		Returns <i>FALSE</i> if it's not a FAT 12 file system or when an error occured.<br>
 */
gboolean gw_fs_is_fat32 ( const gchar *fs);


/*!
 * @function	gw_fs_is_iso9660
 * @abstract	Checks if the file system is a ISO 9660 file system.
 * @discussion	This function checks if the file system is a ISO 9660 file system.<br>
 * @param	fs		device name of the file system
 * @result	Returns <i>TRUE</i> if it's a ISO 9660 file sytem.<br>
 *		Returns <i>FALSE</i> if it's not a ISO 9660 file system or when an error occured.<br>
 */
gboolean gw_fs_is_iso9660 ( const gchar *fs);


/*!
 * @function	gw_fs_fat12_get_volume_name
 * @abstract	Gets the volume name of a FAT12 file system.
 * @discussion	This function gets the volume name of a FAT12 file system..<br>
 * @param	fs		device name of the file system
 * @result	The volume name.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_fs_fat12_get_volume_name ( const gchar *fs);


/*!
 * @function	gw_fs_fat16_get_volume_name
 * @abstract	Gets the volume name of a FAT16 file system.
 * @discussion	This function gets the volume name of a FAT16 file system..<br>
 * @param	fs		device name of the file system
 * @result	The volume name.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_fs_fat16_get_volume_name ( const gchar *fs);


/*!
 * @function	gw_fs_fat32_get_volume_name
 * @abstract	Gets the volume name of a FAT32 file system.
 * @discussion	This function gets the volume name of a FAT32 file system..<br>
 * @param	fs		device name of the file system
 * @result	The volume name.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_fs_fat32_get_volume_name ( const gchar *fs);


/*!
 * @function	gw_fs_iso9660_get_volume_name
 * @abstract	Gets the volume name of a ISO9660 file system.
 * @discussion	This function gets the volume name of a ISO 9660 file system..<br>
 * @param	fs		device name of the file system
 * @result	The volume name.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_fs_iso9660_get_volume_name ( const gchar *fs);


/*!
 * @function	gw_fs_fat12_get_serial_number
 * @abstract	Gets the serial number of a FAT12 file system.
 * @discussion	This function gets the serial number of a FAT12 file system..<br>
 * @param	fs		device name of the file system
 * @result	The serial number.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_fs_fat12_get_serial_number ( const gchar *fs);


/*!
 * @function	gw_fs_fat16_get_serial_number
 * @abstract	Gets the serial number of a FAT16 file system.
 * @discussion	This function gets the serial number of a FAT16 file system..<br>
 * @param	fs		device name of the file system
 * @result	The serial number.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_fs_fat16_get_serial_number ( const gchar *fs);


/*!
 * @function	gw_fs_fat32_get_serial_number
 * @abstract	Gets the serial number of a FAT32 file system.
 * @discussion	This function gets the serial number of a FAT32 file system..<br>
 * @param	fs		device name of the file system
 * @result	The serial number.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_fs_fat32_get_serial_number ( const gchar *fs);


/*!
 * @function	gw_fs_iso9660_get_serial_number
 * @abstract	Gets the serial number of a ISO9660 file system.
 * @discussion	This function gets the serial number of a ISO 9660 file system.<br>
 * @param	fs		device name of the file system
 * @result	The serial number.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_fs_iso9660_get_serial_number ( const gchar *fs);


#endif
