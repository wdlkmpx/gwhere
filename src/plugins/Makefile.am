SUBDIRS = . descr catalog
SOURCES = gwdescr.h gwcatalog.h

AM_CPPFLAGS = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src \
	${GTK_CFLAGS}

noinst_LIBRARIES = libgwplugins.a

libgwplugins_a_SOURCES = \
	gwcatalog.h \
	gwdescr.h \
	gwplugininfo.c gwplugininfo.h

EXTRA_DIST = $(SOURCES)

libgwplugins_a_LIBADD = 
