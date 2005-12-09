#include "mathmlview.h"

#include "qmmlpainter.h"
#include <mathml/mmldocument.h>
#include <mathml/constmathcursor.h>
#include <QPainter>
#include <QMatrix>
#include <QMouseEvent>
using namespace std;

MathMLView::MathMLView(QWidget *parent)
	: QWidget(parent) {
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setAttribute(Qt::WA_NoBackground, true);
	resize(100, 100);
	doc = NULL;
	scale = 1;
	setFocusPolicy(Qt::StrongFocus);
    mmlpix.setOutline(false);
    mmlpix.setFont(font());
    mmlpix.setPalette(palette());
}
MathMLView::~MathMLView() {
	if (doc) {
		delete doc;
	}
}
void
MathMLView::setDocument(const MMLDocument *d) {
	if (doc != d) {
		delete doc;
	}
	doc = d;
	if (doc) {
        mmlpix.setDocument(doc);
        updatePix();
	} else {
		pix = QPixmap();
	}
    updateGeometry();
}
void
MathMLView::updatePix() {
    if (doc) {
        mmlpix.setFont(font());
        mmlpix.setPalette(palette());
        pix = mmlpix.getPixmap();
    }
}
void
MathMLView::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.scale(scale, scale);
    p.drawPixmap(0, 0, pix);
}
void
MathMLView::changeFont(const QFont &f) {
	setFont(f);
    updatePix();
    updateGeometry();
}
void
MathMLView::changeZoom(float s) {
	scale = s;
    updateGeometry();
}
void
MathMLView::setOutline(bool o) {
	mmlpix.setOutline(o);
    updatePix();
    update();
}
void
MathMLView::mousePressEvent(QMouseEvent *e) {
	setFocus();
	if (doc) {
        float x = e->x()/scale;
        float y = e->y()/scale;
        QPointF p = mmlpix.getCoords(x, y);
        bool change;
		if (e->modifiers() == Qt::ShiftModifier) {
			change = doc->constcursor()->selectTo(p.x(), p.y());
		} else {
			change = doc->constcursor()->moveTo(p.x(), p.y());
		}
		if (change) {
			emit cursorChanged();
            mmlpix.repaint();
            updatePix();
            update();
		}
	}
}
void
MathMLView::mouseMoveEvent ( QMouseEvent *e  ) {
	setFocus();
	if (doc) {
		float x = e->x()/scale;
		float y = e->y()/scale;
        QPointF p = mmlpix.getCoords(x, y);
		bool change = doc->constcursor()->selectTo(p.x(), p.y());
		if (change) {
            mmlpix.repaint();
            updatePix();
            update();
		}
	}
}
void
MathMLView::keyPressEvent(QKeyEvent *e) {
	if (doc) {
		ConstMathCursor *c = doc->constcursor();
		bool change = true;
		if (e->modifiers() == Qt::ShiftModifier) {
			switch (e->key()) {
			case Qt::Key_Up:
				//n = c->moveUp();
				break;
			case Qt::Key_Down:
				//n = c->moveDown();
				break;
			case Qt::Key_Left:
				c->selectPrevious();
				break;
			case Qt::Key_Right:
				c->selectNext();
				break;
			default:
				change = false;
				break;
			}
		} else {
			switch (e->key()) {
			case Qt::Key_Up:
				c->moveUp();
				break;
			case Qt::Key_Down:
				c->moveDown();
				break;
			case Qt::Key_Left:
				c->movePrevious();
				break;
			case Qt::Key_Right:
				c->moveNext();
				break;
			default:
				change = false;
				break;
			}
		}
		if (change) {
			emit cursorChanged();
            mmlpix.repaint();
            updatePix();
            update();
		}
		printf("%s\n", c->container()->nodeName());
	}
}
