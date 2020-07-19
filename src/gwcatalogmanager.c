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


#include "gwsupport.h"
#include "gwcatalogmanager.h"

#if defined ( OS_CYGWIN) || defined ( OS_WIN32)
	/* A port for Cygwin OS, the GLib should be define this macro, but it doesn't work on my Cygwin OS */
	#define NAME_MAX 255
#elif defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD)
	/* For NAME_MAX and PATH_MAX */
	#include <sys/syslimits.h>
#endif

#include <gtk/gtk.h>
#include <sys/stat.h>
#include <sys/types.h> /* opendir */
#include <dirent.h> /* opendir */

/* Notes that exist win32 implementation of these librairies. */
#if defined ( OS_LINUX) || defined ( OS_CYGWIN) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD)
    #include <pwd.h>
    #include <grp.h>
#elif defined ( OS_WIN32)
/*  Should be used later with an external library (YAPL)
    #include <pwd.h>
*/
    #include <dirent.h>
#endif

#include <time.h>
#include <stdlib.h> /* strtol strtoul strtoull */
#include <stdio.h> /* perror */
#include <string.h> /* strncmp */
#include <errno.h>

/* To open and close files */
#include <fcntl.h>
#include <unistd.h> /* chdir readlink get_current_working_dir_name getcwd */

/* To catch any SIGSEGV restore memory */
#include <signal.h> /* signal */
#include <setjmp.h> /* setjmp longjmp */

#include "data/gwdata.h"
#include "tools/gwtools.h"
#include "res/gwres.h"
#include "gui/gwgui.h"

#include "gwhelper.h"
#include "gwapplicationmanager.h"
#include "gwpluginsmanager.h"
#include "gwguimanager.h"
#include "gwsupermount.h"


jmp_buf env;


void gw_cm_rollback_plugin_call ( int signum) {
#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "catch signum %d",signum);
#endif


	longjmp ( env, 1);
}


gint gw_cm_load_file_node ( GtkCTree *ctree, GtkCTreeNode *parent, GWDBFile *file) {
	gint i = 0, cpt = 0;
	gchar *text[1];
	GtkCTreeNode *node = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
	GWDBFile **files = NULL;


	if ( gw_db_file_is_real_directory ( file) ) {
		g_strdup_to_gtk_text ( gw_db_file_get_name ( file), text[0]);
		node = gtk_ctree_insert_node ( ctree, parent, NULL, text, 5, PixFolder, MskFolder, PixOpenFolder, MskOpenFolder, FALSE, FALSE);
		gtk_ctree_node_set_row_data ( ctree, node, gw_db_file_get_ref ( file));

		/* Loads folder */
		if ( (files = plugin->gw_db_file_get_db_files ( context, gw_db_file_get_ref ( file))) != NULL) {
			for ( i = 0; files[i] != NULL; i++) {
				if ( gw_db_file_is_real_directory ( files[i])) {
					cpt++;
					gw_cm_load_file_node ( ctree, node, files[i]);
				}

				gw_db_file_free ( files[i]);
			}

			g_free ( files);
		} else {}

		if ( cpt==0 ) {
			if ( i == 0) {
				gtk_ctree_set_node_info ( ctree, node, text[0], 5, PixLockedFolder, MskLockedFolder, PixLockedFolder, MskLockedFolder, TRUE, FALSE);
			} else {
				gtk_ctree_set_node_info ( ctree, node, text[0], 5, PixFolder, MskFolder, PixOpenFolder, MskOpenFolder, TRUE, FALSE);
			}
		} else {}

		g_free ( text[0]);
	} else {}

	return cpt;
}


