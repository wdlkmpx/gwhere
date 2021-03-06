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
#include "gwnotebooksearch.h"

#include <string.h> /* strncmp */

#include "../gwapplicationmanager.h"
#include "../gwguimanager.h"
#include "gwnotebooksearchcallback.h"


/*! @define	GW_REF_NOTEBOOK_SEARCH_TABBED_PANE_LABEL	The tabbed pane title */
#define GW_REF_NOTEBOOK_SEARCH_TABBED_PANE_LABEL "gw_ref_gw_notebook_search_tabbed_pane_label"
/*! @define	GW_REF_NOTEBOOK_SEARCH_ENTRY		The search text entry */
#define GW_REF_NOTEBOOK_SEARCH_ENTRY "gw_notebook_search_entry"
/*! @define	GW_REF_NOTEBOOK_START_SEARCH_BUTTON		The start search button */
#define GW_REF_NOTEBOOK_START_SEARCH_BUTTON "gw_notebook_start_search_button"
/*! @define	GW_REF_NOTEBOOK_CLEAR_BUTTON		The clear results button */
#define GW_REF_NOTEBOOK_CLEAR_BUTTON "gw_notebook_clear_button"
/*! @define	GW_REF_NOTEBOOK_SEARCH_USE_CASE_SENSITIVE_CHECK_BUTTON		The use case or uncase sensitive check button */
#define GW_REF_NOTEBOOK_SEARCH_USE_CASE_SENSITIVE_CHECK_BUTTON "gw_ref_gw_notebook_search_use_case_sensitive_check_button"
/*! @define	GW_REF_NOTEBOOK_SEARCH_USE_KEY_WORDS_RADIO_BUTTON		The use or not key words radio button */
#define GW_REF_NOTEBOOK_SEARCH_USE_KEY_WORDS_RADIO_BUTTON "gw_ref_gw_notebook_search_use_key_words_radio_button"
/*! @define	GW_REF_NOTEBOOK_SEARCH_USE_WILDCARDS_RADIO_BUTTON		The use or not wildcards radio button */
#define GW_REF_NOTEBOOK_SEARCH_USE_WILDCARDS_RADIO_BUTTON "gw_ref_gw_notebook_search_use_wildcards_radio_button"
/*! @define	GW_REF_NOTEBOOK_SEARCH_USE_REGULAR_EXPRESSION_RADIO_BUTTON		The use or not regular expression radio button */
#define GW_REF_NOTEBOOK_SEARCH_USE_REGULAR_EXPRESSION_RADIO_BUTTON "gw_ref_gw_notebook_search_use_regular_expression_radio_button"
/*! @define	GW_REF_NOTEBOOK_SEARCH_MATCH_FILE_CHECK_BUTTON		The match file check button */
#define GW_REF_NOTEBOOK_SEARCH_MATCH_FILE_CHECK_BUTTON "gw_ref_gw_notebook_search_match_file_check_button"
/*! @define	GW_REF_NOTEBOOK_SEARCH_MATCH_FOLDER_CHECK_BUTTON		The match folder check button */
#define GW_REF_NOTEBOOK_SEARCH_MATCH_FOLDER_CHECK_BUTTON "gw_ref_gw_notebook_search_match_folder_check_button"
/*! @define	GW_REF_NOTEBOOK_SEARCH_MATCH_DISK_CHECK_BUTTON		The match disk check button */
#define GW_REF_NOTEBOOK_SEARCH_MATCH_DISK_CHECK_BUTTON "gw_ref_gw_notebook_search_match_disk_check_button"
/*! @define	GW_REF_NOTEBOOK_SEARCH_MATCH_CATEGORY_CHECK_BUTTON		The match category check button */
#define GW_REF_NOTEBOOK_SEARCH_MATCH_CATEGORY_CHECK_BUTTON "gw_ref_gw_notebook_search_match_category_check_button"
/*! @define	GW_REF_NOTEBOOK_SEARCH_MATCH_DESCRIPTION_CHECK_BUTTON		The match description check button */
#define GW_REF_NOTEBOOK_SEARCH_MATCH_DESCRIPTION_CHECK_BUTTON "gw_ref_gw_notebook_search_match_description_check_button"
/*! @define	GW_REF_NOTEBOOK_SEARCH_CLIST_SEARCH		The result list of search */
#define GW_REF_NOTEBOOK_SEARCH_CLIST_SEARCH "gw_ref_gw_notebook_search_clist_search"


