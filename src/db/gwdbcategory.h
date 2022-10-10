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


/*!
 * @header		gwdbcategory.h
 * 				GWhere<br />
 * 				Copyright (C) 2000  Sébastien LECACHEUR<br /><br />
 * 				This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br /><br />
 * 				This component was developed for the GWhere project.<br />
 * 				It's an object for category representation. His structure gets many informations as file name, description, ...<br /><br />
 * @abstract	This is the category data structure.
 * @author		Sébastien LECACHEUR <zero@gwhere.org>
 * @version		1.0 2004/06/07
 * @see			gwsupport.h
 * @see			glib.h
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK+ Web Site <http://www.gtk.org>
 * @ref			gwdbcategory.c
 * @author		Author <zero@gwhere.org>
 */


#ifndef GW_DATA_DB_CATEGORY_H
#define GW_DATA_DB_CATEGORY_H


#include <glib.h>


typedef gpointer GWDBCategoryPK;


/*!
 * @typedef		GWDBCategory
 * @abstract	The used category structure
 * @discussion	GWDBCategory data is an opaque data structure containing information about a category.
 * @struct		gw_db_category_s
 */
typedef struct gw_db_category_s GWDBCategory;


/*!
 * @function	gw_db_category_new
 * @abstract	Creates a new category.
 * @discussion	This function creates a new category. It's an allocation function.
 * @result		a pointer to the category structure.<br />
 *				Returns <i>NULL</i> when an error occured.<br />
 */
GWDBCategory * gw_db_category_new ( void);


/*!
 * @function	gw_db_category_dup
 * @abstract	Duplicates a category.
 * @discussion	This function duplicated an existing category. It's an allocation function.
 * @param		category		the category to duplicate
 * @param		dup				the pointer reference to duplicate the category. If it is
 * 								<i>NULL</i> allocates a new category data structure.
 * @result		a pointer to duplicated category structure.<br />
 *				Returns <i>NULL</i> when an error occured.<br />
 */
GWDBCategory * gw_db_category_dup ( GWDBCategory *category, GWDBCategory **dup);


/*!
 * @function	gw_db_category_set_ref
 * @abstract	Sets the internal category's reference.
 * @discussion	This function sets the internal category's reference. This reference must be unique
 * 				and must not be modified by client application.
 * @param		category		the category to set the reference
 * @param		ref				the reference pointer
 * @result		an error code.<br />
 * 				Returns <i>0</i> when it's done.<br />
 * 				Returns <i>-1</i> when an error occured.<br />
 */
gint gw_db_category_set_ref ( GWDBCategory *category, GWDBCategoryPK ref);


/*!
 * @function	gw_db_category_set_index
 * @abstract	Sets the category's index.
 * @discussion	This function sets the category's index. This reference must be unique.
 * @param		category		the category to set the reference
 * @param		index			the index number
 * @result		an error code.<br />
 * 				Returns <i>0</i> when it's done.<br />
 * 				Returns <i>-1</i> when an error occured.<br />
 */
gint gw_db_category_set_index ( GWDBCategory *category, gint index);


/*!
 * @function	gw_db_category_set_name
 * @abstract	Sets the category's name.
 * @discussion	This function sets the category's name.<br>
 * 				<b>Warning :</b>The name may be <i>NULL</i>. It's dangerous!!
 * @param		category		the category to set the name
 * @param		name			the name
 * @result		an error code.<br />
 * 				Returns <i>0</i> when it's done.<br />
 * 				Returns <i>-1</i> when an error occured.<br />
 */
gint gw_db_category_set_name ( GWDBCategory *category, gchar *name);


/*!
 * @function	gw_db_category_set_description
 * @abstract	Sets the category's description.
 * @discussion	This function sets the category's description.<br>
 * @param		category		the category to set the description
 * @param		description		the description
 * @result		an error code.<br />
 * 				Returns <i>0</i> when it's done.<br />
 * 				Returns <i>-1</i> when an error occured.<br />
 */
gint gw_db_category_set_description ( GWDBCategory *category, gchar *description);


/*!
 * @function	gw_db_category_set_nb_disks
 * @abstract	Sets the category's number of disk.
 * @discussion	This function sets the number of disk which use this category.
 * @param		category		the category to set the number of disk
 * @param		nb				the number of disks
 * @result		an error code.<br />
 * 				Returns <i>0</i> when it's done.<br />
 * 				Returns <i>-1</i> when an error occured.<br />
 */
gint gw_db_category_set_nb_disks ( GWDBCategory *category, gulong nb);


/*!
 * @function	gw_db_category_set_nb_files
 * @abstract	Sets the category's number of files.
 * @discussion	This function sets the number of files which use this category.
 * @param		category		the category to set the number of files
 * @param		nb				the number of files
 * @result		an error code.<br />
 * 				Returns <i>0</i> when it's done.<br />
 * 				Returns <i>-1</i> when an error occured.<br />
 */
