#include "wxmmlpainter.h"
#include <mathml/mmldocument.h>

#include <wx/dc.h>
#include <wx/settings.h>
#include <cmath>

const wxString wxMMLPainter::abc
	= wxT("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

wxMMLPainter::wxMMLPainter(wxDC *dc) {
	p = dc;
	debugdrawtext = false;
	absx = absy = 0;
	defaultfont = dc->GetFont();
	pointsize = dc->GetFont().GetPointSize();
}
void
wxMMLPainter::setOutline(bool outline) {
	debugdrawtext = outline;
}
float
wxMMLPainter::dpi(bool horizontal) const {
	wxCoord w, h;
	w = h = 0;
	p->GetSize(&w, &h);
	if (horizontal) {
		return w;
	} else {
		return h;
	}
}
/* In Qt the total height of a font is given as ascent + 1 + descent.
   The 1 is for the baseline.
   In a continuous coordinate system, the baseline is infinetly thin.
   So there, the total height is ascent + descent. To make sure the total
   font size in both systems is equal, we add the 1 for the baseline to the
   ascent of the font. The ascent is the best choice because it is the larger
   value and it's relative change is smaller. */
float
wxMMLPainter::fontAscent() const {
	int w, h, d;
	w = h = d = 0;
	p->GetTextExtent(abc, &w, &h, &d);
	return h-d;
}
float
wxMMLPainter::fontDescent() const {
	int w, h, d;
	w = h = d = 0;
	p->GetTextExtent(abc, &w, &h, &d);
	return d;
}
float
wxMMLPainter::stringWidth(const DOMString &s) const {
	int w, h, d;
	p->GetTextExtent(wxstring(s), &w, &h, &d);
	return w;
}
/* Em
 * A font-relative measure encoded by the font. Before electronic typesetting,
 * an "em" was the width of an "M" in the font. In modern usage, an "em" is
 * either specified by the designer of the font or is taken to be the height
 * (point size) of the font. Em's are typically used for font-relative
 * horizontal sizes. */
float
wxMMLPainter::em() const {
	return p->GetFont().GetPointSize();
}
/* Ex
 * A font-relative measure that is the height of an "x" in the font. "ex"s are
 * typically used for font-relative vertical sizes. */
float
wxMMLPainter::ex() const {
	int w, h;
	wxString s(wxT("x"));
	p->GetTextExtent(s, &w, &h);
	h = p->GetFont().GetPointSize(); // debug statement
	return h;
}
MathColor
wxMMLPainter::mathColor() const {
	MathColor mc;
	wxColour wc = p->GetTextForeground();
	return mathcolor(wc);
}
MathColor
wxMMLPainter::highlightColor(uchar level) const {
	MathColor mc;
	wxColour bg = p->GetBackground().GetColour();
	wxColour hl = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);
	int r, g, b;
	int lm = int(pow(2,level));
	r = (hl.Red() - bg.Red())/lm + bg.Red();
	g = (hl.Green() - bg.Green())/lm + bg.Green();
	b = (hl.Blue() - bg.Blue())/lm + bg.Blue();
    printf("highlight: %i, %i, %i\n", r, g, b);
	mc.setRgb(r, g, b);
	return mc;
}
MathColor
wxMMLPainter::selectionColor() const {
	MathColor mc;
	wxColour sc = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);
	mc.setRgb(sc.Red(), sc.Green(), sc.Blue());
    printf("selection: %i, %i, %i\n", sc.Red(), sc.Green(), sc.Blue());
	return mc;
}
void
wxMMLPainter::setMathVariant(MathVariant mv) {
	wxFont f = p->GetFont();
	switch (mv) {
	case (NORMAL):
		// strangely, setting the default values for a font results in
		// an invisible font! so we use a stored value for the default
		// font
		//f.SetFamily(wxROMAN);
		//f.SetWeight(wxNORMAL);
		//f.SetStyle(wxNORMAL);
		f = defaultfont;
		f.SetPointSize(pointsize);
		break;
	case (BOLD):
		f.SetFamily(wxROMAN);
		f.SetWeight(wxBOLD);
		f.SetStyle(wxNORMAL);
		break;
	case (ITALIC):
		f.SetFamily(wxROMAN);
		f.SetWeight(wxNORMAL);
		f.SetStyle(wxITALIC);
		break;
	case (BOLD_ITALIC):
		f.SetFamily(wxROMAN);
		f.SetWeight(wxBOLD);
		f.SetStyle(wxITALIC);
		break;
	case (DOUBLE_STRUCK): break;
	case (SCRIPT):
		f.SetFamily(wxSCRIPT);
		f.SetWeight(wxNORMAL);
		f.SetStyle(wxNORMAL);
		break;
	case (BOLD_SCRIPT):
		f.SetFamily(wxSCRIPT);
		f.SetWeight(wxBOLD);
		f.SetStyle(wxNORMAL);
		break;
	case (FRAKTUR): break;
	case (BOLD_FRAKTUR): break;
	case (SANS_SERIF):
		f.SetFamily(wxSWISS);
		f.SetWeight(wxNORMAL);
		f.SetStyle(wxNORMAL);
		break;
	case (BOLD_SANS_SERIF):
		f.SetFamily(wxSWISS);
		f.SetWeight(wxBOLD);
		f.SetStyle(wxNORMAL);
		break;
	case (SANS_SERIF_ITALIC):
		f.SetFamily(wxSWISS);
		f.SetWeight(wxNORMAL);
		f.SetStyle(wxITALIC);
		break;
	case (SANS_SERIF_BOLD_ITALIC):
		f.SetFamily(wxSWISS);
		f.SetWeight(wxBOLD);
		f.SetStyle(wxITALIC);
		break;
	case (MONOSPACE):
		f.SetFamily(wxMODERN);
		f.SetWeight(wxNORMAL);
		f.SetStyle(wxNORMAL);
		break;
	default:
		printf("value for MathVariant is out of range\n");
	}
	p->SetFont(f);
}
void
wxMMLPainter::setMathColor(MathColor mc) {
	wxPen pen = p->GetPen();
	if (mc.isTransparent()) {
		// mathcolor cannot be transparent, only background can
		pen.SetStyle(wxTRANSPARENT);
	} else {
		wxColour c;
		c.Set(mc.r(), mc.g(), mc.b());
		pen.SetColour(c);
	}
	p->SetPen(pen);
}
void
wxMMLPainter::setMathBackground(MathColor mc) {
	wxBrush brush = p->GetBrush();
	if (mc.isTransparent()) {
		// mathcolor cannot be transparent, only background can
		brush.SetStyle(wxTRANSPARENT);
	} else {
		wxColour c;
		c.Set(mc.r(), mc.g(), mc.b());
		brush.SetColour(c);
	}
	p->SetBrush(brush);
}
void
wxMMLPainter::setFontSize(float pt) {
	wxFont f = p->GetFont();
	pointsize = int(pt);
	f.SetPointSize(pointsize);
	p->SetFont(f);
}
void
wxMMLPainter::setLineThickness(float t) { // thickness in px
	wxPen pen = p->GetPen();
	int it = f2l(t);
	pen.SetWidth(it ?it :1);
	p->SetPen(pen);
}
float
wxMMLPainter::fontSize() const {
	return p->GetFont().GetPointSize();
}
void
wxMMLPainter::drawLine(float x1, float y1, float x2, float y2,
		float linethickness) {
	wxPen backup;
	if (linethickness) {
		wxPen pen = p->GetPen();
		backup = pen;
		pen.SetWidth(f2l(linethickness));
		p->SetPen(pen);
	}

	p->DrawLine(f2xc(x1), f2yc(y1), f2xc(x2), f2yc(y2));

	if (linethickness) {
		p->SetPen(backup);
	}
}
void
wxMMLPainter::drawRect(float x, float y, float w, float h) {
	p->DrawRectangle(f2xc(x), f2yc(y), f2l(w), f2l(h));
}
void
wxMMLPainter::fillRect(float x, float y, float w, float h, const MathColor &bg,
		const MathColor &fg) {
	wxBrush b, bbackup;
	wxPen pen, pbackup;
	b = bbackup = p->GetBrush();
	pen = pbackup = p->GetPen();
	b.SetStyle(wxSOLID);
	if (bg.isTransparent()) {
		b.SetColour(p->GetPen().GetColour());
	} else {
		b.SetColour(wxcolour(bg));
	}
	p->SetBrush(b);
	int style = 0;
	if (fg.isTransparent()) {
		style = p->GetPen().GetStyle();
		pen.SetStyle(wxTRANSPARENT);
	} else {
		pen.SetColour(wxcolour(fg));
	}
	p->SetPen(pen);
	p->DrawRectangle(f2xc(x), f2yc(y), f2l(w), f2l(h));
	p->SetPen(pbackup);
	p->SetBrush(bbackup);
}
/* we map the points (x1, y1), (x2, y2), (x3, y3) to the points (0, 0), (1, 0),
   (0, 1), then we draw a rectangle that covers these points. */
