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
#include "gwnotebookcatalog.h"

#include <string.h> /* strcmp */

#include "gwnotebookcatalogcallback.h"
#include "gwmenupopup.h"
#include "gwnotebooksearch.h"
#include "gwnotebookmanagmentcallback.h"
#include "gwstatusbar.h"
#include "gwreferences.h"

#include "../gwguimanager.h"
#include "../gwapplicationmanager.h"


/*! @define	GW_REF_NOTEBOOK_CATALOG_PANE	The catalog pane */
#define GW_REF_NOTEBOOK_CATALOG_PANE "gw_ref_gw_notebook_catalog_pane"
/*! @define	GW_REF_NOTEBOOK_CATALOG_ARCHIVE_LABEL	The the archive label in the scrollpane */
#define GW_REF_NOTEBOOK_CATALOG_ARCHIVE_LABEL "gw_ref_gw_notebook_catalog_archive_label"
/*! @define	GW_REF_NOTEBOOK_CATALOG_TREE_SCROLLPANE	The tree scrollpane */
#define GW_REF_NOTEBOOK_CATALOG_TREE_SCROLLPANE "gw_ref_gw_notebook_catalog_tree_scrollpane"
/*! @define	GW_REF_NOTEBOOK_CATALOG_LIST_SCROLLPANE	The list scrollpane */
#define GW_REF_NOTEBOOK_CATALOG_LIST_SCROLLPANE "gw_ref_gw_notebook_catalog_list_scrollpane"
/*! @define	GW_REF_NOTEBOOK_CATALOG_TABBED_PANE_LABEL	The pabbed pane title */
#define GW_REF_NOTEBOOK_CATALOG_TABBED_PANE_LABEL "gw_ref_gw_notebook_catalog_tabbed_pane_label"


GtkWidget * gw_notebook_catalog_create ( GtkWindow * window) {
	GtkCList *clist_info = NULL;
	GtkWidget *hpan_catalog;
	GtkWidget *lbl_archive;
	GtkWidget *scr_win_ctree, *scr_win_info_catalog;
	GtkWidget *ctree_catalog, *clist_info_catalog;
	GtkWidget *lbl_col00, *lbl_col01, *lbl_col02, *lbl_col03, *lbl_col04, *lbl_col05, *lbl_col06, *lbl_col07, *lbl_col08, *lbl_col09, *lbl_col10, *lbl_col11;
	gchar *text_utf8 = NULL;
	gint hpan_pos = 0;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Horizontal pane for the first notebook pane.*/
	hpan_catalog = gtk_hpaned_new ( );
	gtk_widget_ref ( hpan_catalog);
	gtk_object_set_data_full ( GTK_OBJECT ( window), GW_REF_NOTEBOOK_CATALOG_PANE, hpan_catalog, (GtkDestroyNotify) gtk_widget_unref);
	/* Gets the saved value of the horizontal pane position. */
	if ( (hpan_pos = gw_am_get_settings_tod ( GW_VALUE_APP_EXPLORER_HPAN_POSITION)) == -1 ) {
		hpan_pos = GW_VALUE_APP_EXPLORER_HPAN_POSITION_DEFAULT;
	}
	gtk_paned_set_position ( GTK_PANED ( hpan_catalog), hpan_pos);

	/* Catalog tree explorer */
	scr_win_ctree = gtk_scrolled_window_new ( NULL, NULL);
	gtk_widget_ref ( scr_win_ctree);
	gtk_object_set_data_full ( GTK_OBJECT ( window), GW_REF_NOTEBOOK_CATALOG_TREE_SCROLLPANE, scr_win_ctree, (GtkDestroyNotify) gtk_widget_unref);
	gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scr_win_ctree), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_container_add ( GTK_CONTAINER ( hpan_catalog), scr_win_ctree);

	ctree_catalog = gtk_ctree_new ( 1, 0);
	gtk_widget_ref ( ctree_catalog);
	gtk_object_set_data_full ( GTK_OBJECT ( window), GW_REF_TREE, ctree_catalog, (GtkDestroyNotify) gtk_widget_unref);
	gtk_signal_connect ( GTK_OBJECT ( ctree_catalog), "button_press_event", GTK_SIGNAL_FUNC ( gw_notebook_catalog_ctree_button_press_event), NULL);
