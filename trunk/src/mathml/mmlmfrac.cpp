#include "mmlmfrac.h"
#include "nodegui.h"
using std::list;
#include "mathml.h"
#include "mmltext.h"
#include "attributes.h"
#include "mmlpainter.h"

v_unit MMLmfrac::defLineThickness(0.1, l_unit::em);

MMLmfrac::MMLmfrac(MMLDocument *o)
    : MMLElement(MML::MFRAC, o) {

    // initialize the default values for the attributes
    if (!defset[id]) {
        defset[id] = true;
        const MMLAttribute **da = defatt[id];
        using namespace MML;
        // we specify a length an not a relative number for the line-
        // thickness, because when linethickness is set, it can be set
        // relative to the default value
        createAttribute(LINETHICKNESS, "1", id, da);
        createAttribute(NUMALIGN, "center", id, da);
        createAttribute(DENOMALIGN, "center", id, da);
        createAttribute(BEVELLED, "false", id, da);
    }
    defLineThickness.set(0.05, l_unit::em);
}
bool
MMLmfrac::validate() {
    if (validated) {
        return valid;
    }
    validated = true;
    validateChildren(2);
    return valid;
}
void
MMLmfrac::doLayout(MML::Attributes *a) const {
    // a fraction will usually be larger than a normal line of text
    // here, we draw it such that it extends equally much on the top
    // as on the bottom of a normal character (font().height()

    MMLNode *num = first;
    MMLNode *den = last;
    float lineth = a->linethickness().get(a, defLineThickness);
    v_unit ex = v_unit(1, l_unit::ex);
    float ly = -ex.get(a)/2;

    // read metrics for current font
    if (a->displaystyle()) {
        a->setAttribute(MML::DISPLAYSTYLE, "false");
    } else {
        int sl = a->scriptlevel()+1;
        a->setAttribute(MML::SCRIPTLEVEL, sl);
    }
    num->layout(a);
    den->layout(a);

    // horizontal alignment
    float diff = num->getWidth() - den->getWidth();
    if (diff > 0) {
        gui->width = num->getWidth();
        num->setX(0);
        den->setX(diff/2);
    } else {
        gui->width = den->getWidth();
        num->setX(-diff/2);
        den->setX(0);
    }
    float numasc = num->getAscent();
    float numdes = num->getDescent();
    float denasc = den->getAscent();
    float dendes = den->getDescent();
    gui->ascent = numasc + numdes + 3*lineth/2 - ly;
    gui->descent = denasc + dendes + 3*lineth/2 + ly;
    num->setY(numasc-gui->ascent);
    den->setY(gui->descent-dendes);
}
void
MMLmfrac::doPaint(MML::Attributes *a) const {
    // retreive environment data before we modify the environment
    float lineth = a->linethickness().get(a, defLineThickness);
    v_unit ex = v_unit(1, l_unit::ex);
    float ly = -ex.get(a)/2;

    // modify the enviroment for drawing the nom and denominator
    if (a->displaystyle()) {
        a->setAttribute(MML::DISPLAYSTYLE, false);
    } else {
        int sl = a->scriptlevel()+1;
        a->setAttribute(MML::SCRIPTLEVEL, sl);
    }
    first->paint(a);
    last->paint(a);

    // draw the line
    if (lineth) {
        a->p->drawLine(0, ly, gui->width, ly);
    }
}
