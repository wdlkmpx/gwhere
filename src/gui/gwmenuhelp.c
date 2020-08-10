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
#include "gwmenuhelp.h"

#include <gdk/gdkkeysyms.h>

#include "gwmenuhelpcallback.h"
#include "gwreferences.h"


/*! @define	GW_REF_MENU_BAR_HELP_MENU_HEADER	The help menu header reference */
#define GW_REF_MENU_BAR_HELP_MENU_HEADER "gw_menu_bar_help_menu_header"
/*! @define	GW_REF_MENU_BAR_HELP_MENU	The help menu reference */
#define GW_REF_MENU_BAR_HELP_MENU "gw_menu_bar_help_menu"
/*! @define	GW_REF_MENU_BAR_HELP_MENU_ABOUT	The help menu -> about reference */
#define GW_REF_MENU_BAR_HELP_MENU_ABOUT "gw_menu_bar_help_menu_about"


GtkWidget * gw_menu_help_create ( GtkWindow *w, GtkAccelGroup *ag, GtkWidget *parent)
{
	GtkWidget *gw_menu_help_header = NULL;
	GtkWidget *menu_help = NULL;
	GtkWidget *gw_menu_help_about = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Menu help header */
	gw_menu_help_header = gtk_menu_item_new_with_mnemonic (_( "_Help"));
	gtk_object_set_data ( GTK_OBJECT ( w), GW_REF_MENU_BAR_HELP_MENU_HEADER, gw_menu_help_header);

	menu_help = gtk_menu_new ( );
	gtk_object_set_data ( GTK_OBJECT ( w), GW_REF_MENU_BAR_HELP_MENU, menu_help);
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_help_header), menu_help);

	/* Menu help -> about */
	gw_menu_help_about = gtk_menu_item_new_with_mnemonic (_( "A_bout"));
	gtk_object_set_data ( GTK_OBJECT ( w), GW_REF_MENU_BAR_HELP_MENU_ABOUT, gw_menu_help_about);
	gtk_container_add ( GTK_CONTAINER ( menu_help), gw_menu_help_about);
	gtk_widget_add_accelerator ( gw_menu_help_about, "activate", ag, GDK_b, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_signal_connect ( GTK_OBJECT ( gw_menu_help_about), "activate", GTK_SIGNAL_FUNC ( gw_menu_help_about_click), w);

	return gw_menu_help_header;
}
