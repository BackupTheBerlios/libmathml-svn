#ifndef DUMMYPAINTER
#define DUMMYPAINTER

#include <mathml/mmlpainter.h>

class DummyPainter : public MMLPainter {
public:
    float dpi(bool horizontal) const {
        return 70;
    }
    float fontAscent() const {
        return 8;
    }
    float fontDescent() const {
        return 4;
    }
    float stringWidth(const DOMString &) const {
        return 20;
    }
    float em() const {
        return 12;
    }
    float ex() const {
        return 12;
    }

    MathColor mathColor() const {
        return MathColor::black;
    }
    MathColor highlightColor(uchar level) const {
        return MathColor::black;
    }
    MathColor selectionColor() const {
        return MathColor::black;
    }
    float fontSize() const {
        return 10;
    }

    // settings changes
    void translate(float x, float y) {}
    // the fontstretch function should be redundant by the
    // drawText-in-a-box function below

    // drawing actions
    void drawLine(float x1, float y1, float x2, float y2,
        float linethickness=0) {}
    void drawRect(float x, float y, float w, float h) {}
    void fillRect(float x, float y, float w, float h,
        const MathColor &bg = MathColor(),
        const MathColor &border = MathColor()) {}
    void fillParallelogram(float x1, float y1, float x2, float y2,
        float x3, float y3) {}
    void drawPolygon(int n, float *x, float *y) {}
    void drawText(const DOMString &s) {}
    void drawText(const DOMString &s, float w) {}
    void drawText(const DOMString &s, float a, float d) {}
    void drawText(const DOMString &s, float w, float a, float d){}
    // draw the text so that it fits exactly into the specified box
    // if the font cannot be to fit the box exactly, use a smaller font
    // and centre the content in the specified direction
protected:
    void setMathvariant(mathvariant::Mathvariant) {}
    void setMathColor(MathColor c) {}
    void setMathBackground(MathColor c) {}
    void setFontSize(float f) {} // f in pt (point size)
    void setLineThickness(float t) {} // thickness in px


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
private:
    MathColor m_mathcolor;
    MathColor m_mathbackground;
    MathColor m_highlightcolor;
    MathColor m_selectioncolor;
    mathvariant::Mathvariant m_mathvariant;
    float m_linethickness;
    float m_fontsize;
};

#endif
