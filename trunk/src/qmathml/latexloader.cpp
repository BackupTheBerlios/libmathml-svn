#include "latexloader.h"
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QPixmap>
#include <QApplication>
#include <cstdlib>

LatexLoader::LatexLoader(QObject *parent)
		: QObject(parent) {
    latex = new QProcess(parent);
    connect(latex, SIGNAL(finished(int exitCode)), this, SLOT(processExited()));
    cmd = qApp->applicationDirPath() + "/../share/libmathml/xsltml/mml2png.sh";
    char dirname[16];
    strcpy(dirname, "/tmp/mmlXXXXXX");
    if (mkdtemp(dirname) != 0) {
        tempdir = dirname;
    }
}
LatexLoader::~LatexLoader() {
    if (!QDir("/tmp").rmdir(tempdir.absolutePath())) {
	printf("Could not remove %s.\n",
		(const char*)tempdir.absolutePath().toUtf8());
    }
    delete latex;
}
void
LatexLoader::parseData(const QString &data) {
    // write the xml to the temporary file
    QString filepath = tempdir.absoluteFilePath("temp");
	QFile f(filepath);
    f.open(QIODevice::WriteOnly);
	QTextStream str(&f);
	str << data;
	f.close();

	img = QImage();
    delete latex;
    latex = new QProcess(this);
    connect(latex, SIGNAL(finished(int)), this, SLOT(processExited()));
    QStringList args;
    args.push_back(cmd);
    args.push_back(filepath);
    imgname = filepath+".png";
    latex->start("sh", args);
}
QImage
LatexLoader::getImage() const {
	return img;
}
bool
LatexLoader::isEmptyRow(const QImage &img, int row, QRgb c) const {
	bool empty = true;
	for (int i=x; empty && i<w; ++i) {
		empty &= img.pixel(i, row) == c;
	}
	return empty;
}
bool
LatexLoader::isEmptyCol(const QImage &img, int col, QRgb c) const {
	bool empty = true;
	for (int i=y; empty && i<h; ++i) {
		empty &= img.pixel(col, i) == c;
	}
	return empty;
}
void
LatexLoader::getBackgroundColor(const QImage &img) {
	// obtain colors of four corners
	QRgb tl = img.pixel(0,0);
	QRgb bl = img.pixel(0,h-1);
	QRgb tr = img.pixel(w-1, 0);
	QRgb br = img.pixel(w-1, h-1);
	if (tl == bl && isEmptyCol(img, 0, tl)) {
		bg = tl;
	} else if (tl == tr && isEmptyRow(img, 0, tl)) {
		bg = tl;
	} else if (bl == br && isEmptyRow(img, h-1, bl)) {
		bg = bl;
	} else {
		bg = tr;
	}
	bgr = qRed(bg);
	bgg = qGreen(bg);
	bgb = qBlue(bg);
}
void
LatexLoader::cropImage(QImage &img) {
	x = 0;
	y = 0;
	w = img.width();
	h = img.height();
	getBackgroundColor(img);
	bool empty = true;
	for (; empty && x<w;) {
		empty &= isEmptyCol(img, x, bg);
		if (empty) ++x;
	}
	empty = true;
	for (; empty && w-x>0;) {
		empty &= isEmptyCol(img, w-1, bg);
		if (empty) --w;
	}
	empty = true;
	for (; empty && y<h;) {
		empty &= isEmptyRow(img, y, bg);
		if (empty) ++y;
	}
	empty = true;
	for (; empty && h-y>0;) {
		empty &= isEmptyRow(img, h-1, bg);
		if (empty) --h;
	}
	w -= x;
	h -= y;
	img = img.copy(x, y, w, h);
}
float
LatexLoader::getMinAlpha(float c, float b) const {
	float a = 1;
	if (b == c) {
		a = 0;
	} else if (b != 0 && b > c) {
		a = 1-c/b;
	} else if (b != 255 && c > b) {
		a = (c-b)/(255-b);
	}
	return a;
}
int
LatexLoader::getOrigColor(float a, float c, float b) const {
	if (a > 0 && a < 1) {
		c = (c-b)/a + b;
	}
	return int(c+0.5);
}
QRgb
LatexLoader::addTransparency(QRgb &c) const {
	int r = qRed(c);
	int g = qGreen(c);
	int b = qBlue(c);
	float ra = getMinAlpha(r, bgr);
	float ga = getMinAlpha(g, bgg);
	float ba = getMinAlpha(b, bgb);
	float a = (ra > ga) ?ra :ga;
	a = (a > ba) ?a :ba;
	r = getOrigColor(a, r, bgr);
	g = getOrigColor(a, g, bgg);
	b = getOrigColor(a, b, bgb);
	return qRgba(r, g, b, int(a*255+0.5));
}
void
LatexLoader::addTransparency(QImage &img) const {
    if (img.isNull()) return;
    img = img.convertToFormat(QImage::Format_ARGB32);
    QRgb p;
	for (int i=0; i<w; ++i) {
		for (int j=0; j<h; ++j) {
            p = img.pixel(i,j);
            p = addTransparency(p);
			img.setPixel(i, j, p);
		}
	}
}
QImage
LatexLoader::cleanse(const QImage &i) {
	QImage j = i;
	cropImage(j);
	addTransparency(j);
	return j;
}
void
LatexLoader::processExited() {
     if (latex->exitCode() == 0) {
         if (img.load(imgname)) {
            cropImage(img);
            addTransparency(img);
            emit readImage(QPixmap::fromImage(img));
        }
     }
     printf("%s", (const char*)latex->readAllStandardError());
     QFile(imgname).remove();
}
