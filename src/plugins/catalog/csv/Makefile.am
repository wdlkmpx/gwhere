libdir = $(exec_prefix)/share/${PACKAGE}/plugins/catalog

lib_LTLIBRARIES = libgwplugincatalogcsv.la

libgwplugincatalogcsv_la_LDFLAGS = 'glib-config --cflags gmodule' -fPIC -version-info 1:0:0

libgwplugincatalogcsv_la_SOURCES = csv.c

INCLUDES = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src \
	@GTK_CFLAGS@

libgwplugincatalogcsv_la_LIBADD = \
	@top_srcdir@/src/plugins/libgwplugins.a \
	@top_srcdir@/src/db/libgwdb.a \
	@top_srcdir@/src/tools/libgwtools.a \
	@top_srcdir@/src/data/libgwdata.a
