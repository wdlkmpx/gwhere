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
#include "gwcategorieseditbox.h"

#include <string.h> /* strcmp strlen */

#include "../gwapplicationmanager.h"
#include "gtktextarea.h"
#include "gwmsgbox.h"
#include "gwnotebookmanagmentcallback.h"


/*! @define	GW_REF_CATEGORIES_EDIT_BOX_MAIN_WINDOW	The main window */
#define GW_REF_CATEGORIES_EDIT_BOX_MAIN_WINDOW "gw_ref_gw_categories_edit_box_main_window"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_NAME_ENTRY	The category name */
#define GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_NAME_ENTRY "gw_ref_gw_categories_edit_box_category_name_entry"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_NAME_ENTRY_TOOLTIPS	The category name tooltips */
#define GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_NAME_ENTRY_TOOLTIPS "gw_ref_gw_categories_edit_box_category_name_entry_tooltips"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_DESCRIPTION_TEXT	The category description */
#define GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_DESCRIPTION_TEXT "gw_ref_gw_categories_edit_box_category_description_text"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_DESCRIPTION_TEXT_TOOLTIPS	The category description tooltips */
#define GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_DESCRIPTION_TEXT_TOOLTIPS "gw_ref_gw_categories_edit_box_category_description_text_tooltips"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_UPDATE_BUTTON_TOOLTIPS	The update button tooltips */
#define GW_REF_CATEGORIES_EDIT_BOX_UPDATE_BUTTON_TOOLTIPS "gw_ref_gw_categories_edit_box_update_button_tooltips"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_UPDATE_BUTTON	The update button */
#define GW_REF_CATEGORIES_EDIT_BOX_UPDATE_BUTTON "gw_ref_gw_categories_edit_box_update_button"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_REMOVE_BUTTON	The remove button */
#define GW_REF_CATEGORIES_EDIT_BOX_REMOVE_BUTTON "gw_ref_gw_categories_edit_box_remove_button"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON	The add/update button */
#define GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON "gw_ref_gw_categories_edit_box_add_update_button"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON_TOOLTIPS	The add/update button tooltips */
#define GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON_TOOLTIPS "gw_ref_gw_categories_edit_box_add_update_button_tooltips"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_REMOVE_BUTTON_TOOLTIPS	The remove button tooltips */
#define GW_REF_CATEGORIES_EDIT_BOX_REMOVE_BUTTON_TOOLTIPS "gw_ref_gw_categories_edit_box_remove_button_tooltips"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_CATEGORIES_LIST	The list of categories */
#define GW_REF_CATEGORIES_EDIT_BOX_CATEGORIES_LIST "gw_ref_gw_categories_edit_box_categories_list"
/*! @define	GW_REF_CATEGORIES_EDIT_BOX_CLOSE_BUTTON_TOOLTIPS	The close button tooltipd */
#define GW_REF_CATEGORIES_EDIT_BOX_CLOSE_BUTTON_TOOLTIPS "gw_ref_gw_categories_edit_box_close_button_toltips"


