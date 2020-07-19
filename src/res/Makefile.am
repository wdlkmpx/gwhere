## Process this file with automake to produce Makefile.in

INCLUDES = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src \
	@GTK_CFLAGS@ \
	-D${HOST_OS}

noinst_LIBRARIES = libgwres.a

libgwres_a_SOURCES = \
	gwres.h \
	gwicons.c gwicons.h

EXTRA_DIST = $(SOURCES)
