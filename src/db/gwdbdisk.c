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


#include <string.h> /* strcmp */
#include "gwsupport.h" /* str_equals */
#include "gwdbdisk.h"


typedef struct gw_db_disk_s {
	gpointer ref;			/* Disk reference				*/
	gchar *name;			/* Disk name					*/
	gchar *fsname;			/* Device file system name			*/
	gchar *fstype;			/* Device file system type			*/
	gchar *path;			/* Disk access path				*/
	gint num;			/* Number archive in catalog			*/
	GWDBDiskType type;		/* Device type					*/
	gchar *volume;			/* Disk label					*/
	guint64 full;			/* Disk full capacity				*/
	guint64 free;			/* Disk free space				*/
	gulong date;			/* Disk adding date				*/
	gchar *serial;			/* Disk serial number				*/
	GWDBCategoryPK category;	/* Disk category pk				*/
	gchar *description;		/* Disk description				*/
}_GWDBDisk;


GWDBDisk * gw_db_disk_new ( void) {
	GWDBDisk *disk = NULL;


	if ( (disk = (GWDBDisk*)g_malloc0 ( sizeof ( GWDBDisk))) != NULL) {
		disk->ref = NULL;
		disk->name = NULL;
		disk->fsname = NULL;
		disk->fstype = NULL;
		disk->path = NULL;
		disk->num = 0;
		disk->type = NONE;
		disk->volume = NULL;
		disk->full = 0;
		disk->free = 0;
		disk->date = 0;
		disk->serial = NULL;
		disk->category = NULL;
		disk->description = NULL;
	}

	return disk;
}


gint gw_db_disk_set_ref ( GWDBDisk *disk, gpointer ref) {
	if ( disk != NULL ) {
		disk->ref = ref;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_name ( GWDBDisk *disk, gchar *name) {
	if ( disk != NULL ) {
		if ( disk->name != NULL ) {
			g_free ( disk->name);
		}

		disk->name = name;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_fsname ( GWDBDisk *disk, gchar *fsname) {
	if ( disk != NULL ) {
		if ( disk->fsname != NULL ) {
			g_free ( disk->fsname);
		}

		disk->fsname = fsname;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_fstype ( GWDBDisk *disk, gchar *fstype) {
	if ( disk != NULL ) {
		if ( disk->fstype != NULL ) {
			g_free ( disk->fstype);
		}

		disk->fstype = fstype;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_path ( GWDBDisk *disk, gchar *path) {
	if ( disk != NULL ) {
		if ( disk->path != NULL ) {
			g_free ( disk->path);
		}

		disk->path = path;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_num ( GWDBDisk *disk, gint num) {
	if ( disk != NULL ) {
		disk->num = num;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_type ( GWDBDisk *disk, GWDBDiskType type) {
	if ( disk != NULL ) {
		disk->type = type;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_volume ( GWDBDisk *disk, gchar *volume) {
	if ( disk != NULL ) {
		if ( disk->volume != NULL ) {
			g_free ( disk->volume);
		}

		disk->volume = volume;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_full ( GWDBDisk *disk, guint64 full) {
	if ( disk != NULL ) {
		disk->full = full;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_free ( GWDBDisk *disk, guint64 free) {
	if ( disk != NULL ) {
		disk->free = free;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_date ( GWDBDisk *disk, gulong date) {
	if ( disk != NULL ) {
		disk->date = date;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_serial ( GWDBDisk *disk, gchar *serial) {
	if ( disk != NULL ) {
		if ( disk->serial != NULL ) {
			g_free ( disk->serial);
		}

		disk->serial = serial;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_category ( GWDBDisk *disk, GWDBCategoryPK category) {
	if ( disk != NULL ) {
		disk->category = category;

		return 0;
	}

	return -1;
}


gint gw_db_disk_set_description ( GWDBDisk *disk, gchar *description) {
	if ( disk != NULL ) {
		if ( disk->description != NULL ) {
			g_free ( disk->description);
		}

		disk->description = description;

		return 0;
	}

	return -1;
}


gpointer gw_db_disk_get_ref ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->ref;
	}

	return NULL;
}


gchar * gw_db_disk_get_name ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->name;
	}

	return NULL;
}


gchar * gw_db_disk_get_fsname ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->fsname;
	}

	return NULL;
}


gchar * gw_db_disk_get_fstype ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->fstype;
	}

	return NULL;
}


gchar * gw_db_disk_get_path ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->path;
	}

	return NULL;
}


gint gw_db_disk_get_num ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->num;
	}

	return -1;
}


GWDBDiskType gw_db_disk_get_type ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->type;
	}

	return NONE;
}


gchar * gw_db_disk_get_volume ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->volume;
	}

	return NULL;
}


guint64 gw_db_disk_get_full ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->full;
	}

	return 0;
}


guint64 gw_db_disk_get_free ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->free;
	}

	return 0;
}


guint64 gw_db_disk_get_capacity ( GWDBDisk *disk) {
	guint64 size = G_GINT64_CONSTANT ( 0);


	if ( disk != NULL ) {
		size = gw_db_disk_get_full ( disk) + gw_db_disk_get_free ( disk);
	}

	return size;
}


gulong gw_db_disk_get_date ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->date;
	}

	return 0;
}


gchar * gw_db_disk_get_serial ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->serial;
	}

	return NULL;
}


GWDBCategoryPK gw_db_disk_get_category ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->category;
	}

	return NULL;
}


