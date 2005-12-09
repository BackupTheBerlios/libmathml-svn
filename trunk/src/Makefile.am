if HAVE_QT
QT_SUBDIRS=qmathml XMLSchema tests
endif

if HAVE_CAIRO
CAIRO_SUBDIR=cairomathml
endif

if HAVE_XML2
XML_SUBDIR=libxmlbuilder
if HAVE_WX
WX_SUBDIR=wxmathml
endif

if HAVE_GTK
if HAVE_CAIRO
GTK_SUBDIR=gtkmathml
endif
endif
endif

SUBDIRS = mathml $(CAIRO_SUBDIR) $(XML_SUBDIR) $(QT_SUBDIRS) $(WX_SUBDIR) \
	$(GTK_SUBDIR)

