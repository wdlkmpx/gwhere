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
 * @header	gwapplicationmanager.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a component to manage GWhere application.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @see		data/gwsettings.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwapplicationmanager.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_APPLICATION_MANAGER_H
#define GW_APPLICATION_MANAGER_H

#include "data/gwdata.h"
#include "gui/gwgui.h"
#include "gwpluginsmanager.h"


/*! @define	GWECATNOMODIFIED	An error code : catalog isn't modified */
#define GWECATNOMODIFIED 4000
/*! @define	GWECATNOFILENAME	An error code : there isn't file nale to save catalog */
#define GWECATNOFILENAME 4001
/*! @define	GWECATCANNOTSAVE	An error code : cannot save catalog */
#define GWECATCANNOTSAVE 4002


/*!
 * @typedef     GWApplicationSettings
 * @discussion	Common application variable
 * @field	user_name			name of the current user
 * @field	user_gwhere_home		path of the user gwhere home
 * @field	user_gwhere_settings_file	path of the user gwhere settings file
 * @field	settings			current settings
 */
typedef struct gw_application_settings {
	gchar *user_name;
	gchar *user_gwhere_home;
	gchar *user_gwhere_settings_file;
	GWSettings *settings;
} GWApplicationSettings;


typedef struct gw_mail_s
{
/*	gchar *server_name;
	int server_port;
	gchar *from;
*/	gchar *to;
	gchar *cc;
	gchar *bcc;
	gchar *subject;
	gchar *message;
	gchar *file_path;
}GWMail;


