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
#include "gwcomboboxcategories.h"

#include <string.h> /* strcmp */
#include "../gwapplicationmanager.h"
#include "../gwpluginsmanager.h"


/*! @define	GW_REF_CMB_BOX_CATEGORIES_CMB	The real combo */
#define GW_REF_CMB_BOX_CATEGORIES_CMB "gw_ref_cmb_box_categories_cmb"


GtkHBox * gw_combo_box_categories_create ( GtkWindow *w, gchar *title, GWDBCatalog *catalog) {
	GtkWidget *hb, *lbl, *cmb;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Vertical box for categories */
	hb = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width ( GTK_CONTAINER ( hb), 2);

	/* Title label for categories */
	if ( title != NULL ) {
		g_strdup_to_gtk_text ( title, text_utf8);
		lbl = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_box_pack_start ( GTK_BOX ( hb), lbl, FALSE, FALSE, 0);
	}

	/* Combo box for categories */
	cmb = gtk_combo_new ( );
	gtk_widget_ref ( cmb);
	gtk_combo_set_use_arrows_always ( GTK_COMBO ( cmb), TRUE);
	gtk_object_set_data_full ( GTK_OBJECT ( hb), GW_REF_CMB_BOX_CATEGORIES_CMB, cmb, (GtkDestroyNotify) gtk_widget_unref);
	gtk_entry_set_editable ( GTK_ENTRY ( GTK_COMBO ( cmb)->entry), FALSE);
	gtk_box_pack_start ( GTK_BOX ( hb), cmb, TRUE, TRUE, 0);

	return GTK_HBOX ( hb);
}


gint gw_combo_box_categories_load ( GtkHBox *cbc) {
	GList *categories = NULL;
	GList *glist = NULL;
	GtkCombo *cmb = NULL;
	gchar *text_utf8 = NULL;
	gint result = -1;
	gint i = 0;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (cmb = gw_combo_box_categories_get_combo ( cbc)) != NULL ) {
		if ( (glist = gw_combo_box_categories_get_categories ( cbc)) == NULL ) {
			glist = g_list_append ( glist, "");
			gtk_combo_set_popdown_strings ( cmb, glist);

			result = -1;
		} else {
			glist = g_list_first ( glist);

			while ( glist != g_list_last ( glist)) {
				categories = g_list_append ( categories, gw_db_category_get_name ( (GWDBCategory*)glist->data));
				glist = g_list_next ( glist);
			}

			categories = g_list_append ( categories, gw_db_category_get_name ( glist->data));

			if ( categories != NULL ) {
				gtk_combo_set_popdown_strings ( cmb, categories);
			}

			if ( categories != NULL ) {
				g_strdup_to_gtk_text ( g_list_first ( categories)->data, text_utf8);
				gtk_entry_set_text ( GTK_ENTRY ( cmb->entry), text_utf8);

				g_free ( text_utf8);

				result = 0;
			} else {
				/*gtk_entry_set_text ( GTK_ENTRY ( cmb->entry), _("none"));*/
				result = -1;
			}

			glist = g_list_first ( glist);
			for ( i = 0; i < g_list_length ( glist); i++) {
				gw_db_category_free ( g_list_nth_data ( glist, i));
			}
			g_list_free ( glist);
			g_list_free ( categories);
		}
	}

	return result;
}


gint category_ref_cmp ( gpointer src, gpointer dst) {
	GWDBCategory *category = src;


	if (src != NULL && gw_db_category_get_ref ( category) == dst) {
		return 0;
	} else {
		return -1;
	}
}


