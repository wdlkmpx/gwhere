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


#include "../gwsupport.h"
#include "gwnotebookcatalogcallback.h"

#include <string.h> /* strcmp strlen */

#include "tools/gwtools.h"
#include "res/gwres.h"
#include "data/gwdata.h"

#include "gwstatusbar.h"
#include "gwstatusbarcallback.h"
#include "gwnotebookcatalog.h"
#include "gwnotebooksearch.h"
#include "gwnotebookmanagmentcallback.h"
#include "gwmenupopup.h"

#include "../gwapplicationmanager.h"
#include "../gwguimanager.h"
#include "../gwcatalogmanager.h"
#include "../gwhelper.h"


gint gw_catalog_compare_disk_int ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2) {
	GWDBDisk *disk1 = NULL, *disk2 = NULL;
	int nb1 = -1, nb2 = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) ) {
		disk1 = (GWDBDisk*)(((GtkCListRow *)ptr1)->data);
		disk2 = (GWDBDisk*)(((GtkCListRow *)ptr2)->data);

		if ( (disk1!=NULL) && (disk2!=NULL) ) {
			switch ( clist->sort_column) {
				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT:	nb1 = gw_db_disk_get_num ( disk1);
													nb2 = gw_db_disk_get_num ( disk2);
													break;
			}
		}
	}

	return nb1 - nb2;
}


gint gw_catalog_compare_disk_gulong ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2) {
	GWDBDisk *disk1 = NULL, *disk2 = NULL;
	gulong nb1 = 0, nb2 = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) ) {
		disk1 = (GWDBDisk*)(((GtkCListRow *)ptr1)->data);
		disk2 = (GWDBDisk*)(((GtkCListRow *)ptr2)->data);

		if ( (disk1!=NULL) && (disk2!=NULL) ) {
			switch ( clist->sort_column) {
				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT:	nb1 = gw_db_disk_get_date ( disk1);
												nb2 = gw_db_disk_get_date ( disk2);
												break;
			}
		}
	}

	return nb1 - nb2;
}


gint gw_catalog_compare_disk_guint64 ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2) {
	GWDBDisk *disk1 = NULL, *disk2 = NULL;
	guint64 nb1 = -1, nb2 = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) ) {
		disk1 = (GWDBDisk*)(((GtkCListRow *)ptr1)->data);
		disk2 = (GWDBDisk*)(((GtkCListRow *)ptr2)->data);

		if ( (disk1!=NULL) && (disk2!=NULL) ) {
			switch ( clist->sort_column) {
				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT:	nb1 = gw_db_disk_get_full ( disk1);
													nb2 = gw_db_disk_get_full ( disk2);
													break;

				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT:		nb1 = gw_db_disk_get_free ( disk1);
													nb2 = gw_db_disk_get_free ( disk2);
													break;
			}
		}
	}

	return nb1 - nb2;
}


gint gw_catalog_compare_disk_str ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2) {
	GWDBDisk *disk1 = NULL, *disk2 = NULL;
	gchar *str1 = NULL, *str2 = NULL;
	gint result = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) ) {
		disk1 = (GWDBDisk*)(((GtkCListRow *)ptr1)->data);
		disk2 = (GWDBDisk*)(((GtkCListRow *)ptr2)->data);

		if ( (disk1!=NULL) && (disk2!=NULL) ) {
			switch ( clist->sort_column) {
				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT:		str1 = gw_db_disk_get_name ( disk1);
													str2 = gw_db_disk_get_name ( disk2);
													break;

				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT:		str1 = gw_db_disk_get_fsname ( disk1);
													str2 = gw_db_disk_get_fsname ( disk2);
													break;

				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT:		str1 = gw_db_disk_get_path ( disk1);
													str2 = gw_db_disk_get_path ( disk2);
													break;

				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT:		str1 = gw_db_disk_get_fstype ( disk1);
													str2 = gw_db_disk_get_fstype ( disk2);
													break;

				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT:		str1 = gw_db_disk_get_volume ( disk1);
													str2 = gw_db_disk_get_volume ( disk2);
													break;

				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT:		str1 = gw_db_disk_get_serial ( disk1);
													str2 = gw_db_disk_get_serial ( disk2);
													break;

//FIXME add support category name sort
//				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT:	str1 = gw_db_disk_get_category_name ( disk1);
//													str2 = gw_db_disk_get_category_name ( disk2);
//													break;

				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT:	str1 = gw_db_disk_get_description ( disk1);
													str2 = gw_db_disk_get_description ( disk2);
													break;
			}

			if ( (str1!=NULL) && (str2!=NULL) ) {
				if ( gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE) == 1 ) {
					result = strcmp ( str1, str2);
				} else {
					result = strcasecmp ( str1, str2);
				}
			}
		}
	}

	return result;
}


