#include "mmlmsqrt.h"
#include "attributes.h"
#include "mmlmrow.h"
#include "mmlpainter.h"
#include "nodegui.h"
#include <cmath>

MMLmsqrt::MMLmsqrt(MMLDocument *o)
    : MMLElement(MML::MSQRT, o) {
}
bool
MMLmsqrt::validate() {
    if (validated) {
        return valid;
    }
    validated = true;
    validateChildren(1, true);
    if (!valid) return false;

    // if there are more than one children: construct an inferred mrow
    if (first != last) {
        MMLNode *mrow = owner->createInferredmrow(this);
        appendChild(mrow);
    }
    return valid;
}
void
MMLmsqrt::doLayout(MML::Attributes *a) const {
    MMLNode *sqrt = first;
    sqrt->layout(a);
    v_unit linethickness(0.05, l_unit::em);
    float lineth = linethickness.get(a);
    gui->ascent = sqrt->getAscent() + 4*lineth;
    gui->descent = sqrt->getDescent();
    float d = (gui->ascent + gui->descent)/12;
    gui->width = sqrt->getWidth()+5*d;
    sqrt->setX(5*d);
}
void
MMLmsqrt::doPaint(MML::Attributes *a) const {
    MMLNode *sqrt = first;
    v_unit linethickness(0.05, l_unit::em);
    float lineth = linethickness.get(a);
    sqrt->paint(a);

    float ly = -sqrt->getAscent() - 3.5*lineth;
    float d = (gui->ascent + gui->descent)/12;
    float bx = sqrt->getX();
    v_unit ex = v_unit(-0.5, v_unit::ex);
    float hex = ex.get(a);

    float x[10], y[10];
    float px[5], py[5];
    float t[4];
    px[0] = 0;      py[0] = 0.7*hex;
    px[1] = d;      py[1] = hex;
    px[2] = 3*d;    py[2] = gui->descent/2;
    px[3] = bx;     py[3] = ly;
    px[4] = gui->width;  py[4] = ly;
    t[0] = lineth/2;
    t[1] = 2*lineth;
    t[2] = t[3] = lineth;
    rootPoints(px, py, t, x, y);
    a->p->drawPolygon(10, x, y);
}
void
MMLmsqrt::rootPoints(float px[5], float py[5], float t[4],
        float x[10], float y[10]) {
    float a[4];
    float hx, hy;
    a[0] = atan2(py[1]-py[0], px[1]-px[0]);
    a[1] = atan2(py[2]-py[1], px[2]-px[1]);
    a[2] = atan2(py[3]-py[2], px[3]-px[2]);
    a[3] = atan2(py[4]-py[3], px[4]-px[3]);

    x[0] = px[0] - sin(a[0])*t[0]/2;
    y[0] = py[0] + cos(a[0])*t[0]/2;
    hx = px[1] - sin(a[1])*t[1]/2;
    hy = py[1] + cos(a[1])*t[1]/2;
    x[1] = (x[0]*tan(a[0])-hx*tan(a[1])+hy-y[0]) / (tan(a[0])-tan(a[1]));
    y[1] = (x[1]-x[0])*tan(a[0])+y[0];
    hx = px[2] - sin(a[2])*t[2]/2;
    hy = py[2] + cos(a[2])*t[2]/2;
    x[2] = (x[1]*tan(a[1])-hx*tan(a[2])+hy-y[1]) / (tan(a[1])-tan(a[2]));
    y[2] = (x[2]-x[1])*tan(a[1])+y[1];
    hx = px[3] - sin(a[3])*t[3]/2;
    hy = py[3] + cos(a[3])*t[3]/2;
    x[3] = (x[2]*tan(a[2])-hx*tan(a[3])+hy-y[2]) / (tan(a[2])-tan(a[3]));
    y[3] = (x[3]-x[2])*tan(a[2])+y[2];
    x[4] = px[4] - sin(a[3])*t[3]/2;
    y[4] = py[4] + cos(a[3])*t[3]/2;

    x[9] = px[0] + sin(a[0])*t[0]/2;
    y[9] = py[0] - cos(a[0])*t[0]/2;
    hx = px[1] + sin(a[1])*t[1]/2;
    hy = py[1] - cos(a[1])*t[1]/2;
    x[8] = (x[9]*tan(a[0])-hx*tan(a[1])+hy-y[9]) / (tan(a[0])-tan(a[1]));
    y[8] = (x[8]-x[9])*tan(a[0])+y[9];
    hx = px[2] + sin(a[2])*t[2]/2;
    hy = py[2] - cos(a[2])*t[2]/2;
    x[7] = (x[8]*tan(a[1])-hx*tan(a[2])+hy-y[8]) / (tan(a[1])-tan(a[2]));
    y[7] = (x[7]-x[8])*tan(a[1])+y[8];
    hx = px[3] + sin(a[3])*t[3]/2;
    hy = py[3] - cos(a[3])*t[3]/2;
    x[6] = (x[7]*tan(a[2])-hx*tan(a[3])+hy-y[7]) / (tan(a[2])-tan(a[3]));
    y[6] = (x[6]-x[7])*tan(a[2])+y[7];
    x[5] = px[4] + sin(a[3])*t[3]/2;
    y[5] = py[4] - cos(a[3])*t[3]/2;
}
