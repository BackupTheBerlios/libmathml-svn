noinst_PROGRAMS = qfontmetrics

qfontmetrics_SOURCES = program.cpp fontdisplay.cpp
nodist_qfontmetrics_SOURCES = fontdisplay_moc.cpp 
qfontmetrics_LDFLAGS = 
qfontmetrics_LDADD = $(QT_LIBS)
qfontmetrics_CXXFLAGS = $(QT_CXXFLAGS) -I$(top_srcdir)/src

SUBDIRS =

# rule to generate source files from headers
%_moc.cpp: %.h
	$(MOC) -o $@ $<

noinst_HEADERS = fontdisplay.h