GtkWindow * gw_categories_edit_box_create ( GtkWindow *window, GWDBCatalog *catalog) {
	/* This window must be single, this property may be changed */
	static GtkWidget *w = NULL;
	GtkWidget *vb, *hb, *scr, *list, *bt, *hsp, *ent, *lbl, *frm, *txt;
	guint bt_key;
	GtkAccelGroup *accel;
	GtkTooltips *tips;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Init an accel group for shortcuts */
	accel = gtk_accel_group_new ( );

	/* Init tooltips */
	tips = gtk_tooltips_new ( );

	if ( !w ) {
		w = gtk_window_new ( GTK_WINDOW_TOPLEVEL);
		gtk_window_set_modal ( GTK_WINDOW ( w), TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( w), window);
		gtk_window_set_position ( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);
		gtk_window_set_policy ( GTK_WINDOW ( w), FALSE, FALSE, FALSE);
		g_strdup_to_gtk_text ( _( "Edit categories"), text_utf8);
		gtk_window_set_title ( GTK_WINDOW ( w), text_utf8);
		g_free ( text_utf8);
		gtk_container_set_border_width ( GTK_CONTAINER ( w), 5);

		gtk_object_set_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_MAIN_WINDOW, window);

		gtk_signal_connect ( GTK_OBJECT ( w), "destroy", GTK_SIGNAL_FUNC (gtk_widget_destroyed), &w);

		/* Vertical box */
		vb = gtk_vbox_new ( FALSE, 10);
		gtk_container_add ( GTK_CONTAINER ( w), vb);

		/* Frame category description */
		g_strdup_to_gtk_text ( _( "Categories list : "), text_utf8);
		frm = gtk_frame_new ( text_utf8);
		g_free ( text_utf8);
		gtk_box_pack_start ( GTK_BOX ( vb), frm, TRUE, TRUE, 0);

		/* 1st horizontal box*/
		hb = gtk_hbox_new ( TRUE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb), 5);
		gtk_container_add ( GTK_CONTAINER ( frm), hb);

		/* Scrolled panel */
		scr = gtk_scrolled_window_new ( NULL, NULL);
		gtk_box_pack_start ( GTK_BOX ( hb), scr, TRUE, TRUE, 0);

		/* Categories list */
		list = gtk_clist_new ( 2);
		gtk_widget_set_usize ( list, 100, 100);
		/*gtk_widget_ref ( list);*/
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORIES_LIST, list, /*(GtkDestroyNotify)gtk_widget_unref*/NULL);
		/*gtk_signal_connect ( GTK_OBJECT ( list), "click_column", GTK_SIGNAL_FUNC ( gw_categories_edit_box_list_click_column), w);*/
		gtk_signal_connect ( GTK_OBJECT ( list), "select_row", GTK_SIGNAL_FUNC ( gw_categories_edit_box_list_select_row), w);
		gtk_container_add ( GTK_CONTAINER ( scr), list);
		gtk_clist_set_column_width ( GTK_CLIST ( list), 0, 80);
		gtk_clist_set_column_width ( GTK_CLIST ( list), 1, 20);
		gtk_clist_column_titles_show ( GTK_CLIST ( list));

		/* 1st column label */
		g_strdup_to_gtk_text ( _( "Name"), text_utf8);
		lbl = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_clist_set_column_widget ( GTK_CLIST ( list), 0, lbl);

		/* 2nd column label */
		g_strdup_to_gtk_text ( _( "Description"), text_utf8);
		lbl = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_clist_set_column_widget ( GTK_CLIST ( list), 1, lbl);

		/* 2nd horizontal box */
		hb = gtk_hbox_new ( TRUE, 0);
		gtk_box_pack_start ( GTK_BOX ( vb), hb, TRUE, TRUE, 0);

		/* Update button */
		bt = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "_Update"), text_utf8);
		bt_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( bt)->child), text_utf8);
		g_free ( text_utf8);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_UPDATE_BUTTON, bt, /*(GtkDestroyNotify)gtk_widget_unref*/NULL);
		gtk_widget_add_accelerator ( bt, "clicked", accel, bt_key, GDK_MOD1_MASK, 0);
		gtk_signal_connect ( GTK_OBJECT ( bt), "clicked", GTK_SIGNAL_FUNC ( gw_categories_edit_box_update_click), GTK_WINDOW ( w));
		gtk_object_set_user_data ( GTK_OBJECT ( bt), w);
		gtk_box_pack_start ( GTK_BOX ( hb), bt, FALSE, TRUE, 5);
		g_strdup_to_gtk_text ( _( "Allows to update category properties of the selected category. Clicks on Add / Update button to save updates."), text_utf8);
		gtk_tooltips_set_tip ( tips, bt, text_utf8, GW_REF_CATEGORIES_EDIT_BOX_UPDATE_BUTTON_TOOLTIPS);
		g_free ( text_utf8);
		gtk_widget_set_sensitive ( GTK_WIDGET ( bt), FALSE);

		/* Remove button */
		bt = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "_Remove"), text_utf8);
		bt_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( bt)->child), text_utf8);
		g_free ( text_utf8);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_REMOVE_BUTTON, bt, /*(GtkDestroyNotify) gtk_widget_unref)*/NULL);
		gtk_widget_add_accelerator ( bt, "clicked", accel, bt_key, GDK_MOD1_MASK, 0);
		gtk_signal_connect ( GTK_OBJECT ( bt), "clicked", GTK_SIGNAL_FUNC ( gw_categories_edit_box_remove_click), GTK_WINDOW ( w));
		gtk_object_set_user_data ( GTK_OBJECT ( bt), w);
		gtk_box_pack_start ( GTK_BOX ( hb), bt, FALSE, TRUE, 5);
		g_strdup_to_gtk_text ( _( "Remove the selected category from categories list. This categories may removed only if there's not any item which uses this category."), text_utf8);
		gtk_tooltips_set_tip ( tips, bt, text_utf8, GW_REF_CATEGORIES_EDIT_BOX_REMOVE_BUTTON_TOOLTIPS);
		g_free ( text_utf8);
		gtk_widget_set_sensitive ( GTK_WIDGET ( bt), FALSE);

		/* 1st horizontal separator */
		hsp = gtk_hseparator_new ( );
		gtk_box_pack_start ( GTK_BOX ( vb), hsp, TRUE, TRUE, 0);

		/* 3rd horizontal box */
		hb = gtk_hbox_new ( FALSE, 0);
		gtk_box_pack_start ( GTK_BOX ( vb), hb, TRUE, TRUE, 0);

		/* Label for category name */
		g_strdup_to_gtk_text ( _( "Category name : "), text_utf8);
		lbl = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_box_pack_start ( GTK_BOX ( hb), lbl, FALSE, FALSE, 5);

		/* Field text for category name */
		ent = gtk_entry_new ( );
		/*gtk_widget_ref ( ent);*/
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_NAME_ENTRY, ent, /*(GtkDestroyNotify)gtk_widget_unref*/NULL);
		gtk_signal_connect ( GTK_OBJECT ( ent), "changed", GTK_SIGNAL_FUNC ( gw_categories_edit_box_category_name_changed), w);
		gtk_box_pack_start ( GTK_BOX ( hb), ent, TRUE, TRUE, 5);
		g_strdup_to_gtk_text ( _( "Enter the name of the category."), text_utf8);
		gtk_tooltips_set_tip ( tips, ent, text_utf8, GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_NAME_ENTRY_TOOLTIPS);
		g_free ( text_utf8);

		/* Frame category description */
		g_strdup_to_gtk_text ( _( "Description : "), text_utf8);
		frm = gtk_frame_new ( text_utf8);
		g_free ( text_utf8);
		gtk_box_pack_start ( GTK_BOX ( vb), frm, TRUE, TRUE, 0);

		/* 4th horizontal box */
		hb = gtk_hbox_new ( TRUE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb), 5);
		gtk_container_add ( GTK_CONTAINER ( frm), hb);

		/* Text scrollbar */
		scr = gtk_scrolled_window_new ( NULL, NULL);
		gtk_box_pack_start ( GTK_BOX ( hb), scr, TRUE, TRUE, 0);
		gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scr), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

		/* Text area for category description */
		txt = gtk_text_area_new ( );
		gtk_text_area_set_editable ( GTK_TEXT_AREA ( txt), TRUE);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_DESCRIPTION_TEXT, txt, /*(GtkDestroyNotify)gtk_widget_unref*/NULL);
