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


#include "gwsupport.h"
#include "gwhelper.h"

#include <gtk/gtk.h>

#include <stdlib.h> /* strtol */
#include <string.h> /* strlen strncmp */

#include "data/gwdata.h"
#include "res/gwres.h"
#include "tools/gwtools.h"

#include "gwapplicationmanager.h"
#include "gwguimanager.h"


gint gw_catalog_get_total_disks ( GtkCTree *ctree, GtkCTreeNode *node)
{
	GtkCTreeNode *child = NULL;
	gint n = 0;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	child = GTK_CTREE_ROW ( node)->children;
	while ( child != NULL )
	{
		n++;
		child = GTK_CTREE_ROW ( child)->sibling;
	}

	return n;
}


gint gw_catalog_get_total_folders ( GtkCTree *ctree, GtkCTreeNode *node)
{
	GtkCTreeNode *child = NULL;
	int n = 0;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	child = GTK_CTREE_ROW( node)->children;
	while ( child != NULL )
	{
		/* Counts the number of files for each disk. */
		n = n + gw_disk_get_total_folders ( ctree, child);
		child = GTK_CTREE_ROW ( child)->sibling;
	}

	return n;
}


#ifdef __DEPRECATED__
gint gw_catalog_get_num_disk_with_type ( GtkCTree *ctree, GtkCTreeNode *node, gchar *type)
{
	GtkCTreeNode *child = NULL;
	struct disk_info *disk_info;
	gint n = 0;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	child = GTK_CTREE_ROW ( node)->children;
	while ( child != NULL )
	{
		if ( (disk_info = disk_data_get_info ( gtk_ctree_node_get_row_data ( ctree, child))) == NULL )
		{
			disk_info = NULL;
			child = GTK_CTREE_ROW ( child)->sibling;
			continue;
		}

		/* Checks the disk type. */
		if ( strncmp ( type, disk_info_get_type ( disk_info), strlen ( type)) == 0 )
		{
			if ( strncmp ( type, "iso9660", 7) == 0 )
			{
				n++;
			}
		}
		else { if ( strncmp ( type, disk_info_get_fsname ( disk_info), strlen ( type)) == 0 )
		{
			if ( strncmp ( type, "/dev/fd", 7) == 0 )
			{
				n++;
			}
			else { if ( strncmp ( type, "/dev/zip", 8) == 0 )
			{
				n++;
			}
			else { if ( strncmp ( type, "/dev/hd", 7) == 0 )
			{
				n++;
			}}}
		}
		else { if ( strncmp ( disk_info_get_type ( disk_info), "ntfs", 4) == 0 )
		{
			if ( strncmp ( type, "/dev/hd", 7) == 0 )
			{
				n++;
			}
		}
		else { if ( strncmp ( disk_info_get_type ( disk_info), "cdfs", 4) == 0 )
		{
			if ( strncmp ( type, "iso9660", 7) == 0 )
			{
				n++;
			}
		}
		else { if ( strncmp ( disk_info_get_dir ( disk_info), "A", 1) == 0 )
		{
			if ( strncmp ( type, "/dev/fd", 7) == 0 )
			{
				n++;
			}
		}
		else { if ( strncmp ( disk_info_get_dir ( disk_info), "B", 1) == 0 )
		{
			if ( strncmp ( type, "/dev/fd", 7) == 0 )
			{
				n++;
			}
		}
		else { if ( strncmp ( type, "Other", 5) == 0 )
		{
			n++;
			if ( strncmp ( "iso9660", disk_info_get_type ( disk_info ), 7) == 0 )
			{
				n--;
			}
			else { if ( strncmp ( disk_info_get_fsname ( disk_info), "/dev/fd", 7) == 0 )
			{
				n--;
			}
			else { if ( strncmp ( disk_info_get_fsname ( disk_info), "/dev/zip", 8) == 0 )
			{
				n--;
			}
			else { if ( strncmp ( disk_info_get_fsname ( disk_info), "/dev/hd", 7) == 0 )
			{
				n--;
			}}}}
		}}}}}}}

/*		if ( strncmp ( type, disk_info_get_type ( disk_data_get_info ( gtk_ctree_node_get_row_data ( ctree, child))), strlen ( type)) == 0 )
		{
			n++;
		}
*/
		disk_info = NULL;
		child = GTK_CTREE_ROW ( child)->sibling;
	}

	return n;
}
#endif


