#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include "fontdisplay.h"

int
main(int argc, char **argv) {
    QApplication a( argc, argv );
    QWidget w;
    QVBoxLayout *layout = new QVBoxLayout(&w);

    // with bug and direct rendering
    FontDisplay fd1(true, true);
    layout->addWidget(&fd1);

    FontDisplay fd2(false, true);
    layout->addWidget(&fd2);

    // with bug and indirect rendering: the real problem
    FontDisplay fd3(true, false);
    layout->addWidget(&fd3);

    FontDisplay fd4(false, false);
    layout->addWidget(&fd4);

    QLineEdit qle;
    layout->addWidget(&qle);

    QObject::connect(&qle, SIGNAL(textChanged(const QString &)),
                     &fd1,  SLOT(setText(const QString &)));
    QObject::connect(&qle, SIGNAL(textChanged(const QString &)),
                     &fd2,  SLOT(setText(const QString &)));
    QObject::connect(&qle, SIGNAL(textChanged(const QString &)),
                     &fd3,  SLOT(setText(const QString &)));
    QObject::connect(&qle, SIGNAL(textChanged(const QString &)),
                     &fd4,  SLOT(setText(const QString &)));

    QHBoxLayout *hlayout = new QHBoxLayout();
    layout->addLayout(hlayout);

    QCheckBox bold("bold");
    hlayout->addWidget(&bold);

    QObject::connect(&bold, SIGNAL(stateChanged(int)),
                     &fd1, SLOT(setBold(bool)));
    QObject::connect(&bold, SIGNAL(stateChanged(int)),
                     &fd2, SLOT(setBold(bool)));
    QObject::connect(&bold, SIGNAL(stateChanged(int)),
                     &fd3, SLOT(setBold(bool)));
    QObject::connect(&bold, SIGNAL(stateChanged(int)),
                     &fd4, SLOT(setBold(bool)));

    QCheckBox italic("italic");
    hlayout->addWidget(&italic);

    QObject::connect(&italic, SIGNAL(stateChanged(int)),
                     &fd1, SLOT(setItalic(bool)));
    QObject::connect(&italic, SIGNAL(stateChanged(int)),
                     &fd2, SLOT(setItalic(bool)));
    QObject::connect(&italic, SIGNAL(stateChanged(int)),
                     &fd3, SLOT(setItalic(bool)));
    QObject::connect(&italic, SIGNAL(stateChanged(int)),
                     &fd4, SLOT(setItalic(bool)));

    QSpinBox *fontsize = new QSpinBox(&w);
    fontsize->setValue(12);
    fontsize->setMinimum(1);
    hlayout->addWidget(fontsize);

    QObject::connect(fontsize, SIGNAL(valueChanged(int)),
                     &fd1, SLOT(setPointSize(int)));
    QObject::connect(fontsize, SIGNAL(valueChanged(int)),
                     &fd2, SLOT(setPointSize(int)));
    QObject::connect(fontsize, SIGNAL(valueChanged(int)),
                     &fd3, SLOT(setPointSize(int)));
    QObject::connect(fontsize, SIGNAL(valueChanged(int)),
                     &fd4, SLOT(setPointSize(int)));

    w.show();
    return a.exec();
}
