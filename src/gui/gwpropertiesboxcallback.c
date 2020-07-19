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


#include "../gwsupport.h"
#include "gwpropertiesboxcallback.h"

#include <stdlib.h> /* strtol */
#include <string.h> /* strcmp */

#include "tools/gwtools.h"

#include "gwpropertiesbox.h"
#include "gwcomboboxcategories.h"

#include "../gwpluginsmanager.h"
#include "../gwapplicationmanager.h"

#include "../gwhelper.h"


/* I don't like globals variables, but how to take another way? */
extern GtkCTree *ctree_properties;
extern GtkCTreeNode *node_properties;
extern GWDBFile *file_properties;


gboolean gw_properties_box_catalog_ok ( GtkWidget *b, GtkWidget *w) {
	GtkCTreeNode *selection = NULL;
	gboolean result = FALSE;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && context != NULL ) {
		selection = GTK_CTREE_NODE ( GTK_CLIST ( ctree_properties)->selection->data);

		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
			if ( (catalog = plugin->gw_db_catalog_get_db_catalog ( context)) != NULL) {
				/* Checks if must update catalog name */
				gw_properties_box_catalog_name_check ( w, node_properties, catalog);

				/* Checks if must update catalog description */
				gw_properties_box_catalog_description_check ( w, catalog);

				plugin->gw_db_catalog_update ( context, catalog);
				gw_db_catalog_free ( catalog);
			}

			gtk_widget_destroy ( w);

			/* Selectes the selected item in the exploration tree to update files informations */
			gtk_ctree_select ( ctree_properties, selection);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_properties_box_disk_ok ( GtkWidget *b, GtkWidget *w) {
	GtkCTreeNode *selection = NULL;
	gboolean result = FALSE;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	GWDBDisk *disk = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && context != NULL ) {
		selection = GTK_CTREE_NODE ( GTK_CLIST ( ctree_properties)->selection->data);

		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
			/* Gets catalog and disk informations */
			if ( (disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( ctree_properties, node_properties))) != NULL) {
				/* Checks if must update disk name */
				gw_properties_box_disk_name_check ( w, node_properties, catalog, disk);

				/* Checks if must update disk number archive */
				gw_properties_box_disk_num_archive_check ( w, node_properties, catalog, disk);

				/* Checks if must update disk category */
				gw_properties_box_disk_category_check ( w, node_properties, catalog, disk);

				/* Checks if must update disk description */
				gw_properties_box_disk_description_check ( w, node_properties, catalog, disk);

				plugin->gw_db_disk_update ( context, disk);
				gw_db_disk_free ( disk);
			}

			if ( (catalog = plugin->gw_db_catalog_get_db_catalog ( context)) != NULL) {
				/* Checks if must update catalog name */
				gw_properties_box_catalog_name_check ( w, GTK_CTREE_ROW ( node_properties)->parent, catalog);

				/* Checks if must update catalog description */
				gw_properties_box_catalog_description_check ( w, catalog);

				plugin->gw_db_catalog_update ( context, catalog);
				gw_db_catalog_free ( catalog);
			}

			gtk_widget_destroy ( w);

			/* Selectes the selected item in the exploration tree to update files informations */
			gtk_ctree_select ( ctree_properties, selection);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_properties_box_folder_ok ( GtkWidget *b, GtkWidget *w) {
	GWDBFile *folder = NULL;
	GWDBDisk *disk = NULL;
	GtkCTreeNode *selection = NULL, *disk_node = NULL;
	gboolean result = FALSE;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && context != NULL ) {
		selection = GTK_CTREE_NODE ( GTK_CLIST ( ctree_properties)->selection->data);

		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
			disk_node = gw_folder_get_disk ( GTK_CTREE ( ctree_properties), node_properties);

			/* Gets catalog, disk and folder informations */
			if ( (folder = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( ctree_properties, node_properties))) != NULL) {
				/* Checks if must update folder category */
				gw_properties_box_folder_category_check ( w, folder);

				/* Checks if must update folder description */
				gw_properties_box_folder_description_check ( w, folder);

				plugin->gw_db_file_update ( context, folder);
			}

			if ( (disk = plugin->gw_db_file_get_db_disk ( context, gw_db_file_get_ref ( folder))) != NULL) {
				/* Checks if must update disk name */
				gw_properties_box_disk_name_check ( w, disk_node, catalog, disk);

				/* Checks if must update disk number archive */
				gw_properties_box_disk_num_archive_check ( w, disk_node, catalog, disk);

				/* Checks if must update disk category */
				gw_properties_box_disk_category_check ( w, disk_node, catalog, disk);

				/* Checks if must update disk description */
				gw_properties_box_disk_description_check ( w, disk_node, catalog, disk);

				plugin->gw_db_disk_update ( context, disk);
				gw_db_disk_free ( disk);
			}

			if ( (catalog = plugin->gw_db_catalog_get_db_catalog ( context)) != NULL) {
				/* Checks if must update catalog name */
				gw_properties_box_catalog_name_check ( w, GTK_CTREE_ROW ( disk_node)->parent, catalog);

				/* Checks if must update catalog description */
				gw_properties_box_catalog_description_check ( w, catalog);

				plugin->gw_db_catalog_update ( context, catalog);
				gw_db_catalog_free ( catalog);
			}

			if ( folder != NULL) {
				gw_db_file_free ( folder);
			}

			gtk_widget_destroy ( w);

			/* Selectes the selected item in the exploration tree to update files informations */
			gtk_ctree_select ( ctree_properties, selection);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_properties_box_file_ok ( GtkWidget *b, GtkWidget *w) {
	GWDBFile *folder = NULL, *file = file_properties;
	GWDBDisk *disk = NULL;
	GtkCTreeNode *selection = NULL;
	GtkCTreeNode *folder_node = node_properties, *disk_node = NULL;
	gboolean result = FALSE;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && context != NULL ) {
		selection = GTK_CTREE_NODE ( GTK_CLIST ( ctree_properties)->selection->data);

		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
			disk_node = gw_folder_get_disk ( GTK_CTREE ( ctree_properties), folder_node);

			/* Gets catalog, disk, folder and file informations */
			if ( file != NULL ) {
				/* Checks if must update file category */
				gw_properties_box_file_category_check ( w, file);

				/* Checks if must update file description */
				gw_properties_box_file_description_check ( w, file);

				plugin->gw_db_file_update ( context, file);
			}

			if ( (folder = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( ctree_properties, folder_node))) != NULL) {
				/* Checks if must update folder category */
				gw_properties_box_folder_category_check ( w, folder);

				/* Checks if must update folder description */
				gw_properties_box_folder_description_check ( w, folder);

				plugin->gw_db_file_update ( context, folder);
				gw_db_file_free ( folder);
			}

			if ( (disk = plugin->gw_db_file_get_db_disk ( context, gw_db_file_get_ref ( file))) != NULL) {
				/* Checks if must update disk name */
				gw_properties_box_disk_name_check ( w, disk_node, catalog, disk);

				/* Checks if must update disk number archive */
				gw_properties_box_disk_num_archive_check ( w, disk_node, catalog, disk);

				/* Checks if must update disk category */
				gw_properties_box_disk_category_check ( w, disk_node, catalog, disk);

				/* Checks if must update disk description */
				gw_properties_box_disk_description_check ( w, disk_node, catalog, disk);

				plugin->gw_db_disk_update ( context, disk);
				gw_db_disk_free ( disk);
			}

			if ( (catalog = plugin->gw_db_catalog_get_db_catalog ( context)) != NULL) {
				/* Checks if must update catalog name */
				gw_properties_box_catalog_name_check ( w, GTK_CTREE_ROW ( disk_node)->parent, catalog);

				/* Checks if must update catalog description */
				gw_properties_box_catalog_description_check ( w, catalog);

				plugin->gw_db_catalog_update ( context, catalog);
				gw_db_catalog_free ( catalog);
			}

			gtk_widget_destroy ( w);

			/* Selectes the selected item in the exploration tree to update files informations */
			gtk_ctree_select ( ctree_properties, selection);

			result = TRUE;
		}
	}

	return result;
}


