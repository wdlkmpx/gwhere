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
#include "gwmenuaction.h"

#include <gdk/gdkkeysyms.h>

#include "gwmenuactioncallback.h"


/*! @define	GW_REF_MENU_BAR_ACTION_MENU_HEADER	The action menu header reference */
#define GW_REF_MENU_BAR_ACTION_MENU_HEADER "gw_menu_bar_action_menu_header"
/*! @define	GW_REF_MENU_BAR_ACTION_MENU	The action menu reference */
#define GW_REF_MENU_BAR_ACTION_MENU "gw_menu_bar_action_menu"
/*! @define	GW_REF_MENU_BAR_ACTION_MENU_EXPAND_ALL	The action menu -> expand all reference */
#define GW_REF_MENU_BAR_ACTION_MENU_EDIT_EXPAND_ALL "gw_menu_bar_action_menu_expand_all"
/*! @define	GW_REF_MENU_BAR_ACTION_MENU_EXPAND_DISKS	The action menu -> expand disk reference */
#define GW_REF_MENU_BAR_ACTION_MENU_EDIT_EXPAND_DISKS "gw_menu_bar_action_menu_expand_disks"
/*! @define	GW_REF_MENU_BAR_ACTION_MENU_COLLAPSE_ALL	The action menu -> collapse all reference */
#define GW_REF_MENU_BAR_ACTION_MENU_EDIT_COLLAPSE_ALL "gw_menu_bar_action_menu_collapse_all"
/*! @define	GW_REF_MENU_BAR_ACTION_MENU_SEPARATOR	The action menu -> separator reference */
#define GW_REF_MENU_BAR_ACTION_MENU_SEPARATOR "gw_menu_bar_action_menu_separator"
/*! @define	GW_REF_MENU_BAR_ACTION_MENU_EDIT_CATEGORIES	The action menu -> edit categories reference */
#define GW_REF_MENU_BAR_ACTION_MENU_EDIT_CATEGORIES "gw_menu_bar_action_menu_edit_categories"


GtkWidget * gw_menu_action_create ( GtkWindow *w, GtkAccelGroup *ag, GtkWidget *parent)
{
	GtkWidget *gw_menu_action_header = NULL;
	GtkWidget *menu_action = NULL;
	GtkWidget *gw_menu_action_expand_all = NULL;
	GtkWidget *gw_menu_action_expand_disks = NULL;
	GtkWidget *gw_menu_action_collapse_all = NULL;
	GtkWidget *gw_menu_action_edit_categories = NULL;
	GtkWidget *gw_menu_action_separator = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Menu action header */
	gw_menu_action_header = gtk_menu_item_new_with_mnemonic (_("_Action"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_ACTION_MENU_HEADER, gw_menu_action_header);

	menu_action = gtk_menu_new ( );
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_ACTION_MENU, menu_action);
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_action_header), menu_action);

	/* Menu action -> expand all */
	gw_menu_action_expand_all = gtk_menu_item_new_with_mnemonic (_("_Expand all"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_ACTION_MENU_EDIT_EXPAND_ALL, gw_menu_action_expand_all);
	gtk_container_add ( GTK_CONTAINER ( menu_action), gw_menu_action_expand_all);
	g_signal_connect (G_OBJECT ( gw_menu_action_expand_all), "activate", G_CALLBACK ( gw_menu_action_expand_all_click), w);

	/* Menu action -> expand disks */
	gw_menu_action_expand_disks = gtk_menu_item_new_with_mnemonic (_("Expand only _disks"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_ACTION_MENU_EDIT_EXPAND_DISKS, gw_menu_action_expand_disks);
	gtk_container_add ( GTK_CONTAINER ( menu_action), gw_menu_action_expand_disks);
	gtk_widget_add_accelerator ( gw_menu_action_expand_disks, "activate", ag, GDK_KEY(d), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (G_OBJECT ( gw_menu_action_expand_disks), "activate", G_CALLBACK ( gw_menu_action_expand_disks_click), w);

	/* Menu action -> collapse */
	gw_menu_action_collapse_all = gtk_menu_item_new_with_mnemonic (_("C_ollapse all"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_ACTION_MENU_EDIT_COLLAPSE_ALL, gw_menu_action_collapse_all);
	gtk_container_add ( GTK_CONTAINER ( menu_action), gw_menu_action_collapse_all);
	g_signal_connect (G_OBJECT ( gw_menu_action_collapse_all), "activate", G_CALLBACK ( gw_menu_action_collapse_all_click), w);

	/* Menu action -> separator */
	gw_menu_action_separator = gtk_menu_item_new ( );
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_ACTION_MENU_SEPARATOR, gw_menu_action_separator);
	gtk_container_add ( GTK_CONTAINER ( menu_action), gw_menu_action_separator);
	gtk_widget_set_sensitive ( gw_menu_action_separator, FALSE);

	/* Menu action -> edit categories */
	gw_menu_action_edit_categories = gtk_menu_item_new_with_mnemonic (_("Edit _categories"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_ACTION_MENU_EDIT_CATEGORIES, gw_menu_action_edit_categories);
	gtk_container_add ( GTK_CONTAINER ( menu_action), gw_menu_action_edit_categories);
	gtk_widget_add_accelerator ( gw_menu_action_edit_categories, "activate", ag, GDK_KEY(c), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (G_OBJECT ( gw_menu_action_edit_categories), "activate", G_CALLBACK ( gw_menu_action_edit_categories_click), w);

	return gw_menu_action_header;
}
