#ifndef LATEXLOADER
#define LATEXLOADER

#include <QObject>
#include <QImage>
#include <QDir>
class QProcess;

class LatexLoader : public QObject {
Q_OBJECT
public:
	LatexLoader(QObject *parent=0);
	~LatexLoader();
	void parseData(const QString &data);
	QImage getImage() const;
	QImage cleanse(const QImage &);
signals:
	void readImage(const QPixmap &);
private:
	int x, y, w, h;
	QRgb bg;
	int bgr, bgg, bgb;

	QProcess *latex;
	QString cmd;
	QImage img;
	QString imgname;
    QDir tempdir;

	void addTransparency(QImage &img) const;
	QRgb addTransparency(QRgb &c) const;
	int getOrigColor(float a, float c, float b) const;
	float getMinAlpha(float c, float b) const;
	void cropImage(QImage &img);
	void getBackgroundColor(const QImage &img);
	bool isEmptyCol(const QImage &img, int col, QRgb c) const;
	bool isEmptyRow(const QImage &img, int row, QRgb c) const;
private slots:
	void processExited();
};

#endif
