#ifndef MMLPAINTER
#define MMLPAINTER

#include "mathcolor.h"
#include "mathenums.h"
class DOMString;
class MMLPainter {
friend class PainterSettings;
public:
	virtual ~MMLPainter() {}
	virtual float dpi(bool horizontal) const = 0;
//	virtual int fontHeight() const = 0;
	virtual float fontAscent() const = 0;
	virtual float fontDescent() const = 0;
	virtual float stringWidth(const DOMString &) const = 0;
//	virtual void boundingRect(const DOMString &s, float &w, float &h)
//		const = 0;
//	virtual void boundingRect(const DOMString &s, float &descent,
//		float &descent, float &width) const = 0;
	virtual float em() const = 0;
	virtual float ex() const = 0;
	virtual MathColor mathColor() const = 0;
	virtual MathColor highlightColor(uchar level) const = 0;
	virtual MathColor selectionColor() const = 0;
	virtual float fontSize() const = 0;

	// settings changes
	virtual void translate(float x, float y) = 0;
	// the fontstretch function should be redundant by the
	// drawText-in-a-box function below

	// drawing actions
	virtual void drawLine(float x1, float y1, float x2, float y2,
		float linethickness=0) = 0;
	virtual void drawRect(float x, float y, float w, float h) = 0;
	virtual void fillRect(float x, float y, float w, float h,
		const MathColor &bg = MathColor(),
		const MathColor &border = MathColor()) = 0;
	virtual void fillParallelogram(float x1, float y1, float x2, float y2,
		float x3, float y3) = 0;
	virtual void drawPolygon(int n, float *x, float *y) = 0;
	virtual void drawText(const DOMString &s) = 0;
	virtual void drawText(const DOMString &s, float w) = 0;
	virtual void drawText(const DOMString &s, float a, float d) = 0;
	virtual void drawText(const DOMString &s, float w, float a, float d)= 0;
	// draw the text so that it fits exactly into the specified box
	// if the font cannot be to fit the box exactly, use a smaller font
	// and centre the content in the specified direction
protected:
	virtual void setMathVariant(MathVariant) = 0;
	virtual void setMathColor(MathColor c) = 0;
	virtual void setMathBackground(MathColor c) = 0;
	virtual void setFontSize(float f) = 0; // f in pt (point size)
	virtual void setLineThickness(float t) = 0; // thickness in px
};

#endif
