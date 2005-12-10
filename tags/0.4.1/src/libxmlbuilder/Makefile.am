noinst_LTLIBRARIES = libmmlbuilder.la

libmmlbuilder_la_LIBADD = $(top_builddir)/src/mathml/libmathml.la $(XML2_LIBS)
libmmlbuilder_la_SOURCES = mmlreader.cpp
libmmlbuilder_la_CXXFLAGS = -I$(top_srcdir)/src $(XML2_CFLAGS)

noinst_HEADERS = mmlreader.h