gint gw_catalog_compare_file_glong ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2) {
	GWDBFile *file1 = NULL, *file2 = NULL;
	glong nb1 = -1, nb2 = -1;
	gboolean isfolder1 = FALSE, isfolder2 = FALSE;
	gchar *str_name1 = NULL, *str_name2 = NULL;
	gint result = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) ) {
		file1 = (GWDBFile*)(((GtkCListRow *)ptr1)->data);
		file2 = (GWDBFile*)(((GtkCListRow *)ptr2)->data);

		if ( (file1!=NULL) && (file2!=NULL) ) {
			str_name1 = gw_db_file_get_name ( file1);
			str_name2 = gw_db_file_get_name ( file2);
			isfolder1 = gw_db_file_is_real_directory ( file1);
			isfolder2 = gw_db_file_is_real_directory ( file2);

			switch ( clist->sort_column) {
				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT:	nb1 = gw_db_file_get_inode ( file1);
												nb2 = gw_db_file_get_inode ( file2);
												break;
			}

			if ( (str_name1!=NULL) && (str_name2!=NULL) ) {
				if ( (strlen ( str_name1) == 2) && (strncmp ( str_name1, "..", 2) == 0) ) {
					result = (clist->sort_type==GTK_SORT_ASCENDING?-2:2);
				} else {
					if ( (strlen ( str_name2) == 2) && (strncmp ( str_name2, "..", 2) == 0) ) {
						result = (clist->sort_type==GTK_SORT_ASCENDING?2:-2);
					} else {
						result = (((gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER)==0)||(isfolder1==isfolder2))?(nb1-nb2):(isfolder2-isfolder1));
					}
				}
			}
		}
	}

	return result;
}


gint gw_catalog_compare_file_gulong ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2) {
	GWDBFile *file1 = NULL, *file2 = NULL;
	gulong nb1 = 0, nb2 = 0;
	gboolean isfolder1 = FALSE, isfolder2 = FALSE;
	gchar *str_name1 = NULL, *str_name2 = NULL;
	gint result = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) ) {
		file1 = (GWDBFile*)(((GtkCListRow *)ptr1)->data);
		file2 = (GWDBFile*)(((GtkCListRow *)ptr2)->data);

		if ( (file1!=NULL) && (file2!=NULL) ) {
			str_name1 = gw_db_file_get_name ( file1);
			str_name2 = gw_db_file_get_name ( file2);
			isfolder1 = gw_db_file_is_real_directory ( file1);
			isfolder2 = gw_db_file_is_real_directory ( file2);

			switch ( clist->sort_column) {
				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT:	nb1 = gw_db_file_get_cdate ( file1);
												nb2 = gw_db_file_get_cdate ( file2);
												break;

				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT:	nb1 = gw_db_file_get_adate ( file1);
												nb2 = gw_db_file_get_adate ( file2);
												break;

				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT:	nb1 = gw_db_file_get_mdate ( file1);
												nb2 = gw_db_file_get_mdate ( file2);
												break;
			}

			if ( (str_name1!=NULL) && (str_name2!=NULL) ) {
				if ( (strlen ( str_name1) == 2) && (strncmp ( str_name1, "..", 2) == 0) ) {
					result = (clist->sort_type==GTK_SORT_ASCENDING?-1000:1000);
				} else {
					if ( (strlen ( str_name2) == 2) && (strncmp ( str_name2, "..", 2) == 0) ) {
						result = (clist->sort_type==GTK_SORT_ASCENDING?1000:-1000);
					} else {
						result = (((gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER)==0)||(isfolder1==isfolder2))?(nb1-nb2):(isfolder2-isfolder1));
					}
				}
			}
		}
	}

	return result;
}


gint gw_catalog_compare_file_guint64 ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2) {
	GWDBFile *file1 = NULL, *file2 = NULL;
	guint64 nb1 = 0, nb2 = 0;
	gboolean isfolder1 = FALSE, isfolder2 = FALSE;
	gchar *str_name1 = NULL, *str_name2 = NULL;
	gint result = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) ) {
		file1 = (GWDBFile*)(((GtkCListRow *)ptr1)->data);
		file2 = (GWDBFile*)(((GtkCListRow *)ptr2)->data);

		if ( (file1!=NULL) && (file2!=NULL) ) {
			str_name1 = gw_db_file_get_name ( file1);
			str_name2 = gw_db_file_get_name ( file2);
			isfolder1 = gw_db_file_is_real_directory ( file1);
			isfolder2 = gw_db_file_is_real_directory ( file2);

			switch ( clist->sort_column) {
				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT:	nb1 = gw_db_file_get_size ( file1);
												nb2 = gw_db_file_get_size ( file2);
												break;
			}

			if ( (str_name1!=NULL) && (str_name2!=NULL) ) {
				if ( (strlen ( str_name1) == 2) && (strncmp ( str_name1, "..", 2) == 0) ) {
					result = (clist->sort_type==GTK_SORT_ASCENDING?-2:2);
				} else {
					if ( (strlen ( str_name2) == 2) && (strncmp ( str_name2, "..", 2) == 0) ) {
						result = (clist->sort_type==GTK_SORT_ASCENDING?2:-2);
					} else {
						result = (((gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER)==0)||(isfolder1==isfolder2))?(nb1-nb2):(isfolder2-isfolder1));
					}
				}
			}
		}
	}

	return result;
}


