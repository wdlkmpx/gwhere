SUBDIRS = man

DOXYGEN = doxygen

noinst_DATA = Doxyfile.in

doxygen-html: Doxyfile
	$(DOXYGEN) $<

EXTRA_DIST = $(noinst_DATA)