void
wxMMLPainter::fillParallelogram(float x1, float y1, float x2, float y2,
		float x3, float y3) {
	wxPoint list[4];
	list[0] = wxPoint(f2xc(x1), f2yc(y1));
	list[1] = wxPoint(f2xc(x2), f2yc(y2));
	list[2] = wxPoint(f2xc(x3), f2yc(y3));
	list[3] = wxPoint(f2xc(x3+x2-x1), f2yc(y3+y2-y1));
	p->DrawPolygon(4, list);
}
void
wxMMLPainter::drawPolygon(int n, float *x, float *y) {
	wxBrush b, bbackup;
	b = bbackup = p->GetBrush();
	b.SetStyle(wxSOLID);
	b.SetColour(p->GetPen().GetColour());
	p->SetBrush(b);
	wxPoint *list = new wxPoint[n];
	for (int i=0; i<n; ++i) {
		list[i] = wxPoint(f2xc(x[i]), f2yc(y[i]));
	}
	p->DrawPolygon(n, list);
	delete [] list;
	p->SetBrush(bbackup);
}
void
wxMMLPainter::drawText(const DOMString &s) {
	if (debugdrawtext) {
		drawOutline(s);
	}
	float y = fontAscent();
	p->DrawText(wxstring(s), f2xc(0), f2yc(-y));
}
/* wxwindows cannot stretch fonts, so we draw at the centre of the designated
   area */
