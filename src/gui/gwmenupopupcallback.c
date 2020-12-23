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
#include "gwmenupopupcallback.h"

#include <string.h> /* strlen strcmp */

#include "data/gwdata.h"

#include "gwnotebookcatalog.h"
#include "gwcategorieseditbox.h"
#include "gwpropertiesbox.h"
#include "gwmisc.h"
#include "gwtextbox.h"

#include "../gwguimanager.h"
#include "../gwapplicationmanager.h"
#include "../gwpluginsmanager.h"
#include "../gwhelper.h"


/* I don't like globals variables. But it's in order to memorize last selected node and files list. */
GtkCTreeNode *node_gw_menu_popup_callback = NULL;
//GList *files_gw_menu_popup_callback = NULL;
GWDBFile *files_gw_menu_popup_callback = NULL;


gboolean gw_menu_popup_catalog_rename ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkWindow *window = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL && context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);
			window = gw_gui_manager_main_interface_get_main_window ( );
			node_gw_menu_popup_callback = node;

			gw_input_box (window, _( "Rename catalog"), _( "Enter new catalog name"), gw_db_catalog_get_name ( catalog), 
			              gw_menu_popup_catalog_rename_ok);

			gw_db_catalog_free ( catalog);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_menu_popup_catalog_rename_ok ( GtkWidget *w, gpointer data) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GtkCTreeNode *selection = NULL;
	guint8 spc;
	GdkBitmap *btmp;
	GdkPixmap *pxmp;
	char * tmp_name = (char *) data;
	char * name;
	GtkWindow *window = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if (context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL )
		{
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);
			tree = gw_gui_manager_main_interface_get_tree ( );
			selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);
			window = gw_gui_manager_main_interface_get_main_window ( );

			gw_db_catalog_set_name ( catalog, g_strdup ( tmp_name));
			plugin->gw_db_catalog_update ( context, catalog);

			/* Updates the catalog name in the tree */
			gtk_ctree_node_get_pixtext ( tree, node_gw_menu_popup_callback, 0, &name, &spc, &pxmp, &btmp);
			gtk_ctree_node_set_pixtext ( tree, node_gw_menu_popup_callback, 0, gw_db_catalog_get_name (catalog), spc, pxmp, btmp);
			gw_db_catalog_free (catalog);

			/* Selects the selected item in the exploration tree to refresh the list of files. */
			gtk_ctree_select ( tree, selection);

			result = TRUE;
		}

		node_gw_menu_popup_callback = NULL;
		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_catalog_add_new_disk ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL ) {
		//TODO Must implement this function!!
	}

	return result;
}


gboolean gw_menu_popup_catalog_edit_description ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkWindow *window = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL && context != NULL ) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);
			window = gw_gui_manager_main_interface_get_main_window ( );
			node_gw_menu_popup_callback = node;

			gw_text_box_create ( window, _( "Edit description"), _( "Catalog description"), gw_db_catalog_get_description ( catalog), G_CALLBACK ( gw_menu_popup_catalog_edit_description_ok));

			gw_db_catalog_free ( catalog);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_menu_popup_catalog_edit_description_ok ( GtkWidget *b, GtkWidget *w)
{
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GtkCTreeNode *selection = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gchar *tmp_description = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && context != NULL ) {
		if ( (tmp_description = gw_text_box_get_text ( w)) != NULL) {
			if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
				catalog = plugin->gw_db_catalog_get_db_catalog ( context);
				tree = gw_gui_manager_main_interface_get_tree ( );
				selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

				gw_db_catalog_set_description ( catalog, strlen(tmp_description)>0?g_strdup(tmp_description):NULL);
				plugin->gw_db_catalog_update ( context, catalog);
				gw_db_catalog_free ( catalog);

				/* Selects the selected item in the exploration tree to refresh the list of files. */
				gtk_ctree_select ( tree, selection);

				result = TRUE;
			}

			g_free ( tmp_description);
		}

		gtk_widget_destroy ( w);
		node_gw_menu_popup_callback = NULL;
	}

	return result;
}


