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
#include "gwnotebookmanagment.h"

#include <string.h> /* strncmp */
#include <sys/types.h>

#include "tools/gwtools.h"
#include "data/gwdata.h"

#include "gwcomboboxcategories.h"
#include "gwnotebookmanagmentcallback.h"

#include "../gwapplicationmanager.h"
#include "../gwguimanager.h"
#include "../gwsupermount.h"


/*! @define	GW_REF_NOTEBOOK_MANAGMENT_TABBED_PANE_LABEL	The pabbed pane title */
#define GW_REF_NOTEBOOK_MANAGMENT_TABBED_PANE_LABEL "gw_ref_gw_notebook_managment_tabbed_pane_label"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_ENTRY_DEVICE_NAME	The entry for device name*/
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_ENTRY_DEVICE_NAME "ref_gw_gui_gw_notebook_managment_entry_device_name"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_ENTRY_DEVICE_NUMBER_ARCHIVE	The entry for number archive */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_ENTRY_DEVICE_NUMBER_ARCHIVE "ref_gw_gui_gw_notebook_managment_entry_device_number_archive"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_ENTRY_DEVICE_CATEGORY	The combo box entry for category */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_ENTRY_DEVICE_CATEGORY "ref_gw_gui_gw_notebook_managment_combo_box_entry_device_category"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_DISPLAY_INFO	The check box for option display information */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_DISPLAY_INFO "ref_gw_gui_gw_notebook_managment_check_display_info"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_AUTO_MOUNT	The check box for option automount */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_AUTO_MOUNT "ref_gw_gui_gw_notebook_managment_check_auto_mount"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EJECT	The check box for option auto eject */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EJECT "ref_gw_gui_gw_notebook_managment_check_eject"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_CATEGORY_RECURSIVE	The check box for option set category recursively */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_CATEGORY_RECURSIVE "ref_gw_gui_gw_notebook_managment_check_category_recursive"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EXPLORE_TREE_STRUCTURE	The check box for option explore tree structure */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EXPLORE_TREE_STRUCTURE "ref_gw_gui_gw_notebook_managment_check_explore_tree_structure"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EXPLORE_ARCHIVE	The check box for option explore archive files */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EXPLORE_ARCHIVE "ref_gw_gui_gw_notebook_managment_check_explore_archive"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_MAKE_DESCRIPTION	The check box for option automake description */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_MAKE_DESCRIPTION "ref_gw_gui_gw_notebook_managment_check_make_description"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_USE_DISK_LABEL	The check box for option use disk label as name */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_USE_DISK_LABEL "ref_gw_gui_gw_notebook_managment_check_use_disk_label"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_USE_PATTERN	The check box for option use pattern to generate disk name */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_USE_PATTERN "ref_gw_gui_gw_notebook_managment_check_use_pattern"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_DEVICE	The combo box for device selection */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_DEVICE "ref_gw_gui_gw_notebook_managment_combo_box_device"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_CATEGORY	The combo box for category selection */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_CATEGORY "ref_gw_gui_gw_notebook_managment_combo_box_category"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_INFO	The label of  device information */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_INFO "ref_gw_gui_gw_notebook_managment_label_display_info_info"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_TYPE	The label of device type */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_TYPE "ref_gw_gui_gw_notebook_managment_label_display_info_type"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_MOUNTED	The label of device mount status */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_MOUNTED "ref_gw_gui_gw_notebook_managment_label_display_info_mounted"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_VOLUME	The label of device volume name */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_VOLUME "ref_gw_gui_gw_notebook_managment_label_display_info_volume"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_SERIAL_NUMBER	The label of device serial number */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_SERIAL_NUMBER "ref_gw_gui_gw_notebook_managment_label_display_info_serial_number"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_CAPACITY	The label of device capacity */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_CAPACITY "ref_gw_gui_gw_notebook_managment_label_display_info_capacity"
/*! @define	REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_FREE_SPACE	the label of device free space */
#define REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_FREE_SPACE "ref_gw_gui_gw_notebook_managment_label_display_info_free_space"