GtkWidget * gw_notebook_search_create ( GtkWindow * window)
{
	GtkCList *clist_result = NULL;
	GtkWidget *vb_tabbed_pane;
	GtkWidget *hb_control;
	GtkWidget *lbl_search;
	GtkWidget *entry_search_string;
	GtkWidget *bt_search, *bt_clear;
	GtkWidget *chk_bt_case_sensitive;
	GtkWidget *vb_options,*hb_options1,*hb_options1_bis,*hb_options2;
	GtkWidget *chk_match_file;
	GtkWidget *chk_match_folder;
	GtkWidget *chk_match_disk;
	GtkWidget *chk_match_category;
	GtkWidget *chk_match_description;
	GtkWidget *hb_search_result;
	GtkWidget *scrolled_result_list;
	GtkWidget *clist_search_result;
	GtkWidget *lbl_title_col;
	GtkWidget *radio_search_type,*radio_search_type2,*radio_search_type3,*frm_search_type,*vb_search_type;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Inits the accel group for keystroke shortcuts. */

	/* Vertical box of the search tabbed pane. */
	vb_tabbed_pane = gtk_vbox_new ( FALSE, 0);

	/* Horizontal box for controls (checkes boxes, buttons, ...). */
	hb_control = gtk_hbox_new ( FALSE, 10);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_control), 10);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_control, FALSE, TRUE, 0);

	/* Horizontal box for search options. */
	vb_options = gtk_vbox_new ( FALSE, 10);
	gtk_container_set_border_width ( GTK_CONTAINER ( vb_options), 0);
	gtk_box_pack_start ( GTK_BOX ( hb_control), vb_options, TRUE, TRUE, 0);

	/* Horizontal box for search options. */
	hb_options1 = gtk_hbox_new ( FALSE, 10);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_options1), 0);
	gtk_box_pack_start ( GTK_BOX ( vb_options), hb_options1, FALSE, TRUE, 0);

	/* Horizontal box for search options. */
	hb_options2 = gtk_hbox_new ( FALSE, 10);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_options2), 0);
	gtk_box_pack_start ( GTK_BOX ( vb_options), hb_options2, FALSE, TRUE, 0);

	lbl_search = gtk_label_new ( _( "Search : "));
	gtk_box_pack_start ( GTK_BOX ( /*hb_control*/hb_options1), lbl_search, FALSE, FALSE, 0);

	/* Text area to search. */
	entry_search_string = gtk_entry_new ( );
	g_signal_connect (G_OBJECT ( entry_search_string), "activate", G_CALLBACK ( gw_notebook_search_search_string_activate), window);
	g_signal_connect (G_OBJECT ( entry_search_string), "activate", G_CALLBACK ( gw_notebook_search_search_button_click), window);

	/* Store reference to the search string */
	g_object_ref ( entry_search_string);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_ENTRY, entry_search_string, (GDestroyNotify) g_object_unref);
	gtk_box_pack_start ( GTK_BOX ( hb_options1), entry_search_string, TRUE, TRUE, 0);
	GTK_WIDGET_SET_FLAGS ( entry_search_string, GTK_CAN_FOCUS);
	gtk_widget_grab_focus ( entry_search_string);

	/* Horizontal sub box for search options. */
	hb_options1_bis = gtk_hbox_new ( TRUE, 10);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb_options1_bis), 0);
	gtk_box_pack_start ( GTK_BOX ( hb_options1), hb_options1_bis, FALSE, TRUE, 0);

	/* Start search button. */
	bt_search = gtk_button_new_with_label (_( "Search"));

	/* Store reference to the start search button. */
	g_object_ref ( bt_search);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_START_SEARCH_BUTTON, bt_search,(GDestroyNotify) g_object_unref);
	gtk_widget_set_tooltip_text (bt_search,
	                             _("The search can be case sensitive. The wildcards search supports character \"*\".\nExample : img*.bmp or *.htm\nThe key words search accepts a list of obligatory words."));
	g_signal_connect (G_OBJECT ( bt_search), "clicked", G_CALLBACK ( gw_notebook_search_search_button_click), window);
	gtk_container_set_border_width ( GTK_CONTAINER ( bt_search), 5);
	gtk_box_pack_start ( GTK_BOX ( hb_options1_bis), bt_search, TRUE, TRUE, 0);

	/* Clear results button. */
	bt_clear = gtk_button_new_with_label (_( "Clear"));

	/* Store reference to the clear results button. */
	g_object_ref ( bt_clear);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_CLEAR_BUTTON, bt_clear,(GDestroyNotify) g_object_unref);
	gtk_widget_set_tooltip_text (bt_clear, _("Clears all search results"));
	g_signal_connect (G_OBJECT ( bt_clear), "clicked", G_CALLBACK ( gw_notebook_search_clear_button_click), window);
	gtk_container_set_border_width ( GTK_CONTAINER ( bt_clear), 5);
	gtk_box_pack_start ( GTK_BOX ( hb_options1_bis), bt_clear, TRUE, TRUE, 0);

	/* Case/uncase sensitive check buton. */
	chk_bt_case_sensitive = gtk_check_button_new_with_label (_( "Case sensitive"));

	/* Store reference to the case or uncase sensitive check button. */
	g_object_ref ( chk_bt_case_sensitive);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_USE_CASE_SENSITIVE_CHECK_BUTTON, chk_bt_case_sensitive, (GDestroyNotify) g_object_unref);
	gtk_container_set_border_width ( GTK_CONTAINER ( chk_bt_case_sensitive), 5);
	gtk_box_pack_start ( GTK_BOX ( hb_options1_bis), chk_bt_case_sensitive, FALSE, FALSE, 0);
	g_signal_connect (G_OBJECT ( chk_bt_case_sensitive), "clicked", G_CALLBACK (gw_notebook_search_option_use_case_sensitive_click), window);
	gtk_widget_set_tooltip_text (chk_bt_case_sensitive,
	                             _( "The search can be be or not case sensitive.\nIn case sensitive \"File.txt\" doesn't match with \"file.txt\". But in uncase sensitive it matches."));

	/* Create the radio button group for search type. */
	frm_search_type = gtk_frame_new (_( "Search type"));
	gtk_container_set_border_width ( GTK_CONTAINER ( frm_search_type), 10);
	gtk_box_pack_start ( GTK_BOX ( hb_control), frm_search_type, FALSE, TRUE, 0);
	vb_search_type = gtk_vbox_new ( FALSE, 0);
	gtk_container_add ( GTK_CONTAINER ( frm_search_type), vb_search_type);

	radio_search_type = gtk_radio_button_new_with_label_from_widget ( NULL, _("Key words"));
	g_object_ref ( radio_search_type);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_USE_KEY_WORDS_RADIO_BUTTON, radio_search_type, (GDestroyNotify) g_object_unref);
	g_signal_connect (G_OBJECT ( radio_search_type), "clicked", G_CALLBACK (gw_notebook_search_option_search_type_click), GINT_TO_POINTER ( SEARCH_TYPE_KEY_WORDS));
	gtk_container_set_border_width ( GTK_CONTAINER ( radio_search_type), 5);
	gtk_box_pack_start ( GTK_BOX ( vb_search_type), radio_search_type, FALSE, FALSE, 0);
	gtk_widget_set_tooltip_text (radio_search_type,
	                             _( "Enter a list of key words which all must be containted is the matched files."));

	radio_search_type2 = gtk_radio_button_new_with_label_from_widget ( GTK_RADIO_BUTTON ( radio_search_type), _("Wildcards"));
	g_object_ref ( radio_search_type2);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_USE_WILDCARDS_RADIO_BUTTON, radio_search_type2, (GDestroyNotify) g_object_unref);
	g_signal_connect (G_OBJECT ( radio_search_type2), "clicked", G_CALLBACK (gw_notebook_search_option_search_type_click), GINT_TO_POINTER ( SEARCH_TYPE_WILDCARDS));
	gtk_container_set_border_width ( GTK_CONTAINER ( radio_search_type2), 5);
	gtk_box_pack_start ( GTK_BOX ( vb_search_type), radio_search_type2, FALSE, FALSE, 0);
	gtk_widget_set_tooltip_text (radio_search_type2,
	                             _( "Enter the full wildcards pattern. This pattern can contains \"?\" and \"*\" caracters."));

	radio_search_type3 = gtk_radio_button_new_with_label_from_widget ( GTK_RADIO_BUTTON ( radio_search_type2), _("Regular expression"));
	g_object_ref ( radio_search_type3);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_USE_REGULAR_EXPRESSION_RADIO_BUTTON, radio_search_type3, (GDestroyNotify) g_object_unref);
	g_signal_connect (G_OBJECT ( radio_search_type3), "clicked", G_CALLBACK (gw_notebook_search_option_search_type_click), GINT_TO_POINTER ( SEARCH_TYPE_REGEX));
	gtk_container_set_border_width ( GTK_CONTAINER ( radio_search_type3), 5);
	gtk_box_pack_start ( GTK_BOX ( vb_search_type), radio_search_type3, FALSE, FALSE, 0);
	gtk_widget_set_tooltip_text (radio_search_type3, 
	                             _( "Can use regular expression. See documentation for more information."));

	/* Match file check buton. */
	chk_match_file = gtk_check_button_new_with_label (_( "File"));
	g_object_ref ( chk_match_file);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_MATCH_FILE_CHECK_BUTTON, chk_match_file, (GDestroyNotify) g_object_unref);
	g_signal_connect (G_OBJECT ( chk_match_file), "clicked", G_CALLBACK (gw_notebook_search_option_match_file_click), window);
	gtk_container_set_border_width ( GTK_CONTAINER ( chk_match_file), 5);
	gtk_box_pack_start ( GTK_BOX ( hb_options2), chk_match_file, FALSE, FALSE, 0);
	gtk_widget_set_tooltip_text (chk_match_file,
	                             _( "The search matches with files name."));

	/* Match folder check buton. */
	chk_match_folder = gtk_check_button_new_with_label (_( "Folder"));
	g_object_ref ( chk_match_folder);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_MATCH_FOLDER_CHECK_BUTTON, chk_match_folder, (GDestroyNotify) g_object_unref);
	g_signal_connect (G_OBJECT ( chk_match_folder), "clicked", G_CALLBACK (gw_notebook_search_option_match_folder_click), window);
	gtk_container_set_border_width ( GTK_CONTAINER ( chk_match_folder), 5);
	gtk_box_pack_start ( GTK_BOX ( hb_options2), chk_match_folder, FALSE, FALSE, 0);
	gtk_widget_set_tooltip_text (chk_match_folder, 
	                             _( "The search matches with folders name."));

	/* Match disk check buton. */
	chk_match_disk = gtk_check_button_new_with_label (_( "Disk"));
	g_object_ref ( chk_match_disk);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_MATCH_DISK_CHECK_BUTTON, chk_match_disk, (GDestroyNotify) g_object_unref);
	g_signal_connect (G_OBJECT ( chk_match_disk), "clicked", G_CALLBACK (gw_notebook_search_option_match_disk_click), window);
	gtk_container_set_border_width ( GTK_CONTAINER ( chk_match_disk), 5);
	gtk_box_pack_start ( GTK_BOX ( hb_options2), chk_match_disk, FALSE, FALSE, 0);
	gtk_widget_set_tooltip_text (chk_match_disk,
	                             _( "The search matches with disks name."));

	/* Match category check buton. */
	chk_match_category = gtk_check_button_new_with_label (_( "Category"));
	g_object_ref ( chk_match_category);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_MATCH_CATEGORY_CHECK_BUTTON, chk_match_category, (GDestroyNotify) g_object_unref);
	g_signal_connect (G_OBJECT ( chk_match_category), "clicked", G_CALLBACK (gw_notebook_search_option_match_category_click), window);
	gtk_container_set_border_width ( GTK_CONTAINER ( chk_match_category), 5);
	gtk_box_pack_start ( GTK_BOX ( hb_options2), chk_match_category, FALSE, FALSE, 0);
	gtk_widget_set_tooltip_text (chk_match_category,
	                             _( "The search matches with categories name."));

	/* Match description check buton. */
	chk_match_description = gtk_check_button_new_with_label (_( "Description"));
	g_object_ref ( chk_match_description);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_MATCH_DESCRIPTION_CHECK_BUTTON, chk_match_description, (GDestroyNotify) g_object_unref);
	g_signal_connect (G_OBJECT ( chk_match_description), "clicked", G_CALLBACK (gw_notebook_search_option_match_description_click), window);
	gtk_container_set_border_width ( GTK_CONTAINER ( chk_match_description), 5);
	gtk_box_pack_start ( GTK_BOX ( hb_options2), chk_match_description, FALSE, FALSE, 0);
	gtk_widget_set_tooltip_text (chk_match_description,
	                             _( "The search matches with descriptions."));

	/* Horizontal box to display search result. */
	hb_search_result = gtk_hbox_new ( FALSE, 0);
	gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_search_result, TRUE, TRUE, 0);

	/* Scrolled result list. */
	scrolled_result_list = gtk_scrolled_window_new ( NULL, NULL);
	gtk_box_pack_start ( GTK_BOX ( hb_search_result), scrolled_result_list, TRUE, TRUE, 0);

	/* List of search result. */
	clist_search_result = gtk_clist_new ( 7);
	clist_result = GTK_CLIST ( clist_search_result);

	/* Store reference to the result search list. */
	g_object_ref ( clist_search_result);
	g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_CLIST_SEARCH, clist_search_result,(GDestroyNotify) g_object_unref);
	g_signal_connect (G_OBJECT ( clist_search_result), "resize-column", G_CALLBACK ( gw_notebook_search_clist_column_resized), NULL);
	g_signal_connect (G_OBJECT ( clist_search_result), "click_column", G_CALLBACK ( gw_notebook_search_column_sort), NULL);
	g_signal_connect (G_OBJECT ( clist_search_result), "select_row", G_CALLBACK ( gw_notebook_search_select_row), window);
	gtk_container_add ( GTK_CONTAINER ( scrolled_result_list), clist_search_result);

	gtk_clist_column_titles_show ( clist_result);
	gtk_clist_set_column_justification ( clist_result, 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification ( clist_result, 2, GTK_JUSTIFY_LEFT);
	gtk_clist_set_column_justification ( clist_result, 3, GTK_JUSTIFY_RIGHT);
	gtk_clist_set_column_justification ( clist_result, 4, GTK_JUSTIFY_RIGHT);
	gtk_clist_set_column_justification ( clist_result, 5, GTK_JUSTIFY_LEFT);
	gtk_clist_set_column_justification ( clist_result, 6, GTK_JUSTIFY_LEFT);
	gtk_clist_set_sort_column ( clist_result, 0);
	gtk_clist_set_sort_type ( clist_result, GTK_SORT_ASCENDING);
	gtk_clist_set_auto_sort ( clist_result, TRUE);

	lbl_title_col = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_result, 0, lbl_title_col);

	lbl_title_col = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_result, 1, lbl_title_col);

	lbl_title_col = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_result, 2, lbl_title_col);

	lbl_title_col = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_result, 3, lbl_title_col);

	lbl_title_col = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_result, 4, lbl_title_col);

	lbl_title_col = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_result, 5, lbl_title_col);

	lbl_title_col = gtk_label_new ( NULL);
	gtk_clist_set_column_widget ( clist_result, 6, lbl_title_col);

	gw_notebook_search_clist_search_set_column_title ( );

	return vb_tabbed_pane;
}