void
wxMMLPainter::drawText(const DOMString &s, float w) {
	float y = fontAscent();
	float sw = f2l(stringWidth(s));
	float hdiff = w-sw;
	p->DrawText(wxstring(s), f2xc(hdiff/2), f2yc(-y));
}
/* draw the string s with current font, but stretch it to fit the given
   height (a+d). Keep the width the same as the width specified by
   stringWidth(s); */
/* wxwindows cannot stretch fonts, so we draw at the centre of the designated
   area */
void
wxMMLPainter::drawText(const DOMString &s, float a, float d) {
	float fa = fontAscent();
	float fd = fontDescent();
	float vdiff = d-fd - a+fa;
	p->DrawText(wxstring(s), f2xc(0), f2yc(vdiff/2-fa));
}
/* wxwindows cannot stretch fonts, so we draw at the centre of the designated
   area */
void
wxMMLPainter::drawText(const DOMString &s, float w, float a, float d) {
	float sw = f2l(stringWidth(s));
	float hdiff = w-sw;
	float fa = fontAscent();
	float fd = fontDescent();
	float vdiff = d-fd - a+fa;
	p->DrawText(wxstring(s), f2xc(hdiff/2), f2yc(vdiff/2-fa));
}
void
wxMMLPainter::drawOutline(const DOMString &s) {
	int a = int(fontAscent());
	int d = int(fontDescent());
	int w = int(stringWidth(s));
	 // total character area
	wxPen pen, pbackup;
	pen = pbackup = p->GetPen();
	wxBrush brush, bbackup;
	brush = bbackup = p->GetBrush();
	pen.SetColour(*wxGREEN);
	brush.SetColour(wxColour(0,255,255));
	p->SetPen(pen);
	p->SetBrush(brush);
	p->DrawRectangle(f2xc(0), f2yc(-a), f2l(w), f2l(a+d+1));
	p->SetBrush(bbackup);
	p->DrawRectangle(f2xc(0), f2yc(-a), f2l(w), f2l(a+1)); // ascent area
	p->DrawRectangle(f2xc(0), f2yc(0), f2l(w), f2l(d+1)); // descent area
	p->SetPen(pbackup);
}
void
wxMMLPainter::translate(float x, float y) {
	absx += x;
	absy += y;
}
/* from the documentation of wxwindows it's not entirely clear how to convert
   to and from utf16 (domstring) strings to wxString object, so, we'll just
   copy the characters one by one until we know more. */
wxString
wxstring(const DOMString &d) {
	wxString s;
	uint len = d.length();
	s.resize(len);
	for (uint i=0; i<len; ++i) {
		wxChar c = d[i];
		s[i] = c;
	}
	return s;
}
DOMString
domstring(const wxString &s) {
	DOMString d;
        uint len = s.length();
        d.resize(len);
        for (uint i=0; i<len; ++i) {
                d[i] = s[i];
        }
        return d;
}
// convert a coordinate float value to an integer float value
// we always convert such values to the lower value
int
wxMMLPainter::f2xc(float f) const{
	f += absx;
        return (f<0) ? int(f)-1 : int(f);
}
int
wxMMLPainter::f2yc(float f) const {
	f += absy;
        return (f<0) ? int(f)-1 : int(f);
}
// convert a length/size float value to an integer float value
// we always convert such values to nearest value
int
wxMMLPainter::f2l(float f) const {
	f += 0.5;
        return (f<0) ? int(f)-1 : int(f);
}
MathColor
wxMMLPainter::mathcolor(const wxColour &wc) const {
	MathColor mc;
	if (wc.Ok()) {
		mc.setRgb(wc.Red(), wc.Blue(), wc.Green());
	}
	return mc;
}
wxColour
wxMMLPainter::wxcolour(const MathColor &mc) const {
	wxColour wx = wxNullColour;
	if (!mc.isTransparent()) {
		wx.Set(mc.r(), mc.g(), mc.b());
	}
	return wx;
}