gint gw_disk_get_total_folders ( GtkCTree *ctree, GtkCTreeNode *node)
{
	GtkCTreeNode *child = NULL;
	int n = 0;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	child = GTK_CTREE_ROW( node)->children;
	while ( child != NULL )
	{
		n++;
		n = n + gw_disk_get_total_folders ( ctree, child);
		child = GTK_CTREE_ROW ( child)->sibling;
	}

	return n;
}


#ifdef __DEPRECATED__
gint gw_disk_get_total_files ( GtkCTree *ctree, GtkCTreeNode *node)
{
	GtkCTreeNode *child = NULL;
	int n = 0;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	/* Counts the folder's number of files. */
	n = dir_data_get_num_file ( gtk_ctree_node_get_row_data ( ctree, node));

	child = GTK_CTREE_ROW( node)->children;
	while ( child != NULL )
	{
		/* Does the same thing for each subfolder. */
		n = n + gw_disk_get_total_files ( ctree, child);
		child = GTK_CTREE_ROW ( child)->sibling;
	}

	return n;
}
#endif


GtkCTreeNode * gw_folder_get_catalog ( GtkCTree *ctree, GtkCTreeNode *node)
{
	GtkCTreeNode *parent = NULL;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	parent = GTK_CTREE_ROW ( node)->parent;
	while ( GTK_CTREE_ROW ( parent)->parent != NULL )
	{
		parent = GTK_CTREE_ROW ( parent)->parent;
	}

	return parent;
}


GtkCTreeNode * gw_folder_get_disk ( GtkCTree *ctree, GtkCTreeNode *node)
{
	GtkCTreeNode *parent = NULL;
	GtkCTreeNode *root = NULL;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	root = gw_gui_manager_main_interface_get_tree_root ( );

	if ( GTK_CTREE_ROW ( node)->parent == root)
	{
		return node;
	}

	parent = GTK_CTREE_ROW ( node)->parent;

	while ( GTK_CTREE_ROW ( GTK_CTREE_ROW ( parent)->parent)->parent != NULL )
	{
		parent = GTK_CTREE_ROW ( parent)->parent;
	}

	return parent;
}


gboolean gw_helper_db_catalog_is_open ( ) {
	gboolean result = FALSE;
	GWDBContext *context = gw_am_get_current_catalog_context ( );


	if ( context != NULL) {
		result = TRUE;
	} else {}

	return result;
}


gboolean gw_helper_db_catalog_is_open_and_modified ( ) {
	gboolean result = FALSE;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;


	if ( context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);
			gw_db_catalog_free ( catalog);
		} else {}
	} else {}

	return result;
}


gchar * gw_helper_db_catalog_get_usefull_name ( GWDBCatalog *catalog) {
	gchar *name = NULL;


	if ( catalog != NULL) {
		if ( gw_db_catalog_get_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_name ( catalog))>0) {
			name = gw_db_catalog_get_name ( catalog);
		} else {
			if ( gw_db_catalog_get_short_db_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_short_db_name ( catalog))>0) {
				name = gw_db_catalog_get_short_db_name ( catalog);
			} else {}
		}
	} else {}

	return name;
}


gchar * gw_helper_db_catalog_get_full_name ( GWDBCatalog *catalog) {
	gchar *name = NULL;


	if ( catalog != NULL) {
		if ( gw_db_catalog_get_db_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_db_name ( catalog))>0) {
			name = gw_db_catalog_get_db_name ( catalog);
		} else {
			if ( gw_db_catalog_get_short_db_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_short_db_name ( catalog))>0) {
				name = gw_db_catalog_get_short_db_name ( catalog);
			} else {
				if ( gw_db_catalog_get_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_name ( catalog))>0) {
					name = gw_db_catalog_get_name ( catalog);
				} else {
				}
			}
		}
	} else {
	}

	return name;
}


gboolean gw_helper_db_catalog_is_new ( GWDBCatalog *catalog) {
	gboolean is_new = FALSE;


	if ( catalog != NULL) {
		if ( gw_db_catalog_get_db_name ( catalog)==NULL && gw_db_catalog_get_short_db_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_short_db_name ( catalog))>0) {
			is_new = TRUE;
		} else {}
	} else {}

	return is_new;
}


GdkPixmap * gw_helper_db_disk_get_pixmap ( GWDBDisk *disk) {
	GdkPixmap *pix = NULL;


	switch ( gw_db_disk_get_type ( disk)) {
		case CDROM :		pix = PixCDRomDisk;
					break;

		case FLOPPY :		pix = PixFloppyDisk;
					break;

		case HD :		pix = PixHardDriveDisk;
					break;

		case ZIP_DRIVE :	pix = PixZipDisk;
					break;

		default :		pix = PixHardDriveDisk;
					break;
	}

	return pix;
}


