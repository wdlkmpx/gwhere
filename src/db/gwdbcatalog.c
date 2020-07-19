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


#include <string.h> /* strcmp */
#include "gwsupport.h"
#include "gwdbcatalog.h"


typedef struct gw_db_catalog_s {
	gchar* name;
	gchar* short_db_name;
	gchar* db_name;
	gchar* version;
	gchar* program_builder;
	gchar* description;
	gboolean is_modified;
	gulong size;
}_GWDBCatalog;


GWDBCatalog * gw_db_catalog_new ( void) {
	GWDBCatalog *catalog = NULL;


	if ( (catalog = (GWDBCatalog*)g_malloc0 ( sizeof ( GWDBCatalog))) != NULL ) {
		catalog->name = NULL;
		catalog->short_db_name = NULL;
		catalog->db_name = NULL;
		catalog->version = NULL;
		catalog->program_builder = NULL;
		catalog->description = NULL;
		catalog->is_modified = FALSE;
		catalog->size = 0;
	}

	return catalog;
}


gint gw_db_catalog_set_name ( GWDBCatalog *catalog, gchar *name) {
	if ( catalog != NULL ) {
		if ( catalog->name != NULL ) {
			g_free ( catalog->name);
		}

		catalog->name = name;

		return 0;
	}

	return -1;
}


gint gw_db_catalog_set_short_db_name ( GWDBCatalog *catalog, gchar *short_db_name) {
	if ( catalog != NULL ) {
		if ( catalog->short_db_name != NULL ) {
			g_free ( catalog->short_db_name);
		}

		catalog->short_db_name = short_db_name;

		return 0;
	}

	return -1;
}


gint gw_db_catalog_set_db_name ( GWDBCatalog *catalog, gchar *db_name) {
	if ( catalog != NULL ) {
		if ( catalog->db_name != NULL ) {
			g_free ( catalog->db_name);
		}

		catalog->db_name = db_name;

		return 0;
	}

	return -1;
}


gint gw_db_catalog_set_version ( GWDBCatalog *catalog, gchar *version) {
	if ( catalog != NULL ) {
		if ( catalog->version != NULL ) {
			g_free ( catalog->version);
		}

		catalog->version = version;

		return 0;
	}

	return -1;
}


gint gw_db_catalog_set_program_builder ( GWDBCatalog *catalog, gchar *program_builder) {
	if ( catalog != NULL ) {
		if ( catalog->program_builder != NULL ) {
			g_free ( catalog->program_builder);
		}

		catalog->program_builder = program_builder;

		return 0;
	}

	return -1;
}


gint gw_db_catalog_set_description ( GWDBCatalog *catalog, gchar *description) {
	if ( catalog != NULL ) {
		if ( catalog->description != NULL ) {
			g_free ( catalog->description);
		}

		catalog->description = description;

		return 0;
	}

	return -1;
}


gint gw_db_catalog_set_size ( GWDBCatalog *catalog, gulong size) {
	if ( catalog != NULL ) {
		catalog->size = size;

		return 0;
	}

	return -1;
}


gint gw_db_catalog_set_ismodified ( GWDBCatalog *catalog, gboolean modified) {
	if ( catalog != NULL ) {
		catalog->is_modified = modified;

		return 0;
	}

	return -1;
}


gchar * gw_db_catalog_get_name ( GWDBCatalog *catalog) {
	if ( catalog != NULL ) {
		return catalog->name;
	}

	return NULL;
}


gchar * gw_db_catalog_get_short_db_name ( GWDBCatalog *catalog) {
	if ( catalog != NULL ) {
		return catalog->short_db_name;
	}

	return NULL;
}


gchar * gw_db_catalog_get_db_name ( GWDBCatalog *catalog) {
	if ( catalog != NULL ) {
		return catalog->db_name;
	}

	return NULL;
}


gchar * gw_db_catalog_get_version ( GWDBCatalog *catalog) {
	if ( catalog != NULL ) {
		return catalog->version;
	}

	return NULL;
}


gchar * gw_db_catalog_get_program_builder ( GWDBCatalog *catalog) {
	if ( catalog != NULL ) {
		return catalog->program_builder;
	}

	return NULL;
}


gchar * gw_db_catalog_get_description ( GWDBCatalog *catalog) {
	if ( catalog != NULL ) {
		return catalog->description;
	}

	return NULL;
}


gulong gw_db_catalog_get_size ( GWDBCatalog *catalog) {
	if ( catalog != NULL ) {
		return catalog->size;
	}

	return 0;
}