GtkWidget * gw_notebook_managment_create ( GtkWindow * window)
{
	GtkWidget *vb_tabbed_pane = NULL;
	GtkWidget *hb_control;
	GtkWidget *frm_new_disk_control;
	GtkWidget *vb_new_disk_control;
	GtkWidget *hb_disk_selection;
	GtkWidget *lbl_disk_selection;
	GtkWidget *cmb_disk_selection;
	GtkWidget *hseparator;
	GtkWidget *hb_number_archive;
	GtkWidget *lbl_number_archive;
	GtkWidget *entry_number_archive;
	GtkWidget *hb_disk_name;
	GtkWidget *lbl_disk_name;
	GtkWidget *entry_disk_name;
	GtkBox *cmb_categories;
	GtkWidget *hb_device_file;
	GtkWidget *lbl_device_file;
	GtkWidget *hb_device_type;
	GtkWidget *lbl_device_type;
#ifdef HAVE_MOUNT_SYSTEM
	GtkWidget *hb_device_ismounted;
	GtkWidget *lbl_device_ismounted;
#endif
	GtkWidget *hb_device_volume_name;
	GtkWidget *lbl_device_volume_name;
	GtkWidget *hb_device_serial_number;
	GtkWidget *lbl_device_serial_number;
	GtkWidget *hb_device_capacity;
	GtkWidget *lbl_device_capacity;
	GtkWidget *hb_device_free_space;
	GtkWidget *lbl_device_free_space;
	GtkWidget *frm_options;
	GtkWidget *vb_options;
	GtkWidget *chk_display_device_info;
#ifdef HAVE_MOUNT_SYSTEM
	GtkWidget *chk_automount_device;
#endif
	GtkWidget *chk_explore_tree_structure;
	GtkWidget *chk_explore_archive_files;
	GtkWidget *chk_auto_eject_device;
	GtkWidget *chk_category_recursively;
	GtkWidget *chk_auto_make_description;
	GtkWidget *chk_use_disk_label;
	GtkWidget *chk_use_pattern;
	GtkWidget *bt_start_device_scan;
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( window != NULL )
	{
		tree = gw_gui_manager_main_interface_get_tree ( );
		root = gw_gui_manager_main_interface_get_tree_root ( );

		/* Vertical box of the managment tabbed pane. */
		vb_tabbed_pane = gtk_vbox_new ( FALSE, 0);

		/* Horizontal box for controls (text field, checks buttons, ...). */
		hb_control = gtk_hbox_new ( TRUE, 0);
		gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), hb_control, TRUE, TRUE, 0);

		/* Frame of new disk control */
		frm_new_disk_control = gtk_frame_new (_( "New disk"));
		gtk_container_set_border_width ( GTK_CONTAINER ( frm_new_disk_control), 10);
		gtk_box_pack_start ( GTK_BOX ( hb_control), frm_new_disk_control, FALSE, TRUE, 0);
	
		/* Vertical box for new disk control */
		vb_new_disk_control = gtk_vbox_new ( FALSE, 0);
		gtk_container_add ( GTK_CONTAINER ( frm_new_disk_control), vb_new_disk_control);
	
		/* Horizontal box for media selection */
		hb_disk_selection = gtk_hbox_new ( FALSE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb_disk_selection), 10);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hb_disk_selection, TRUE, TRUE, 0);
		gtk_widget_set_tooltip_text (hb_disk_selection,
		                             _("Select the media that will be added as disk to your catalog."));
	
		/* Label for media selection */
		lbl_disk_selection = gtk_label_new (_( "Select media : "));
		gtk_box_pack_start ( GTK_BOX ( hb_disk_selection), lbl_disk_selection, FALSE, FALSE, 0);
	
		/* ComboBox to select media */
		cmb_disk_selection = gtk_combo_box_text_new_with_entry ( );
		g_object_ref ( cmb_disk_selection);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_DEVICE, cmb_disk_selection, (GDestroyNotify) g_object_unref);
		gtk_editable_set_editable (GTK_EDITABLE (gtk_bin_get_child (GTK_BIN (cmb_disk_selection))), FALSE);

		/* Loads the list of devices */
		gw_notebook_managment_load_device_list ( window);

		/* To fix : when user click on combo's button, the first item of the list is selected
		   automaticaly. This emits the "changed" event!!
		*/
		g_signal_connect_after (cmb_disk_selection, "changed", G_CALLBACK ( gw_notebook_managment_select_device), GTK_WINDOW (window));
		gtk_box_pack_start ( GTK_BOX ( hb_disk_selection), cmb_disk_selection, TRUE, TRUE, 0);
	
		/* Horizontal separator */
		hseparator = gtk_hseparator_new ( );
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hseparator, TRUE, TRUE, 0);
	
		/* Horizontal box for number archive */
		hb_number_archive = gtk_hbox_new ( FALSE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb_number_archive), 10);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hb_number_archive, TRUE, TRUE, 0);
		gtk_widget_set_tooltip_text (hb_number_archive,
		                             _( "Enter the number of the new disk. This number can help you with the history of your catalog."));
	
		/* Label for number archive */
		lbl_number_archive = gtk_label_new (_( "Archive N# : "));
		gtk_box_pack_start ( GTK_BOX ( hb_number_archive), lbl_number_archive, FALSE, FALSE, 0);
	
		/* Entry for number archive */
		entry_number_archive = gtk_entry_new ( );
		g_object_ref ( entry_number_archive);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_ENTRY_DEVICE_NUMBER_ARCHIVE, entry_number_archive, (GDestroyNotify) g_object_unref);
		gtk_box_pack_start ( GTK_BOX ( hb_number_archive), entry_number_archive, TRUE, TRUE, 0);
	
		/* Horizontal box for disk name */
		hb_disk_name = gtk_hbox_new ( FALSE, 0);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hb_disk_name, TRUE, TRUE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb_disk_name), 10);
		gtk_widget_set_tooltip_text (hb_disk_name,
		                             _( "Enter the name of the new disk. This name will be appear in your catalog."));
	
		/* Label for disk name */
		lbl_disk_name = gtk_label_new (_( "Name : "));
		gtk_box_pack_start ( GTK_BOX ( hb_disk_name), lbl_disk_name, FALSE, FALSE, 0);
	
		/* Entry for disk name */
		entry_disk_name = gtk_entry_new ( );
		g_object_ref ( entry_disk_name);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_ENTRY_DEVICE_NAME, entry_disk_name, (GDestroyNotify) g_object_unref);
		gtk_box_pack_start ( GTK_BOX ( hb_disk_name), entry_disk_name, TRUE, TRUE, 0);
		g_signal_connect (G_OBJECT ( entry_disk_name), "activate", G_CALLBACK ( gw_notebook_managment_scan_click), window);

		/* Horizontal separator */
		hseparator = gtk_hseparator_new ( );
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hseparator, TRUE, TRUE, 0);
	
		/* ComboBox for category selection */
		/* It's not mandatory to encode to UTF-8 because gw_combo_box_categories_create() encodes itself. */
		cmb_categories = gw_combo_box_categories_create ( window, _( "Category : "), gtk_ctree_node_get_row_data ( tree, root));
		g_object_ref ( GTK_WIDGET ( cmb_categories));
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_CATEGORY, GTK_WIDGET ( cmb_categories), (GDestroyNotify) g_object_unref);
		gw_combo_box_categories_load ( cmb_categories);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), GTK_WIDGET ( cmb_categories), TRUE, TRUE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( cmb_categories), 10);
		gtk_widget_set_tooltip_text (GTK_WIDGET ( cmb_categories),
		                             _( "Select the category to apply to the disk which will be added (even if the option is checked)."));
	
		/* Horizontal separator */
		hseparator = gtk_hseparator_new ( );
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hseparator, TRUE, TRUE, 0);
	
		/* Horizontal box for device file information */
		hb_device_file = gtk_hbox_new ( FALSE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb_device_file), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hb_device_file, TRUE, TRUE, 0);
		gtk_widget_set_tooltip_text (hb_device_file,
		                             _( "Give the device file of the selected media."));
	
		/* Device file information label */
		lbl_device_file = gtk_label_new (_( "Info : "));
		g_object_ref ( lbl_device_file);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_INFO, lbl_device_file, (GDestroyNotify) g_object_unref);
		gtk_box_pack_start ( GTK_BOX ( hb_device_file), lbl_device_file, FALSE, FALSE, 0);
	
		/* Horizontal box for device type information */
		hb_device_type = gtk_hbox_new ( FALSE, 0);
		gtk_widget_show ( hb_device_type);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hb_device_type, TRUE, TRUE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb_device_type), 5);
		gtk_widget_set_tooltip_text (hb_device_type,
		                             _( "Give the type of the selected media (ex : ext2, ext3, vfat, ntfs, ...)."));
	
		/* Device type information label */
		lbl_device_type = gtk_label_new (_( "Type : "));
		g_object_ref ( lbl_device_type);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_TYPE, lbl_device_type, (GDestroyNotify) g_object_unref);
		gtk_box_pack_start ( GTK_BOX ( hb_device_type), lbl_device_type, FALSE, FALSE, 0);
	
