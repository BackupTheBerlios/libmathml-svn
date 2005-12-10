#include "mmlmsup.h"
#include "attributes.h"
#include "nodegui.h"

MMLmsup::MMLmsup(MMLDocument *o)
    : MMLElement(MML::MSUP, o) {

    if (!defset[id]) {
        defset[id] = true;
        const MMLAttribute **da = defatt[id];
        using namespace MML;
        MML::createAttribute(MML::SUPERSCRIPTSHIFT, "1ex", id, da);
    }
}
bool
MMLmsup::validate() {
    if (validated) {
        return valid;
    }
    validated = true;
    validateChildren(2);
    return valid;
}
void
MMLmsup::doLayout(MML::Attributes *a) const {
    MMLNode *base = first;
    MMLNode *sup = last;
    // read metrics for current font
    base->layout(a);
    a->setAttribute(MML::DISPLAYSTYLE, false);
    int sl = a->scriptlevel()+1;
    a->setAttribute(MML::SCRIPTLEVEL, sl);
    sup->layout(a);

    float shift = a->superscriptshift().get(a);
    if (shift == 0) {
        shift = base->getAscent()-sup->getAscent();
    }
    sup->setX(base->getWidth());
    sup->setY(-shift);

    gui->width = base->getWidth() + sup->getWidth();
    gui->ascent = base->getAscent();
    gui->descent = base->getDescent();
}
void
MMLmsup::doPaint(MML::Attributes *a) const {
    MMLNode *base = first;
    MMLNode *sup = last;
    base->paint(a);
    a->setAttribute(MML::DISPLAYSTYLE, false);
    int sl = a->scriptlevel()+1;
    a->setAttribute(MML::SCRIPTLEVEL, sl);
    sup->paint(a);
}
