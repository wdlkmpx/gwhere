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

#include "gwicons.h"

#include "catalog.xpm"
#include "cdrom.xpm"
#include "file.xpm"
#include "floppy.xpm"
#include "folder.xpm"
#include "hard_disk.xpm"
#include "locked_folder.xpm"
#include "open_folder.xpm"
#include "parent_folder.xpm"
#include "zip_disk.xpm"


gint icons_load_catalog ( GtkWindow *w)
{
	GdkColor transparent = { 0 };


	if ( w != NULL )
	{
		PixCDRomDisk = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskCDRomDisk, &transparent, cdrom_disk_xpm);
		PixFloppyDisk = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskFloppyDisk, &transparent, floppy_disk_xpm);
		PixHardDriveDisk = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskHardDriveDisk, &transparent, harddrive_disk_xpm);
		PixZipDisk = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskZipDisk, &transparent, zip_disk_xpm);
		PixFolder = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskFolder, &transparent, folder_xpm);
		PixParentFolder = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskParentFolder, &transparent, parent_folder_xpm);
		PixLockedFolder = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskLockedFolder, &transparent, locked_folder_xpm);
		PixOpenFolder = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskOpenFolder, &transparent, open_folder_xpm);
		PixFile = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskFile, &transparent, file_xpm);
		PixCatalog = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskCatalog, &transparent, catalog_xpm);

		return 0;
	}

	return -1;
}
