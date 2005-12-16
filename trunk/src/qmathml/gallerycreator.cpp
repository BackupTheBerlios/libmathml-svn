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

MMLDocument *
parse(QString filepath) {
        QFile f(filepath);
        f.open(QIODevice::ReadOnly);
        r.parse(f);
        f.close();
        return r.document();
}

void
renderFile(QString &path) {
    static QString lastdir;
    QFileInfo f(path);
    QString outputdir = suitedir.relativeFilePath(f.absolutePath());
    if (outputdir != lastdir) {
        out << "<tr><td colspan='2' style='border-top: 1px solid black;border-bottom: 1px solid black'>"
            << outputdir << "</td></tr>" << endl;
        lastdir = outputdir;
        baseout.mkpath(outputdir);
        testout.mkpath(outputdir);
    }
    QString outputfile = outputdir+"/"+f.baseName()+".png";
    MMLDocument *doc = parse(path);
    out << "<tr><td>" << f.baseName() << "</td><td>";
    if (doc->validate()) {
        pix->setDocument(doc);
        QPixmap p = pix->getPixmap();
        if (!p.save("libmathml/"+outputfile, "PNG")) {
            printf("could not save\n");
        } else {
            // calculate offset for the image, so that it aligns with the text
            int valign = (int)-doc->getDescent()-4;
            out << "_<img style='border:1px solid #EEEEEE;vertical-align:"
                << valign << "px;' src='libmathml/" << outputfile << "' />_";
            QString orig = f.absolutePath() + QDir::separator() + f.baseName()
                + ".png";
            if (QFile::copy(orig, "testsuite/" + outputfile)) {
                out << " <img src='testsuite/" + outputfile + "'/>";
            }
        }
    } else {
        out << doc->errorMsg().utf8();
    }
    out << "</td></tr>" << endl;
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

    pix = new MMLPixmap();
    QPalette p;
    p.setColor(QPalette::Background, QColor(255,255,255,0));
    pix->setPalette(p);
    pix->setFont(QFont("serif", 10));

    renderTestSuite();

    out << "</table></body></html>" << endl;
    htmloutput.close();

    delete pix;

    return 0;
}