gint gw_catalog_compare_file_str ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2) {
	GWDBFile *file1 = NULL, *file2 = NULL;
	gchar *str_name1 = NULL, *str_name2 = NULL;
	gchar *str1 = NULL, *str2 = NULL;
	gboolean isfolder1 = FALSE, isfolder2 = FALSE;
	gint result = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) ) {
		file1 = (GWDBFile*)(((GtkCListRow *)ptr1)->data);
		file2 = (GWDBFile*)(((GtkCListRow *)ptr2)->data);

		if ( (file1!=NULL) && (file2!=NULL) ) {
			str_name1 = gw_db_file_get_name ( file1);
			str_name2 = gw_db_file_get_name ( file2);
			isfolder1 = gw_db_file_is_real_directory ( file1);
			isfolder2 = gw_db_file_is_real_directory ( file2);

			switch ( clist->sort_column) {
				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT:		str1 = str_name1;
													str2 = str_name2;
													break;

				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT:		str1 = gw_db_file_get_rights_to_gchar ( file1);
													str2 = gw_db_file_get_rights_to_gchar ( file2);
													break;

				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT:		str1 = gw_db_file_get_owner ( file1);
													str2 = gw_db_file_get_owner ( file2);
													break;

				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT:		str1 = gw_db_file_get_group ( file1);
													str2 = gw_db_file_get_group ( file2);
													break;

//FIXME add support category name sort
//				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT:	str1 = gw_db_file_get_category_name ( file1);
//													str2 = gw_db_file_get_category_name ( file2);
//													break;

				case GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT:	str1 = gw_db_file_get_description ( file1);
													str2 = gw_db_file_get_description ( file2);
													break;
			}

			if ( (str_name1!=NULL) && (str_name2!=NULL) && (str1!=NULL) && (str2!=NULL) ) {
				if ( (strlen ( str_name1) == 2) && (strncmp ( str_name1, "..", 2) == 0) ) {
					result = (clist->sort_type==GTK_SORT_ASCENDING?-2:2);
				} else {
					if ( (strlen ( str_name2) == 2) && (strncmp ( str_name2, "..", 2) == 0) ) {
						result = (clist->sort_type==GTK_SORT_ASCENDING?2:-2);
					} else {
						if ( gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE) == 1 ) {
							result = (((gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER)==0)||(isfolder1==isfolder2))?strcmp ( str1, str2):(isfolder2-isfolder1));
						} else {
							result = (((gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER)==0)||(isfolder1==isfolder2))?strcasecmp ( str1, str2):(isfolder2-isfolder1));
						}
					}
				}
			}

			if ( clist->sort_column == GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT ) {
				if ( str1 != NULL ) {
					g_free ( str1);
				}

				if ( str2 != NULL ) {
					g_free ( str2);
				}
			}
		}
	}

	return result;
}


gint gw_notebook_catalog_set_column_sort ( GtkCList *clist, gint column) {
	GtkCTree *ctree = NULL;
	GtkCTreeNode *selection = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (clist!=NULL) && (column>-1) ) {
		/* Gets the selected item in the tree. */
		if ( (ctree = gw_gui_manager_main_interface_get_tree ( )) != NULL ) {
			if ( (GTK_CLIST ( ctree)->selection != NULL) && ((selection = GTK_CTREE_NODE ( GTK_CLIST ( ctree)->selection->data)) != NULL) ) {
				if ( GTK_CTREE_ROW ( selection)->parent == NULL ) {
					/* User is in the catalog : this is a list of disks. */
					switch ( column) {
						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_str);
																							break;

						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_str);
																							break;

						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_str);
																							break;

						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT:	gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_int);
																							break;

						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_str);
																							break;

						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_str);
																							break;

						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT:	gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_guint64);
																							break;

						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_guint64);
																							break;

						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_gulong);
																							break;

						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_str);
																							break;

						//FIXME compare category name
						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT:	gtk_clist_set_compare_func ( clist, NULL);
																							break;

						case GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT:	gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_disk_str);
																							break;

						default:															gtk_clist_set_compare_func ( clist, NULL);
																							break;
					}
				} else {
					/* User is in a disk or a folder : this is a list of files. */
					switch ( column) {
						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_file_str);
																							break;

						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_file_str);
																							break;

						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_file_str);
																							break;

						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_file_str);
																							break;

						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_file_guint64);
																							break;

						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_file_glong);
																							break;

						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_file_gulong);
																							break;

						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_file_gulong);
																							break;

						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_file_gulong);
																							break;

						//FIXME compare category name
						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT:	gtk_clist_set_compare_func ( clist, NULL);
																							break;

						case GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT:	gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_file_str);
																							break;

						default:															gtk_clist_set_compare_func ( clist, NULL);
																							break;
					}
				}
			}
		}

		result = 0;
	}

	return result;
}


gboolean gw_notebook_catalog_column_sort ( GtkCList *clist, gint column, gpointer data) {
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : column=%d data=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, column, GPOINTER_TO_INT ( data));
#endif

	if ( clist != NULL ) {
		if ( GPOINTER_TO_INT ( data) != -1 ) {
			if ( column == clist->sort_column ) {
				if ( clist->sort_type == GTK_SORT_ASCENDING ) {
					clist->sort_type = GTK_SORT_DESCENDING;
				} else {
					clist->sort_type = GTK_SORT_ASCENDING;
				}
			} else {
				gtk_clist_set_sort_column ( clist, column);
			}
		}

		gw_notebook_catalog_set_column_sort ( clist, column);

		if ( GPOINTER_TO_INT ( data) != -1 ) {
			gtk_clist_sort ( clist);
		}

		result = TRUE;
	}

	return result;
}