#ifdef HAVE_MOUNT_SYSTEM
		/* Horizontal box for media mount state information */
		hb_device_ismounted = gtk_hbox_new ( FALSE, 0);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hb_device_ismounted, TRUE, TRUE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb_device_ismounted), 5);
		gtk_widget_set_tooltip_text (hb_device_ismounted,
		                             _( "Display if the selected media is mounted or no."));
	
		/* Media mount state information label */
		lbl_device_ismounted = gtk_label_new (_( "Mounted : "));
		g_object_ref ( lbl_device_ismounted);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_MOUNTED, lbl_device_ismounted, (GDestroyNotify) g_object_unref);
		gtk_box_pack_start ( GTK_BOX ( hb_device_ismounted), lbl_device_ismounted, FALSE, FALSE, 0);
#endif
	
		/* Horizontal box for media volume name information */
		hb_device_volume_name = gtk_hbox_new ( FALSE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb_device_volume_name), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hb_device_volume_name, TRUE, TRUE, 0);
		gtk_widget_set_tooltip_text (hb_device_volume_name,
		                             _( "Give the volume name of the selected media (only if is mounted)."));
	
		/* Media volume information label */
		lbl_device_volume_name = gtk_label_new (_( "Volume : "));
		g_object_ref ( lbl_device_volume_name);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_VOLUME, lbl_device_volume_name, (GDestroyNotify) g_object_unref);
		gtk_box_pack_start ( GTK_BOX ( hb_device_volume_name), lbl_device_volume_name, FALSE, FALSE, 0);
	
		/* Horizontal box for media serial number information */
		hb_device_serial_number = gtk_hbox_new ( FALSE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb_device_serial_number), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hb_device_serial_number, TRUE, TRUE, 0);
		gtk_widget_set_tooltip_text (hb_device_serial_number,
		                             _( "Give the serial number of the selected media (only if is mounted). This number is a manufacture number."));
	
		/* Media serial number information label */
		lbl_device_serial_number = gtk_label_new (_( "Serial N# : "));
		g_object_ref ( lbl_device_serial_number);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_SERIAL_NUMBER, lbl_device_serial_number, (GDestroyNotify) g_object_unref);
		gtk_box_pack_start ( GTK_BOX ( hb_device_serial_number), lbl_device_serial_number, FALSE, FALSE, 0);
	
		/* Horizontal box for media capacity information */
		hb_device_capacity = gtk_hbox_new ( FALSE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb_device_capacity), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hb_device_capacity, TRUE, TRUE, 0);
		gtk_widget_set_tooltip_text (hb_device_capacity,
		                             _( "Give the full space of the selected media (only if is mounted)."));
	
		/* Media capacity information label */
		lbl_device_capacity = gtk_label_new (_( "Capacity : "));
		g_object_ref ( lbl_device_capacity);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_CAPACITY, lbl_device_capacity, (GDestroyNotify) g_object_unref);
		gtk_box_pack_start ( GTK_BOX ( hb_device_capacity), lbl_device_capacity, FALSE, FALSE, 0);
	
		/* Horizontal box for media free space information */
		hb_device_free_space = gtk_hbox_new ( FALSE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( hb_device_free_space), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_new_disk_control), hb_device_free_space, TRUE, TRUE, 0);
		gtk_widget_set_tooltip_text (hb_device_free_space,
		                             _( "Give the free space of the selected media (only if is mounted)."));
	
		/* Media free space information label */
		lbl_device_free_space = gtk_label_new (_( "Free space : "));
		g_object_ref ( lbl_device_free_space);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_FREE_SPACE, lbl_device_free_space, (GDestroyNotify) g_object_unref);
		gtk_box_pack_start ( GTK_BOX ( hb_device_free_space), lbl_device_free_space, FALSE, FALSE, 0);
	
		/* Frame for scan options */
		frm_options = gtk_frame_new (_( "Options"));
		gtk_container_set_border_width ( GTK_CONTAINER ( frm_options), 10);
		gtk_box_pack_start ( GTK_BOX ( hb_control), frm_options, TRUE, TRUE, 0);
	
		/* Vertical box of the frame options */
		vb_options = gtk_vbox_new ( FALSE, 0);
		gtk_container_add ( GTK_CONTAINER ( frm_options), vb_options);
	
		/* Check button for the displaying of media information */
		chk_display_device_info = gtk_check_button_new_with_label (_( "Display info"));
		g_object_ref ( chk_display_device_info);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_DISPLAY_INFO, chk_display_device_info, (GDestroyNotify) g_object_unref);
		g_signal_connect (G_OBJECT ( chk_display_device_info), "clicked", G_CALLBACK ( gw_notebook_managment_refresh_info), window);
		gtk_container_set_border_width ( GTK_CONTAINER ( chk_display_device_info), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_options), chk_display_device_info, FALSE, FALSE, 0);
		gtk_widget_set_tooltip_text (chk_display_device_info,
		                             _( "Displays selected media informations as path, capacity, free space, label,..."));

