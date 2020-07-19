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
 * @header	gwsearchiteminfo.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br>
 *		It's an object for search item representation. His structure gets many informations as name, size, owner, ...<br><br>
 *		Category field is collaborative. All other fields are agregated.
 * @abstract	This is the item resultn data structure.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		glib.h
 * @see		gwsupport.h
 * @see		gwcategory.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwsearchiteminfo.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_DATA_SEARCH_ITEM_INFO_H
#define GW_DATA_SEARCH_INFO_H


#define SEARCH_ITEM_TYPE_NONE 0
#define SEARCH_ITEM_TYPE_CATALOG 1
#define SEARCH_ITEM_TYPE_DISK 2
#define SEARCH_ITEM_TYPE_FOLDER 3
#define SEARCH_ITEM_TYPE_FILE 4

#include <glib.h>
#include "db/gwdb.h"


/*!
 * @struct	search_item_info
 * @abstract	Search item information data structure
 * @discussion	Search item information is an opaque data structure containing information about search item properties and informations.
 */
struct search_item_info;


/*!
 * @function	search_item_info_new
 * @abstract	Creates a new search item information.
 * @discussion	This function creates a new search item information. It's an allocation function.
 * @result	a pointer to the search item information structure.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
struct search_item_info * search_item_info_new ( void);


/*!
 * @function	search_item_info_set_type
 * @abstract	Sets the search item type.
 * @discussion	This function sets the type of the search item
 * @param	p	the search item information to set the name
 * @param	type	the type
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint search_item_info_set_type ( struct search_item_info *p, gint type);


/*!
 * @function	search_item_info_set_name
 * @abstract	Sets the search item name.
 * @discussion	This function sets the name of the search item
 * @param	p	the search item information to set the name
 * @param	name	the name
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint search_item_info_set_name ( struct search_item_info *p, gchar *name);


/*!
 * @function	search_item_info_set_disk
 * @abstract	Sets the search item disk.
 * @discussion	This function sets the disk of the search item
 * @param	p	the search item information to set the disk
 * @param	disk	the disk
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint search_item_info_set_disk ( struct search_item_info *p, gchar *disk);


/*!
 * @function	search_item_info_set_path
 * @abstract	Sets the search item path.
 * @discussion	This function sets the path of the search item
 * @param	p	the search item information to set the path
 * @param	path	the path
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint search_item_info_set_path ( struct search_item_info *p, gchar *path);


/*!
 * @function	search_item_info_set_size
 * @abstract	Sets the search item size.
 * @discussion	This function sets the search item information size.<br>
 * @param	p	the search item information to set size
 * @param	size	the size
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint search_item_info_set_size ( struct search_item_info *p, guint64 size);


/*!
 * @function	search_item_info_set_date
 * @abstract	Sets the search item date.
 * @discussion	This function sets the search item information date.<br>
 * @param	p	the search item information to set date
 * @param	cdate	the creation date
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint search_item_info_set_date ( struct search_item_info *p, gulong date);


/*!
 * @function	search_item_info_set_category
 * @abstract	Sets the search item category.
 * @discussion	This function sets the search item information category. The category is <i>struct category</i><br>
 * @param	p	the information to set category
 * @param	category	the category
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint search_item_info_set_category ( struct search_item_info *p, GWDBCategory *category);


/*!
 * @function	search_item_info_set_description
 * @abstract	Sets the search item description.
 * @discussion	This function sets the search item information description.<br>
 * @param	p	the search item information to set description
 * @param	description	the description
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint search_item_info_set_description ( struct search_item_info *p, gchar *description);


/*!
 * @function	search_item_info_get_type
 * @abstract	Gets the search item type.
 * @discussion	This function gets the search item information type.<br>
 * @param	p	the search item information to get type
 * @result	The name.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gint search_item_info_get_type ( struct search_item_info *p);


/*!
 * @function	search_item_info_get_name
 * @abstract	Gets the search item name.
 * @discussion	This function gets the search item information name.<br>
 * @param	p	the search item information to get name
 * @result	The name.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * search_item_info_get_name ( struct search_item_info *p);


/*!
 * @function	search_item_info_get_disk
 * @abstract	Gets the search item disk.
 * @discussion	This function gets the search item information disk.<br>
 * @param	p	the search item information to get disk
 * @result	The disk.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * search_item_info_get_disk ( struct search_item_info *p);


/*!
 * @function	search_item_info_get_path
 * @abstract	Gets the search item path.
 * @discussion	This function gets the search item information path.<br>
 * @param	p	the search item information to get path
 * @result	The path.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * search_item_info_get_path ( struct search_item_info *p);


/*!
 * @function	search_item_info_get_size
 * @abstract	Gets the search item size.
 * @discussion	This functions gets the search item information size.<br>
 * @param	p	the search item information to get size
 * @result	The size.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
guint64 search_item_info_get_size ( struct search_item_info *p);


/*!
 * @function	search_item_info_get_date
 * @abstract	Gets the search item date.
 * @discussion	This function gets the search item information date.<br>
 * @param	p	the search item information to get date
 * @result	The date.<br>
 *		Returns <i>0</i> when an error occured.<br>
 */
gulong search_item_info_get_date ( struct search_item_info *p);


/*!
 * @function	search_item_info_get_category
 * @abstract	Gets the search item category.
 * @discussion	This function gets the search item information category. The category is the category datas structure.<br>
 * @param	p	the search item information to get category
 * @result	The category.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GWDBCategory * search_item_info_get_category ( struct search_item_info *p);


/*!
 * @function	search_item_info_get_category_name
 * @abstract	Gets the search item category name.
 * @discussion	This function gets the search item category name.<br>
 * @param	p	the search item information to get category name
 * @result	The category name.<br>
 *		Returns <i>""</i> when there are not category.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * search_item_info_get_category_name ( struct search_item_info *p);


/*!
 * @function	search_item_info_get_category_index
 * @abstract	Gets the search item category index.
 * @discussion	This function gets the search item information category index.<br>
 * @param	p	the search item information to get category index
 * @result	The category index.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint search_item_info_get_category_index ( struct search_item_info *p);


/*!
 * @function	search_item_info_get_description
 * @abstract	Gets the search item description.
 * @discussion	This function gets the search item information description.<br>
 * @param	p	the search item information to get description
 * @result	The description.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * search_item_info_get_description ( struct search_item_info *p);


/*!
 * @function	search_item_info_free
 * @abstract	Frees datas structure.
 * @discussion	This function frees the search item information datas structure.<br>
 *		Doesn't free Category because it's collaborative.<br>
 * @param	p	the search item information to free
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint search_item_info_free ( struct search_item_info *p);


#endif
