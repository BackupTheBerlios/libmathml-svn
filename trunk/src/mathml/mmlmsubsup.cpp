#include "mmlmsubsup.h"
#include "attributes.h"
#include "nodegui.h"

MMLmsubsup::MMLmsubsup(MMLDocument *o)
    : MMLElement(MML::MSUBSUP, o) {

    if (!defset[id]) {
        defset[id] = true;
        const MMLAttribute **da = defatt[id];
        using namespace MML;
        MML::createAttribute(MML::SUBSCRIPTSHIFT, "0.7ex", id, da);
        MML::createAttribute(MML::SUPERSCRIPTSHIFT, "1ex", id, da);
    }
}
bool
MMLmsubsup::validate() {
    if (validated) {
        return valid;
    }
    validated = true;
    validateChildren(3);
    return valid;
}
void
MMLmsubsup::doLayout(MML::Attributes *a) const {
    MMLNode *base = first;
    MMLNode *sub = getNext(first);
    MMLNode *sup = last;
    // read metrics for current font
    base->layout(a);
    a->setAttribute(MML::DISPLAYSTYLE, false);
    int sl = a->scriptlevel()+1;
    a->setAttribute(MML::SCRIPTLEVEL, sl);
    sub->layout(a);
    sup->layout(a);

    float subshift = a->superscriptshift().get(a);
    if (subshift == 0) {
        subshift = base->getDescent() - sub->getDescent();
    }
    sub->setX(base->getWidth());
    sub->setY(subshift);
    float supshift = a->superscriptshift().get(a);
    if (supshift == 0) {
        supshift = base->getAscent()-sup->getAscent();
    }
    sup->setX(base->getWidth());
    sup->setY(-supshift);

    float subwidth = sub->getWidth();
    float supwidth = sup->getWidth();
    gui->width = base->getWidth()
        + ((subwidth>supwidth) ? subwidth : supwidth);
    gui->ascent = base->getAscent();
    gui->descent = base->getDescent();
}
void
MMLmsubsup::doPaint(MML::Attributes *a) const {
    MMLNode *base = first;
    MMLNode *sub = getNext(first);
    MMLNode *sup = last;
    base->paint(a);
    a->setAttribute(MML::DISPLAYSTYLE, false);
    int sl = a->scriptlevel()+1;
    a->setAttribute(MML::SCRIPTLEVEL, sl);
    sub->paint(a);
    sup->paint(a);
}
