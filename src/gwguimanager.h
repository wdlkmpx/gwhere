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


/*!
 * @header	gwguimanager.h
 * 		GWhere<br>
 * 		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 * 		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 * 		This component was developed for the GWhere project.<br><br>
 * 		GWhere is a GUI application (Graphical User Interface). This interface contains many components. In order to acces to
 * 		theses components the API many functions.<br><br>
 * 		All graphical components are GtkWidget. Theses widget can be referenced to the application with the function :<br>
 * 		<i>gtk_object_set_data_full ( gtk_object_referencer, "reference_object", gtk_object_referenced, (GtkDestroyNotify) gtk_widget_unref);</i><br><br>
 * 		<div align="center"><table border="1">
 * 			<tr>
 * 				<td>Name</td>
 * 				<td>Type</td>
 * 				<td>Desription</td>
 * 			</tr>
 * 		</table></div>
 * @abstract	This is a component to manage GWhere GUI.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwguimanager.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_MANAGER_H
#define GW_GUI_MANAGER_H


/*!
 * @function	gw_gui_manager_main_interface_create
 * @abstract	Creates the main window.
 * @discussion	This function creates the main application window.
 * 		This window can be destroyed when exit program.
 * @result	the main window.<br>
 * 		Returns <i>NULL</i> when an error occured.
 */
GtkWindow * gw_gui_manager_main_interface_create ( void);


/*!
 * @function	gw_gui_manager_main_interface_set_tree_root
 * @abstract	Sets the tree's root explorer of the catalog.
 * @discussion	This function sets the tree's root explorer the catalog.
 * @param	node	the new node of catalog
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_gui_manager_main_interface_set_tree_root ( GtkCTreeNode *node);


/*!
 * @function	gw_gui_manager_main_interface_get_main_window
 * @abstract	Gets the main window of application.
 * @discussion	This function gets the main window of the application.
 * @result	the main window.
 */
GtkWindow * gw_gui_manager_main_interface_get_main_window ( void);


/*!
 * @function	gw_gui_manager_main_interface_get_progress_bar_box
 * @abstract	Gets the progress bar box.
 * @discussion	This function gets the progress bar box.
 * @result	the progress bar box.
 */
GtkWindow * gw_gui_manager_main_interface_get_progress_bar_box ( void);


/*!
 * @function	gw_gui_manager_main_interface_get_tree
 * @abstract	Gets the tree explorer of the catalog.
 * @discussion	This function gets the tree explorer the catalog.
 * @result	the tree catalog.
 */
GtkCTree * gw_gui_manager_main_interface_get_tree ( void);


/*!
 * @function	gw_gui_manager_main_interface_get_tree_root
 * @abstract	Gets the tree's root explorer of the catalog.
 * @discussion	This function gets the tree's root explorer the catalog.
 * @result	the tree's root catalog.
 */
GtkCTreeNode * gw_gui_manager_main_interface_get_tree_root ( void);


/*!
 * @function	gw_gui_manager_main_interface_refresh
 * @abstract	Refreshes the graphical interface of application.
 * @discussion	This function refreshes the graphical interface of application.
 */
void gw_gui_manager_main_interface_refresh ( void);


/*!
 * @function	gw_gui_manager_main_interface_update_all
 * @abstract	Updates all GUI components.
 * @discussion	This function updates all GUI components.
 */
void gw_gui_manager_main_interface_update_all ( void);


/*!
 * @function	gw_gui_manager_main_interface_update_menus
 * @abstract	Updates all menus.
 * @discussion	This function updates all menus.
 */
void gw_gui_manager_main_interface_update_menus ( void);


/*!
 * @function	gw_gui_manager_main_interface_update_notebook_catalog
 * @abstract	Updates the notebook catalog.
 * @discussion	This function updates the notebook catalog.
 */
void gw_gui_manager_main_interface_update_notebook_catalog ( void);


/*!
 * @function	gw_gui_manager_main_interface_update_notebook_managment
 * @abstract	Updates the notebook managment.
 * @discussion	This function updates the notebook managment.
 */
void gw_gui_manager_main_interface_update_notebook_managment ( void);


/*!
 * @function	gw_gui_manager_main_interface_update_notebook_search
 * @abstract	Updates the notebook search.
 * @discussion	This function updates the notebook search.
 */
void gw_gui_manager_main_interface_update_notebook_search ( void);


/*!
 * @function	gw_gui_manager_exit
 * @abstract	Called when exit program.
 * @discussion	This function is called when exit program.
 */

void gw_gui_manager_exit ( void);


#endif