gboolean gw_menu_popup_catalog_edit_categories ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GWDBCatalog *catalog = NULL;
	GtkWindow *window = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL ) {
		tree = gw_gui_manager_main_interface_get_tree ( );
		catalog = gtk_ctree_node_get_row_data ( tree, node);
		window = gw_gui_manager_main_interface_get_main_window ( );

		gw_categories_edit_box_create ( window, catalog);

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_catalog_properties ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkWindow *window = NULL;
	GtkCTree *tree = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL ) {
		window = gw_gui_manager_main_interface_get_main_window ( );
		tree = gw_gui_manager_main_interface_get_tree ( );

		gw_properties_box_create_catalog ( m, window, tree, node);

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_disk_move_to ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL ) {
		tree = gw_gui_manager_main_interface_get_tree ( );

		if ( !GTK_CTREE_ROW ( node)->expanded ) {
			if ( node != NULL ) {
				gtk_ctree_expand ( tree, node);
			}
		}

		gtk_ctree_select ( GTK_CTREE ( tree), node);

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_disk_rename ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GtkWindow *window = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBDisk *disk = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL && context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			tree = gw_gui_manager_main_interface_get_tree ( );
			window = gw_gui_manager_main_interface_get_main_window ( );
			disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( tree, node));
			node_gw_menu_popup_callback = node;

			gw_input_box (window, _( "Rename disk"), _( "Enter new disk name"), gw_db_disk_get_name ( disk),
			              gw_menu_popup_disk_rename_ok);
			gw_db_disk_free ( disk);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_menu_popup_disk_rename_ok ( GtkWidget *w, gpointer data)
{
	gboolean result = FALSE;
	guint8 spc;
	GdkBitmap *btmp;
	GdkPixmap *pxmp;
	char * tmp_name = (char *) data;
	char * name = NULL;
	GtkCTree *tree = NULL;
	GtkCTreeNode *selection = NULL;
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBDisk *disk = NULL;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if (context != NULL )
	{
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL )
		{
			tree = gw_gui_manager_main_interface_get_tree ( );
			selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

			disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( tree, node_gw_menu_popup_callback));

			if ( strlen ( tmp_name)>0 && strcmp ( tmp_name, gw_db_disk_get_name ( disk))!=0 )
			{
				if ( gw_helper_db_disk_name_is_exist ( context, tmp_name))
				{
					gw_msg_box_create ( window, _("Rename disk"), _("The filled disk name already exist in the current catalog"));
				} else {
					gw_db_disk_set_name ( disk, g_strdup ( tmp_name));
					plugin->gw_db_disk_update ( context, disk);

					gtk_ctree_node_get_pixtext ( tree, node_gw_menu_popup_callback, 0, &name, &spc, &pxmp, &btmp);
					gtk_ctree_node_set_pixtext ( tree, node_gw_menu_popup_callback, 0, tmp_name, spc, pxmp, btmp);

					/* Selects the selected item in the exploration tree to refresh the list of files. */
					gtk_ctree_select ( tree, selection);
				}
			}

			gw_db_disk_free ( disk);
		}

		node_gw_menu_popup_callback = NULL;
		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_disk_delete ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkWindow *w = NULL;
	GtkCList *clist_info = NULL;
	GtkCList *clist = NULL;
	GtkCTree *tree = NULL;
	GtkCTreeNode *parent = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL && context != NULL ) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			tree = gw_gui_manager_main_interface_get_tree ( );
			w = gw_gui_manager_main_interface_get_main_window ( );
			parent = GTK_CTREE_ROW ( node)->parent;
			clist_info = gw_notebook_catalog_get_clist_explorer ( w);

			plugin->gw_db_catalog_remove_db_disk ( context, gtk_ctree_node_get_row_data ( tree, node));

			clist = GTK_CLIST ( tree);
			gtk_clist_freeze ( clist);
			gtk_clist_freeze ( clist_info);
			gtk_clist_clear ( clist_info);
			gtk_ctree_remove_node ( tree, node);
			gtk_clist_thaw ( clist);
			gtk_clist_thaw ( clist_info);
			gtk_ctree_select ( GTK_CTREE ( tree), parent);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_menu_popup_disk_change_volume_label ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GtkWindow *window = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBDisk *disk = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL && context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			tree = gw_gui_manager_main_interface_get_tree ( );
			window = gw_gui_manager_main_interface_get_main_window ( );
			disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( tree, node));
			node_gw_menu_popup_callback = node;

			gw_input_box (window, _( "Change volume label"), _( "Enter new disk volume label"), gw_db_disk_get_volume ( disk),
			              gw_menu_popup_disk_change_volume_label_ok);
			gw_db_disk_free ( disk);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_menu_popup_disk_change_volume_label_ok ( GtkWidget *w, gpointer data)
{
	gboolean result = FALSE;
	char *tmp_volume = (char *) data;
	GtkCTree *tree = NULL;
	GtkCTreeNode *selection = NULL;
	GtkWindow *window = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBDisk *disk = NULL;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if (context != NULL)
	{
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL )
		{
			tree = gw_gui_manager_main_interface_get_tree ( );
			selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);
			window = gw_gui_manager_main_interface_get_main_window ( );
			disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( tree, node_gw_menu_popup_callback));

			gw_db_disk_set_volume ( disk, g_strdup ( tmp_volume));
			plugin->gw_db_disk_update ( context, disk);
			gw_db_disk_free ( disk);

			/* Selects the selected item in the exploration tree to refresh the list of files. */
			gtk_ctree_select ( tree, selection);
		}

		node_gw_menu_popup_callback = NULL;
		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_disk_edit_description ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GtkWindow *window = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBDisk *disk = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL && context != NULL ) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			tree = gw_gui_manager_main_interface_get_tree ( );
			disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( tree, node));
			window = gw_gui_manager_main_interface_get_main_window ( );
			node_gw_menu_popup_callback = node;

			gw_text_box_create ( window, _( "Edit description"), _( "Disk description"), gw_db_disk_get_description ( disk), G_CALLBACK ( gw_menu_popup_disk_edit_description_ok));

			gw_db_disk_free ( disk);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_menu_popup_disk_edit_description_ok ( GtkWidget *b, GtkWidget *w) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GtkCTreeNode *selection = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBDisk *disk = NULL;
	gchar *tmp_description = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if (context != NULL ) {
		if ( (tmp_description = gw_text_box_get_text ( w)) != NULL) {
			if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
				tree = gw_gui_manager_main_interface_get_tree ( );
				disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( tree, node_gw_menu_popup_callback));
				selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

				gw_db_disk_set_description ( disk, strlen(tmp_description)>0?g_strdup(tmp_description):NULL);
				plugin->gw_db_disk_update ( context, disk);
				gw_db_disk_free ( disk);

				/* Selects the selected item in the exploration tree to refresh the list of files. */
				gtk_ctree_select ( tree, selection);

				result = TRUE;
			}

			g_free ( tmp_description);
		}

		gtk_widget_destroy ( w);
		node_gw_menu_popup_callback = NULL;
	}

	return result;
}