/*! @define	GW_VALUE_APP_CATALOG_LAST	The variable name for the last opened catalog */
#define GW_VALUE_APP_CATALOG_LAST "GWhere.application.catalog.last"
/*! @define	GW_VALUE_APP_RECENTS_FILES	The variable name for recents opened files */
#define GW_VALUE_APP_RECENTS_FILES "GWhere.application.recents.files"
/*! @define	GW_VALUE_APP_RECENT_SIZE	The variable name for the size of recents opened files list */
#define GW_VALUE_APP_RECENT_SIZE "GWhere.application.recents.size"
/*! @define	GW_VALUE_APP_RECENT_SIZE_DEFAULT	The default size of recents opened file list */
#define GW_VALUE_APP_RECENT_SIZE_DEFAULT 5
/*! @define	GW_VALUE_APP_RECENT_SIZE_MIN	The minimum size of recents opened file list */
#define GW_VALUE_APP_RECENT_SIZE_MIN 0
/*! @define	GW_VALUE_APP_RECENT_SIZE_MAX	The maximum size of recents opened file list */
#define GW_VALUE_APP_RECENT_SIZE_MAX 20
/*! @define	GW_VALUE_APP_GUI_RC_FILE	The variable name for the GTK+ ressource file properties */
#define GW_VALUE_APP_GUI_RC_FILE "GWhere.application.gui.rc"
/*! @define	GW_VALUE_APP_GUI_RC_FILE_DEFAULT	The default GTK+ ressource file name */
#define GW_VALUE_APP_GUI_RC_FILE_DEFAULT "gwhererc"
/*! @define	GW_VALUE_APP_GUI_AUTOSAVE	The variable name for the autosaving GUI properties */
#define GW_VALUE_APP_GUI_AUTOSAVE "GWhere.application.gui.autosave"
/*! @define	GW_VALUE_APP_GUI_BEEP	The variable name for allowing beep */
#define GW_VALUE_APP_GUI_BEEP "GWhere.application.gui.beep"
/*! @define	GW_VALUE_APP_GUI_BEEP_DEFAULT	The default value for allowing beep */
#define GW_VALUE_APP_GUI_BEEP_DEFAULT 0
/*! @define	GW_VALUE_APP_WIN_X	The variable name for window horizontal position */
#define GW_VALUE_APP_WIN_X "GWhere.application.window.x"
/*! @define	GW_VALUE_APP_WIN_X_DEFAULT	The default value for window horizontal position */
#define GW_VALUE_APP_WIN_X_DEFAULT 0
/*! @define	GW_VALUE_APP_WIN_Y	The variable name for window vertical position */
#define GW_VALUE_APP_WIN_Y "GWhere.application.window.y"
/*! @define	GW_VALUE_APP_WIN_Y_DEFAULT	The default value for window vertical position */
#define GW_VALUE_APP_WIN_Y_DEFAULT 0
/*! @define	GW_VALUE_APP_WIN_HEIGHT	The variable name for window vertical size */
#define GW_VALUE_APP_WIN_HEIGHT "GWhere.application.window.height"
/*! @define	GW_VALUE_APP_WIN_HEIGHT_DEFAULT	The default value for window vertical size */
#define GW_VALUE_APP_WIN_HEIGHT_DEFAULT 600
/*! @define	GW_VALUE_APP_WIN_WIDTH	The variable name for window horizontal size */
#define GW_VALUE_APP_WIN_WIDTH "GWhere.application.window.width"
/*! @define	GW_VALUE_APP_WIN_WIDTH_DEFAULT	The default value for window horizontal size */
#define GW_VALUE_APP_WIN_WIDTH_DEFAULT 800
/*! @define	GW_VALUE_APP_EXPLORER_HPAN_POSITION	The variable name for the horizontal pane position */
#define GW_VALUE_APP_EXPLORER_HPAN_POSITION "GWhere.application.explorer.hpan.pos"
/*! @define	GW_VALUE_APP_EXPLORER_HPAN_POSITION_DEFAULT	The default value for variable name for the horizontal pane position */
#define GW_VALUE_APP_EXPLORER_HPAN_POSITION_DEFAULT 205
/*! @define	GW_VALUE_APP_WIN_WIDTH_DEFAULT	The default value for window horizontal size */
#define GW_VALUE_APP_WIN_WIDTH_DEFAULT 800
/*! @define	GW_VALUE_APP_CATALOG_AUTOLOAD	The variable name for the autoloading catalog option */
#define GW_VALUE_APP_CATALOG_AUTOLOAD "GWhere.application.catalog.autoload"
/*! @define	GW_VALUE_APP_CATALOG_AUTOLOAD_LAST	The variable name for the autoloading last opened catalog option */
#define GW_VALUE_APP_CATALOG_AUTOLOAD_LAST "GWhere.application.catalog.autoload.last"
/*! @define	GW_VALUE_APP_CATALOG_AUTOLOAD_SELECTED	The variable name for the autoloading selected catalog option */
#define GW_VALUE_APP_CATALOG_AUTOLOAD_SELECTED "GWhere.application.catalog.autoload.selected"
/*! @define	GW_VALUE_APP_CATALOG_AUTOLOAD_FILEPATH	The variable name for the autoloading file path */
#define GW_VALUE_APP_CATALOG_AUTOLOAD_FILEPATH "GWhere.application.catalog.autoload.filepath"
/*! @define	GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL	The variable name for the catalog compression ratio */
#define GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL "GWhere.application.catalog.compression.level"
/*! @define	GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_DEFAULT	The default catalog compression ratio */
#define GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_DEFAULT 3
/*! @define	GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_MIN	The minimum catalog compression ratio */
#define GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_MIN 0
/*! @define	GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_MAX	The maximun catalog compression ratio */
#define GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_MAX 9
/*! @define	GW_VALUE_APP_MAIL_EMAIL_ADDRESS	The variable name for email adress */
#define GW_VALUE_APP_MAIL_EMAIL_ADDRESS "GWhere.application.mail.email.address"
/*! @define	GW_VALUE_APP_MAIL_SERVER_ADDRESS	The variable name for outgoing mail server name */
#define GW_VALUE_APP_MAIL_SERVER_ADDRESS "GWhere.application.mail.server.address"
/*! @define	GW_VALUE_APP_MAIL_SERVER_PORT	The variable name for outgoing mail server port */
#define GW_VALUE_APP_MAIL_SERVER_PORT "GWhere.application.mail.server.port"
/*! @define	GW_VALUE_APP_MAIL_SERVER_PORT_DEFAULT	The default outgoing mail server port */
#define GW_VALUE_APP_MAIL_SERVER_PORT_DEFAULT "25"
/*! @define	GW_VALUE_APP_SEARCH_STRING	The variable name for search string */
#define GW_VALUE_APP_SEARCH_STRING "GWhere.application.search.string"
/*! @define	GW_VALUE_APP_SEARCH_CASE_SENSITIVE	The variable name for search case sensitive status */
#define GW_VALUE_APP_SEARCH_CASE_SENSITIVE "GWhere.application.search.case_sensitive"
/*! @define	GW_VALUE_APP_SEARCH_CASE_SENSITIVE_DEFAULT	The default value of search case sensitive status */
#define GW_VALUE_APP_SEARCH_CASE_SENSITIVE_DEFAULT 0
/*! @define	GW_VALUE_APP_SEARCH_TYPE	The variable name for search type */
#define GW_VALUE_APP_SEARCH_TYPE "GWhere.application.search.type"
/*! @define	GW_VALUE_APP_SEARCH_TYPE_DEFAULT	The default value of search type */
#define GW_VALUE_APP_SEARCH_TYPE_DEFAULT 0
/*! @define	GW_VALUE_APP_SEARCH_TYPE_KEY_WORDS_MODE	The variable name for key words search mode */
#define GW_VALUE_APP_SEARCH_TYPE_KEY_WORDS_MODE "GWhere.application.search.type.key_words.mode"
/*! @define	GW_VALUE_APP_SEARCH_TYPE_KEY_WORDS_MODE_DEFAULT	The default value for key words search mode 0=all 1=only one */
#define GW_VALUE_APP_SEARCH_TYPE_KEY_WORDS_MODE_DEFAULT 0
/*! @define	GW_VALUE_APP_SEARCH_FILE_NAME	The variable name for search in file name */
#define GW_VALUE_APP_SEARCH_FILE_NAME "GWhere.application.search.file"
/*! @define	GW_VALUE_APP_SEARCH_FILE_NAME_DEFAULT	The default value of search in file name */
#define GW_VALUE_APP_SEARCH_FILE_NAME_DEFAULT 1
/*! @define	GW_VALUE_APP_SEARCH_FOLDER_NAME	The variable name for search in folder name */
#define GW_VALUE_APP_SEARCH_FOLDER_NAME "GWhere.application.search.folder"
/*! @define	GW_VALUE_APP_SEARCH_FOLDER_NAME_DEFAULT	The default value of search in folder name */
#define GW_VALUE_APP_SEARCH_FOLDER_NAME_DEFAULT 0
/*! @define	GW_VALUE_APP_SEARCH_DISK_NAME	The variable name for search in disk name */
#define GW_VALUE_APP_SEARCH_DISK_NAME "GWhere.application.search.disk"
/*! @define	GW_VALUE_APP_SEARCH_DISK_NAME_DEFAULT	The default value of search in disk name */
#define GW_VALUE_APP_SEARCH_DISK_NAME_DEFAULT 0
/*! @define	GW_VALUE_APP_SEARCH_CATEGORY_NAME	The variable name for search in category name */
#define GW_VALUE_APP_SEARCH_CATEGORY_NAME "GWhere.application.search.category"
/*! @define	GW_VALUE_APP_SEARCH_CATEGORY_NAME_DEFAULT	The default value of search in categoryname */
#define GW_VALUE_APP_SEARCH_CATEGORY_NAME_DEFAULT 0
/*! @define	GW_VALUE_APP_SEARCH_DESCRIPTION	The variable name for search in description */
#define GW_VALUE_APP_SEARCH_DESCRIPTION "GWhere.application.search.description"
/*! @define	GW_VALUE_APP_SEARCH_DESCRIPTION_DEFAULT	The default value of search in description name */
#define GW_VALUE_APP_SEARCH_DESCRIPTION_DEFAULT 0
/*! @define	GW_VALUE_APP_DISK_SELECTED	The variable name for selected disk */
#define GW_VALUE_APP_DISK_SELECTED "GWhere.application.disk.selected"
/*! @define	GW_VALUE_APP_DISK_SELECTED_DEFAULT	The default value of selected disk */
#define GW_VALUE_APP_DISK_SELECTED_DEFAULT "/mnt/cdrom"
/*! @define	GW_VALUE_APP_DISK_DISPLAY_INFO	The variable name for option diplaying information */
#define GW_VALUE_APP_DISK_DISPLAY_INFO "GWhere.application.disk.display_info"
/*! @define	GW_VALUE_APP_DISK_DISPLAY_INFO_DEFAULT	The default value for the displaying information */
#define GW_VALUE_APP_DISK_DISPLAY_INFO_DEFAULT 0
/*! @define	GW_VALUE_APP_DISK_SCAN_EXPLORE_ARCHIVE	The variable name of option exploring archive files */
#define GW_VALUE_APP_DISK_SCAN_EXPLORE_ARCHIVE "GWhere.application.disk.scan.explore_archive"
/*! @define	GW_VALUE_APP_DISK_SCAN_EXPLORE_ARCHIVE_DEFAULT	The default value of the option exploring archive files */
#define GW_VALUE_APP_DISK_SCAN_EXPLORE_ARCHIVE_DEFAULT 0
/*! @define	GW_VALUE_APP_DISK_SCAN_EXPLORE_TREE_STRUCTURE	The variable name of option exploring the tree structure */
#define GW_VALUE_APP_DISK_SCAN_EXPLORE_TREE_STRUCTURE "GWhere.application.disk.scan.explore_tree_structure"
/*! @define	GW_VALUE_APP_DISK_SCAN_EXPLORE_TREE_STRUCTURE_DEFAULT	The default value of the option exploring the tree structure */
#define GW_VALUE_APP_DISK_SCAN_EXPLORE_TREE_STRUCTURE_DEFAULT 1
/*! @define	GW_VALUE_APP_DISK_SCAN_CATEGORY	The variable name of option setting recursively category */
#define GW_VALUE_APP_DISK_SCAN_CATEGORY "GWhere.application.disk.scan.category"
/*! @define	GW_VALUE_APP_DISK_SCAN_CATEGORY_DEFAULT	The default value of option setting recursively category */
#define GW_VALUE_APP_DISK_SCAN_CATEGORY_DEFAULT 1
/*! @define	GW_VALUE_APP_DISK_SCAN_DESCRIPTION	The variable name of option scanning file description */
#define GW_VALUE_APP_DISK_SCAN_DESCRIPTION "GWhere.application.disk.scan.description"
/*! @define	GW_VALUE_APP_DISK_SCAN_DESCRIPTION_DEFAULT	The default value of option scanning file description */
#define GW_VALUE_APP_DISK_SCAN_DESCRIPTION_DEFAULT 0
/*! @define	GW_VALUE_APP_DISK_SCAN_LABEL	The variable name of option using volume name as disk name */
#define GW_VALUE_APP_DISK_SCAN_LABEL "GWhere.application.disk.scan.label"
/*! @define	GW_VALUE_APP_DISK_SCAN_LABEL_DEFAULT	The default value of option using volume name as disk name */
#define GW_VALUE_APP_DISK_SCAN_LABEL_DEFAULT 0
/*! @define	GW_VALUE_APP_DISK_AUTOMOUNT	The variable name of option automounting disk */
#define GW_VALUE_APP_DISK_AUTOMOUNT "GWhere.application.disk.automount"
/*! @define	GW_VALUE_APP_DISK_AUTOMOUNT_DEFAULT	The default value of option automounting disk */
#define GW_VALUE_APP_DISK_AUTOMOUNT_DEFAULT 0
/*! @define	GW_VALUE_APP_DISK_EJECT	The variable name of option autojecting disk */
#define GW_VALUE_APP_DISK_EJECT "GWhere.application.disk.eject"
/*! @define	GW_VALUE_APP_DISK_EJECT_DEFAULT	The default value of option autoejecting disk */
#define GW_VALUE_APP_DISK_EJECT_DEFAULT 1
/*! @define	GW_VALUE_APP_DISK_SCAN_USE_PATTERN	The variable name of option using pattern for disk name */
#define GW_VALUE_APP_DISK_SCAN_USE_PATTERN "GWhere.application.disk.scan.use_pattern"
/*! @define	GW_VALUE_APP_DISK_SCAN_USE_PATTERN_DEFAULT	The default value of option using pattern for disk name */
#define GW_VALUE_APP_DISK_SCAN_USE_PATTERN_DEFAULT 1
/*! @define	GW_VALUE_APP_DISK_SCAN_PATTERN	The variable name of pattern for disk name */
#define GW_VALUE_APP_DISK_SCAN_PATTERN "GWhere.application.disk.scan.pattern"
/*! @define	GW_VALUE_APP_DISK_SCAN_PATTERN_DEFAULT	The default value of pattern for disk name */
#define GW_VALUE_APP_DISK_SCAN_PATTERN_DEFAULT ""


