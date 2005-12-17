#include "mmlpixmap.h"
#include <mathml/mmldocument.h>
#include <cmath>

MMLPixmap::MMLPixmap() {
    m_border = 4;
    m_outline = false;
    m_mustLayout = true;
    m_mustPaint = true;
    m_doc = 0;
    m_buffer = QPixmap(1, 1);
    m_painter.setPainter(&m_qpainter);
    m_background = m_qpainter.background().color();
}
void
MMLPixmap::setDocument(const MMLDocument *doc) {
    m_doc = doc;
    m_mustLayout = true;
}
void
MMLPixmap::setFont(const QFont &font) {
    if (m_font != font) {
        m_mustLayout = true;
        m_font = font;
    }
}
void
MMLPixmap::layout() {
    m_qpainter.begin(&m_buffer);
    m_qpainter.setRenderHint(QPainter::Antialiasing);
    m_qpainter.setFont(m_font);

    m_doc->setPainter(&m_painter);
    m_doc->layout();
    m_qpainter.end();

    // obtain the dimensions of the document
    float ascent = 0;
    float height = 0;
    float maxwidth = 0;
    bool more = true;
    int view = 0;
    do {
        m_doc->setCurrentView(view++);
        m_doc->setX(0);
        m_doc->setY(height);
        more = m_doc->setMaxViewWidth(1000);
        ascent += m_doc->getAscent();
        height += m_doc->getHeight();
        float w = m_doc->getWidth();
        if (w > maxwidth) maxwidth = w;
    } while (more);
    m_ascent = (int)ceil(ascent);
    m_w = int(ceil(maxwidth + 2*m_border));
    m_h = int(ceil(height + 2*m_border));
    if (m_w > 1000) m_w = 1000;
    if (m_h > 1000) m_h = 1000;

    m_mustLayout = false;
}
void
MMLPixmap::repaint() {
    if (m_mustLayout) layout();

    if (m_buffer.width() != m_w || m_buffer.height() != m_h) {
        m_buffer = QPixmap(m_w, m_h);
    }

    // initialize the buffer and painter
    m_buffer.fill(m_background);
    m_qpainter.begin(&m_buffer);
    m_qpainter.setRenderHint(QPainter::Antialiasing);
    m_qpainter.setFont(m_font);
    m_qpainter.setBackground(m_painter.getPalette().background());
    int w = m_buffer.width();
    int h = m_buffer.height();
    m_qpainter.translate(m_border, m_ascent + m_border);

    // paint all the views below each other
    for (ushort i=0; i < m_doc->countViewPorts(); ++i) {
        m_doc->setCurrentView(i);
        m_doc->paint();
    }

    // paint a border
    if (m_outline) {
        QPen pen = m_qpainter.pen();
        pen.setColor(Qt::red);
        pen.setWidthF(1);
        m_qpainter.setPen(pen);
        w -= 2*m_border;
        h -= 2*m_border;
        m_qpainter.drawRect(QRectF(-0.5, -m_ascent-0.5, w+1, h+1));
    }
    m_qpainter.end();
    m_mustPaint = false;
}
const QPixmap &
MMLPixmap::getPixmap() {
    if (m_mustLayout || m_mustPaint) repaint();
    return m_buffer;
}
