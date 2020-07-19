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
 * @header		gwdbcontext.h
 * 				GWhere<br />
 * 				Copyright (C) 2000  Sébastien LECACHEUR<br /><br />
 * 				This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br /><br />
 * 				This component was developed for the GWhere project.<br />
 * 				It's an object for context database...
 * @abstract	This is the context database structure.
 * @author		Sébastien LECACHEUR <zero@gwhere.org>
 * @version		1.0 2004/06/07
 * @see			gwpluginsmanageryy.h
 * @see			gwsupport.h
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK+ Web Site <http://www.gtk.org>
 * @ref			gwdbcontext.c
 * @author		Author <zero@gwhere.org>
 */


#ifndef GW_DATABASE_CONTEXT_H
#define GW_DATADASE_CONTEXT_H


typedef struct gw_db_context_s GWDBContext;

GWDBContext * gw_db_context_new ( void);
gint gw_db_context_set_plugin ( GWDBContext *context, gpointer plugin);
gint gw_db_context_set_data ( GWDBContext *context, gpointer data);
gpointer gw_db_context_get_plugin ( GWDBContext *context);
gpointer gw_db_context_get_data ( GWDBContext *context);
gint gw_db_context_free ( GWDBContext *context);


#endif
