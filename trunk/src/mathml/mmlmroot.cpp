#include "mmlmroot.h"
#include "nodegui.h"
#include "mmlmsqrt.h"
#include "mmltext.h"
#include "attributes.h"
#include "mmlpainter.h"

MMLmroot::MMLmroot(MMLDocument *o)
	: MMLElement(MML::MROOT, o) {
}
bool
MMLmroot::validate() {
	if (validated) {
		return valid;
	}
	validated = true;
	validateChildren(2);
	return valid;
}
void
MMLmroot::doLayout(MML::Attributes *a) const {
	MMLNode *base = first;
	MMLNode *index = last;

	// use the linethickness variable
	// (this is an attribute of the element 'mfrac')
	v_unit linethickness(0.05, l_unit::em);
	float lineth = linethickness.get(a);
	base->layout(a);
	a->setAttribute(MML::DISPLAYSTYLE, false);
	int sl = a->scriptlevel()+2;
	a->setAttribute(MML::SCRIPTLEVEL, sl);
	index->layout(a);

	float bascent = base->getAscent() + 4*lineth;
	// the base descent is used for the mroot too
	gui->descent = base->getDescent();
	// the width of the root sign is 5/12 th the height of the base
	float d = (bascent+gui->descent)/12;
	v_unit ex = v_unit(0.5, v_unit::ex);
	float hex = ex.get(a);
	float iascent = hex + index->getAscent()+index->getDescent();
	gui->ascent = (bascent < iascent) ?iascent :bascent;
	float brwidth = 3*d;
	float irwidth = index->getWidth();
	float rwidth = (brwidth < irwidth) ?irwidth : brwidth;
	base->setX(rwidth + 2*d);
	gui->width = rwidth + 2*d + base->getWidth();
	index->setY(-hex - index->getDescent());
}
void
MMLmroot::doPaint(MML::Attributes *a) const {
	//float lineth = a->linethickness().get(a);
	v_unit linethickness(0.05, l_unit::em);
	float lineth = linethickness.get(a);
	MMLNode *base = first;
	MMLNode *index = last;
	base->paint(a);
	a->setAttribute(MML::DISPLAYSTYLE, false);
	int sl = a->scriptlevel()+2;
	a->setAttribute(MML::SCRIPTLEVEL, sl);
	index->paint(a);

//	float ly = -base->getAscent() - 3.5*lineth;
//	float d = (base->getAscent()+descent)/10;
	float ly = -base->getAscent() - 3.5*lineth;
	float d = (base->getAscent() + gui->descent)/12;
//	float bx = base->getX();
	v_unit ex = v_unit(-0.5, v_unit::ex);
	float hex = ex.get(a);

	float brwidth = 3*d;
	float irwidth = index->getWidth();
	float rwidth = (brwidth < irwidth) ?irwidth : brwidth;

	float bx = rwidth + 2*d;

/*	float x[8], y[8];
	x[0] = bx;     y[0] = ly+0.5*lineth;
	x[1] = width;  y[1] = ly+0.5*lineth;
	x[2] = width;  y[2] = ly-0.5*lineth;
	x[3] = bx;     y[3] = ly-0.5*lineth;
	x[4] = bx-2*d; y[4] = descent;
	x[5] = bx-3*d; y[5] = descent-4*d;
	x[6] = bx-3*d+2*lineth; y[6] = descent-4*d;
	x[7] = bx-2*d; y[7] = descent-lineth;
*/
//	a->p->drawPolygon(8, x, y);
	float x[10], y[10];
	float px[5], py[5];
	float t[4];
	px[0] = bx-5*d; py[0] = 0.7*hex;
	px[1] = bx-4*d; py[1] = hex;
	px[2] = bx-2*d; py[2] = gui->descent/2;
	px[3] = bx;     py[3] = ly;
	px[4] = gui->width;  py[4] = ly;
	t[0] = lineth/2;
	t[1] = 2*lineth;
	t[2] = t[3] = lineth;
	MMLmsqrt::rootPoints(px, py, t, x, y);
	a->p->drawPolygon(10, x, y);
}