GtkWidget * gw_notebook_search_create_and_add ( GtkWindow *window, GtkNotebook *parent)
{
	GtkWidget *tabbed_pane_search = NULL;
	GtkWidget *search_tabbed_pane_label;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( window != NULL )
	{
		tabbed_pane_search = gw_notebook_search_create ( window);

		if ( tabbed_pane_search != NULL )
		{
			gtk_container_add ( GTK_CONTAINER ( parent), tabbed_pane_search);

			/* Text label of the search tabbed pane. */
			search_tabbed_pane_label = gtk_label_new (_( "Search"));

			/* Store reference to the title of tabbed pane */
			g_object_ref ( search_tabbed_pane_label);
			g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_SEARCH_TABBED_PANE_LABEL, search_tabbed_pane_label,(GDestroyNotify) g_object_unref);
			gtk_notebook_set_tab_label ( parent, gtk_notebook_get_nth_page ( parent, 1), search_tabbed_pane_label);
		}
	}

	return tabbed_pane_search;
}


gchar * gw_notebook_search_get_search_text ( GtkWindow *w)
{
	GtkEntry *search_entry = NULL;
	gchar *search_text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		search_entry = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_ENTRY);

		if ( search_entry != NULL )
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( search_entry), search_text);
		}
	}

	return search_text;
}