#if defined ( HAVE_GTK12)
 		gtk_signal_connect ( GTK_OBJECT ( txt), "changed", GTK_SIGNAL_FUNC ( gw_categories_edit_box_category_description_changed), w);
#elif defined ( HAVE_GTK20)
		g_signal_connect ( G_OBJECT ( gtk_text_view_get_buffer ( GTK_TEXT_VIEW ( txt))), "changed", GTK_SIGNAL_FUNC ( gw_categories_edit_box_category_description_changed), w);
#endif
		gtk_container_add ( GTK_CONTAINER ( scr), txt);
		g_strdup_to_gtk_text ( _( "Enter the description of the category."), text_utf8);
		gtk_tooltips_set_tip ( tips, txt, text_utf8, GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_DESCRIPTION_TEXT_TOOLTIPS);
		g_free ( text_utf8);

		/* The Add/Update/Close button area */
		hb = gtk_hbutton_box_new ( );
		gtk_button_box_set_layout ( GTK_BUTTON_BOX ( hb), GTK_BUTTONBOX_END);
		gtk_button_box_set_spacing ( GTK_BUTTON_BOX ( hb), 5);
		gtk_box_pack_end ( GTK_BOX ( vb), hb, FALSE, FALSE, 0);

		/* Add/Update button */
		bt = gtk_button_new_with_label ( "");
		/* Is it not mandatory? */
		/*g_strdup_to_gtk_text ( _( "Add"), text_utf8);
		gtk_label_set_text ( GTK_LABEL ( GTK_BIN ( bt)->child), text_utf8);
		g_free ( text_utf8);
		*/
		/*gtk_widget_ref ( bt);*/
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON, bt, /*(GtkDestroyNotify)gtk_widget_unref*/NULL);
		g_strdup_to_gtk_text ( _( "Add / Update"), text_utf8);
		bt_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( bt)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( bt, "clicked", accel, bt_key, GDK_MOD1_MASK, 0);
		gtk_signal_connect ( GTK_OBJECT ( bt), "clicked", GTK_SIGNAL_FUNC ( gw_categories_edit_box_add_update_click), w);
		gtk_object_set_user_data ( GTK_OBJECT ( bt), w);
		gtk_box_pack_start ( GTK_BOX ( hb), bt, TRUE, TRUE, 5);
		g_strdup_to_gtk_text ( _( "Save properties changes of category."), text_utf8);
		gtk_tooltips_set_tip ( tips, bt, text_utf8, GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON_TOOLTIPS);
		g_free ( text_utf8);
		gtk_widget_set_sensitive ( GTK_WIDGET ( bt), FALSE);
		GTK_WIDGET_SET_FLAGS ( bt, GTK_CAN_FOCUS);
		GTK_WIDGET_SET_FLAGS ( bt, GTK_CAN_DEFAULT);
		gtk_widget_grab_default ( bt);

		/* Close button */
		bt = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "Close"), text_utf8);
		bt_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( bt)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( bt, "clicked", accel, bt_key, GDK_MOD1_MASK, 0);
		gtk_signal_connect_object ( GTK_OBJECT ( bt), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));
		gtk_object_set_user_data ( GTK_OBJECT ( bt), w);
		gtk_box_pack_start ( GTK_BOX ( hb), bt, TRUE, TRUE, 5);
		g_strdup_to_gtk_text ( _( "Close the categories properties edit window."), text_utf8);
		gtk_tooltips_set_tip ( tips, bt, text_utf8, GW_REF_CATEGORIES_EDIT_BOX_CLOSE_BUTTON_TOOLTIPS);
		g_free ( text_utf8);
		GTK_WIDGET_SET_FLAGS ( bt, GTK_CAN_FOCUS);

		gtk_window_add_accel_group ( GTK_WINDOW ( w), accel);
	}

	if ( !GTK_WIDGET_VISIBLE ( w) ) {
#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : show the window\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		gtk_widget_show_all ( w);
	} else {
#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : destroy the window\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		gtk_widget_destroy ( w);
	}

	gw_categories_edit_box_load_categories_list ( GTK_WINDOW ( w));

	return GTK_WINDOW ( w);
}


