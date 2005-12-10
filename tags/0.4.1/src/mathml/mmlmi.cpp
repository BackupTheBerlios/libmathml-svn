#include "mmlmi.h"
#include "nodegui.h"
using std::list;
#include "mathml.h"
#include "mmltext.h"
#include "attributes.h"
#include "mmlpainter.h"

MMLmi::MMLmi(MMLDocument *o)
    : MMLElement(MML::MI, o) {
    // initialize the default values for the attributes
    DOMString italic = "italic";
    if (!defset[id]) {
        defset[id] = true;
        const MMLAttribute **da = defatt[id];
        using namespace MML;
        MML::createAttribute(MATHVARIANT, italic, id, da);
    }
    MML::createAttribute(MML::MATHVARIANT, italic, id, att);
}
#include <iostream>
using std::cerr;
using std::endl;
bool
MMLmi::validate() {
    if (validated) {
        return valid;
    }
    valid = true;
    // an mi element may only contain MMLtext elements
    MMLNode *n = first;
    while (valid && n) {
        valid &= n->isText();
        if (!valid) {
            errmsg = "An mi element may contain only text and no elements.";
        }
        n = getNext(n);
    }
    validated = true;
    return valid;
}
void
MMLmi::doLayout(MML::Attributes *a) const {
    if (!first) return;

    first->layout(a);
    first->setX(0);
    gui->width = first->getWidth();
    gui->ascent = first->getAscent();
    gui->descent = first->getDescent();
}
void
MMLmi::doPaint(MML::Attributes *a) const {
    if (!first) return;
    first->paint(a);
}
