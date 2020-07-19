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
 * @header	gwscandiskinfo.h
 * @discussion	GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is the scan disk information data structure
 * @version	1.0 2002/01/17
 * @author	Author <zero@gwhere.org>
 * @see		glib.h
 * @see		gwsupport.h
 * @see		gwvirtualfilesystemstats.h
 * @see		gwcategory.h
 * @ref		gwscandiskinfo.c
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK Web Site <http://www.gtk.org>
 * @author	S&eacute;bastien LECACHEUR <zero@gwhere.org>
 */


#ifndef GW_DATA_SCAN_DISK_INFO_H
#define GW_DATA_SCAN_DISK_INFO_H


#include <glib.h>
#include "gwvirtualfilesystemstats.h"
#include "db/gwdb.h"


/*!
 * @struct	scan_disk_info
 * @abstract	Scan disk information data structure
 * @discussion	Scan disk information is an opaque data structure containing information about a scan process.
 */
struct scan_disk_info;


/*!
 * @typedef	func_descr_t
 *		Specifies the type of the value f function passed to scan_disk_info_set_scan_disk_get_file_description().
 *		The function get the description of a file.
 * @abstract	Functions specification
 * @param	file_name		file name to get description
 */
typedef gchar * (*func_descr_t)( gchar *file_name);


/*!
 * @typedef	func_statment_t
 *		Specifies the type of the value f function passed to scan_disk_info_set_scan_disk_set_current_statment().
 *		The function update the statmant of the progression. It's usefull in order to update progress bar for example.
 * @abstract	Functions specification
 * @param	object	the object to update
 * @param	value	the value to increment for statment progress.
 */
typedef gint (*func_statment_t)( gpointer object, gfloat value);


/*!
 * @function	scan_disk_info_new
 * @abstract	Creates a new scan disk information
 * @discussion	This function creates a new scan disk information. It's an allocation function.<br>
 *		VFSStats and Categories are collaboratived and all other data agregated.
 * @result	a pointer to the scan disk information structure.
 *		Returns <i>NULL</i> when an error occured.
 */
struct scan_disk_info * scan_disk_info_new ( void);


