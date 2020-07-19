libdir = $(exec_prefix)/share/${PACKAGE}/plugins/descr

lib_LTLIBRARIES = libgwplugindescriptionavi.la \
			libgwplugindescriptiondescript_ion.la \
			libgwplugindescriptionfile_id_diz.la \
			libgwplugindescriptionhtml.la \
			libgwplugindescriptionmp3.la \
			libgwplugindescriptionmpc.la

libgwplugindescriptionavi_la_LDFLAGS = 'glib-config --cflags gmodule' -fPIC -version-info 1:0:0
libgwplugindescriptiondescript_ion_la_LDFLAGS = 'glib-config --cflags gmodule' -fPIC -version-info 1:0:0
libgwplugindescriptionfile_id_diz_la_LDFLAGS = 'glib-config --cflags gmodule' -fPIC -version-info 1:0:0
libgwplugindescriptionhtml_la_LDFLAGS = 'glib-config --cflags gmodule' -fPIC -version-info 1:0:0
libgwplugindescriptionmp3_la_LDFLAGS = 'glib-config --cflags gmodule' -fPIC -version-info 1:0:0
libgwplugindescriptionmpc_la_LDFLAGS = 'glib-config --cflags gmodule' -fPIC -version-info 1:0:0

libgwplugindescriptionavi_la_SOURCES = avi.c
libgwplugindescriptiondescript_ion_la_SOURCES = descript_ion.c
libgwplugindescriptionfile_id_diz_la_SOURCES = file_id_diz.c
libgwplugindescriptionhtml_la_SOURCES = html.c
libgwplugindescriptionmp3_la_SOURCES = mp3.c
libgwplugindescriptionmpc_la_SOURCES = mpc.c

INCLUDES = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src \
	@GTK_CFLAGS@

libgwplugindescriptiondescript_ion_la_LIBADD = \
	@top_srcdir@/src/tools/libgwtools.a
libgwplugindescriptionfile_id_diz_la_LIBADD = \
	@top_srcdir@/src/tools/libgwtools.a
libgwplugindescriptionhtml_la_LIBADD = \
	@top_srcdir@/src/tools/libgwtools.a
libgwplugindescriptionmp3_la_LIBADD = \
	@top_srcdir@/src/tools/libgwtools.a