GtkCList * gw_notebook_search_get_clist_search ( GtkWindow *w)
{
	GtkCList *clist_search = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		clist_search = GTK_CLIST ( g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_CLIST_SEARCH));
	}

	return clist_search;
}


gboolean gw_notebook_search_set_search_text ( GtkWindow *w, gchar *text)
{
	GtkEntry *search_entry = NULL;
	gchar *search_text = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		search_entry = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_ENTRY);

		if ( search_entry != NULL )
		{
			g_strdup_to_gtk_text ( text, search_text);
			gtk_entry_set_text ( search_entry, search_text);
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_notebook_search_set_option_case_sensitive ( GtkWindow *w, gboolean case_sensitive)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_CASE_SENSITIVE_CHECK_BUTTON);

		if ( chk != NULL )
		{
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chk), case_sensitive);
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_notebook_search_set_option_key_words ( GtkWindow *w, gboolean key_words)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_KEY_WORDS_RADIO_BUTTON);

		if ( chk != NULL )
		{
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chk), key_words);
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_notebook_search_set_option_wildcards ( GtkWindow *w, gboolean wildcards)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_WILDCARDS_RADIO_BUTTON);

		if ( chk != NULL )
		{
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chk), wildcards);
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_notebook_search_set_option_regular_expression ( GtkWindow *w, gboolean regex)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_REGULAR_EXPRESSION_RADIO_BUTTON);

		if ( chk != NULL )
		{
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chk), regex);
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_notebook_search_set_option_search_type ( GtkWindow *w, gint search_type)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	switch ( search_type)
	{
		case SEARCH_TYPE_KEY_WORDS:	result = gw_notebook_search_set_option_key_words ( w, TRUE);
						break;

		case SEARCH_TYPE_WILDCARDS:	result = gw_notebook_search_set_option_wildcards ( w, TRUE);
						break;

		case SEARCH_TYPE_REGEX:		result = gw_notebook_search_set_option_regular_expression ( w, TRUE);
						break;

		default:			break;
	}
	return result;
}


