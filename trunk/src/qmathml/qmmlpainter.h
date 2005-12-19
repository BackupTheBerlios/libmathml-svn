#ifndef QMMLPAINTER
#define QMMLPAINTER

#include <mathml/mmlpainter.h>
#include <QPalette>
#include <QFontMetrics>

class QPainter;
class QString;
class QMMLPainter : public MMLPainter {
public:
    QMMLPainter();
    virtual ~QMMLPainter() {};
    void setPainter(QPainter *);
    void setPalette(const QPalette &);
    const QPalette &getPalette() const {
        return palette;
    }
    void setOutline(bool outline);

    // functions required by libmathml
    float dpi(bool horizontal) const;
    float fontAscent() const;
    float fontDescent() const;
    float stringWidth(const DOMString &) const;
    float em() const;
    float ex() const;
    MathColor mathColor() const;
    MathColor highlightColor(uchar level) const;
    MathColor selectionColor() const;
    float fontSize() const;

    // settings changes
    void translate(float x, float y);
    void setMathvariant(mathvariant::Mathvariant);
    void setMathColor(MathColor c);
    void setMathBackground(MathColor c);
    void setFontSize(float f); // f in pt (point size)
    void setLineThickness(float t); // thickness in px

    // drawing actions
    void drawLine(float x1, float y1, float x2, float y2,
        float linethickness=0);
    void drawRect(float x, float y, float w, float h);
    void fillRect(float x, float y, float w, float h,
        const MathColor &bg, const MathColor &fg);
    void fillParallelogram(float x1, float y1, float x2, float y2,
        float x3, float y3);
    void drawPolygon(int n, float *x, float *y);
    void drawText(const DOMString &s);
    void drawText(const DOMString &s, float w);
    void drawText(const DOMString &s, float a, float d);
    void drawText(const DOMString &s, float w, float a, float d);
    QColor qcolor(const MathColor &) const;
    MathColor mathcolor(const QColor &) const;
private:
    QPainter *p;
    QPalette palette;
    QFontMetricsF fontmetrics;
    QFont seriffont;
    QFont sansseriffont;
    QFont scriptfont;
    QFont monospacefont;

    float absx, absy;
    bool debugdrawtext;
    bool fittext;
    void drawOutline(float width);
};

#endif
