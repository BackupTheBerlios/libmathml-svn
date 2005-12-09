#include "mathmlview2.h"

#include <mathml/mmldocument.h>
#include <mathml/constmathcursor.h>
#include <QPainter>
#include <QMatrix>
#include <QMouseEvent>
using namespace std;

MathMLView2::MathMLView2(QWidget *parent)
	: QWidget(parent) {
    // the size of the widget is fixed
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // we have a buffered widget
    setAttribute(Qt::WA_NoBackground, true);
	m_doc = NULL;
	m_scale = 1;
	setFocusPolicy(Qt::StrongFocus);
    m_mmlimg.setOutline(false);
    QColor c = palette().background().color();
    m_mmlimg.setBackgroundColor(c.red()/256.0, c.green()/256.0, c.blue()/256.0);
//    void setForeGroundColor(float, float, float);
    // initialize the font
    changeFont(font());
}
MathMLView2::~MathMLView2() {
	if (m_doc) {
		delete m_doc;
	}
}
void
MathMLView2::setDocument(const MMLDocument *d) {
	if (m_doc == d) return;

    // remove the image, because it references the buffer
    m_img = QImage();
    if (m_doc) {
        delete m_doc;
	}
	m_doc = d;
    m_mmlimg.setDocument(m_doc);
    updatePix();
}
void
MathMLView2::updatePix() {
    if (m_doc) {
        uchar *data = m_mmlimg.getPixmap();
        int lw, lh;
        if (data) {
            lw = m_mmlimg.getWidth();
            lh = m_mmlimg.getHeight();
            m_img = QImage(data, lw, lh, QImage::Format_ARGB32_Premultiplied);
        } else {
            m_img = QImage();
            lw = lh = 0;
        }
        if (lw*m_scale != width() || lh*m_scale != m_scale*height()) {
            updateGeometry();
        }
        update();
    }
}
void
MathMLView2::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.scale(m_scale, m_scale);
    p.drawImage(0, 0, m_img);
}
void
MathMLView2::changeFont(const QFont &f) {
    float size = font().pointSizeF();
    if (size == -1) {
        // there are 72 points per inch
        size = font().pixelSize()*72.0/logicalDpiX();
    }
    m_mmlimg.setFont((const char*)font().family().toUtf8(), size);
	setFont(f);
    updatePix();
}
void
MathMLView2::changeZoom(float s) {
    if (m_scale != s) {
	    m_scale = s;
        updateGeometry();
    }
}
void
MathMLView2::setOutline(bool o) {
	m_mmlimg.setOutline(o);
    updatePix();
}
void
MathMLView2::mousePressEvent(QMouseEvent *e) {
	setFocus();
	if (m_doc) {
        float x = e->x()/m_scale;
        float y = e->y()/m_scale;
        m_mmlimg.getCoords(x, y);
        bool change;
		if (e->modifiers() == Qt::ShiftModifier) {
			change = m_doc->constcursor()->selectTo(x, y);
		} else {
			change = m_doc->constcursor()->moveTo(x, y);
		}
		if (change) {
			emit cursorChanged();
            m_mmlimg.repaint();
            updatePix();
		}
	}
}
void
MathMLView2::mouseMoveEvent ( QMouseEvent *e  ) {
	setFocus();
	if (m_doc) {
		float x = e->x()/m_scale;
		float y = e->y()/m_scale;
        m_mmlimg.getCoords(x, y);
		bool change = m_doc->constcursor()->selectTo(x, y);
		if (change) {
            m_mmlimg.repaint();
            updatePix();
		}
	}
}
void
MathMLView2::keyPressEvent(QKeyEvent *e) {
	if (m_doc) {
		ConstMathCursor *c = m_doc->constcursor();
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
            m_mmlimg.repaint();
            updatePix();
		}
		printf("%s\n", c->container()->nodeName());
	}
}
void
MathMLView2::focusOutEvent ( QFocusEvent * event ) {
    printf("focus out\n");
    if (m_doc) {
        m_doc->constcursor()->setBeforeNode(0);
    }
}
