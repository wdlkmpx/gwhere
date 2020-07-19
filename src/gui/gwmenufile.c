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
#include "gwmenufile.h"

#include <gdk/gdkkeysyms.h>

#include "gwmenufilecallback.h"
#include "gwreferences.h"


/*! @define	GW_REF_MENU_BAR_FILE_MENU_HEADER	The file menu header reference */
#define GW_REF_MENU_BAR_FILE_MENU_HEADER "gw_menu_bar_file_menu_header"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_NEW	The file menu -> new reference */
#define GW_REF_MENU_BAR_FILE_MENU_NEW "gw_menu_bar_file_menu_new"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_OPEN	The file menu -> open reference */
#define GW_REF_MENU_BAR_FILE_MENU_OPEN "gw_menu_bar_file_menu_open"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_SAVE	The file menu -> save reference */
#define GW_REF_MENU_BAR_FILE_MENU_SAVE "gw_menu_bar_file_menu_save"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_SAVEAS	The file menu -> save as reference */
#define GW_REF_MENU_BAR_FILE_MENU_SAVEAS "gw_menu_bar_file_menu_saveas"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_CLOSE	The file menu -> close reference */
#define GW_REF_MENU_BAR_FILE_MENU_CLOSE "gw_menu_bar_file_menu_close"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_SEPARATOR	The file menu -> separator reference */
#define GW_REF_MENU_BAR_FILE_MENU_SEPARATOR "gw_menu_bar_file_menu_separator"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_IMPORT	The file menu -> import reference */
#define GW_REF_MENU_BAR_FILE_MENU_IMPORT "gw_menu_bar_file_menu_import"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_EXPORT	The file menu -> export reference */
#define GW_REF_MENU_BAR_FILE_MENU_EXPORT "gw_menu_bar_file_menu_export"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_PROPERTIES	The file menu -> properties reference */
#define GW_REF_MENU_BAR_FILE_MENU_PROPERTIES "gw_menu_bar_file_menu_properties"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_RECENTS_FILES	The file menu -> recents files reference */
#define GW_REF_MENU_BAR_FILE_MENU_RECENTS_FILES "gw_menu_bar_file_menu_recents_files"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_EXIT	The file menu -> exit reference */
#define GW_REF_MENU_BAR_FILE_MENU_EXIT "gw_menu_bar_file_menu_exit"
/*! @define	GW_REF_MENU_BAR_FILE_MENU	The file menu reference */
#define GW_REF_MENU_BAR_FILE_MENU "gw_menu_bar_file_menu"


GtkWidget * gw_menu_file_create ( GtkWindow *w, GtkAccelGroup *ag, GtkWidget *parent) {
	GtkWidget *gw_menu_file_header = NULL;
	GtkWidget *menu_file = NULL;
	GtkWidget *gw_menu_file_new = NULL;
	GtkWidget *gw_menu_file_open = NULL;
	GtkWidget *gw_menu_file_save = NULL;
	GtkWidget *gw_menu_file_saveas = NULL;
	GtkWidget *gw_menu_file_close = NULL;
	GtkWidget *gw_menu_file_separator = NULL;
	GtkWidget *gw_menu_file_import = NULL;
	GtkWidget *gw_menu_file_import_items = NULL;
	GtkWidget *gw_menu_file_export = NULL;
	GtkWidget *gw_menu_file_export_items = NULL;
	GtkWidget *gw_menu_file_properties = NULL;
	GtkWidget *gw_menu_file_recents_files = NULL;
	GtkWidget *gw_menu_file_recents_files_items = NULL;
	GtkWidget *gw_menu_file_exit = NULL;
	GtkAccelGroup *gw_menu_file_ag = NULL;
	guint tmp_key;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Menu file header */
	gw_menu_file_header = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "_File"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_header)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_header, "activate-item", ag, tmp_key, GDK_MOD1_MASK, 0);
