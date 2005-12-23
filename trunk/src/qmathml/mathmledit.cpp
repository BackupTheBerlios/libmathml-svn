#include "mathmledit.h"
#include "mathmlview.h"
#ifdef HAVE_CAIRO
#include "mathmlview2.h"
#endif
#include "cursorinfo.h"
#include "mmlreader.h"
#include "latexloader.h"
#include <mathml/mmldocument.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QListWidget>
#include <QComboBox>
#include <QFontDatabase>
#include <QCheckBox>
#include <QDir>
#include <QApplication>
#include <cstdlib>

/**
 * Main widget that displays the MathMLEdit program.
 **/
MathMLEdit::MathMLEdit(QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f) {
    // set layout
    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);
    donotupdate = false;

    /* add a text field for writing the mathml
       every time the text changes, a signal is sent to various other parts
       of the program */
    QHBoxLayout *hl = new QHBoxLayout();
    layout->addLayout(hl);
    qte = new QTextEdit();
    hl->addWidget(qte);
    connect(qte, SIGNAL(textChanged()), this, SLOT(setMML()));
    // on the same line, add a cursorinfo widget
    cursorinfo = new CursorInfo();
    hl->addWidget(cursorinfo);

    /* start a new row */
    hl = new QHBoxLayout();
    layout->addLayout(hl);
//  hl->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    /* add the most important widget: the one for viewing the mathml */
    mv = new MathMLView(this);
    hl->addWidget(mv);
    connect(mv, SIGNAL(cursorChanged()), cursorinfo, SLOT(cursorChanged()));

    ql = new QLabel("No errors");
    layout->addWidget(ql);
    testimage = new QLabel();
    hl->addWidget(testimage);
    testimage->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    testimage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    latex = new LatexLoader(this);
    connect(latex, SIGNAL(readImage(const QPixmap &)),
        testimage, SLOT(setPixmap(const QPixmap &)));

    testicons = new QListWidget();
    testicons->setViewMode(QListView::IconMode);
    layout->addWidget(testicons);
    testicons->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    testicons->setMaximumHeight(160);
