#include "mmlmtable.h"
#include "nodegui.h"
#include "mmlmtr.h"
using std::list;
#include "mathml.h"
#include "mmltext.h"
#include "attributes.h"
#include "mmlpainter.h"

MMLmtable::MMLmtable(MMLDocument *o)
    : MMLElement(MML::MTABLE, o) {

    // initialize the default values for the attributes once per element type
    if (!defset[id]) {
        defset[id] = true;
        const MMLAttribute **da = defatt[id];
        using namespace MML;
        createAttribute(ALIGN, "axis", id, da);
        createAttribute(ROWALIGN, "baseline", id, da);
        createAttribute(COLUMNALIGN, "center", id, da);
        createAttribute(GROUPALIGN, "{left}", id, da);
        createAttribute(ALIGNMENTSCOPE, "true", id, da);
        createAttribute(COLUMNWIDTH, "auto", id, da);
        createAttribute(WIDTH, "0", id, da); // this should be 'auto' but
	// because we use a unified type for all width attributes this is not
	// possible yet
        createAttribute(ROWSPACING, "1.0ex", id, da);
        createAttribute(COLUMNSPACING, "0.8em", id, da);
        createAttribute(ROWLINES, "none", id, da);
        createAttribute(COLUMNLINES, "none", id, da);
        createAttribute(FRAME, "none", id, da);
        createAttribute(FRAMESPACING, "0.4em 0.5ex", id, da);
        createAttribute(EQUALROWS, "false", id, da);
        createAttribute(EQUALCOLUMNS, "false", id, da);
        createAttribute(DISPLAYSTYLE, "false", id, da);
        createAttribute(SIDE, "right", id, da);
        createAttribute(MINLABELSPACING, "0.8em", id, da);
    }
}
bool
MMLmtable::validate() {
    if (validated) {
        return valid;
    }
    validated = true;
    validateChildren(-1); // 0 or more child elements
    MMLNode *n;
    for (n = first; n && valid; n = getNext(n)) {
        if (n->nodeName() != MML::elementTag[MML::MTR]
                && n->nodeName() != MML::elementTag[MML::MLABELEDTR]) {
            errmsg = "Element of type ";
            errmsg += tagName();
            errmsg += " may contain only elements 'mtr' and 'mlabeledtr'.";
            valid = false;
        }
    }
    return valid;
}
void
MMLmtable::doLayout(MML::Attributes *a) const {
    if (!first) return;

    float cw, ca, cd;
    cw = ca = cd = 0;
    MMLNode *n;
    // find the width for each column
    bool more = true;
    int i = 0;
    do {
        float mcw = 0;
        more = false;
        for (n = first; n; n = getNext(n)) {
            MMLNode *m = getFirst(n);
            for (int j = 0; m && j < i; j++) {
                m = getNext(m);
            }
            if (m) {
                m->layout(a);
                m->setX(cw);
                if (m->getWidth() > mcw) {
                    mcw = m->getWidth();
                }
                more = true;
            }
        }
        cw += mcw;
        ++i;
    } while (more);

    // layout the rows
    for (n = first; n; n = getNext(n)) {
        n->layout(a);
        MMLmtr *mtr = static_cast<MMLmtr *>(n);
        mtr->gui->width = cw;
        ca += n->getAscent();
        cd += n->getDescent();
    }
    float ca2 = 0;
    for (n = first; n; n = getNext(n)) {
        ca2 += n->getAscent();
        n->setY(-ca+ca2);
        ca2 += n->getDescent();
    }

    gui->width = cw;
    gui->ascent = ca;
    gui->descent = cd;
}
void
MMLmtable::doPaint(MML::Attributes *a) const {
    if (!first) return;

    float cw, ca, cd;
    cw = ca = cd = 0;
    MMLNode *n;
    for (n = first; n && valid; n = getNext(n)) {
        n->paint(a);
    }
}
