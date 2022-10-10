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
#include "gwpropertiesbox.h"

#include <stdlib.h>
#include <string.h> /* strlen */

#include "tools/gwtools.h"
#include "res/gwres.h"

#include "gtktextarea.h"
#include "gwpropertiesboxcallback.h"
#include "gwcomboboxcategories.h"
#include "../gwapplicationmanager.h"
#include "../gwpluginsmanager.h"

#include "../gwhelper.h"


/*! @define	GW_REF_PROPERTIES_BOX_PARENT_WINDOW	The parent window reference */
#define GW_REF_PROPERTIES_BOX_PARENT_WINDOW "gw_ref_gw_properties_box_parent_window"
/*! @define	GW_REF_PROPERTIES_BOX_CATALOG_NAME_ENTRY	The catalog name entry */
#define GW_REF_PROPERTIES_BOX_CATALOG_NAME_ENTRY "gw_ref_gw_properties_box_catalog_name_entry"
/*! @define	GW_REF_PROPERTIES_BOX_CATALOG_DESCRIPTION_TEXT	The catalog description text */
#define GW_REF_PROPERTIES_BOX_CATALOG_DESCRIPTION_TEXT "gw_ref_gw_properties_box_catalog_description_text"
/*! @define	GW_REF_PROPERTIES_BOX_DISK_NAME_ENTRY	The disk name entry */
#define GW_REF_PROPERTIES_BOX_DISK_NAME_ENTRY "gw_ref_gw_properties_box_disk_name_entry"
/*! @define	GW_REF_PROPERTIES_BOX_DISK_NUMBER_ARCHIVE_ENTRY	The disk number archive entry */
#define GW_REF_PROPERTIES_BOX_DISK_NUMBER_ARCHIVE_ENTRY "gw_ref_gw_properties_box_disk_number_archive_entry"
/*! @define	GW_REF_PROPERTIES_BOX_DISK_CATEGORIES_CMB_BOX	The disk categories combo box */
#define GW_REF_PROPERTIES_BOX_DISK_CATEGORIES_CMB_BOX "gw_ref_gw_properties_box_disk_categories_cmb_box"
/*! @define	GW_REF_PROPERTIES_BOX_DISK_DESCRIPTION_TEXT	The disk description text */
#define GW_REF_PROPERTIES_BOX_DISK_DESCRIPTION_TEXT "gw_ref_gw_properties_box_disk_description_text"
/*! @define	GW_REF_PROPERTIES_BOX_FOLDER_CATEGORIES_CMB_BOX	The folder categories combo box */
#define GW_REF_PROPERTIES_BOX_FOLDER_CATEGORIES_CMB_BOX "gw_ref_gw_properties_box_folder_categories_cmb_box"
/*! @define	GW_REF_PROPERTIES_BOX_FOLDER_DESCRIPTION_TEXT	The folder description text */
#define GW_REF_PROPERTIES_BOX_FOLDER_DESCRIPTION_TEXT "gw_ref_gw_properties_box_folder_description_text"
/*! @define	GW_REF_PROPERTIES_BOX_FILE_CATEGORIES_CMB_BOX	The file categories combo box */
#define GW_REF_PROPERTIES_BOX_FILE_CATEGORIES_CMB_BOX "gw_ref_gw_properties_box_file_categories_cmb_box"
/*! @define	GW_REF_PROPERTIES_BOX_FILE_DESCRIPTION_TEXT	The file description text */
#define GW_REF_PROPERTIES_BOX_FILE_DESCRIPTION_TEXT "gw_ref_gw_properties_box_file_description_text"


/* I don't like globals variables, but how to take another way? */
GtkCTree *ctree_properties = NULL;
GtkCTreeNode *node_properties = NULL;
GWDBFile *file_properties = NULL;


GtkWidget * gw_properties_box_create ( GtkWindow *window, GtkCTree *ctree, GtkCTreeNode *node, gint what, GWDBFile *file) {
	/* This is a single window, this properties may be changed */
	static GtkWidget *w = NULL;
	GtkWidget *vb_properties;
	GtkWidget *notebook_properties;
	GtkWidget *hb_buttons;
	GtkWidget *button;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	GWDBDisk *disk = NULL;
	GWDBFile *folder = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( !w && context != NULL ) {
		plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
		catalog = plugin->gw_db_catalog_get_db_catalog ( context);

		w = gtk_window_new ( GTK_WINDOW_TOPLEVEL);

		gtk_window_set_modal ( GTK_WINDOW ( w), TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( w), window);
		gtk_window_set_position ( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);
		gtk_window_set_title ( GTK_WINDOW ( w), _( "Properties"));
		gtk_container_set_border_width ( GTK_CONTAINER ( w), 5);

		/* Store parent window reference */
		g_object_ref ( w);
		g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_PARENT_WINDOW, window, (GDestroyNotify) g_object_unref);

		g_signal_connect (G_OBJECT ( w), "destroy", G_CALLBACK (gtk_widget_destroyed), &w);

		vb_properties = gtk_vbox_new ( FALSE, 0);
		gtk_container_add ( GTK_CONTAINER ( w), vb_properties);

		notebook_properties = gtk_notebook_new ( );
		gtk_container_set_border_width ( GTK_CONTAINER ( notebook_properties), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_properties), notebook_properties, TRUE, TRUE, 0);

		/* Creates tabbed panes switch of properties box kind */
		switch ( what)
		{
			case GW_PROPERTIES_TYPE_CATALOG :	ctree_properties = ctree;
							node_properties = node;

							gw_properties_box_create_notebook_panel_catalog_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), ctree, node, catalog);

							break;

			case GW_PROPERTIES_TYPE_DISK :		ctree_properties = ctree;
							node_properties = node;

//							gtk_ctree_node_get_pixtext ( ctree, GTK_CTREE_ROW ( node)->parent, 0, &name, &spc, &pxmp, &btmp);
							disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( ctree, node));
							gw_properties_box_create_notebook_panel_disk_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), ctree, node, catalog, disk);
							gw_properties_box_create_notebook_panel_catalog_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), ctree, GTK_CTREE_ROW ( node)->parent, catalog);
							gw_db_disk_free ( disk);

							break;

			case GW_PROPERTIES_TYPE_FOLDER :	ctree_properties = ctree;
							node_properties = node;