/*! @define	GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE	The variable name for the autoresize column option */
#define GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE "GWhere.application.explorer.column.autoresize"
/*! @define	GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE_DEFAULT	The default value of the autoresize column option */
#define GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE_DEFAULT 1
/*! @define	GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER	The variable name to know if the sort in explorer must group by folder */
#define GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER "GWhere.application.explorer.sort.by_folder"
/*! @define	GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER_DEFAULT	The default value of the sort in explorer must group by folder */
#define GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER_DEFAULT 1
/*! @define	GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE	The variable name to know if the sort in explorer is case sensitive */
#define GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE "GWhere.application.explorer.sort.case_sensitive"
/*! @define	GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE_DEFAULT	The default value of the sort in explorer is case sensitive */
#define GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE_DEFAULT 0


/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_TITLE	The title column of the column Name */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_TITLE N_( "Name")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SHOW	The variable name to if the column Name should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SHOW "GWhere.application.explorer.file.column.name.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SIZE	The variable name for the size the column Name */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SIZE "GWhere.application.explorer.file.column.name.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SIZE_DEFAULT	The default value of the size the column Name */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SIZE_DEFAULT 320
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION	The variable name for the position of the column Name */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION "GWhere.application.explorer.file.column.name.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT	The default value of the postion of the column Name */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT 0
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_TITLE	The title column of the column Rights */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_TITLE N_( "Rights")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SHOW	The variable name to if the column Rights should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SHOW "GWhere.application.explorer.file.column.rights.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SIZE	The variable name for the size the column Rights */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SIZE "GWhere.application.explorer.file.column.rights.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SIZE_DEFAULT	The default value of the size the column Rights */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SIZE_DEFAULT 65
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION	The variable name for the position of the column Rights */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION "GWhere.application.explorer.file.column.rights.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT	The default value of the position of the column Rights */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT 1
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_TITLE	The title column of the column Owner */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_TITLE N_( "Owner")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SHOW	The variable name to if the column Owner should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SHOW "GWhere.application.explorer.file.column.owner.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SIZE	The variable name for the size the column Owner */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SIZE "GWhere.application.explorer.file.column.owner.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SIZE_DEFAULT	The default value of the size the column Owner */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SIZE_DEFAULT 40
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION	The variable name for the position of the column Owner */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION "GWhere.application.explorer.file.column.owner.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT	The default value of the position of the column Owner */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT 2
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_TITLE	The title column of the column Group */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_TITLE N_( "Group")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SHOW	The variable name to if the column Group should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SHOW "GWhere.application.explorer.file.column.group.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SIZE	The variable name for the size the column Group */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SIZE "GWhere.application.explorer.file.column.group.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SIZE_DEFAULT	The default value of the size the column Group */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SIZE_DEFAULT 40
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION	The variable name for the position of the column Group */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION "GWhere.application.explorer.file.column.group.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT	The default value of the position of the column Group */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT 3
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_TITLE	The title column of the column Size */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_TITLE N_( "Size")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SHOW	The variable name to if the column Size should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SHOW "GWhere.application.explorer.file.column.size.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SIZE	The variable name for the size the column Size */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SIZE "GWhere.application.explorer.file.column.size.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SIZE_DEFAULT	The default value of the size the column Size */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION	The variable name for the position of the column Size */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION "GWhere.application.explorer.file.column.size.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT	The default value of the position of the column Size */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT 4
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_TITLE	The title column of the column INode */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_TITLE N_( "INode")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SHOW	The variable name to if the column INode should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SHOW "GWhere.application.explorer.file.column.inode.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SIZE	The variable name for the size the column INode */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SIZE "GWhere.application.explorer.file.column.inode.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SIZE_DEFAULT	The default value of the size the column INode */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SIZE_DEFAULT 35
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION	The variable name for the position of the column INode */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION "GWhere.application.explorer.file.column.inode.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT	The default value of the position of the column INode */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT 5
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_TITLE	The title column of the column Access Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_TITLE N_( "Access date")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SHOW	The variable name to if the column Access Date should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SHOW "GWhere.application.explorer.file.column.adate.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SIZE	The variable name for the size the column Access Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SIZE "GWhere.application.explorer.file.column.adate.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SIZE_DEFAULT	The default value of the size the column Access Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION	The variable name for the position the column Access Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION "GWhere.application.explorer.file.column.adate.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT	The default value of the position of the column Access Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT 6
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_TITLE	The title column of the column Modification Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_TITLE N_( "Modification date")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SHOW	The variable name to if the column Modification Date should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SHOW "GWhere.application.explorer.file.column.mdate.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SIZE	The variable name for the size the column Modification Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SIZE "GWhere.application.explorer.file.column.mdate.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SIZE_DEFAULT	The default value of the size the column Modification Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION	The variable name for the position of the column Modification Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION "GWhere.application.explorer.file.column.mdate.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT	The default value of the position of the column Modification Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT 7
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_TITLE	The title column of the column Creation Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_TITLE N_( "Creation date")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SHOW	The variable name to if the column Create Date should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SHOW "GWhere.application.explorer.file.column.cdate.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_CDATE_NAME_SIZE	The variable name for the size the column Creation Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SIZE "GWhere.application.explorer.file.column.cdate.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SIZE_DEFAULT	The default value of the size the column Creation Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_EXPLORER_FILE_CDATE_NAME_POSITION	The variable name for the position of the column Creation Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION "GWhere.application.explorer.file.column.cdate.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT	The default value of the position of the column Creation Date */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT 8
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_TITLE	The title column of the column Category */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_TITLE N_( "Category")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SHOW	The variable name to if the column Category should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SHOW "GWhere.application.explorer.file.column.category.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SIZE	The variable name for the size the column Category */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SIZE "GWhere.application.explorer.file.column.category.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SIZE_DEFAULT	The default value of the size the column Category */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION	The variable name for the position of the column Category */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION "GWhere.application.explorer.file.column.category.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT	The default value of the position of the column Category */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT 9
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_TITLE	The title column of the column Description */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_TITLE N_( "Description")
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SHOW	The variable name to if the column Description should be showed */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SHOW "GWhere.application.explorer.file.column.description.show"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SIZE	The variable name for the size the column Description */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SIZE "GWhere.application.explorer.file.column.description.size"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SIZE_DEFAULT	The default value of the size the column Description */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SIZE_DEFAULT 100
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION	The variable name for the position of the column Description */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION "GWhere.application.explorer.file.column.description.position"
/*! @define	GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT	The default value of the position of the column Description */
#define GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT 10