GdkBitmap * gw_helper_db_disk_get_bitmap ( GWDBDisk *disk) {
	GdkBitmap *msk = NULL;


	switch ( gw_db_disk_get_type ( disk)) {
		case CDROM :		msk = MskCDRomDisk;
					break;

		case FLOPPY :		msk = MskFloppyDisk;
					break;

		case HD :		msk = MskHardDriveDisk;
					break;

		case ZIP_DRIVE :	msk = MskZipDisk;
					break;

		default :		msk = MskHardDriveDisk;
					break;
	}

	return msk;
}

GWDBDiskType gw_helper_db_disk_get_db_type ( GWDBDisk *disk) {
	gchar *type = gw_db_disk_get_fstype ( disk);
	gchar *name = gw_db_disk_get_fsname ( disk);
	GWDBDiskType dt = NONE;


	if ( strcmp ( "iso9660", type) == 0) {
		dt = CDROM;
	} else if ( strcmp ( "cdfs", type) == 0) {
		dt = CDROM;
	} else if ( strcmp ( "smb", type) == 0) {
		dt = NETWORK_DRIVE;
	} else if ( strcmp ( "/dev/hd", name) == 0) {
		dt = HD;
	} else if ( strcmp ( "/dev/fd", name) == 0) {
		dt = FLOPPY;
	} else if ( strcmp ( "/dev/zip", name) == 0) {
		dt = ZIP_DRIVE;
	} else if ( strcmp ( "\\\\.\\A:\\", name) == 0) {
		dt = FLOPPY;
	} else if ( strcmp ( "\\\\.\\B:\\", name) == 0) {
		dt = FLOPPY;
	} else if ( strcmp ( "ntfs", type) == 0) {
		dt = HD;
	} else {
	}

	return dt;
}


gint gw_helper_db_catalog_get_nb_db_disk_of_type ( GWDBContext *context, GWDBDiskType type) {
	GWCatalogPlugin *plugin = NULL;
	GWDBDisk **disks = NULL;
	gint nb = -1, i = 0;


	if ( context != NULL ) {
		if ( (plugin = ((GWCatalogPlugin*)gw_db_context_get_plugin ( context))) != NULL ) {
			nb = 0;

			if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL ) {
				for ( i = 0; disks[i]!=NULL; i++) {
					if ( gw_db_disk_get_type ( disks[i]) == type ) {
						nb++;
					}

					gw_db_disk_free ( disks[i]);
					disks[i] = NULL;
				}

				g_free ( disks);
			}
		}
	}

	return nb;
}


gboolean gw_helper_db_disk_num_is_exist ( GWDBContext *context, gint num) {
	GWCatalogPlugin *plugin = NULL;
	gboolean exist = FALSE;
	GWDBDisk **disks = NULL;
	gint i = 0;


	if ( context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
			if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL) {
				for ( i = 0; disks[i] != NULL; i++) {
					if ( !exist && gw_db_disk_get_num (disks[i]) == num) {
						exist = TRUE;
					}

					gw_db_disk_free ( disks[i]);
				}

				g_free ( disks);
			}
		}
	}

	return exist;
}


gint gw_helper_db_disk_get_max_num ( GWDBContext *context) {
	GWCatalogPlugin *plugin = NULL;
	gint max = 0;
	GWDBDisk **disks = NULL;
	gint i = 0;


	if ( context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
			if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL) {
				for ( i = 0; disks[i] != NULL; i++) {
					if ( gw_db_disk_get_num (disks[i]) > max) {
						max = gw_db_disk_get_num (disks[i]);
					}

					gw_db_disk_free ( disks[i]);
				}

				g_free ( disks);
			}
		}
	}

	return max;
}


gint gw_helper_db_disk_get_num_archive ( GWDBContext *context, gchar *num) {
	gint num_archive = 0;


	if ( context != NULL && num != NULL) {
		if ( strlen ( num) == 0 ) {
			/* If number archive no filled. */
			num_archive = gw_helper_db_disk_get_max_num ( context) + 1;
		} else if ( gw_helper_db_disk_num_is_exist ( context, strtol ( num, NULL, 10)) ) {
			/* If the filled archive number exists. */
			num_archive = gw_helper_db_disk_get_max_num ( context) + 1;
		} else {
			/* If the filled archive number is valid. */
			num_archive = strtol ( num, NULL, 10);
		}
	}

	return num_archive;
}


