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
#include "gwmenu.h"
#include "gwsettingswindowbox.h"

#include <gdk/gdkkeysyms.h>

static void
gw_menu_options_settings_click (GtkMenuItem *m, gpointer w)
{
	if (w) {
		gw_settings_window_box_create (GTK_WINDOW (w));
	}
}


GtkWidget * gw_menu_options_create ( GtkWindow *w, GtkAccelGroup *ag, GtkWidget *parent)
{
	GtkWidget *gw_menu_options_header = NULL;
	GtkWidget *menu_options = NULL;
	GtkWidget *gw_menu_options_settings = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		/* Menu action header */
		gw_menu_options_header = gtk_menu_item_new_with_mnemonic (_("_Options"));

		menu_options = gtk_menu_new ( );
		gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_options_header), menu_options);

		/* Menu action -> edit categories */
		gw_menu_options_settings = gtk_menu_item_new_with_mnemonic (_("Se_ttings"));
		gtk_container_add ( GTK_CONTAINER ( menu_options), gw_menu_options_settings);
		gtk_widget_add_accelerator ( gw_menu_options_settings, "activate", ag, GDK_t, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
		gtk_signal_connect ( GTK_OBJECT ( gw_menu_options_settings), "activate", GTK_SIGNAL_FUNC ( gw_menu_options_settings_click), w);
	}

	return gw_menu_options_header;
}
