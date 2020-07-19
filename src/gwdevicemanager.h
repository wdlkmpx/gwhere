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
 * @header	gwdevicemanager.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a component to manage devices.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwdevicemanager.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_DEVICE_MANAGER_H
#define GW_DEVICE_MANAGER_H


#include <glib.h>

#include "data/gwdata.h"


/*!
 * @function	gw_dm_device_load_to_vfs_stats
 * @abstract	Loads the virtual file system stats.
 * @discussion	This function loads the virtual file system. Initialize
 * 		all informations as name, path, total size, free space,
 * 		label, ...
 * @param	p	the virtual file system to load
 * @param	dir	the file system path
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_dm_device_load_to_vfs_stats ( struct vfs_stats *p, gchar *dir);


/*!
 * @function	gw_dm_disk_try_mount_from_vfs_stats
 * @abstract	Tries to mount the disk.
 * @discussion	This function tries to mount the disk of the virtual file system stats.<br>
 *		Use the /bin/mount and /bin/umount programs to mount disk
 * @param	p	the virtual file system stats to try to mount disk
 * @result	<i>TRUE</i> if can be mounted or <i>FALSE</i> if can be not mounted.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_dm_disk_try_mount_from_vfs_stats ( struct vfs_stats *p);


/*!
 * @function	gw_dm_search_disk_in_tab_file_to_vfs_stats
 * @abstract	Searches and sets informations from the device table
 * @discussion	This function searches and sets informations from the device table.<br>
 * @param	p		the virtual file system stats to search and set informations
 * @param	tab_file	the device table file name
 * @param	dir		the file system path
 * @result	<i>TRUE</i> if the disk found and loaded or <i>FALSE</i> if hasn't been found.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_dm_search_disk_in_tab_file_to_vfs_stats ( struct vfs_stats *p, const gchar *tab_file, const gchar *dir);


/*!
 * @function	gw_dm_disk_mount_from_vfs_stats
 * @abstract	Mounts the disk.
 * @discussion	This function mounts the disk of the virtual file system stats.<br>
 *		Use the /bin/mount programs to mount disk
 * @param	p	the virtual file system stats to try to mount disk
 * @result	<i>TRUE</i> if can mount or <i>FALSE</i> if cannot mount.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_dm_disk_mount_from_vfs_stats ( struct vfs_stats *p);


/*!
 * @function	gw_dm_disk_umount_from_vfs_stats
 * @abstract	Umounts the disk.
 * @discussion	This function umounts the disk of the virtual file system stats.<br>
 *		Use the /bin/umount programs to umount disk
 * @param	p	the virtual file system stats to try to umount disk
 * @result	<i>TRUE</i> if can umount or <i>FALSE</i> if cannot umount.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_dm_disk_umount_from_vfs_stats ( struct vfs_stats *p);


/*!
 * @function	gw_pipe_get_data
 * @abstract	Gets data in the pipe.
 * @discussion	This function gets the data in the pipe.<br>
 * @param	entry	the pipe to get data
 * @param	line	the string to extract data from pipe
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_pipe_get_data ( gint entry, gchar * line);


/*!
 * @function	gw_dm_disk_get_device_name
 * @abstract	Gets the device name of a mount point.
 * @discussion	This function gets the device name of a mount point.<br>
 *		<b>Warning :</b> it's an ugly function. Runs only for floppy drive
 * 		(1 and 2) and for first primary disk (partition 1 and 2).
 *		It was developped in the cas eof the experimental port on Cygwin.
 * @param	mount_point	the mount point path
 * @param	device_name	a pointer to get device name (Note that device_name
 * 				must be free with g_free).
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_dm_disk_get_device_name ( const gchar *mount_point, gchar **device_name);


/*!
 * @function	gw_dm_disk_is_mounted_from_vfs_stats
 * @abstract	Gets if is mounted.
 * @discussion	This function tries and gets if the virtual file system stats is mounted.<br>
 * @param	p	the virtual file system stats to get if is mounted
 * @result	<i>TRUE</i> if is mounted or <i>FALSE</i> if is not mounted.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_dm_disk_is_mounted_from_vfs_stats ( struct vfs_stats *p);


/*!
 * @function	gw_dm_disk_can_mounted_from_vfs_stats
 * @abstract	Gets if can be mounted.
 * @discussion	This function gets if the virtual file system stats can be mounted.<br>
 * @param	p	the virtual file system stats to get if can be mounted
 * @result	<i>TRUE</i> if can be mounted or <i>FALSE</i> if can be not mounted.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_dm_disk_can_mounted_from_vfs_stats ( struct vfs_stats *p);


/*!
 * @function	gw_dm_is_disk_in_drive
 * @abstract	Gets if there is a disk in the drive.
 * @discussion	This function gets if there is a disk in the drive.<br>
 *		Use mount as drive_path under Linux-like system.<br>
 *		Use the drive letter ("A:\", "D:\", ...) under win32 system.<br>
 * @param	drive_path	the drive path
 * @result	<i>TRUE</i> if there is a disk or <i>FALSE</i> if there is no disk.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_dm_is_disk_in_drive ( const gchar *drive_path);


#endif
