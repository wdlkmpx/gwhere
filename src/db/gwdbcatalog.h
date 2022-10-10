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
 * @header		gwdbcatalog.h
 * 				GWhere<br />
 * 				Copyright (C) 2000  Sébastien LECACHEUR<br /><br />
 * 				This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br /><br />
 * 				This component was developed for the GWhere project.<br />
 * 				It's an object for catalog database...
 * @abstract	This is the catalog database structure.
 * @author		Sébastien LECACHEUR <zero@gwhere.org>
 * @version		1.0 2004/06/07
 * @see			gwdbcategory.h
 * @see			gwsupport.h
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK+ Web Site <http://www.gtk.org>
 * @ref			gwdbcatalog.c
 * @author		Author <zero@gwhere.org>
 */


#ifndef GW_DATA_DB_CATALOG_H
#define GW_DATA_DB_CATALOG_H


typedef struct gw_db_catalog_s GWDBCatalog;


GWDBCatalog * gw_db_catalog_new ( void);
gint gw_db_catalog_set_name ( GWDBCatalog *catalog, gchar *name);
gint gw_db_catalog_set_short_db_name ( GWDBCatalog *catalog, gchar *db_name);
gint gw_db_catalog_set_db_name ( GWDBCatalog *catalog, gchar *db_name);
gint gw_db_catalog_set_version ( GWDBCatalog *catalog, gchar *version);
gint gw_db_catalog_set_program_builder ( GWDBCatalog *catalog, gchar *program_builder);
gint gw_db_catalog_set_description ( GWDBCatalog *catalog, gchar *_description);
gint gw_db_catalog_set_size ( GWDBCatalog *catalog, gulong size);
gint gw_db_catalog_set_ismodified ( GWDBCatalog *catalog, gboolean modified);
gchar * gw_db_catalog_get_name ( GWDBCatalog *catalog);
gchar * gw_db_catalog_get_db_name ( GWDBCatalog *catalog);
gchar * gw_db_catalog_get_short_db_name ( GWDBCatalog *catalog);
gchar * gw_db_catalog_get_version ( GWDBCatalog *catalog);
gchar * gw_db_catalog_get_program_builder ( GWDBCatalog *catalog);
gchar * gw_db_catalog_get_description ( GWDBCatalog *catalog);
gulong gw_db_catalog_get_size ( GWDBCatalog *catalog);
gboolean gw_db_catalog_is_modified ( GWDBCatalog *catalog);
GWDBCatalog * gw_db_catalog_dup ( GWDBCatalog *catalog, GWDBCatalog **dup);
gint gw_db_catalog_free ( GWDBCatalog *catalog);
gboolean gw_db_catalog_equals ( GWDBCatalog *catalog, GWDBCatalog *to);


#endif
