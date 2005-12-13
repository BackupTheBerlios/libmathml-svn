#include "mmlmtr.h"
#include "nodegui.h"
using std::list;
#include "mathml.h"
#include "mmltext.h"
#include "attributes.h"
#include "mmlpainter.h"

MMLmtr::MMLmtr(MMLDocument *o)
    : MMLElement(MML::MTR, o) {
}
bool
MMLmtr::validate() {
    if (validated) {
        return valid;
    }
    validated = true;
    validateChildren(-1);
    MMLNode *n;
    for (n = first; n && valid; n = getNext(n)) {
        if (n->nodeName() != MML::elementTag[MML::MTD]) {
            errmsg = "Element of type ";
            errmsg += tagName();
            errmsg += " may contain only elements 'mtd'.";
            valid = false;
        }
    }
    return valid;
}
void
MMLmtr::doLayout(MML::Attributes *a) const {
    // the layout for the row will be performed by its parent mtable
    float cw, ca, cd;
    cw = ca = cd = 0;
    MMLNode *n;
    for (n = first; n && valid; n = getNext(n)) {
//        n->layout(a);
        if (n->getAscent() > ca) {
            ca = n->getAscent();
        }
        if (n->getDescent() > cd) {
            cd = n->getDescent();
        }
        cw += n->getWidth();
    }
    gui->ascent = ca;
    gui->descent = cd;
}
void
MMLmtr::doPaint(MML::Attributes *a) const {
    MMLNode *n;
    for (n = first; n && valid; n = getNext(n)) {
        n->paint(a);
    }
}