#ifdef HAVE_MOUNT_SYSTEM
		/* Check button for the automount */
		chk_automount_device = gtk_check_button_new_with_label (_("Automount"));
		g_object_ref ( chk_automount_device);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_AUTO_MOUNT, chk_automount_device, (GDestroyNotify) g_object_unref);
		g_signal_connect (G_OBJECT ( chk_automount_device), "clicked", G_CALLBACK (gw_notebook_managment_option_automount_click), window);
		gtk_container_set_border_width ( GTK_CONTAINER ( chk_automount_device), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_options), chk_automount_device, FALSE, FALSE, 0);
		gtk_widget_set_tooltip_text (chk_automount_device,
		                             _( "Mount the media if it wasn't mounted. And unmount after the media even if it was mounted before the scan."));
#endif
	
		/* Check button for the exploring of tree structure */
		chk_explore_tree_structure = gtk_check_button_new_with_label (_( "Explore tree structure of the media."));
		g_object_ref ( chk_explore_tree_structure);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EXPLORE_TREE_STRUCTURE, chk_explore_tree_structure, (GDestroyNotify) g_object_unref);
		g_signal_connect (G_OBJECT ( chk_explore_tree_structure), "clicked", G_CALLBACK (gw_notebook_managment_option_explore_tree_structure_click), window);
		gtk_container_set_border_width ( GTK_CONTAINER ( chk_explore_tree_structure), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_options), chk_explore_tree_structure, FALSE, FALSE, 0);
		gtk_widget_set_tooltip_text (chk_explore_tree_structure,
		                             _( "Keep this option checked to scan all folders and files informations."));

		/* Check button for the exploring of archive files */
		chk_explore_archive_files = gtk_check_button_new_with_label (_( "Explore archive files (.tar, .gz, .zip, ...)"));
		g_object_ref ( chk_explore_archive_files);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EXPLORE_ARCHIVE, chk_explore_archive_files, (GDestroyNotify) g_object_unref);
		g_signal_connect (G_OBJECT ( chk_explore_archive_files), "clicked", G_CALLBACK (gw_notebook_managment_option_explore_archive_click), window);
		gtk_container_set_border_width ( GTK_CONTAINER ( chk_explore_archive_files), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_options), chk_explore_archive_files, FALSE, FALSE, 0);
		gtk_widget_set_tooltip_text (chk_explore_archive_files,
		                             _( "Not yet implemented!!\nExplore all archives, as it was a directory. Archives are tarred or gzipped files."));
	
		/* Check button for the auto eject */
		chk_auto_eject_device = gtk_check_button_new_with_label (_( "Eject media if possible"));
		g_object_ref ( chk_auto_eject_device);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EJECT, chk_auto_eject_device, (GDestroyNotify) g_object_unref);
		g_signal_connect (G_OBJECT ( chk_auto_eject_device), "clicked", G_CALLBACK (gw_notebook_managment_option_eject_click), window);
		gtk_container_set_border_width ( GTK_CONTAINER ( chk_auto_eject_device), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_options), chk_auto_eject_device, FALSE, FALSE, 0);
		gtk_widget_set_tooltip_text (chk_auto_eject_device,
		                             _( "Eject the media if possible (CD-ROM...), even if the tray was closed. This is enable only if automount is enable!!"));
	
		/* Check button for setting category recursively */
		chk_category_recursively = gtk_check_button_new_with_label (_( "Sets category recursive"));
		g_object_ref ( chk_category_recursively);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_CATEGORY_RECURSIVE, chk_category_recursively, (GDestroyNotify) g_object_unref);
		g_signal_connect (G_OBJECT ( chk_category_recursively), "clicked", G_CALLBACK (gw_notebook_managment_option_category_click), window);
		gtk_container_set_border_width ( GTK_CONTAINER ( chk_category_recursively), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_options), chk_category_recursively, FALSE, FALSE, 0);
		gtk_widget_set_tooltip_text (chk_category_recursively,
		                             _( "Apply selected category to all items in the disk to add (disk, folders and files)."));
	
		/* Check button for the auto make description */
		chk_auto_make_description = gtk_check_button_new_with_label (_( "Auto make description"));
		g_object_ref ( chk_auto_make_description);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_MAKE_DESCRIPTION, chk_auto_make_description, (GDestroyNotify) g_object_unref);
		g_signal_connect (G_OBJECT ( chk_auto_make_description), "clicked", G_CALLBACK (gw_notebook_managment_option_description_click), window);
		gtk_container_set_border_width ( GTK_CONTAINER ( chk_auto_make_description), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_options), chk_auto_make_description, FALSE, FALSE, 0);
		gtk_widget_set_tooltip_text (chk_auto_make_description,
		                             _( "Make auto description of file (file format description, image size for xmp or jpg, etc...)."));
	
		/* Check button for the using a pattern to generate disk name */
		chk_use_pattern = gtk_check_button_new_with_label (_( "Use an advanced pattern to generate disk name"));
		g_object_ref ( chk_use_pattern);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_USE_PATTERN, chk_use_pattern, (GDestroyNotify) g_object_unref);
		g_signal_connect (G_OBJECT ( chk_use_pattern), "clicked", G_CALLBACK (gw_notebook_managment_option_use_pattern_click), window);
		gtk_container_set_border_width ( GTK_CONTAINER ( chk_use_pattern), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_options), chk_use_pattern, FALSE, FALSE, 0);
		gtk_widget_set_tooltip_text (chk_use_pattern,
		                             _( "You can fill extra tags to generate a disk name with disk information :\n- %% : %\n- %n : number archive (can use prefix to prefixed by 0 : %.4n give 0001, 0002, 0003, ..., 0091, ...\n- %l : media volume label\n- %t : media type\n- %s : serial number"));

		/* Check button for the using media label */
		chk_use_disk_label = gtk_check_button_new_with_label (_( "Use media volume name as disk name (only when disk name is empty)"));
		g_object_ref ( chk_use_disk_label);
		g_object_set_data_full (G_OBJECT ( window), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_USE_DISK_LABEL, chk_use_disk_label, (GDestroyNotify) g_object_unref);
		g_signal_connect (G_OBJECT ( chk_use_disk_label), "clicked", G_CALLBACK (gw_notebook_managment_option_use_disk_label_click), window);
		gtk_container_set_border_width ( GTK_CONTAINER ( chk_use_disk_label), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_options), chk_use_disk_label, FALSE, FALSE, 0);
		gtk_widget_set_tooltip_text (chk_use_disk_label,
		                             _( "If you didn't enter disk name and if your selected media has a volume name, the media volume name will be applied as disk name."));

		/* The add disk button to start the media scanning */
		bt_start_device_scan = gtk_button_new_with_label (_( "Add disk"));
		g_signal_connect (G_OBJECT ( bt_start_device_scan), "clicked", G_CALLBACK ( gw_notebook_managment_scan_click), window);
		gtk_container_set_border_width ( GTK_CONTAINER ( bt_start_device_scan), 5);
		gtk_box_pack_start ( GTK_BOX ( vb_tabbed_pane), bt_start_device_scan, FALSE, FALSE, 0);
	
		/* Loads the list of devices */
		/* Do not still load device info at time.
		gw_notebook_managment_load_device_list ( window);
		*/

		/* Loads the list of categories */
		gw_combo_box_categories_load ( cmb_categories);

		/* Fills the pattern to use for disk name */
		if ( gw_am_get_settings_tol ( GW_VALUE_APP_DISK_SCAN_USE_PATTERN) == 1)
		{
			gw_notebook_managment_set_device_name ( window, gw_am_get_settings ( GW_VALUE_APP_DISK_SCAN_PATTERN));
		}
	}

	return vb_tabbed_pane;
}


