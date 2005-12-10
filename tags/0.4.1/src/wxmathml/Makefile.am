bin_PROGRAMS = wxmathml

wxmathml_SOURCES = mathmledit.cpp wxmmlpainter.cpp mathmlview.cpp \
	mmlpixmap.h mmlpixmap.cpp
wxmathml_LDFLAGS = 
wxmathml_LDADD = $(top_builddir)/src/mathml/libmathml.la \
	$(top_builddir)/src/libxmlbuilder/libmmlbuilder.la \
	$(XML2_LIBS) $(WX_LIBS)
wxmathml_CXXFLAGS = $(WX_CXXFLAGS) $(XML2_CFLAGS) -I$(top_srcdir)/src \
	-I$(top_srcdir)/src/libxmlbuilder

SUBDIRS = 