gint gw_cm_load_disk_node ( GtkCTree *ctree, GtkCTreeNode *parent, GWDBDisk *disk) {
	gchar *text[1];
	GtkCTreeNode *node = NULL;
	GdkPixmap *pix = NULL;
	GdkBitmap *msk = NULL;
	GWDBFile **files = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
	int i = 0;


	/* Creates the disk node */
	g_strdup_to_gtk_text ( gw_db_disk_get_name ( disk), text[0]);
	pix = gw_helper_db_disk_get_pixmap ( disk);
	msk = gw_helper_db_disk_get_bitmap ( disk);
	node = gtk_ctree_insert_node ( ctree, parent, NULL, text, 5, pix, msk, pix, msk, FALSE, FALSE);
	g_free ( text[0]);
	gtk_ctree_node_set_row_data ( ctree, node, gw_db_disk_get_ref ( disk));

	/* Loads disk */
	if ( (files = plugin->gw_db_disk_get_db_files ( context, gw_db_disk_get_ref ( disk))) != NULL) {
		for ( i = 0; files[i] != NULL; i++) {
			if ( gw_db_file_is_real_directory ( files[i])) {
				gw_cm_load_file_node ( ctree, node, files[i]);
			} else {}

			gw_db_file_free ( files[i]);
		}

		g_free ( files);
	} else {}

	return 0;
}


gint gw_cm_load ( GWDBContext *context) {
	gint result = -1;
	GtkCList *clist;
	gchar *tmp_text = NULL, *text_utf8 = NULL;
	gchar *text[1];
	GWDBCatalog *catalog = NULL;
	GWDBDisk **disks = NULL;
	gint i = 0;
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	GtkCList *clist_info = gw_notebook_catalog_get_clist_explorer ( window);
	GtkCTree *ctree = gw_gui_manager_main_interface_get_tree ( );
	GtkCTreeNode *root = gw_gui_manager_main_interface_get_tree_root ( );
	GWCatalogPlugin *plugin = ((GWCatalogPlugin*)gw_db_context_get_plugin ( context));


	gw_am_set_current_catalog_context ( context);
	catalog = plugin->gw_db_catalog_get_db_catalog ( context);

	/* Sets the new window title */
	tmp_text = g_strconcat ( PROJECT_NAME, " - ", gw_helper_db_catalog_get_full_name ( catalog), NULL);
	g_strdup_to_gtk_text ( tmp_text, text_utf8);
	g_free ( tmp_text);
	gtk_window_set_title ( window, text_utf8);
	g_free ( text_utf8);

	/* Freezes the exploration tree */
	clist = GTK_CLIST ( ctree);
	gtk_clist_freeze ( clist);
	gtk_clist_freeze ( clist_info);

	/* Creates catalog root node */
	g_strdup_to_gtk_text ( gw_helper_db_catalog_get_usefull_name ( catalog), text[0]);
	root = gtk_ctree_insert_node ( ctree, NULL, NULL, text, 5, PixCatalog, MskCatalog, PixCatalog, MskCatalog, FALSE, TRUE);
	g_free ( text[0]);
	gw_gui_manager_main_interface_set_tree_root ( root);

	/* Loads all disks */
	if ( (disks = ((GWCatalogPlugin*)gw_db_context_get_plugin ( context))->gw_db_catalog_get_db_disks ( context)) != NULL) {
		for ( i = 0; disks[i] != NULL; i++) {
			gw_cm_load_disk_node ( ctree, root, disks[i]);
			gw_db_disk_free ( disks[i]);
		}

		g_free ( disks);
	} else {}

	/* Loads all categories */
	gw_notebook_managment_refresh_categories ( window);

	/* Refreshes the exploration tree */
	root = gw_gui_manager_main_interface_get_tree_root ( );
	gtk_ctree_sort_recursive ( ctree, root);
	gtk_ctree_select ( ctree, root);
	gtk_clist_thaw ( clist);
	gtk_clist_thaw ( clist_info);

	return result;
}


