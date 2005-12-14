#include "mmlpixmap.h"
#include "mmlreader.h"
#include "mathml/mmldocument.h"
#include <QFile>
#include <QApplication>

MMLDocument *
parse(MMLReader *r, QString filepath) {
        QFile f(filepath);
        f.open(QIODevice::ReadOnly);
        r->parse(f);
        f.close();
        return r->document();
}

int
main(int argc, char **argv) {
        QApplication a( argc, argv );

	QString path = "/home/oever/cpp/libmathmlsvn/trunk/share/libmathml/testsuite/Presentation/GeneralLayout/msqrt-mroot/mrootB1.mml";

	MMLReader r;
	MMLDocument *doc = parse(&r, path);
	printf("validate: %i\n", doc->validate());
	MMLPixmap pix;
	pix.setDocument(doc);
	QPixmap p = pix.getPixmap();
	if (!p.save("/tmp/test.png", "PNG")) {
		printf("could not save\n");
	}
	delete doc;
	
        return 0;
}
