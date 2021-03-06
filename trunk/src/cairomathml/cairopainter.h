#ifndef CAIROPAINTER
#define CAIROPAINTER

#include <mathml/mmlpainter.h>
#include <cairo/cairo.h>
#include <string>

/**
 * @brief This class is a Cairo implementation of the MathML Painter
 *
 **/
class CairoPainter : public MMLPainter {
public:
    CairoPainter();
    void setPainter(cairo_t *p);
    void setFont(const std::string &family, float size);
    void setOutline(bool outline);
    void setBackground(uint r, uint g, uint b, uint a=255);

/** functions called by libmathml **/

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
private:
    std::string m_seriffont;
    std::string m_sansseriffont;
    std::string m_scriptfont;
    std::string m_monofont;

    MathColor m_mathcolor;
    MathColor m_mathbackground;
    MathColor m_highlightcolor;
    MathColor m_selectioncolor;
    mathvariant::Mathvariant m_mathvariant;
    float m_linethickness;
    float m_fontsize;

    cairo_t *m_painter;
    cairo_font_extents_t m_fontmetrics;
    mutable cairo_text_extents_t m_textsize;

    float absx, absy;
    bool debugdrawtext;
    bool fittext;
    void drawOutline(float width);
};

#endif