gint gw_cm_add_disk ( struct scan_disk_info *scan_disk) {
	gchar past_dir[512];
	GWDBDisk * disk = NULL;
	gulong date;
	gchar *error_msg = NULL;
	struct vfs_stats *vfs = NULL;
	GWDBCategoryPK category = NULL;
	guint64 disk_size = G_GINT64_CONSTANT ( 0);
	GList *forbidden = NULL, *self = NULL, *current = NULL;
	gint i = 0;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = ((GWCatalogPlugin*)gw_db_context_get_plugin ( context));
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	GtkCList *clist_info = gw_notebook_catalog_get_clist_explorer ( window);
	GtkCTree *ctree = gw_gui_manager_main_interface_get_tree ( );
	GtkCTreeNode *parent = gw_gui_manager_main_interface_get_tree_root ( );


#if GW_DEBUG_TIME
	time_t begin;
	time ( &begin);
#endif

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	vfs = scan_disk_info_get_vfs ( scan_disk);
	category = scan_disk_info_get_disk_category_ref ( scan_disk);

#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
	vfs_stats_display ( vfs);
#endif

	/* Creates disk node */
	disk = gw_db_disk_new ( );
	gw_db_disk_set_name ( disk, g_strdup ( scan_disk_info_get_disk_name ( scan_disk)));
	gw_db_disk_set_fsname ( disk, g_strdup ( vfs_stats_get_name ( vfs)));
	gw_db_disk_set_path ( disk, g_strdup ( vfs_stats_get_dir ( vfs)));
	gw_db_disk_set_num ( disk, scan_disk_info_get_disk_num_archive ( scan_disk));
	if ( vfs_stats_get_type ( vfs) != NULL ) {
		gw_db_disk_set_fstype ( disk, g_strdup ( vfs_stats_get_type ( vfs)));
	}
	gw_db_disk_set_type ( disk, gw_helper_db_disk_get_db_type ( disk));
	gw_db_disk_set_volume ( disk, g_strdup ( vfs_stats_get_label ( vfs)));
	disk_size = vfs_stats_get_total_used_space ( vfs);
	gw_db_disk_set_full ( disk, disk_size);
	disk_size = vfs_stats_get_total_free_space ( vfs);
	gw_db_disk_set_free ( disk, disk_size);
	gw_db_disk_set_date ( disk, time ( &date));
	gw_db_disk_set_serial ( disk, g_strdup ( vfs_stats_get_serial_number ( vfs)));
	gw_db_disk_set_category ( disk, scan_disk_info_get_disk_category_ref ( scan_disk));
	gw_db_disk_set_description ( disk, NULL);

	plugin->gw_db_catalog_add_db_disk ( context, disk);

	if ( scan_disk_info_get_explore_tree_structure ( scan_disk) == TRUE ) {
		/* Gets current folder */
		if ( getcwd ( past_dir, 512) == NULL ) {
			error_msg = g_strconcat ( _( "Error : cannot get current folder."), "\n", strerror ( errno), NULL);
			scan_disk_info_set_error_msg ( scan_disk, error_msg);

			plugin->gw_db_catalog_remove_db_disk ( context, gw_db_disk_get_ref ( disk));
			gw_db_disk_free ( disk);

			return -1;
		}

		/* Builds the list of all the folders which must not be scanned.
		   These forbidden folders are included mount point of the current disk to scan. */
		forbidden = gw_get_drives_list ( forbidden);

		/* Removes the disk itself from the forbidden list. */
		if ( (self = g_list_find_custom ( forbidden, gw_db_disk_get_path ( disk), (GCompareFunc)strcmp)) != NULL ) {
			g_free ( self->data);
			forbidden = g_list_remove_link ( forbidden, self);
		}

		/* Removes all the mount points which are not included in the current disk to scan. */
		for ( i = 0; i < g_list_length ( forbidden); i++) {
			current = g_list_nth ( forbidden, i);
			/* Removes all mount points which are smaller or which start by the current disk to scan. */
			if ( strlen ( current->data) < strlen ( gw_db_disk_get_path ( disk)) || strncmp ( gw_db_disk_get_path ( disk), current->data, strlen ( gw_db_disk_get_path ( disk)))!=0 ) {
				i--;
				g_free ( current->data);
				forbidden = g_list_remove_link ( forbidden, current);
				current = NULL;
			}
		}

		/* Interrupt all signals */
		for ( i = 0; i < NSIG; i++) {
			if ( signal ( i, gw_cm_rollback_plugin_call) == SIG_ERR) {
#if GW_DEBUG_MODE
				gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "signum %d interruption is not ready", i);
#endif
			} else {
#if GW_DEBUG_MODE
				gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "signum %d interruption is ready", i);
#endif
			}
		}

		/* Adds the new disk */
		if ( gw_cm_add_dir ( scan_disk, vfs_stats_get_dir ( vfs), disk, NULL, &forbidden) == -1 ) {
			/* Remove the new disk */
			plugin->gw_db_catalog_remove_db_disk ( context, gw_db_disk_get_ref ( disk));
			gw_db_disk_free ( disk);

			/* Goes to the current application directory */
			chdir ( past_dir);

			/* Frees the forbidden list. */
			g_list_foreach ( forbidden, (GFunc)g_free, NULL);
			g_list_free ( forbidden);

			return -1;
		}

		/* Stop the signals interruption */
		for ( i = 0; i < NSIG; i++) {
			if ( signal ( i, SIG_DFL) == SIG_ERR) {
#if GW_DEBUG_MODE
				gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "signum %d interruption is not stopped", i);
#endif
			} else {
#if GW_DEBUG_MODE
				gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "signum %d interruption is stopped", i);