//    testicons->setResizeMode(QIconView::Adjust);
    connect(testicons, SIGNAL(itemSelectionChanged()),
        this, SLOT(showFile()));

    hl = new QHBoxLayout();
    layout->addLayout(hl);
    dirlist = new QComboBox();
    hl->addWidget(dirlist);
    connect(dirlist, SIGNAL(highlighted(const QString &)),
        this, SLOT(setExamplesSubDir(const QString &)));

    subdirlist = new QComboBox();
    hl->addWidget(subdirlist);
    connect(subdirlist, SIGNAL(highlighted(const QString &)),
        this, SLOT(setExamplesSubSubDir(const QString &)));

    subsubdirlist = new QComboBox();
    hl->addWidget(subsubdirlist);
    connect(subsubdirlist, SIGNAL(highlighted(const QString &)),
        this, SLOT(loadExampleDir(const QString &)));
    
    setExamplesDir(qApp->applicationDirPath()
        + "/../share/libmathml/testsuite");
    setActive(dirlist, "Presentation");
    setExamplesSubDir("Presentation");
    setActive(subdirlist, "GeneralLayout");
    setExamplesSubSubDir("GeneralLayout");
    setActive(subsubdirlist, "msqrt-mroot");
    loadExampleDir("msqrt-mroot");
    testicons->setCurrentItem(testicons->item(0));

    hl = new QHBoxLayout();
    layout->addLayout(hl);
    sizelabel = new QLabel("font:");
    hl->addWidget(sizelabel);
    sizelabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    familylist = new QComboBox();
    hl->addWidget(familylist);
    stylelist = new QComboBox();
    hl->addWidget(stylelist);
    stylelist->hide(); // does not have a lot of influence
    sizelabel = new QLabel("");
    hl->addWidget(sizelabel);
    sizelabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sizelist = new QComboBox();
    hl->addWidget(sizelist);
    zoomlabel = new QLabel("zoom:");
    hl->addWidget(zoomlabel);
    zoomlabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    zoomlist = new QComboBox();
    hl->addWidget(zoomlist);
    QFontDatabase qfd;
    QStringList l = qfd.families();
    familylist->insertItems(0, l);
    familylist->setEnabled(familylist->count()>1);
    connect(familylist, SIGNAL(highlighted(const QString &)),
        this, SLOT(changeFont(const QString &)));
    connect(stylelist, SIGNAL(highlighted(const QString &)),
        this, SLOT(changeStyle(const QString &)));
    connect(sizelist, SIGNAL(highlighted(const QString &)),
        this, SLOT(changeSize(const QString &)));
    connect(zoomlist, SIGNAL(highlighted(const QString &)),
        this, SLOT(changeZoom(const QString &)));

    lastSelectedSize = 16;
    for (int i=0; i< familylist->count(); ++i) {
        if (familylist->itemText(i).indexOf("Roman") != -1) {
            familylist->setCurrentIndex(i);
        }
    }
    changeFont(familylist->currentText());
    zoomlist->addItem("50");
    zoomlist->addItem("100");
    zoomlist->addItem("150");
    zoomlist->addItem("200");
    zoomlist->addItem("300");
    zoomlist->setCurrentIndex(1);
    debug = new QCheckBox("outline");
    hl->addWidget(debug);
    connect(debug, SIGNAL(toggled(bool)),
        mv, SLOT(setOutline(bool)));
}
MathMLEdit::~MathMLEdit() {
}
void
MathMLEdit::setMML() {
    if (donotupdate) return;
    MMLReader mr;

    mr.parse(qte->toPlainText());
    MMLDocument *doc = mr.document();
    if (doc && doc->validate()) {
        ql->setText("No errors");
        cursorinfo->setDocument(doc);
        mv->setDocument(doc);
    } else {
        ql->setText(mr.error());
        cursorinfo->setDocument(0);
        mv->setDocument(0);
    }
    //latex->parseData(qte->toPlainText());
}
void
MathMLEdit::setExamplesDir(const QString &dir) {
    examplesdir = dir;
    QDir d(dir);
    // find all subdirectories
    QStringList list;
    list.push_back("[^.]*");
    d.setNameFilters(list);
    QStringList entries = d.entryList(QDir::Dirs);
    dirlist->clear();
    // if there are examples in the current dir, add it
    list.clear();
    list.push_back("*.mml");
    d.setNameFilters(list);
    if (d.entryList(QDir::Files).size() > 0) {
        entries += ".";
    }
    dirlist->addItems(entries);
    if (entries.size() < 2) {
        dirlist->hide();
    } else {
        dirlist->show();
    }
    setExamplesSubDir(dirlist->currentText());
}
void
MathMLEdit::setExamplesSubDir(const QString &dir) {
    subdir = examplesdir;
    subdir += "/" + dir;
    QDir d(subdir);
    // find all subdirectories
    QStringList list;
    list.push_back("[^.]*");
    d.setNameFilters(list);
    QStringList entries = d.entryList(QDir::Dirs);
    subdirlist->clear();
    // if there are examples in the current dir, add it
    list.clear();
    list.push_back("*.mml");
    d.setNameFilters(list);
    if (d.entryList(QDir::Files).size() > 0) {
        entries += ".";
    }
    subdirlist->addItems(entries);
    if (entries.size() < 2) {
        subdirlist->hide();
    } else {
        subdirlist->show();
    }
    setExamplesSubSubDir(subdirlist->currentText());
}
void
MathMLEdit::setExamplesSubSubDir(const QString &dir) {
    subsubdir = subdir + "/" + dir;
    QDir d(subsubdir);
    QStringList list;
    list.push_back("[^.]*");
    d.setNameFilters(list);
    QStringList entries = d.entryList(QDir::Dirs);
    subsubdirlist->clear();
    // if there are examples in the current dir, add it
    list.clear();
    list.push_back("*.mml");
    d.setNameFilters(list);
    if (d.entryList(QDir::Files).size() > 0) {
        entries += ".";
    }
    subsubdirlist->addItems(entries);
    if (entries.size() < 2) {
        subsubdirlist->hide();
    } else {
        subsubdirlist->show();
    }
    loadExampleDir(subsubdirlist->currentText());
}
void
MathMLEdit::loadExampleDir(const QString &sssdir) {
    dir = subsubdir + "/" + sssdir;
    QDir d(dir);
    QStringList list;
    list.push_back("*.mml");
    d.setNameFilters(list);
    QStringList files = d.entryList(QDir::Files);
    testicons->clear();
    if (files.size()) {
        for (int i=0; i<files.size(); ++i) {
            QString f = files[i];
            QString imgf = f.left(f.length()-3) + "png";
            QImage qi(dir+"/"+imgf);
            int height = 64;
            if (!qi.isNull()) {
                qi = qi.scaled(height, height,
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation);
            }
            QListWidgetItem *ivi;
            ivi = new QListWidgetItem(f, testicons);
            ivi->setIcon(QPixmap::fromImage(qi));
        }
        testicons->show();
        testimage->show();
    } else {
        testicons->hide();
        testimage->hide();
    }
}
void
MathMLEdit::showFile() {
    donotupdate = true;
    QListWidgetItem *ivi = testicons->currentItem();
    QString f = ivi->text();
    QString i = f.left(f.length()-3) + "png";
    QImage img(dir+"/"+i);
    img = latex->cleanse(img);
    testimage->setPixmap(QPixmap::fromImage(img));
    QFile file(dir+"/"+f);
    file.open(QIODevice::ReadOnly);
    qte->setPlainText(file.readAll());
    donotupdate = false;
    setMML();
}
void
MathMLEdit::changeFont(const QString &family) {
    QFontDatabase qfd;

    QString style = stylelist->currentText();
    stylelist->clear();
    stylelist->addItems(qfd.styles(family));
    for (int i=0; i< stylelist->count(); ++i) {
        if (style == stylelist->itemText(i)) {
            stylelist->setCurrentIndex(i);
        }
    }

    int size = updateSizeList(family, style);
    mv->changeFont(qfd.font(family, style, size));
}
int
MathMLEdit::updateSizeList(const QString family, const QString &style) {
    QFontDatabase qfd;
    QList<int> sizes = qfd.smoothSizes(family, style);
    pointsize = true;
    if (sizes.isEmpty()) {
        sizes = qfd.pointSizes(family);
        pointsize = false;
    }
    if (sizes.isEmpty()) {
        sizes = qfd.standardSizes();
        pointsize = true;
    }
    if (pointsize) {
        sizelabel->setText("pointsize:");
    } else {
        sizelabel->setText("pixelsize:");
    }
    int size = lastSelectedSize;
    sizelist->clear();
    int ds=1000;
    int pos = 0;
    for (int i=0; i < sizes.size(); ++i) {
        sizelist->addItem(QString::number(sizes[i]));
        int x = 0;
        if (sizes[i] == 0) x = 1;
        if (abs(sizes[i]-size) <= ds) {
            ds = abs(sizes[i]-size);
            pos = i;
        }
    }
    sizelist->setCurrentIndex(pos);
    sizelist->setEnabled(sizelist->count()>1);
    return size;
}
void
MathMLEdit::changeStyle(const QString &style) {
    QFontDatabase qfd;
    QString family = familylist->currentText();
    int size = updateSizeList(family, style);
    mv->changeFont(qfd.font(family, style, size));
}
void
MathMLEdit::changeSize(const QString &s) {
    bool ok;
    int size = s.toInt(&ok);
    if (!ok) {
        return;
    }
    QFontDatabase qfd;
    QFont f = qfd.font(familylist->currentText(),
        stylelist->currentText(),
        size);
    if (!pointsize) {
        f.setPixelSize(size);
    }
    mv->changeFont(f);
    lastSelectedSize = size;
}
void
MathMLEdit::changeZoom(const QString &s) {
    bool ok;
    int size = s.toInt(&ok);
    if (!ok) {
        return;
    }
    mv->changeZoom(size/100.0);
}
void
MathMLEdit::setOutline() {
    mv->setOutline(debug->isChecked());
}
void
MathMLEdit::setActive(QComboBox *b, const QString &s) {
    int size = b->count();
    for (int i=0; i<size; ++i) {
        if (b->itemText(i) == s) {
            b->setCurrentIndex(i);
        }
    }
}
