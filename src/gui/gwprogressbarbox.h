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


#ifndef GW_GUI_PROGRESS_BAR_BOX_H
#define GW_GUI_PROGRESS_BAR_BOX_H


/*!
 * @header	gwprogressbarbox.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 *		This is a dialog box window with a progress bar. It's usefull to indicate progress state of a process.<br>
 * @abstract	This is a GUI component.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwprogressbarbox.c
 * @author	Author <zero@gwhere.org>
 */


/*! @define	STATE_OK	The ok state */
#define STATE_OK 1
/*! @define	STATE_CANCEL	The cancel state */
#define STATE_CANCEL 2


/*!
 * @typedef	func_stop_progress_t
 * 		Specifies the type of the value stop function passed to
 *		gw_progress_bar_box_create(). The function stop the progress
 *		represented by the progress bar box.
 * @abstract	Functions specification
 * @param	ob	the invoker
 * @param	p	the information structure which manage process
 */
typedef gboolean (*func_stop_progress_t)(GtkObject *ob, gpointer p);


/*!
 * @function	gw_progress_bar_box_create
 * @abstract	Creates the progress bar box window.
 * @discussion	This function creates the progress bar box window. If stop
 *		is <i>NULL</i> the default function is
 *		gw_progress_bar_box_ok_cancel_click().<br>
 *		Doesn't show the progress bar when max is 0.
 * @param	window	parent window
 * @param	title	the window title
 * @param	subject	the window subject
 * @param	text	the message to display
 * @param	max	the maximum value of the progress bar
 * @param	stop	function to stop progress
 * @param	p	data to use with callbacks
 * @result	the message box window.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWindow * gw_progress_bar_box_create ( GtkWindow *window, gchar *title, gchar *subject, gchar *text, gfloat max, func_stop_progress_t stop, gpointer p);


/*!
 * @function	gw_progress_bar_box_get_parent_window
 * @abstract	Gets the parent window.
 * @discussion	This function gets the parent window.
 * @param	w	the progress bar box window to get parent window
 * @result	The parent window of the progress bar.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWindow * gw_progress_bar_box_get_parent_window ( GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_get_progress_bar
 * @abstract	Gets the real progress bar.
 * @discussion	This function gets the real progress bar.
 * @param	w	the progress bar box window to get the real progress bar
 * @result	The real progress bar.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkProgress * gw_progress_bar_box_get_progress_bar ( GtkWindow *w);

/*!
 * @function	gw_progress_bar_box_get_ok_cancel_button
 * @abstract	Gets the ok/cancel button.
 * @discussion	This function gets the ok/cancel button.
 * @param	w	the progress bar box window to get the ok/cancel button
 * @result	The ok/cancel button.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkButton * gw_progress_bar_box_get_ok_cancel_button ( GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_get_iscancel_state
 * @abstract	Checks if Ok/Cancel button is in "Cancel mode".
 * @discussion	This function checks if Ok/Cancel button is in "Cancel mode".<br>
 * @param	w		the progress bar box
 * @result	is in "Cancel mode".<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_progress_bar_box_get_iscancel_state ( GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_get_isok_state
 * @abstract	Checks if Ok/Cancel button is in "Ok mode".
 * @discussion	This function checks if Ok/Cancel button is in "Ok mode".<br>
 * @param	w		the progress bar box
 * @result	is in "Ok mode".<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_progress_bar_box_get_isok_state ( GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_get_text
 * @abstract	Gets the text of the progress bar.
 * @discussion	This function gets the text of the progress bar.
 * @param	w	the progress bar box window to get text
 * @result	The text of the progress bar. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_progress_bar_box_get_text ( GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_get_state
 * @abstract	Gets the state of the progress bar.
 * @discussion	This function gets the state of the progress bar.
 * @param	w	the progress bar box window to get text
 * @result	The state of the progress bar. It could be STATE_OK or STATE_CANCEL.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_progress_bar_box_get_state ( GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_get_value
 * @abstract	Gets the value of the progress bar.
 * @discussion	This function gets the value of the progress bar.
 * @param	w	the progress bar box window to get value
 * @result	The value of the progress bar.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gfloat gw_progress_bar_box_get_value ( GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_get_percentage
 * @abstract	Gets the percentage of the progress bar.
 * @discussion	This function gets the percentage of the progress bar.
 * @param	w	the progress bar box window to get percentage
 * @result	The percentage of the progress bar.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gfloat gw_progress_bar_box_get_percentage ( GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_set_value
 * @abstract	Sets a value to the progress bar.
 * @discussion	This function sets a value to the progress bar.
 * @param	w	the progress bar box window
 * @param	value	the value to set
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_progress_bar_box_set_value ( GtkWindow *w, gfloat value);


/*!
 * @function	gw_progress_bar_box_add_value
 * @abstract	Add a value to current statment of the progress bar.
 * @discussion	This function adds a value to current statment of the progress bar.
 * @param	w	the progress bar box window
 * @param	value	the value to set
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_progress_bar_box_add_value ( GtkWindow *w, gfloat value);


/*!
 * @function	gw_progress_bar_box_set_percentage
 * @abstract	Sets a percentage to the progress bar.
 * @discussion	This function sets a percentage to the progress bar.
 * @param	w	the progress bar box window
 * @param	percentage	the percentage to set
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_progress_bar_box_set_percentage ( GtkWindow *w, gfloat percentage);


/*!
 * @function	gw_progress_bar_box_set_text
 * @abstract	Sets a text to the progress bar box.
 * @discussion	This function sets a text to the progress bar box.
 * @param	w	the progress bar box window
 * @param	text	the text to set
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_progress_bar_box_set_text ( GtkWindow *w, gchar *file_name);


/*!
 * @function	gw_progress_bar_box_set_state
 * @abstract	Sets the state of the progress bar box.
 * @discussion	This function sets the state of the progress bar box.
 * @param	w	the progress bar box window
 * @param	state	the state of progress bar (STATE_OK or STATE_CANCEL)
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_progress_bar_box_set_state ( GtkWindow *w, gint state);


/*!
 * @function	gw_progress_bar_box_set_ok_state
 * @abstract	Sets Ok/Cancel button in Ok mode.
 * @discussion	This function sets in "Ok mode" the Ok/Cancel button.<br>
 * @param	w		the progress bar box
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_progress_bar_box_set_ok_state ( GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_set_cancel_state
 * @abstract	Sets Ok/Cancel button in Cancel mode.
 * @discussion	This function sets in "Cancel mode" the Ok/Cancel button.<br>
 * @param	w		the progress bar box
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_progress_bar_box_set_cancel_state ( GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_ok_cancel_click
 * @abstract	Do Ok or Cancel for the progress bar box.
 * @discussion	This function execute the ok or cancel function for
 *		the progress bar box.<br>
 *		This function call when the user click on ok/cancel
 *		button.<br>
 * @param	w	the progress bar box
 * @result	an error code.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_progress_bar_box_ok_cancel_click ( GtkWidget *bt, GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_ok_click
 * @abstract	Ok the progress bar box.
 * @discussion	This function oks the progress bar box. This is the
 *		default ok callback function.<br>
 *		This function call when the user click on ok button,
 *		but doesn't do nothing.<br>
 * @param	w	the progress bar box
 * @result	an error code.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */


