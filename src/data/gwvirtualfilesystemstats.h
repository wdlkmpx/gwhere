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
 * @header	gwvirtualfilesystemstats.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br>
 *		It's an object for the virtual representation of a file system. This structure gets many informations as name, path, label, size, ...
 *		Can check or try mount the virtual file system.<br><br>
 * @abstract	This is the virtual file system stats data structure.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 20020/12/05
 * @see		gwsupport.h
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK+ Web Site <http://www.gtk.org>
 * @ref		gwvirtualfilesystemstats.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_DATA_VIRTUAL_FILE_SYSTEM_STATS_H
#define GW_DATA_VIRTUAL_FILE_SYSTEM_STATS_H


#include <glib.h>


/*!
 * @struct	vfs_stats
 * @abstract	Virtual File System Statistics information data structure
 * @discussion	Virtual File System Statstics information is an opaque data structure containing information about a virtual file system properties and informations.
 */
struct vfs_stats;


/*!
 * @function	vfs_stats_new
 * @abstract	Creates a new virtual file system stats.
 * @discussion	This function creates a new virtual file system stats. It's an allocation function.
 * @result	a pointer to the virtual file system stats structure.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
struct vfs_stats * vfs_stats_new ( void);


/*!
 * @function	vfs_stats_display
 * @abstract	Dipslays all informations of the virtual file system stats.
 * @discussion	This function displays all informations of the virtual file system stats in the console.
 * @param	p	the virtual file system to load
 */
void vfs_stats_display ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_set_name
 * @abstract	Sets the virtual file system stats name.
 * @discussion	This function sets the virtual file system stats name.<br>
 * @param	p	the virtual file system stats to set name
 * @param	name	the name
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_name ( struct vfs_stats *p, gchar *name);


/*!
 * @function	vfs_stats_set_dir
 * @abstract	Sets the virtual file system stats path.
 * @discussion	This function sets the virtual file system stats path.<br>
 * @param	p	the virtual file system stats to set path
 * @param	dir	the fiel system path
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_dir ( struct vfs_stats *p, gchar *dir);


/*!
 * @function	vfs_stats_set_label
 * @abstract	Sets the virtual file system stats label.
 * @discussion	This function sets the virtual file system stats label.<br>
 * @param	p	the virtual file system stats to set label
 * @param	label	the file system label
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_label ( struct vfs_stats *p, gchar *label);


/*!
 * @function	vfs_stats_set_type
 * @abstract	Sets the virtual file system stats type.
 * @discussion	This function sets the virtual file system stats type.<br>
 *		Type can be <i>vfat, ext2, iso9660,...</i>
 * @param	p	the virtual file system stats to set type
 * @param	type	the file system type
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_type ( struct vfs_stats *p, gchar *type);


/*!
 * @function	vfs_stats_set_options
 * @abstract	Sets the virtual file system stats options.
 * @discussion	This function sets the virtual file system stats options.<br>
 * @param	p	the virtual file system stats to set options
 * @param	options	the file system options
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_options ( struct vfs_stats *p, gchar **options);


/*!
 * @function	vfs_stats_set_ismounted
 * @abstract	Sets if the virtual file system stats is mounted.
 * @discussion	This function sets if the virtual file system stats is mounted.<br>
 * @param	p	the virtual file system stats to set mount status
 * @param	mounted	the mount status
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_ismounted ( struct vfs_stats *p, gboolean mounted);


/*!
 * @function	vfs_stats_set_nb_files
 * @abstract	Sets the total number of files of the virtual file system stats.
 * @discussion	This function sets the total number of files of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to set number of files
 * @param	nb_file	the number of files
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_nb_files ( struct vfs_stats *p, gulong nb_files);


/*!
 * @function	vfs_stats_set_blocks_size
 * @abstract	Sets blocks size of the virtual file system stats.
 * @discussion	This function sets blocks size of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to set blocks size
 * @param	blocks_size	the blocks size
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_blocks_size ( struct vfs_stats *p, glong blocks_size);


/*!
 * @function	vfs_stats_set_blocks
 * @abstract	Sets total number blocks of the virtual file system stats.
 * @discussion	This function sets total number blocks of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to set total number blocks
 * @param	blocks	the total number blocks
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_blocks ( struct vfs_stats *p, gulong blocks);


/*!
 * @function	vfs_stats_set_blocks_free
 * @abstract	Sets free blocks number of the virtual file system stats.
 * @discussion	This function sets free blocks number size of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to set free blocks number
 * @param	blocks_free	the free blocks number
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_blocks_free ( struct vfs_stats *p, gulong blocks_free);


/*!
 * @function	vfs_stats_set_serial_number
 * @abstract	Sets the virtual file system stats serial number.
 * @discussion	This function sets the virtual file system stats serial number.<br>
 * @param	p	the virtual file system stats to set serial number
 * @param	serial_number	the file system serial number
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint vfs_stats_set_serial_number ( struct vfs_stats *p, gchar *serial_number);


/*!
 * @function	vfs_stats_get_name
 * @abstract	Gets the virtual file system stats name.
 * @discussion	This function gets the virtual file system stats name.<br>
 * @param	p	the virtual file system stats to get name
 * @result	The name.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * vfs_stats_get_name ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_dir
 * @abstract	Gets the virtual file system stats path.
 * @discussion	This function gets the virtual file system stats path.<br>
 * @param	p	the virtual file system stats to get path
 * @result	The path.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * vfs_stats_get_dir ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_label
 * @abstract	Gets the virtual file system stats label.
 * @discussion	This function gets the virtual file system stats label.<br>
 * @param	p	the virtual file system stats to get label
 * @result	The label.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * vfs_stats_get_label ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_type
 * @abstract	Gets the virtual file system stats type.
 * @discussion	This function gets the virtual file system stats type.<br>
 * @param	p	the virtual file system stats to get type
 * @result	The file system type.<br>
 *		Returns <i>NULL</i> when file system type is unknown or
 *		when an error occured.<br>
 */