//							gtk_ctree_node_get_pixtext ( ctree, gw_folder_get_catalog ( ctree, node), 0, &name, &spc, &pxmp, &btmp);
							disk = plugin->gw_db_file_get_db_disk ( context, gtk_ctree_node_get_row_data ( ctree, node));
							folder = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( ctree, node));
							gw_properties_box_create_notebook_panel_folder_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), catalog, disk, folder);
							gw_properties_box_create_notebook_panel_disk_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), ctree, gw_folder_get_disk ( ctree, node), catalog, disk);
							gw_properties_box_create_notebook_panel_catalog_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), ctree, gw_folder_get_catalog ( ctree, node), catalog);
							gw_db_disk_free ( disk);
							gw_db_file_free ( folder);

							break;

			case GW_PROPERTIES_TYPE_FILE :		ctree_properties = ctree;
							node_properties = node;
							file_properties = file;

							gw_properties_box_create_notebook_panel_file_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), ctree, node, gtk_ctree_node_get_row_data ( ctree, gw_folder_get_catalog ( ctree, node)), file);

							if ( GTK_CTREE_ROW ( GTK_CTREE_ROW ( node)->parent)->parent != NULL ) {
								/* If file is not in the disk root */
//								gtk_ctree_node_get_pixtext ( ctree, gw_folder_get_catalog ( ctree, node), 0, &name, &spc, &pxmp, &btmp);

								disk = plugin->gw_db_file_get_db_disk ( context, gtk_ctree_node_get_row_data ( ctree, node));
								folder = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( ctree, node));
								gw_properties_box_create_notebook_panel_folder_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), catalog, disk, folder);
								gw_properties_box_create_notebook_panel_disk_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), ctree, gw_folder_get_disk ( ctree, node), catalog, disk);
								gw_properties_box_create_notebook_panel_catalog_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), ctree, gw_folder_get_catalog ( ctree, node), catalog);
								gw_db_disk_free ( disk);
								gw_db_file_free ( folder);
							} else {
								/* Else if the file is in disk root */
//								gtk_ctree_node_get_pixtext ( ctree, GTK_CTREE_ROW ( node)->parent, 0, &name, &spc, &pxmp, &btmp);

								disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( ctree, node));
								gw_properties_box_create_notebook_panel_disk_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), ctree, node, catalog, disk);
								gw_properties_box_create_notebook_panel_catalog_info ( GTK_WINDOW ( w), GTK_NOTEBOOK ( notebook_properties), ctree, gw_folder_get_catalog ( ctree, node), catalog);
								gw_db_disk_free ( disk);
							}

							break;

			default :		break;
		}

		/* The OK/Cancel button area */
		hb_buttons = gtk_hbutton_box_new ( );
		gtk_button_box_set_layout ( GTK_BUTTON_BOX ( hb_buttons), GTK_BUTTONBOX_END);
		gtk_box_set_spacing (GTK_BOX ( hb_buttons), 5);
		gtk_box_pack_end ( GTK_BOX ( vb_properties), hb_buttons, FALSE, FALSE, 0);

		button = gtk_button_new_with_mnemonic (_("_OK"));
		g_object_set_data (G_OBJECT ( button), "userdata", w);
		gtk_box_pack_start ( GTK_BOX ( hb_buttons), button, TRUE, TRUE, 0);
		GTK_WIDGET_SET_FLAGS ( button, GTK_CAN_FOCUS);
		GTK_WIDGET_SET_FLAGS ( button, GTK_CAN_DEFAULT);
		gtk_widget_grab_default ( button);

		switch ( what)
		{
			case GW_PROPERTIES_TYPE_CATALOG :	g_signal_connect (G_OBJECT ( button), "clicked", G_CALLBACK ( gw_properties_box_catalog_ok), w);

							break;

			case GW_PROPERTIES_TYPE_DISK :		g_signal_connect (G_OBJECT ( button), "clicked", G_CALLBACK ( gw_properties_box_disk_ok), w);

							break;

			case GW_PROPERTIES_TYPE_FOLDER :	g_signal_connect (G_OBJECT ( button), "clicked", G_CALLBACK ( gw_properties_box_folder_ok), w);

							break;

			case GW_PROPERTIES_TYPE_FILE :		g_signal_connect (G_OBJECT ( button), "clicked", G_CALLBACK ( gw_properties_box_file_ok), w);

							break;

			default :		break;
		}

		button = gtk_button_new_with_mnemonic (_("_Cancel"));
		g_object_set_data (G_OBJECT ( button), "userdata", w);
		gtk_box_pack_start ( GTK_BOX ( hb_buttons), button, TRUE, TRUE, 0);
		g_signal_connect_swapped (G_OBJECT ( button), "clicked", G_CALLBACK ( gtk_widget_destroy), GTK_OBJECT ( w));
		GTK_WIDGET_SET_FLAGS ( button, GTK_CAN_FOCUS);

		gw_db_catalog_free ( catalog);
	}

	if ( !gtk_widget_get_visible ( w) )
	{
#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : show the window\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		gtk_widget_show_all ( w);
	}
	else
	{
#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : destroy the window\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		gtk_widget_destroy ( w);
	}

	return w;
}


GtkWidget * gw_properties_box_create_catalog ( GtkMenuItem *m, GtkWindow *win, GtkCTree *ctree, GtkCTreeNode *node)
{
#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return gw_properties_box_create ( win, ctree, node, GW_PROPERTIES_TYPE_CATALOG, NULL);
}


GtkWidget * gw_properties_box_create_disk ( GtkMenuItem *m, GtkWindow *win, GtkCTree *ctree, GtkCTreeNode *node)
{
#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return gw_properties_box_create ( win, ctree, node, GW_PROPERTIES_TYPE_DISK, NULL);
}


GtkWidget * gw_properties_box_create_folder ( GtkMenuItem *m, GtkWindow *win, GtkCTree *ctree, GtkCTreeNode *node)
{
#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return gw_properties_box_create ( win, ctree, node, GW_PROPERTIES_TYPE_FOLDER, NULL);
}


GtkWidget * gw_properties_box_create_file ( GtkMenuItem *m, GtkWindow *win, GtkCTree *ctree, GtkCTreeNode *node, GWDBFile *file)
{
#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return gw_properties_box_create ( win, ctree, node, GW_PROPERTIES_TYPE_FILE, file);
}


