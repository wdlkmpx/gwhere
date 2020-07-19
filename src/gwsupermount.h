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
 * @header	gwsupermount.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a component to manipulate disks.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwsupermount.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_SUPERMOUNT_H
#define GW_SUPERMOUNT_H


/*!
 * @function	gw_get_drives_list
 * @abstract	Gets the list of all drives in the system.
 * @discussion	This function gets the list of all drives in the system.<br>
 *		Search all mount points for Unix-like system or all logical
 *		drives for Win32 system.
 * @param	drives_list	the list to store the list.
 * @result	the list of drives.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GList * gw_get_drives_list ( GList *drives_list);


/*!
 * @function	gw_drive_eject
 * @abstract	Ejects the drive.
 * @discussion	This function ejects the drive.<br>
 *		<b>Warning :</b> eject only CD-ROM drive.<br>
 *		On Unix-like system the drive path is the mount point.<br>
 *		On Win32 system the drive path is the drive letter, use "[A-Z]:\".<br>
 * @param	drive_path	the access path of drive.
 * @result	Returns <i>TRUE</i> if it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_drive_eject ( const gchar *drive_path);


#ifdef HAVE_MOUNT_SYSTEM


/*!
 * @function	gw_drive_mount
 * @abstract	Tries to mount the drive.
 * @discussion	This function tries to mount the drive.<br>
 *		<b>Warning :</b> only for Unix-like system with super-user rights.<br>
 *		On Unix-like system the drive path is the mount point.<br>
 * @param	drive_path	the access path of drive.
 * @result	Returns <i>O</i> if it's done.<br>
 *		Returns <i>1</i> if it is already mounted.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_drive_mount ( const gchar *drive_path);


/*!
 * @function	gw_drive_umount
 * @abstract	Tries to unmount the drive.
 * @discussion	This function tries to unmount the drive.<br>
 *		<b>Warning :</b> only for Unix-like system with super-user rights.<br>
 *		On Unix-like system the drive path is the mount point.<br>
 * @param	drive_path	the access path of drive.
 * @result	Returns <i>TRUE</i> if it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_drive_umount ( const gchar *drive_path);


/*!
 * @function	gw_drive_get_device_type
 * @abstract	Gets the type of the device.
 * @discussion	This function gets the type of the device.<br>
 *		<b>Warning :</b> only for Unix-like system.<br>
 *		On Unix-like system the drive path is the mount point.<br>
 * @param	drive_path	the access path of drive.
 * @result	Device type.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_drive_get_device_type ( const gchar *drive_path);


/*!
 * @function	gw_drive_get_device_name
 * @abstract	Gets the name of the device.
 * @discussion	This function gets the name of the device.<br>
 *		<b>Warning :</b> only for Unix-like system.<br>
 *		On Unix-like system the drive path is the mount point.<br>
 * @param	drive_path	the access path of drive.
 * @result	Device name.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_drive_get_device_name ( const gchar *drive_path);


/*!
 * @function	gw_drive_is_mounted
 * @abstract	Checks if the drive is mounted.
 * @discussion	This function checks if the drive is mounted.<br>
 *		<b>Warning :</b> only for Unix-like system.<br>
 *		On Unix-like system the drive path is the mount point.<br>
 * @param	drive_path	the access path of drive.
 * @result	Returns <i>TRUE</i> if the drive is mounted.<br>
 *		Returns <i>FALSE</i> if the drive is not mounted or when an error occured.
 */
gboolean gw_drive_is_mounted ( const gchar *drive_path);


/*!
 * @function	gw_drive_is_mountable
 * @abstract	Checks if the drive is mountable.
 * @discussion	This function checks if the drive is mountable.<br>
 *		<b>Warning :</b> deprecated function!!<br>
 *		<b>Warning :</b> only for Unix-like system.<br>
 *		On Unix-like system the drive path is the mount point.<br>
 * @param	drive_path	the access path of drive.
 * @result	Returns <i>TRUE</i> if the drive is mountable.<br>
 *		Returns <i>FALSE</i> if the drive is not mountable or when an error occured.
 */
gboolean gw_drive_is_mountable ( const gchar *drive_path);


#endif


/*!
 * @function	gw_drive_get_capacity
 * @abstract	Gets the capacity of the drive.
 * @discussion	This function gets the capacity of the drive..<br>
 *		<b>Warning :</b> deprecated function!!<br>
 *		<b>Warning :</b> under win32 the size is inKbytes.<br>
 *		On Unix-like system the drive path is the mount point.<br>
 * @param	drive_path	the access path of drive.
 * @result	the capacity of the drive.<br>
 *		Returns <i>0</i> when an error occured.
 */
gulong gw_drive_get_capacity ( const gchar *drive_path);


/*!
 * @function	gw_drive_get_free_space
 * @abstract	Gets the free space of the drive.
 * @discussion	This function gets the free space of the drive..<br>
 *		<b>Warning :</b> deprecated function!!<br>
 *		<b>Warning :</b> under win32 the size is in Kbytes.<br>
 *		On Unix-like system the drive path is the mount point.<br>
 * @param	drive_path	the access path of drive.
 * @result	the free space of the drive.<br>
 *		Returns <i>0</i> when an error occured.
 */
gulong gw_drive_get_free_space ( const gchar *drive_path);


#endif