GtkWidget * gw_notebook_managment_create_and_add ( GtkWindow *window, GtkNotebook *parent)
{
	GtkWidget *tabbed_pane = NULL;
	GtkWidget *managment_tabbed_pane_label;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( window != NULL )
	{
		tabbed_pane = gw_notebook_managment_create ( window);

		if ( (parent != NULL) && (tabbed_pane != NULL) )
		{
			gtk_container_add ( GTK_CONTAINER ( parent), tabbed_pane);

			/* Text label of the managment tabbed pane. */
			managment_tabbed_pane_label = gtk_label_new (_( "Management"));

			/* Store reference to the title of tabbed pane */
			g_object_ref ( managment_tabbed_pane_label);
			g_object_set_data_full (G_OBJECT ( window), GW_REF_NOTEBOOK_MANAGMENT_TABBED_PANE_LABEL, managment_tabbed_pane_label,(GDestroyNotify) g_object_unref);
			gtk_notebook_set_tab_label ( parent, gtk_notebook_get_nth_page ( parent, 2), managment_tabbed_pane_label);
		}
	}

	return tabbed_pane;
}


gint gw_notebook_managment_set_device_dir ( GtkWindow *w, gchar *device_dir)
{
#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* To do. */

	return -1;
}


gint gw_notebook_managment_set_device_name ( GtkWindow *w, gchar *device_name)
{
	GtkEntry *ent = NULL;
	gint result = -1;

	if (device_name != NULL) {
		ent = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_ENTRY_DEVICE_NAME);
		gtk_entry_set_text ( ent, device_name);
		result = 0;
	}
	return result;
}