gchar * vfs_stats_get_type ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_serial_number
 * @abstract	Gets the virtual file system stats serial number.
 * @discussion	This function gets the virtual file system stats serial number.<br>
 * @param	p	the virtual file system stats to get serial number
 * @result	The device serial number.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * vfs_stats_get_serial_number ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_options
 * @abstract	Gets the virtual file system stats options.
 * @discussion	This function gets the virtual file system stats options.<br>
 * @param	p	the virtual file system stats to get options
 * @result	The mount options
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar ** vfs_stats_get_options ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_ismounted
 * @abstract	Gets if is mounted.
 * @discussion	This function gets if the virtual file system stats is mounted.<br>
 * @param	p	the virtual file system stats to get if is mounted
 * @result	<i>TRUE</i> if is mounted or <i>FALSE</i> if is not mounted.<br>
 *		Returns <i>FALSE</i> when an error occured.<br>
 */
gboolean vfs_stats_get_ismounted ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_nb_files
 * @abstract	Gets the total number of files of the virtual file system stats.
 * @discussion	This function gets the total number of files of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to get number of files
 * @result	The number of files
 *		Returns <i>0</i> when an error occured.<br>
 */
gulong vfs_stats_get_nb_files ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_blocks_size
 * @abstract	Gets blocks size of the virtual file system stats.
 * @discussion	This function gets blocks size of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to get blocks size
 * @result	The blocks size
 *		Returns <i>0</i> when an error occured.<br>
 */
glong vfs_stats_get_blocks_size ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_blocks
 * @abstract	Gets total number blocks of the virtual file system stats.
 * @discussion	This function gets total number blocks of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to get total number blocks
 * @result	Total number blocks
 *		Returns <i>0</i> when an error occured.<br>
 */
gulong vfs_stats_get_blocks ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_blocks_free
 * @abstract	Gets free blocks number of the virtual file system stats.
 * @discussion	This function gets free blocks number of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to get free blocks number
 * @result	Free number blocks
 *		Returns <i>0</i> when an error occured.<br>
 */
gulong vfs_stats_get_blocks_free ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_total_capacity
 * @abstract	Gets total capacity of the virtual file system stats.
 * @discussion	This function gets the total capacity of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to get total capacity
 * @result	Total capacity
 *		Returns <i>-1</i> when an error occured.<br>
 */
guint64 vfs_stats_get_total_capacity ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_total_free_space
 * @abstract	Gets free space of the virtual file system stats.
 * @discussion	This function gets the free space of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to get free space
 * @result	Free space
 *		Returns <i>-1</i> when an error occured.<br>
 */
guint64 vfs_stats_get_total_free_space ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_get_total_used_space
 * @abstract	Gets total used space of the virtual file system stats.
 * @discussion	This function gets the total used space of the virtual file system stats.<br>
 * @param	p	the virtual file system stats to get total used space
 * @result	Total used space
 *		Returns <i>-1</i> when an error occured.<br>
 */
guint64 vfs_stats_get_total_used_space ( struct vfs_stats *p);


/*!
 * @function	vfs_stats_free
 * @abstract	Frees datas structure.
 * @discussion	This function frees the virtual file system stats datas structure.<br>
 * @param	p	the virtual file system stats to free
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gboolean vfs_stats_free ( struct vfs_stats *p);

#endif