gboolean gw_notebook_catalog_clist_button_press_event ( GtkWidget *w, GdkEventButton *event) {
	GtkCList *clist_info = NULL;
	GtkCTreeNode *selection = NULL, *node = NULL, *child = NULL;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBDisk *disk = NULL;
	GWDBFile *file = NULL;
	GWDBFile **files = NULL;
	GdkEventButton *bev = event;
	gint row,col;
	GtkWindow *window = NULL;
	GtkCTree *ctree = NULL;
	GtkCTreeNode *root = NULL;
	gchar *tmp_date = NULL;
	gint i = 0, nb = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Gets all needs references. */
	window = gw_gui_manager_main_interface_get_main_window ( );
	ctree = gw_gui_manager_main_interface_get_tree ( );
	root = gw_gui_manager_main_interface_get_tree_root ( );
	clist_info = gw_notebook_catalog_get_clist_explorer ( window);

	/* Checks if a catalog is opened. */
	if ( root != NULL && context != NULL && (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
		/* Ignores clicks on scrollbars. */
		if ( event->window == GTK_CLIST ( clist_info)->clist_window ){
			/* Gets the selected item in the tree. */
			selection = GTK_CTREE_NODE ( GTK_CLIST ( ctree)->selection->data);

			/* Gets the selected item in the list. */
			gtk_clist_get_selection_info ( clist_info, event->x, event->y, &row, &col);

			/* Stops the signal during the process. */
			/* If uncomment this line, the item will not be selected.
			gtk_signal_emit_stop_by_name ( GTK_OBJECT ( clist_info), "button_press_event");
			*/

			/* Checks the type of click */
			switch ( event->type) {
				case GDK_BUTTON_PRESS:	/* Single click */

										/* Checks clicked bouton. */
										switch ( event->button) {
											case 1:	/* Left bouton */

													if ( GTK_CTREE_ROW ( selection)->parent == NULL ) {
														/* User is in the catalog : he clicked on a disk. */

														/* Gets informations attached to the line. */
														if ( (disk = (GWDBDisk*)gtk_clist_get_row_data ( clist_info, row)) != NULL ) {
															/* User clicked on a disk. */

															/* Updates the status bar. */
															gw_status_bar_put_msg_disk ( window,
																			gw_db_disk_get_name ( disk),
																			gw_db_disk_get_fstype ( disk),
																			gw_db_disk_get_capacity ( disk),
																			gw_db_disk_get_free ( disk),
																			(long double)gw_db_disk_get_full ( disk),
																			0);

															/* Must return FALSE to show the selected item with GTK+ 2.x (with bleu background) */
															return FALSE;
														} else {
															/* If user clicked on a empty space. */

															/* Must return FALSE to show the selected item with GTK+ 2.x (with bleu background) */
															//FIXME why??
															return TRUE;
														}
													} else {
														/* If user clicked on a folder or a file. */

														/* Gets informations attached to the line. */
														if ( (file = (GWDBFile*)gtk_clist_get_row_data ( GTK_CLIST ( clist_info), row)) == NULL ) {
															/* User clicked on a empty space. */

															return TRUE;
														} else {
															/* If user clicked on an item. */
															if ( gw_db_file_is_real_directory ( file) ) {
																/* If it's a folder. */
																if ( (strlen ( gw_db_file_get_name ( file)) == 2) && (strncmp ( gw_db_file_get_name ( file), "..", 2) == 0) ) {
																	/* If it's the parent folder. */

																	/* Updates the status bar. */
																	tmp_date = gw_helper_db_file_get_cdate_to_str ( file);
																	gw_status_bar_put_msg_file ( window,
																								gw_db_file_get_name ( file),
																								gw_db_file_get_size ( file),
																								tmp_date,
																								1);
																	g_free ( tmp_date);

																	/* Must return FALSE to show the selected item with GTK+ 2.x (with bleu background) */
																	return FALSE;
																} else {
																	/* If it's an unspecified folder. */

																	/* Searches in the tree where is the selected folder. */
																	node = gw_notebook_catalog_ctree_node_get_child ( GTK_CTREE_NODE ( GTK_CLIST ( ctree)->selection->data), gw_db_file_get_name ( file));
																	file = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( ctree, node));
//																	file = gtk_ctree_node_get_row_data ( ctree, node);

																	/* Counts the number of files (to depth 1) in the given folder (except "." and ".." folders). */
																	if ( (files = plugin->gw_db_file_get_db_files ( context, gw_db_file_get_ref ( file))) != NULL ) {
																		for ( i = 0; files[i] != NULL; i++) {
																			nb++;
																			if ( strlen ( gw_db_file_get_name ( files[i]))==1 && strcmp ( gw_db_file_get_name ( files[i]), ".")==0 ) {nb--;}
																			if ( strlen ( gw_db_file_get_name ( files[i]))==2 && strcmp ( gw_db_file_get_name ( files[i]), "..")==0 ) {nb--;}
																			gw_db_file_free(files[i]);files[i]=NULL;
																		}
																		g_free(files);files=NULL;
																	} else {
																	}


																	/* Updates the status bar. */
																	gw_status_bar_put_msg_dir ( window,
																								gw_db_file_get_name ( file),
																								gw_db_file_get_size ( file),
																								nb,
																								gw_notebook_catalog_ctree_node_get_num_children ( node),
																								0);
																	gw_db_file_free ( file);

																	/* Must return FALSE to show the selected item with GTK+ 2.x (with bleu background) */
																	return FALSE;
																}
															} else {
																/* If it's a file. */

																/* Updates a the status bar. */
																tmp_date = gw_helper_db_file_get_cdate_to_str ( file);
																gw_status_bar_put_msg_file ( window,
																							gw_db_file_get_name ( file),
																							gw_db_file_get_size ( file),
																							tmp_date,
																							1);
																g_free ( tmp_date);

																return FALSE;
															}
														}
													}


													break;

											case 2:	/* Middle bouton */
													break;

											case 3:	/* Right bouton */

													/* If it's a right click : displays the popup menu. */
													if ( GTK_CTREE_ROW ( selection)->parent == NULL ) {
														/* User is in the catalog : he clicked on a disk. */

														/* Gets informations attached to the line. */
														if ( (disk = (GWDBDisk*)gtk_clist_get_row_data ( clist_info, row)) == NULL ) {
															/* User clicked on empty space. */

															return TRUE;
														} else {
															/* Else if user clicked on a disk. */

															/* Searches in the tree where is the selected disk. */
															node = gw_notebook_catalog_ctree_node_get_child ( GTK_CTREE_NODE ( GTK_CLIST( ctree)->selection->data), gw_db_disk_get_name ( disk));

															/* Displays the popup menu. */
															gtk_menu_popup ( gw_menu_popup_disk_create_and_show ( node, window), NULL, NULL, NULL, NULL, bev->button, bev->time);

															return TRUE;
														}
													} else {
														/* User clicked on a folder or a file. */

														/* Gets informations attached to the line. */
														if ( (file = (GWDBFile*)gtk_clist_get_row_data ( GTK_CLIST ( clist_info), row)) == NULL ) {
															/* If user clicked on empty space. */

															return TRUE;
														} else {
															/* Else if user clicked on an item. */

															if ( gw_db_file_is_directory ( file) ) {
																/* If it's a folder. */
																if ( (strlen ( gw_db_file_get_name ( file)) == 2) && (strncmp ( gw_db_file_get_name ( file), "..", 2) == 0) ) {
																	/* If it's the parent folder. */

																	return TRUE;
																} else {
																	/* Else if it's an unspecified folder. */

																	/* Searches in the tree where is the selected folder. */
																	node = gw_notebook_catalog_ctree_node_get_child ( GTK_CTREE_NODE ( GTK_CLIST ( ctree)->selection->data), gw_db_file_get_name ( file));

																	/* Displays the popup menu. */
																	gtk_menu_popup ( gw_menu_popup_dir_create_and_show ( node, window), NULL, NULL, NULL, NULL, bev->button, bev->time);

																	return TRUE;
																}
															} else {
																/* If it's a file which is selected. */

																/* Displays the popup menu. */
																gtk_menu_popup ( gw_menu_popup_file_create_and_show ( GINT_TO_POINTER ( row), window), NULL, NULL, NULL, NULL, bev->button, bev->time);

																return TRUE;
															}
														}
													}

													break;

											default:break;
										}

										break;

				case GDK_2BUTTON_PRESS:	/* Double click*/

										/* Checks clicked bouton. */
										switch ( event->button) {
											case 1:	/* Left bouton */

													/* To prevent that double click generates a signal in excess. */
													gdk_event_get ( );

													/* Checks the type of selected item. */
													if ( GTK_CTREE_ROW ( selection)->parent == NULL ) {
														/* User is in the catalog : he clicked on a disk. */

														/* Gets informations attached to the line. */
														if ( (disk = (GWDBDisk*)gtk_clist_get_row_data ( clist_info, row)) != NULL ) {
															/* Really clicked on a disk. */
															if ( !GTK_CTREE_ROW ( selection)->expanded ) {
																gtk_ctree_expand ( ctree, selection);
															}

															/* Searches in the tree where is the selected disk. */
															child = GTK_CTREE_ROW ( selection)->children;
															while ( child != NULL ) {
																if ( gw_db_disk_get_ref ( disk) == gtk_ctree_node_get_row_data ( ctree, child)) {
//																if ( strcmp ( gw_db_disk_get_name ( tmp_disk), gw_db_disk_get_name ( disk)) == 0 ) {
																	gtk_ctree_select ( ctree, child);

																	return TRUE;
																}

																child = GTK_CTREE_NODE_NEXT ( child);

																return TRUE;
															}
														} else {
															/* Clicked in empty space. */
															return TRUE;
														}
													} else {
														/* Else if user clicked on a folder or a file. */

														/* Gets informations attached to the line. */
														if ( (file = (GWDBFile*)gtk_clist_get_row_data ( clist_info, row)) != NULL ) {
															/* Really clicked on an item. */

															if ( gw_db_file_is_directory ( file) ) {
																/* If it's a folder. */
																if ( (strlen ( gw_db_file_get_name ( file)) == 2) && (strncmp ( gw_db_file_get_name ( file), "..", 2) == 0) ) {
																	/* If it's the parent folder. */
																	child = GTK_CTREE_ROW ( selection)->parent;

																	if ( child != root ) {
																		gtk_ctree_select ( ctree, child);
																	}

																	return TRUE;
																} else {
																	/* Else if it's an unspecified folder. */
																	if ( !GTK_CTREE_ROW ( selection)->expanded ) {
																		gtk_ctree_expand ( ctree, selection);
																	}

																	/* Searches in the tree where is the selected folder. */
																	child = GTK_CTREE_ROW ( selection)->children;
																	while ( child != NULL ) {
																		if ( gw_db_file_get_ref ( file) == gtk_ctree_node_get_row_data ( ctree, child)) {
//																		if ( strcmp ( gw_db_file_get_name ( gtk_ctree_node_get_row_data ( ctree, child)), gw_db_file_get_name ( file)) == 0 ) {
																			gtk_ctree_select ( ctree, child);

																			return TRUE;
																		}

																		child = GTK_CTREE_NODE_NEXT ( child);
																	}

																	return TRUE;
																}
															} else {
																/* If it's a file. */
																tmp_date = gw_helper_db_file_get_cdate_to_str ( file);
																gw_status_bar_put_msg_file ( window,
																							gw_db_file_get_name ( file),
																							gw_db_file_get_size ( file),
																							tmp_date,
																							1);
																g_free ( tmp_date);

																return TRUE;
															}
														} else {
															/* If user clicked in empty space. */

															return TRUE;
														}
													}

													break;

											case 2:	/* Middle bouton */
													break;

											case 3:	/* Right bouton */

													break;

											default:break;
										}

										break;

				default:				break;
			}
		} else {
		}
	} else {
	}

	return FALSE;
}