gboolean gw_notebook_search_set_option_match_file ( GtkWindow *w, gboolean match_file)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_MATCH_FILE_CHECK_BUTTON);

		if ( chk != NULL )
		{
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chk), match_file);
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_notebook_search_set_option_match_folder ( GtkWindow *w, gboolean match_folder)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_MATCH_FOLDER_CHECK_BUTTON);

		if ( chk != NULL )
		{
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chk), match_folder);
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_notebook_search_set_option_match_disk ( GtkWindow *w, gboolean match_disk)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_MATCH_DISK_CHECK_BUTTON);

		if ( chk != NULL )
		{
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chk), match_disk);
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_notebook_search_set_option_match_category ( GtkWindow *w, gboolean match_category)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_MATCH_CATEGORY_CHECK_BUTTON);

		if ( chk != NULL )
		{
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chk), match_category);
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_notebook_search_set_option_match_description ( GtkWindow *w, gboolean match_description)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_MATCH_DESCRIPTION_CHECK_BUTTON);

		if ( chk != NULL )
		{
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chk), match_description);
			result = match_description;
		}
	}

	return result;
}


gboolean gw_notebook_search_get_option_case_sensitive ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_CASE_SENSITIVE_CHECK_BUTTON);

		if ( chk != NULL )
		{
			result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
		}
	}

	return result;
}


