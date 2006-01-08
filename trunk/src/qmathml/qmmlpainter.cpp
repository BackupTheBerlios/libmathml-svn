#include "qmmlpainter.h"
#include "qdomstring.h"
#include <QPainter>
#include <QPolygon>
#include <QFontDatabase>
#include <QFontMetricsF>
#include <QPainterPath>
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

QMMLPainter::QMMLPainter() {
    p = 0;
    absx = absy = 0;
    m_linethickness = 1;
    cout << "----" << endl;
    debugdrawtext = false;
    fittext = true;

    m_fontsize = 12;
    m_mathvariant = mathvariant::NORMAL;

    QFont f;
    f.setStyleHint(QFont::Serif);
    f.setFamily(f.defaultFamily());
    //setSerifFont(QFont("Nimbus Roman No9 L"));
    setSerifFont(f);
    f.setStyleHint(QFont::SansSerif);
    f.setFamily(f.defaultFamily());
    setSansSerifFont(f);
    f.setStyleHint(QFont::OldEnglish);
    f.setFamily(f.defaultFamily());
    setScriptFont(f);
    f.setStyleHint(QFont::TypeWriter);
    f.setFamily(f.defaultFamily());
    setMonoSpaceFont(f);
}
void
QMMLPainter::setSerifFont(QFont font) {
    font.setBold(false);
    font.setItalic(false);
    m_font.setFontType(mathvariant::NORMAL, font);
    font.setBold(true);
    m_font.setFontType(mathvariant::BOLD, font);
    font.setItalic(true);
    m_font.setFontType(mathvariant::BOLD_ITALIC, font);
    font.setBold(false);
    m_font.setFontType(mathvariant::ITALIC, font);
}
void
QMMLPainter::setSansSerifFont(QFont font) {
    font.setBold(false);
    font.setItalic(false);
    m_font.setFontType(mathvariant::SANS_SERIF, font);
    font.setBold(true);
    m_font.setFontType(mathvariant::BOLD_SANS_SERIF, font);
    font.setItalic(true);
    m_font.setFontType(mathvariant::SANS_SERIF_BOLD_ITALIC, font);
    font.setBold(false);
    m_font.setFontType(mathvariant::SANS_SERIF_ITALIC, font);
}
void
QMMLPainter::setMonoSpaceFont(QFont font) {
    m_font.setFontType(mathvariant::MONOSPACE, font);
}
void
QMMLPainter::setScriptFont(QFont font) {
    font.setBold(false);
    m_font.setFontType(mathvariant::SCRIPT, font);
    font.setBold(true);
    m_font.setFontType(mathvariant::BOLD_SCRIPT, font);
}
void
QMMLPainter::setFrakturFont(QFont font) {
    font.setBold(false);
    m_font.setFontType(mathvariant::FRAKTUR, font);
    font.setBold(true);
    m_font.setFontType(mathvariant::BOLD_FRAKTUR, font);
}
void
QMMLPainter::setDoubleStruckFont(QFont font) {
    m_font.setFontType(mathvariant::DOUBLE_STRUCK, font);
}
void
QMMLPainter::setPainter(QPainter *p) {
    this->p = p;
}
void
QMMLPainter::initializePainter() {
    if (!p || !p->isActive()) return;
    // adjust QPainter to setting of QMMLPainter
    setMathColor(m_mathcolor);
    setMathBackground(m_mathbackground);
    setLineThickness(m_linethickness);
    setMathvariant(mathvariant::NORMAL);
}
void
QMMLPainter::setOutline(bool outline) {
    debugdrawtext = outline;
}
float
QMMLPainter::dpi(bool horizontal) const {
    if (horizontal) {
        return p->device()->logicalDpiX();
    } else {
        return p->device()->logicalDpiY();
    }
}
float
QMMLPainter::fontAscent() const {
    return m_font.ascent();
}
float
QMMLPainter::fontDescent() const {
//    printf("fontDescent: %f, fontsize %f, fontname %s\n", fontmetrics.descent(), m_fontsize,
//        (const char *)p->font().family().toUtf8());
    return m_font.descent();
}
float
QMMLPainter::stringWidth(const DOMString &s) const {
    QString qs = qstring(s);
    QRectF r = m_font.boundingRect(qs);
    float w = r.width();
    return w;
}
/* Em
 * A font-relative measure encoded by the font. Before electronic typesetting,
 * an "em" was the width of an "M" in the font. In modern usage, an "em" is
 * either specified by the designer of the font or is taken to be the height
 * (point size) of the font. Em's are typically used for font-relative
 * horizontal sizes. */
