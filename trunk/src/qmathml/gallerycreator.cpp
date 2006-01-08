#include "mmlpixmap.h"
#ifdef HAVE_CAIRO
#include "mmlimage.h"
#endif
#include "mmlreader.h"
#include "mathml/mmldocument.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QApplication>

MMLReader r;
MMLPixmap* pix;
MMLImage* img;
const QString srcdirpath(SRCDIR);
const QDir srcdir(srcdirpath);
const QDir suitedir(SRCDIR"/share/libmathml/testsuite");
const QDir baseout(QDir::currentPath() + QDir::separator() + "libmathml");
const QDir testout(QDir::currentPath() + QDir::separator() + "testsuite");
QTextStream out;
bool do_output = true;
bool do_q = false;
bool output_erroneous = false;

void
initPixmap() {
    pix = new MMLPixmap();
    QPalette p;
    p.setColor(QPalette::Background, QColor(255,255,255,0));
    pix->setPalette(p);

    pix->setFont(QFont("Nimbus Roman No9 L"));

#ifdef HAVE_CAIRO
    img = new MMLImage();
#endif
}
void
deletePixmap() {
    delete pix;
#ifdef HAVE_CAIRO
    delete img;
#endif
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
        out << "<p style='border-top: 1px solid black;border-bottom: 1px solid black'>"<<dir<<"</p>"<<endl;
        printedhead = true;
    }
}
void
renderFile(QString &path, QTextStream &out) {
//    deletePixmap();
//    initPixmap();
    QFileInfo f(path);
    QString outputdir = suitedir.relativeFilePath(f.absolutePath());
    baseout.mkpath(outputdir);
    testout.mkpath(outputdir);
    QString coutputfile = outputdir+"/"+f.baseName()+"c.png";
    QString coutputoutlinefile = outputdir+"/"+f.baseName()+"coutline.png";
    MMLDocument *doc = parse(path);
    if (doc->validate()) {
        printhead(outputdir);
        out << "<p>" << f.baseName();

        int valign;
        QString qoutputfile = outputdir+"/"+f.baseName()+"q.png";
        if (do_q) {
            QString qoutputoutlinefile = outputdir+"/"+f.baseName()+"qoutline.png";
            pix->setDocument(doc);
            pix->setOutline(false);
            QPixmap p = pix->getPixmap();
            if (do_output) {
                p.save("libmathml/"+qoutputfile, "PNG", 0);
            }
            pix->setOutline(true);
            p = pix->getPixmap();
            if (do_output) {
                p.save("libmathml/"+qoutputoutlinefile, "PNG", 0);
            }

            // calculate offset for the image, so that it aligns with the text
            valign = (int)-doc->getDescent() - 4 - 2;
            out << "_<img style='border:1px solid #E0E0E0;vertical-align:"
                << valign << "px;' src='libmathml/" << qoutputfile << "' "
                << "onmouseover='this.src=\"libmathml/" << qoutputoutlinefile
                << "\";' onmouseout='this.src=\"libmathml/" << qoutputfile
                << "\";' width='" << p.width() << "px' height='" << p.height()
                << "'/>_";
        }

#ifdef HAVE_CAIRO
        img->setDocument(doc);
        cairo_surface_t *surface = img->getSurface();
        QString outpath = "libmathml/"+coutputfile;
        cairo_surface_write_to_png(surface, outpath.toUtf8());
        img->setOutline(true);
        outpath = "libmathml/"+coutputoutlinefile;
        cairo_surface_write_to_png(surface, outpath.toUtf8());

        valign = (int)-doc->getDescent() - 4 - 2;

        out << " _<img style='border:1px solid #E0E0E0;vertical-align:"
            << valign << "px;' src='libmathml/" << coutputfile << "' "
            << "onmouseover='this.src=\"libmathml/" << coutputoutlinefile
            << "\";' onmouseout='this.src=\"libmathml/" << coutputfile
            << "\";' width='" << img->getWidth() << "px' height='" << img->getHeight()
            << "'/>_";
#endif

        QString orig = f.absolutePath() + QDir::separator() + f.baseName()
            + ".png";
        QString origcopy = "testsuite/" + qoutputfile;
        if (do_output) {
            // open file to get sizes
            QPixmap ref(orig);
            if (!ref.isNull()) {
            QFile::copy(orig, origcopy);
            int cvalign =
                -(int)(doc->getDescent()/doc->getHeight()*ref.height());
            if (cvalign > 0 || cvalign < -1000) {
                cvalign = - ref.height()/2;
            }
            out << " _<img style='border:1px solid #E0E0E0;vertical-align:"
                << cvalign << "px;' src='" << origcopy << "' width='"
                << ref.width() << "px' height='" << ref.height() << "'/>";
            }
        }
        out << "</p>" << endl;
    } else if (output_erroneous) {
        printhead(outputdir);
        out << "<p>" << f.baseName() << " ";
        out << doc->errorMsg().utf8();
        out << "</p>" << endl;
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
            renderFile(path, out);
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

    initPixmap();

    if (argc > 1) {
        for (int i=1; i<argc; ++i) {
            QString path(argv[i]);
            QFileInfo fileinfo(argv[i]);
            MMLDocument *doc = parse(path);
            doc->validate();
            if (do_q) {
                pix->setDocument(doc);
                pix->setOutline(false);
                QPixmap p = pix->getPixmap();
                if (do_output) {
                    p.save(fileinfo.baseName()+"q.png", "PNG");
                }
                printf("%i, %i\n", p.width(), p.height());
            }

#ifdef HAVE_CAIRO
            img->setDocument(doc);
            cairo_surface_t *surface = img->getSurface();
            QString filepath = fileinfo.baseName()+"c.png";
            cairo_surface_write_to_png(surface, filepath.toUtf8());
#endif

            delete doc;
        }
    } else {
        QFile htmloutput("gallery.html");
        htmloutput.open(QIODevice::WriteOnly);
        out.setDevice(&htmloutput);
        out << "<html><body style='background:#FAFAFA;'>";
        renderTestSuite();
        out << "</body></html>" << endl;
        htmloutput.close();
    }

    deletePixmap();

    return 0;
}
