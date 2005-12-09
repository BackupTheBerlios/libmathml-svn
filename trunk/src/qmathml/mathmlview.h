#ifndef MATHMLVIEW_H
#define MATHMLVIEW_H

#include "mmlpixmap.h"
#include <QWidget>
class MMLDocument;

class MathMLView : public QWidget {
Q_OBJECT
public:
	MathMLView(QWidget *parent);
	~MathMLView();
	void setDocument(const MMLDocument *);
	void changeFont(const QFont &);
	void changeZoom(float);
    QSize sizeHint() const {
        return scale*pix.size();
    }
signals:
	void cursorChanged();
public slots:
	void setOutline(bool);
protected:
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent ( QMouseEvent * e );
	void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
private:
	float scale;
	const MMLDocument *doc;
    QPixmap pix;
    MMLPixmap mmlpix;

    void updatePix();
};

#endif