/*!
 * @function	scan_disk_info_set_vfs
 * @abstract	Sets the VFSStats to scan
 * @discussion	This function sets the VFSStats to scan.
 * @param	p	the scan disk information to set VFSStats
 * @param	vfs	the VFSStats
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_vfs ( struct scan_disk_info *p, struct vfs_stats *vfs);


/*!
 * @function	scan_disk_info_set_disk_name
 * @abstract	Sets the disk name for catalog
 * @discussion	This function sets the disk name for catalog.
 * @param	p	the scan disk information to set disk name
 * @param	name	the disk name
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_disk_name ( struct scan_disk_info *p, gchar *name);


/*!
 * @function	scan_disk_info_set_disk_num_archive
 * @abstract	Sets the disk number archive for catalog
 * @discussion	This function sets the disk number archive for catalog.
 * @param	p	the scan disk information to set number archive
 * @param	num	the disk number archive
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_disk_num_archive ( struct scan_disk_info *p, gint num);


/*!
 * @function	scan_disk_info_set_disk_category
 * @abstract	Sets the category disk for catalog
 * @discussion	This function sets the category disk for catalog.
 * @param	p	the scan disk information to set category
 * @param	category	the category
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_disk_category_ref ( struct scan_disk_info *p, GWDBCategoryPK ref);


/*!
 * @function	scan_disk_info_set_explore_tree_structure
 * @abstract	Sets if the scan disk had to explore tree structure
 * @discussion	This function sets if the scan disk had to explore tree structure.
 * @param	p	the scan disk information to set explore tree structure status
 * @param	tree_structure	<i>TRUE</i> to explore files archive or <i>FALSE</i> to no explore them
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_explore_tree_structure ( struct scan_disk_info *p, gboolean tree_structure);


/*!
 * @function	scan_disk_info_set_explore_archive
 * @abstract	Sets if the scan disk had to explore archive files
 * @discussion	This function sets if the scan disk had to explore archive files.
 * @param	p	the scan disk information to set explore archive files status
 * @param	explore_archive	<i>TRUE</i> to explore files archive or <i>FALSE</i> to no explore them
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_explore_archive ( struct scan_disk_info *p, gboolean explore_archive);


/*!
 * @function	scan_disk_info_set_make_description
 * @abstract	Sets if the scan disk had to make file description
 * @discussion	This function sets if the scan disk had to make file description.
 * @param	p	the scan disk information to set make file description status
 * @param	make_description	<i>TRUE</i> to make description or <i>FALSE</i> to not make description
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_make_description ( struct scan_disk_info *p, gboolean make_description);


/*!
 * @function	scan_disk_info_set_category_recursive
 * @abstract	Sets if the scan disk had to set recursively category
 * @discussion	This function sets if the scan disk had to set recursively category.
 * @param	p	the scan disk information to set recursively category status
 * @param	category_recursive	<i>TRUE</i> to set category recursively or <i>FALSE</i> to not set them
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_category_recursive ( struct scan_disk_info *p, gboolean category_recursive);


/*!
 * @function	scan_disk_info_set_stop
 * @abstract	Sets if the scan disk must stop
 * @discussion	This function sets if the scan disk had to stop.
 * @param	p	the scan disk information to set stop status
 * @param	stop	<i>TRUE</i> to stop scan disk or <i>FALSE</i> to continue
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_stop ( struct scan_disk_info *p, gboolean stop);


/*!
 * @function	scan_disk_info_set_error_msg
 * @abstract	Sets the error message
 * @discussion	This function sets the error message. The message indicate why
 *		the scan disk failed.
 * @param	p	the scan disk information to set error message
 * @param	error_ms	the error message
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_error_msg ( struct scan_disk_info *p, gchar *error_msg);


/*!
 * @function	scan_disk_info_set_statment_controler
 * @abstract	Sets the statment controler
 * @discussion	This function sets the statment controler. This controler is the first parameter of
 *		func_stament_t function.
 * @param	p	the scan disk information to set statment controler
 * @param	statment_controler		the statment controler
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_statment_controler ( struct scan_disk_info *p, gpointer statment_controler);


/*!
 * @function	scan_disk_info_set_scan_disk_get_file_description
 * @abstract	Sets the function to get file description
 * @discussion	This function sets the function to get file description. This
 *		is active only if "make description" is activated.
 * @param	p	the scan disk information to set make description function
 * @param	f	the function
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_scan_disk_get_file_description ( struct scan_disk_info *p, func_descr_t f);


/*!
 * @function	scan_disk_info_set_scan_disk_set_current_statment
 * @abstract	Sets the function to set current process statment
 * @discussion	This function sets the function to set current process statment.
 * @param	p	the scan disk information to set current process statment status
 * @param	f	the function
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_set_scan_disk_set_current_statment ( struct scan_disk_info *p, func_statment_t f);


/*!
 * @function	scan_disk_info_get_vfs
 * @abstract	Gets the VFSStats to scan
 * @discussion	This function gets the VFSStats to scan.
 * @param	p	the scan disk information to get VFSStats
 * @result	the VFSStats.
 *		Returns <i>NULL</i> when an error occured.
 */
struct vfs_stats * scan_disk_info_get_vfs ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_disk_name
 * @abstract	Gets the disk name for catalog
 * @discussion	This function gets the disk name for catalog.
 * @param	p	the scan disk information to get disk name
 * @result	the disk name
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * scan_disk_info_get_disk_name ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_disk_num_archive
 * @abstract	Gets the disk number archive for catalog
 * @discussion	This function gets the disk number archive for catalog.
 * @param	p	the scan disk information to get number archive
 * @result	the disk number archive
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_get_disk_num_archive ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_disk_category
 * @abstract	Gets the disk category for catalog
 * @discussion	This function gets the disk category for catalog.
 * @param	p	the scan disk information to get
 * @result	the category
 *		Returns <i>NULL</i> when an error occured.
 */