gint gw_notebook_catalog_clist_column_resized ( GtkCList *clist, gint column, gint width, gpointer user_data) {
	GtkCTreeNode *root = gw_gui_manager_main_interface_get_tree_root ( );
	GtkCTree *ctree = NULL;
	GtkCTreeNode *selection = NULL;
	gint result = -1;
	gint autoresize = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (root!=NULL) && (clist!=NULL) && (column>-1) ) {
		if ( (autoresize = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE)) == -1 ) {
			autoresize = GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE_DEFAULT;
		}

		/* Saves the column width only if the autoresize mode is desactivated. */
		if ( autoresize == FALSE ) {
			/* Gets the selected item in the tree. */
			if ( (ctree = gw_gui_manager_main_interface_get_tree ( )) != NULL ) {
				if ( (GTK_CLIST ( ctree)->selection != NULL) && ((selection = GTK_CTREE_NODE ( GTK_CLIST ( ctree)->selection->data)) != NULL) ) {
					if ( GTK_CTREE_ROW ( selection)->parent == NULL ) {
						/* User is in the catalog : this is a list of disks. */
						switch ( column) {
							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT:	gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT:	gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT:	gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT:	gw_am_set_settings ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SIZE, g_strdup_printf ( "%d", width));
																								break;

							default:															break;
						}

						result = 0;
					} else {
						/* User is in a disk or a folder : this is a list of files. */
						switch ( column) {
							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT:	gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SIZE, g_strdup_printf ( "%d", width));
																								break;

							case GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT:	gw_am_set_settings ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SIZE, g_strdup_printf ( "%d", width));
																								break;

							default:															break;
						}

						result = 0;
					}
				} else {}
			} else {}
		}
	}

	return result;
}


