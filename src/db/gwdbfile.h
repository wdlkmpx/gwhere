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
 * @header		gwdbfile.h
 * 				GWhere<br />
 * 				Copyright (C) 2000  Sébastien LECACHEUR<br /><br />
 * 				This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br /><br />
 * 				This component was developed for the GWhere project.<br />
 * 				It's an object for file representation. His structure gets many informations as name, size, owner, ...<br /><br />
 * 				Category field is collaborative. All other fields are agregated.
 * @abstract	This is the file information data structure.
 * @author		Sébastien LECACHEUR <zero@gwhere.org>
 * @version		1.0 2004/06/07
 * @see			glib.h
 * @see			gwsupport.h
 * @see			gwdbcategory.h
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK+ Web Site <http://www.gtk.org>
 * @ref			gwdbfile.c
 * @author		Author <zero@gwhere.org>
 */


#ifndef GW_DATA_DB_FILE_H
#define GW_DATA_DB_FILE_H


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "gwdbcategory.h"


typedef gpointer GWDBFilePK;


typedef struct gw_db_file_s GWDBFile;


GWDBFile * gw_db_file_new ( void);
gint gw_db_file_set_ref ( GWDBFile *file, GWDBFilePK ref);
gint gw_db_file_set_name ( GWDBFile *file, gchar *name);
gint gw_db_file_set_rights ( GWDBFile *file, mode_t rights);
gint gw_db_file_set_rights_from_gchar ( GWDBFile *file, gchar *rights);
//TODO gint gw_db_file_set_is_directory ( GWDBFile *file, gboolean is_directory);
gint gw_db_file_set_owner ( GWDBFile *file, gchar *owner);
gint gw_db_file_set_group ( GWDBFile *file, gchar *group);
gint gw_db_file_set_size ( GWDBFile *file, guint64 size);
gint gw_db_file_set_inode ( GWDBFile *file, glong inode);
gint gw_db_file_set_cdate ( GWDBFile *file, gulong cdate);
gint gw_db_file_set_adate ( GWDBFile *file, gulong adate);
gint gw_db_file_set_mdate ( GWDBFile *file, gulong mdate);
gint gw_db_file_set_category ( GWDBFile *file, GWDBCategoryPK category);
gint gw_db_file_set_description ( GWDBFile *file, gchar *description);
GWDBFilePK gw_db_file_get_ref ( GWDBFile *file);
gchar * gw_db_file_get_name ( GWDBFile *file);
gboolean gw_db_file_is_directory ( GWDBFile *file);
gboolean gw_db_file_is_real_directory ( GWDBFile *file);
gboolean gw_db_file_is_real_file ( GWDBFile *file);
mode_t gw_db_file_get_rights ( GWDBFile *file);
gchar * gw_db_file_get_rights_to_gchar ( GWDBFile *file);
gchar * gw_db_file_get_owner ( GWDBFile *file);
gchar * gw_db_file_get_group ( GWDBFile *file);
guint64 gw_db_file_get_size ( GWDBFile *file);
glong gw_db_file_get_inode ( GWDBFile *file);
gulong gw_db_file_get_cdate ( GWDBFile *file);
gulong gw_db_file_get_adate ( GWDBFile *file);
gulong gw_db_file_get_mdate ( GWDBFile *file);
GWDBCategoryPK gw_db_file_get_category ( GWDBFile *file);
gchar * gw_db_file_get_description ( GWDBFile *file);
GWDBFile * gw_db_file_dup ( GWDBFile *file, GWDBFile **dup);
gint gw_db_file_free ( GWDBFile *file);
gboolean gw_db_file_equals ( GWDBFile *file, GWDBFile *to);


#endif
