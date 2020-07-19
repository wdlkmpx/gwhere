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
#include "gwdbcategory.h"


typedef struct gw_db_category_s {
	gpointer ref;				/* plugin internal reference						*/
	gint index;				/* TODO should it be replaced by ref??				*/
	gchar *name;				/* Category's name									*/
	gchar *description;			/* Category's description							*/
	gulong nb_disks;			/* Number of disks which are in this category		*/
	gulong nb_files;			/* Number of files which are in this category		*/
}_GWDBCategory;


GWDBCategory * gw_db_category_new ( void) {
	GWDBCategory *category = NULL;


	if ( (category = (GWDBCategory*)g_malloc0 ( sizeof ( GWDBCategory))) != NULL ) {
		category->ref = NULL;
		category->name = NULL;
		category->description = NULL;
		category->nb_disks = 0;
		category->nb_files = 0;
	}

	return category;
}


gint gw_db_category_set_ref ( GWDBCategory *category, gpointer ref) {
	if ( category != NULL ) {
		category->ref = ref;

		return 0;
	}

	return -1;
}


gint gw_db_category_set_index ( GWDBCategory *category, gint index) {
	if ( category != NULL ) {
		category->index = index;

		return 0;
	}

	return -1;
}


gint gw_db_category_set_name ( GWDBCategory *category, gchar *name) {
	if ( category != NULL ) {
		if ( category->name != NULL ) {
			g_free ( category->name);
		}

		category->name = name;

		return 0;
	}

	return -1;
}


gint gw_db_category_set_description ( GWDBCategory *category, gchar *description) {
	if ( category != NULL ) {
		if ( category->name != NULL ) {
			g_free ( category->description);
		}

		category->description = description;

		return 0;
	}

	return -1;
}


gint gw_db_category_set_nb_disks ( GWDBCategory *category, gulong nb) {
	if ( category != NULL )	{
		category->nb_disks = nb;

		return 0;
	}

	return -1;
}


gint gw_db_category_set_nb_files ( GWDBCategory *category, gulong nb) {
	if ( category != NULL )	{
		category->nb_files = nb;

		return 0;
	}

	return -1;
}


gpointer gw_db_category_get_ref ( GWDBCategory *category) {
	if ( category != NULL ) {
		return category->ref;
	}

	return NULL;
}


gint gw_db_category_get_index ( GWDBCategory *category) {
	if ( category != NULL ) {
		return category->index;
	}

	return -1;
}


gchar * gw_db_category_get_name ( GWDBCategory *category) {
	if ( category != NULL ) {
		return category->name;
	}

	return NULL;
}


gchar * gw_db_category_get_description ( GWDBCategory *category) {
	if ( category != NULL ) {
		return category->description;
	}

	return NULL;
}


gulong gw_db_category_get_nb_disks ( GWDBCategory *category) {
	if ( category != NULL ) {
		return category->nb_disks;
	}

	return 0;
}


gulong gw_db_category_get_nb_files ( GWDBCategory *category) {
	if ( category != NULL ) {
		return category->nb_files;
	}

	return 0;
}


gulong gw_db_category_add_disk ( GWDBCategory *category) {
	if ( category != NULL ) {
		category->nb_disks++;

		return category->nb_disks;
	}

	return 0;
}


gulong gw_db_category_add_file ( GWDBCategory *category) {
	if ( category != NULL ) {
		category->nb_files++;

		return category->nb_files;
	}

	return 0;
}


gulong gw_db_category_remove_disk ( GWDBCategory *category) {
	if ( category != NULL ) {
		if ( category->nb_disks > 0 ) {
			category->nb_disks--;
		}

		return category->nb_disks;
	}

	return 0;
}


gulong gw_db_category_remove_file ( GWDBCategory *category) {
	if ( category != NULL ) {
		if ( category->nb_files > 0 ) {
			category->nb_files--;
		}

		return category->nb_files;
	}

	return 0;
}


gboolean gw_db_category_can_removed ( GWDBCategory *category) {
	if ( category != NULL ) {
		if ( (gw_db_category_get_nb_disks ( category) == 0) && (gw_db_category_get_nb_files ( category) == 0) ) {
			return TRUE;
		}
	}

	return FALSE;
}


GWDBCategory * gw_db_category_dup ( GWDBCategory *category, GWDBCategory **dup) {
	GWDBCategory *dup_category = NULL;


	if ( category != NULL ) {
		dup_category = *dup;
		if ( dup_category == NULL ) {
			/* Don't check if gw_db_category_new return NULL because all following functions check it too. */
			(*dup) = dup_category = gw_db_category_new ( );
		}

		gw_db_category_set_ref ( dup_category, gw_db_category_get_ref ( category));
		gw_db_category_set_index ( dup_category, gw_db_category_get_index ( category));
		if ( gw_db_category_get_name ( category) != NULL ) {
			gw_db_category_set_name ( dup_category, g_strdup ( gw_db_category_get_name ( category)));
		} else {
			gw_db_category_set_name ( dup_category, NULL);
		}
		if ( gw_db_category_get_description ( category) != NULL ) {
			gw_db_category_set_description ( dup_category, g_strdup ( gw_db_category_get_description ( category)));
		} else {
			gw_db_category_set_description ( dup_category, NULL);
		}
		gw_db_category_set_nb_disks ( dup_category, gw_db_category_get_nb_disks ( category));
		gw_db_category_set_nb_files ( dup_category, gw_db_category_get_nb_files ( category));
	}

	return dup_category;
}


gint gw_db_category_free ( GWDBCategory *category) {
	if ( category != NULL )	{
		gw_db_category_set_name ( category, NULL);
		gw_db_category_set_description ( category, NULL);

		g_free ( category);

		return 0;
	}

	return -1;
}


gboolean gw_db_category_equals ( GWDBCategory *category, GWDBCategory *to) {
	gboolean equals = FALSE;


	if ( category != NULL && to != NULL) {
		if ( gw_db_category_get_ref ( category) == gw_db_category_get_ref ( to)
			&& gw_db_category_get_index ( category) == gw_db_category_get_index ( to)
			&& str_equals ( gw_db_category_get_name ( category), gw_db_category_get_name ( to))
			&& str_equals ( gw_db_category_get_description ( category), gw_db_category_get_description ( to))
			&& gw_db_category_get_nb_disks ( category) == gw_db_category_get_nb_disks ( to)
			&& gw_db_category_get_nb_files ( category) == gw_db_category_get_nb_files ( to) ) {
			equals = TRUE;
		}
	}

	return equals;
}