gboolean gw_menu_popup_disk_properties ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkWindow *window = NULL;
	GtkCTree *tree = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL ) {
		window = gw_gui_manager_main_interface_get_main_window ( );
		tree = gw_gui_manager_main_interface_get_tree ( );

		gw_properties_box_create_disk ( m, window, tree, node);

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_folder_move_to ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL ) {
		tree = gw_gui_manager_main_interface_get_tree ( );

		if ( !GTK_CTREE_ROW ( node)->expanded ) {
			if ( node != NULL ) {
				gtk_ctree_expand ( tree, node);
			}
		}

		gtk_ctree_select ( GTK_CTREE ( tree), node);

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_folder_rename ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GtkWindow *window = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBFile *file = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL && context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			tree = gw_gui_manager_main_interface_get_tree ( );
			window = gw_gui_manager_main_interface_get_main_window ( );
			file = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( tree, node));
			node_gw_menu_popup_callback = node;

			gw_input_box (window, _( "Rename folder"), _( "Enter new folder name"), gw_db_file_get_name ( file),
			              gw_menu_popup_folder_rename_ok);
			gw_db_file_free ( file);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_menu_popup_folder_rename_ok ( GtkWidget *w, gpointer data)
{
	gboolean result = FALSE;
	guint8 spc;
	GdkBitmap *btmp;
	GdkPixmap *pxmp;
	char * tmp_name = (char *) data;
	char * name = NULL;
	GtkCTree *tree = NULL;
	GtkCTreeNode *selection = NULL;
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBFile *file = NULL;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if (context != NULL)
	{
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL )
		{
			tree = gw_gui_manager_main_interface_get_tree ( );
			selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

			file = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( tree, node_gw_menu_popup_callback));

			/* Checks of the filled folder name isn't equals to the current folder name. */
			if ( strlen ( tmp_name)>0 && strcmp ( tmp_name, gw_db_file_get_name ( file))!=0 ) {
				if ( gw_helper_db_file_name_is_exist ( context, gw_db_file_get_ref ( file), tmp_name) ) {
					gw_msg_box_create ( window, _("Rename folder"), _("The filled folder name already exist in the current folder"));
				} else {
					gw_db_file_set_name ( file, g_strdup ( tmp_name));
					plugin->gw_db_file_update ( context, file);

					gtk_ctree_node_get_pixtext ( tree, node_gw_menu_popup_callback, 0, &name, &spc, &pxmp, &btmp);
					gtk_ctree_node_set_pixtext ( tree, node_gw_menu_popup_callback, 0, tmp_name, spc, pxmp, btmp);

					/* Selects the selected item in the exploration tree to refresh the list of files. */
					gtk_ctree_select ( tree, selection);
				}
			}

			gw_db_file_free ( file);
		} 

		node_gw_menu_popup_callback = NULL;
		files_gw_menu_popup_callback = NULL;
		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_folder_edit_description ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GtkWindow *window = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBFile *file = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL && context != NULL ) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			tree = gw_gui_manager_main_interface_get_tree ( );
			file = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( tree, node));
			window = gw_gui_manager_main_interface_get_main_window ( );
			node_gw_menu_popup_callback = node;

			gw_text_box_create ( window, _( "Edit description"), _( "Folder description"), gw_db_file_get_description ( file), G_CALLBACK ( gw_menu_popup_folder_edit_description_ok));

			gw_db_file_free ( file);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_menu_popup_folder_edit_description_ok ( GtkWidget *b, GtkWidget *w)
{
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GtkCTreeNode *selection = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBFile *file = NULL;
	gchar *tmp_description = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && context != NULL ) {
		if ( (tmp_description = gw_text_box_get_text ( w)) != NULL) {
			if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
				tree = gw_gui_manager_main_interface_get_tree ( );
				file = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( tree, node_gw_menu_popup_callback));
				selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

				gw_db_file_set_description ( file, strlen(tmp_description)>0?g_strdup(tmp_description):NULL);
				plugin->gw_db_file_update ( context, file);
				gw_db_file_free ( file);

				/* Selects the selected item in the exploration tree to refresh the list of files. */
				gtk_ctree_select ( tree, selection);

				result = TRUE;
			}

			g_free ( tmp_description);
		}

		gtk_widget_destroy ( w);
		node_gw_menu_popup_callback = NULL;
	}

	return result;
}


