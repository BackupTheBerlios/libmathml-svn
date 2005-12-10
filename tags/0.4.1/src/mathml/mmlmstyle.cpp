#include "mmlmstyle.h"
#include "attributes.h"
#include "mmlmrow.h"
#include "nodegui.h"

MMLmstyle::MMLmstyle(MMLDocument *o)
    : MMLElement(MML::MSTYLE, o) {
}
MMLmstyle::MMLmstyle(MML::Element e, MMLDocument *o)
    : MMLElement(e, o) {
}
bool
MMLmstyle::validate() {
    if (validated) {
        return valid;
    }
    validated = true;
    validateChildren(-1);
    if (first != last || !first) {
        MMLmrow *mrow = owner->createInferredmrow(this);
        appendChild(mrow);
    }
    return valid;
}
void
MMLmstyle::doLayout(MML::Attributes *a) const {
    // since the MMLelement class takes care of layouting,
    // and Attributes class does the argument setting, mstyle does not
    // have to do anything special
    if (!first) return;
    first->layout(a);
    gui->width = first->getWidth();
    gui->ascent = first->getAscent();
    gui->descent = first->getDescent();
}
void
MMLmstyle::doPaint(MML::Attributes *a) const {
    if (first) {
        first->paint(a);
    }
}
