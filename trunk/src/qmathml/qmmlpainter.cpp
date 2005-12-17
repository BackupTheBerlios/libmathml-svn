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

QMMLPainter::QMMLPainter()
    : fontmetrics(QFont()) {
    absx = absy = 0;
    cout << "----" << endl;
    debugdrawtext = false;
    fittext = true;

    seriffont.setStyleHint(QFont::Serif);
    seriffont.setFamily(seriffont.defaultFamily());
    sansseriffont.setStyleHint(QFont::SansSerif);
    sansseriffont.setFamily(sansseriffont.defaultFamily());
    scriptfont.setFamily("URW Chancery L");
    monospacefont.setFamily("Monospace");
}
void
QMMLPainter::setPainter(QPainter *p) {
    this->p = p;
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
    return fontmetrics.ascent();
}
float
QMMLPainter::fontDescent() const {
    return fontmetrics.descent();
}
float
QMMLPainter::stringWidth(const DOMString &s) const {
    QFontMetricsF f(p->font());
    QString qs = qstring(s);
    QRectF r = f.boundingRect(qs);
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
    return fontmetrics.height();
}
/* Ex
 * A font-relative measure that is the height of an "x" in the font. "ex"s are
 * typically used for font-relative vertical sizes. */
float
QMMLPainter::ex() const {
    return fontmetrics.boundingRect("x").height();
}
MathColor
QMMLPainter::mathColor() const {
    MathColor mc;
    if (p->pen() != Qt::NoPen) {
        mc = mathcolor(p->pen().color());
    }
    return mc;
}
MathColor
QMMLPainter::highlightColor(uchar level) const {
    MathColor mc;
    QColor hl = palette.highlight().color();
    QColor bg = palette.background().color();
    int r, g, b;
    int lm = int(pow(2,level));
    r = (hl.red() - bg.red())/lm + bg.red();
    g = (hl.green() - bg.green())/lm + bg.green();
    b = (hl.blue() - bg.blue())/lm + bg.blue();
    mc.setRgb(r, g, b);
    return mc;
}
MathColor
QMMLPainter::selectionColor() const {
    return mathcolor(palette.highlight().color());
}
void
QMMLPainter::setMathVariant(MathVariant mv) {
    QFont f = p->font();
    float size = f.pointSize();
    switch (mv) {
    case (NORMAL):
        f = seriffont;
        f.setBold(false);
        f.setItalic(false);
        break;
    case (BOLD):
        f = seriffont;
        f.setBold(true);
        f.setItalic(false);
        break;
    case (ITALIC):
        f = seriffont;
        f.setBold(false);
        f.setItalic(true);
        break;
    case (BOLD_ITALIC):
        f = seriffont;
        f.setBold(true);
        f.setItalic(true);
        break;
    case (DOUBLE_STRUCK): break;
        break;
    case (BOLD_FRAKTUR): break;
        break;
    case (SCRIPT):
        f = scriptfont;
        f.setBold(false);
        f.setItalic(false);
        break;
    case (BOLD_SCRIPT):
        f = scriptfont;
        f.setBold(true);
        f.setItalic(false);
        break;
    case (FRAKTUR): break;
        break;
    case (SANS_SERIF):
        f = sansseriffont;
        f.setBold(false);
        f.setItalic(false);
        break;
    case (BOLD_SANS_SERIF):
        f = sansseriffont;
        f.setBold(true);
        f.setItalic(false);
        break;
    case (SANS_SERIF_ITALIC):
        f = sansseriffont;
        f.setBold(false);
        f.setItalic(true);
        break;
    case (SANS_SERIF_BOLD_ITALIC):
        f = sansseriffont;
        f.setBold(true);
        f.setItalic(true);
        break;
    case (MONOSPACE):
        f = monospacefont;
        f.setBold(false);
        f.setItalic(false);
        break;
    }
    f.setPointSizeF(size);
    p->setFont(f);
    fontmetrics = QFontMetricsF(f);
    //printf("%s\n", (const char*)p->font().family().toUtf8());
}
void
QMMLPainter::setMathColor(MathColor mc) {
    if (mc.isTransparent()) {
        // mathcolor cannot be transparent, only background can
        p->setPen(Qt::NoPen);
    } else {
        p->setPen(qcolor(mc));
    }
}
void
QMMLPainter::setMathBackground(MathColor mc) {
    if (mc.isTransparent()) {
        p->setBrush(Qt::NoBrush);
    } else {
        p->setBrush(qcolor(mc));
    }
}
void
QMMLPainter::setFontSize(float pt) {
    QFont f = p->font();
    if (f.pointSize() == -1) {
        int newsize = (int)(pt*dpi(false)/72);
        f.setPixelSize(newsize);
    } else {
        f.setPointSizeF(pt);
    }
    p->setFont(f);
    fontmetrics = QFontMetricsF(f);
}
void
QMMLPainter::setLineThickness(float t) { // thickness in px
    QPen pen = p->pen();
    pen.setWidthF(t);
    p->setPen(pen);
}
float
QMMLPainter::fontSize() const {
    QFont f = p->font();
    float size;
    if (f.pointSize() == -1) {
        size = f.pixelSize()*72/dpi(false);
    } else {
        size = f.pointSizeF();
    }
    return size;
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
    QString qs = qstring(s);
    if (debugdrawtext) {
        QRectF rf = fontmetrics.boundingRect(qs);
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
    p->save();
    p->translate(0, - realf*fd + d);
    p->scale(1, realf);
    if (debugdrawtext) {
        QRectF rf = fontmetrics.boundingRect(qs);
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
void
QMMLPainter::setPalette(const QPalette &cg) {
    palette = cg;
}
QColor
QMMLPainter::qcolor(const MathColor &mc) const {
    QColor qc;
    if (!mc.isTransparent()) {
        qc.setRgb(mc.r(), mc.g(), mc.b());
    }
    return qc;
}
MathColor
QMMLPainter::mathcolor(const QColor &qc) const {
    MathColor mc;
    if (qc.isValid()) {
        mc.setRgb(qc.red(), qc.green(), qc.blue());
    }
    return mc;
}