gboolean gw_helper_db_disk_name_is_exist ( GWDBContext *context, gchar *name) {
	GWCatalogPlugin *plugin = NULL;
	gboolean exist = FALSE;
	GWDBDisk **disks = NULL;
	gint i = 0;


	if ( context != NULL && name != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
			if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL) {
				for ( i = 0; disks[i] != NULL; i++) {
					if ( !exist && strcmp ( name, gw_db_disk_get_name (disks[i])) == 0) {
						exist = TRUE;
					}

					gw_db_disk_free ( disks[i]);
				}

				g_free ( disks);
			}
		}
	}

	return exist;
}


gchar * gw_helper_db_disk_get_name ( GWDBContext *context, gchar *name) {
	gchar *tmp_name = NULL;
	gint i = 2;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( context != NULL && name != NULL ) {
		tmp_name = g_strdup ( name);

		while ( gw_helper_db_disk_name_is_exist ( context, tmp_name) ) {
			g_free ( tmp_name);
			tmp_name = g_strdup_printf ( "%s (%d)", name, i++);
		}
	}

	return tmp_name;
}


gboolean gw_helper_db_file_name_is_exist ( GWDBContext *context, GWDBFilePK file, gchar *name) {
	GWCatalogPlugin *plugin = NULL;
	gboolean exist = FALSE;
	GWDBFile *parent = NULL, *found = NULL;
	GWDBDisk *disk = NULL;


	if ( context != NULL && name != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			if ( (parent = plugin->gw_db_file_get_parent_db_file ( context, file)) != NULL ) {
				if ( (found = plugin->gw_db_file_get_db_file_by_name ( context, gw_db_file_get_ref ( parent), name)) != NULL) {
					exist = TRUE;
					gw_db_file_free ( found);
				}

				gw_db_file_free ( parent);
			} else if ( (disk = plugin->gw_db_file_get_db_disk ( context, file)) != NULL ) {
				if ( (found = plugin->gw_db_disk_get_db_file_by_name ( context, gw_db_disk_get_ref ( disk), name)) != NULL) {
					exist = TRUE;
					gw_db_file_free ( found);
				}

				gw_db_disk_free ( disk);
			}
		}
	}

	return exist;
}


guint64 gw_helper_plugin_db_catalog_get_capacity ( GWDBContext *context) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBDisk **disks = NULL;
	guint64 capacity = 0;
	gint i = 0;


	if ( context != NULL && plugin != NULL) {
		if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL) {
			for ( i = 0; disks[i] != NULL; i++ ) {
				capacity += gw_db_disk_get_capacity ( disks[i]);
				gw_db_disk_free ( disks[i]);
			}

			g_free ( disks);
		}
	}

	return capacity;
}


guint64 gw_helper_plugin_db_catalog_get_full ( GWDBContext *context) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBDisk **disks = NULL;
	guint64 full = 0;
	gint i = 0;


	if ( context != NULL && plugin != NULL) {
		if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL) {
			for ( i = 0; disks[i] != NULL; i++ ) {
				full += gw_db_disk_get_full ( disks[i]);
				gw_db_disk_free ( disks[i]);
			}

			g_free ( disks);
		}
	}

	return full;
}


guint64 gw_helper_plugin_db_catalog_get_free ( GWDBContext *context) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBDisk **disks = NULL;
	guint64 free = 0;
	gint i = 0;


	if ( context != NULL && plugin != NULL) {
		if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL) {
			for ( i = 0; disks[i] != NULL; i++ ) {
				free += gw_db_disk_get_full ( disks[i]);
				gw_db_disk_free ( disks[i]);
			}

			g_free ( disks);
		}
	}

	return free;
}


GWDBCategory * gw_helper_plugin_db_catalog_get_db_category_by_index ( GWDBContext *context, gint index) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBCategory **categories = NULL;
	GWDBCategory *category = NULL;
	gint i = 0;


	if ( context != NULL && plugin != NULL) {
		if ( (categories = plugin->gw_db_catalog_get_db_categories ( context)) != NULL) {
			for ( i = 0; categories[i] != NULL; i++ ) {
				if ( category == NULL && gw_db_category_get_index ( categories[i]) == index ) {
					category = categories[i];
				} else {
					gw_db_category_free ( categories[i]);
				}
			}

			g_free ( categories);
		}
	}

	return category;
}


