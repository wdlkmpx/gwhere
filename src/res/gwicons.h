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


/*!
 * @header	Icons.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 *		Contains all ressources icons and pictures. Can load theses image icons for the GUI.
 * @abstract	This is a ressource component.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gtk/gtk.h
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK+ Web Site <http://www.gtk.org>
 * @ref		Icons.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_RES_ICONS_H
#define GW_RES_ICONS_H


#include <gtk/gtk.h>

/*!
* @var         PixCatalog
* @abstract    Catalog icon.
* @discussion  The catalog icon pixmap for catalog representation.<br>
*/
extern GdkPixmap *PixCatalog;


/*!
* @var         MskCatalog
* @abstract    Catalog icon.
* @discussion  The catalog icon bitmap for catalog representation.<br>
*/
extern GdkBitmap *MskCatalog;


/*!
* @var         PixCDRomDisk
* @abstract    CD-Rom disk icon.
* @discussion  The CD-Rom disk icon pixmap for catalog representation.<br>
*/
extern GdkPixmap *PixCDRomDisk;


/*!
* @var         MskCDRomDisk
* @abstract    CD-Rom disk icon.
* @discussion  The CD-Rom disk icon bitmap for catalog representation.<br>
*/
extern GdkBitmap *MskCDRomDisk;


/*!
* @var         PixFloppyDisk
* @abstract    Floppy disk icon.
* @discussion  The floppy disk icon pixmap for catalog representation.<br>
*/
extern GdkPixmap *PixFloppyDisk;


/*!
* @var         MskFloppyDisk
* @abstract    Floppy disk icon.
* @discussion  The floppy disk icon bitmap for catalog representation.<br>
*/
extern GdkBitmap *MskFloppyDisk;


/*!
* @var         PixHardDriveDisk
* @abstract    Hard Drive disk icon.
* @discussion  The hard drive disk icon pixmap for catalog representation.<br>
*/
extern GdkPixmap *PixHardDriveDisk;


/*!
* @var         MskHardDriveDisk
* @abstract    Hard drive disk icon.
* @discussion  The hard drive disk icon bitmap for catalog representation.<br>
*/
extern GdkBitmap *MskHardDriveDisk;


/*!
* @var         PixZipDisk
* @abstract    Zip disk icon.
* @discussion  The zip disk icon pixmap for catalog representation.<br>
*/
extern GdkPixmap *PixZipDisk;


/*!
* @var         MskZipDisk
* @abstract    Zip drive disk icon.
* @discussion  The zip disk icon bitmap for catalog representation.<br>
*/
extern GdkBitmap *MskZipDisk;


/*!
* @var         PixFolder
* @abstract    Folder icon.
* @discussion  The folder icon pixmap for catalog representation.<br>
*/
extern GdkPixmap *PixFolder;


/*!
* @var         MskFolder
* @abstract    Folder icon.
* @discussion  The folder icon bitmap for catalog representation.<br>
*/
extern GdkBitmap *MskFolder;


/*!
* @var         PixOpenFolder
* @abstract    Open folder icon.
* @discussion  The open folder icon pixmap for catalog representation.<br>
*/
extern GdkPixmap *PixOpenFolder;


/*!
* @var         MskOpenFolder
* @abstract    Open folder icon.
* @discussion  The open folder icon bitmap for catalog representation.<br>
*/
extern GdkBitmap *MskOpenFolder;


/*!
* @var         PixParentFolder
* @abstract    Parent folder icon.
* @discussion  The parent folder icon pixmap for catalog representation.<br>
*/
extern GdkPixmap *PixParentFolder;


/*!
* @var         MskParentFolder
* @abstract    Parent folder icon.
* @discussion  The parent folder icon bitmap for catalog representation.<br>
*/
extern GdkBitmap *MskParentFolder;


/*!
* @var         PixLockedFolder
* @abstract    Locked folder icon.
* @discussion  The locked folder icon pixmap for catalog representation.<br>
*/
extern GdkPixmap *PixLockedFolder;


/*!
* @var         MskLockedFolder
* @abstract    Locked folder icon.
* @discussion  The locked folder icon bitmap for catalog representation.<br>
*/
extern GdkBitmap *MskLockedFolder;


/*!
* @var         PixFile
* @abstract    File icon.
* @discussion  The file icon pixmap for catalog representation.<br>
*/
extern GdkPixmap *PixFile;


/*!
* @var         MskFile
* @abstract    File icon.
* @discussion  The file icon bitmap for catalog representation.<br>
*/
extern GdkBitmap *MskFile;


/*!
 * @function	icons_load_catalog
 * @abstract	Loads icons for catalog.
 * @discussion	This function loads icons for catalog representation (catalog/disk/folder/file icons...).<br>
 * @param	w	the main application window to load icons
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint icons_load_catalog ( GtkWindow *w);

#endif
