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

#include "gwreferences.h"

#include "gwwindowboxabout.h" // gw_window_box_about_create

static void
gw_menu_help_about_click (GtkMenuItem *m, gpointer user_data)
{
	gw_window_box_about_create (GTK_WINDOW(user_data));
}

GtkWidget * gw_menu_help_create ( GtkWindow *w, GtkAccelGroup *ag, GtkWidget *parent)
{
	GtkWidget *gw_menu_help_header = NULL;
	GtkWidget *menu_help = NULL;
	GtkWidget *gw_menu_help_about = NULL;

	/* Menu help header */
	gw_menu_help_header = gtk_menu_item_new_with_mnemonic (_( "_Help"));

	menu_help = gtk_menu_new ( );
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_help_header), menu_help);

	/* Menu help -> about */
	gw_menu_help_about = gtk_menu_item_new_with_mnemonic (_( "A_bout"));
	gtk_container_add ( GTK_CONTAINER ( menu_help), gw_menu_help_about);
	g_signal_connect (gw_menu_help_about, "activate",
	                  G_CALLBACK (gw_menu_help_about_click),
	                  w);

	return gw_menu_help_header;
}