gint gw_properties_box_catalog_name_check ( GtkWidget *w, GtkCTreeNode *node, GWDBCatalog *catalog) {
	guint8 spc;
	GdkBitmap *btmp;
	GdkPixmap *pxmp;
	gchar *catalog_name = NULL, *name = NULL, *text_utf8 = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && catalog != NULL) {
		if ( (catalog_name = gw_properties_box_get_catalog_name ( w)) != NULL) {
			//TODO The GUI updating should not be done here!!
			if ( strlen ( catalog_name) > 0 ) {
				/* If a name is displayed */
				gw_db_catalog_set_name ( catalog, g_strdup ( catalog_name));

				gtk_ctree_node_get_pixtext ( ctree_properties, node, 0, &name, &spc, &pxmp, &btmp);
				g_strdup_to_gtk_text ( gw_db_catalog_get_name ( catalog), text_utf8);
				gtk_ctree_node_set_pixtext ( ctree_properties, node, 0, text_utf8, spc, pxmp, btmp);
				g_free ( text_utf8);
			} else {
				gw_db_catalog_set_name ( catalog, NULL);

				gtk_ctree_node_get_pixtext ( ctree_properties, node, 0, &name, &spc, &pxmp, &btmp);
				g_strdup_to_gtk_text ( gw_db_catalog_get_short_db_name ( catalog), text_utf8);
				gtk_ctree_node_set_pixtext ( ctree_properties, node, 0, text_utf8, spc, pxmp, btmp);
				g_free ( text_utf8);
			}

			result = 0;

			g_free ( catalog_name);
		}
	}

	return result;
}