gboolean gw_notebook_search_get_option_key_words ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_KEY_WORDS_RADIO_BUTTON);

		if ( chk != NULL )
		{
			result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
		}
	}

	return result;
}


gboolean gw_notebook_search_get_option_wildcards ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_WILDCARDS_RADIO_BUTTON);

		if ( chk != NULL )
		{
			result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
		}
	}

	return result;
}


gboolean gw_notebook_search_get_option_regular_expression ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_REGULAR_EXPRESSION_RADIO_BUTTON);

		if ( chk != NULL )
		{
			result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
		}
	}

	return result;
}


gint gw_notebook_search_get_option_search_type ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_KEY_WORDS_RADIO_BUTTON);

		if ( (chk != NULL) && (gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk)) == TRUE) )
		{
			result = SEARCH_TYPE_KEY_WORDS;
		}

		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_WILDCARDS_RADIO_BUTTON);

		if ( (chk != NULL) && (gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk)) == TRUE) )
		{
			result = SEARCH_TYPE_WILDCARDS;
		}

		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_USE_REGULAR_EXPRESSION_RADIO_BUTTON);

		if ( (chk != NULL) && (gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk)) == TRUE) )
		{
			result = SEARCH_TYPE_REGEX;
		}
	}

	return result;
}


gboolean gw_notebook_search_get_option_match_file ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_MATCH_FILE_CHECK_BUTTON);

		if ( chk != NULL )
		{
			result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
		}
	}

	return result;
}


