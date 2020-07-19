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
#include "gwmenuactioncallback.h"

#include "gwcategorieseditbox.h"
#include "gwmsgbox.h"

#include "../gwguimanager.h"


gboolean gw_menu_action_expand_all_click ( GtkMenuItem *m, GtkWindow *w)
{
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (root = gw_gui_manager_main_interface_get_tree_root ( )) != NULL )
		{
			if ( (tree = gw_gui_manager_main_interface_get_tree ( )) != NULL )
			{
				gtk_clist_freeze ( GTK_CLIST ( tree));
				gtk_ctree_expand_recursive ( tree, root);
				gtk_clist_thaw ( GTK_CLIST ( tree));

				result = TRUE;
			}
		}
	}

	return result;
}


gboolean gw_menu_action_expand_disks_click ( GtkMenuItem *m, GtkWindow *w)
{
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;
	GtkCTreeNode *child = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (root = gw_gui_manager_main_interface_get_tree_root ( )) != NULL )
		{
			if ( (tree = gw_gui_manager_main_interface_get_tree ( )) != NULL )
			{
				gtk_clist_freeze ( GTK_CLIST ( tree));
				child = GTK_CTREE_ROW ( root)->children;
				while ( child != NULL )
				{
					gtk_ctree_collapse_recursive ( tree, child);
					child = GTK_CTREE_ROW ( child)->sibling;
				}

				gtk_ctree_expand_to_depth ( tree, root, 1);
				gtk_clist_thaw ( GTK_CLIST ( tree));

				result = TRUE;
			}
		}
	}

	return result;
}


gboolean gw_menu_action_collapse_all_click ( GtkMenuItem *m, GtkWindow *w)
{
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (root = gw_gui_manager_main_interface_get_tree_root ( )) != NULL )
		{
			if ( (tree = gw_gui_manager_main_interface_get_tree ( )) != NULL )
			{
				gtk_clist_freeze ( GTK_CLIST ( tree));
				gtk_ctree_collapse_recursive ( tree, root);
				gtk_clist_thaw ( GTK_CLIST ( tree));

				result = TRUE;
			}
		}
	}

	return result;
}


gboolean gw_menu_action_edit_categories_click ( GtkMenuItem *m, GtkWindow *w)
{
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (root = gw_gui_manager_main_interface_get_tree_root ( )) != NULL )
		{
			if ( (tree = gw_gui_manager_main_interface_get_tree ( )) != NULL )
			{
				gw_categories_edit_box_create ( w, gtk_ctree_node_get_row_data ( tree, root));

				result = TRUE;
			}
		}
		else
		{
			gw_msg_box_create ( w, _( "Edit categories"), _( "No catalog is opened : cannot edit categories"));
		}
	}

	return result;
}
