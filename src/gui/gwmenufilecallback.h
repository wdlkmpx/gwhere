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
 * @header	gwmenufilecallback.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a link component between menu bar and functionalities.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/02/11
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwmenufilecallback.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_MENU_FILE_CALLBACK_H
#define GW_GUI_GW_MENU_FILE_CALLBACK_H


/*!
 * @function	gw_menu_file_new_click
 * @abstract	Launches from menu file : new catalog.
 * @discussion	This function launches from the menu file the functionality : new catalog.
 * @param	m	menu item invoker
 * @param	w	reference to the main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_new_click ( GtkMenuItem *mi, GtkWindow *w);


/*!
 * @function	gw_menu_file_open_click
 * @abstract	Launches from menu file : open catalog.
 * @discussion	This function launches from the menu file the functionality : open catalog.
 * @param	m	menu item invoker
 * @param	w	reference to the main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_open_click ( GtkMenuItem *mi, GtkWindow *w);


/*!
 * @function	gw_menu_file_save_click
 * @abstract	Launches from menu file : save catalog.
 * @discussion	This function launches from the menu file the functionality : save catalog.
 * @param	m	menu item invoker
 * @param	w	reference to the main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_save_click ( GtkMenuItem *mi, GtkWindow *w);


/*!
 * @function	gw_menu_file_saveas_click
 * @abstract	Launches from menu file : save as catalog.
 * @discussion	This function launches from the menu file the functionality : save as catalog.
 * @param	m	menu item invoker
 * @param	w	reference to the main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_saveas_click ( GtkMenuItem *mi, GtkWindow *w);


/*!
 * @function	gw_menu_file_close_click
 * @abstract	Launches from menu file : close catalog.
 * @discussion	This function launches from the menu file the functionality : close catalog.
 * @param	m	menu item invoker
 * @param	w	reference to the main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_close_click ( GtkMenuItem *mi, GtkWindow *w);


/*!
 * @function	gw_menu_file_send_mail_click
 * @abstract	Launches from menu file : send catalog by mail.
 * @discussion	This function launches from the menu file the functionality : send catalog by mail.
 * @param	m	menu item invoker
 * @param	w	reference to the main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_send_mail_click ( GtkMenuItem *mi, GtkWindow *w);


/*!
 * @function	gw_menu_file_properties_click
 * @abstract	Launches from menu file : catalog properties.
 * @discussion	This function launches from the menu file the functionality : catalog properties.
 * @param	m	menu item invoker
 * @param	w	reference to the main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_properties_click ( GtkMenuItem *mi, GtkWindow *w);


/*!
 * @function	gw_menu_file_exit_click
 * @abstract	Launches from menu file : exit program.
 * @discussion	This function launches from the menu file the functionality : exit program.
 * @param	m	menu item invoker
 * @param	w	reference to the main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_exit_click ( GtkMenuItem *mi, GtkWindow *w);


/*!
 * @function	gw_menu_file_open_file_ok
 * @abstract	Opens the selected catalog.
 * @discussion	This function is call when the user click on OK button in the file selection box. This function opens the selected catalog
 * @param	ob	gtk object invoker
 * @param	fs	the file selection box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_open_file_ok ( GtkObject *ob, GtkFileSelection *fs);


/*!
 * @function	gw_menu_file_open_file_cancel
 * @abstract	Closes the file selection box.
 * @discussion	This function is call when the user click on Cancel button in the file selection box. This function closes the file selection box
 * @param	ob	gtk object invoker
 * @param	fs	the file selection box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_open_file_cancel ( GtkObject *ob, GtkFileSelection *fs);


/*!
 * @function	gw_menu_file_new_file_ok
 * @abstract	Creates a new catalog.
 * @discussion	This function creates a new catalog
 * @param	bt	button invoker
 * @param	w	the capture box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_new_file_ok ( GtkWidget *bt, GtkWindow *w);


/*!
 * @function	gw_menu_file_new_save_file_ok
 * @abstract	Saves the opened catalog and creates a new one.
 * @discussion	This function saves the opened catalog and creates a new one
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_new_save_file_ok ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_new_save_file_no
 * @abstract	Creates a new catalog without save the opened one.
 * @discussion	This function creates a new catalog without save the opened one
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_new_save_file_no ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_new_saveas_file_selection_ok
 * @abstract	Saves as file name the opened catalog and creates a new one.
 * @discussion	This function saves as file name the opened catalog and creates a new one
 * @param	bt	button invoker
 * @param	fs	the file selection box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_new_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs);


/*!
 * @function	gw_menu_file_open_save_file_ok
 * @abstract	Saves the opened catalog and opens one.
 * @discussion	This function saves the opened catalog and opens one
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_open_save_file_ok ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_open_save_file_no
 * @abstract	Opens a catalog without save the opened one.
 * @discussion	This function opens a catalog without save the opened one
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_open_save_file_no ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_open_saveas_file_selection_ok
 * @abstract	Saves as file name the opened catalog and opens one.
 * @discussion	This function saves as file name the opened catalog and opens one
 * @param	bt	button invoker
 * @param	fs	the file selection box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_open_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs);


/*!
 * @function	gw_menu_file_open_recents_files_save_file_ok
 * @abstract	Saves the opened catalog and opens one recent.
 * @discussion	This function saves the opened catalog and opens one recent.
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_open_recents_files_save_file_ok ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_open_recents_files_save_file_no
 * @abstract	Opens a catalog without save the opened one recent.
 * @discussion	This function opens a catalog without save the opened one recent.
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_open_recents_files_save_file_no ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_open_recents_files_saveas_file_selection_ok
 * @abstract	Saves as file name the opened catalog and opens one recent.
 * @discussion	This function saves as file name the opened catalog and opens one recent.
 * @param	bt	button invoker
 * @param	fs	the file selection box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_open_recents_files_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs);


/*!
 * @function	gw_menu_file_save_file_ok
 * @abstract	Saves the opened catalog.
 * @discussion	This function saves the opened catalog
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_save_file_ok ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_save_file_no
 * @abstract	Doesn't save the opened catalog.
 * @discussion	This function doesn't save the opened catalog
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_save_file_no ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_saveas_file_selection_ok
 * @abstract	Saves as file name the opened catalog.
 * @discussion	This function saves as file name the opened catalog
 * @param	bt	button invoker
 * @param	fs	the file selection box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs);


/*!
 * @function	gw_menu_file_close_save_file_ok
 * @abstract	Saves the opened catalog and close it.
 * @discussion	This function saves the opened catalog and close it
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_close_save_file_ok ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_close_save_file_no
 * @abstract	Closes a catalog without save it.
 * @discussion	This function closes a catalog without save it
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_close_save_file_no ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_close_saveas_file_selection_ok
 * @abstract	Saves as file name the opened catalog and closes it.
 * @discussion	This function saves as file name the opened catalog and closes it
 * @param	bt	button invoker
 * @param	fs	the file selection box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_close_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs);


/*!
 * @function	gw_menu_file_send_mail_save_file_ok
 * @abstract	Saves the opened catalog and sends it by mail.
 * @discussion	This function saves the opened catalog and sends it by mail
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_send_mail_save_file_ok ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_send_mail_save_file_no
 * @abstract	Sends a catalog by mail without save it.
 * @discussion	This function sends a catalog by mail without save it
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_send_mail_save_file_no ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_send_mail_saveas_file_selection_ok
 * @abstract	Saves as file name the opened catalog and sends it by mail.
 * @discussion	This function saves as file name the opened catalog and sends it by mail
 * @param	bt	button invoker
 * @param	fs	the file selection box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_send_mail_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs);

/*!
 * @function	gw_menu_file_exit_save_file_ok
 * @abstract	Saves the opened catalog and exits program.
 * @discussion	This function saves the opened catalog and exits program
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_exit_save_file_ok ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_exit_save_file_no
 * @abstract	Exits program without save the opened catalog.
 * @discussion	This function exits program without save the opened catalog
 * @param	bt	button invoker
 * @param	dg	the dialog box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_exit_save_file_no ( GtkWidget *bt, GtkWindow *dg);


/*!
 * @function	gw_menu_file_exit_saveas_file_selection_ok
 * @abstract	Saves as file name the opened catalog and exits program.
 * @discussion	This function saves as file name the opened catalog and exits program
 * @param	bt	button invoker
 * @param	fs	the file selection box
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_exit_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs);


/*!
 * @function	gw_menu_file_exit
 * @abstract	Exits program.
 * @discussion	This function exits the program
 */
void gw_menu_file_exit ( void);


/*!
 * @function	gw_menu_file_recents_files_item_click
 * @abstract	Loads the selected recent file.
 * @discussion	This function loads the selected recent file.
 * @param	m	menu item invoker
 * @param	data	index, notes that it is a guint variable made with GUINT_TO_POINTER()
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_file_recents_files_item_click ( GtkMenuItem *m, gpointer data);


gboolean gw_menu_file_import_item_click ( GtkMenuItem *m, gpointer data);


gboolean gw_menu_file_export_item_click ( GtkMenuItem *m, gpointer data);



#endif
