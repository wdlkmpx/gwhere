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
GtkWidget * gtk_text_area_new ( ) {
	GtkWidget *text = NULL;


#if defined HAVE_GTK12
	text = gtk_text_new ( NULL, NULL);
#elif defined HAVE_GTK20
	text = gtk_text_view_new ( );
#endif

	return text;
}


/* Clear a GtkTextArea */
void gtk_text_area_clear ( GtkTextArea *text) {
#if defined HAVE_GTK12
	if ( text != NULL ) {
		gtk_text_freeze ( GTK_TEXT ( text));
		gtk_text_set_point ( GTK_TEXT ( text), 0);
		gtk_text_forward_delete ( GTK_TEXT ( text), gtk_text_get_length ( GTK_TEXT ( text)));
		gtk_text_thaw ( GTK_TEXT ( text));
	}
#elif defined HAVE_GTK20
		GtkTextBuffer *buffer;
		GtkTextIter start;
		GtkTextIter end;


	if ( text != NULL ) {
		buffer = gtk_text_view_get_buffer ( GTK_TEXT_VIEW ( text));
		gtk_text_buffer_get_start_iter ( buffer, &start);
		gtk_text_buffer_get_end_iter ( buffer, &end);
		gtk_text_buffer_delete ( buffer, &start, &end);
	}
#endif

	return;
}


/* Insert text in a GtkTextArea */
void gtk_text_area_insert ( GtkTextArea *text, const gchar *words) {
	gchar *text_utf8 = NULL;
#if defined HAVE_GTK12


	if ( text != NULL ) {
		g_strdup_to_gtk_text ( words, text_utf8);
		gtk_text_insert ( GTK_TEXT ( text), NULL, NULL, NULL, text_utf8, -1);
	}
#elif defined HAVE_GTK20
	GtkTextBuffer *buffer;
	GtkTextIter end;


	if ( text != NULL ) {
		g_strdup_to_gtk_text ( words, text_utf8);
		buffer = gtk_text_view_get_buffer ( GTK_TEXT_VIEW ( text));
		gtk_text_buffer_get_end_iter ( buffer, &end);
		gtk_text_buffer_insert ( buffer, &end, text_utf8, -1);
	}
#endif

	return;
}


/* Get text in a GtkTextArea */
gchar * gtk_text_area_get_text ( GtkTextArea *text) {
	gchar *words = NULL, *text_utf8 = NULL;
#if defined HAVE_GTK12


	if ( text != NULL ) {
		text_utf8 = gtk_editable_get_chars ( GTK_EDITABLE ( text), 0, -1);
	}
#elif defined HAVE_GTK20
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;


	if ( text != NULL ) {
		buffer = gtk_text_view_get_buffer ( GTK_TEXT_VIEW ( text));
		gtk_text_buffer_get_start_iter ( buffer, &start);
		gtk_text_buffer_get_end_iter ( buffer, &end);
		text_utf8 = gtk_text_buffer_get_text ( buffer, &start, &end, TRUE);
	}
#endif

	/* words must be free later with g_free() */
	g_strdup_from_gtk_text ( text_utf8, words);

	if ( text_utf8 != NULL ) {
		g_free ( text_utf8);
	}

	return words;
}
