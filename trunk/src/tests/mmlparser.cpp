#include <QFile>

#include <mathml/mmldocument.h>
#include "../qmathml/mmlreader.h"
#include "valgrind.h"
#include "dummypainter.h"

void
parse(MMLReader *r, const char *filepath) {
        QFile f(filepath);
        f.open(QIODevice::ReadOnly);
        r->parse(f);
        f.close();
        MMLDocument *doc = r->document();
        DummyPainter p;
        doc->setPainter(&p);
        doc->validate();
        doc->layout();
        doc->paint();
        delete doc;
}

int
main(int argc, const char **argv) {
    MMLReader r;
    for (int i=1; i<argc; ++i) {
        printf("%s\n", argv[i]);
        parse(&r, argv[i]);
    }
    return VALGRIND_COUNT_ERRORS;
}