#endif
			}
		}

		/* Frees the forbidden list. */
		g_list_foreach ( forbidden, (GFunc)g_free, NULL);
		g_list_free ( forbidden);

		/* Bug to fix : why we did it?
		size = dir_info_get_size ( dir_info);
		disk_info_set_full ( disk_info, size);
		*/

		/* Goes to the begining folder */
		if ( chdir ( past_dir) == -1 ) {
			error_msg = g_strconcat ( _( "The disk has been added"), "\n", _( "Error : cannot go to working folder."), "\n", strerror ( errno), NULL);
			scan_disk_info_set_error_msg ( scan_disk, error_msg);
		}
	}

	/* BUG : fix me please */
	/* The total used space different from all files size. */
	if ( !scan_disk_info_get_stop ( scan_disk) ) {
		scan_disk_info_get_scan_disk_set_current_statment ( scan_disk)( scan_disk_info_get_statment_controler ( scan_disk), (long double)vfs_stats_get_total_used_space ( vfs));
	}

	/* Freezes the exploration tree */
	gtk_clist_freeze ( GTK_CLIST ( ctree));
	gtk_clist_freeze ( clist_info);

	gw_cm_load_disk_node ( ctree, parent, disk);
	gw_db_disk_free ( disk);

	gtk_ctree_sort_recursive ( ctree, parent);
	gtk_clist_thaw ( GTK_CLIST ( ctree));
	gtk_clist_thaw ( clist_info);

	/* Refreshes the exploration tree */
	gtk_ctree_collapse_recursive ( ctree, parent);
	gtk_ctree_expand ( ctree, parent);
	gtk_ctree_select ( ctree, parent);

#if GW_DEBUG_TIME
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Elapsed time to load the catalog: %u secs\n", time ( NULL) - begin);
#endif

	return 0;
}


