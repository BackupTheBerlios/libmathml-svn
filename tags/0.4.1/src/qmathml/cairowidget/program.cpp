#include "cairotest.h"
#include <QApplication>

int
main(int argc, char **argv) {
        QApplication a( argc, argv );

        CairoTest m;
        m.show();
        return a.exec();
}
