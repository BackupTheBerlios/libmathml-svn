#ifndef WXMMLPAINTER_H
#define WXMMLPAINTER_H

#include <mathml/mmlpainter.h>
#ifndef TRUE
    #define TRUE  ((bool)1)
    #define FALSE ((bool)0)
#endif
#include <wx/font.h>
#include <wx/colour.h>

class wxMMLPainter : public MMLPainter {
public:
    wxMMLPainter(wxDC *);
    ~wxMMLPainter() {}
    void setOutline(bool outline);

    int f2xc(float) const; // convert x float coordinate to int
    int f2yc(float) const; // convert x float coordinate to int
    int f2l(float) const; // convert float length/size to int

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
    // the fontstretch function should be redundant by the
    // drawText-in-a-box function below

    // drawing actions
    void drawLine(float x1, float y1, float x2, float y2,
        float linethickness=0);
    void drawRect(float x, float y, float w, float h);
    void fillRect(float x, float y, float w, float h,
        const MathColor &bg = MathColor(),
        const MathColor &fg = MathColor());
    void fillParallelogram(float x1, float y1, float x2, float y2,
        float x3, float y3);
    void drawPolygon(int n, float *x, float *y);
    void drawText(const DOMString &s);
    void drawText(const DOMString &s, float w);
    void drawText(const DOMString &s, float a, float d);
    void drawText(const DOMString &s, float w, float a, float d);

    MathColor mathcolor(const wxColour &) const;
    wxColour wxcolour(const MathColor &) const;
protected:
    void setMathVariant(MathVariant);
    void setMathColor(MathColor c);
    void setMathBackground(MathColor c);
    void setFontSize(float f); // f in pt (point size)
    void setLineThickness(float t); // thickness in px
private:
    wxDC *p;
    wxFont defaultfont;
    int pointsize;
    bool debugdrawtext;
    float absx, absy;
    static const wxString abc;
    void drawOutline(const DOMString &);
};

class wxString;
wxString wxstring(const DOMString &);
DOMString domstring(const wxString &);

#endif