GtkNotebook * gw_properties_box_create_notebook_panel_catalog_info ( GtkWindow *w, GtkNotebook *parent, GtkCTree *ctree, GtkCTreeNode *node, GWDBCatalog *catalog) {
	GtkWidget *vb_tabbed_pane; /* Vertical box of the tabbed pane */
	GtkWidget *hb_1; /* 1st horizontal box */
	GtkWidget *hb_2; /* 2nd horizontal box */
	GtkWidget *hb_3; /* 3th horizontal box */
	GtkWidget *vb_2_1; /* 1st vertical box of 2nd horizontal box*/
	GtkWidget *vb_2_2; /* 2nd vertival box of 2nd horizontal box */
	GtkWidget *vb_3_1; /* 1st vertical box of 3th horizontal box */
	GtkWidget *vb_3_2; /* 2nd vertical box of 3th horizontal box */
	GtkWidget *pix_ico_catalog; /* catalog icon */
	GtkWidget *hb_empty; /* horizontal box (used for empty box) */
	GtkWidget *lbl; /* label */
	GtkWidget *entry; /* entry (filled area) */
	GtkWidget *hseparator; /* horizontal separator */
	GtkWidget *scrolled_area; /* scrolled window for text area */
	GtkWidget *text_area; /* text area */
	GtkBox *cmb_categories;	/* Categories combo box */
	gchar *text = NULL;
	gchar *tempstr = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Vertical box of the tabbed pane */
	vb_tabbed_pane = gtk_vbox_new ( FALSE, 5);
	gtk_container_set_border_width ( GTK_CONTAINER ( vb_tabbed_pane), 10);
	gtk_container_add ( GTK_CONTAINER ( parent), vb_tabbed_pane);

	/* 1st horizontal box */
	hb_1 = gtk_hbox_new ( FALSE, 5);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_1), 5);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_1, FALSE, FALSE, 0);

	/* Catalog icon */
	pix_ico_catalog = gtk_pixmap_new ( PixCatalog, MskCatalog);
	gtk_box_pack_start ( GTK_BOX ( hb_1), pix_ico_catalog, FALSE, TRUE, 10);

	/* Filled area of catalog name */
	entry = gtk_entry_new ( );
	gtk_entry_set_text ( GTK_ENTRY ( entry), gw_db_catalog_get_name ( catalog));
	g_object_ref ( entry);
	g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_CATALOG_NAME_ENTRY, entry, (GDestroyNotify) g_object_unref);
	gtk_box_pack_start ( GTK_BOX ( hb_1), entry, FALSE, TRUE, 0);
	gtk_widget_set_tooltip_text (entry, _( "Enter the name of the catalog."));

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( hb_1), hb_empty, TRUE, TRUE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* 2nd horizontal box*/
	hb_2 = gtk_hbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_2, FALSE, FALSE, 0);

	/* 1st vertical box of 2nd horizontal box */
	vb_2_1 = gtk_vbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( hb_2), vb_2_1, TRUE, TRUE, 0);

	/* Horizontal box for catalog file version */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* Catalog file version label */
	lbl = gtk_label_new (_( "Version : "));
	text = g_strconcat ( _( "Version "), gw_db_catalog_get_version ( catalog), _( " built with "), gw_db_catalog_get_program_builder ( catalog), NULL);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for number of disks */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* Number of disks label */
	lbl = gtk_label_new (_("Disks in catalog : "));
	text = g_strdup_printf ( _( "Disks in catalog : %d"), ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_nb_db_disks ( gw_am_get_current_catalog_context ( )));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for total number of files */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* Total number of files label */
	lbl = gtk_label_new (_( "Total Files : "));
	text = g_strdup_printf ( _( "Total Files : %ld"), ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_nb_db_files ( gw_am_get_current_catalog_context ( )));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for total number of folders */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* Total number of files label */
	lbl = gtk_label_new (_( "Total Folders : "));
	text = g_strdup_printf ( _( "Total Folders : %ld"), ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_nb_db_folders ( gw_am_get_current_catalog_context ( )));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* 2nd vertical box of the 2nd horizontal box */
	vb_2_2 = gtk_vbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( hb_2), vb_2_2, TRUE, TRUE, 0);

	/* Horizontal box for catalog size */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* Catalog size label */
	lbl = gtk_label_new (_( "File Size : "));
	tempstr = gw_ul_byte_to_str_format ( gw_db_catalog_get_size ( catalog));
	text = g_strconcat ( _( "File Size : "), tempstr, NULL);
	if (tempstr) {
		g_free (tempstr);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for total capacity of catalog */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* Total capacity of catalog label */
	lbl = gtk_label_new (_( "Total Storage Space : "));
	tempstr = gw_ld_byte_to_str_format ( ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_capacity ( gw_am_get_current_catalog_context ( )));
	text = g_strconcat ( _( "Total Storage Space : "), tempstr, NULL);
	if (tempstr) {
		g_free (tempstr);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for used space of catalog */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* Used space of catalog label */
	lbl = gtk_label_new (_( "Total Used Space : "));
	tempstr = gw_ld_byte_to_str_format ( ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_full ( gw_am_get_current_catalog_context ( )));
	text = g_strconcat ( _( "Total Used Space : "), tempstr, NULL);
	if (tempstr) {
		g_free (tempstr);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Boite horizontale pour l'espace libre du catalogue */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* Free space of catalog label */
	lbl = gtk_label_new (_( "Total Free Space : "));
	tempstr = gw_ld_byte_to_str_format ( ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_free ( gw_am_get_current_catalog_context ( )));
	text = g_strconcat ( _( "Total Free Space : "), tempstr, NULL);
	if (tempstr) {
		g_free (tempstr);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Horizontal box for statistics */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* Statistics label */
	lbl = gtk_label_new ( _( "Disk Statistics : "));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* 3th horizontal box */
	hb_3 = gtk_hbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_3, FALSE, FALSE, 0);

	/* 1st vertical box of the 3th horizontal box */
	vb_3_1 = gtk_vbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( hb_3), vb_3_1, TRUE, TRUE, 0);

	/* Horizontal box for CD-Roms statistics */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_3_1), hb_empty, TRUE, TRUE, 0);

	/* CD-Roms statistics label */
	lbl = gtk_label_new (_( "CD-Rom : "));

	text = g_strdup_printf ( _( "CD-Rom : %d"), gw_helper_db_catalog_get_nb_db_disk_of_type ( gw_am_get_current_catalog_context ( ), CDROM));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for Audio CD statistics */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_3_1), hb_empty, TRUE, TRUE, 0);

	/* Audio CD statistics label */
	lbl = gtk_label_new (_( "Audio CD : "));

	text = g_strdup_printf ( _( "Audio CD : %d"), gw_helper_db_catalog_get_nb_db_disk_of_type ( gw_am_get_current_catalog_context ( ), AUDIOCD));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for HDs statistics */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_3_1), hb_empty, TRUE, TRUE, 0);

	/* HDs statistics label */
	lbl = gtk_label_new (_( "HD : "));

	text = g_strdup_printf ( _( "HD : %d"), gw_helper_db_catalog_get_nb_db_disk_of_type ( gw_am_get_current_catalog_context ( ), HD));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for floppies statistics */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_3_1), hb_empty, TRUE, TRUE, 0);

	/* Floppies statistics label */
	lbl = gtk_label_new (_( "Floppy : "));

	text = g_strdup_printf ( _( "Floppy : %d"), gw_helper_db_catalog_get_nb_db_disk_of_type ( gw_am_get_current_catalog_context ( ), FLOPPY));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for Zips statistics */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_3_1), hb_empty, TRUE, TRUE, 0);

	/* Zips statistics label */
	lbl = gtk_label_new (_( "Zip : "));

	text = g_strdup_printf ( _( "Zip : %d"), gw_helper_db_catalog_get_nb_db_disk_of_type ( gw_am_get_current_catalog_context ( ), ZIP_DRIVE));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* 2nd vertical box of 3th horizontal box */
	vb_3_2 = gtk_vbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( hb_3), vb_3_2, TRUE, TRUE, 0);

	/* Horizontal box for tapes statistics */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_3_2), hb_empty, TRUE, TRUE, 0);

	/* Tape drive statistics label */
	lbl = gtk_label_new (_( "Tape : "));

	text = g_strdup_printf ( _( "Tape : %d"), gw_helper_db_catalog_get_nb_db_disk_of_type ( gw_am_get_current_catalog_context ( ), TAPE_DRIVE));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for network statistics */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_3_2), hb_empty, TRUE, TRUE, 0);

	/* Network drive statistics label */
	lbl = gtk_label_new (_( "Network : "));

	text = g_strdup_printf ( _( "Network : %d"), gw_helper_db_catalog_get_nb_db_disk_of_type ( gw_am_get_current_catalog_context ( ), NETWORK_DRIVE));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for Jaz statistics */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_3_2), hb_empty, TRUE, TRUE, 0);

	/* Jaz statistics label */
	lbl = gtk_label_new (_( "Jaz : "));

	text = g_strdup_printf ( _( "Jaz : %d"), gw_helper_db_catalog_get_nb_db_disk_of_type ( gw_am_get_current_catalog_context ( ), JAZ_DRIVE));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for others media */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_3_2), hb_empty, TRUE, TRUE, 0);

	/* Others media statistics label */
	lbl = gtk_label_new (_( "Other : "));

	text = g_strdup_printf ( _( "Other : %d"), gw_helper_db_catalog_get_nb_db_disk_of_type ( gw_am_get_current_catalog_context ( ), NONE));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_3_2), hb_empty, TRUE, TRUE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Combo box for categories list */
	cmb_categories = gw_combo_box_categories_create ( w, _( "Catalog categories : "), catalog);
	gw_combo_box_categories_load ( cmb_categories);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), GTK_WIDGET ( cmb_categories), FALSE, FALSE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Horizontal box for description */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* Title description label */
	lbl = gtk_label_new (_( "Catalog Description : "));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Text area scrollbar */
	scrolled_area = gtk_scrolled_window_new ( NULL, NULL);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), scrolled_area, TRUE, TRUE, 0);
	gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scrolled_area), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

	/* Text area for description */
	text_area = gtk_text_area_new ( );
	gtk_text_area_set_editable ( GTK_TEXT_AREA ( text_area), TRUE);
	if ( (text = gw_db_catalog_get_description ( catalog)) != NULL) {
		gtk_text_area_insert ( GTK_TEXT_AREA ( text_area), text);
	}

	g_object_ref ( text_area);
	g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_CATALOG_DESCRIPTION_TEXT, text_area, (GDestroyNotify) g_object_unref);
	gtk_container_add ( GTK_CONTAINER ( scrolled_area), text_area);

	/* Tabbed pane label */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	pix_ico_catalog = gtk_pixmap_new ( PixCatalog, MskCatalog);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), pix_ico_catalog, FALSE, TRUE, 0);
	gtk_misc_set_padding ( GTK_MISC ( pix_ico_catalog), 3, 1);

	lbl = gtk_label_new (_( "Catalog Info"));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, TRUE, 0);

	gtk_widget_show_all ( hb_empty);
	gtk_notebook_set_tab_label ( GTK_NOTEBOOK ( parent), vb_tabbed_pane, hb_empty);

	return parent;
}