/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_TITLE	The title column of the column Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_TITLE N_( "Name")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SHOW	The variable name to if the column Name should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SHOW "GWhere.application.explorer.disk.column.name.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SIZE	The variable name for the size the column Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SIZE "GWhere.application.explorer.disk.column.name.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SIZE_DEFAULT	The default value of the size the column Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SIZE_DEFAULT 200
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION	The variable name for the position of the column Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION "GWhere.application.explorer.disk.column.name.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT	The default value of the postion of the column Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT 0
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_TITLE	The title column of the column File System Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_TITLE N_( "File system name")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SHOW	The variable name to if the column File System Name should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SHOW "GWhere.application.explorer.disk.column.fsname.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SIZE	The variable name for the size the column File System Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SIZE "GWhere.application.explorer.disk.column.fsname.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SIZE_DEFAULT	The default value of the size the column File System Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SIZE_DEFAULT 65
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION	The variable name for the position of the column File System Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION "GWhere.application.explorer.disk.column.fsname.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT	The default value of the position of the column Rights */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT 1
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_TITLE	The title column of the column Access Path */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_TITLE N_( "Access path")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SHOW	The variable name to if the column Access Path should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SHOW "GWhere.application.explorer.disk.column.path.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SIZE	The variable name for the size the column Access Path */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SIZE "GWhere.application.explorer.disk.column.path.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SIZE_DEFAULT	The default value of the size the column Access Path */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SIZE_DEFAULT 65
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION	The variable name for the position of the column Access Path */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION "GWhere.application.explorer.disk.column.path.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT	The default value of the position of the column Access Path */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT 2
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_TITLE	The title column of the column Archive Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_TITLE N_( "Archive N#")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SHOW	The variable name to if the column Archive Number should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SHOW "GWhere.application.explorer.disk.column.archivenb.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SIZE	The variable name for the size the column Archive Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SIZE "GWhere.application.explorer.disk.column.archivenb.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_GROUP_SIZE_DEFAULT	The default value of the size the column Archive Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SIZE_DEFAULT 65
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION	The variable name for the position of the column Archive Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION "GWhere.application.explorer.disk.column.archivenb.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT	The default value of the position of the column Archive Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT 3
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_TITLE	The title column of the column Type */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_TITLE N_( "Type")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SHOW	The variable name to if the column Type should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SHOW "GWhere.application.explorer.disk.column.type.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SIZE	The variable name for the size the column Type */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SIZE "GWhere.application.explorer.disk.column.type.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SIZE_DEFAULT	The default value of the size the column Type */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SIZE_DEFAULT 120
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION	The variable name for the position of the column Type */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION "GWhere.application.explorer.disk.column.type.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT	The default value of the position of the column Type */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT 4
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_TITLE	The title column of the column Volume Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_TITLE N_( "Volume name")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SHOW	The variable name to if the column Volume Name should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SHOW "GWhere.application.explorer.disk.column.volume.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SIZE	The variable name for the size the column Volume Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SIZE "GWhere.application.explorer.disk.column.volume.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SIZE_DEFAULT	The default value of the size the column Volume Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SIZE_DEFAULT 80
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION	The variable name for the position of the column Volume Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION "GWhere.application.explorer.disk.column.volume.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT	The default value of the position of the column Volume Name */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT 5
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_TITLE	The title column of the column Full Capacity */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_TITLE N_( "Full capacity")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SHOW	The variable name to if the column Full Capacity should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SHOW "GWhere.application.explorer.disk.column.capacity.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SIZE	The variable name for the size the column Full Capacity */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SIZE "GWhere.application.explorer.disk.column.capacity.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SIZE_DEFAULT	The default value of the size the column Full Capacity */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION	The variable name for the position the column Full Capacity */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION "GWhere.application.explorer.disk.column.capacity.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT	The default value of the position of the column Full Capacity */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT 6
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_TITLE	The title column of the column Free Space */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_TITLE N_( "Free space")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SHOW	The variable name to if the column Free Space should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SHOW "GWhere.application.explorer.disk.column.free.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SIZE	The variable name for the size the column Free Space */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SIZE "GWhere.application.explorer.disk.column.free.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SIZE_DEFAULT	The default value of the size the column Free Space */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SIZE_DEFAULT 65
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION	The variable name for the position of the column Free Space */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION "GWhere.application.explorer.disk.column.free.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT	The default value of the position of the column Free Space */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT 7
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_TITLE	The title column of the column Date */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_TITLE N_( "Date")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SHOW	The variable name to if the column Date should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SHOW "GWhere.application.explorer.disk.column.date.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SIZE	The variable name for the size the column Date */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SIZE "GWhere.application.explorer.disk.column.date.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SIZE_DEFAULT	The default value of the size the column Date */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION	The variable name for the position of the column Date */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION "GWhere.application.explorer.disk.column.date.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT	The default value of the position of the column Date */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT 8
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_TITLE	The title column of the column Serial Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_TITLE N_( "Serial number")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SHOW	The variable name to if the column Serial Number should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SHOW "GWhere.application.explorer.disk.column.serial.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SIZE	The variable name for the size the column Serial Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SIZE "GWhere.application.explorer.disk.column.serial.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SIZE_DEFAULT	The default value of the size the column Serial Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION	The variable name for the position of the column Serial Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION "GWhere.application.explorer.disk.column.serial.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT	The default value of the position of the column Serial Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT 9
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_TITLE	The title column of the column Serial Number */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_TITLE N_( "Category")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SHOW	The variable name to if the column Category should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SHOW "GWhere.application.explorer.disk.column.category.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SIZE	The variable name for the size the column Category */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SIZE "GWhere.application.explorer.disk.column.category.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SIZE_DEFAULT	The default value of the size the column Category */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION	The variable name for the position of the column Category */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION "GWhere.application.explorer.disk.column.category.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT	The default value of the position of the column Category */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT 10
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_TITLE	The title column of the column Description */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_TITLE N_( "Description")
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SHOW	The variable name to if the column Description should be showed */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SHOW "GWhere.application.explorer.disk.column.description.show"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SIZE	The variable name for the size the column Description */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SIZE "GWhere.application.explorer.disk.column.description.size"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SIZE_DEFAULT	The default value of the size the column Description */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SIZE_DEFAULT 100
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION	The variable name for the position of the column Description */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION "GWhere.application.explorer.disk.column.description.position"
/*! @define	GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT	The default value of the position of the column Description */
#define GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT 11