gint gw_cm_add_dir ( struct scan_disk_info *scan_disk, gchar *directory, GWDBDisk *disk, GWDBFile *parent, GList **forbidden) {
	DIR *dir;
	struct dirent *f;
	struct stat f_info;
#if defined ( OS_LINUX) || defined ( OS_CYGWIN) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD)
	struct passwd *f_proprio;
	struct group *f_group;
#endif
	guint ret;
	GWDBFile *file = NULL;
	gchar *info_description = NULL;
#if defined ( OS_LINUX) || defined ( OS_CYGWIN) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD)
	gchar buf[1024];
#endif
	gchar /**name = NULL,*/ *error_msg = NULL;
	GWDBCategoryPK category = NULL;
	char *ext = NULL;
	func_get_file_descr_t func_get_file_descr = NULL;
	func_get_files_descr_t func_get_files_descr = NULL;
	func_get_parent_descr_t func_get_parent_descr = NULL;
	gchar*** files_descr_list = NULL;
	int i = 0;
#ifdef GW_DEBUG_MODE
	char *dir_name = NULL;
#endif
	gchar *tmp = NULL;
	GList *self = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = ((GWCatalogPlugin*)gw_db_context_get_plugin ( context));


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "scan the folder : %s", directory);
#endif

	if ( scan_disk_info_get_stop ( scan_disk) ) {
#if GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "stop scan disk.");
#endif

		error_msg = g_strdup ( _( "The disk hasn't been added\nAdding canceled by user"));
		scan_disk_info_set_error_msg ( scan_disk, error_msg);

		return -1;
	}

	category = scan_disk_info_get_disk_category_ref ( scan_disk);

	if ( chdir ( directory) == -1 ) {
		switch ( errno) {
			case EACCES :	/* Folder is locked */

							return 0;

			case EFAULT:	error_msg = g_strconcat ( _( "The disk hasn't been added\n"), g_strdup_printf ( _( "%s outside the process's allocated address space."), directory), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;

			case ENAMETOOLONG:error_msg = g_strconcat ( _( "The disk hasn't been added\n"), g_strdup_printf ( _( "A component of the following pathname exceeded %d characters, or an entire path name exceeded %d characters : %s."), NAME_MAX, PATH_MAX, directory), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;

			case ENOENT:	error_msg = g_strconcat ( _( "The disk hasn't been added\n"), g_strdup_printf ( _( "The following directory does not exist : %s."), directory), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;

			case ENOMEM:	error_msg = g_strconcat ( _( "The disk hasn't been added\n"), _( "Insufficient memory to complete the operation."), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;

			case ENOTDIR:	error_msg = g_strconcat ( _( "The disk hasn't been added\n"), g_strdup_printf ( _( "A component of the path prefix is not a directory : %s."), directory), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;

#if defined ( OS_LINUX) || defined ( OS_CYGWIN) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD)
			case ELOOP:		error_msg = g_strconcat ( _( "The disk hasn't been added\n"), g_strdup_printf ( _( "Too many symbolic links were encountered in resolving following path : %s."), directory), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;
#endif
			case EIO:		error_msg = g_strconcat ( _( "The disk hasn't been added\n"), g_strdup_printf ( _( "An I/O error occurred when change directory to : %s."), directory), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;

			default:		error_msg = g_strconcat ( _( "The disk hasn't been added\n"), _( "Unknown error"), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;
		}
	}

#ifdef GW_DEBUG_MODE
	dir_name = getcwd ( NULL, -1);
#endif

	/* Check if the current folder is a forbidden folder. In this case
	   must not scan this one. */
	tmp = (gchar*)g_malloc ( 1025 * sizeof ( gchar));
	tmp = getcwd ( tmp, 1024);
	if ( (self = g_list_find_custom ( *forbidden, tmp, (GCompareFunc)strcmp)) != NULL ) {
		/* If the current folder is forbidden, removesit from the forbidden list
		   because it will not be encountered at time. */
		g_free ( self->data);
		*forbidden = g_list_remove_link ( *forbidden, self);
		if (tmp!=NULL) g_free ( tmp);
		tmp = NULL;

		if ( chdir ( "..") == -1 ) {
			error_msg = g_strdup ( _( "The disk hasn't been added\nError : cannot go to parent folder."));
			scan_disk_info_set_error_msg ( scan_disk, error_msg);

			return -1;
		}

		return 0;
	}

	if (tmp!=NULL) g_free ( tmp);
	tmp = NULL;

	if ( ( dir = opendir ( ".")) == NULL ) {
		switch ( errno ) {
			case EACCES : /* Folder is locked */

							return 0;

			case EMFILE:	error_msg = g_strconcat ( _( "The disk hasn't been added\n"), _( "Too many file descriptors in use by process."), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

					return -1;

			case ENFILE:	error_msg = g_strconcat ( _( "The disk hasn't been added\n"), _( "Too many files are currently open in the system."), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;

			case ENOENT:	error_msg = g_strconcat ( _( "The disk hasn't been added\n"), (tmp = g_strdup_printf ( _( "The following directory does not exist, or name is an empty string : %s."), directory)), NULL);
							g_free ( tmp);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;

			case ENOMEM:	error_msg = g_strconcat ( _( "The disk hasn't been added\n"), _( "Insufficient memory to complete the operation."), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;

			case ENOTDIR:	error_msg = g_strconcat ( _( "The disk hasn't been added\n"), (tmp = g_strdup_printf ( _( "The following directory name is not a directory : %s."), directory)), NULL);
							g_free ( tmp);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;

			default:		error_msg = g_strconcat ( _( "The disk hasn't been added\n"), _( "Unknown error"), NULL);
							scan_disk_info_set_error_msg ( scan_disk, error_msg);

							return -1;
		}
	}


	while ( (f = readdir ( dir)) != NULL ) {
#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
		/* Skips this system folder. It's an unscanable folder. */
		if ( (parent == NULL) && ( (strcmp ( f->d_name, "System Volume Information") == 0) || (strcmp ( f->d_name, "RECYCLER") == 0) ) ) {
#ifdef GW_DEBUG_MODE
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "warning encounter %s%s%s", dir_name, G_DIR_SEPARATOR_S, file->d_name);
#endif
			continue;
		}
#endif

#if defined ( OS_WIN32)
		if ( (ret = stat ( f->d_name, &f_info)) == -1 ) {
#else
		if ( (ret = lstat ( f->d_name, &f_info)) == -1 ) {
#endif
			continue;
		} else {
#ifdef GW_DEBUG_MODE
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "add %s%s%s", dir_name, G_DIR_SEPARATOR_S, f->d_name);
#endif

			file = gw_db_file_new ( );

			/* File name */
			gw_db_file_set_name ( file, g_strdup ( f->d_name));

			/* File rights */
			gw_db_file_set_rights ( file, f_info.st_mode);

			switch ( S_IFMT & f_info.st_mode ) {
#if defined ( OS_LINUX) || defined ( OS_CYGWIN) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD)
				case S_IFLNK:	memset ( buf, '\0', 1024);
#ifdef GW_DEBUG_MODE
								gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "current link is %s/%s", directory, f->d_name);
#endif
								//FIXME With not use G_DIR_SEPARATOR?!?
								if ( readlink ( (tmp = g_strconcat ( directory, "/", f->d_name, NULL)), buf, 1023) != -1 ) {
									if ( tmp != NULL ) {
										g_free ( tmp);
										tmp = NULL;
									}

									gw_db_file_set_name ( file, g_strconcat ( f->d_name, " -> ", buf, NULL));
								}

								break;

#endif
				case S_IFDIR:	break;

				default:		break;
			}

#if defined ( OS_LINUX) || defined ( OS_CYGWIN) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD)
			/* Owner file */
			f_proprio = getpwuid ( f_info.st_uid);
			if ( f_proprio != NULL ) {
				gw_db_file_set_owner ( file, g_strdup ( f_proprio->pw_name));
			}
#endif

#if defined ( OS_LINUX) || defined ( OS_CYGWIN) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD)
			/* Owner group file */
			f_group = getgrgid ( f_info.st_gid);
			if ( f_group != NULL ) {
				gw_db_file_set_group ( file, g_strdup ( f_group->gr_name));
			}
#endif

			/* File size */
			gw_db_file_set_size ( file, f_info.st_size);

			if ( !scan_disk_info_get_stop ( scan_disk) ) {
				/* What it is the real size, f_info.st_size or f_info.st_blksize * f_info.st_blocks? */
				scan_disk_info_get_scan_disk_set_current_statment ( scan_disk)( scan_disk_info_get_statment_controler ( scan_disk), f_info.st_size);
			}

			/* File inode */
			gw_db_file_set_inode ( file, f_info.st_ino);

			/* Creation file date */
			gw_db_file_set_cdate ( file, f_info.st_ctime);

			/* Last file access date */
			gw_db_file_set_adate ( file, f_info.st_atime);

			/* Last file modification date */
			gw_db_file_set_mdate ( file, f_info.st_mtime);

			/* Category file */
			gw_db_file_set_category ( file, category);

			info_description = NULL;
			if ( gw_db_file_is_real_file ( file) && gw_db_file_get_size( file) > 0 && scan_disk_info_get_make_description ( scan_disk)) {
				if ( setjmp ( env) == 0 ) {
					ext = strrchr ( f->d_name, '.');

					if ( ext != NULL ) {
						ext++;

#ifdef GW_DEBUG_MODE
						gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "extension is %s", ext);
#endif

						gw_pm_get_file_descr_func ( ext, &func_get_file_descr);

						if ( func_get_file_descr != NULL) {
#ifdef GW_DEBUG_MODE
							gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "start plugin for file description");
#endif

							info_description = func_get_file_descr ( f->d_name, NULL);
						} else {
#ifdef GW_DEBUG_MODE
							gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "no plugin for file description");
#endif
						}
					}

					gw_pm_get_parent_descr_func ( f->d_name, &func_get_parent_descr);

					if ( func_get_parent_descr != NULL) {
#ifdef GW_DEBUG_MODE
						gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "start plugin for parent description");
#endif

						if ( (parent != NULL) && ((gw_db_file_get_description ( parent) == NULL) || (strlen ( gw_db_file_get_description ( parent)) == 0)) ) {
							gw_db_file_set_description ( parent, func_get_parent_descr ( f->d_name, NULL));
						}
					} else {
#ifdef GW_DEBUG_MODE
						gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "no plugin for parent description");
#endif
					}

					gw_pm_get_files_descr_func ( f->d_name, &func_get_files_descr);

					if ( func_get_files_descr != NULL) {
#ifdef GW_DEBUG_MODE
						gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "start plugin for files description");
#endif

						if ( files_descr_list == NULL ) {
							files_descr_list = func_get_files_descr ( f->d_name, NULL);
						} else {
#ifdef GW_DEBUG_MODE
							gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "warning!! There is already files description list");
#endif
						}
					} else {
#ifdef GW_DEBUG_MODE
						gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "no plugin for files description");
#endif
					}
				} else {
					/* An critical error occured, should exit GWhere proprely */
					tmp = (gchar*)g_malloc ( 1025 * sizeof ( gchar));
					memset ( tmp, '\0', 1025);
					tmp = getcwd ( tmp, 1024);
					if ( tmp == NULL) {
						tmp = g_strdup_printf ( "...%s%s", G_DIR_SEPARATOR_S, directory);
					}

					error_msg = g_strdup_printf ( _( "A critical error occured when extracting file information of %s%s%s.\nSave your catalog if it is possible, exit GWhere and report this trouble to the GWhere project team please."), tmp, G_DIR_SEPARATOR_S, f->d_name);
					if ( tmp != NULL) {
						g_free ( tmp);
						tmp = NULL;
					}

					scan_disk_info_set_error_msg ( scan_disk, error_msg);

					return -1;
				}
			}

			/* Description file */
			gw_db_file_set_description ( file, info_description);

			/* Adds the file to the catalog */
			if ( parent == NULL) {
				plugin->gw_db_disk_add_db_file ( context, gw_db_disk_get_ref ( disk), file);
			} else {
				plugin->gw_db_file_add_db_file ( context, gw_db_file_get_ref ( parent), file);
			}

			if ( gw_db_file_is_directory ( file) == TRUE ) {
				/* Case : is a folder */
				ret = 0;

				if ( gw_db_file_is_real_directory ( file) ) {
					if ( gw_cm_add_dir ( scan_disk, f->d_name, disk, file, forbidden) == -1 ) {
						gw_db_file_free ( file);
						return -1;
					}

					if ( parent != NULL) {
						/* Increase the parent folder size*/
						gw_db_file_set_size ( parent, gw_db_file_get_size ( file) + gw_db_file_get_size ( parent));
						plugin->gw_db_file_update ( context, file);
					} else {
					}
				} else {
				}
			} else {
				if ( parent != NULL) {
					/* Increase the parent folder size*/
					gw_db_file_set_size ( parent, gw_db_file_get_size ( file) + gw_db_file_get_size ( parent));
					plugin->gw_db_file_update ( context, file);
				} else {
				}
			}

			//TODO optimize it with recycling
			gw_db_file_free ( file);
		}
	}

	//TODO add this feature
	if ( files_descr_list != NULL ) {
#ifdef GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "set all files description...");
#endif

		for ( i = 0; files_descr_list[i] != NULL; i++) {
#ifdef GW_DEBUG_MODE
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "set file description number %d", i);
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "chearching file named %s", files_descr_list[i][0]);
#endif

			if ( parent != NULL ) {
				file = plugin->gw_db_file_get_db_file_by_name ( context, gw_db_file_get_ref ( parent), files_descr_list[i][0]);
			} else {
				file = plugin->gw_db_disk_get_db_file_by_name ( context, gw_db_disk_get_ref ( disk), files_descr_list[i][0]);
			}

			if ( file != NULL && (gw_db_file_get_description ( file) == NULL || strlen ( gw_db_file_get_description ( file)) == 0)) {
				gw_db_file_set_description ( file, files_descr_list[i][1]);
				plugin->gw_db_file_update ( context, file);
			} else {
				g_free ( files_descr_list[i][1]);
			}

			if ( files_descr_list[i][0] != NULL ) {
				/* TODO : to remove or not ? */
				g_free ( files_descr_list[i][0]);
			}

			/* TODO : to remove or not ? */
			g_free ( files_descr_list[i]);
		}

		g_free ( files_descr_list);
		files_descr_list = NULL;

