#include "cairotest.h"
#include <QPainter>

CairoTest::CairoTest() {
    setAttribute(Qt::WA_NoBackground, true);
}

void
CairoTest::drawPath(cairo_t *cr, int w, int h) {
    cairo_set_line_width(cr, (w>h) ?h/10.0 : w/10.0);
    cairo_move_to (cr, 0.5*w, 0.1*h);
    cairo_line_to (cr, 0.9*w, 0.9*h);
    cairo_rel_line_to (cr, -0.4*w, 0.0);
    cairo_curve_to (cr, 0.2*w, 0.9*h, 0.2*w, 0.5*h, 0.5*w, 0.5*h);
    cairo_stroke (cr);
}

void
CairoTest::resizeEvent(QResizeEvent* event) {
    int w = width();
    int h = height();

    // create a buffer
    m_buffer = QImage(w, h, QImage::Format_ARGB32_Premultiplied);
    uchar *bits = m_buffer.bits();

    // initialize cairo
    cairo_surface_t *cs = cairo_image_surface_create_for_data(bits,
        CAIRO_FORMAT_ARGB32, w, h, 4*w);
    cairo_t *c = cairo_create(cs);
    QColor bg = palette().color(QPalette::Background);
    cairo_set_source_rgb(c, bg.redF(), bg.greenF(), bg.blueF());
    cairo_rectangle(c, 0, 0, w, h);
    cairo_fill(c);
    QColor fg = palette().color(QPalette::Foreground);
    cairo_set_source_rgb(c, fg.redF(), fg.greenF(), fg.blueF());

    // do the drawing
    drawPath(c, w, h);

    // clean up
    cairo_destroy(c);
    cairo_surface_destroy(cs);
}
void
CairoTest::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.drawImage(0, 0, m_buffer);
}
