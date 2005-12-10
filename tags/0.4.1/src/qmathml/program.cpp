#include "mathmledit.h"
#include <QApplication>

int
main(int argc, char **argv) {
        QApplication a( argc, argv );

        MathMLEdit m;
        m.show();
        return a.exec();
}
