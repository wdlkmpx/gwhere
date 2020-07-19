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


/*!
 * @header	gtktextarea.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component to text area.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2004/08/10
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gtktextarea.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GTK_TEXT_AREA_H
#define GW_GUI_GTK_TEXT_AREA_H


/* Define the GtkTextArea */
#if defined ( HAVE_GTK12)
	typedef GtkText GtkTextArea;
	#define GTK_TEXT_AREA GTK_TEXT
#elif defined ( HAVE_GTK20)
	typedef GtkTextView GtkTextArea;
	#define GTK_TEXT_AREA GTK_TEXT_VIEW
#endif


/*!
 * @function	gtk_text_area_new
 * @abstract	Create a new text area GUI component.
 * @discussion
 * @result		the text area.<br />
 *				Returns <i>NULL</i> when an error occured.<br />
 */
GtkWidget * gtk_text_area_new ( );


/* Set the editable property of GtkTextArea */
#if defined HAVE_GTK12
	#define gtk_text_area_set_editable(text,editable) gtk_text_set_editable(GTK_TEXT(text),editable)
#elif defined HAVE_GTK20
	#define gtk_text_area_set_editable(text,editable) gtk_text_view_set_editable(GTK_TEXT_VIEW(text),editable)
#endif


/*!
 * @function	gtk_text_area_clear
 * @abstract	Clear a text area GUI component
 * @discussion
 * @param		text	the text area to clear
 */
void gtk_text_area_clear ( GtkTextArea *text);


/*!
 * @function	gtk_text_area_insert
 * @abstract	Insert text in a text area GUI component
 * @discussion
 * @param		text	the text area into insert
 * @param		words	the text to insert
 */
void gtk_text_area_insert ( GtkTextArea *text, const gchar *words);


/*!
 * @function	gtk_text_area_get_text
 * @abstract	Get the text from a text area GUI component
 * @discussion
 * @param		text	the text area into get ext
 * @result		the text into the text area.<br />
 * 				Returns <i>NULL</i> when an error occured.<br />
 */
gchar * gtk_text_area_get_text ( GtkTextArea *text);


#endif
