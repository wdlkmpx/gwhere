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
 * @header		gwdbdistype.h
 * 				GWhere<br />
 * 				Copyright (C) 2000  Sébastien LECACHEUR<br /><br />
 * 				This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br /><br />
 * 				This component was developed for the GWhere project.<br />
 * 				It's an object for disk representation. His structure gets many informations as name, capacity, size, label,...<br /><br />
 * @abstract	This is the disk data structure.
 * @author		Sébastien LECACHEUR <zero@gwhere.org>
 * @version		1.0 2004/06/07
 * @see			gtk/gtk.h
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK+ Web Site <http://www.gtk.org>
 * @author		Author <zero@gwhere.org>
 */


#ifndef GW_DATA_DB_DISK_TYPE_H
#define GW_DATA_DB_DISK_TYPE_H


typedef enum {NONE = 0, CDROM = 1, FLOPPY = 2, HD = 3, ZIP_DRIVE = 4, TAPE_DRIVE = 5, AUDIOCD = 6, NETWORK_DRIVE = 7, JAZ_DRIVE = 8} GWDBDiskType;


#endif