gboolean gw_progress_bar_box_ok_click ( GtkWidget *bt, GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_cancel_click
 * @abstract	Cancels the progress bar box.
 * @discussion	This function cancels the progress bar box. this is
 *		the default cancel callback function.<br>
 *		This function call when the user click on cancel button,
 *		but doesn't do nothing.<br>
 * @param	w	the progress bar box
 * @result	an error code.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_progress_bar_box_cancel_click ( GtkWidget *bt, GtkWindow *w);


/*!
 * @function	gw_progress_bar_box_destroy
 * @abstract	Destroys the progress bar box window.
 * @discussion	This function destroys the progress bar box window.<br>
 *		<b>Warning :<b> today this function doesn't do nothing.
 *		Before implements this function, must to change the
 *		signals connexions in gw_progress_bar_box_create().
 * @param	w	the object invoker
 * @param	p	a pointer (free today)
 * @result	Return <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured
 */
gboolean gw_progress_bar_box_destroy ( GtkObject *w, gpointer *p);


/*!
 * @function	gw_progress_bar_box_dignal_do_nothing
 * @abstract	Does nothing.
 * @discussion	This function doesn't do anything. It's must be connect
 *		to a signal to cancel it.
 * @param	ob	the object invoker
 * @param	p	a pointer (free today)
 * @result	Return <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_progress_bar_box_signal_do_nothing ( GtkObject *ob, gpointer p);


#endif