#endif
	gtk_widget_ref ( gw_menu_file_header);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_HEADER, gw_menu_file_header, (GtkDestroyNotify) gtk_widget_unref);

	menu_file = gtk_menu_new ( );
	gtk_widget_ref ( menu_file);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU, menu_file, (GtkDestroyNotify) gtk_widget_unref);
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_file_header), menu_file);
#if defined ( HAVE_GTK12)
	gw_menu_file_ag = gtk_menu_ensure_uline_accel_group ( GTK_MENU ( menu_file));
#else
	gw_menu_file_ag = gtk_accel_group_new ( );
#endif

	/* Menu file -> new */
	gw_menu_file_new = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "_New"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_new)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_new, "activate-item", gw_menu_file_ag, tmp_key, 0, 0);
#endif
	gtk_widget_ref ( gw_menu_file_new);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_NEW, gw_menu_file_new, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_new);
	gtk_widget_add_accelerator ( gw_menu_file_new, "activate", ag, GDK_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_signal_connect ( GTK_OBJECT ( gw_menu_file_new), "activate", GTK_SIGNAL_FUNC ( gw_menu_file_new_click), w);

	/* Menu file -> open */
	gw_menu_file_open = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "_Open"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_open)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_open, "activate-item", gw_menu_file_ag, tmp_key, 0, 0);
#endif
	gtk_widget_ref ( gw_menu_file_open);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_OPEN, gw_menu_file_open, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_open);
	gtk_widget_add_accelerator ( gw_menu_file_open, "activate", ag, GDK_o, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_signal_connect ( GTK_OBJECT ( gw_menu_file_open), "activate", GTK_SIGNAL_FUNC ( gw_menu_file_open_click), w);

	/* Menu file -> save */
	gw_menu_file_save = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "_Save"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_save)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_save, "activate-item", gw_menu_file_ag, tmp_key, 0, 0);
#endif
	gtk_widget_ref ( gw_menu_file_save);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SAVE, gw_menu_file_save, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_save);
	gtk_widget_add_accelerator ( gw_menu_file_save, "activate", ag, GDK_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_signal_connect ( GTK_OBJECT ( gw_menu_file_save), "activate", GTK_SIGNAL_FUNC ( gw_menu_file_save_click), w);

	/* Menu file -> save as */
	gw_menu_file_saveas = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "Sav_e as"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_saveas)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_saveas, "activate-item", gw_menu_file_ag, tmp_key, 0, 0);
#endif
	gtk_widget_ref ( gw_menu_file_saveas);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SAVEAS, gw_menu_file_saveas, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_saveas);
	gtk_widget_add_accelerator ( gw_menu_file_saveas, "activate", ag, GDK_e, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_signal_connect ( GTK_OBJECT ( gw_menu_file_saveas), "activate", GTK_SIGNAL_FUNC ( gw_menu_file_saveas_click), w);

	/* Menu file -> close */
	gw_menu_file_close = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "C_lose"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_close)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_close, "activate-item", gw_menu_file_ag, tmp_key, 0, 0);
#endif
	gtk_widget_ref ( gw_menu_file_close);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_CLOSE, gw_menu_file_close, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_close);
	gtk_widget_add_accelerator ( gw_menu_file_close, "activate", ag, GDK_f, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_signal_connect ( GTK_OBJECT ( gw_menu_file_close), "activate",GTK_SIGNAL_FUNC ( gw_menu_file_close_click), w);

	/* Menu file -> separator */
	gw_menu_file_separator = gtk_menu_item_new ( );
	gtk_widget_ref ( gw_menu_file_separator);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SEPARATOR, gw_menu_file_separator, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_separator);
	gtk_widget_set_sensitive ( gw_menu_file_separator, FALSE);

	/* Menu file -> import catalog */
	gw_menu_file_import = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "Import"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_import)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_import, "activate-item", gw_menu_file_ag, tmp_key, 0, 0);
#endif
	gtk_widget_ref ( gw_menu_file_import);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_IMPORT, gw_menu_file_import, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_import);
//	gtk_widget_add_accelerator ( gw_menu_file_import, "activate", ag, GDK_m, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gw_menu_file_import_items = gtk_menu_new ( );
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_file_import), gw_menu_file_import_items);

	/* Menu file -> export catalog */
	gw_menu_file_export = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "Export"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_export)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_export, "activate-item", gw_menu_file_ag, tmp_key, 0, 0);
