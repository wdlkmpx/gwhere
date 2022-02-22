DOXYGEN = doxygen
noinst_DATA = Doxyfile.in

man_MANS = gwhere.1

desktopdir = $(datadir)/applications
desktop_DATA = gwhere.desktop

pixdir = $(datadir)/pixmaps
pix_DATA = gwhere.xpm

doxygen-html: Doxyfile
	$(DOXYGEN) $<

EXTRA_DIST = $(noinst_DATA) gwhere.xpm gwhere.desktop