gboolean gw_notebook_catalog_ctree_button_press_event ( GtkWidget *w, GdkEventButton *event) {
	GtkCList *clist;
	GtkCTreeNode *node;
	gint row, col;
	GdkEventButton *bev = event;
	GtkCTree *ctree = NULL;
	GtkWindow *window = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	ctree = gw_gui_manager_main_interface_get_tree ( );
	window = gw_gui_manager_main_interface_get_main_window ( );
	clist = GTK_CLIST ( w);

	/* Ignores clicks on scrollbars. */
	if ( event->window == GTK_CLIST ( clist)->clist_window ) {
		gtk_clist_get_selection_info ( GTK_CLIST ( clist), event->x, event->y, &row, &col);
		node = GTK_CTREE_NODE ( g_list_nth ( clist->row_list, row));

		/* Stops the signal during the process, except for single left click in order expand or
		   collapse node with click on the cross node. */
		if ( !((event->type == GDK_BUTTON_PRESS) && (event->button == 1)) ) {
			gtk_signal_emit_stop_by_name ( GTK_OBJECT ( ctree), "button_press_event");
		}

		switch ( event->type) {
			case GDK_BUTTON_PRESS:	/* Single click. */
						switch ( event->button) {
							case 1:		if ( node != NULL ) {
										/* If user didn't click in the empty space : select the row. */
										gtk_ctree_select ( ctree, node);
									}

									return FALSE;

									break;

							case 2:		break;

							case 3:		/* Displays the popup menu. */
									if ( node == NULL ) {
										/* If user clicked in the empty space. */
										gtk_menu_popup ( gw_menu_popup_create_and_show ( window), NULL, NULL, NULL, NULL, bev->button, bev->time);

										return TRUE;
									} else {
										/* Selects the item for more user visibility. */
										gtk_ctree_select ( ctree, node);
										gw_gui_manager_main_interface_refresh ( );

										if ( GTK_CTREE_ROW ( node)->parent == NULL ) {
											/* If user clicked on a catalog. */
											gtk_menu_popup ( gw_menu_popup_catalog_create_and_show ( node, window), NULL, NULL, NULL, NULL, bev->button, bev->time);

											return TRUE;
										} else if ( GTK_CTREE_ROW ( GTK_CTREE_ROW ( node)->parent)->parent == NULL ) {
											/* If user clicked on a disk. */
											gtk_menu_popup ( gw_menu_popup_disk_create_and_show ( node, window), NULL, NULL, NULL, NULL, bev->button, bev->time);

											return TRUE;
										} else {
											/* If user clicked on a folder. */
											gtk_menu_popup ( gw_menu_popup_dir_create_and_show ( node, window), NULL, NULL, NULL, NULL, bev->button, bev->time);

											return TRUE;
										}
									}

									return TRUE;

									break;

							default:	break;
						}

						break;

			case GDK_2BUTTON_PRESS:	/* Double click. */
						switch ( event->button) {
							case 1:		/* Prevents from double click to generate too many signals. */
									gdk_event_get ( );

									/* Checks if user didn't click in the empty space. */
									if ( node != NULL ) {
										/* Opens or closes the node. */
										if ( GTK_CTREE_ROW ( node)->expanded ) {
											gtk_ctree_collapse ( ctree, node);
										} else {
											gtk_ctree_expand ( ctree, node);
										}

										gtk_ctree_select ( ctree, node);
									} else {}

									return /*TRUE*/FALSE;

									break;

							case 2:		break;
							case 3: 	break;
							default:	break;
						}

						break;

			default:		/* Unknown click. */
						break;
		}
	} else {
		return TRUE;
	}

	return FALSE;
}