gint gw_notebook_managment_set_device_number ( GtkWindow *w, gchar *device_number)
{
	GtkEntry *ent = NULL;
	gint result = -1;

	if (device_number != NULL) {
		ent = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_ENTRY_DEVICE_NUMBER_ARCHIVE);
		gtk_entry_set_text ( ent, device_number);
		result = 0;
	}
	return result;
}


gint gw_notebook_managment_set_device_category ( GtkWindow *w, gchar *device_category)
{
	GtkBox *cmb;
	gint result = -1;

	if (device_category != NULL) {
		cmb = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_ENTRY_DEVICE_CATEGORY);
		gw_combo_box_categories_set_selected_category_name (cmb, device_category);
		result = 0;
	}
	return result;
}


gint gw_notebook_managment_set_option_display_info ( GtkWindow *w, gboolean b)
{
	GtkToggleButton *chk = NULL;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_DISPLAY_INFO);
	gtk_toggle_button_set_active ( chk, b);
	return 0;
}


gint gw_notebook_managment_set_option_automount ( GtkWindow *w, gboolean b)
{
	GtkToggleButton *chk = NULL;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_AUTO_MOUNT);
	gtk_toggle_button_set_active ( chk, b);
	return 0;
}


gint gw_notebook_managment_set_option_eject ( GtkWindow *w, gboolean b)
{
	GtkToggleButton *chk = NULL;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EJECT);
	gtk_toggle_button_set_active ( chk, b);
	return 0;
}


