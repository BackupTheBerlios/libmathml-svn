#include "mmlpixmap.h"
#include "mmlreader.h"
#include "mathml/mmldocument.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QApplication>

MMLReader r;
MMLPixmap *pix;
const QString srcdirpath(SRCDIR);
const QDir srcdir(srcdirpath);
const QDir suitedir(SRCDIR"/share/libmathml/testsuite");
const QDir baseout(QDir::currentPath() + QDir::separator() + "libmathml");
const QDir testout(QDir::currentPath() + QDir::separator() + "testsuite");
QTextStream out;
bool do_output = true;
bool output_erroneous = false;

void
initPixmap() {
    pix = new MMLPixmap();
    QPalette p;
    p.setColor(QPalette::Background, QColor(255,255,255,0));
    pix->setPalette(p);
    QFont f("Times New Roman", 12);
    f.setStyleHint(QFont::Serif);
    f.setFamily(f.defaultFamily());
    pix->setFont(f);
}
void
deletePixmap() {
    delete pix;
}

MMLDocument *
parse(QString filepath) {
        QFile f(filepath);
        f.open(QIODevice::ReadOnly);
        r.parse(f);
        f.close();
        return r.document();
}
void
printhead(QString dir) {
    static bool printedhead = true;
    static QString lastdir;
    if (dir != lastdir) {
        lastdir = dir;
        printedhead = false;
    }
    if (printedhead == false) {
        out << "<tr><td colspan='2' style='border-top: 1px solid black;border-bottom: 1px solid black'>"
            << dir << "</td></tr>" << endl;
        printedhead = true;
    }
}
void
renderFile(QString &path) {
    deletePixmap();
    initPixmap();
    QFileInfo f(path);
    QString outputdir = suitedir.relativeFilePath(f.absolutePath());
    baseout.mkpath(outputdir);
    testout.mkpath(outputdir);
    QString outputfile = outputdir+"/"+f.baseName()+".png";
    QString outputoutlinefile = outputdir+"/"+f.baseName()+"outline.png";
    MMLDocument *doc = parse(path);
    if (doc->validate()) {
        printhead(outputdir);
        out << "<tr><td>" << f.baseName() << "</td><td>";
        pix->setDocument(doc);
        pix->setOutline(false);
        QPixmap p = pix->getPixmap();
        if (do_output) {
            p.save("libmathml/"+outputfile, "PNG", 0);
        }
        pix->setOutline(true);
        p = pix->getPixmap();
        if (do_output) {
            p.save("libmathml/"+outputoutlinefile, "PNG", 0);
        }

        // calculate offset for the image, so that it aligns with the text
        int valign = (int)-doc->getDescent() - 4 - 2;
        out << "_<img style='border:1px solid #E0E0E0;vertical-align:"
            << valign << "px;' src='libmathml/" << outputfile << "' "
            << "onmouseover='this.src=\"libmathml/" << outputoutlinefile
            << "\";' onmouseout='this.src=\"libmathml/" << outputfile
            << "\";' width='" << p.width() << "px' height='" << p.height()
            << "'/>_";
        QString orig = f.absolutePath() + QDir::separator() + f.baseName()
            + ".png";
        QString origcopy = "testsuite/" + outputfile;
        // open file to get sizes
        QPixmap ref(orig);
        if (do_output && !ref.isNull()) {
            QFile::copy(orig, origcopy);
            int cvalign =
                -(int)(doc->getDescent()/doc->getHeight()*ref.height());
            if (cvalign > 0 || cvalign < -1000) {
                cvalign = - ref.height()/2;
            }
            out << " <img style='border:1px solid #E0E0E0;vertical-align:"
                << cvalign << "px;' src='" << origcopy << "' width='"
                << ref.width() << "px' height='" << ref.height() << "'/>";
        }
        out << "</td></tr>" << endl;
    } else if (output_erroneous) {
        printhead(outputdir);
        out << "<tr><td>" << f.baseName() << "</td><td>";
        out << doc->errorMsg().utf8();
        out << "</td></tr>" << endl;
    }
    delete doc;
}
bool processDir(QDir &dir) {
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fi = list.at(i);
        if (fi.isDir() && fi.fileName() != "." && fi.fileName() != "..") {
            QDir d(fi.absoluteFilePath());
            if (processDir(d)) {
                return true;
            }
        } else if (fi.fileName().endsWith(".mml")) {
            QString path = fi.absoluteFilePath();
            renderFile(path);
        }
    }
    return false;
}

void renderTestSuite()
{
    QString dir(SRCDIR);
    QDir d(srcdirpath+"/share/libmathml/testsuite");
    printf("%s\n", (const char*)d.absolutePath().toUtf8());
    processDir(d);
}
int
main(int argc, char **argv) {
    QApplication a( argc, argv );

    QFile htmloutput("gallery.html");
    htmloutput.open(QIODevice::WriteOnly);
    out.setDevice(&htmloutput);
    out << "<html><body style='background:#FAFAFA;'><table>";

    initPixmap();

    if (argc > 1) {
        for (int i=1; i<argc; ++i) {
            QString path(argv[i]);
            renderFile(path);
        }
    } else {
        renderTestSuite();
    }

    out << "</table></body></html>" << endl;
    htmloutput.close();

    deletePixmap();

    return 0;
}