#ifdef GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "all files description are setted");
#endif
	}

#ifdef GW_DEBUG_MODE
	free ( dir_name);
#endif

	if ( closedir ( dir) == -1 ) {
		error_msg = g_strdup ( _( "The disk hasn't been added\nError : cannot close current folder."));
		scan_disk_info_set_error_msg ( scan_disk, error_msg);

		return -1;
	}

	if ( chdir ( "..") == -1 ) {
		error_msg = g_strdup ( _( "The disk hasn't been added\nError : cannot go to parent folder."));
		scan_disk_info_set_error_msg ( scan_disk, error_msg);

		return -1;
	}

	return 0;
}


void gw_cm_catalog_copy_folder ( GWDBContext *ictx, GWDBContext *octx, GWDBFilePK ifolder, GWDBFilePK ofolder) {
	GWCatalogPlugin *op = NULL;
	GWCatalogPlugin *ip = NULL;
	GWDBFile **files = NULL;
	GWDBFilePK ifilePK = NULL;
	GWDBFilePK ofilePK = NULL;
	gint i = 0;


	ip = gw_db_context_get_plugin ( ictx);
	op = gw_db_context_get_plugin ( octx);

	if ( (files = ip->gw_db_file_get_db_files ( ictx, ifolder)) != NULL) {
		for ( i = 0; files[i]!=NULL; i++) {
			ifilePK = gw_db_file_get_ref ( files[i]);
			ofilePK = op->gw_db_file_add_db_file ( octx, ofolder, files[i]);
			gw_cm_catalog_copy_folder ( ictx, octx, ifilePK, ofilePK);
			gw_db_file_free ( files[i]);
		}

		g_free ( files);
	}
}