GWDBCategory * gw_helper_plugin_db_catalog_get_db_category_by_name ( GWDBContext *context, gchar *name) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBCategory **categories = NULL;
	GWDBCategory *category = NULL;
	gint i = 0;


	if ( context != NULL && plugin != NULL && name != NULL) {
		if ( (categories = plugin->gw_db_catalog_get_db_categories ( context)) != NULL) {
			for ( i = 0; categories[i] != NULL; i++ ) {
				if ( category == NULL && strcmp ( name, gw_db_category_get_name ( categories[i])) == 0 ) {
					category = categories[i];
				} else {
					gw_db_category_free ( categories[i]);
				}
			}

			g_free ( categories);
		}
	}

	return category;
}


GWDBDisk * gw_helper_plugin_db_catalog_get_db_disk_by_name ( GWDBContext *context, gchar *name) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBDisk **disks = NULL;
	GWDBDisk *disk = NULL;
	gint i = 0;


	if ( context != NULL && plugin != NULL && name != NULL) {
		if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL) {
			for ( i = 0; disks[i] != NULL; i++ ) {
				if ( disk == NULL && strcmp ( name, gw_db_disk_get_name ( disks[i])) == 0 ) {
					disk = disks[i];
				} else {
					gw_db_disk_free ( disks[i]);
				}
			}

			g_free ( disks);
		}
	}

	return disk;
}


GWDBFile * gw_helper_plugin_db_disk_get_db_file_by_name ( GWDBContext *context, GWDBDiskPK ref, gchar *name) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBFile **files = NULL;
	GWDBFile *file = NULL;
	gint i = 0;


	if ( context != NULL && plugin != NULL && name != NULL) {
		if ( (files = plugin->gw_db_disk_get_db_files ( context, ref)) != NULL) {
			for ( i = 0; files[i] != NULL; i++ ) {
				if ( file == NULL && strcmp ( name, gw_db_file_get_name ( files[i])) == 0 ) {
					file = files[i];
				} else {
					gw_db_file_free ( files[i]);
				}
			}

			g_free ( files);
		}
	}

	return file;
}


GWDBFile * gw_helper_plugin_db_file_get_db_file_by_name ( GWDBContext *context, GWDBFilePK ref, gchar *name) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBFile **files = NULL;
	GWDBFile *file = NULL;
	gint i = 0;


	if ( context != NULL && plugin != NULL && name != NULL) {
		if ( (files = plugin->gw_db_file_get_db_files ( context, ref)) != NULL) {
			for ( i = 0; files[i] != NULL; i++ ) {
				if ( file == NULL && strcmp ( name, gw_db_file_get_name ( files[i])) == 0 ) {
					file = files[i];
				} else {
					gw_db_file_free ( files[i]);
				}
			}

			g_free ( files);
		}
	}

	return file;
}


gchar * gw_helper_plugin_db_file_get_location ( GWDBContext *context, GWDBFilePK ref) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	gchar *location = NULL, *tmp = NULL;
	GWDBFile *parent = NULL;
	GWDBFilePK current = ref;


	if ( context != NULL && plugin != NULL) {
		location = g_strdup ( "/");
		while ( (parent = plugin->gw_db_file_get_parent_db_file ( context, current)) != NULL ) {
			tmp = g_strconcat ( "/", gw_db_file_get_name ( parent), location, NULL);
			g_free ( location);
			location = tmp;
			current = gw_db_file_get_ref ( parent);
			gw_db_file_free ( parent);
		}

	}

	return location;
}


gchar * gw_helper_db_file_get_cdate_to_str ( GWDBFile *file) {
	return gw_time_to_str_df ( gw_db_file_get_cdate ( file));
}


gchar * gw_helper_db_file_get_adate_to_str ( GWDBFile *file) {
	return gw_time_to_str_df ( gw_db_file_get_adate ( file));
}


gchar * gw_helper_db_file_get_mdate_to_str ( GWDBFile *file) {
	return gw_time_to_str_df ( gw_db_file_get_mdate ( file));
}


gchar * gw_helper_db_disk_get_date_to_str ( GWDBDisk *disk) {
	return gw_time_to_str_df ( gw_db_disk_get_date ( disk));
}


gchar * gw_helper_search_item_info_date_to_str ( struct search_item_info *si) {
	return gw_time_to_str_df ( search_item_info_get_date ( si));
}