#endif
	gtk_widget_ref ( gw_menu_file_export);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_EXPORT, gw_menu_file_export, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_export);
//	gtk_widget_add_accelerator ( gw_menu_file_export, "activate", ag, GDK_x, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gw_menu_file_export_items = gtk_menu_new ( );
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_file_export), gw_menu_file_export_items);

	/* Menu file -> separator */
	gw_menu_file_separator = gtk_menu_item_new ( );
	gtk_widget_ref ( gw_menu_file_separator);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SEPARATOR, gw_menu_file_separator, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_separator);
	gtk_widget_set_sensitive ( gw_menu_file_separator, FALSE);

	/* Menu file -> properties */
	gw_menu_file_properties = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "_Properties"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_properties)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_properties, "activate-item", gw_menu_file_ag, tmp_key, 0, 0);
#endif
	gtk_widget_ref ( gw_menu_file_properties);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_PROPERTIES, gw_menu_file_properties, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_properties);
	gtk_widget_add_accelerator ( gw_menu_file_properties, "activate", ag, GDK_p, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_signal_connect ( GTK_OBJECT ( gw_menu_file_properties), "activate", GTK_SIGNAL_FUNC ( gw_menu_file_properties_click), w);

	/* Menu file -> separator */
	gw_menu_file_separator = gtk_menu_item_new ( );
	gtk_widget_ref ( gw_menu_file_separator);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SEPARATOR, gw_menu_file_separator, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_separator);
	gtk_widget_set_sensitive ( gw_menu_file_separator, FALSE);

	/* Menu file -> recents files */
	gw_menu_file_recents_files = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "_Recents files"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_recents_files)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_recents_files, "activate-item", gw_menu_file_ag, tmp_key, 0, 0);
#endif
	gtk_widget_ref ( gw_menu_file_recents_files);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_RECENTS_FILES, gw_menu_file_recents_files, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_recents_files);
	gtk_widget_add_accelerator ( gw_menu_file_recents_files, "activate", ag, GDK_r, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gw_menu_file_recents_files_items = gtk_menu_new ( );
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_file_recents_files), gw_menu_file_recents_files_items);

	/* Menu file -> separator */
	gw_menu_file_separator = gtk_menu_item_new ( );
	gtk_widget_ref ( gw_menu_file_separator);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SEPARATOR, gw_menu_file_separator, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_separator);
	gtk_widget_set_sensitive ( gw_menu_file_separator, FALSE);

	/* Menu file -> exit */
	gw_menu_file_exit = gtk_menu_item_new_with_label ( "");
	g_strdup_to_gtk_text ( _( "E_xit"), text_utf8);
	tmp_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( gw_menu_file_exit)->child), text_utf8);
	g_free ( text_utf8);
#if defined ( HAVE_GTK12)
	gtk_widget_add_accelerator ( gw_menu_file_exit, "activate-item", gw_menu_file_ag, tmp_key, 0, 0);
#endif
	gtk_widget_ref ( gw_menu_file_exit);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_EXIT, gw_menu_file_exit, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_exit);
	gtk_widget_add_accelerator ( gw_menu_file_exit, "activate", ag, GDK_x, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_signal_connect ( GTK_OBJECT ( gw_menu_file_exit), "activate", GTK_SIGNAL_FUNC ( gw_menu_file_exit_click), w);

	return gw_menu_file_header;
}