//	gtk_signal_connect ( GTK_OBJECT ( ctree_catalog), "tree_select_row", GTK_SIGNAL_FUNC ( gw_notebook_catalog_ctree_select_row), NULL);
	gtk_signal_connect_after ( GTK_OBJECT ( ctree_catalog), "tree_select_row", GTK_SIGNAL_FUNC ( gw_notebook_catalog_ctree_select_row), NULL);
	gtk_clist_set_selection_mode ( GTK_CLIST ( ctree_catalog), GTK_SELECTION_BROWSE);
	gtk_container_add ( GTK_CONTAINER ( scr_win_ctree), ctree_catalog);
	gtk_clist_set_column_width ( GTK_CLIST ( ctree_catalog), 0, 80);
	gtk_clist_set_column_auto_resize ( GTK_CLIST ( ctree_catalog), 0, TRUE);
	gtk_clist_column_titles_show ( GTK_CLIST ( ctree_catalog));
	gtk_clist_set_column_justification ( GTK_CLIST ( ctree_catalog), 0, GTK_JUSTIFY_LEFT);
	gtk_clist_set_sort_column ( GTK_CLIST ( ctree_catalog), 0);
	gtk_clist_set_sort_type ( GTK_CLIST ( ctree_catalog), GTK_SORT_ASCENDING);
	gtk_clist_set_auto_sort ( GTK_CLIST ( ctree_catalog), TRUE);

	g_strdup_to_gtk_text ( _( "Archive"), text_utf8);
	lbl_archive = gtk_label_new ( text_utf8);
	g_free ( text_utf8);
	gtk_widget_ref ( lbl_archive);
	gtk_object_set_data_full ( GTK_OBJECT ( window), GW_REF_NOTEBOOK_CATALOG_ARCHIVE_LABEL, lbl_archive,(GtkDestroyNotify) gtk_widget_unref);
	gtk_label_set_justify ( GTK_LABEL ( lbl_archive), GTK_JUSTIFY_LEFT);
	gtk_misc_set_alignment ( GTK_MISC ( lbl_archive), 0, 0.5);
	gtk_clist_set_column_widget ( GTK_CLIST ( ctree_catalog), 0, lbl_archive);

	/* List of catalog explorer. */
	scr_win_info_catalog = gtk_scrolled_window_new ( NULL, NULL);
	gtk_widget_ref ( scr_win_info_catalog);
	gtk_object_set_data_full ( GTK_OBJECT ( window), GW_REF_NOTEBOOK_CATALOG_LIST_SCROLLPANE, scr_win_info_catalog, (GtkDestroyNotify) gtk_widget_unref);
	gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scr_win_info_catalog), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_container_add ( GTK_CONTAINER ( hpan_catalog), scr_win_info_catalog);

	clist_info_catalog = gtk_clist_new ( 12);
	clist_info = GTK_CLIST ( clist_info_catalog);
	gtk_widget_ref ( clist_info_catalog);
	gtk_object_set_data_full ( GTK_OBJECT ( window), GW_REF_CLIST_EXPLORER, clist_info_catalog,(GtkDestroyNotify) gtk_widget_unref);
