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
#include "gwmenupopup.h"

#include "gwmenufilecallback.h"
#include "gwmenupopupcallback.h"
#include "gwmisc.h"

#include "../gwguimanager.h"


GtkMenu * gw_menu_popup_create ( GtkWindow *w)
{
	GtkWidget *menu = NULL;
	GtkWidget *menuitem = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	menu = gtk_menu_new ( );

	menuitem = gtk_menu_item_new_with_label (_("New"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_new_click, w);

	menuitem = gtk_menu_item_new_with_label (_("Open"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_open_click, w);

	menuitem = gtk_menu_item_new_with_label (_( "Save"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_save_click, w);

	menuitem = gtk_menu_item_new_with_label (_("Save as"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_saveas_click, w);

	menuitem = gtk_menu_item_new_with_label (_("Close"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_close_click, w);

	menuitem = gtk_menu_item_new ( );
	gtk_menu_append ( GTK_MENU ( menu), menuitem);

	menuitem = gtk_menu_item_new_with_label (_("Exit"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_exit_click, w);

	return GTK_MENU ( menu);
}


GtkMenu * gw_menu_popup_create_and_show ( GtkWindow *w)
{
	GtkMenu *menu = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL)
	{
		if  ( (menu = gw_menu_popup_create ( w)) != NULL )
		{
			gtk_widget_show_all ( GTK_WIDGET ( menu));
		}
	}

	return menu;
}


GtkMenu * gw_menu_popup_catalog_create ( GtkCTreeNode *node, GtkWindow *w)
{
	GtkWidget *menu = NULL;
	GtkWidget *menuitem = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	menu = gtk_menu_new ( );
	menuitem = gtk_menu_item_new_with_label (_( "Rename"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_catalog_rename, node);

/*	menuitem = gtk_menu_item_new_with_label (_("Add new disk"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_catalog_add_new_disk, node);
*/
	menuitem = gtk_menu_item_new_with_label (_( "Edit description"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_catalog_edit_description, node);

	menuitem = gtk_menu_item_new_with_label (_( "Edit categories"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_catalog_edit_categories, node);

	menuitem = gtk_menu_item_new ( );
	gtk_menu_append ( GTK_MENU ( menu), menuitem);

	menuitem = gtk_menu_item_new_with_label (_( "New"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_new_click, w);

	menuitem = gtk_menu_item_new_with_label (_( "Open"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_open_click, w);

	menuitem = gtk_menu_item_new_with_label (_( "Save"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_save_click, w);

	menuitem = gtk_menu_item_new_with_label (_( "Save as"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_saveas_click, w);

	menuitem = gtk_menu_item_new_with_label (_( "Close"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_file_close_click, w);

	menuitem = gtk_menu_item_new ( );
	gtk_menu_append ( GTK_MENU ( menu), menuitem);

	menuitem = gtk_menu_item_new_with_label (_( "Properties"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_catalog_properties, node);

	return GTK_MENU ( menu);
}


GtkMenu * gw_menu_popup_catalog_create_and_show ( GtkCTreeNode *node, GtkWindow *w)
{
	GtkMenu *menu = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL)
	{
		if  ( (menu = gw_menu_popup_catalog_create ( node, w)) != NULL )
		{
			gtk_widget_show_all ( GTK_WIDGET ( menu));
		}
	}

	return menu;
}


GtkMenu * gw_menu_popup_disk_create ( GtkCTreeNode *node, GtkWindow *w)
{
	GtkWidget *menu = NULL;
	GtkWidget *menuitem = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	menu = gtk_menu_new ( );
	menuitem = gtk_menu_item_new_with_label (_( "Move To..."));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_disk_move_to, node);

	menuitem = gtk_menu_item_new_with_label (_( "Rename"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_disk_rename, node);

	menuitem = gtk_menu_item_new_with_label (_( "Delete disk"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_disk_delete, node);

	menuitem = gtk_menu_item_new_with_label (_( "Change volume label"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_disk_change_volume_label, node);

	menuitem = gtk_menu_item_new_with_label (_( "Edit description"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_disk_edit_description, node);

	menuitem = gtk_menu_item_new ( );
	gtk_menu_append ( GTK_MENU ( menu), menuitem);

	menuitem = gtk_menu_item_new_with_label (_( "Properties"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_disk_properties, node);

	return GTK_MENU ( menu);
}


GtkMenu * gw_menu_popup_disk_create_and_show ( GtkCTreeNode *node, GtkWindow *w)
{
	GtkMenu *menu = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL)
	{
		if  ( (menu = gw_menu_popup_disk_create ( node, w)) != NULL )
		{
			gtk_widget_show_all ( GTK_WIDGET ( menu));
		}
	}

	return menu;
}


GtkMenu * gw_menu_popup_dir_create ( GtkCTreeNode *node, GtkWindow *w)
{
	GtkWidget *menu = NULL;
	GtkWidget *menuitem = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	menu = gtk_menu_new ( );
	menuitem = gtk_menu_item_new_with_label (_( "Move To..."));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_folder_move_to, node);

	menuitem = gtk_menu_item_new_with_label (_( "Rename"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_folder_rename, node);

	menuitem = gtk_menu_item_new_with_label (_( "Edit description"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_folder_edit_description, node);

	menuitem = gtk_menu_item_new_with_label (_( "Remove from catalog"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_folder_remove, node);

	menuitem = gtk_menu_item_new ( );
	gtk_menu_append ( GTK_MENU ( menu), menuitem);

	menuitem = gtk_menu_item_new_with_label (_( "Properties"));
	gtk_menu_append ( GTK_MENU ( menu), menuitem);
	gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_folder_properties, node);

	return GTK_MENU ( menu);
}


GtkMenu * gw_menu_popup_dir_create_and_show ( GtkCTreeNode *node, GtkWindow *w)
{
	GtkMenu *menu = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL)
	{
		if  ( (menu = gw_menu_popup_dir_create ( node, w)) != NULL )
		{
			gtk_widget_show_all ( GTK_WIDGET ( menu));
		}
	}

	return menu;
}


GtkMenu * gw_menu_popup_file_create ( gpointer row, GtkWindow *w)
{
	GtkWidget *menu = NULL;
	GtkWidget *menuitem = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		menu = gtk_menu_new ( );

		if ( (menu != NULL) && (GPOINTER_TO_UINT ( row) >= 0) )
		{
			menuitem = gtk_menu_item_new_with_label (_( "Rename"));
			gtk_menu_append ( GTK_MENU ( menu), menuitem);
			gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_file_rename, row);

			menuitem = gtk_menu_item_new_with_label (_( "Edit description"));
			gtk_menu_append ( GTK_MENU ( menu), menuitem);
			gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_file_edit_description, row);

			menuitem = gtk_menu_item_new_with_label (_( "Remove from catalog"));
			gtk_menu_append ( GTK_MENU ( menu), menuitem);
			gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_file_remove, row);

			menuitem = gtk_menu_item_new ( );
			gtk_menu_append ( GTK_MENU ( menu), menuitem);

			menuitem = gtk_menu_item_new_with_label (_( "Properties"));
			gtk_menu_append ( GTK_MENU ( menu), menuitem);
			gtk_signal_connect ( GTK_OBJECT ( menuitem), "activate", (GtkSignalFunc)gw_menu_popup_file_properties, row);
		}
		else
		{
			gw_msg_box_create ( w, _( "Edit file"), _( "Can't edit this file!!\n"));
		}
	}

	return GTK_MENU ( menu);
}


GtkMenu * gw_menu_popup_file_create_and_show ( gpointer row, GtkWindow *w)
{
	GtkMenu *menu = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL)
	{
		if  ( (menu = gw_menu_popup_file_create ( row, w)) != NULL )
		{
			gtk_widget_show_all ( GTK_WIDGET ( menu));
		}
	}

	return menu;
}
