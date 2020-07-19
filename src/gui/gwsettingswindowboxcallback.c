/*  GWhere
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
#include "gwsettingswindowboxcallback.h"

#include "gwsettingswindowbox.h"
#include "gwsettingsinterface.h"
#include "gwdialogbox.h"
#include "gwguimanager.h"


void gw_settings_window_box_tree_select_row ( GtkCTree *ctree, GList *node, gint column, GtkWindow *w)
{
	GtkNotebook *notebook_settings = NULL;
	GWSettingsModule *module = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ctree != NULL )
	{
		notebook_settings = gw_settings_window_box_get_notebook ( w);
		module = gtk_ctree_node_get_row_data ( ctree, GTK_CTREE_NODE ( node));

		if ( module != NULL )
		{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : selected settings module is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, module->name);
#endif

			/* Switches to the selected setting page. */
			gtk_notebook_set_page ( notebook_settings, gtk_notebook_page_num ( notebook_settings, GTK_WIDGET ( module->page)));
		}
	}

	return;
}


void gw_settings_window_box_tree_unselect_row ( GtkCTree *ctree, GList *node, gint column, GtkWindow *w)
{
	GtkNotebook *notebook_settings = NULL;
	GWSettingsModule *module = NULL;
	gboolean is_modified;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ctree != NULL )
	{
		notebook_settings = gw_settings_window_box_get_notebook ( w);
		is_modified = gw_settings_window_box_apply_button_get_enable ( w);

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : is modified = %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, is_modified);
#endif

		if (  is_modified == TRUE )
		{
			module = gtk_ctree_node_get_row_data ( ctree, GTK_CTREE_NODE ( node));
	
			if ( module != NULL )
			{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : current settings module is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, module->name);
#endif

				gw_dialog_box_create ( w, _( "Settings changed"), _( "If you don't apply changes you will lose all changes. Do you want apply changes?"), (GtkSignalFunc)gw_settings_window_box_apply_ok, (GtkSignalFunc)gw_settings_window_box_apply_no, (GtkSignalFunc)gw_settings_window_box_apply_cancel, module);
			}
			else
			{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : no current settings module\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
			}

/*			gw_settings_window_box_set_modified ( w, FALSE);
*/		}
		else
		{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : settings not changed\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		/* Switches to the home page of settings. */
/*		gtk_notebook_set_page ( notebook_settings, 0);
*/	}

	return;
}


void gw_settings_window_box_tree_expand ( GtkCTree *ctree, GList *node, GtkWindow *w)
{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ctree != NULL )
	{
		/* Does nothing at time. */
	}

	return;
}


void gw_settings_window_box_tree_collapse ( GtkCTree *ctree, GList *node, GtkWindow *w)
{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ctree != NULL )
	{
		/* Does nothing at time. */
	}

	return;
}


void gw_settings_window_box_tree_move ( GtkCTree *ctree, GList *node, GList *new_parent, GList *new_sibling, GtkWindow *w)
{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ctree != NULL )
	{
		/* Does nothing at time. */
	}

	return;
}


void gw_settings_window_box_tree_change_focus_row_expansion ( GtkCTree *ctree, GtkCTreeExpansionType expansion, GtkWindow *w)
{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ctree != NULL )
	{
		/* Does nothing at time. */
	}

	return;
}


void gw_settings_window_box_noteboox_settings_switch_page ( GtkNotebook *notebook, GtkNotebookPage *page, gint page_num, GtkWindow *w)
{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( notebook != NULL )
	{
		/* Does nothing at time. */
/*		gw_settings_window_box_set_modified ( w, FALSE);
*/	}

	return;
}


void gw_settings_window_box_btn_ok_clicked ( GtkButton *button, GtkWindow *w)
{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		gw_settings_window_box_btn_apply_clicked ( button, w);
		gw_settings_window_box_btn_cancel_clicked ( button, w);
	}

	return;
}


void gw_settings_window_box_btn_cancel_clicked ( GtkButton *button, GtkWindow *w)
{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		gtk_widget_destroy ( GTK_WIDGET ( w));
	}

	return;
}


void gw_settings_window_box_btn_apply_clicked ( GtkButton *button, GtkWindow *w)
{
	GtkNotebook *notebook_settings = NULL;
	GWSettingsModule *module = NULL;
	gint page = 0;
	GtkWidget *current_page = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (notebook_settings = gw_settings_window_box_get_notebook ( w)) != NULL )
		{
			page = gtk_notebook_get_current_page ( notebook_settings);
			if ( (current_page = gtk_notebook_get_nth_page ( notebook_settings, page)) != NULL )
			{
				if ( (module = gtk_object_get_data ( GTK_OBJECT ( current_page), GW_REF_SETTINGS_MODULE)) != NULL )
				{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
					g_print ( "*** GW - %s (%d) :: %s() : current settings module is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, module->name);
#endif

					module->apply ( module->pane);
				}

				/* Updates all the GUI. */
				gw_gui_manager_main_interface_update_all ( );
			}
		}
	}

	return;
}


void gw_settings_window_box_apply_ok ( GtkButton *button, GtkWindow *w)
{
	GWSettingsModule *module = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (module = gw_dialog_box_get_user_data ( w)) != NULL )
		{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : current module is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, module->name);
#endif

			module->apply ( module->pane);
		}
		else
		{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : no current module selected\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		gtk_widget_destroy ( GTK_WIDGET ( w));
	}

	return;
}


void gw_settings_window_box_apply_no ( GtkButton *button, GtkWindow *w)
{
	GWSettingsModule *module = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (module = gw_dialog_box_get_user_data ( w)) != NULL )
		{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : current module is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, module->name);
#endif

			module->load ( module->pane);

			/* BUG : it will be better to stop the "changed" signal in all load() functions. */
			gw_settings_window_box_set_modified ( module->settings_window, FALSE);
		}
		else
		{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : no current module selected\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		gtk_widget_destroy ( GTK_WIDGET ( w));
	}

	return;
}


void gw_settings_window_box_apply_cancel ( GtkButton *button, GtkWindow *w)
{
	GtkNotebook *notebook_settings = NULL;
	GWSettingsModule *module = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (module = gw_dialog_box_get_user_data ( w)) != NULL )
		{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : current module is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, module->name);
#endif

			if ( (notebook_settings = gw_settings_window_box_get_notebook ( module->settings_window)) != NULL )
			{
				/* Switches to the selected setting page. */
				gtk_notebook_set_page ( notebook_settings, gtk_notebook_page_num ( notebook_settings, GTK_WIDGET ( module->page)));
			}
		}
		else
		{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : no current module selected\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		gtk_widget_destroy ( GTK_WIDGET ( w));
	}

	return;
}


void gw_settings_window_box_closed ( GtkWindow *settings_window_box, GtkWindow *window)
{
#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (settings_window_box != NULL) && (window != NULL) )
	{
		/* Updates all the GUI. */
		gw_gui_manager_main_interface_update_all ( );
	}
}
