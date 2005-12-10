#include "mmlmerror.h"
#include "mmlmrow.h"
#include "attributes.h"
#include "nodegui.h"

MMLmerror::MMLmerror(MMLDocument *o)
    : MMLElement(MML::MERROR, o) {
}
bool
MMLmerror::validate() {
    if (validated) {
        return valid;
    }
    validated = true;
    validateChildren(1, true);

    if (first != last) {
        MMLmrow *mrow = owner->createInferredmrow(this);
        appendChild(mrow);
    }
    return valid;
}
void
MMLmerror::doLayout(MML::Attributes *a) const {
    if (!first) return;
    first->layout(a);
    gui->width = first->getWidth();
    gui->ascent = first->getAscent();
    gui->descent = first->getDescent();
}
void
MMLmerror::doPaint(MML::Attributes *a) const {
    if (first) {
        a->setAttribute(MML::MATHCOLOR, "red");
        first->paint(a);
    }
}