gboolean gw_menu_popup_folder_remove ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkWindow *w = NULL;
	GtkCList *clist_info = NULL;
	GtkCList *clist;
	GtkCTreeNode *tmp, *parent = NULL;
	GtkCTree *tree = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBFile *file = NULL, *tmp_file = NULL;
	GWDBDisk *disk = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL && context != NULL ) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			parent = GTK_CTREE_ROW ( node)->parent;
			w = gw_gui_manager_main_interface_get_main_window ( );
			clist_info = gw_notebook_catalog_get_clist_explorer ( w);
			tree = gw_gui_manager_main_interface_get_tree ( );

			//TODO very bad way!!
			/* Updates the folders size which contains the folder to delete. */
			tmp = parent;
			file = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( tree, node));

			while ( GTK_CTREE_ROW ( GTK_CTREE_ROW ( tmp)->parent)->parent != NULL ) {
				tmp_file = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( tree, tmp));
				gw_db_file_set_size ( tmp_file, gw_db_file_get_size ( tmp_file) - gw_db_file_get_size ( file));
				plugin->gw_db_file_update ( context, tmp_file);
				tmp = GTK_CTREE_ROW ( tmp)->parent;
				gw_db_file_free ( tmp_file);
			}

			/* Updates the disk size which contains the folder to delete. */
			disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( tree, tmp));
			gw_db_disk_set_full ( disk, gw_db_disk_get_full ( disk) - gw_db_file_get_size ( file));
			plugin->gw_db_disk_update ( context, disk);
			gw_db_disk_free ( disk);
			plugin->gw_db_catalog_remove_db_file ( context, gw_db_file_get_ref ( file));
			gw_db_file_free ( file);

			clist = GTK_CLIST ( tree);
			gtk_clist_freeze ( clist);
			gtk_clist_freeze ( clist_info);
			gtk_clist_clear ( clist_info);
			gtk_ctree_remove_node ( tree, node);
			gtk_clist_thaw ( clist);
			gtk_clist_thaw ( clist_info);
			gtk_ctree_select ( GTK_CTREE ( tree), parent);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_menu_popup_folder_properties ( GtkMenuItem *m, GtkCTreeNode *node) {
	gboolean result = FALSE;
	GtkWindow *window = NULL;
	GtkCTree *tree = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL ) {
		window = gw_gui_manager_main_interface_get_main_window ( );
		tree = gw_gui_manager_main_interface_get_tree ( );

		gw_properties_box_create_folder ( m, window, tree, node);

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_file_rename ( GtkMenuItem *m, gpointer row) {
	gboolean result = FALSE;
	GtkCTree *tree = NULL;
	GtkWindow *window = NULL;
	GtkCTreeNode *selection = NULL;
	GtkCList *clist_info = NULL;
	gchar *name = NULL;
	guint8 spc;
	GdkBitmap *btmp;
	GdkPixmap *pxmp;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( GPOINTER_TO_INT ( row ) >= 0 ) {
		tree = gw_gui_manager_main_interface_get_tree ( );
		window = gw_gui_manager_main_interface_get_main_window ( );
		clist_info = gw_notebook_catalog_get_clist_explorer ( window);

		/* Gets the file name. */
		gtk_clist_get_pixtext ( GTK_CLIST ( clist_info), GPOINTER_TO_INT ( row), 0, &name, &spc, &btmp, &pxmp);
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : selected file is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, name);
#endif

		/* Gets the parent folder. */
		selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

		/* Gets file informations. */
		files_gw_menu_popup_callback = (GWDBFile*)gtk_clist_get_row_data ( GTK_CLIST ( clist_info), GPOINTER_TO_INT ( row));

		gw_input_box (window, _( "Rename file"), _( "Enter new file name"), name,
		              gw_menu_popup_file_rename_ok);

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_file_rename_ok ( GtkWidget *w, gpointer data)
{
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	gboolean result = FALSE;
	GWDBFile *file = NULL;
	GtkCTree *tree = NULL;
	GtkCTreeNode *selection = NULL;
	char *tmp_name = (char *) data;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if (context != NULL)
	{
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL )
		{
			tree = gw_gui_manager_main_interface_get_tree ( );
			selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

			file = files_gw_menu_popup_callback;
				/* Checks of the filled file name isn't equals to the current file name. */
			if ( strlen ( tmp_name)>0 && strcmp ( tmp_name, gw_db_file_get_name ( file))!=0 )
			{
				if ( gw_helper_db_file_name_is_exist ( context, gw_db_file_get_ref ( file), tmp_name) ) {
					gw_msg_box_create ( window, _("Rename file"), _("The filled file name already exist in the current folder"));
				} else {
					gw_db_file_set_name ( file, g_strdup ( tmp_name));
					plugin->gw_db_file_update ( context, file);

					/* Selects the selected item in the exploration tree to refresh the list of files. */
					gtk_ctree_select ( tree, selection);
				}
			}
		}

		node_gw_menu_popup_callback = NULL;
		files_gw_menu_popup_callback = NULL;
		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_file_edit_description ( GtkMenuItem *m, gpointer row) {
	gboolean result = FALSE;
	GtkWindow *w = NULL;
	GtkCList *clist_info = NULL;
	GtkCTreeNode *selection;
	gchar *name = NULL;
	guint8 spc;
	GdkBitmap *btmp;
	GdkPixmap *pxmp;
	GtkCTree *tree = NULL;
	GtkWindow *window = NULL;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( GPOINTER_TO_INT ( row ) >= 0 ) {
		tree = gw_gui_manager_main_interface_get_tree ( );
		window = gw_gui_manager_main_interface_get_main_window ( );

		w = gw_gui_manager_main_interface_get_main_window ( );
		clist_info = gw_notebook_catalog_get_clist_explorer ( w);

		/* Gets the file name. */
		gtk_clist_get_pixtext ( GTK_CLIST ( clist_info), GPOINTER_TO_INT ( row), 0, &name, &spc, &btmp, &pxmp);
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : selected file is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, name);
#endif

		/* Gets the parent folder. */
		selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

		/* Gets file informations. */
		files_gw_menu_popup_callback = (GWDBFile*)gtk_clist_get_row_data ( GTK_CLIST ( clist_info), GPOINTER_TO_INT ( row));

		node_gw_menu_popup_callback = selection;
		gw_text_box_create ( window, _( "Edit description"), _( "File description"), gw_db_file_get_description ( files_gw_menu_popup_callback), G_CALLBACK ( gw_menu_popup_file_edit_description_ok));

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_popup_file_edit_description_ok ( GtkWidget *b, gpointer data)
{
	gboolean result = FALSE;
	GWDBFile *file = NULL;
	GtkCTree *tree = NULL;
	GtkCTreeNode *selection = NULL;
	gchar *text = (char *) data;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	tree = gw_gui_manager_main_interface_get_tree ( );
	selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

	file = files_gw_menu_popup_callback;

	if ( (gw_db_file_get_description ( file) == NULL) || (strcmp ( text, gw_db_file_get_description ( file)) != 0) ) {
		/* If the filled description isn't equals to the file description. */
		if ( strlen ( text) > 0 ) {
			gw_db_file_set_description ( file, g_strdup ( text));
		} else {
			gw_db_file_set_description ( file, NULL);
		}
		((GWCatalogPlugin*)gw_db_context_get_plugin ( context))->gw_db_file_update ( context, file);

		/* Indicates that catalog have been modified. */
		catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( context))->gw_db_catalog_get_db_catalog ( context);
		gw_db_catalog_set_ismodified ( catalog, TRUE);
		((GWCatalogPlugin*)gw_db_context_get_plugin ( context))->gw_db_catalog_update ( context, catalog);
	}

	/* Selects the selected item in the exploration tree to refresh the list of files. */
	gtk_ctree_select ( tree, selection);

	node_gw_menu_popup_callback = NULL;
	files_gw_menu_popup_callback = NULL;

	return TRUE;
}


gboolean gw_menu_popup_file_remove ( GtkMenuItem *m, gpointer row) {
	gboolean result = FALSE;
	GtkWindow *w = NULL;
	GtkCList *clist_info = NULL;
	GWDBFile *file = NULL;
	GtkCTreeNode *selection = NULL, *parent = NULL, *tmp = NULL;
	GtkCTree *tree = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBDisk *disk = NULL;
	GWDBFile *tmp_file = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( GPOINTER_TO_INT ( row ) >= 0 && context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			tree = gw_gui_manager_main_interface_get_tree ( );
			w = gw_gui_manager_main_interface_get_main_window ( );
			clist_info = gw_notebook_catalog_get_clist_explorer ( w);

			/* Gets the file to delete. */
			file = (GWDBFile*)gtk_clist_get_row_data ( GTK_CLIST ( clist_info), GPOINTER_TO_INT ( row));
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : selected file is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, gw_db_file_get_name ( file));
#endif

			/* Gets the parent folder. */
			parent = selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

			/* Updates the folders size which contains the file to delete. */
			tmp = parent;

			while ( GTK_CTREE_ROW ( GTK_CTREE_ROW ( tmp)->parent)->parent != NULL ) {
				tmp_file = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( tree, tmp));
				gw_db_file_set_size ( tmp_file, gw_db_file_get_size ( tmp_file) - gw_db_file_get_size ( file));
				plugin->gw_db_file_update ( context, tmp_file);
				tmp = GTK_CTREE_ROW ( tmp)->parent;
				gw_db_file_free ( tmp_file);
			}

			/* Updates the disk size which contains the folder to delete. */
			disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( tree, tmp));
			gw_db_disk_set_full ( disk, gw_db_disk_get_full ( disk) - gw_db_file_get_size ( file));
			plugin->gw_db_disk_update ( context, disk);
			gw_db_disk_free ( disk);
			plugin->gw_db_catalog_remove_db_file ( context, gw_db_file_get_ref ( file));

			/* Selects the selected item in the exploration tree to refresh the list of files. */
			gtk_ctree_select ( GTK_CTREE ( tree), selection);


			result = TRUE;
		}
	}

	return result;
}


gboolean gw_menu_popup_file_properties ( GtkMenuItem *m, gpointer row) {
	gboolean result = FALSE;
	GtkCList *clist_info = NULL;
	GtkCTreeNode *selection = NULL;
	GtkWindow *window = NULL;
	GtkCTree *tree = NULL;
	GWDBFile *file = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( GPOINTER_TO_INT ( row ) >= 0 ) {
		window = gw_gui_manager_main_interface_get_main_window ( );
		tree = gw_gui_manager_main_interface_get_tree ( );
		clist_info = gw_notebook_catalog_get_clist_explorer ( window);

		/* Gets the file to show properties. */
		file = gtk_clist_get_row_data ( GTK_CLIST ( clist_info), GPOINTER_TO_INT ( row));

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : selected file (%d) is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, GPOINTER_TO_INT ( row), gw_db_file_get_name ( file));
#endif

		/* Gets the parent folder. */
		selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data);

		gw_properties_box_create_file ( m, window, tree, selection, file);

		result = TRUE;
	}

	return result;
}