gint gw_properties_box_catalog_description_check ( GtkWidget *w, GWDBCatalog *catalog) {
	gint result = -1;
	gchar *catalog_description = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && catalog != NULL) {
		if ( (catalog_description = gw_properties_box_get_catalog_description ( w)) != NULL) {
			//TODO must we check the description length and force it to NULL when equals to 0??
			if ( strlen ( catalog_description) > 0 ) {
				gw_db_catalog_set_description ( catalog, g_strdup ( catalog_description));
			} else {
				gw_db_catalog_set_description ( catalog, NULL);
			}

			result = 0;

			g_free ( catalog_description);
		}
	}

	return result;
}


gint gw_properties_box_disk_name_check ( GtkWidget *w, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBDisk *disk) {
	guint8 spc;
	GdkBitmap *btmp;
	GdkPixmap *pxmp;
	gchar *disk_name = NULL, *name = NULL, *text_utf8 = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && disk != NULL) {
		if ( (disk_name = gw_properties_box_get_disk_name ( w)) != NULL) {
			//TODO The GUI updating should not be done here!!
			if ( strlen ( disk_name) > 0 && strcmp ( disk_name, gw_db_disk_get_name ( disk))!=0 ) {
				if ( !gw_helper_db_disk_name_is_exist ( gw_am_get_current_catalog_context ( ), disk_name)) {
					gw_db_disk_set_name ( disk, g_strdup ( disk_name));
					gtk_ctree_node_get_pixtext ( ctree_properties, node, 0, &name, &spc, &pxmp, &btmp);
					g_strdup_to_gtk_text ( disk_name, text_utf8);
					gtk_ctree_node_set_pixtext ( ctree_properties, node, 0, text_utf8, spc, pxmp, btmp);
					g_free ( text_utf8);
				} else {}
			}

			result = 0;

			g_free ( disk_name);
		}
	}

	return result;
}


