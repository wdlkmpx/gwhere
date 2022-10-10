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
 * @header		gwdbdisk.h
 * 				GWhere<br />
 * 				Copyright (C) 2000  Sébastien LECACHEUR<br /><br />
 * 				This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br /><br />
 * 				This component was developed for the GWhere project.<br />
 * 				It's an object for disk representation. His structure gets many informations as name, capacity, size, label,...<br /><br />
 * @abstract	This is the disk data structure.
 * @author		Sébastien LECACHEUR <zero@gwhere.org>
 * @version		1.0 2004/06/07
 * @see			gtk/gtk.h
 * @see			gwsupport.h
 * @see			gwdbcategory.h
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK+ Web Site <http://www.gtk.org>
 * @ref			gwdbdisk.c
 * @author		Author <zero@gwhere.org>
 */


#ifndef GW_DATA_DB_DISK_H
#define GW_DATA_DB_DISK_H


#include "gwdbcategory.h"
#include "gwdbdisktype.h"


typedef gpointer GWDBDiskPK;


typedef struct gw_db_disk_s GWDBDisk;


GWDBDisk* gw_db_disk_new ( void);
gint gw_db_disk_set_ref ( GWDBDisk *disk, GWDBDiskPK ref);
gint gw_db_disk_set_name ( GWDBDisk *disk, gchar *name);
gint gw_db_disk_set_fsname ( GWDBDisk *disk, gchar *fsname);
gint gw_db_disk_set_fstype ( GWDBDisk *disk, gchar *fstype);
gint gw_db_disk_set_path ( GWDBDisk *disk, gchar *path);
gint gw_db_disk_set_num ( GWDBDisk *disk, gint num);
gint gw_db_disk_set_type ( GWDBDisk *disk, GWDBDiskType type);
gint gw_db_disk_set_volume ( GWDBDisk *disk, gchar *volume);
gint gw_db_disk_set_full ( GWDBDisk *disk, guint64 full);
gint gw_db_disk_set_free ( GWDBDisk *disk, guint64 free);
gint gw_db_disk_set_date ( GWDBDisk *disk, gulong date);
gint gw_db_disk_set_serial ( GWDBDisk *disk, gchar *serial);
gint gw_db_disk_set_category ( GWDBDisk *disk, GWDBCategoryPK category);
gint gw_db_disk_set_description ( GWDBDisk *disk, gchar *description);
GWDBDiskPK gw_db_disk_get_ref ( GWDBDisk *disk);
gchar * gw_db_disk_get_name ( GWDBDisk *disk);
gchar * gw_db_disk_get_fsname ( GWDBDisk *disk);
gchar * gw_db_disk_get_fstype ( GWDBDisk *disk);
gchar * gw_db_disk_get_path ( GWDBDisk *disk);
gint gw_db_disk_get_num ( GWDBDisk *disk);
GWDBDiskType gw_db_disk_get_type ( GWDBDisk *disk);
gchar * gw_db_disk_get_volume ( GWDBDisk *disk);
guint64 gw_db_disk_get_full ( GWDBDisk *disk);
guint64 gw_db_disk_get_free ( GWDBDisk *disk);
guint64 gw_db_disk_get_capacity ( GWDBDisk *disk);
gulong gw_db_disk_get_date ( GWDBDisk *disk);
gchar * gw_db_disk_get_serial ( GWDBDisk *disk);
GWDBCategoryPK gw_db_disk_get_category ( GWDBDisk *disk);
gchar * gw_db_disk_get_description ( GWDBDisk *disk);
GWDBDisk * gw_db_disk_dup ( GWDBDisk *disk, GWDBDisk **dup);
gint gw_db_disk_free ( GWDBDisk *disk);
gboolean gw_db_disk_equals ( GWDBDisk *disk, GWDBDisk *to);


#endif
