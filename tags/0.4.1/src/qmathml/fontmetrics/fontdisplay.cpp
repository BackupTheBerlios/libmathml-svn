#include "fontdisplay.h"
#include <QPainter>
#include <QPicture>
#include <QFontMetricsF>
#include <cstdio>

FontDisplay::FontDisplay(bool bug, bool direct) {
    m_bug = bug;
    m_direct = direct;
    m_border = 4;
}

void
FontDisplay::drawText(QPaintDevice *dev, const float border) const {

    // set up the painter
    QPainter p(dev);
    p.setFont(font());
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(border, border);

    // determine the bounding box
    QRectF textbox;
    float ascent, descent;
    QFontMetricsF *fm;
    if (m_bug) {
        fm = new QFontMetricsF(p.font());
    } else {
        fm = new QFontMetricsF(font());
    }
    textbox = fm->boundingRect(m_text);
    ascent = fm->ascent();
    descent = fm->descent();
    delete fm;

    // translate the painter with respect to the font baseline
    // float yoff = -textbox.y();
    p.translate(0, (int)ascent);

    // draw the ascent and the descent
    p.fillRect(QRectF(textbox.x(), 0, textbox.width(), descent), Qt::red);
    p.fillRect(QRectF(textbox.x(), -ascent, textbox.width(), ascent), Qt::red);

    // draw string on its boundingRect
    p.fillRect(textbox, Qt::blue);
    p.drawText(QPointF(0, 0), m_text);

    // draw the baseline
    // p.fillRect(QRectF(textbox.x(), -0.5, textbox.width(), 1), Qt::yellow);

    p.end();
}

void
FontDisplay::setText(const QString &text) {
    m_text = text;
    drawText();
}
void
FontDisplay::drawText() {

    // draw the string to a picture
    QPicture pict;
    drawText(&pict, 0);

    // create a pixmap to draw the string on
    QRect pictrect = pict.boundingRect();
    int border = 4;
    int w = pict.width()+2*border;
    int h = pict.height()+2*border;
    QPixmap pix(w, h);
    pix.fill();

    // draw the string to a pixmap
    if (m_direct) {
        drawText(&pix, m_border);
    } else {
        QPainter p(&pix);
        p.drawPicture(QPointF(border, border), pict);
        p.end();
    }

    // blow up the image
    QImage qi = pix.toImage();
    qi = qi.scaled(pix.width()*4, pix.height()*4);
    pix = pix.fromImage(qi);

    // draw the image
    setPixmap(pix);
    update();
}
void
FontDisplay::setBold(bool b) {
    QFont f = font();
    f.setBold(b);
    setFont(f);
    drawText();
}
void
FontDisplay::setItalic(bool i) {
    QFont f = font();
    f.setItalic(i);
    setFont(f);
    drawText();
}
void
FontDisplay::setPointSize(int size) {
    QFont f = font();
    f.setPointSize(size);
    setFont(f);
    drawText();
}