gint gw_categories_edit_box_load_categories_list ( GtkWindow *w) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCategory **categories = NULL;
	gint i = 0;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && context != NULL ) {
		plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
		if ( (categories = plugin->gw_db_catalog_get_db_categories ( context)) != NULL ) {
			for ( i = 0; categories[i] != NULL; i++ ) {
				if ( strcmp ( _("none"), gw_db_category_get_name ( categories[i])) != 0 ) {
					gw_categories_edit_box_add_category ( w, categories[i]);
				} else {
					gw_db_category_free ( categories[i]);
				}
			}

			g_free ( categories);
		}
		
		result = 0;
	}

	gw_categories_edit_box_set_add_state ( w);

	return result;
}


gint gw_categories_edit_box_update_click ( GtkWidget *bt, GtkWindow *w) {
	GWDBCategory *category = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (category = gw_categories_edit_box_get_category ( w)) != NULL ) {
			gw_categories_edit_box_set_category_name ( w, gw_db_category_get_name ( category));
			gw_categories_edit_box_set_category_description ( w, gw_db_category_get_description ( category));

			gw_categories_edit_box_set_update_state ( w);

			result = 0;
		}
	}

	return result;
}


gint gw_categories_edit_box_remove_click ( GtkWidget *bt, GtkWindow *w) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCategory *category = NULL, *real_category = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (category = gw_categories_edit_box_get_category ( w)) != NULL ) {
			if ( context != NULL) {
				if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
					real_category = plugin->gw_db_catalog_get_db_category ( context, gw_db_category_get_ref ( category));
					
					if ( gw_db_category_can_removed ( real_category)) {
						gw_categories_edit_box_remove_category ( w);

						gw_categories_edit_box_set_category_name ( w, "");
						gw_categories_edit_box_set_category_description ( w, "");

						gw_categories_edit_box_set_add_state ( w);
						gw_notebook_managment_refresh_categories ( gw_categories_edit_box_get_main_window ( w));

						result = 0;
					} else {
						gw_msg_box_create ( w, _( "Remove category"), _( "Can't remove this category. It's used by an item."));
					}

					gw_db_category_free ( real_category);
				} else {
				}
			} else {}

