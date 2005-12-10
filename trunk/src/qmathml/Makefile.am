noinst_LTLIBRARIES = libmmlreader.la

libmmlreader_la_LIBADD = -lQtCore -lQtXml \
	$(top_builddir)/src/mathml/libmathml.la
libmmlreader_la_SOURCES = mmlreader.cpp mmlcontenthandler.cpp qdomstring.cpp
libmmlreader_la_CXXFLAGS = $(QT_CXXFLAGS) -I$(top_srcdir)/src

bin_PROGRAMS = qmathml

qmathml_SOURCES = program.cpp mathmledit.cpp mathmlview.cpp cursorinfo.cpp \
	bpinfo.cpp latexloader.cpp qmmlpainter.cpp mmlpixmap.cpp
nodist_qmathml_SOURCES = latexloader_moc.cpp cursorinfo_moc.cpp \
	mathmlview_moc.cpp mathmledit_moc.cpp
if HAVE_CAIRO
qmathml_SOURCES += mathmlview2.cpp
nodist_qmathml_SOURCES += mathmlview2_moc.cpp
endif

qmathml_LDFLAGS = 
qmathml_LDADD = $(QT_LIBS) $(top_builddir)/src/mathml/libmathml.la \
	libmmlreader.la $(top_builddir)/src/cairomathml/libcairomml.la
qmathml_CXXFLAGS = $(QT_CXXFLAGS) -I$(top_srcdir)/src \
	-I$(top_srcdir)/src/cairomathml $(CAIRO_CFLAGS)

if HAVE_CAIRO
CAIRO_SUBDIR=cairowidget
endif
SUBDIRS = fontmetrics $(CAIRO_SUBDIR)


# rule to generate source files from headers
%_moc.cpp: %.h
	$(MOC) -o $@ $<

noinst_HEADERS = bpinfo.h cursorinfo.h latexloader.h mathmledit.h mathmlview2.h mathmlview.h mmlcontenthandler.h mmlpixmap.h mmlreader.h qdomstring.h qmmlpainter.h