gboolean gw_menu_file_set_import ( GtkWindow *w, gchar **plugins) {
	gboolean result = FALSE;
	GtkMenuItem *import_menu = NULL;
	GtkWidget *menu_item_import = NULL;
	GtkWidget *import_submenu = NULL;
	guint i = 0;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (w != NULL) && (plugins != NULL) ) {
		import_menu = GTK_MENU_ITEM ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_IMPORT));

		if ( import_menu != NULL ) {
			gtk_menu_item_remove_submenu ( import_menu);

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			import_submenu = gtk_menu_new ( );
			gtk_menu_item_set_submenu ( import_menu, import_submenu);

			for ( i = 0; plugins[i] != NULL; i++) {
#ifdef GW_DEBUG_GUI_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item at %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item => %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, plugins[i]);
#endif

				g_strdup_to_gtk_text ( plugins[i], text_utf8);
				menu_item_import = gtk_menu_item_new_with_label ( text_utf8);
				g_free ( text_utf8);
				gtk_container_add ( GTK_CONTAINER ( import_submenu), menu_item_import);

				gtk_signal_connect ( GTK_OBJECT ( menu_item_import), "activate", GTK_SIGNAL_FUNC ( gw_menu_file_import_item_click), plugins[i]);
			}

			gtk_widget_show_all ( GTK_WIDGET ( import_menu));

			result = TRUE;
		}

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : import plugins are added.\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return result;
}


gboolean gw_menu_file_set_export ( GtkWindow *w, gchar **plugins) {
	gboolean result = FALSE;
	GtkMenuItem *import_menu = NULL;
	GtkWidget *menu_item_import = NULL;
	GtkWidget *import_submenu = NULL;
	guint i = 0;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (w != NULL) && (plugins != NULL) ) {
		import_menu = GTK_MENU_ITEM ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_EXPORT));

		if ( import_menu != NULL ) {
			gtk_menu_item_remove_submenu ( import_menu);

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			import_submenu = gtk_menu_new ( );
			gtk_menu_item_set_submenu ( import_menu, import_submenu);

			for ( i = 0; plugins[i] != NULL; i++) {
#ifdef GW_DEBUG_GUI_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item at %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item => %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, plugins[i]);
#endif

				g_strdup_to_gtk_text ( plugins[i], text_utf8);
				menu_item_import = gtk_menu_item_new_with_label ( text_utf8);
				g_free ( text_utf8);
				gtk_container_add ( GTK_CONTAINER ( import_submenu), menu_item_import);

				/* Warning use a gint value instead of a gpointer value!! */
				gtk_signal_connect ( GTK_OBJECT ( menu_item_import), "activate", GTK_SIGNAL_FUNC ( gw_menu_file_export_item_click), /*GUINT_TO_POINTER ( i)*/g_strdup ( plugins[i]));
			}

			gtk_widget_show_all ( GTK_WIDGET ( import_menu));

			result = TRUE;
		}

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : export plugins are added.\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return result;
}


gboolean gw_menu_file_set_recents_files ( GtkWindow *w, gchar **files) {
	gboolean result = FALSE;
	GtkMenuItem *recents_files_menu = NULL;
	GtkWidget *menu_item_recents_files = NULL;
	GtkWidget *recents_files_submenu = NULL;
	guint i = 0;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (w != NULL) && (files != NULL) ) {
		recents_files_menu = GTK_MENU_ITEM ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_RECENTS_FILES));

		if ( recents_files_menu != NULL ) {
			gtk_menu_item_remove_submenu ( recents_files_menu);

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			recents_files_submenu = gtk_menu_new ( );
			gtk_menu_item_set_submenu ( recents_files_menu, recents_files_submenu);

			for ( i = 0; files[i] != NULL; i++) {
#ifdef GW_DEBUG_GUI_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item at %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item => %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, files[i]);
#endif

				g_strdup_to_gtk_text ( files[i], text_utf8);
				menu_item_recents_files = gtk_menu_item_new_with_label ( text_utf8);
				g_free ( text_utf8);
				gtk_container_add ( GTK_CONTAINER ( recents_files_submenu), menu_item_recents_files);

				/* Warning use a gint value instead of a gpointer value!! */
				gtk_signal_connect ( GTK_OBJECT ( menu_item_recents_files), "activate", GTK_SIGNAL_FUNC ( gw_menu_file_recents_files_item_click), GUINT_TO_POINTER ( i));
			}

			gtk_widget_show_all ( GTK_WIDGET ( recents_files_menu));

			result = TRUE;
		}

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : recents opened catalog files are added.\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return result;
}
