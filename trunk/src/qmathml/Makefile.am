noinst_LTLIBRARIES = libmmlreader.la libpainter.la

libmmlreader_la_LIBADD = -lQtCore -lQtXml \
	$(top_builddir)/src/mathml/libmathml.la
libmmlreader_la_SOURCES = mmlreader.cpp mmlcontenthandler.cpp qdomstring.cpp
libmmlreader_la_CXXFLAGS = $(QT_CXXFLAGS) -I$(top_srcdir)/src

libpainter_la_LIBADD = $(QT_LIBS) \
	$(top_builddir)/src/mathml/libmathml.la
libpainter_la_SOURCES = mmlpixmap.cpp qmmlpainter.cpp
libpainter_la_CXXFLAGS = $(QT_CXXFLAGS) -I$(top_srcdir)/src	

bin_PROGRAMS = qmathml
noinst_PROGRAMS = gallerycreator

qmathml_SOURCES = program.cpp mathmledit.cpp mathmlview.cpp cursorinfo.cpp \
	bpinfo.cpp latexloader.cpp
nodist_qmathml_SOURCES = latexloader_moc.cpp cursorinfo_moc.cpp \
	mathmlview_moc.cpp mathmledit_moc.cpp
if HAVE_CAIRO
qmathml_SOURCES += mathmlview2.cpp
nodist_qmathml_SOURCES += mathmlview2_moc.cpp
endif
qmathml_LDFLAGS = 
qmathml_LDADD = $(top_builddir)/src/mathml/libmathml.la \
	libmmlreader.la $(top_builddir)/src/cairomathml/libcairomml.la \
	libpainter.la
qmathml_CXXFLAGS = $(QT_CXXFLAGS) -I$(top_srcdir)/src \
	-I$(top_srcdir)/src/cairomathml $(CAIRO_CFLAGS)

gallerycreator_SOURCES = gallerycreator.cpp
gallerycreator_LDADD = libpainter.la libmmlreader.la
gallerycreator_CXXFLAGS = $(QT_CXXFLAGS) -I$(top_srcdir)/src \
	-DSRCDIR="\"$(top_srcdir)\""

if HAVE_CAIRO
CAIRO_SUBDIR=cairowidget
endif
SUBDIRS = fontmetrics $(CAIRO_SUBDIR)


# rule to generate source files from headers
%_moc.cpp: %.h
	$(MOC) -o $@ $<

noinst_HEADERS = bpinfo.h cursorinfo.h latexloader.h mathmledit.h mathmlview2.h mathmlview.h mmlcontenthandler.h mmlpixmap.h mmlreader.h qdomstring.h qmmlpainter.h