/*! @define	GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE	The variable name for the autoresize column option */
#define GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE "GWhere.application.search.column.autoresize"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE_DEFAULT	The default value of the autoresize column option */
#define GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE_DEFAULT 1
/*! @define	GW_VALUE_APP_SEARCH_SORT_BY_FOLDER	The variable name to know if the sort in search must group by type : catalog/disk/folder/file */
#define GW_VALUE_APP_SEARCH_SORT_BY_TYPE "GWhere.application.search.sort.by_type"
/*! @define	GW_VALUE_APP_SEARCH_SORT_BY_FOLDER_DEFAULT	The default value of the sort in search must group by type : catalog/disk/folder/file */
#define GW_VALUE_APP_SEARCH_SORT_BY_TYPE_DEFAULT 1
/*! @define	GW_VALUE_APP_SEARCH_SORT_CASE_SENSITIVE	The variable name to know if the sort in search is case sensitive */
#define GW_VALUE_APP_SEARCH_SORT_CASE_SENSITIVE "GWhere.application.search.sort.case_sensitive"
/*! @define	GW_VALUE_APP_SEARCH_SORT_CASE_SENSITIVE_DEFAULT	The default value of the sort in search is case sensitive */
#define GW_VALUE_APP_SEARCH_SORT_CASE_SENSITIVE_DEFAULT 0


