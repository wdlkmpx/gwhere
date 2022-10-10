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
#include "gwstatusbarcallback.h"

#include <string.h> /* strcmp */

#include "data/gwdata.h"
#include "tools/gwtools.h"

#include "gwapplicationmanager.h"
#include "gwhelper.h"
#include "gwstatusbar.h"


gint gw_status_bar_put_msg_catalog ( GtkWindow *w, GtkCTree *ctree, GtkCTreeNode *root, gint num, gdouble size) {
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
	GWDBCatalog *catalog = NULL;
	gchar *msg1, *msg2;
	gchar *tmp = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : total size is %e\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, size);
#endif

	if ( w != NULL ) {
		catalog = plugin->gw_db_catalog_get_db_catalog ( context);

		msg1 = g_strdup_printf ( _( " %s [ %s ], total disks : %d"), gw_helper_db_catalog_get_usefull_name ( catalog), gw_helper_db_catalog_get_full_name ( catalog), num);
		msg2 = g_strdup_printf ( _( " Listed Items : %d (total size : %s)"), num, (tmp = gw_d_byte_to_str_format ( size)));
		if ( tmp != NULL ) g_free ( tmp);

		result = gw_status_bar_put_messages ( w, msg1, msg2);

		g_free ( msg1);
		g_free ( msg2);
		gw_db_catalog_free ( catalog);

		result = 0;
	}


	return result;
}


gint gw_status_bar_put_msg_disk ( GtkWindow *w, gchar *name, gchar *type, guint64 capacity, guint64 free, gdouble size, gint num)
{
	gchar *msg1, *msg2;
	gint result = -1;
	gchar * text1, * text2;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		if ( name != NULL && type != NULL) {
			text1 = gw_ui64_byte_to_str_format (capacity);
			text2 = gw_ui64_byte_to_str_format (free);
			msg1 = g_strdup_printf ( _( " %s [ %s ], capacity : %s, free : %s"), name, type, text1, text2);
			if (text1) g_free (text1);
			if (text2) g_free (text2);

			if ( num == -1 ) {
				msg2 = g_strdup ( _( " Empty disk"));
			} else if ( num == 0 ) {
				text1 = gw_d_byte_to_str_format (size);
				msg2 = g_strdup_printf ( _( " Selected Item : %d (total size : %s)"), 1, text1);
				if (text1) g_free (text1);
			} else {
				text1 = gw_d_byte_to_str_format (size);
				msg2 = g_strdup_printf ( _( " Listed Items : %d (total size : %s)"), num, text1);
				if (text1) g_free (text1);
			}

			result = gw_status_bar_put_messages ( w, msg1, msg2);

			g_free ( msg1);
			g_free ( msg2);
		} else {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : name or type are NULL\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}
	} else {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : parent window is NULL\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return result;
}


gint gw_status_bar_put_msg_dir ( GtkWindow *w, gchar *name, gdouble size, gint nb_files, gint nb_subfolders, gint num) {
	gchar *msg1, *msg2;
	gint result = -1;
	gchar * text1;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		text1 = gw_d_byte_to_str_format (size);
		msg1 = g_strdup_printf ( _( " Folder \"%s\", %s (files %d, subfolders %d)"), name, text1, nb_files, nb_subfolders);
		if (text1) g_free (text1);

		text1 = gw_d_byte_to_str_format (size);
		if ( num == 0 ) {
			msg2 = g_strdup_printf ( _( " Selected Item : %d (total size : %s)"), 1, text1);
		} else {
			msg2 = g_strdup_printf ( _( " Listed Items : %d (total size : %s)"), num, text1);
		}
		if (text1) g_free (text1);

		result = gw_status_bar_put_messages ( w, msg1, msg2);

		g_free ( msg1);
		g_free ( msg2);
	}

	return result;
}


gint gw_status_bar_put_msg_file ( GtkWindow *w, gchar *name, gdouble size, gchar *date, gint num) {
	gchar *msg1, *msg2;
	gint result = -1;
	gchar *text1;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		text1 = gw_d_byte_to_str_format ( size);
		msg1 = g_strdup_printf ( _( " %s, %s, %s"), name, text1, date);
		if (text1) g_free (text1);

		text1 = gw_d_byte_to_str_format ( size);
		msg2 = g_strdup_printf ( _( " Selected Item : %d (total size : %s)"), num, text1);
		if (text1) g_free (text1);

		result = gw_status_bar_put_messages ( w, msg1, msg2);
		g_free ( msg1);
		g_free ( msg2);
	}

	return result;
}


gint gw_status_bar_set_catalog_explorer_page ( GtkWindow *w, gint n) {
	gchar *msg = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		msg = g_strdup_printf ( _( " Selected Item : %d"), n);
		result = gw_status_bar_put_messages ( w, _( " Catalog explorer"), msg);
		g_free ( msg);
	}

	return result;
}


gint gw_status_bar_set_catalog_search_page ( GtkWindow *w, gint n) {
	gchar *msg = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		msg = g_strdup_printf ( _( " Selected Item : %d"), n);
		result = gw_status_bar_put_messages ( w, _( " Search engine"), msg);
		g_free ( msg);
	}

	return result;
}


gint gw_status_bar_set_catalog_managment_page ( GtkWindow *w) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		result = gw_status_bar_put_messages ( w, _( " Catalog managment"), "");
	}

	return result;
}