gboolean gw_notebook_search_get_option_match_folder ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_MATCH_FOLDER_CHECK_BUTTON);

		if ( chk != NULL )
		{
			result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
		}
	}

	return result;
}


gboolean gw_notebook_search_get_option_match_disk ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_MATCH_DISK_CHECK_BUTTON);

		if ( chk != NULL )
		{
			result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
		}
	}

	return result;
}


gboolean gw_notebook_search_get_option_match_category ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_MATCH_CATEGORY_CHECK_BUTTON);

		if ( chk != NULL )
		{
			result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
		}
	}

	return result;
}


gboolean gw_notebook_search_get_option_match_description ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk = g_object_get_data (G_OBJECT ( w), GW_REF_NOTEBOOK_SEARCH_MATCH_DESCRIPTION_CHECK_BUTTON);

		if ( chk != NULL )
		{
			result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
		}
	}

	return result;
}


struct user_quick_search * gw_notebook_search_get_user_quick_search ( GtkWindow *w)
{
	struct user_quick_search *user_qs = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		user_qs = user_quick_search_new ( );

		user_quick_search_set_pattern ( user_qs, gw_notebook_search_get_search_text ( w));
		user_quick_search_set_case_sensitive ( user_qs, gw_notebook_search_get_option_case_sensitive ( w));
		user_quick_search_set_type ( user_qs, gw_notebook_search_get_option_search_type ( w));
		user_quick_search_set_match_file ( user_qs, gw_notebook_search_get_option_match_file ( w));
		user_quick_search_set_match_folder ( user_qs, gw_notebook_search_get_option_match_folder ( w));
		user_quick_search_set_match_disk ( user_qs, gw_notebook_search_get_option_match_disk ( w));
		user_quick_search_set_match_category ( user_qs, gw_notebook_search_get_option_match_category ( w));
		user_quick_search_set_match_description ( user_qs, gw_notebook_search_get_option_match_description ( w));
	}

	return user_qs;
}


