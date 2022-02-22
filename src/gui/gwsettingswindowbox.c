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
#include "gwsettingswindowbox.h"

#include "gwsettingswindowboxcallback.h"
#include "gwsettingsinterface.h"
#include "gwsettingsgeneral.h"
#include "gwsettingsgui.h"
#include "gwsettingscatalogfile.h"
#include "gwsettingsexplorer.h"
#include "gwsettingssearch.h"

#include "../gwapplicationmanager.h"

/*! @define	GW_REF_SETTINGS_WINDOW_BOX_PARENT_WINDOW	The parent window */
#define GW_REF_SETTINGS_WINDOW_BOX_PARENT_WINDOW "gw_ref_settings_window_box_parent_window"
/*! @define	GW_REF_SETTINGS_WINDOW_BOX_CTREE	The settings ctree */
#define GW_REF_SETTINGS_WINDOW_BOX_CTREE "gw_ref_settings_window_box_ctree"
/*! @define	GW_REF_SETTINGS_WINDOW_BOX_NOTEBOOK	The settings notebook */
#define GW_REF_SETTINGS_WINDOW_BOX_NOTEBOOK "gw_ref_settings_window_box_notebook"
/*! @define	GW_REF_SETTINGS_WINDOW_BOX_OK_BTN	The ok button */
#define GW_REF_SETTINGS_WINDOW_BOX_OK_BTN "gw_ref_settings_window_box_ok_btn"
/*! @define	GW_REF_SETTINGS_WINDOW_BOX_CANCEL_BTN	The cancel button */
#define GW_REF_SETTINGS_WINDOW_BOX_CANCEL_BTN "gw_ref_settings_window_box_cancel_btn"
/*! @define	GW_REF_SETTINGS_WINDOW_BOX_APPLY_BTN	The apply button */
#define GW_REF_SETTINGS_WINDOW_BOX_APPLY_BTN "gw_ref_settings_window_box_apply_btn"

static gboolean gw_settings_window_box_load_sections ( GtkWindow *settings);


