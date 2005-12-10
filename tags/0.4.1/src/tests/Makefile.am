TESTS = testrunner valgrindtest.sh
check_PROGRAMS = testrunner
noinst_PROGRAMS = mmlparser

testrunner_LDFLAGS = 
testrunner_LDADD = $(QT_LIBS) $(top_builddir)/src/mathml/libmathml.la \
	$(top_builddir)/src/qmathml/libmmlreader.la -lcppunit
testrunner_CXXFLAGS = $(QT_CXXFLAGS) -I$(top_srcdir)/src \
	-DSRCDIR="\"$(top_srcdir)\""
testrunner_SOURCES = testrunner.cpp mathml-test.cpp

mmlparser_LDFLAGS = 
mmlparser_LDADD = $(top_builddir)/src/qmathml/libmmlreader.la 
mmlparser_CXXFLAGS = $(QT_CXXFLAGS) -I$(top_srcdir)/src
mmlparser_SOURCES = mmlparser.cpp

noinst_HEADERS = dummypainter.h valgrind.h