//	gtk_signal_connect ( GTK_OBJECT ( clist_info_catalog), "resize-column", GTK_SIGNAL_FUNC ( gw_notebook_catalog_clist_column_resized), NULL);
//	gtk_signal_connect ( GTK_OBJECT ( clist_info_catalog), "click_column", GTK_SIGNAL_FUNC ( gw_notebook_catalog_column_sort), NULL);
//	gtk_signal_connect ( GTK_OBJECT ( clist_info_catalog), "button_press_event", GTK_SIGNAL_FUNC ( gw_notebook_catalog_clist_button_press_event), NULL);
	gtk_clist_set_selection_mode ( clist_info, GTK_SELECTION_BROWSE);
	gtk_container_add ( GTK_CONTAINER ( scr_win_info_catalog), clist_info_catalog);

	gtk_clist_column_titles_show ( clist_info);
/*	gtk_clist_set_column_justification ( clist_info, 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification ( clist_info, 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification ( clist_info, 3, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification ( clist_info, 4, GTK_JUSTIFY_RIGHT);
	gtk_clist_set_column_justification ( clist_info, 5, GTK_JUSTIFY_RIGHT);
	gtk_clist_set_column_justification ( clist_info, 6, GTK_JUSTIFY_RIGHT);
	gtk_clist_set_column_justification ( clist_info, 7, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification ( clist_info, 8, GTK_JUSTIFY_LEFT);
	gtk_clist_set_column_justification ( clist_info, 9, GTK_JUSTIFY_LEFT);
	gtk_clist_set_column_justification ( clist_info, 10, GTK_JUSTIFY_LEFT);
	gtk_clist_set_column_justification ( clist_info, 11, GTK_JUSTIFY_LEFT);
*/

	gtk_clist_set_sort_column ( clist_info, 0);
	gtk_clist_set_sort_type ( clist_info, GTK_SORT_ASCENDING);
	gtk_clist_set_auto_sort ( clist_info, FALSE);

	lbl_col00 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 0, lbl_col00);

	lbl_col01 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 1, lbl_col01);

	lbl_col02 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 2, lbl_col02);

	lbl_col03 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 3, lbl_col03);

	lbl_col04 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 4, lbl_col04);

	lbl_col05 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 5, lbl_col05);

	lbl_col06 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 6, lbl_col06);

	lbl_col07 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 7, lbl_col07);

	lbl_col08 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 8, lbl_col08);

	lbl_col09 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 9, lbl_col09);

	lbl_col10 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 10, lbl_col10);

	lbl_col11 = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_info, 10, lbl_col11);

	gw_notebook_catalog_clist_explorer_set_column_title_disk ( );
	gtk_signal_connect ( GTK_OBJECT ( clist_info_catalog), "resize-column", GTK_SIGNAL_FUNC ( gw_notebook_catalog_clist_column_resized), NULL);
	gtk_signal_connect ( GTK_OBJECT ( clist_info_catalog), "click_column", GTK_SIGNAL_FUNC ( gw_notebook_catalog_column_sort), NULL);
	gtk_signal_connect ( GTK_OBJECT ( clist_info_catalog), "button_press_event", GTK_SIGNAL_FUNC ( gw_notebook_catalog_clist_button_press_event), NULL);

	return hpan_catalog;
}


GtkWidget * gw_notebook_catalog_create_and_add ( GtkWindow * window, GtkNotebook * parent) {
	GtkWidget *tabbed_pane_catalog = NULL;
	GtkWidget *catalog_tabbed_pane_label;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( window != NULL ) {
		tabbed_pane_catalog = gw_notebook_catalog_create ( window);

		if ( tabbed_pane_catalog != NULL ) {
			gtk_container_add ( GTK_CONTAINER ( parent), tabbed_pane_catalog);

			/* Text label of the search tabbed pane. */
			g_strdup_to_gtk_text ( _( "Catalog"), text_utf8);
			catalog_tabbed_pane_label = gtk_label_new ( text_utf8);
			g_free ( text_utf8);

			/* Store reference to the title of tabbed pane */
			gtk_widget_ref ( catalog_tabbed_pane_label);
			gtk_object_set_data_full ( GTK_OBJECT ( window), GW_REF_NOTEBOOK_CATALOG_TABBED_PANE_LABEL, catalog_tabbed_pane_label,(GtkDestroyNotify) gtk_widget_unref);
			gtk_notebook_set_tab_label ( parent, gtk_notebook_get_nth_page ( parent, 0), catalog_tabbed_pane_label);
		}
	}

	return tabbed_pane_catalog;
}