GtkWindow * gw_settings_window_box_create ( GtkWindow *window)
{
	static GtkWidget *settings_window_box = NULL;
	GtkWidget *vb_settings;
	GtkWidget *hp_settings;
	GtkWidget *ctree_settings;
	GtkWidget *lbl_settings;
	GtkWidget *notebook_settings;
	GtkWidget *home_notebook_page;
	GtkWidget *text_home_notebook_page;
	GtkWidget *btn_ok;
	GtkWidget *btn_cancel;
	GtkWidget *btn_apply;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( !settings_window_box )
	{
		settings_window_box = gtk_dialog_new ();
		gtk_widget_set_tooltip_text (settings_window_box,
		                             _( "This Settings box allows to configure some functionnalities and properties of the program."));

		gtk_window_set_title ( GTK_WINDOW ( settings_window_box), _( "Settings"));
		gtk_window_set_modal ( GTK_WINDOW ( settings_window_box), TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( settings_window_box), window);
		gtk_window_set_position ( GTK_WINDOW ( settings_window_box), GTK_WIN_POS_CENTER);
		gtk_window_set_policy ( GTK_WINDOW ( settings_window_box), TRUE, TRUE, FALSE);
/*		gtk_widget_set_size_request ( settings_window_box, 600, 400);
		gtk_window_set_default_size ( GTK_WINDOW ( settings_window_box), 600, 400);
*/		g_signal_connect (G_OBJECT ( settings_window_box), "destroy", G_CALLBACK ( gw_settings_window_box_closed), window);
		g_signal_connect (G_OBJECT ( settings_window_box), "destroy", G_CALLBACK ( gtk_widget_destroyed), &settings_window_box);

		g_object_set_data (G_OBJECT ( settings_window_box), GW_REF_SETTINGS_WINDOW_BOX_PARENT_WINDOW, window);

		vb_settings = gtk_dialog_get_content_area (GTK_DIALOG (settings_window_box));

		hp_settings = gtk_hpaned_new ( );
		gtk_box_pack_start ( GTK_BOX ( vb_settings), hp_settings, TRUE, TRUE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hp_settings), 5);
		gtk_paned_set_position ( GTK_PANED ( hp_settings), 180);

		ctree_settings = gtk_ctree_new ( 1, 0);
		gtk_clist_set_column_width ( GTK_CLIST ( ctree_settings), 0, 170);
		gtk_clist_column_titles_show ( GTK_CLIST ( ctree_settings));
		g_object_ref ( ctree_settings);
		g_object_set_data_full (G_OBJECT ( settings_window_box), GW_REF_SETTINGS_WINDOW_BOX_CTREE, ctree_settings, (GDestroyNotify) g_object_unref);
		gtk_paned_pack1 ( GTK_PANED ( hp_settings), ctree_settings, FALSE, TRUE);
		gtk_container_set_border_width ( GTK_CONTAINER ( ctree_settings), 5);
		gtk_widget_set_tooltip_text (ctree_settings, _( "Select the section to configure."));

		lbl_settings = gtk_label_new (_( "Settings"));
		gtk_clist_set_column_widget ( GTK_CLIST ( ctree_settings), 0, lbl_settings);

		notebook_settings = gtk_notebook_new ( );
		g_object_ref ( notebook_settings);
		g_object_set_data_full (G_OBJECT ( settings_window_box), GW_REF_SETTINGS_WINDOW_BOX_NOTEBOOK, notebook_settings, (GDestroyNotify) g_object_unref);
		gtk_paned_pack2 ( GTK_PANED ( hp_settings), notebook_settings, TRUE, TRUE);
		GTK_WIDGET_UNSET_FLAGS ( notebook_settings, GTK_CAN_FOCUS);
		gtk_widget_set_tooltip_text (notebook_settings,
		                             _( "Change in this pane all availables properties in order to configure the program as you want."));
		gtk_notebook_set_show_tabs ( GTK_NOTEBOOK ( notebook_settings), FALSE);
		gtk_notebook_set_show_border ( GTK_NOTEBOOK ( notebook_settings), FALSE);
		gtk_notebook_set_scrollable ( GTK_NOTEBOOK ( notebook_settings), TRUE);
		gtk_notebook_popup_enable ( GTK_NOTEBOOK ( notebook_settings));

		home_notebook_page = gtk_vbox_new ( FALSE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( home_notebook_page), 5);
		gtk_container_add ( GTK_CONTAINER ( notebook_settings), home_notebook_page);
		text_home_notebook_page = gtk_label_new (_( "This settings windows box allows to configure the program. Some properties may be modified here."));
		gtk_label_set_justify ( GTK_LABEL ( text_home_notebook_page), GTK_JUSTIFY_FILL);
		gtk_label_set_line_wrap ( GTK_LABEL ( text_home_notebook_page), TRUE);
		gtk_container_add ( GTK_CONTAINER ( home_notebook_page), text_home_notebook_page);

		/* The OK/Cancel button area */
		btn_ok = gtk_dialog_add_button (GTK_DIALOG (settings_window_box), _("_OK"), GTK_RESPONSE_OK);
		g_object_set_data (G_OBJECT ( settings_window_box), GW_REF_SETTINGS_WINDOW_BOX_OK_BTN, btn_ok);
		gtk_widget_set_tooltip_text (btn_ok, _( "Click on OK button to apply changes and close the Settings box."));
		gtk_widget_grab_default ( btn_ok);

		btn_cancel = gtk_dialog_add_button (GTK_DIALOG (settings_window_box), _("_Cancel"), GTK_RESPONSE_CANCEL);
		g_object_set_data (G_OBJECT ( settings_window_box), GW_REF_SETTINGS_WINDOW_BOX_CANCEL_BTN, btn_cancel);

		btn_apply = gtk_dialog_add_button (GTK_DIALOG (settings_window_box), _("_Apply"), GTK_RESPONSE_APPLY);
		g_object_set_data (G_OBJECT ( settings_window_box), GW_REF_SETTINGS_WINDOW_BOX_APPLY_BTN, btn_apply);
		gtk_widget_set_tooltip_text (btn_apply, _( "Click on Apply button to apply changes (without close the Settings box)."));
		gtk_widget_set_sensitive ( GTK_WIDGET ( btn_apply), FALSE);

		g_signal_connect (G_OBJECT ( ctree_settings), "change_focus_row_expansion", G_CALLBACK (gw_settings_window_box_tree_change_focus_row_expansion), GTK_WINDOW ( settings_window_box));
		g_signal_connect (G_OBJECT ( ctree_settings), "tree_collapse", G_CALLBACK (gw_settings_window_box_tree_collapse), GTK_WINDOW ( settings_window_box));
		g_signal_connect (G_OBJECT ( ctree_settings), "tree_expand", G_CALLBACK (gw_settings_window_box_tree_expand), GTK_WINDOW ( settings_window_box));
		g_signal_connect (G_OBJECT ( ctree_settings), "tree_move", G_CALLBACK (gw_settings_window_box_tree_move), GTK_WINDOW ( settings_window_box));
		g_signal_connect (G_OBJECT ( ctree_settings), "tree_select_row", G_CALLBACK (gw_settings_window_box_tree_select_row), GTK_WINDOW ( settings_window_box));
		g_signal_connect (G_OBJECT ( ctree_settings), "tree_unselect_row", G_CALLBACK (gw_settings_window_box_tree_unselect_row), GTK_WINDOW ( settings_window_box));
		g_signal_connect (G_OBJECT ( notebook_settings), "switch_page", G_CALLBACK (gw_settings_window_box_noteboox_settings_switch_page), GTK_WINDOW ( settings_window_box));
		g_signal_connect (G_OBJECT ( btn_ok), "clicked", G_CALLBACK (gw_settings_window_box_btn_ok_clicked), GTK_WINDOW ( settings_window_box));
		g_signal_connect (G_OBJECT ( btn_cancel), "clicked", G_CALLBACK (gw_settings_window_box_btn_cancel_clicked), GTK_WINDOW ( settings_window_box));
		g_signal_connect (G_OBJECT ( btn_apply), "clicked", G_CALLBACK (gw_settings_window_box_btn_apply_clicked), GTK_WINDOW ( settings_window_box));

		gtk_widget_grab_focus ( btn_ok);

		gw_settings_window_box_load_sections ( GTK_WINDOW ( settings_window_box));
	}

	if ( !gtk_widget_get_visible ( settings_window_box) )
	{
#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : show the window\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		gtk_widget_show_all ( settings_window_box);
	}
	else
	{
#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : destroy the window\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		gtk_widget_destroy ( settings_window_box);
	}

	return GTK_WINDOW ( settings_window_box);
}


