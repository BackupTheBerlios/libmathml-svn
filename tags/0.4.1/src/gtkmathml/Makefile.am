bin_PROGRAMS = gtkmathml

gtkmathml_SOURCES = test.cpp
gtkmathml_LDFLAGS = 
gtkmathml_LDADD =  $(XML2_LIBS) $(top_builddir)/src/mathml/libmathml.la \
	$(top_builddir)/src/libxmlbuilder/libmmlbuilder.la \
	$(top_builddir)/src/cairomathml/libcairomml.la \
	$(GTKMM_LIBS)

gtkmathml_CXXFLAGS = $(GTKMM_CFLAGS) $(XML2_CFLAGS) -I$(top_srcdir)/src \
	-I$(top_srcdir)/src/cairomathml -I$(top_srcdir)/src/libxmlbuilder

SUBDIRS = 