/*! @define	GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE	The variable name for the autoresize column option */
#define GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE "GWhere.application.search.column.autoresize"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE_DEFAULT	The default value of the autoresize column option */
#define GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE_DEFAULT 1
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_NAME_TITLE	The title column of the column Name */
#define GW_VALUE_APP_SEARCH_COLUMN_NAME_TITLE N_( "Name")
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_NAME_SHOW	The variable name to if the column Name should be showed */
#define GW_VALUE_APP_SEARCH_COLUMN_NAME_SHOW "GWhere.application.search.column.name.show"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_NAME_SIZE	The variable name for the size the column Name */
#define GW_VALUE_APP_SEARCH_COLUMN_NAME_SIZE "GWhere.application.search.column.name.size"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_NAME_SIZE_DEFAULT	The default value of the size the column Name */
#define GW_VALUE_APP_SEARCH_COLUMN_NAME_SIZE_DEFAULT 200
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION	The variable name for the position of the column Name */
#define GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION "GWhere.application.search.column.name.position"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION_DEFAULT	The default value of the postion of the column Name */
#define GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION_DEFAULT 0
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_RIGHTS_TITLE	The title column of the column Rights */
#define GW_VALUE_APP_SEARCH_COLUMN_DISK_TITLE N_( "Disk")
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DISK_SHOW	The variable name to if the column Disk should be showed */
#define GW_VALUE_APP_SEARCH_COLUMN_DISK_SHOW "GWhere.application.search.column.disk.show"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DISK_SIZE	The variable name for the size the column Disk */
#define GW_VALUE_APP_SEARCH_COLUMN_DISK_SIZE "GWhere.application.search.column.disk.size"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DISK_SIZE_DEFAULT	The default value of the size the column Disk */
#define GW_VALUE_APP_SEARCH_COLUMN_DISK_SIZE_DEFAULT 160
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION	The variable name for the position of the column Disk */
#define GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION "GWhere.application.search.column.disk.position"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION_DEFAULT	The default value of the position of the column Disk */
#define GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION_DEFAULT 1
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_PATH_TITLE	The title column of the column Path */
#define GW_VALUE_APP_SEARCH_COLUMN_PATH_TITLE N_( "Path")
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_PATH_SHOW	The variable name to if the column Path should be showed */
#define GW_VALUE_APP_SEARCH_COLUMN_PATH_SHOW "GWhere.application.search.column.path.show"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_PATH_SIZE	The variable name for the size the column Path */
#define GW_VALUE_APP_SEARCH_COLUMN_PATH_SIZE "GWhere.application.search.column.path.size"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_PATH_SIZE_DEFAULT	The default value of the size the column Path */
#define GW_VALUE_APP_SEARCH_COLUMN_PATH_SIZE_DEFAULT 320
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION	The variable name for the position of the column Path */
#define GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION "GWhere.application.search.column.path.position"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION_DEFAULT	The default value of the position of the column Path */
#define GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION_DEFAULT 2
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_SIZE_TITLE	The title column of the column Size */
#define GW_VALUE_APP_SEARCH_COLUMN_SIZE_TITLE N_( "Size")
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_SIZE_SHOW	The variable name to if the column Size should be showed */
#define GW_VALUE_APP_SEARCH_COLUMN_SIZE_SHOW "GWhere.application.search.column.size.show"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_SIZE_SIZE	The variable name for the size the column Size */
#define GW_VALUE_APP_SEARCH_COLUMN_SIZE_SIZE "GWhere.application.search.column.size.size"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_SIZE_SIZE_DEFAULT	The default value of the size the column Size */
#define GW_VALUE_APP_SEARCH_COLUMN_SIZE_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION	The variable name for the position of the column Size */
#define GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION "GWhere.application.search.column.size.position"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION_DEFAULT	The default value of the position of the column Size */
#define GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION_DEFAULT 3
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DATE_TITLE	The title column of the column Date */
#define GW_VALUE_APP_SEARCH_COLUMN_DATE_TITLE N_( "Date")
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DATE_SHOW	The variable name to if the column Date should be showed */
#define GW_VALUE_APP_SEARCH_COLUMN_DATE_SHOW "GWhere.application.search.column.date.show"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DATE_SIZE	The variable name for the size the column Date */
#define GW_VALUE_APP_SEARCH_COLUMN_DATE_SIZE "GWhere.application.search.column.date.size"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DATE_SIZE_DEFAULT	The default value of the size the column Date */
#define GW_VALUE_APP_SEARCH_COLUMN_DATE_SIZE_DEFAULT 120
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION	The variable name for the position of the column Date */
#define GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION "GWhere.application.search.column.date.position"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION_DEFAULT	The default value of the position of the column Date */
#define GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION_DEFAULT 4
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_TITLE	The title column of the column Category */
#define GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_TITLE N_( "Category")
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SHOW	The variable name to if the column Category should be showed */
#define GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SHOW "GWhere.application.search.column.category.show"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SIZE	The variable name for the size the column Category */
#define GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SIZE "GWhere.application.search.column.category.size"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SIZE_DEFAULT	The default value of the size the column Category */
#define GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION	The variable name for the position of the column Category */
#define GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION "GWhere.application.search.column.category.position"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION_DEFAULT	The default value of the position of the column Category */
#define GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION_DEFAULT 5
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_TITLE	The title column of the column Description */
#define GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_TITLE N_( "Description")
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SHOW	The variable name to if the column Description should be showed */
#define GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SHOW "GWhere.application.search.column.description.show"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SIZE	The variable name for the size the column Description */
#define GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SIZE "GWhere.application.search.column.description.size"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SIZE_DEFAULT	The default value of the size the column Description */
#define GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SIZE_DEFAULT 60
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION	The variable name for the position the column Description */
#define GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION "GWhere.application.search.column.description.position"
/*! @define	GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION_DEFAULT	The default value of the position of the column Description */
#define GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION_DEFAULT 6