//			if ( gw_db_category_can_removed ( category) ) {
//				gw_categories_edit_box_remove_category ( w);
//
//				gw_categories_edit_box_set_category_name ( w, "");
//				gw_categories_edit_box_set_category_description ( w, "");
//
//				gw_categories_edit_box_set_add_state ( w);
//
//				result = 0;
//			} else {
//				gw_msg_box_create ( w, _( "Remove category"), _( "Can't remove this category. It's used by an item."));
//			}
		}
	}

	return result;
}


gint gw_categories_edit_box_add_update_click ( GtkWidget *bt, GtkWindow *w) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( gw_categories_edit_box_get_isadd_state ( w) ) {
			gw_categories_edit_box_add_category ( w, NULL);

			gw_categories_edit_box_set_category_name ( w, "");
			gw_categories_edit_box_set_category_description ( w, "");
	
			gw_categories_edit_box_set_add_state ( w);
			gw_notebook_managment_refresh_categories ( gw_categories_edit_box_get_main_window ( w));

			result = 0;
		} else if ( gw_categories_edit_box_get_isupdate_state ( w) ) {
			gw_categories_edit_box_update_category ( w);

			gw_categories_edit_box_set_category_name ( w, "");
			gw_categories_edit_box_set_category_description ( w, "");

			gw_categories_edit_box_set_add_state ( w);
			gw_notebook_managment_refresh_categories ( gw_categories_edit_box_get_main_window ( w));

			result = 0;
		} else {
			/* If they're no state */
		}
	}

	return result;
}


gboolean gw_categories_edit_box_list_select_row ( GtkCList *list, gint line, gint column, GdkEvent *event, GtkWindow *w) {
	GtkButton *bt = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		gw_categories_edit_box_set_category_name ( w, "");
		gw_categories_edit_box_set_category_description ( w, "");

		if ( (bt = gw_categories_edit_box_get_update_category_button ( w)) != NULL ) {
			gtk_widget_set_sensitive ( GTK_WIDGET ( bt), TRUE);
		}

		if ( (bt = gw_categories_edit_box_get_remove_category_button ( w)) != NULL ) {
			gtk_widget_set_sensitive ( GTK_WIDGET ( bt), TRUE);
		}

		gw_categories_edit_box_set_add_state ( w);

		result = TRUE;
	}

	return result;
}


gint gw_categories_edit_box_set_category_name ( GtkWindow *w, gchar *category_name) {
	GtkEntry *entry = NULL;
	gchar *text_utf8 = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (entry = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_NAME_ENTRY)) != NULL ) {
			g_strdup_to_gtk_text ( category_name, text_utf8);
			gtk_entry_set_text ( entry, text_utf8);
			g_free ( text_utf8);

			result = 0;
		}
	}

	return result;
}


gint gw_categories_edit_box_set_category_description ( GtkWindow *w, gchar *category_description) {
	GtkTextArea *txt = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (txt = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_DESCRIPTION_TEXT)) != NULL ) {
			gtk_text_area_clear ( GTK_TEXT_AREA ( txt));
			gtk_text_area_insert ( GTK_TEXT_AREA ( txt), category_description);

			result = 0;
		}
	}

	return result;
}


gint gw_categories_edit_box_set_add_state ( GtkWindow *w) {
	GtkButton *bt = NULL;
	gchar *text_utf8 = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (bt = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON)) != NULL ) {
			g_strdup_to_gtk_text ( _( "Add"), text_utf8);
			gtk_label_set_text ( GTK_LABEL ( GTK_BIN ( bt)->child), text_utf8);
			g_free ( text_utf8);

			result = 0;
		}
	}

	return result;
}