GtkNotebook * gw_properties_box_create_notebook_panel_disk_info ( GtkWindow *w, GtkNotebook *parent, GtkCTree *ctree, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBDisk *disk) {
	GtkWidget *vb_tabbed_pane; /* Vertical box of the tabbed pane */
	GtkWidget *hb_1; /* 1st horizontal box */
	GtkWidget *hb_2; /* 2nd horizontal box */
	GtkWidget *vb_2_1; /* 1st vertical box of 2nd horizontal box*/
	GtkWidget *vb_2_2; /* 2nd vertival box of 2nd horizontal box */
	GtkWidget *pix_ico_disk; /* disk icon */
	GtkWidget *hb_empty; /* horizontal box (used for empty box) */
	GtkWidget *lbl; /* label */
	GtkWidget *entry; /* entry (filled area) */
	GtkWidget *hseparator; /* horizontal separator */
	GtkWidget *scrolled_area; /* scrolled window for text area */
	GtkWidget *text_area; /* text area */
	GtkBox *cmb_categories;	/* Categories combo box */
	gchar *text;
	GdkPixmap *pix;
	GdkBitmap *msk;
	gchar *tempstr = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

//	disk = gtk_ctree_node_get_row_data ( ctree, node);
	pix = gw_helper_db_disk_get_pixmap ( disk);
	msk = gw_helper_db_disk_get_bitmap ( disk);

	/* Vertical box of the tabbed pane */
	vb_tabbed_pane = gtk_vbox_new ( FALSE, 5);
	gtk_container_set_border_width ( GTK_CONTAINER ( vb_tabbed_pane), 10);
	gtk_container_add ( GTK_CONTAINER ( parent), vb_tabbed_pane);

	/* 1st horizontal box */
	hb_1 = gtk_hbox_new ( FALSE, 5);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_1), 5);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_1, FALSE, FALSE, 0);

	/* Disk icon */
	pix_ico_disk = gtk_pixmap_new ( pix, msk);
	gtk_box_pack_start ( GTK_BOX ( hb_1), pix_ico_disk, FALSE, TRUE, 10);

	/* Filled area of disk name */
	entry = gtk_entry_new ( );
	gtk_entry_set_text ( GTK_ENTRY ( entry), gw_db_disk_get_name ( disk));
	g_object_ref ( entry);
	g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_DISK_NAME_ENTRY, entry, (GDestroyNotify) g_object_unref);
	gtk_box_pack_start ( GTK_BOX ( hb_1), entry, FALSE, TRUE, 0);
	gtk_widget_set_tooltip_text (entry, _( "Enter the name of the disk."));

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( hb_1), hb_empty, TRUE, TRUE, 0);

	/* Horizontal box for number archive */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( hb_1), hb_empty, FALSE, TRUE, 0);

	/* Number archive label */
	lbl = gtk_label_new (_( "Archive N# : "));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, TRUE, 0);

	/* Filled area of number archive */
	entry = gtk_entry_new ( );
	text = g_strdup_printf ( "%d", gw_db_disk_get_num ( disk));
	gtk_entry_set_text ( GTK_ENTRY ( entry), text);
	g_free ( text);
	g_object_ref ( entry);
	g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_DISK_NUMBER_ARCHIVE_ENTRY, entry, (GDestroyNotify) g_object_unref);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), entry, FALSE, TRUE, 0);
	gtk_widget_set_size_request ( entry, 40, 20);
	gtk_widget_set_tooltip_text (entry, _( "Enter the archive number of the disk."));

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* 2nd horizontal box */
	hb_2 = gtk_hbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_2, FALSE, FALSE, 0);

	/* 1st vertical box of the 2nd horizontal box */
	vb_2_1 = gtk_vbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( hb_2), vb_2_1, TRUE, TRUE, 0);

	/* Horizontal box for disk type */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, FALSE, 0);

	/* Disk type label */
	lbl = gtk_label_new (_(" Type : "));
	text = g_strconcat ( _( "Type : "), gw_db_disk_get_fstype ( disk), NULL);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for disk serial number */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, FALSE, FALSE, 0);

	/* Disk serial number label */
	lbl = gtk_label_new (_( "Serial : "));
	text = g_strconcat ( _( "Serial : "), gw_db_disk_get_serial ( disk), NULL);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for disk volume name */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, FALSE, FALSE, 0);

	/* Disk volume name label */
	lbl = gtk_label_new (_( "Volume Label : "));
	text = g_strconcat ( _( "Volume Label : "), gw_db_disk_get_volume ( disk), NULL);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for total number of files of disk */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, FALSE, FALSE, 0);

	/* Total number of files of disk label */
	lbl = gtk_label_new (_( "Total Files : "));
	text = g_strdup_printf ( _( "Total Files : %ld"), ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_disk_get_nb_db_files ( gw_am_get_current_catalog_context ( ), gw_db_disk_get_ref ( disk)));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for total number of folders of disk */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, FALSE, FALSE, 0);

	/* Total number of folders of disk label */
	lbl = gtk_label_new (_( "Total Folders : "));
	text = g_strdup_printf ( _( "Total Folders : %ld"), ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_disk_get_nb_db_folders ( gw_am_get_current_catalog_context ( ), gw_db_disk_get_ref ( disk)));
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* 2nd vertical box of the 2nd horizontal box */
	vb_2_2 = gtk_vbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( hb_2), vb_2_2, TRUE, TRUE, 0);

	/* Horizontal box for total capacity of disk */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, FALSE, FALSE, 0);

	/* Total capacity of disk label */
	lbl = gtk_label_new (_( "Total Capacity : "));
	tempstr = gw_ui64_byte_to_str_format ( gw_db_disk_get_capacity ( disk));
	text = g_strconcat ( _( "Total Capacity : "), tempstr, NULL);
	if (tempstr) {
		g_free (tempstr);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for used space of disk */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, FALSE, FALSE, 0);

	/* Used space of disk label */
	lbl = gtk_label_new (_( "Used Space : "));
	tempstr = gw_ui64_byte_to_str_format ( gw_db_disk_get_full ( disk));
	text = g_strconcat ( _( "Used Space : "), tempstr, NULL);
	if (tempstr) {
		g_free (tempstr);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for free space of disk */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, FALSE, FALSE, 0);

	/* Free space of disk label */
	lbl = gtk_label_new (_( "Free Space : "));
	tempstr = gw_ui64_byte_to_str_format ( gw_db_disk_get_free ( disk));
	text = g_strconcat ( _( "Free Space : "), tempstr, NULL);
	if (tempstr) {
		g_free (tempstr);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, FALSE, FALSE, 0);

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, FALSE, FALSE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Horizontal box for catalog name */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* Catalog name label */
	lbl = gtk_label_new (_( "Catalog Name : "));
	if ( gw_db_catalog_get_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_name ( catalog))>0) {
		text = g_strconcat ( _( "Catalog Name : "), gw_db_catalog_get_name ( catalog), NULL);
	} else if ( gw_db_catalog_get_short_db_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_short_db_name ( catalog))>0) {
		text = g_strconcat ( _( "Catalog Name : "), gw_db_catalog_get_short_db_name ( catalog), NULL);
	} else {
		text = g_strconcat ( _( "Catalog Name : "), _( "none"), NULL);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for adding date of disk */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* Adding date label of disk */
	lbl = gtk_label_new (_( "Update in catalog : "));
	tempstr = gw_helper_db_disk_get_date_to_str ( disk);
	text = g_strconcat ( _( "Update in catalog : "), tempstr, NULL);
	g_free (tempstr);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Combo box for categories list */
	cmb_categories = gw_combo_box_categories_create ( w, _( "Category : "), catalog);
	g_object_ref ( GTK_WIDGET ( cmb_categories));
	g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_DISK_CATEGORIES_CMB_BOX, GTK_WIDGET ( cmb_categories), (GDestroyNotify) g_object_unref);
	gw_combo_box_categories_load ( cmb_categories);
	gw_combo_box_categories_set_selected_category ( cmb_categories, gw_db_disk_get_category ( disk));
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), GTK_WIDGET ( cmb_categories), FALSE, FALSE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Horizontal box for description */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* Title description label */
	lbl = gtk_label_new (_( "Disk Description : "));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Text area scrollbar */
	scrolled_area = gtk_scrolled_window_new ( NULL, NULL);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), scrolled_area, TRUE, TRUE, 0);
	gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scrolled_area), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

	/* Text area for description */
	text_area = gtk_text_area_new ( );
	gtk_text_area_set_editable ( GTK_TEXT_AREA ( text_area), TRUE);
	if ( (text = gw_db_disk_get_description ( disk)) != NULL) {
		gtk_text_area_insert ( GTK_TEXT_AREA ( text_area), text);
	}

	g_object_ref ( text_area);
	g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_DISK_DESCRIPTION_TEXT, text_area, (GDestroyNotify) g_object_unref);
	gtk_container_add ( GTK_CONTAINER ( scrolled_area), text_area);

	/* Tabbed pane label */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	pix_ico_disk = gtk_pixmap_new ( pix, msk);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), pix_ico_disk, FALSE, TRUE, 0);
	gtk_misc_set_padding ( GTK_MISC ( pix_ico_disk), 3, 1);

	lbl = gtk_label_new (_( "Disk Info"));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, TRUE, 0);

	gtk_widget_show_all ( hb_empty);
	gtk_notebook_set_tab_label ( GTK_NOTEBOOK ( parent), vb_tabbed_pane, hb_empty);

	return parent;
}


