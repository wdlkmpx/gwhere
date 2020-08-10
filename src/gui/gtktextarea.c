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
#include "gtktextarea.h"


/* Create a new GtkTextArea */
GtkWidget * gtk_text_area_new ( )
{
	GtkWidget *text = NULL;
	text = gtk_text_view_new ( );
	return text;
}


/* Clear a GtkTextArea */
void gtk_text_area_clear ( GtkTextArea *text)
{
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;
	if ( text != NULL ) {
		buffer = gtk_text_view_get_buffer ( GTK_TEXT_VIEW ( text));
		gtk_text_buffer_get_start_iter ( buffer, &start);
		gtk_text_buffer_get_end_iter ( buffer, &end);
		gtk_text_buffer_delete ( buffer, &start, &end);
	}
	return;
}


/* Insert text in a GtkTextArea */
void gtk_text_area_insert ( GtkTextArea *text, const gchar *words)
{
	gchar *text_utf8 = NULL;
	GtkTextBuffer *buffer;
	GtkTextIter end;

	if ( text != NULL ) {
		g_strdup_to_gtk_text ( words, text_utf8);
		buffer = gtk_text_view_get_buffer ( GTK_TEXT_VIEW ( text));
		gtk_text_buffer_get_end_iter ( buffer, &end);
		gtk_text_buffer_insert ( buffer, &end, text_utf8, -1);
	}
	return;
}


/* Get text in a GtkTextArea */
gchar * gtk_text_area_get_text ( GtkTextArea *text) {
	gchar *words = NULL, *text_utf8 = NULL;
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;

	if ( text != NULL ) {
		buffer = gtk_text_view_get_buffer ( GTK_TEXT_VIEW ( text));
		gtk_text_buffer_get_start_iter ( buffer, &start);
		gtk_text_buffer_get_end_iter ( buffer, &end);
		text_utf8 = gtk_text_buffer_get_text ( buffer, &start, &end, TRUE);
	}
	/* words must be free later with g_free() */
	g_strdup_from_gtk_text ( text_utf8, words);

	if ( text_utf8 != NULL ) {
		g_free ( text_utf8);
	}

	return words;
}