gint gw_notebook_managment_set_option_category_recursive ( GtkWindow *w, gboolean b)
{
	GtkToggleButton *chk = NULL;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_CATEGORY_RECURSIVE);
	gtk_toggle_button_set_active ( chk, b);
	return 0;
}


gint gw_notebook_managment_set_option_explore_tree_structure ( GtkWindow *w, gboolean b)
{
	GtkToggleButton *chk = NULL;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EXPLORE_TREE_STRUCTURE);
	gtk_toggle_button_set_active ( chk, b);
	return 0;
}


gint gw_notebook_managment_set_option_explore_archive ( GtkWindow *w, gboolean b)
{
	GtkToggleButton *chk = NULL;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EXPLORE_ARCHIVE);
	gtk_toggle_button_set_active ( chk, b);
	return 0;
}


gint gw_notebook_managment_set_option_make_description ( GtkWindow *w, gboolean b)
{
	GtkToggleButton *chk = NULL;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_MAKE_DESCRIPTION);
	gtk_toggle_button_set_active ( chk, b);
	return 0;
}


gint gw_notebook_managment_set_option_use_pattern ( GtkWindow *w, gboolean b)
{
	GtkToggleButton *chk = NULL;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_USE_PATTERN);
	gtk_toggle_button_set_active (chk, b);
	return 0;
}


gint gw_notebook_managment_set_option_use_disk_label ( GtkWindow *w, gboolean b)
{
	GtkToggleButton *chk = NULL;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_USE_DISK_LABEL);
	gtk_toggle_button_set_active ( chk, b);
	return 0;
}


gchar * gw_notebook_managment_get_device_dir ( GtkWindow *w)
{
	GtkComboBoxText *cmb = NULL;
	gchar *device_dir = NULL;

	cmb = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_DEVICE);
	device_dir = gtk_combo_box_text_get_active_text (cmb);
	return device_dir;
}