//GtkNotebook * gw_properties_box_create_notebook_panel_folder_info ( GtkWindow *w, GtkNotebook *parent, GtkCTree *ctree, GtkCTreeNode *node, GWDBCatalog *catalog) {
GtkNotebook * gw_properties_box_create_notebook_panel_folder_info ( GtkWindow *w, GtkNotebook *parent, GWDBCatalog *catalog, GWDBDisk *disk, GWDBFile *folder) {
	GtkWidget *vb_tabbed_pane; /* Vertical box of the tabbed pane */
	GtkWidget *hb_1; /* 1st horizontal box */
	GtkWidget *hb_2; /* 2nd horizontal box */
	GtkWidget *vb_2_1; /* 1st vertical box of 2nd horizontal box*/
	GtkWidget *vb_2_2; /* 2nd vertival box of 2nd horizontal box */
	GtkWidget *pix_ico_folder; /* folder icon */
	GtkWidget *hb_empty; /* horizontal box (used for empty box) */
	GtkWidget *lbl; /* label */
	GtkWidget *hseparator; /* horizontal separator */
	GtkWidget *scrolled_area; /* scrolled window for text area */
	GtkWidget *text_area; /* text area */
	GtkBox *cmb_categories;	/* Categories combo box */
	gchar *text;
	gchar *tempstr = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Vertical box of the tabbed pane */
	vb_tabbed_pane = gtk_vbox_new ( FALSE, 5);
	gtk_container_set_border_width ( GTK_CONTAINER ( vb_tabbed_pane), 10);
	gtk_container_add ( GTK_CONTAINER ( parent), vb_tabbed_pane);

	/* 1st horizontal box */
	hb_1 = gtk_hbox_new ( FALSE, 5);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_1), 5);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_1, FALSE, FALSE, 0);

	/* Folder icon */
	pix_ico_folder = gtk_pixmap_new ( PixFolder, MskFolder);
	gtk_box_pack_start ( GTK_BOX ( hb_1), pix_ico_folder, FALSE, TRUE, 10);

	/* Folder name label */
	lbl = gtk_label_new (_( "Folder Name"));
	gtk_label_set_text ( GTK_LABEL ( lbl), gw_db_file_get_name ( folder));
	gtk_box_pack_start ( GTK_BOX ( hb_1), lbl, FALSE, TRUE, 0);

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( hb_1), hb_empty, TRUE, TRUE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* 2nd horizontal box */
	hb_2 = gtk_hbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_2, FALSE, FALSE, 0);

	/* 1st vertical box of the 2nd horizontal box */
	vb_2_1 = gtk_vbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( hb_2), vb_2_1, TRUE, TRUE, 0);

	/* Horizontal box for the folder type */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* The folder type label */
	lbl = gtk_label_new (_( "Type : (folder)"));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for the folder size */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* The folder size label */
	lbl = gtk_label_new (_( "Folder Size : "));
	tempstr = gw_l_byte_to_str_format ( gw_db_file_get_size ( folder));
	text = g_strconcat ( _( "Folder Size : "), tempstr, NULL);
	if (tempstr) {
		g_free (tempstr);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for the folder creation date */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* The folder creation date label */
	lbl = gtk_label_new (_( "Created on : "));
	tempstr = gw_helper_db_file_get_cdate_to_str ( folder);
	text = g_strconcat ( _( "Created on : "), tempstr, NULL);
	g_free (tempstr);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for the folder last update date */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* the folder last update date label */
	lbl = gtk_label_new (_( "Last modified on : "));
	tempstr = gw_helper_db_file_get_mdate_to_str ( folder);
	text = g_strconcat ( _( "Last modified on : "), tempstr, NULL);
	g_free ( tempstr);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for the folder last access date */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* The folder last access date label */
	lbl = gtk_label_new (_( "Last accessed on : "));
	tempstr = gw_helper_db_file_get_adate_to_str ( folder);
	text = g_strconcat ( _( "Last accessed on : "), tempstr, NULL);
	g_free ( tempstr);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* 2nd vertical box of the 2nd horizontal box */
	vb_2_2 = gtk_vbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( hb_2), vb_2_2, TRUE, TRUE, 0);

	/* Horizontal box for the folder rights */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* Folder rights label */
	lbl = gtk_label_new (_( "Rights : "));
	tempstr = gw_db_file_get_rights_to_gchar ( folder);
	text = g_strconcat ( _( "Rights : "), tempstr, NULL);
	g_free (tempstr);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for the folder owner name */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* The folder owner name label */
	lbl = gtk_label_new (_( "Owner : "));
	if ( (gw_db_file_get_owner ( folder) == NULL) || (strlen ( gw_db_file_get_owner ( folder)) == 0) ) {
		text = g_strconcat ( _( "Owner : "), _( "unknown owner"), NULL);
	} else {
		text = g_strconcat ( _( "Owner : "), gw_db_file_get_owner ( folder), NULL);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for the folder group name */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* The folder group name label */
	lbl = gtk_label_new (_( "Group : "));
	if ( (gw_db_file_get_group ( folder) == NULL) || (strlen ( gw_db_file_get_group ( folder)) == 0) ) {
		text = g_strconcat ( _( "Group : "), _( "unknown group"), NULL);
	} else {
		text = g_strconcat ( _( "Group : "), gw_db_file_get_group ( folder), NULL);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Horizontal box for the disk name */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* Disk name label */
	lbl = gtk_label_new (_( "Disk Name : "));
	text = g_strconcat ( _( "Disk Name : "), gw_db_disk_get_name ( disk), " (", gw_db_disk_get_fstype ( disk), ")", NULL);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for the folder location */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* The folder location label */
	lbl = gtk_label_new (_( "Location on Disk : "));
	tempstr = ((GWCatalogPlugin*) gw_db_context_get_plugin (gw_am_get_current_catalog_context( )))->gw_db_file_get_location (gw_am_get_current_catalog_context(), gw_db_file_get_ref (folder));
	text = g_strconcat ( _( "Location on Disk : "), tempstr, NULL);
	if (tempstr) {
		g_free (tempstr);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Combo box for categories list */
	cmb_categories = gw_combo_box_categories_create ( w, _( "Category : "), catalog);
	g_object_ref ( GTK_WIDGET ( cmb_categories));
	g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_FOLDER_CATEGORIES_CMB_BOX, GTK_WIDGET ( cmb_categories), (GDestroyNotify) g_object_unref);
	gw_combo_box_categories_load ( cmb_categories);
	gw_combo_box_categories_set_selected_category ( cmb_categories, gw_db_file_get_category ( folder));
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), GTK_WIDGET ( cmb_categories), FALSE, FALSE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Horizontal box for description */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* Title description label */
	lbl = gtk_label_new (_( "Folder Description : "));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Text area scrollbar */
	scrolled_area = gtk_scrolled_window_new ( NULL, NULL);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), scrolled_area, TRUE, TRUE, 0);
	gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scrolled_area), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

	/* Text area for description */
	text_area = gtk_text_area_new ( );
	gtk_text_area_set_editable ( GTK_TEXT_AREA ( text_area), TRUE);
	if ( (text = gw_db_file_get_description ( folder)) != NULL) {
		gtk_text_area_insert ( GTK_TEXT_AREA ( text_area), text);
	}

	g_object_ref ( text_area);
	g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_FOLDER_DESCRIPTION_TEXT, text_area, (GDestroyNotify) g_object_unref);
	gtk_container_add ( GTK_CONTAINER ( scrolled_area), text_area);

	/* Tabbed pane label */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	pix_ico_folder = gtk_pixmap_new ( PixFolder, MskFolder);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), pix_ico_folder, FALSE, TRUE, 0);
	gtk_misc_set_padding ( GTK_MISC ( pix_ico_folder), 3, 1);

	lbl = gtk_label_new (_( "Folder Info"));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, TRUE, 0);

	gtk_widget_show_all ( hb_empty);
	gtk_notebook_set_tab_label ( GTK_NOTEBOOK ( parent), vb_tabbed_pane, hb_empty);

	return parent;
}


