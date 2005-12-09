noinst_LTLIBRARIES = libcairomml.la

libcairomml_la_LIBADD = $(CAIRO_LIBS) $(PANGO_LIBS)
	$(top_builddir)/src/mathml/libmathml.la
libcairomml_la_SOURCES = cairopainter.cpp mmlimage.cpp
libcairomml_la_CXXFLAGS = $(PANGO_CFLAGS) $(CAIRO_CFLAGS) -I$(top_srcdir)/src

noinst_HEADERS = cairopainter.h mmlimage.h