gint gw_categories_edit_box_set_update_state ( GtkWindow *w) {
	GtkButton *bt = NULL;
	gchar *text_utf8 = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (bt = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON)) != NULL ) {
			g_strdup_to_gtk_text ( _( "Update"), text_utf8);
			gtk_label_set_text ( GTK_LABEL ( GTK_BIN ( bt)->child), text_utf8);
			g_free ( text_utf8);

			result = 0;
		}
	}

	return result;
}


gint gw_categories_edit_box_add_category ( GtkWindow *w, GWDBCategory *p) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCategory *category = NULL;
	GtkCList *list = NULL;
	gchar *info[2];
	guint row;
	gint result = -1;
	gchar *category_name = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		list = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORIES_LIST);

		/* Does one have to leave the program if list is NULL? */
		if ( p == NULL ) {
			category = gw_db_category_new ( );
			category_name = gw_categories_edit_box_get_category_name ( w);

			if ( category_name != NULL ) {
				if ( strlen ( category_name) > 0 ) {
					if ( context != NULL) {
						plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
						gw_db_category_set_name ( category, category_name);
						gw_db_category_set_description ( category, gw_categories_edit_box_get_category_description ( w));

						plugin->gw_db_catalog_add_db_category ( context, category);
					}
				} else {
					g_free ( category_name);
				}
			}
		} else {
			category = p;
		}

		g_strdup_to_gtk_text ( gw_db_category_get_name ( category), info[0]);
		g_strdup_to_gtk_text ( gw_db_category_get_description ( category), info[1]);
		row = gtk_clist_append ( list, info);
		//FIXME memory leak
//		gtk_clist_set_row_data ( list, row, category);
		gtk_clist_set_row_data_full ( list, row, category, (GtkDestroyNotify)gw_db_category_free);
		g_free ( info[0]);
		g_free ( info[1]);

		result = 0;
	}

	return result;
}


gint gw_categories_edit_box_update_category ( GtkWindow *w) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCategory *category = NULL;
	GtkCList *list = NULL;
	gchar *text_utf8 = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL && context != NULL ) {
		if ( (category = gw_categories_edit_box_get_category ( w)) != NULL ) {
			if ( (list = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORIES_LIST)) != NULL ) {
				if ( list->selection != NULL ) {
					plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
					gw_db_category_set_name ( category, gw_categories_edit_box_get_category_name ( w));
					gw_db_category_set_description ( category, gw_categories_edit_box_get_category_description ( w));

					plugin->gw_db_category_update ( context, category);

					g_strdup_to_gtk_text ( gw_db_category_get_name ( category), text_utf8);
					gtk_clist_set_text ( list, (gint)(list->selection->data), 0, text_utf8);
					g_free ( text_utf8);
					g_strdup_to_gtk_text ( gw_db_category_get_description ( category), text_utf8);
					gtk_clist_set_text ( list, (gint)(list->selection->data), 1, text_utf8);
					g_free ( text_utf8);

					result = 0;
				}
			}
		}
	}

	return result;
}


gint gw_categories_edit_box_remove_category ( GtkWindow *w) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCategory *category = NULL;
	GtkCList *list = NULL;
	/* Remove category isn't implemented yet. */
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (category = gw_categories_edit_box_get_category ( w)) != NULL ) {
			if ( (list = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORIES_LIST)) != NULL ) {
				if ( list->selection != NULL ) {
					if ( context != NULL) {
						plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);

						gtk_clist_remove ( list, (gint)(list->selection->data));

						plugin->gw_db_catalog_remove_db_category ( context, gw_db_category_get_ref ( category));

						result = 0;
					}
				}
			}
		}
	}

	return result;
}


GtkWindow * gw_categories_edit_box_get_main_window ( GtkWindow *w) {
	GtkWindow *window = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		window = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_MAIN_WINDOW);
	}

	return window;
}


GtkButton * gw_categories_edit_box_get_update_category_button ( GtkWindow *w) {
	GtkButton *bt = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		bt = GTK_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_UPDATE_BUTTON));
	}

	return bt;
}