GtkNotebook * gw_properties_box_create_notebook_panel_file_info ( GtkWindow *w, GtkNotebook *parent, GtkCTree *ctree, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBFile *file) {
	GtkWidget *vb_tabbed_pane; /* Vertical box of the tabbed pane */
	GtkWidget *hb_1; /* 1st horizontal box */
	GtkWidget *hb_2; /* 2nd horizontal box */
	GtkWidget *vb_2_1; /* 1st vertical box of 2nd horizontal box*/
	GtkWidget *vb_2_2; /* 2nd vertival box of 2nd horizontal box */
	GtkWidget *pix_ico_file; /* file icon */
	GtkWidget *hb_empty; /* horizontal box (used for empty box) */
	GtkWidget *lbl; /* label */
	GtkWidget *hseparator; /* horizontal separator */
	GtkWidget *scrolled_area; /* scrolled window for text area */
	GtkWidget *text_area; /* text area */
	GtkBox *cmb_categories;	/* Categories combo box */
	gchar *text;
	gchar *tempstr = NULL;
	gchar *tmp = NULL;
	GWDBDisk *disk = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Vertical box of the tabbed pane */
	vb_tabbed_pane = gtk_vbox_new ( FALSE, 5);
	gtk_container_set_border_width ( GTK_CONTAINER ( vb_tabbed_pane), 10);
	gtk_container_add ( GTK_CONTAINER ( parent), vb_tabbed_pane);

	/* 1st horizontal box */
	hb_1 = gtk_hbox_new ( FALSE, 5);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_1), 5);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_1, FALSE, FALSE, 0);

	/* File icon */
	pix_ico_file = gtk_pixmap_new ( PixFile, MskFile);
	gtk_box_pack_start ( GTK_BOX ( hb_1), pix_ico_file, FALSE, TRUE, 10);

	/* Folder name label */
	lbl = gtk_label_new (_( "File name : "));
	gtk_label_set_text ( GTK_LABEL ( lbl), gw_db_file_get_name ( file));
	gtk_box_pack_start ( GTK_BOX ( hb_1), lbl, FALSE, TRUE, 0);

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( hb_1), hb_empty, TRUE, TRUE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* 2nd horizontal box */
	hb_2 = gtk_hbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_2, FALSE, FALSE, 0);

	/* 1st vertical box of the 2nd horizontal box */
	vb_2_1 = gtk_vbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( hb_2), vb_2_1, TRUE, TRUE, 0);

	/* Horizontal box for file type */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* The file type label */
	lbl = gtk_label_new (_( "File type : not yet implemented!!"));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for file size */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* The file size label */
	lbl = gtk_label_new (_( "File Size : "));
	tempstr = gw_l_byte_to_str_format ( gw_db_file_get_size ( file));
	tmp = gw_ui64_byte_to_str_format ( gw_db_file_get_size ( file));
	text = g_strdup_printf ( _( "File Size : %s (%s bytes)"), tempstr, tmp);
	if (tempstr) {
		g_free (tempstr);
	}
	if ( tmp != NULL ) {
		g_free ( tmp);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for file creation date */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* The file creation date label */
	lbl = gtk_label_new (_( "Created on : "));
	tempstr = gw_helper_db_file_get_cdate_to_str ( file);
	text = g_strconcat ( _( "Created on : "), tempstr, NULL);
	g_free ( tempstr);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for file last modification date */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* The file last modification date lalbel */
	lbl = gtk_label_new (_( "Last modified on : "));
	tempstr = gw_helper_db_file_get_mdate_to_str ( file);
	text = g_strconcat ( _( "Last modified on : "), tempstr, NULL);
	g_free ( tempstr);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for file last access date */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_1), hb_empty, TRUE, TRUE, 0);

	/* The file last access date label */
	lbl = gtk_label_new (_( "Last accessed on : "));
	tempstr = gw_helper_db_file_get_adate_to_str ( file);
	text = g_strconcat ( _( "Last accessed on : "), tempstr, NULL);
	g_free ( tempstr);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* 2nd vertical box of the 2nd horizontal box */
	vb_2_2 = gtk_vbox_new ( TRUE, 0);
	gtk_box_pack_start ( GTK_BOX ( hb_2), vb_2_2, TRUE, TRUE, 0);

	/* Horizontal box for file rights */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* the file rights label */
	lbl = gtk_label_new (_( "Rights : "));
	tempstr = gw_db_file_get_rights_to_gchar ( file);
	text = g_strconcat ( _( "Rights : "), tempstr, NULL);
	g_free ( tempstr);
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for file owner name */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* The file owner name label */
	lbl = gtk_label_new (_( "Owner : "));
	if ( (gw_db_file_get_owner ( file) == NULL) || (strlen ( gw_db_file_get_owner ( file)) == 0) ) {
		text = g_strconcat ( _( "Owner : "), _( "unknown owner"), NULL);
	} else {
		text = g_strconcat ( _( "Owner : "), gw_db_file_get_owner ( file), NULL);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for file group name */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* File group name label */
	lbl = gtk_label_new (_( "Group : "));
	if ( (gw_db_file_get_group ( file) == NULL) || (strlen ( gw_db_file_get_group ( file)) == 0) ) {
		text = g_strconcat ( _( "Group : "), _( "unknown group"), NULL);
	} else {
		text = g_strconcat ( _( "Group : "), gw_db_file_get_group ( file), NULL);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free (text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* Empty horizontal box */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_2_2), hb_empty, TRUE, TRUE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Horizontal box for disk name */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* The disk name label */
	lbl = gtk_label_new (_( "Disk Name : "));
	disk = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_file_get_db_disk ( gw_am_get_current_catalog_context ( ), gw_db_file_get_ref ( file));
	text = g_strconcat ( _( "Disk Name : "), gw_db_disk_get_name ( disk), " (", gw_db_disk_get_fstype ( disk), ")", NULL);
	gw_db_disk_free ( disk);

	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free ( text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Horizontal box for the file location */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* The file location label */
	lbl = gtk_label_new (_( "Location on Disk : "));
	tempstr = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_file_get_location ( gw_am_get_current_catalog_context ( ), gw_db_file_get_ref ( file));
	text = g_strconcat ( _( "Location on Disk : "), tempstr, NULL);
	if (tempstr) {
		g_free (tempstr);
	}
	gtk_label_set_text ( GTK_LABEL ( lbl), text);
	g_free (text);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Combo box for categories list */
	cmb_categories = gw_combo_box_categories_create ( w, _( "Category : "), catalog);
	g_object_ref ( GTK_WIDGET ( cmb_categories));
	g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_FILE_CATEGORIES_CMB_BOX, GTK_WIDGET ( cmb_categories), (GDestroyNotify) g_object_unref);
	gw_combo_box_categories_load ( cmb_categories);
	gw_combo_box_categories_set_selected_category ( cmb_categories, gw_db_file_get_category ( file));
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), GTK_WIDGET ( cmb_categories), FALSE, FALSE, 0);

	/* Separator */
	hseparator = gtk_hseparator_new ( );
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hseparator, FALSE, FALSE, 0);

	/* Horizontal box for description */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_empty), 2);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_empty, FALSE, FALSE, 0);

	/* Title description label */
	lbl = gtk_label_new (_( "File Description : "));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, FALSE, 0);

	/* Text area scrollbar */
	scrolled_area = gtk_scrolled_window_new ( NULL, NULL);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), scrolled_area, TRUE, TRUE, 0);
	gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scrolled_area), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

	/* Text area for description */
	text_area = gtk_text_area_new ( );
	gtk_text_area_set_editable ( GTK_TEXT_AREA ( text_area), TRUE);
	if ( (text = gw_db_file_get_description ( file)) != NULL) {
		gtk_text_area_insert ( GTK_TEXT_AREA ( text_area), text);
	}

	g_object_ref ( text_area);
	g_object_set_data_full (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_FILE_DESCRIPTION_TEXT, text_area, (GDestroyNotify) g_object_unref);
	gtk_container_add ( GTK_CONTAINER ( scrolled_area), text_area);

	/* Tabbed pane label */
	hb_empty = gtk_hbox_new ( FALSE, 0);
	pix_ico_file = gtk_pixmap_new ( PixFile, MskFile);
	gtk_box_pack_start ( GTK_BOX ( hb_empty), pix_ico_file, FALSE, TRUE, 0);
	gtk_misc_set_padding ( GTK_MISC ( pix_ico_file), 3, 1);

	lbl = gtk_label_new (_( "File Info"));
	gtk_box_pack_start ( GTK_BOX ( hb_empty), lbl, FALSE, TRUE, 0);

	gtk_widget_show_all ( hb_empty);
	gtk_notebook_set_tab_label ( GTK_NOTEBOOK ( parent), vb_tabbed_pane, hb_empty);

	return parent;
}