GtkCList * gw_notebook_catalog_get_clist_explorer ( GtkWindow *w) {
	GtkCList *clist_explorer = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		clist_explorer = GTK_CLIST ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CLIST_EXPLORER));
	}

	return clist_explorer;
}


gint gw_notebook_catalog_clist_explorer_set_column_title_file ( void) {
	GtkWindow *w = NULL;
	GtkCList *clist = NULL;
	gchar *showed = NULL;
	gchar *text_utf8 = NULL;
	gint autoresize = -1;
	gint width = -1;
	gint i = 0;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	w = gw_gui_manager_main_interface_get_main_window ( );
	clist = gw_notebook_catalog_get_clist_explorer ( w);

	if ( clist != NULL ) {
		gtk_clist_freeze ( clist);
//		gtk_signal_emit_stop_by_name ( GTK_OBJECT ( clist), "resize-column");

		/* Sets columns width. */
		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT, width);

		if ( (autoresize = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE)) == -1 ) {
			autoresize = GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE_DEFAULT;
		}

		/* Sets the autoresize mode. */
		for ( i = 0; i < 11; i++) {
			/* Enabling auto-resize on a column disallows user-resizing of the column. */
			if ( autoresize ) {
				gtk_clist_set_column_resizeable ( clist, i, FALSE);
				gtk_clist_set_column_auto_resize ( clist, i, TRUE);
			} else {
				gtk_clist_set_column_auto_resize ( clist, i, FALSE);
				gtk_clist_set_column_resizeable ( clist, i, TRUE);
			}
		}

		/* Sets columns title. */
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT, TRUE);
		}

		/* The last column should never be visible. */
		gtk_clist_set_column_visibility ( clist, 11, FALSE);

//		gw_notebook_catalog_column_sort ( clist, clist->sort_column, GINT_TO_POINTER ( -1));
		gw_notebook_catalog_set_column_sort ( clist, clist->sort_column);
		gtk_clist_thaw ( clist);

		return 0;
	}

	return -1;
}


gint gw_notebook_catalog_clist_explorer_set_column_title_disk ( void) {
	GtkWindow *w = NULL;
	GtkCList *clist = NULL;
	gchar *showed = NULL;
	gchar *text_utf8 = NULL;
	gint autoresize = -1;
	gint width = -1;
	gint i = 0;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	w = gw_gui_manager_main_interface_get_main_window ( );
	clist = gw_notebook_catalog_get_clist_explorer ( w);

	if ( clist != NULL ) {
		gtk_clist_freeze ( clist);
//		gtk_signal_emit_stop_by_name ( GTK_OBJECT ( clist), "resize-column");

		/* Sets columns width. */
		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SIZE)) == -1 ) {
			width = GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT, width);

		if ( (autoresize = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE)) == -1 ) {
			autoresize = GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE_DEFAULT;
		}

		/* Sets the autoresize mode. */
		for ( i = 0; i < 11; i++) {
			/* Enabling auto-resize on a column disallows user-resizing of the column. */
			if ( autoresize ) {
				gtk_clist_set_column_resizeable ( clist, i, FALSE);
				gtk_clist_set_column_auto_resize ( clist, i, TRUE);
			} else {
				gtk_clist_set_column_auto_resize ( clist, i, FALSE);
				gtk_clist_set_column_resizeable ( clist, i, TRUE);
			}
		}

		/* Sets columns title. */
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_TITLE), text_utf8);
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT, text_utf8);
		g_free ( text_utf8);

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) ) {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT, FALSE);
		} else {
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT, TRUE);
		}