gboolean gw_notebook_catalog_ctree_select_row ( GtkCTree *ctree, GtkCTreeNode *node, gint column, gpointer g) {
        GtkCList *clist_info = NULL;
        gchar *info[12];
        gint i, row, compt = 0, compt_file = 0;
        double size = 0;
        GtkWindow *window = NULL;
        GtkCTreeNode *root = NULL;
        gchar *text_utf8 = NULL;
        gchar *tmp_date = NULL;
        GWCatalogPlugin *plugin = NULL;
        GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBDisk **disks = NULL;
	GWDBDisk *disk = NULL;
	GWDBFile **files = NULL;
	GWDBFile *file = NULL;
	gint j = 0;
	gboolean result = FALSE;
	GWDBCategory *category = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
        g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	window = gw_gui_manager_main_interface_get_main_window ( );
	root = gw_gui_manager_main_interface_get_tree_root ( );
	clist_info = gw_notebook_catalog_get_clist_explorer ( window);

	/* Checks if the catalog is loaded and selected node exists */
	if ( root != NULL && node != NULL) {
		/* Stop the signal during the process. */
		gtk_signal_emit_stop_by_name ( GTK_OBJECT ( ctree), "tree_select_row");

		/* Freezes informations table */
		gtk_clist_freeze ( clist_info);
		gtk_clist_clear ( clist_info);

plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
		/* Updates list */
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : updates list\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		/* Checks the type of selected node */
		if ( GTK_CTREE_ROW ( node)->parent == NULL ) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : catalog selected\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			/* If a catalog is selected, must to display disk list */
			gw_notebook_catalog_clist_explorer_set_column_title_disk ( );

			if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL) {
				for ( i = 0; disks[i] != NULL; i++) {
					category = plugin->gw_db_catalog_get_db_category ( context, gw_db_disk_get_category ( disks[i]));
					compt++;
					size = size + gw_db_disk_get_full ( disks[i]);
					g_strdup_to_gtk_text ( gw_db_disk_get_name ( disks[i]), info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT]);
					g_strdup_to_gtk_text ( gw_db_disk_get_fsname ( disks[i]), info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT]);
					g_strdup_to_gtk_text ( gw_db_disk_get_path ( disks[i]), info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT]);
					text_utf8 = g_strdup_printf ( "%d", gw_db_disk_get_num ( disks[i]));
					g_strdup_to_gtk_text ( text_utf8, info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT]);
					g_free ( text_utf8);
					g_strdup_to_gtk_text ( gw_db_disk_get_fstype ( disks[i]), info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT]);
					g_strdup_to_gtk_text ( gw_db_disk_get_volume ( disks[i]), info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT]);
					text_utf8 = gw_ui64_byte_to_str_format ( gw_db_disk_get_capacity ( disks[i]));
					g_strdup_to_gtk_text ( text_utf8, info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT]);
					g_free ( text_utf8);
					text_utf8 = gw_ui64_byte_to_str_format ( gw_db_disk_get_free ( disks[i]));
					g_strdup_to_gtk_text ( text_utf8, info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT]);
					g_free ( text_utf8);
					tmp_date = gw_helper_db_disk_get_date_to_str ( disks[i]);
					g_strdup_to_gtk_text ( tmp_date, info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT]);
					g_free ( tmp_date);
					g_strdup_to_gtk_text ( gw_db_disk_get_serial ( disks[i]), info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT]);
					g_strdup_to_gtk_text ( gw_db_category_get_name ( category), info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT]);
					g_strdup_to_gtk_text ( gw_db_disk_get_description ( disks[i]), info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT]);
					gw_str_replace_char ( info[GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT], '\n', ' ');
					row = gtk_clist_append ( clist_info, info);

					gtk_clist_set_row_data_full ( clist_info, row, disks[i], (GtkDestroyNotify)gw_db_disk_free);
					gtk_clist_set_pixtext ( clist_info, row, 0, info[0], 5, gw_helper_db_disk_get_pixmap ( disks[i]), gw_helper_db_disk_get_bitmap ( disks[i]));

					/* Frees memory used by info. */
					for ( j = 0; j < 11; j++) {
						g_free ( info[j]);
					}
					gw_db_category_free ( category);
				}

				g_free ( disks);
			}

			/* Displays in the status bar the informations about the selected item. */
			gw_status_bar_put_msg_catalog ( window, ctree, root, compt, size);

			result = TRUE;
		} else {
			if ( GTK_CTREE_ROW ( node)->parent == root ) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : disk selected\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

				/* If a disk is selected, must to display folders and files list */
				gw_notebook_catalog_clist_explorer_set_column_title_file ( );

				if ( (disk = plugin->gw_db_catalog_get_db_disk ( context, gtk_ctree_node_get_row_data ( ctree, node))) != NULL ) {
					if ( (files = plugin->gw_db_disk_get_db_files ( context, gw_db_disk_get_ref ( disk))) != NULL ) {
					} else {}
				} else {}
			} else {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : folder selected\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

				/* If a folder is selected, must to display folders and files list */
				gw_notebook_catalog_clist_explorer_set_column_title_file ( );

				if ( (file = plugin->gw_db_catalog_get_db_file ( context, gtk_ctree_node_get_row_data ( ctree, node))) != NULL ) {
					if ( (files = plugin->gw_db_file_get_db_files ( context, gw_db_file_get_ref ( file))) != NULL ) {
					} else {}
				} else {}
			}

			if ( files != NULL ) {
				for ( i = 0; files[i] != NULL; i++) {
					/* Don't display the "." folder */
					if ( strcmp ( gw_db_file_get_name ( files[i]), ".") != 0) {
						category = plugin->gw_db_catalog_get_db_category ( context, gw_db_file_get_category ( files[i]));
						compt++;
						size = size + gw_db_file_get_size ( files[i]);
						g_strdup_to_gtk_text ( gw_db_file_get_name ( files[i]), info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT]);
						tmp_date = gw_db_file_get_rights_to_gchar ( files[i]);
						g_strdup_to_gtk_text ( tmp_date, info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT]);
						g_free ( tmp_date);
						if ( gw_db_file_get_owner ( files[i])!=NULL && strlen ( gw_db_file_get_owner ( files[i])) != 0 ) {
							g_strdup_to_gtk_text ( gw_db_file_get_owner ( files[i]), info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT]);
						} else {
							g_strdup_to_gtk_text ( _( "unknown owner"), info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT]);
						}
						if ( gw_db_file_get_group ( files[i])!=NULL && strlen ( gw_db_file_get_group ( files[i])) != 0 ) {
							g_strdup_to_gtk_text ( gw_db_file_get_group ( files[i]), info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT]);
						} else {
							g_strdup_to_gtk_text ( _( "unknown group"), info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT]);
						}
						text_utf8 = gw_ui64_byte_to_str_format ( gw_db_file_get_size ( files[i]));
						g_strdup_to_gtk_text ( text_utf8, info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT]);
						g_free ( text_utf8);
						text_utf8 = g_strdup_printf ( "%ld", gw_db_file_get_inode ( files[i]));
						g_strdup_to_gtk_text ( text_utf8, info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT]);
						g_free ( text_utf8);
						tmp_date = gw_helper_db_file_get_cdate_to_str ( files[i]);
						g_strdup_to_gtk_text ( tmp_date, info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT]);
						g_free ( tmp_date);
						tmp_date = gw_helper_db_file_get_mdate_to_str ( files[i]);
						g_strdup_to_gtk_text ( tmp_date, info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT]);
						g_free ( tmp_date);
						tmp_date = gw_helper_db_file_get_adate_to_str ( files[i]);
						g_strdup_to_gtk_text ( tmp_date, info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT]);
						g_free ( tmp_date);
						g_strdup_to_gtk_text ( gw_db_category_get_name ( category), info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT]);
						g_strdup_to_gtk_text ( gw_db_file_get_description ( files[i]), info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT]);
						gw_str_replace_char ( info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT], '\n', ' ');
						g_strdup_to_gtk_text ( NULL, info[11]);

						if ( strcmp ( gw_db_file_get_name ( files[i]), "..") == 0) {
							compt_file++;
							row = gtk_clist_prepend ( clist_info, info);
							gtk_clist_set_row_data_full ( clist_info, row, files[i], (GtkDestroyNotify)gw_db_file_free);
							gtk_clist_set_pixtext ( clist_info, row, 0, info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT], 5, PixParentFolder, MskParentFolder);
						} else {
							row = gtk_clist_append ( clist_info, info);
							gtk_clist_set_row_data_full ( clist_info, row, files[i], (GtkDestroyNotify)gw_db_file_free);
							if ( gw_db_file_is_directory ( files[i])) {
								//TODO test if it is a locked folder...
								//gtk_clist_set_pixtext ( clist_info, row, 0, info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT], 5, PixLockedFolder, MskLockedFolder);
								gtk_clist_set_pixtext ( clist_info, row, 0, info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT], 5, PixFolder, MskFolder);
							} else {
								compt_file++;
								gtk_clist_set_pixtext ( clist_info, row, 0, info[GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT], 5, PixFile, MskFile);
							}
						}

						/* Frees memory used by info. */
						for ( j = 0; j < 11; j++) {
							g_free ( info[j]);
						}
						gw_db_category_free ( category);
					} else {
						gw_db_file_free ( files[i]);
					}
				}

				g_free ( files);
			} else {
				//TODO what should we do??
			}

			if ( GTK_CTREE_ROW ( node)->parent == root ) {
				/* Displays in the status bar the informations about the selected item. */
				gw_status_bar_put_msg_disk ( window,
					gw_db_disk_get_name ( disk),
					gw_db_disk_get_fstype ( disk),
					gw_db_disk_get_capacity ( disk),
					gw_db_disk_get_free ( disk),
					size,
					compt - 1);
				gw_db_disk_free ( disk);
			} else {
				/* Displays in the status bar the informations about the selected item. */
				gw_status_bar_put_msg_dir ( window,
					gw_db_file_get_name ( file),
					size,
					compt_file - 1,
					compt - compt_file,
					compt - 1);

				gw_db_file_free ( file);
			}
		}

		/* Updates the list */
		gtk_clist_sort ( clist_info);
		gtk_clist_thaw ( clist_info);

		result = TRUE;
	} else {}

	return result;
}
