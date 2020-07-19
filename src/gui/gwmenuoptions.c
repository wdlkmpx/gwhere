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
#include "gwmenuoptions.h"

#include <gdk/gdkkeysyms.h>

#include "gwmenuoptionscallback.h"


/*! @define	GW_REF_MENU_BAR_OPTIONS_MENU_HEADER	The options menu header reference */
#define GW_REF_MENU_BAR_OPTIONS_MENU_HEADER "gw_menu_bar_options_menu_header"
/*! @define	GW_REF_MENU_BAR_OPTIONS_MENU	The options menu reference */
#define GW_REF_MENU_BAR_OPTIONS_MENU "gw_menu_bar_options_menu"
/*! @define	GW_REF_MENU_BAR_OPTIONS_MENU_SETTINGS	The options menu -> settings reference */
#define GW_REF_MENU_BAR_OPTIONS_MENU_SETTINGS "gw_menu_bar_options_menu_settings"


GtkWidget * gw_menu_options_create ( GtkWindow *w, GtkAccelGroup *ag, GtkWidget *parent)
{
	GtkWidget *gw_menu_options_header = NULL;
	GtkWidget *menu_options = NULL;
	GtkWidget *gw_menu_options_settings = NULL;
	GtkAccelGroup *gw_menu_options_ag = NULL;
	guint tmp_key;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		/* Menu action header */
		gw_menu_options_header = gtk_menu_item_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "_Options"), text_utf8);
		tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_options_header)->child), text_utf8);
		g_free ( text_utf8);
#if defined ( HAVE_GTK12)
		gtk_widget_add_accelerator ( gw_menu_options_header, "activate-item", ag, tmp_key, GDK_MOD1_MASK, 0);
#endif
		gtk_widget_ref ( gw_menu_options_header);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_OPTIONS_MENU_HEADER, gw_menu_options_header, (GtkDestroyNotify) gtk_widget_unref);

		menu_options = gtk_menu_new ( );
		gtk_widget_ref ( menu_options);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_OPTIONS_MENU, menu_options, (GtkDestroyNotify) gtk_widget_unref);
		gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_options_header), menu_options);
#if defined ( HAVE_GTK12)
		gw_menu_options_ag = gtk_menu_ensure_uline_accel_group ( GTK_MENU ( menu_options));
#else
		gw_menu_options_ag = gtk_accel_group_new ( );
#endif

		/* Menu action -> edit categories */
		gw_menu_options_settings = gtk_menu_item_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "Se_ttings"), text_utf8);
		tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_options_settings)->child), text_utf8);
		g_free ( text_utf8);
#if defined ( HAVE_GTK12)
		gtk_widget_add_accelerator ( gw_menu_options_settings, "activate-item", gw_menu_options_ag, tmp_key, 0, 0);
#endif
		gtk_widget_ref ( gw_menu_options_settings);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_OPTIONS_MENU_SETTINGS, gw_menu_options_settings, (GtkDestroyNotify) gtk_widget_unref);
		gtk_container_add ( GTK_CONTAINER ( menu_options), gw_menu_options_settings);
		gtk_widget_add_accelerator ( gw_menu_options_settings, "activate", ag, GDK_t, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
		gtk_signal_connect ( GTK_OBJECT ( gw_menu_options_settings), "activate", GTK_SIGNAL_FUNC ( gw_menu_options_settings_click), w);
	}

	return gw_menu_options_header;
}