gint gw_combo_box_categories_set_selected_category ( GtkHBox *cbc, GWDBCategoryPK ref) {
	GList *categories = NULL;
	GList *selection = NULL;
	GtkCombo *cmb;
	gchar *text_utf8 = NULL;
	gint result = -1;
	gint i = 0;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (cbc != NULL) && (ref != NULL) ) {
		if ( (categories = gw_combo_box_categories_get_categories ( cbc)) != NULL ) {
			if ( (selection = g_list_find_custom ( categories, ref, (GCompareFunc)category_ref_cmp)) != NULL ) {
				cmb = gw_combo_box_categories_get_combo ( cbc);
				g_strdup_to_gtk_text ( gw_db_category_get_name ( selection->data), text_utf8);
				gtk_entry_set_text ( GTK_ENTRY ( cmb->entry), text_utf8);
				g_free ( text_utf8);

				result = 0;
			}

			for ( i = 0; i < g_list_length ( categories); i++) {
				gw_db_category_free ( g_list_nth_data ( categories, i));
			}
			g_list_free ( categories);
		}
	}

	return result;
}


gint category_name_cmp ( gpointer src, gpointer dst) {
	GWDBCategory *category = src;
	gchar *name = dst;


	if ( dst != NULL && src != NULL && strcmp ( name, gw_db_category_get_name ( category)) == 0 ) {
		return 0;
	} else {
		return -1;
	}
}


gint gw_combo_box_categories_set_selected_category_name ( GtkHBox *cbc, gchar *name) {
	GList *categories = NULL;
	GList *selection = NULL;
	GtkCombo *cmb;
	gchar *text_utf8 = NULL;
	gint result = -1;
	gint i = 0;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (cbc != NULL) && (name != NULL) ) {
		if ( (categories = gw_combo_box_categories_get_categories ( cbc)) != NULL ) {
			if ( (selection = g_list_find_custom ( categories, name, (GCompareFunc)category_name_cmp)) != NULL ) {
				cmb = gw_combo_box_categories_get_combo ( cbc);
				g_strdup_to_gtk_text ( g_list_first ( selection)->data, text_utf8);
				gtk_entry_set_text ( GTK_ENTRY ( cmb->entry), text_utf8);
				g_free ( text_utf8);

				result = 0;
			}

			for ( i = 0; i < g_list_length ( categories); i++) {
				gw_db_category_free ( g_list_nth_data ( categories, i));
			}
			g_list_free ( categories);
		}
	}

	return result;
}


GWDBCategory * gw_combo_box_categories_get_selected_category ( GtkHBox *cbc) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	gchar *name;
	GWDBCategory *category = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( cbc != NULL && context != NULL ) {
		name = gw_combo_box_categories_get_selected_category_name ( cbc);

		if ( name != NULL ) {
			plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
			category = plugin->gw_db_catalog_get_db_category_by_name ( context, name);
			g_free ( name);
		}
	}

	return category;
}


gchar * gw_combo_box_categories_get_selected_category_name ( GtkHBox *cbc) {
	GtkCombo *cmb = NULL;
	gchar *category_name = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( cbc != NULL ) {
		if ( (cmb = gtk_object_get_data ( GTK_OBJECT ( cbc), GW_REF_CMB_BOX_CATEGORIES_CMB)) != NULL) {
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( cmb->entry)), category_name);
		}
	}

	return category_name;
}


GtkCombo * gw_combo_box_categories_get_combo ( GtkHBox *cbc) {
	GtkCombo *combo = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( cbc != NULL ) {
		combo = GTK_COMBO ( gtk_object_get_data ( GTK_OBJECT ( cbc), GW_REF_CMB_BOX_CATEGORIES_CMB));
	}

	return combo;
}


GList * gw_combo_box_categories_get_categories ( GtkHBox *cbc) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCategory **categories = NULL;
	GList *result = NULL;
	gint i = 0;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( cbc != NULL && context != NULL) {
		plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
		if ( (categories = plugin->gw_db_catalog_get_db_categories ( context)) != NULL ) {
			for ( i = 0; categories[i]!=NULL; i++) {
				result = g_list_append ( result, categories[i]);
			}

			g_free ( categories);
		}
	}

	return result;
}
