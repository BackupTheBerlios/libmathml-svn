#include "cairopainter.h"
#include <mathml/domstring.h>
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

CairoPainter::CairoPainter() {
    absx = absy = 0;
    debugdrawtext = false;
    fittext = true;

    m_seriffont = "serif";
    m_sansseriffont = "sans-serif";
    m_scriptfont = "script";
    m_monofont = "monospace";
    m_foreground.setRgb(0,0,0);
    m_background.setRgb(255,255,255);
    m_highlight.setRgb(255,0,0);
    m_selection.setRgb(0,255,0);
    m_fontsize = 12;
}
void
CairoPainter::setPainter(cairo_t *p) {
    m_painter = p;
    // initialise the painter
    cairo_set_antialias(m_painter, CAIRO_ANTIALIAS_GRAY);
    setFont(m_seriffont, m_fontsize);
}
void
CairoPainter::setFont(const std::string &family, float size) {
    m_seriffont = family;
    m_fontsize = size;
    cairo_select_font_face(m_painter, m_seriffont.c_str(),
        CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(m_painter, size);
    cairo_font_extents(m_painter, &m_fontmetrics);
}
void
CairoPainter::setOutline(bool outline) {
    debugdrawtext = outline;
}
void
CairoPainter::setBackground(uint r, uint g, uint b) {
    m_background.setRgb(r, g, b);
}
float
CairoPainter::dpi(bool /* horizontal */) const {
    return 72;//pango_cairo_context_get_resolution(m_pango);
}
float
CairoPainter::fontAscent() const {
    return m_fontmetrics.ascent;
}
float
CairoPainter::fontDescent() const {
    return m_fontmetrics.descent;
}
float
CairoPainter::stringWidth(const DOMString &s) const {
    cairo_text_extents(m_painter, s.utf8(), &m_textsize);
    return m_textsize.width;
}
/* Em
 * A font-relative measure encoded by the font. Before electronic typesetting,
 * an "em" was the width of an "M" in the font. In modern usage, an "em" is
 * either specified by the designer of the font or is taken to be the height
 * (point size) of the font. Em's are typically used for font-relative
 * horizontal sizes. */
float
CairoPainter::em() const {
    return stringWidth("M");
}
/* Ex
 * A font-relative measure that is the height of an "x" in the font. "ex"s are
 * typically used for font-relative vertical sizes. */
float
CairoPainter::ex() const {
    cairo_text_extents(m_painter, "x", &m_textsize);
    return m_textsize.height;
}
MathColor
CairoPainter::mathColor() const {
    return m_foreground;
}
MathColor
CairoPainter::highlightColor(uchar level) const {
    MathColor mc;
    int r, g, b;
    int lm = int(pow(2,level));
    r = (m_highlight.r() - m_background.r())/lm + m_background.r();
    g = (m_highlight.g() - m_background.g())/lm + m_background.g();
    b = (m_highlight.b() - m_background.b())/lm + m_background.b();
    mc.setRgb(r, g, b);
    return mc;
}
MathColor
CairoPainter::selectionColor() const {
    return m_selection;
}
void
CairoPainter::setMathVariant(mathvariant::Mathvariant mv) {
    using namespace mathvariant;
    switch (mv) {
    case (NORMAL):
        cairo_select_font_face(m_painter, m_seriffont.c_str(),
            CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        break;
    case (BOLD):
        cairo_select_font_face(m_painter, m_seriffont.c_str(),
            CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        break;
    case (ITALIC):
        cairo_select_font_face(m_painter, m_seriffont.c_str(),
            CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_NORMAL);
        break;
    case (BOLD_ITALIC):
        cairo_select_font_face(m_painter, m_seriffont.c_str(),
            CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_BOLD);
        break;
    case (DOUBLE_STRUCK): break;
    case (BOLD_FRAKTUR): break;
    case (SCRIPT):
        cairo_select_font_face(m_painter, m_scriptfont.c_str(),
            CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        break;
    case (BOLD_SCRIPT):
        cairo_select_font_face(m_painter, m_scriptfont.c_str(),
            CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        break;
    case (FRAKTUR): break;
    case (SANS_SERIF):
        cairo_select_font_face(m_painter, m_sansseriffont.c_str(),
            CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        break;
    case (BOLD_SANS_SERIF):
        cairo_select_font_face(m_painter, m_sansseriffont.c_str(),
            CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        break;
    case (SANS_SERIF_ITALIC):
        cairo_select_font_face(m_painter, m_sansseriffont.c_str(),
            CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_NORMAL);
        break;
    case (SANS_SERIF_BOLD_ITALIC):
        cairo_select_font_face(m_painter, m_sansseriffont.c_str(),
            CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_BOLD);
        break;
    case (MONOSPACE):
        cairo_select_font_face(m_painter, m_monofont.c_str(),
            CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        break;
    }
    cairo_font_extents(m_painter, &m_fontmetrics);
}
void
CairoPainter::setMathColor(MathColor mc) {
    if (mc.isTransparent()) {
        // mathcolor cannot be transparent, only background can
        cairo_set_source_rgba(m_painter, 0, 0, 0, 1);
    } else {
        cairo_set_source_rgb(m_painter, mc.r()/256.0, mc.g()/256.0,
            mc.b()/256.0);
    }
}
void
CairoPainter::setMathBackground(MathColor mc) {
//    m_background = mc;
}
void
CairoPainter::setFontSize(float pt) {
    m_fontsize = pt;
    cairo_set_font_size(m_painter, pt);
    cairo_font_extents(m_painter, &m_fontmetrics);
}
void
CairoPainter::setLineThickness(float t) { // thickness in px
    cairo_set_line_width(m_painter, t);
}
float
CairoPainter::fontSize() const {
    return m_fontsize;
}
void
CairoPainter::drawLine(float x1, float y1, float x2, float y2,
        float linethickness) {
    if (linethickness <= 0) {
        linethickness = 1;
    }
    float t = cairo_get_line_width(m_painter);
    cairo_set_line_width(m_painter, linethickness);

    cairo_move_to(m_painter, x1+absx, y1+absy);
    cairo_line_to(m_painter, x2+absx, y2+absy);
    cairo_stroke(m_painter);

    cairo_set_line_width(m_painter, t);
}
void
CairoPainter::drawRect(float x, float y, float w, float h) {
    cairo_rectangle(m_painter, x+absx, y+absy, w, h);
    cairo_stroke(m_painter);
}
void
CairoPainter::fillRect(float x, float y, float w, float h, const MathColor &bg,
        const MathColor &fg) {
    cairo_save(m_painter);
    setMathColor(bg);
    cairo_rectangle(m_painter, x+absx, y+absy, w, h);
    cairo_fill(m_painter);
    setMathColor(fg);
    cairo_rectangle(m_painter, x+absx, y+absy, w, h);
    cairo_stroke(m_painter);
    cairo_restore(m_painter);
}
void
CairoPainter::fillParallelogram(float x1, float y1, float x2, float y2,
        float x3, float y3) {
    x1 += absx;
    y1 += absy;
    x2 += absx;
    y2 += absy;
    cairo_move_to(m_painter, x1, y1);
    cairo_line_to(m_painter, x1, y2);
    cairo_line_to(m_painter, x2, y2);
    cairo_line_to(m_painter, x2, y1);
    cairo_line_to(m_painter, x1, y1);
    cairo_fill(m_painter);
}
void
CairoPainter::drawPolygon(int n, float *x, float *y) {
    if (n <= 0) return;

    cairo_move_to(m_painter, x[n-1]+absx, y[n-1]+absy);
    for (int i=0; i<n; ++i) {
        cairo_line_to(m_painter, x[i]+absx, y[i]+absy);
    }
    cairo_fill(m_painter);
}
void
CairoPainter::drawText(const DOMString &s) {
    if (debugdrawtext) {
        drawOutline(stringWidth(s));
    }
    cairo_move_to(m_painter, absx, absy);
    cairo_show_text(m_painter, s.utf8());
}
/* draw the string s with current font, but stretch it to fit the given
   width (a+d). We haven't implemented stretching, so i just center the character. */
void
CairoPainter::drawText(const DOMString &s, float w) {
    float sw = stringWidth(s) + absx; // this can't be right
    float hdiff = w - sw;
    cairo_move_to(m_painter, hdiff/2+absx, absy);
    cairo_show_text(m_painter, s.utf8());
}
/* draw the string s with current font, but stretch it to fit the given
   height (a+d). Keep the width the same as the width specified by
   stringWidth(s); */
void
CairoPainter::drawText(const DOMString &s, float a, float d) {
    drawText(s);
}
void
CairoPainter::drawOutline(float w) {
    float a = fontAscent();
    float d = fontDescent();
     // total character area
    cairo_save(m_painter);
    cairo_set_source_rgb(m_painter, 1, 0, 0);
    cairo_rectangle(m_painter, absx, absy-a, w, a);
    cairo_fill(m_painter);
    cairo_set_source_rgb(m_painter, 0, 0, 1);
    cairo_rectangle(m_painter, absx, absy, w, d);
    cairo_fill(m_painter);
    cairo_restore(m_painter);
}
void
CairoPainter::drawText(const DOMString &s, float w, float a, float d) {
    float sw = stringWidth(s);
    float hdiff = w-sw;
    float fa = fontAscent();
    float fd = fontDescent();
    float vdiff = d-fd - a+fa;
    cairo_move_to(m_painter, hdiff/2, vdiff/2);
    cairo_show_text(m_painter, s.utf8());
}
void
CairoPainter::translate(float x, float y) {
    absx += x;
    absy += y;
}