gchar * gw_notebook_managment_get_device_name ( GtkWindow *w)
{
	GtkEntry *ent = NULL;
	gchar *device_name = NULL;
	ent = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_ENTRY_DEVICE_NAME);
	device_name = g_strdup (gtk_entry_get_text (ent));
	return device_name;
}


gchar * gw_notebook_managment_get_device_number ( GtkWindow *w)
{
	GtkEntry *ent = NULL;
	gchar * device_number = NULL;
	ent = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_ENTRY_DEVICE_NUMBER_ARCHIVE);
	device_number = g_strdup (gtk_entry_get_text (ent));
	return device_number;
}


gchar * gw_notebook_managment_get_device_category ( GtkWindow *w)
{
	GtkEntry *ent = NULL;
	gchar * device_category = NULL;
	ent = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_ENTRY_DEVICE_CATEGORY);
	g_strdup_from_gtk_text ( gtk_entry_get_text ( ent), device_category);
	return device_category;
}


gboolean gw_notebook_managment_get_option_display_info ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_DISPLAY_INFO);
	result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
	return TRUE;
}


gboolean gw_notebook_managment_get_option_automount ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_AUTO_MOUNT);
	result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
	return TRUE;
}


gboolean gw_notebook_managment_get_option_eject ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EJECT);
	result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
	return TRUE;
}


gboolean gw_notebook_managment_get_option_category_recursive ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_CATEGORY_RECURSIVE);
	result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
	return TRUE;
}


gboolean gw_notebook_managment_get_option_explore_tree_structure ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EXPLORE_TREE_STRUCTURE);
	result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
	return TRUE;
}


gboolean gw_notebook_managment_get_option_explore_archive ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_EXPLORE_ARCHIVE);
	result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
	return TRUE;
}


gboolean gw_notebook_managment_get_option_make_description ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_MAKE_DESCRIPTION);
	result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
	return TRUE;
}


gboolean gw_notebook_managment_get_option_use_pattern ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_USE_PATTERN);
	result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
	return TRUE;
}


gboolean gw_notebook_managment_get_option_use_disk_label ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result;
	chk = g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_CHECK_USE_DISK_LABEL);
	result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
	return TRUE;
}


GtkBox * gw_notebook_managment_get_combo_box_categories ( GtkWindow *w)
{
	GtkBox *hbox = NULL;
	hbox = GTK_BOX ( g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_CATEGORY));
	return hbox;
}


GtkComboBoxText * gw_notebook_managment_get_combo_box_device ( GtkWindow *w)
{
	GtkComboBoxText *cmb_device = NULL;
	cmb_device = GTK_COMBO_BOX_TEXT ( g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_COMBO_BOX_DEVICE));
	return cmb_device;
}


GtkLabel * gw_notebook_managment_get_label_device_info ( GtkWindow *w)
{
	GtkLabel *label = NULL;
	label = GTK_LABEL ( g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_INFO));
	return label;
}


GtkLabel * gw_notebook_managment_get_label_device_type ( GtkWindow *w)
{
	GtkLabel *label = NULL;
	label = GTK_LABEL ( g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_TYPE));
	return label;
}


GtkLabel * gw_notebook_managment_get_label_device_mounted ( GtkWindow *w)
{
	GtkLabel *label = NULL;
	label = GTK_LABEL ( g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_MOUNTED));
	return label;
}


GtkLabel * gw_notebook_managment_get_label_device_volume ( GtkWindow *w)
{
	GtkLabel *label = NULL;
	label = GTK_LABEL ( g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_VOLUME));
	return label;
}


GtkLabel * gw_notebook_managment_get_label_device_serial_number ( GtkWindow *w)
{
	GtkLabel *label = NULL;
	label = GTK_LABEL ( g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_SERIAL_NUMBER));
	return label;
}


GtkLabel * gw_notebook_managment_get_label_device_capacity ( GtkWindow *w)
{
	GtkLabel *label = NULL;
	label = GTK_LABEL ( g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_CAPACITY));
	return label;
}


GtkLabel * gw_notebook_managment_get_label_device_free_space ( GtkWindow *w)
{
	GtkLabel *label = NULL;
	label = GTK_LABEL ( g_object_get_data (G_OBJECT ( w), REF_GW_GUI_NOTEBOOK_MANAGMENT_LABEL_DISPLAY_INFO_FREE_SPACE));
	return label;
}