float
QMMLPainter::em() const {
    return m_font.em();
}
/* Ex
 * A font-relative measure that is the height of an "x" in the font. "ex"s are
 * typically used for font-relative vertical sizes. */
float
QMMLPainter::ex() const {
    return m_font.ex();
}
MathColor
QMMLPainter::highlightColor(uchar level) const {
    if (m_highlightcolor.isTransparent()) {
        return m_highlightcolor;
    }
    MathColor mc;
    int lm = int(pow(2,level));
    if (m_mathbackground.isTransparent()) {
        mc.setRgb(m_highlightcolor.r(), m_highlightcolor.g(),
            m_highlightcolor.b(), 255/lm);
    } else {
        uchar r = m_mathbackground.r();
        uchar g = m_mathbackground.g();
        uchar b = m_mathbackground.b();
        uchar a = m_mathbackground.a();
        r += (m_highlightcolor.r() - r)/lm;
        g += (m_highlightcolor.g() - g)/lm;
        b += (m_highlightcolor.b() - b)/lm;
        a += (m_highlightcolor.a() - a)/lm;
        mc.setRgb(r, g, b, a);
    }
    return mc;
}
MathColor
QMMLPainter::selectionColor() const {
    return m_selectioncolor;
}
void
QMMLPainter::setMathvariant(mathvariant::Mathvariant mv) {
    m_mathvariant = mv;
    printf("setMathvariant %i (fontsize: %f)\n", mv, m_fontsize);
    m_font.setFont(m_mathvariant, m_fontsize);
    p->setFont(m_font.font());
}
void
QMMLPainter::setMathColor(MathColor mc) {
    m_mathcolor = mc;
    p->setPen(qcolor(mc));
}
void
QMMLPainter::setMathBackground(MathColor mc) {
    m_mathbackground = mc;
    if (mc.isTransparent()) {
        p->setBrush(Qt::NoBrush);
    } else {
        p->setBrush(qcolor(mc));
    }
}
void
QMMLPainter::setFontSize(float pt) {
    printf("setFontSize\n");
    m_fontsize = pt;
    setMathvariant(m_mathvariant);
}
void
QMMLPainter::setLineThickness(float t) { // thickness in px
    QPen pen = p->pen();
    pen.setWidthF(t);
    p->setPen(pen);
}
void
QMMLPainter::drawLine(float x1, float y1, float x2, float y2,
        float linethickness) {
    QPen backup;
    if (linethickness) {
        QPen pen = p->pen();
        backup = pen;
        pen.setWidthF(linethickness);
        p->setPen(pen);
    }

    p->drawLine(QPointF(x1+absx, y1+absy), QPointF(x2+absx, y2+absy));

    if (linethickness) {
        p->setPen(backup);
    }
}
void
QMMLPainter::drawRect(float x, float y, float w, float h) {
    QRectF r(x+absx, y+absy, w, h);
    p->drawRect(r);
}
void
QMMLPainter::fillRect(float x, float y, float w, float h, const MathColor &bg,
        const MathColor &fg) {
    QPen pen = p->pen();
    QBrush brush = p->brush();
    if (fg.isTransparent()) {
        p->setPen(Qt::NoPen);
    } else {
        p->setPen(qcolor(fg));
    }
    if (!bg.isTransparent()) {
        p->setBrush(qcolor(bg));
    }
    QRectF r(x+absx, y+absy, w, h);
    p->drawRect(r);
    p->setPen(pen);
    p->setBrush(brush);
}
void
QMMLPainter::fillParallelogram(float x1, float y1, float x2, float y2,
        float x3, float y3) {
    QPainterPath path;
    x1 += absx;
    y1 += absy;
    x2 += absx;
    y2 += absy;
    path.moveTo(x1, y1);
    path.lineTo(x1, y2);
    path.lineTo(x2, y2);
    path.lineTo(x2, y1);
    path.lineTo(x1, y1);
    p->fillPath(path, p->pen().color());
}
void
QMMLPainter::drawPolygon(int n, float *x, float *y) {
    QPen pen = p->pen();
    QBrush brush = p->brush();

    QPolygonF list(n);
    for (int i=0; i<n; ++i) {
        list[i] = QPointF(absx+x[i], absy+y[i]);
    }

    // draw polygon in mathcolor
    p->setPen(Qt::NoPen);
    p->setBrush(pen.color());
    p->drawPolygon(list);
    // restore pen and brush
    p->setPen(pen);
    p->setBrush(brush);
}
void
QMMLPainter::drawText(const DOMString &s) {
    //printf("%s %s\n", (const char*)p->font().family().toUtf8(), (const char*)seriffont.family().toUtf8());
    printf("'%s' in %s italic: %i\n", s.utf8(), (const char*)p->font().family().toUtf8(),
        p->font().italic());
    QString qs = qstring(s);
    if (debugdrawtext) {
        QRectF rf = m_font.boundingRect(qs);
        drawOutline(rf.width());
    }
    p->drawText(QPointF(absx, absy), qs);
}
/* draw the string s with current font, but stretch it to fit the given
   width (a+d). We haven't implemented stretching, so i just center the character. */