gchar * gw_properties_box_get_catalog_name ( GtkWidget *w) {
	GtkEntry *entry = NULL;
	gchar *catalog_name = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		entry = g_object_get_data (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_CATALOG_NAME_ENTRY);

		if ( entry != NULL ) {
			g_strdup_from_gtk_text ( gtk_entry_get_text ( entry), catalog_name);
		} else {}
	} else {}

	return catalog_name;
}


gchar * gw_properties_box_get_catalog_description ( GtkWidget *w)
{
	GtkTextArea *text_area = NULL;
	gchar *catalog_description = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		text_area = g_object_get_data (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_CATALOG_DESCRIPTION_TEXT);

		if ( text_area != NULL )
		{
			catalog_description = gtk_text_area_get_text ( GTK_TEXT_AREA ( text_area));
		}
	}

	return catalog_description;
}


gchar * gw_properties_box_get_disk_name ( GtkWidget *w)
{
	GtkWidget *entry = NULL;
	gchar *disk_name = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		entry = g_object_get_data (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_DISK_NAME_ENTRY);

		if ( entry != NULL )
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), disk_name);
		}
	}

	return disk_name;
}


gchar * gw_properties_box_get_disk_num ( GtkWidget *w)
{
	GtkWidget *entry = NULL;
	gchar *disk_num = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		entry = g_object_get_data (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_DISK_NUMBER_ARCHIVE_ENTRY);

		if ( entry != NULL )
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), disk_num);
		}
	}

	return disk_num;
}


