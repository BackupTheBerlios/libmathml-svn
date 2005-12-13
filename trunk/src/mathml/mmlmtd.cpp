#include "mmlmtd.h"
#include "nodegui.h"
using std::list;
#include "mathml.h"
#include "mmltext.h"
#include "mmlmrow.h"
#include "attributes.h"
#include "mmlpainter.h"

MMLmtd::MMLmtd(MMLDocument *o)
    : MMLElement(MML::MTD, o) {
    // initialize the default values for the attributes once per element type
    if (!defset[id]) {
        defset[id] = true;
        const MMLAttribute **da = defatt[id];
        using namespace MML;
        createAttribute(ROWSPAN, "1", id, da);
        createAttribute(COLUMNSPAN, "1", id, da);
    }
}
bool
MMLmtd::validate() {
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
MMLmtd::doLayout(MML::Attributes *a) const {
    first->layout(a);
    gui->width = first->getWidth();
    gui->ascent = first->getAscent();
    gui->descent = first->getDescent();
}
void
MMLmtd::doPaint(MML::Attributes *a) const {
    a->setAttribute(MML::MATHCOLOR, "red");
    first->paint(a);
}