/*!
 * @function	gw_am_init
 * @abstract	Initializes the application settings.
 * @discussion	This function initializes the application settings.
 * @param	filepath	file path of the catalog to load
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_am_init ( gint argc, gchar *argv[]);


/*!
 * @function	gw_am_load_default_settings
 * @abstract	Loads default settings.
 * @discussion	This function loads default settings.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_am_load_default_settings ( );


/*!
 * @function	gw_am_can_send_mail
 * @abstract	Checks if can send mails.
 * @discussion	This function checks if can send mails. To
 *		send mails, the user must configure mail
 *		options in the settings.
 * @result	Returns <i>TRUE</i> if can send mails.<br>
 *		Returns <i>FALSE</i> if cannot send mails or
 *		when an error occured.
 */
gboolean gw_am_can_send_mail ( );


/*!
 * @function	gw_am_get_settings_tod
 * @abstract	Gets the gfloat value of a setting.
 * @discussion	This function gets the gfloat value of a setting.
 * @param	name	name of setting
 * @result	the gfloat value of setting.
 */
gfloat gw_am_get_settings_tod ( const gchar *name);


/*!
 * @function	gw_am_get_settings_tol
 * @abstract	Gets the gint value of a setting.
 * @discussion	This function gets the gint value of a setting.
 * @param	name	name of setting
 * @result	the gint value of setting.
 */
gint gw_am_get_settings_tol ( const gchar *name);


/*!
 * @function	gw_am_get_settings_tolx
 * @abstract	Gets the gint value of a setting.
 * @discussion	This function gets the gint value of a setting.
 * @param	name	name of setting
 * @param	value	the default value
 * @result	the gint value of setting or the default value if
 *		doesn't exist.
 */
gint gw_am_get_settings_tolx ( const gchar *name, const gint value);


/*!
 * @function	gw_am_get_settings_tob
 * @abstract	Gets the gboolean value of a setting.
 * @discussion	This function gets the gboolean value of a setting.
 * @param	name	name of setting
 * @result	the gboolean value of setting.
 */
gboolean gw_am_get_settings_tob ( const gchar *name);


