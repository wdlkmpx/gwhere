DOXYGEN = doxygen

man_MANS = gwhere.1

noinst_DATA = Doxyfile.in

doxygen-html: Doxyfile
	$(DOXYGEN) $<

EXTRA_DIST = $(noinst_DATA)