gint gw_notebook_search_clist_search_set_column_title ( void)
{
	GtkWindow *w = NULL;
	GtkCList *clist = NULL;
	gchar *showed = NULL;
	gint autoresize = -1;
	gint width = -1;
	gint i =0;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	w = gw_gui_manager_main_interface_get_main_window ( );
	clist = gw_notebook_search_get_clist_search ( w);

	if ( clist != NULL )
	{
		/* Sets columns width. */
		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_NAME_SIZE)) == -1 )
		{
			width = GW_VALUE_APP_SEARCH_COLUMN_NAME_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_DISK_SIZE)) == -1 )
		{
			width = GW_VALUE_APP_SEARCH_COLUMN_DISK_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_PATH_SIZE)) == -1 )
		{
			width = GW_VALUE_APP_SEARCH_COLUMN_PATH_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_SIZE_SIZE)) == -1 )
		{
			width = GW_VALUE_APP_SEARCH_COLUMN_SIZE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_DATE_SIZE)) == -1 )
		{
			width = GW_VALUE_APP_SEARCH_COLUMN_DATE_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SIZE)) == -1 )
		{
			width = GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION_DEFAULT, width);

		if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SIZE)) == -1 )
		{
			width = GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SIZE_DEFAULT;
		}

		gtk_clist_set_column_width ( clist, GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION_DEFAULT, width);

		/* Sets columns width. */
		if ( (autoresize = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE)) == -1 )
		{
			autoresize = GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE_DEFAULT;
		}

		/* Sets the autoresize mode. */
		for ( i = 0; i < 7; i++)
		{
			/* Enabling auto-resize on a column disallows user-resizing of the column. */
			if ( autoresize )
			{
				gtk_clist_set_column_auto_resize ( clist, i, TRUE);
			}
			else
			{
				gtk_clist_set_column_resizeable ( clist, i, TRUE);
			}
		}

		/* Sets columns title. */
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION_DEFAULT,
		                            _( GW_VALUE_APP_SEARCH_COLUMN_NAME_TITLE));
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION_DEFAULT,
		                            _( GW_VALUE_APP_SEARCH_COLUMN_DISK_TITLE));
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION_DEFAULT,
		                            _( GW_VALUE_APP_SEARCH_COLUMN_PATH_TITLE));
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION_DEFAULT,
		                            _( GW_VALUE_APP_SEARCH_COLUMN_SIZE_TITLE));
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION_DEFAULT,
		                            _( GW_VALUE_APP_SEARCH_COLUMN_DATE_TITLE));
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION_DEFAULT,
		                            _( GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_TITLE));
		gtk_clist_set_column_title ( clist, GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION_DEFAULT,
		                            _( GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_TITLE));

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_SEARCH_COLUMN_NAME_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) )
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION_DEFAULT, FALSE);
		}
		else
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_SEARCH_COLUMN_DISK_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) )
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION_DEFAULT, FALSE);
		}
		else
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_SEARCH_COLUMN_PATH_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) )
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION_DEFAULT, FALSE);
		}
		else
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_SEARCH_COLUMN_SIZE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) )
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION_DEFAULT, FALSE);
		}
		else
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_SEARCH_COLUMN_DATE_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) )
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION_DEFAULT, FALSE);
		}
		else
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) )
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION_DEFAULT, FALSE);
		}
		else
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION_DEFAULT, TRUE);
		}

		if ( ((showed = gw_am_get_settings ( GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SHOW)) != NULL) && (strncmp ( showed, "0", 1) == 0) )
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION_DEFAULT, FALSE);
		}
		else
		{
			gtk_clist_set_column_visibility ( clist, GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION_DEFAULT, TRUE);
		}

		gw_notebook_search_set_column_sort ( clist, clist->sort_column);

		return 0;
	}

	return -1;
}