gint gw_db_category_set_nb_files ( GWDBCategory *category, gulong nb);


/*!
 * @function	gw_db_category_get_ref
 * @abstract	Gets the category's internal reference.
 * @discussion	This function gets the category's internal reference.
 * @param		category		the category to get internal reference
 * @result		the category internal reference.<br />
 * 				Returns <i>NULL</i> when an error occured.<br />
 */
GWDBCategoryPK gw_db_category_get_ref ( GWDBCategory *category);


/*!
 * @function	gw_db_category_get_index
 * @abstract	Gets the category's index.
 * @discussion	This function gets the category's index.
 * @param		category		the category to get index
 * @result		the category index.<br />
 * 				Returns <i>-1</i> when an error occured.<br />
 */
gint gw_db_category_get_index ( GWDBCategory *p);


/*!
 * @function	gw_db_category_get_name
 * @abstract	Gets the category's name.
 * @discussion	This function gets the category's name.
 * @param		category		the category to get name
 * @result		the name.<br />
 * 				Returns <i>NULL</i> when an error occured.<br />
 */
gchar * gw_db_category_get_name ( GWDBCategory *category);


/*!
 * @function	gw_db_category_get_description
 * @abstract	Gets the category's description.
 * @discussion	This function gets the category's description.
 * @param		category		the category to get description
 * @result		the description.<br />
 * 				Returns <i>NULL</i> when an error occured.<br />
 */
gchar * gw_db_category_get_description ( GWDBCategory *category);


/*!
 * @function	gw_db_category_get_nb_disks
 * @abstract	Gets the category's number of disks.
 * @discussion	This function gets the number of disks which use this category.
 * @param		category		the category to get number of disks
 * @result		the number of disks.<br />
 * 				Returns <i>0</i> when an error occured.<br />
 */
gulong gw_db_category_get_nb_disks ( GWDBCategory *category);


/*!
 * @function	gw_db_category_get_nb_files
 * @abstract	Gets the category's number of files.
 * @discussion	This function gets the number of files which use this category.
 * @param		category		the category to get number of files
 * @result		the number of files.<br />
 * 				Returns <i>0</i> when an error occured.<br />
 */
gulong gw_db_category_get_nb_files ( GWDBCategory *category);


/*!
 * @function	gw_db_category_add_disk
 * @abstract	Adds a disk to the category
 * @discussion	This function adds a disk that use this category. This function
 * 				increments the category's number of disks.
 * @param		category		the category to add a disk
 * @result		the number of disks.<br />
 * 				Returns <i>0</i> when an error occured.<br />
 */
gulong gw_db_category_add_disk ( GWDBCategory *category);


/*!
 * @function	gw_db_category_add_file
 * @abstract	Adds a file to the category
 * @discussion	This function adds a file that use this category. This function
 * 				increments the category's number of files.
 * @param		category		the category to add a file
 * @result		the number of files.<br />
 * 				Returns <i>0</i> when an error occured.<br />
 */
gulong gw_db_category_add_file ( GWDBCategory *category);


/*!
 * @function	gw_db_category_remove_disk
 * @abstract	Removes a disk to the category
 * @discussion	This function removes a disk that use this category. This function
 * 				decriment the category's number of disks.
 * @param		category		the category to remove a disk
 * @result		the number of disks.<br />
 * 				Returns <i>0</i> when an error occured.<br />
 */
gulong gw_db_category_remove_disk ( GWDBCategory *category);


/*!
 * @function	gw_db_category_remove_file
 * @abstract	Removes a file to the category
 * @discussion	This function removes a file that use this category. This function
 * 				decriment the category's number of files.
 * @param		category		the category to remove a file
 * @result		the number of files.<br />
 * 				Returns <i>0</i> when an error occured.<br />
 */
gulong gw_db_category_remove_file ( GWDBCategory *category);


/*!
 * @function	gw_db_category_can_removed
 * @abstract	Gets if the category can be removed.
 * @discussion	This function gets if the category can be removed. The category
 * 				can be removed if nothing use this category.
 * @param		category		the category to know if it can be removed
 * @result		returns <i>TRUE</i> if it can be removed otherwize returns <i>FALSE</i>.<br />
 * 				Returns <i>FALSE</i> when an error occured.<br />
 */
gboolean gw_db_category_can_removed ( GWDBCategory *category);


GWDBCategory * gw_db_category_dup ( GWDBCategory *category, GWDBCategory **dup);


/*!
 * @function	gw_db_category_free
 * @abstract	Frees datas structure.
 * @discussion	This function frees the category's datas.
 * @param		category		the category to free
 * @result		an error code.<br />
 * 				Returns <i>0</i> when it's done.<br />
 * 				Returns <i>-1</i> when an error occured.<br />
 */
gint gw_db_category_free ( GWDBCategory *category);


gboolean gw_db_category_equals ( GWDBCategory *category, GWDBCategory *to);


#endif