gint gw_properties_box_disk_num_archive_check ( GtkWidget *w, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBDisk *disk) {
	gint num;
	gint result = -1;
	gchar *disk_num = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		disk_num = gw_properties_box_get_disk_num ( w);

		if ( ( num = strtol ( disk_num, NULL, 10)) != gw_db_disk_get_num ( disk) ) {
			/* If displayed number archive is different as disk number archive */
			if ( num > 0 ) {
				if ( !gw_helper_db_disk_num_is_exist ( gw_am_get_current_catalog_context ( ), num) ) {
					gw_db_disk_set_num ( disk, num);
				} else {}
			}
		}

		g_free ( disk_num);

		result = 0;
	}

	return result;
}


gint gw_properties_box_disk_category_check ( GtkWidget *w, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBDisk *disk) {
	gint result = -1;
GWDBCategoryPK src = NULL, dst = NULL;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		src = gw_properties_box_get_disk_category_ref ( w);
		dst = gw_db_disk_get_category ( disk);
//		if ( gw_properties_box_get_disk_category_ref ( w) != gw_db_disk_get_category ( disk) ) {
		if ( src != dst) {
			gw_db_disk_set_category ( disk, gw_properties_box_get_disk_category_ref ( w));
		}

		result = 0;
	}

	return result;
}


gint gw_properties_box_disk_description_check ( GtkWidget *w, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBDisk *disk) {
	gint result = -1;
	gchar *disk_description = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && disk != NULL) {
		if ( (disk_description = gw_properties_box_get_disk_description ( w)) != NULL) {
			//TODO must we check the description length and force it to NULL when equals to 0??
			if ( strlen ( disk_description) > 0 ) {
				gw_db_disk_set_description ( disk, g_strdup ( disk_description));
			} else {
				gw_db_disk_set_description ( disk, NULL);
			}

			result = 0;

			g_free ( disk_description);
		}
	}

	return result;
}


gint gw_properties_box_folder_category_check ( GtkWidget *w, GWDBFile *folder) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( gw_properties_box_get_folder_category_ref ( w) != gw_db_file_get_category ( folder) ) {
			gw_db_file_set_category ( folder, gw_properties_box_get_folder_category_ref ( w));
		}

		result = 0;
	}

	return result;
}


gint gw_properties_box_folder_description_check ( GtkWidget *w, GWDBFile *folder) {
	gint result = -1;
	gchar *folder_description = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && folder != NULL) {
		if ( (folder_description = gw_properties_box_get_folder_description ( w)) != NULL) {
			//TODO must we check the description length and force it to NULL when equals to 0??
			if ( strlen ( folder_description) > 0 ) {
				gw_db_file_set_description ( folder, g_strdup ( folder_description));
			} else {
				gw_db_file_set_description ( folder, NULL);
			}

			result = 0;

			g_free ( folder_description);
		}
	}

	return result;
}


gint gw_properties_box_file_category_check ( GtkWidget *w, GWDBFile *file) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( gw_properties_box_get_file_category_ref ( w) != gw_db_file_get_category ( file) ) {
			gw_db_file_set_category ( file, gw_properties_box_get_file_category_ref ( w));
		}

		result = 0;
	}

	return result;
}


gint gw_properties_box_file_description_check ( GtkWidget *w, GWDBFile *file) {
	gint result = -1;
	gchar *file_description = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && file != NULL) {
		if ( (file_description = gw_properties_box_get_file_description ( w)) != NULL) {
			//TODO must we check the description length and force it to NULL when equals to 0??
			if ( strlen ( file_description) > 0 ) {
				gw_db_file_set_description ( file, g_strdup ( file_description));
			} else {
				gw_db_file_set_description ( file, NULL);
			}

			result = 0;

			g_free ( file_description);
		}
	}

	return result;
}
