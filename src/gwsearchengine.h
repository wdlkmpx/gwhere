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
 * @header	gwsearchengine.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a component to manage GWhere application.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 2003/02/10
 * @see		gwsupport.h
 * @see		data/gwenginequicksearch.h
 * @see		data/gwuserquicksearch.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwsearchengine.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_SEARCH_ENGINE_H
#define GW_SEARCH_ENGINE_H

#include <ctype.h>
#include <regex.h> /* regcomp regexec */

#include "data/gwdata.h"

typedef struct gw_regex_s {
	regex_t r;
	gint cflags;
	size_t no_sub;
} GWRegex;

/*!
 * @function	search_engine_search_in_disk
 * @abstract	Searchs items in a disk.
 * @discussion	This function searchs items in a disk.
 * @param	w	the main window
 * @param	uqs	the user quick search to search
 * @result	the number of matched items.
 */
gulong search_engine_search_in_disk ( GtkWindow *w, struct user_quick_search *uqs);


/*!
 * @function	search_engine_search_in_dir
 * @abstract	Searchs items in a directory.
 * @discussion	This function searchs items in a directory.
 * @param	w	the main window
 * @param	eqs	the engine quick search to search
 * @result	the number of matched items.
 */
//gulong search_engine_search_in_dir ( GtkCTree *ctree, GtkCTreeNode *node, struct engine_quick_search *eqs, GWRegex *regex);
gulong search_engine_search_in_dir ( GWDBFile *folder, struct engine_quick_search *eqs, GWRegex *regex);


/*!
 * @function	search_engine_check_disk_match
 * @abstract	Checks if specified disk matched with search.
 * @discussion	This function checks if specified disk matched with search.
 * @param	disk	the disk information to check
 * @param	eqs	the search properties
 * @result	Returns <i>0</i> if the disk matches.<br>
 * 		Returns <i>-1</i> otherwise or if an error occured.
 */
//gint search_engine_check_disk_match ( struct disk_info *disk, struct engine_quick_search *eqs, GWRegex *regex);
gint search_engine_check_disk_match ( GWDBDisk *disk, GWDBCategory *category, struct engine_quick_search *eqs, GWRegex *regex);


/*!
 * @function	search_engine_check_file_match
 * @abstract	Checks if specified file matched with search.
 * @discussion	This function checks if specified file matched with search.
 * @param	file	the file information to check
 * @param	eqs	the search properties
 * @result	Returns <i>0</i> if the file matches.<br>
 * 		Returns <i>-1</i> otherwise or if an error occured.
 */
//gint search_engine_check_file_match ( struct file_info *file, struct engine_quick_search *eqs, GWRegex *regex);
gint search_engine_check_file_match ( GWDBFile *file, GWDBCategory *category, struct engine_quick_search *eqs, GWRegex *regex);


/*!
 * @function	search_engine_add_item
 * @abstract	Adds a file in the search result list.
 * @discussion	This function adds a file in the search result list.
 * @param	clist	the search result list
 * @param	ctree	the tree where is the file to add
 * @param	node	the node where is the file to add
 * @param	file	the file information to add
 * @result	an error code.<br>
 * 		Returns <i>-1</i> if an error occured.
 */
//gint search_engine_add_item ( GtkCList *clist, GtkCTree *ctree, GtkCTreeNode *node, struct file_info *file_info);
gint search_engine_add_item ( GtkCList *clist, GWDBFile *file, GWDBCategory *category);


/*!
 * @function	search_engine_add_disk
 * @abstract	Adds a disk in the search result list.
 * @discussion	This function adds a disk in the search result list.
 * @param	clist	the search result list
 * @param	ctree	the tree where is the file to add
 * @param	node	the node where is the file to add
 * @param	disk	the disk information to add
 * @result	an error code.<br>
 * 		Returns <i>-1</i> if an error occured.
 */
//gint search_engine_add_disk ( GtkCList *clist, GtkCTree *ctree, GtkCTreeNode *node, struct disk_info *disk_info);
gint search_engine_add_disk ( GtkCList *clist, GWDBDisk *disk, GWDBCategory *category);


#endif
