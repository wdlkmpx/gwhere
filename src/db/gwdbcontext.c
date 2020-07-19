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


#include "gwsupport.h"
#include "gwdbcontext.h"


typedef struct gw_db_context_s {
	gpointer plugin;
	gpointer data;
}_GWDBContext;


GWDBContext * gw_db_context_new ( void) {
	GWDBContext *context = NULL;


	if ( (context = (GWDBContext*)g_malloc0 ( sizeof ( GWDBContext))) != NULL ) {
		context->plugin = NULL;
		context->data = NULL;
	}

	return context;
}


gint gw_db_context_set_plugin ( GWDBContext *context, gpointer plugin) {
	if ( context != NULL ) {
		context->plugin = plugin;

		return 0;
	}

	return -1;
}


gint gw_db_context_set_data ( GWDBContext *context, gpointer data) {
	if ( context != NULL ) {
		context->data = data;

		return 0;
	}

	return -1;
}


gpointer gw_db_context_get_plugin ( GWDBContext *context) {
	if ( context != NULL ) {
		return context->plugin;
	}

	return NULL;
}


gpointer gw_db_context_get_data ( GWDBContext *context) {
	if ( context != NULL ) {
		return context->data;
	}

	return NULL;
}


gint gw_db_context_free ( GWDBContext *context) {
	if ( context != NULL ) {
		gw_db_context_set_plugin ( context, NULL);
		gw_db_context_set_data ( context, NULL);

		g_free ( context);

		return 0;
	}

	return -1;
}