GWDBCategoryPK scan_disk_info_get_disk_category_ref ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_explore_tree_structure
 * @abstract	Gets if the scan disk had to explore tree structure
 * @discussion	This function gets if the scan disk had to explore tree structure.
 * @param	p	the scan disk information to get explore tree structure status
 * @result	<i>TRUE</i> if must explore tree structure or <i>FALSE</i> if not explore them
 */
gboolean scan_disk_info_get_explore_tree_structure ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_explore_archive
 * @abstract	Gets if the scan disk had to explore archive files
 * @discussion	This function gets if the scan disk had to explore archives files.
 * @param	p	the scan disk information to get explore archive status
 * @result	<i>TRUE</i> if must explore files archive or <i>FALSE</i> if not explore them
 */
gboolean scan_disk_info_get_explore_archive ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_make_description
 * @abstract	Gets if the scan disk had to make file description
 * @discussion	This function gets if the scan disk had to make file description. To make
 *		file description the "get file description" must be set.
 * @param	p	the scan disk information to get make description status
 * @result	<i>TRUE</i> if must to make description or <i>FALSE</i> to not make description
 */
gboolean scan_disk_info_get_make_description ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_category_recursive
 * @abstract	Gets if the scan disk had to set category recursively
 * @discussion	This function gets of the scan disk had to set category recursively to
 *		the catalog. If the category is applicated recursively all sub item of
 *		catalog will have this category (folder, subfolder, files).
 * @param	p	the scan disk information to get category recursively status
 * @result	<i>TRUE</i> if must to set category recursively or <i>FALSE</i> to not set them
 */
gboolean scan_disk_info_get_category_recursive ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_stop
 * @abstract	Gets if the scan disk had to stop
 * @discussion	This function gets if the scan disk had to stop process. This property
 *		is usefull to cancel a scan disk (with an external process). Use this
 *		methode to check when scan disk must stop.
 * @param	p	the scan disk information to get stop status
 * @result	<i>TRUE</i> to stop scan disk or <i>FALSE</i> to continue
 */
gboolean scan_disk_info_get_stop ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_error_msg
 * @abstract	Gets the error message
 * @discussion	This function gets the error message. The error message may be put
 *		when a error occured during scan disk or when the process is stoped.
 *		The error message may be use in order to send a report or anything.
 * @param	p	the scan disk information to get error message
 * @result	the error message or <i>NULL</i> if there are no message.
 *		Return <i>NULL</i> when an error occured.
 */
gchar * scan_disk_info_get_error_msg ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_statment_controler
 * @abstract	Gets the statment controler
 * @discussion	This function gets the statment controler. This controler must use with
 *		func_statment_t function.
 * @param	p	the scan disk information to get statment controler
 * @result	the statment controler or <i>NULL</i> if there are no statment controler.
 *		Return <i>NULL</i> when an error occured.
 */
gpointer scan_disk_info_get_statment_controler ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_scan_disk_get_file_description
 * @abstract	Gets the function to get file description
 * @discussion	This function get the function to get file description. This function
 *		must be use only if the "make description" status is set.
 * @param	p	the scan disk information to get function
 * @result	the function or <i>NULL</i> if there are no function.
 *		Returns <i>NULL</i> when an error occured.
 */
func_descr_t scan_disk_info_get_scan_disk_get_file_description ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_get_scan_disk_set_current_statment
 * @abstract	Gets the function to set current process statment
 * @discussion	This function gets the function to set current process statment
 * @param	p	the scan disk information to get function
 * @result	the function or <i>NULL</i> if there are no function.
 *		Returns <i>NULL</i> when an error occured.
 */
func_statment_t scan_disk_info_get_scan_disk_set_current_statment ( struct scan_disk_info *p);


/*!
 * @function	scan_disk_info_free
 * @abstract	Frees data structure
 * @discussion	This function frees the scan disk data structure. Doesn't
 *		free VFSStats, Category, Statment Controler because they're collaboratives.
 * @param	p	the scan disk information to free
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint scan_disk_info_free ( struct scan_disk_info *p);


#endif