gboolean gw_db_catalog_is_modified ( GWDBCatalog *catalog) {
	if ( catalog != NULL ) {
		return catalog->is_modified;
	}

	/* If catalog doesn't exist, it may not be modified. */
	return FALSE;
}


GWDBCatalog * gw_db_catalog_dup ( GWDBCatalog *catalog, GWDBCatalog **dup) {
	GWDBCatalog *dup_catalog = NULL;


	if ( catalog != NULL ) {
		dup_catalog = *dup;
		if ( dup_catalog == NULL ) {
			/* Don't check if gw_db_catalog_new return NULL because all following functions check it too. */
			(*dup) = dup_catalog = gw_db_catalog_new ( );
		}

		if ( gw_db_catalog_get_name ( catalog) != NULL ) {
			gw_db_catalog_set_name ( dup_catalog, g_strdup ( gw_db_catalog_get_name ( catalog)));
		} else {
			gw_db_catalog_set_name ( dup_catalog, NULL);
		}
		if ( gw_db_catalog_get_short_db_name ( catalog) != NULL ) {
			gw_db_catalog_set_short_db_name ( dup_catalog, g_strdup ( gw_db_catalog_get_short_db_name ( catalog)));
		} else {
			gw_db_catalog_set_short_db_name ( dup_catalog, NULL);
		}
		if ( gw_db_catalog_get_db_name ( catalog) != NULL ) {
			gw_db_catalog_set_db_name ( dup_catalog, g_strdup ( gw_db_catalog_get_db_name ( catalog)));
		} else {
			gw_db_catalog_set_db_name ( dup_catalog, NULL);
		}
		if ( gw_db_catalog_get_version ( catalog) != NULL ) {
			gw_db_catalog_set_version ( dup_catalog, g_strdup ( gw_db_catalog_get_version ( catalog)));
		} else {
			gw_db_catalog_set_version ( dup_catalog, NULL);
		}
		if ( gw_db_catalog_get_program_builder ( catalog) != NULL ) {
			gw_db_catalog_set_program_builder ( dup_catalog, g_strdup ( gw_db_catalog_get_program_builder ( catalog)));
		} else {
			gw_db_catalog_set_program_builder ( dup_catalog, NULL);
		}
		if ( gw_db_catalog_get_description ( catalog) != NULL ) {
			gw_db_catalog_set_description ( dup_catalog, g_strdup ( gw_db_catalog_get_description ( catalog)));
		} else {
			gw_db_catalog_set_description ( dup_catalog, NULL);
		}
		gw_db_catalog_set_size ( dup_catalog, gw_db_catalog_get_size ( catalog));
		gw_db_catalog_set_ismodified ( dup_catalog, gw_db_catalog_is_modified ( catalog));
	}

	return dup_catalog;
}


gint gw_db_catalog_free ( GWDBCatalog *catalog) {
	if ( catalog != NULL ) {
		gw_db_catalog_set_name ( catalog, NULL);
		gw_db_catalog_set_short_db_name ( catalog, NULL);
		gw_db_catalog_set_db_name ( catalog, NULL);
		gw_db_catalog_set_version ( catalog, NULL);
		gw_db_catalog_set_program_builder ( catalog, NULL);
		gw_db_catalog_set_description ( catalog, NULL);

		g_free ( catalog);

		return 0;
	}

	return -1;
}


gboolean gw_db_catalog_equals ( GWDBCatalog *catalog, GWDBCatalog *to) {
	gboolean equals = FALSE;


	if ( catalog != NULL && to != NULL) {
		if ( str_equals ( gw_db_catalog_get_name ( catalog), gw_db_catalog_get_name ( to))
			&& str_equals ( gw_db_catalog_get_short_db_name ( catalog), gw_db_catalog_get_short_db_name ( to))
			&& str_equals ( gw_db_catalog_get_db_name ( catalog), gw_db_catalog_get_db_name ( to))
			&& str_equals ( gw_db_catalog_get_version ( catalog), gw_db_catalog_get_version ( to))
			&& str_equals ( gw_db_catalog_get_program_builder ( catalog), gw_db_catalog_get_program_builder ( to))
			&& str_equals ( gw_db_catalog_get_description ( catalog), gw_db_catalog_get_description ( to))
			&& gw_db_catalog_is_modified ( catalog) == gw_db_catalog_is_modified ( to)
			&& gw_db_catalog_get_size ( catalog) == gw_db_catalog_get_size ( to) ) {
			equals = TRUE;
		}
	}

	return equals;
}