void
QMMLPainter::drawText(const DOMString &s, float w) {
    float sw = stringWidth(s) + absx; // this can't be right
    float hdiff = w - sw;
    p->drawText(QPointF(hdiff/2, 0), qstring(s));
}
/* draw the string s with current font, but stretch it to fit the given
   height (a+d). Keep the width the same as the width specified by
   stringWidth(s); */
void
QMMLPainter::drawText(const DOMString &s, float a, float d) {
    QString qs = qstring(s);
    float fd = fontDescent();
    // get the height of the string in the unmodified font
    float realf = (a + d)/(fontAscent()+fd);
    printf("scaling factor: %f, fd: %f, a: %f, d: %f\n", realf, fd, a, d);
    p->save();
    p->translate(0, - realf*fd + d);
    p->scale(1, realf);
    if (debugdrawtext) {
        QRectF rf = m_font.boundingRect(qs);
        drawOutline(rf.width());
    }
    p->drawText(QPointF(absx, absy), qs);
    p->restore();
}
void
QMMLPainter::drawOutline(float w) {
    float a = fontAscent();
    float d = fontDescent();
     // total character area
    p->fillRect(QRectF(absx, absy-a, w, a), Qt::yellow); // ascent area
    p->drawLine(QPointF(absx, 0), QPointF(w, 0));
    p->fillRect(QRectF(absx, absy, w, d), Qt::blue); // descent area
    //p->fillRect(QRectF(absx, absy-a, w, a+d), Qt::blue);
}
void
QMMLPainter::drawText(const DOMString &s, float w, float a, float d) {
    float sw = stringWidth(s);
    float hdiff = w-sw;
    float fa = fontAscent();
    float fd = fontDescent();
    float vdiff = d-fd - a+fa;
    p->drawText(QPointF(hdiff/2, vdiff/2), qstring(s));
}
void
QMMLPainter::translate(float x, float y) {
    absx += x;
    absy += y;
}
QColor
QMMLPainter::qcolor(const MathColor &mc) {
    if (mc.isValid()) {
        return QColor(mc.r(), mc.g(), mc.b(), mc.a());
    }
    return QColor::Invalid;
}
MathColor
QMMLPainter::mathcolor(const QColor &qc) {
    MathColor mc;
    if (qc.isValid()) {
        mc.setRgb(qc.red(), qc.green(), qc.blue(), qc.alpha());
    }
    return mc;
}
