SUBDIRS = . descr catalog
SOURCES = gwdescr.h gwcatalog.h

INCLUDES = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src \
	@GTK_CFLAGS@ \
	-D${HOST_OS}

noinst_LIBRARIES = libgwplugins.a

libgwplugins_a_SOURCES = \
	gwcatalog.h \
	gwdescr.h \
	gwplugininfo.c gwplugininfo.h

EXTRA_DIST = $(SOURCES)

libgwplugins_a_LIBADD = 