gchar * gw_db_disk_get_description ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		return disk->description;
	}

	return NULL;
}


GWDBDisk * gw_db_disk_dup ( GWDBDisk *disk, GWDBDisk **dup) {
	GWDBDisk *dup_disk = NULL;


	if ( disk != NULL ) {
		dup_disk = *dup;
		if ( dup_disk == NULL ) {
			/* Don't check if gw_db_disk_new return NULL because all following functions check it too. */
			(*dup) = dup_disk = gw_db_disk_new ( );
		}

		gw_db_disk_set_ref ( dup_disk, gw_db_disk_get_ref ( disk));
		if ( gw_db_disk_get_name ( disk) != NULL ) {
			gw_db_disk_set_name ( dup_disk, g_strdup ( gw_db_disk_get_name ( disk)));
		} else {
			gw_db_disk_set_name ( dup_disk, NULL);
		}
		if ( gw_db_disk_get_fsname ( disk) != NULL ) {
			gw_db_disk_set_fsname ( dup_disk, g_strdup ( gw_db_disk_get_fsname ( disk)));
		} else {
			gw_db_disk_set_fsname ( dup_disk, NULL);
		}
		if ( gw_db_disk_get_fstype ( disk) != NULL ) {
			gw_db_disk_set_fstype ( dup_disk, g_strdup ( gw_db_disk_get_fstype ( disk)));
		} else {
			gw_db_disk_set_fstype ( dup_disk, NULL);
		}
		if ( gw_db_disk_get_path ( disk) != NULL ) {
			gw_db_disk_set_path ( dup_disk, g_strdup ( gw_db_disk_get_path ( disk)));
		} else {
			gw_db_disk_set_path ( dup_disk, NULL);
		}
		gw_db_disk_set_num ( dup_disk, gw_db_disk_get_num ( disk));
		gw_db_disk_set_type ( dup_disk, gw_db_disk_get_type ( disk));
		if ( gw_db_disk_get_volume ( disk) != NULL ) {
			gw_db_disk_set_volume ( dup_disk, g_strdup ( gw_db_disk_get_volume ( disk)));
		} else {
			gw_db_disk_set_volume ( dup_disk, NULL);
		}
		gw_db_disk_set_full ( dup_disk, gw_db_disk_get_full ( disk));
		gw_db_disk_set_free ( dup_disk, gw_db_disk_get_free ( disk));
		gw_db_disk_set_date ( dup_disk, gw_db_disk_get_date ( disk));
		if ( gw_db_disk_get_serial ( disk) != NULL ) {
			gw_db_disk_set_serial ( dup_disk, g_strdup ( gw_db_disk_get_serial ( disk)));
		} else {
			gw_db_disk_set_serial ( dup_disk, NULL);
		}
		gw_db_disk_set_category ( dup_disk, gw_db_disk_get_category ( disk));
		if ( gw_db_disk_get_description ( disk) != NULL ) {
			gw_db_disk_set_description ( dup_disk, g_strdup ( gw_db_disk_get_description ( disk)));
		} else {
			gw_db_disk_set_description ( dup_disk, NULL);
		}
	}

	return dup_disk;
}


gint gw_db_disk_free ( GWDBDisk *disk) {
	if ( disk != NULL ) {
		gw_db_disk_set_name ( disk, NULL);
		gw_db_disk_set_fsname ( disk, NULL);
		gw_db_disk_set_fstype ( disk, NULL);
		gw_db_disk_set_path ( disk, NULL);
		gw_db_disk_set_volume ( disk, NULL);
		gw_db_disk_set_serial ( disk, NULL);
		gw_db_disk_set_description ( disk, NULL);

		g_free ( disk);

		return 0;
	}

	return -1;
}


gboolean gw_db_disk_equals ( GWDBDisk *disk, GWDBDisk *to) {
	gboolean equals = FALSE;


	if ( disk != NULL && to != NULL) {
		if ( gw_db_disk_get_ref ( disk) == gw_db_disk_get_ref ( to)
			&& str_equals ( gw_db_disk_get_name ( disk), gw_db_disk_get_name ( to))
			&& str_equals ( gw_db_disk_get_fsname ( disk), gw_db_disk_get_fsname ( to))
			&& str_equals ( gw_db_disk_get_fstype ( disk), gw_db_disk_get_fstype ( to))
			&& str_equals ( gw_db_disk_get_path ( disk), gw_db_disk_get_path ( to))
			&& gw_db_disk_get_num ( disk) == gw_db_disk_get_num ( to)
			&& gw_db_disk_get_type ( disk) == gw_db_disk_get_type ( to)
			&& str_equals ( gw_db_disk_get_volume ( disk), gw_db_disk_get_volume ( to))
			&& gw_db_disk_get_full ( disk) == gw_db_disk_get_full ( to)
			&& gw_db_disk_get_free ( disk) == gw_db_disk_get_free ( to)
			&& gw_db_disk_get_date ( disk) == gw_db_disk_get_date ( to)
			&& str_equals ( gw_db_disk_get_serial ( disk), gw_db_disk_get_serial ( to))
			&& gw_db_disk_get_category ( disk) == gw_db_disk_get_category ( to)
			&& str_equals ( gw_db_disk_get_description ( disk), gw_db_disk_get_description ( to))
			 ) {
			equals = TRUE;
		}
	}

	return equals;
}
