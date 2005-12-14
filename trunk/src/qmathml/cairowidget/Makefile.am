
noinst_PROGRAMS = cairotest

cairotest_SOURCES = program.cpp cairotest.cpp

cairotest_LDFLAGS = 
cairotest_LDADD = $(QT_LIBS) $(CAIRO_LIBS)
cairotest_CXXFLAGS = $(QT_CXXFLAGS) $(CAIRO_CFLAGS)
nodist_cairotest_SOURCES = cairotest_moc.cpp

SUBDIRS = 

# rule to generate source files from headers
%_moc.cpp: %.h
	$(MOC) -o $@ $<

noinst_HEADERS = cairotest.h

