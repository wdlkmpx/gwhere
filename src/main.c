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


#include "gwsupport.h"
#include "main.h"

#include <gtk/gtk.h>
#include <glib.h>

#include <stdlib.h>

#if defined ( OS_WIN32)
	#include <windows.h>
#endif

#include "gwapplicationmanager.h"
#include "gwguimanager.h"


int main (int argc, char *argv[]) {
	char *locale_dir = NULL;


#ifdef GW_DEBUG_MODE
#ifdef HAVE_GTK20
	g_mem_set_vtable ( glib_mem_profiler_table);
#endif

	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "application is starting ==> memory status : ");
	g_mem_profile ( );
#endif


#ifdef ENABLE_NLS
#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "NLS enabled");
#endif
	setlocale ( LC_ALL, "");
	if ( (locale_dir = gw_package_get_locale_dir ( )) != NULL) {
#ifdef GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Locale is %s", locale_dir);
#endif

		bindtextdomain ( PACKAGE, locale_dir);
		textdomain ( PACKAGE);
		g_free ( locale_dir);
	}
#endif

	gtk_set_locale ( );

//	g_log_set_handler ( "Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
//	g_log_set_handler ( "Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);
	gtk_init ( &argc, &argv);

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "application is initializing ==> memory status : ");
	g_mem_profile ( );
#endif

	gw_am_init ( argc, argv);

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "application is loading catalog ==> memory status : ");
	g_mem_profile ( );
#endif

	/* Enter the main loop */
	gtk_main ( );

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "application is exited ==> memory status : ");
	g_mem_profile ( );
#endif

	return 0;
}

