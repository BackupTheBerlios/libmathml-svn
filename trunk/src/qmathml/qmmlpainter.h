#ifndef QMMLPAINTER
#define QMMLPAINTER

#include <mathml/mmlpainter.h>
#include "mathfont.h"

class QPainter;
class QString;
class QColor;
class QMMLPainter : public MMLPainter {
public:
    QMMLPainter();
    virtual ~QMMLPainter() {};
    void setPainter(QPainter *);
    void initializePainter();
    void setMathColor(const QColor &c) {
        m_mathcolor = mathcolor(c);
    }
    void setMathBackground(const QColor &c) {
        m_mathbackground = mathcolor(c);
    }
    void setHighlightColor(const QColor &c) {
        m_highlightcolor = mathcolor(c);
    }
    void setSelectionColor(const QColor &c) {
        m_selectioncolor = mathcolor(c);
    }
    void setOutline(bool outline);
    void setSerifFont(QFont font);
    void setSansSerifFont(QFont font);
    void setMonoSpaceFont(QFont font);
    void setScriptFont(QFont font);
    void setFrakturFont(QFont font);
    void setDoubleStruckFont(QFont font);

    // functions required by libmathml
    float dpi(bool horizontal) const;
    float fontAscent() const;
    float fontDescent() const;
    float stringWidth(const DOMString &) const;
    float em() const;
    float ex() const;
    MathColor highlightColor(uchar level) const;
    MathColor selectionColor() const;

    // settings changes
    void translate(float x, float y);
    void setMathvariant(mathvariant::Mathvariant);
    void setMathColor(MathColor c);
    void setMathBackground(MathColor c);
    void setFontSize(float f); // f in pt (point size)
    void setLineThickness(float t); // thickness in px

    mathvariant::Mathvariant getMathvariant() const {
        return m_mathvariant;
    }
    MathColor getMathColor() const {
        return m_mathcolor;
    }
    MathColor getMathBackground() const {
        return m_mathbackground;
    }
    float getFontSize() const {
        return m_fontsize;
    }
    float getLineThickness() const {
        return m_linethickness;
    }
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
    static QColor qcolor(const MathColor &);
    static MathColor mathcolor(const QColor &);
private:
    QPainter *p;
    MathFont m_font;
    MathColor m_mathcolor;
    MathColor m_mathbackground;
    MathColor m_highlightcolor;
    MathColor m_selectioncolor;
    mathvariant::Mathvariant m_mathvariant;
    float m_linethickness;
    float m_fontsize;

    float absx, absy;
    bool debugdrawtext;
    bool fittext;
    void drawOutline(float width);
};

#endif
