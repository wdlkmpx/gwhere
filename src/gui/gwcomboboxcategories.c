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

GtkBox * gw_combo_box_categories_create ( GtkWindow *w, gchar *title, GWDBCatalog *catalog)
{
	GtkWidget *hb, *lbl, *cmb, * combo_entry;

	/* Vertical box for categories */
	hb = gtk_hbox_new ( FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER ( hb), 2);

	/* Title label for categories */
	if ( title != NULL ) {
		lbl = gtk_label_new (title);
		gtk_box_pack_start ( GTK_BOX ( hb), lbl, FALSE, FALSE, 0);
	}

	/* Combo box for categories */
	cmb = gtk_combo_box_text_new_with_entry ();
	combo_entry = gtk_bin_get_child (GTK_BIN (cmb));
	gtk_editable_set_editable (GTK_EDITABLE (combo_entry), FALSE);

	gtk_box_pack_start ( GTK_BOX ( hb), cmb, TRUE, TRUE, 0);
	g_object_ref ( cmb);
	g_object_set_data_full (G_OBJECT ( hb), GW_REF_CMB_BOX_CATEGORIES_CMB, cmb, (GDestroyNotify) g_object_unref);

	return GTK_BOX ( hb);
}


gint gw_combo_box_categories_load ( GtkBox *cbc)
{
	GList *categories = NULL;
	GList *glist = NULL, * gl;
	GtkComboBoxText * cmb;
	gint result = -1;
	gint i = 0;
	char *name;

	cmb = gw_combo_box_categories_get_combo (cbc);
	glist = gw_combo_box_categories_get_categories (cbc);

	if (!glist) {
		return -1;
	} else {
		result = 0;
	}

	GtkTreeModel * model = gtk_combo_box_get_model (GTK_COMBO_BOX (cmb));
	gtk_list_store_clear (GTK_LIST_STORE (model));

	for (gl = glist; gl; gl = gl->next)
	{
		name = gw_db_category_get_name ((GWDBCategory*)gl->data);
		categories = g_list_append (categories, name);
		gtk_combo_box_text_append_text (cmb, name);
	}

	for (gl = glist; gl; gl = gl->next) {
		gw_db_category_free (gl->data);
	}
	g_list_free ( glist);
	g_list_free ( categories);

	return result;
}


gint category_ref_cmp ( gpointer src, gpointer dst)
{
	GWDBCategory *category = src;

	if (src != NULL && gw_db_category_get_ref ( category) == dst) {
		return 0;
	} else {
		return -1;
	}
}


gint gw_combo_box_categories_set_selected_category ( GtkBox *cbc, GWDBCategoryPK ref)
{
	GList *categories = NULL;
	GList *selection = NULL;
	GtkComboBoxText * cmb;
	GtkEntry * entry;
	gint result = -1;
	gint i = 0;

	if (ref != NULL)
	{
		if ( (categories = gw_combo_box_categories_get_categories ( cbc)) != NULL ) {
			if ( (selection = g_list_find_custom ( categories, ref, (GCompareFunc)category_ref_cmp)) != NULL ) {
				cmb = gw_combo_box_categories_get_combo ( cbc);
				char * cat_name = gw_db_category_get_name (selection->data);
				entry = GTK_ENTRY (gtk_bin_get_child (GTK_BIN (cmb)));
				gtk_entry_set_text (entry, cat_name);
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

gint category_name_cmp ( gpointer src, gpointer dst)
{
	GWDBCategory *category = src;
	gchar *name = dst;

	if ( dst != NULL && src != NULL && strcmp ( name, gw_db_category_get_name ( category)) == 0 ) {
		return 0;
	} else {
		return -1;
	}
}

gint gw_combo_box_categories_set_selected_category_name ( GtkBox *cbc, gchar *name)
{
	GList *categories = NULL;
	GList *selection = NULL;
	GtkComboBoxText * cmb;
	GtkEntry * entry;
	gint result = -1;
	gint i = 0;

	if (name)
	{
		categories = gw_combo_box_categories_get_categories (cbc);
		if (categories)
		{
			if ((selection = g_list_find_custom (categories, name, (GCompareFunc)category_name_cmp)) != NULL ) {
				cmb = gw_combo_box_categories_get_combo ( cbc);
				char * cat_name = gw_db_category_get_name (selection->data);
				entry = GTK_ENTRY (gtk_bin_get_child (GTK_BIN (cmb)));
				gtk_entry_set_text (entry, cat_name);

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


GWDBCategory * gw_combo_box_categories_get_selected_category ( GtkBox *cbc)
{
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	gchar *name;
	GWDBCategory *category = NULL;

	if (context)
	{
		name = gw_combo_box_categories_get_selected_category_name ( cbc);

		if ( name != NULL ) {
			plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
			category = plugin->gw_db_catalog_get_db_category_by_name ( context, name);
			g_free ( name);
		}
	}

	return category;
}


gchar * gw_combo_box_categories_get_selected_category_name ( GtkBox *cbc)
{
	GtkComboBoxText * cmb;
	gchar *category_name = NULL;

	cmb = g_object_get_data (G_OBJECT (cbc), GW_REF_CMB_BOX_CATEGORIES_CMB);
	category_name = gtk_combo_box_text_get_active_text (cmb);

	return category_name;
}


GtkComboBoxText * gw_combo_box_categories_get_combo (GtkBox *cbc)
{
	GtkComboBoxText *combo = NULL;
	combo = GTK_COMBO_BOX_TEXT (g_object_get_data (G_OBJECT ( cbc), GW_REF_CMB_BOX_CATEGORIES_CMB));
	return combo;
}


/* this does not require a combo */
GList * gw_combo_box_categories_get_categories ( GtkBox *cbc)
{
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCategory **categories = NULL;
	GList *result = NULL;
	gint i = 0;

	if (context != NULL) {
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
