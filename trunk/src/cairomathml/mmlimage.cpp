#include "mmlimage.h"
#include <mathml/mmldocument.h>
#include <cmath>

MMLImage::MMLImage() {
    m_border = 4;
    m_outline = true;
    m_mustLayout = true;
    m_mustPaint = true;
    m_doc = 0;
    m_foreground[0] = 0;
    m_foreground[1] = 0;
    m_foreground[2] = 0;
    m_background[0] = 1;
    m_background[1] = 1;
    m_background[2] = 1;
    m_background[3] = 1;

    m_w = m_h = m_dataw = m_datah = 1;
    m_data = 0;
    resize(1, 1);
}
MMLImage::~MMLImage() {
    delete [] m_data;
    cairo_destroy(m_cpainter);
    cairo_surface_destroy(m_buffer);
}
void
MMLImage::resize(int w, int h) {
    if (m_data) {
        cairo_destroy(m_cpainter);
        cairo_surface_destroy(m_buffer);
        delete [] m_data;
    }

    // allocate a buffer
    m_data = new unsigned char[m_w*m_h*4];
    m_buffer = cairo_image_surface_create_for_data(m_data,
        CAIRO_FORMAT_ARGB32, m_w, m_h, 4*m_w);
    m_dataw = m_w;
    m_datah = m_h;
    m_cpainter = cairo_create(m_buffer);
    m_painter.setPainter(m_cpainter);
}
void
MMLImage::setDocument(const MMLDocument *doc) {
    m_doc = doc;
    m_mustLayout = true;
}
void
MMLImage::layout() {
    m_doc->setPainter(&m_painter);
    m_doc->layout();

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
MMLImage::repaint() {
    if (m_mustLayout) layout();

    if (m_dataw != m_w || m_datah != m_h) {
        resize(m_w, m_h);
    }

    // initialize the buffer and painter
    cairo_set_source_rgba(m_cpainter, m_background[0], m_background[1],
        m_background[2], m_background[3]);
    cairo_rectangle(m_cpainter, 0, 0, m_w, m_h);
    cairo_fill(m_cpainter);
    cairo_set_line_width(m_cpainter, 1);
    cairo_set_source_rgb(m_cpainter, m_foreground[0], m_foreground[1],
        m_foreground[2]);
    cairo_translate(m_cpainter, m_border, m_ascent + m_border);

    // paint all the views below each other
    for (ushort i=0; i < m_doc->countViewPorts(); ++i) {
        m_doc->setCurrentView(i);
        m_doc->paint();
    }

    // paint a border
    if (m_outline) {
/*        QPen pen = m_qpainter.pen();
        pen.setColor(Qt::red);
        pen.setWidthF(1);
        m_qpainter.setPen(pen);
        w -= 2*m_border;
        h -= 2*m_border;
        m_qpainter.drawRect(QRectF(-0.5, -m_ascent-0.5, w+1, h+1));*/
    }
//    m_qpainter.end();

    cairo_translate(m_cpainter, -m_border, -m_ascent - m_border);

    m_mustPaint = false;
}
uchar *
MMLImage::getPixmap() {
    if (m_mustLayout || m_mustPaint) repaint();
    return m_data;
}
cairo_surface_t*
MMLImage::getSurface() {
    if (m_mustLayout || m_mustPaint) repaint();
    return m_buffer;
}
void
MMLImage::setFont(const std::string &name, float size) {
    if (name != m_fontname || size != m_fontsize) {
        m_fontname = name;
        m_fontsize = size;
        m_mustLayout = true;
        m_painter.setFont(name, size);
    }
}
void
MMLImage::setBackgroundColor(float r , float g , float b, float a) {
    printf("setbackgroundcolor\n");
    m_background[0] = r;
    m_background[1] = g;
    m_background[2] = b;
    m_background[3] = a;
    m_painter.setBackground((uint)(r*256.0), (uint)(g*256.0), (uint)(b*256.0), (uint)(a*256.0));
}
void 
MMLImage::setForeGroundColor(float r, float g, float b) {
    m_foreground[0] = r;
    m_foreground[1] = g;
    m_foreground[2] = b;
}