/*!
 * @function	gw_am_get_settings_tobx
 * @abstract	Gets the gboolean value of a setting.
 * @discussion	This function gets the gboolean value of a setting.
 * @param	name	name of setting
 * @param	value	the default value
 * @result	the gboolean value of setting or the default value if
 *		doesn't exist.
 */
gboolean gw_am_get_settings_tobx ( const gchar *name, const gboolean value);


/*!
 * @function	gw_am_get_settings
 * @abstract	Gets the value of a setting.
 * @discussion	This function gets the value of a setting.
 * @param	name	name of setting
 * @result	the value of setting.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_am_get_settings ( const gchar *name);


/*!
 * @function	gw_am_get_settings
 * @abstract	Gets the value of a setting.
 * @discussion	This function gets the value of a setting.
 * @param	name	name of setting
 * @param	value	value of setting
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_am_set_settings ( const gchar *name, gchar *value);


/*!
 * @function	gw_application_get_current_catalog
 * @abstract	Gets the current opened catalog file informations.
 * @discussion	This function gets the current opened catalog file informations.
 * @result	the catalog file informations.<br>
 *		Returns <i>NULL</i> when no catalog opened or when an error occured.
 */
struct catalog_file_info * gw_am_get_current_catalog ( void);


/*!
 * @function	gw_am_exit
 * @abstract	Exits the application and processes to all savings.
 * @discussion	This function exits the application and processes to all savings.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_am_exit ( );


/*!
 * @function	gw_am_send_mail
 * @abstract	Sends an mail from the application.
 * @discussion	This function sends an mail from the application.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_am_send_mail ( GWMail *mail);


/*!
 * @function	gw_am_load_catalog
 * @abstract	Loads a catalog in the application.
 * @discussion	This function loads a catalog in the application.
 * @param	filepath	catalog file path
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_am_load_catalog ( const char *filepath);


/*!
 * @function	gw_am_save_catalog
 * @abstract	Saves the current opened a catalog in the application.
 * @discussion	This function saves the current opened a catalog in the application.
 * @param	path	the new file name to save the catalog
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_am_save_catalog ( const gchar *path);


/*!
 * @function	gw_am_close_catalog
 * @abstract	Closes the current opened a catalog in the application.
 * @discussion	This function closes the current opened a catalog in the application.
 * @param	save	<i>TRUE</i> if it should check if the catalog is modified before close it.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_am_close_catalog ( gboolean save);


/*!
 * @function	gw_am_add_recent_file
 * @abstract	Adds an entry to the recents opened catalog files list.
 * @discussion	This function adds an entry to the recents opened catalog files list.
 * @param	filepath	file path to add
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_am_add_recent_file ( const gchar *filepath);


/*!
 * @function	gw_am_load_catalog_from_recents_files
 * @abstract	Loads a catalog in the application from the recents files list.
 * @discussion	This function loads a catalog in the application from the recents files list.
 * @param	index	position in the recents files list (start at <i>0</i>)
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_am_load_catalog_from_recents_files ( const guint index);


/*!
 * @function	gw_am_get_catalog_path_name_from_recents_files
 * @abstract	Gets the catalog path name in the application from the recents files list.
 * @discussion	This function gets the catalog path name in the application from
 *		the recents files list. It is a new allocated string (must be freed
 *		with g_free()).
 * @param	index	position in the recents files list (start at <i>0</i>)
 * @result	the catalog path name.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_am_get_catalog_path_name_from_recents_files ( const guint index);


/*!
 * @function	gw_am_log_msg
 * @abstract	Logs a message.
 * @discussion	This function logs a message.
 * @param	level	log level
 * @param	file	file where the log is invoked
 * @param	function	function where the log is invoked
 * @param	line	line where the log is invoked
 * @param	msg	message to log
 */
void gw_am_log_msg ( const gint level, const gchar *file, const gint line, const gchar *function, const gchar *msg, ...);


/*!
 * @function	gw_am_beep
 * @abstract	Emits a short beep.
 * @discussion	This function emits a short beep.
 */
void gw_am_beep ( );


/*!
 * @function	gw_plugin_settings_explorer_disk_get_all_fields
 * @abstract	Loads the list of all disk fields properties.
 * @discussion	This function loads the list of all disk fields properties.
 * @result	a table of fields properties, ended by <i>NULL</i>.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GWSettingsExplorerField ** gw_plugin_settings_explorer_disk_get_all_fields ( void);


/*!
 * @function	gw_plugin_settings_explorer_file_get_all_fields
 * @abstract	Loads the list of all file fields properties.
 * @discussion	This function loads the list of all file fields properties.
 * @result	a table of fields properties, ended by <i>NULL</i>.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GWSettingsExplorerField ** gw_plugin_settings_explorer_file_get_all_fields ( void);


/*!
 * @function	gw_plugin_settings_search_get_all_fields
 * @abstract	Loads the list of all search fields properties.
 * @discussion	This function loads the list of all search fields properties.
 * @result	a table of fields properties, ended by <i>NULL</i>.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GWSettingsExplorerField ** gw_plugin_settings_search_get_all_fields ( void);


void gw_am_set_current_catalog_context ( GWDBContext * context);


GWDBContext * gw_am_get_current_catalog_context ( );


gint gw_am_import_catalog_from ( GWCatalogPlugin *oplugin, GWCatalogPlugin *iplugin, gchar *db_name, gchar *short_db_name);


gint gw_am_export_catalog_to ( GWDBContext *context, GWCatalogPlugin *plugin, gchar *db_name, gchar *short_db_name);


gint gw_am_new_catalog ( const gchar *name);

#endif