GtkButton * gw_categories_edit_box_get_remove_category_button ( GtkWindow *w) {
	GtkButton *bt = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		bt = GTK_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_REMOVE_BUTTON));
	}

	return bt;
}


GtkButton * gw_categories_edit_box_get_add_update_category_button ( GtkWindow *w) {
	GtkButton *bt = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		bt = GTK_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON));
	}

	return bt;
}


GWDBCategory * gw_categories_edit_box_get_category ( GtkWindow *w) {
	GWDBCategory *category = NULL;
	GtkCList *list = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (list = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORIES_LIST)) != NULL ) {
			if ( list->selection != NULL ) {
				category = gtk_clist_get_row_data ( list, (gint)(list->selection->data));
			}
		}
	}

	return category;
}


gchar * gw_categories_edit_box_get_category_name ( GtkWindow *w) {
	GtkEntry *entry = NULL;
	gchar *category_name = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		entry = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_NAME_ENTRY);

		if ( entry != NULL ) {
			g_strdup_from_gtk_text ( gtk_entry_get_text ( entry), category_name);
		}
	}

	return category_name;
}


gchar * gw_categories_edit_box_get_category_description ( GtkWindow *w) {
	GtkTextArea *txt = NULL;
	gchar *category_description = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		txt = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_CATEGORY_DESCRIPTION_TEXT);

		if ( txt != NULL ) {
			category_description = gtk_text_area_get_text ( GTK_TEXT_AREA ( txt));
		}
	}

	return category_description;
}


gboolean gw_categories_edit_box_get_isadd_state ( GtkWindow *w) {
	GtkButton *bt = NULL;
	gchar *label = NULL;
	gchar *text_utf8 = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		bt = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON);

		if ( bt != NULL ) {
			gtk_label_get ( GTK_LABEL ( GTK_BIN ( bt)->child), &label);
			g_strdup_to_gtk_text ( _( "Add"), text_utf8);

			if ( strcmp ( label, text_utf8) == 0 ) {
				result = TRUE;
			}

			g_free ( text_utf8);
		}
	}

	return result;
}


gboolean gw_categories_edit_box_get_isupdate_state ( GtkWindow *w) {
	GtkButton *bt = NULL;
	gchar *label = NULL;
	gchar *text_utf8 = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		bt = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_CATEGORIES_EDIT_BOX_ADD_UPDATE_BUTTON);

		if ( bt != NULL ) {
			gtk_label_get ( GTK_LABEL ( GTK_BIN ( bt)->child), &label);
			g_strdup_to_gtk_text ( _( "Update"), text_utf8);

			if ( strcmp ( label, text_utf8) == 0 ) {
				result = TRUE;
			}

			g_free ( text_utf8);
		}
	}

	return result;
}


gboolean gw_categories_edit_box_category_name_changed ( GtkWidget *entry, GtkWindow *w) {
	GtkButton *bt = NULL;
	gboolean result = FALSE;
	gchar *category_name = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (bt = gw_categories_edit_box_get_add_update_category_button ( w)) != NULL ) {
			category_name = gw_categories_edit_box_get_category_name ( w);

			if ( (category_name != NULL) && (strlen ( category_name) > 0) ) {
				gtk_widget_set_sensitive ( GTK_WIDGET ( bt), TRUE);
			} else {
				gtk_widget_set_sensitive ( GTK_WIDGET ( bt), FALSE);
			}

			if ( category_name != NULL ) {
				g_free ( category_name);
			}
		}
	}

	return result;
}



gboolean gw_categories_edit_box_category_description_changed ( GtkWidget *text, GtkWindow *w) {
	GtkButton *bt = NULL;
	gboolean result = FALSE;
	gchar *category_name = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( (bt = gw_categories_edit_box_get_add_update_category_button ( w)) != NULL ) {
			category_name = gw_categories_edit_box_get_category_name ( w);

			if ( (category_name != NULL) && (strlen ( category_name) > 0) ) {
				gtk_widget_set_sensitive ( GTK_WIDGET ( bt), TRUE);
			} else {
				gtk_widget_set_sensitive ( GTK_WIDGET ( bt), FALSE);
			}

			if ( category_name != NULL ) {
				g_free ( category_name);
			}
		}
	}

	return result;
}