static gboolean gw_settings_window_box_load_sections ( GtkWindow *settings)
{
	gboolean result = FALSE;
	GtkCTree *settings_ctree = NULL;
	GtkNotebook *notebook_settings = NULL;
	GtkCTreeNode *settings_node = NULL;
	GtkCTreeNode *parent_settings_node = NULL;
	GdkPixmap *pix = NULL;
	GdkBitmap *pix_mask = NULL;
	GtkWidget *section_notebook_page = NULL;
	GtkWidget *section_notebook_pane = NULL;
	GtkWidget *frm_section_notebook_page = NULL;
	GWSettingsModule *modules[6];
	gint i, j;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* General options. */
	gw_plugin_settings_general_init ( &modules[0]);
	/* General options. */
	gw_plugin_settings_gui_init ( &modules[1]);
	/* Catalog file. */
	gw_plugin_settings_catalog_file_init ( &modules[2]);
	/* Explorer. */
	gw_plugin_settings_explorer_init ( &modules[3]);
	/* Search. */
	gw_plugin_settings_search_init ( &modules[4]);

	for ( i = 0; i < 5; i++)
	{
		if ( gw_settings_module_check ( modules[i]) == FALSE )
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : invalid settings module -> %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, modules[i]->name);
#endif
			gw_settings_module_free ( modules[i]);
			modules[i] = NULL;
		}
	}

	settings_ctree = gw_settings_window_box_get_ctree ( settings);
	notebook_settings = gw_settings_window_box_get_notebook ( settings);

	gtk_clist_freeze ( GTK_CLIST ( settings_ctree));

	for ( i = 0; i < 5; i++)
	{
		if ( modules[i] != NULL )
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : current settings module -> %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, modules[i]->name);
#endif
			section_notebook_page = NULL;
			section_notebook_pane = NULL;

			section_notebook_page = gtk_vbox_new ( FALSE, 0);
			gtk_container_set_border_width ( GTK_CONTAINER ( section_notebook_page), 5);
			gtk_notebook_append_page  ( notebook_settings, section_notebook_page, NULL);

			/* Creates the settings module pane and init all fields. */
			modules[i]->create ( settings, GTK_CONTAINER ( section_notebook_page), &section_notebook_pane);
			modules[i]->pane = section_notebook_pane;
			modules[i]->page = GTK_CONTAINER ( section_notebook_page);
			modules[i]->settings_window = settings;

			/* Stores a settings module reference to the notebook page. */
			g_object_set_data (G_OBJECT ( section_notebook_page), GW_REF_SETTINGS_MODULE, modules[i]);
			g_object_set_data (G_OBJECT ( notebook_settings), g_strdup_printf ( "%d", i), modules[i]);

			/* Creates a new entry in the settings module tree explorer. */
			parent_settings_node = settings_node = gtk_ctree_insert_node ( GTK_CTREE ( settings_ctree), NULL, NULL,
			                                           &modules[i]->name, 3, pix, pix_mask, pix, pix_mask, FALSE, TRUE);

			frm_section_notebook_page = gtk_frame_new (modules[i]->name);
			gtk_container_add ( GTK_CONTAINER ( section_notebook_page), frm_section_notebook_page);
			gtk_container_add ( GTK_CONTAINER ( frm_section_notebook_page), modules[i]->pane);

			gtk_ctree_node_set_row_data ( GTK_CTREE ( settings_ctree), settings_node, modules[i]);

			/* Loads all children module. */
			if ( modules[i]->child != NULL )
			{
				for ( j = 0; modules[i]->child[j] != NULL; j++)
				{
					if ( gw_settings_module_check ( modules[i]->child[j]) == TRUE )
					{
#ifdef GW_DEBUG_GUI_COMPONENT
						g_print ( "*** GW - %s (%d) :: %s() : current settings module -> %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, modules[i]->child[j]->name);
#endif
						section_notebook_page = gtk_vbox_new ( FALSE, 0);
						gtk_container_set_border_width ( GTK_CONTAINER ( section_notebook_page), 5);
						gtk_notebook_append_page  ( notebook_settings, section_notebook_page, NULL);
						/* Creates the settings module pane and init all fields. */
						modules[i]->child[j]->create ( settings, GTK_CONTAINER ( section_notebook_page), &section_notebook_pane);
						modules[i]->child[j]->pane = section_notebook_pane;
						modules[i]->child[j]->page = GTK_CONTAINER ( section_notebook_page);
						modules[i]->child[j]->settings_window = settings;
						/* Stores a settings module reference to the notebook page. */
						g_object_set_data (G_OBJECT ( section_notebook_page), GW_REF_SETTINGS_MODULE, modules[i]->child[j]);
						g_object_set_data (G_OBJECT ( notebook_settings), g_strdup_printf ( "%d", j), modules[i]->child[j]);
						/* Creates a new entry in the settings module tree explorer. */
						settings_node = gtk_ctree_insert_node ( GTK_CTREE ( settings_ctree), parent_settings_node, NULL,
						                                       &modules[i]->child[j]->name, 3, pix, pix_mask, pix, pix_mask, FALSE, TRUE);
						frm_section_notebook_page = gtk_frame_new (modules[i]->child[j]->name);
						gtk_container_add ( GTK_CONTAINER ( section_notebook_page), frm_section_notebook_page);
						gtk_container_add ( GTK_CONTAINER ( frm_section_notebook_page), modules[i]->child[j]->pane);

						gtk_ctree_node_set_row_data ( GTK_CTREE ( settings_ctree), settings_node, modules[i]->child[j]);
					}
				}
			}
		}
	}

	gtk_clist_thaw ( GTK_CLIST ( settings_ctree));

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : all settings module are loaded\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	result = TRUE;
}