//		gw_notebook_catalog_column_sort ( clist, clist->sort_column, GINT_TO_POINTER ( -1));
		gw_notebook_catalog_set_column_sort ( clist, clist->sort_column);
		gtk_clist_thaw ( clist);

		return 0;
	}

	return -1;
}


GtkCTreeNode * gw_notebook_catalog_ctree_node_get_child  ( GtkCTreeNode *node, gchar *name) {
	GtkCTreeNode *child = NULL;
	gchar *txt;
	guint8 spc;
	GdkBitmap *btmp;
	GdkPixmap *pxmp;
	GtkCTree *ctree = NULL;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL ) {
		child = GTK_CTREE_ROW ( node)->children;
		ctree = gw_gui_manager_main_interface_get_tree ( );

		while ( child != NULL ) {
			if ( gtk_ctree_node_get_pixtext ( GTK_CTREE ( ctree), child, 0, &txt, &spc, &pxmp, &btmp) ) {
				g_strdup_from_gtk_text ( txt, text_utf8);

				if ( strcmp ( text_utf8, name) == 0 ) {
					g_free ( text_utf8);

					return child;
				}

				g_free ( text_utf8);
			}

			child = GTK_CTREE_ROW ( child)->sibling;
		}
	}

	return NULL;
}


gint gw_notebook_catalog_ctree_node_get_num_children ( GtkCTreeNode *node) {
	GtkCTreeNode *child = NULL;
	gint n = 0;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( node != NULL ) {
		child = GTK_CTREE_ROW ( node)->children;

		while ( child != NULL ) {
			n++;
			child = GTK_CTREE_ROW ( child)->sibling;
		}
	}

	return n;
}


gint gw_notebook_catalog_ctree_destroy_all ( void) {
	/* Destroys all explorer tree :'( */
	GtkWindow *w = NULL;
	GtkCList *clist_info = NULL;
	GtkCList *clist_result = NULL;
	GtkCList *clist;
	GtkCTree *ctree = NULL;
	GtkCTreeNode *root = NULL;
	gint result = -1;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (w = gw_gui_manager_main_interface_get_main_window ( )) != NULL ) {
		clist_info = gw_notebook_catalog_get_clist_explorer ( w);
		clist_result = gw_notebook_search_get_clist_search ( w);
		ctree = gw_gui_manager_main_interface_get_tree ( );
		root = gw_gui_manager_main_interface_get_tree_root ( );
		gw_status_bar_put_messages ( w, _( "Closing catalog"), _( "Please wait..."));
		gw_gui_manager_main_interface_refresh ( );

		clist = GTK_CLIST ( ctree);
		gtk_clist_freeze ( clist);
		gtk_clist_freeze ( clist_info);
		gtk_clist_freeze ( clist_result);
		gtk_clist_clear ( clist_info);
		gtk_clist_clear ( clist_result);
		gtk_ctree_remove_node ( ctree, root);
		root = NULL;
		gw_gui_manager_main_interface_set_tree_root ( root);
		gw_status_bar_put_messages ( w, "", "");
		gtk_clist_thaw ( clist);
		gtk_clist_thaw ( clist_result);
		gtk_clist_thaw ( clist_info);

		gtk_window_set_title ( w, PROJECT_NAME);
		gw_status_bar_put_messages ( w, _( "Catalog closed"), "");
		gw_notebook_managment_refresh_categories ( w);
		gw_gui_manager_main_interface_refresh ( );

		result = 0;
	}

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "application is exited ==> memory status : ");
	g_mem_profile ( );
#endif

	return result;
}


gint gw_notebook_catalog_get_hpan_position ( GtkWindow *w) {
	gint position = -1;
	GtkPaned *hpan = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (hpan = GTK_PANED ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_NOTEBOOK_CATALOG_PANE))) != NULL) {
#ifdef HAVE_GTK20
			position = gtk_paned_get_position ( hpan);
#elif defined HAVE_GTK12
			position = hpan->handle_xpos;
#endif

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : hpan position = %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, position);
#endif
		}
	}

	return position;
}