GWDBCategoryPK gw_properties_box_get_disk_category_ref ( GtkWidget *w) {
	GtkWidget *cmb_box_categories = NULL;
	GWDBCategory *category = NULL;
	GWDBCategoryPK ref = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (cmb_box_categories = g_object_get_data (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_DISK_CATEGORIES_CMB_BOX)) != NULL) {
			if ( (category = gw_combo_box_categories_get_selected_category ( GTK_BOX ( cmb_box_categories))) != NULL ) {
				ref = gw_db_category_get_ref ( category);
				gw_db_category_free ( category);
			}
		}
	}

	return ref;
}


gchar * gw_properties_box_get_disk_description ( GtkWidget *w)
{
	GtkTextArea *text_area = NULL;
	gchar *disk_description = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		text_area = g_object_get_data (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_DISK_DESCRIPTION_TEXT);

		if ( text_area != NULL )
		{
			disk_description = gtk_text_area_get_text ( GTK_TEXT_AREA ( text_area));
		}
	}

	return disk_description;
}


GWDBCategoryPK gw_properties_box_get_folder_category_ref ( GtkWidget *w) {
	GtkWidget *cmb_box_categories = NULL;
	GWDBCategory *category = NULL;
	GWDBCategoryPK ref = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (cmb_box_categories = g_object_get_data (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_FOLDER_CATEGORIES_CMB_BOX)) != NULL ) {
			if ( (category = gw_combo_box_categories_get_selected_category ( GTK_BOX ( cmb_box_categories))) != NULL ) {
				ref = gw_db_category_get_ref ( category);
				gw_db_category_free ( category);
			}
		}
	}

	return ref;
}


gchar * gw_properties_box_get_folder_description ( GtkWidget *w)
{
	GtkTextArea *text_area = NULL;
	gchar *folder_description = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		text_area = g_object_get_data (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_FOLDER_DESCRIPTION_TEXT);

		if ( text_area != NULL )
		{
			folder_description = gtk_text_area_get_text ( GTK_TEXT_AREA ( text_area));
		}
	}

	return folder_description;
}


GWDBCategoryPK gw_properties_box_get_file_category_ref ( GtkWidget *w) {
	GtkWidget *cmb_box_categories = NULL;
	GWDBCategory *category = NULL;
	GWDBCategoryPK ref = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (cmb_box_categories = g_object_get_data (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_FILE_CATEGORIES_CMB_BOX)) != NULL) {
			if ( (category = gw_combo_box_categories_get_selected_category ( GTK_BOX ( cmb_box_categories))) != NULL ) {
				ref = gw_db_category_get_ref ( category);
				gw_db_category_free ( category);
			}
		}
	}

	return ref;
}


gchar * gw_properties_box_get_file_description ( GtkWidget *w)
{
	GtkTextArea *entry = NULL;
	gchar *file_description = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		entry = g_object_get_data (G_OBJECT ( w), GW_REF_PROPERTIES_BOX_FILE_DESCRIPTION_TEXT);

		if ( entry != NULL )
		{
			file_description = gtk_text_area_get_text ( GTK_TEXT_AREA ( entry));
		}
	}

	return file_description;
}