gint gw_settings_window_box_set_modified ( GtkWindow *w, gboolean state)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : state is %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, state);
#endif

	if ( w != NULL )
	{
		gw_settings_window_box_apply_button_set_enable ( w, state);

		result = 0;
	}

	return result;
}


GtkCTree * gw_settings_window_box_get_ctree ( GtkWindow *w)
{
	GtkCTree *ctree = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		ctree = g_object_get_data (G_OBJECT ( w), GW_REF_SETTINGS_WINDOW_BOX_CTREE);
	}

	return ctree;
}


GtkNotebook * gw_settings_window_box_get_notebook ( GtkWindow *w)
{
	GtkNotebook *notebook = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		notebook = g_object_get_data (G_OBJECT ( w), GW_REF_SETTINGS_WINDOW_BOX_NOTEBOOK);
	}

	return notebook;
}

GtkButton * gw_settings_window_box_get_ok_button ( GtkWindow *w)
{
	GtkButton *button = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		button = g_object_get_data (G_OBJECT ( w), GW_REF_SETTINGS_WINDOW_BOX_OK_BTN);
	}

	return button;
}


GtkButton * gw_settings_window_box_get_cancel_button ( GtkWindow *w)
{
	GtkButton *button = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		button = g_object_get_data (G_OBJECT ( w), GW_REF_SETTINGS_WINDOW_BOX_CANCEL_BTN);
	}

	return button;
}


GtkButton * gw_settings_window_box_get_apply_button ( GtkWindow *w)
{
	GtkButton *button = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		button = g_object_get_data (G_OBJECT ( w), GW_REF_SETTINGS_WINDOW_BOX_APPLY_BTN);
	}

	return button;
}


GtkWindow * gw_settings_window_box_get_main_window ( GtkWindow *w)
{
	GtkWindow *window = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		window = g_object_get_data (G_OBJECT ( w), GW_REF_SETTINGS_WINDOW_BOX_PARENT_WINDOW);
	}

	return window;
}


gint gw_settings_window_box_apply_button_set_enable ( GtkWindow *w, gboolean state)
{
	gint result = -1;
	GtkButton *button = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		button = gw_settings_window_box_get_apply_button ( w);
		gtk_widget_set_sensitive ( GTK_WIDGET ( button), state);

		result = 0;
	}

	return result;
}


gboolean gw_settings_window_box_apply_button_get_enable ( GtkWindow *w)
{
	gboolean result = FALSE;
	GtkButton *button = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		button = gw_settings_window_box_get_apply_button ( w);

		if ( button != NULL )
		{
			result = gtk_widget_is_sensitive (GTK_WIDGET (button));

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : can apply = %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, result);
#endif
		}
	}

	return result;
}
