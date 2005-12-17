#include "mmlelement.h"
#include "nodegui.h"
#include "mathml.h"
#include "mmltext.h"
#include "attributes.h"
#include "mmlpainter.h"
#include "mathcursor.h"
#include <iostream>
using std::cerr;
using std::endl;

const MMLAttribute **MMLElement::defatt[MML::numElements];
bool MMLElement::defset[MML::numElements];
uint MMLElement::count = 0;

MMLElement::MMLElement(MML::Element e, MMLDocument *o)
    : MMLNode(o), id(e) {
    numAtts = MML::attListLen[id];
    initAtts();
    // allocate memory for pointers to default attribute values
    if (count++ == 0) {
        //defatt = new MMLAttribute**[numElements];
        for (uint i=0; i<MML::numElements; ++i) {
            defatt[i] = 0;
            defset[i] = false;
        }
    }
    if (defatt[id] == 0) {
        defatt[id] = new const MMLAttribute*[numAtts];
        for (short i=0; i<numAtts; ++i) {
            defatt[id][i] = 0;
        }
    }
}
MMLElement::~MMLElement() {
    deleteAtts();
    if (--count == 0) {
        for (uint i=0; i<MML::numElements; ++i) {
            if (defatt[i]) {
                short n = MML::attListLen[i];
                for (short j=0; j<n; ++j) {
                    if (defatt[i][j]) {
                        delete defatt[i][j];
                    }
                }
                delete [] defatt[i];
            }
            defset[i] = false;
        }
    }
}
const char *
MMLElement::tagName() const {
    return MML::elementTag[id];
}
void
MMLElement::initAtts() {
    att = new const MMLAttribute*[numAtts];
    tmpatt = new const MMLAttribute*[numAtts];
    for (short i=0; i<numAtts; ++i) {
        att[i] = 0;
    }
}
/* Delete the array that stores the MMLAttributes associated with this element.
   The array which temporarily holds the global values. */
void
MMLElement::deleteAtts() {
    if (att) {
        for (short i=0; i<numAtts; ++i) {
            if (att[i] && att[i]->cleanup) {
                delete att[i];
            }
        }
        delete [] att;
        delete [] tmpatt;
    }
}
bool
MMLElement::setAttribute(const char *name, const DOMString &value) {
    if (!strcmp(name, "color")) {
        name = "mathcolor";
    } else if (!strcmp(name, "background")) {
        name = "mathbackground";
    }
    bool ok = true;
    int pos = MML::createAttribute(name, value, id, att);
    if (pos == -1) {
        ok = false;
        invalidAttribute(name);
    } else if (pos == -2) {
        ok = false;
        invalidValue(name, value);
    }
    return ok;
}
void
MMLElement::invalidAttribute(const char *n) {
    errmsg = "Attribute '";
    errmsg += n;
    errmsg += "' not allowed in element ";
    errmsg += tagName();
    errmsg += ".";
}
void
MMLElement::invalidValue(const char *name, const DOMString &value) {
    errmsg = "attribute '";
    errmsg += name;
    errmsg += "' cannot have value '" + value + "' in element ";
    errmsg += tagName();
    errmsg += ".";
}
void
MMLElement::layout(MML::Attributes *a) const {
    // reset the coordinates and dimensions
    gui->resetCoords();
    a->setAttributes(this);
    doLayout(a);
    a->unsetAttributes(this);
    gui->firstviewport = gui->lastviewport = -1;
}
void
MMLElement::paint(MML::Attributes *a) const {
    // only draw if the element is present in the current viewport
    if (!drawInViewPort(owner->currentViewNo())) return;
    a->setAttributes(this);
    a->p->translate(gui->x, gui->y);
    int nearness = -1;
    MathCursor *mc = owner->cursor();
    if (mc) {
        nearness = mc->nearness(this);
    }
    if (mc && mc->isSelected(this)) {
        // draw background for selected
        MathColor sb = a->p->selectionColor();
        a->setAttribute(MML::MATHBACKGROUND, sb);
        a->p->fillRect(0, -gui->ascent, gui->width,
            gui->ascent+gui->descent);
    } else if (nearness >= 0 && mc->collapsed()) {
        MathColor sb = a->p->highlightColor(nearness);
        MathColor sc = a->p->highlightColor(0);
        a->setAttribute(MML::MATHBACKGROUND, sb);
        a->p->fillRect(0, -gui->ascent, gui->width,
            gui->ascent + gui->descent, sb, sc);
    }
    doPaint(a);
    // draw caret
    if (mc && mc->container() == this) {
        MMLNode *n = mc->rightNode();
        float cx, ca, cd;
        if (n) {
            cx = n->getX();
        } else {
            n = mc->leftNode();
            if (n) {
                cx = n->getX()+n->getWidth();
            } else {
                cx = gui->width;
            }
        }
        if (n) {
            cd = n->getDescent() + n->getY();
            ca = n->getAscent() - n->getY();
        } else {
            cd = gui->descent;
            ca = gui->ascent;
        }
        a->p->drawLine(cx, -ca, cx, cd, 2);
    }
    a->p->translate(-gui->x,-gui->y);
    a->unsetAttributes(this);
}
void
MMLElement::normalize() {
    MMLNode *p;
    MMLText *t = 0;
    p = first;
    while (p) {
        if (p->isText()) {
            MMLText *t2 = static_cast<MMLText *>(p);
            if (t) {
                t->appendData(t2->data());
                removeChild(t2);
                p = t;
            } else {
                t = t2;
            }
        } else {
            t = 0;
        }
        p = getNext(p);
    }
    validated = false;
}
// this is a check for non-token elements: it checks that there are no
// nodes of type text
// do not call this function on a known invalid function, because
// initially the bool 'valid' is set to true
void
MMLElement::validateChildren(int num, bool orMore) {
    int count = 0;
    // check the number of arguments
    MMLNode *n;
    valid = true;
    for (n = first; valid && n; n = getNext(n)) {
        valid = !n->isText();
        count++;
    }
    if (!valid) {
        errmsg = "Element of type ";
        errmsg += tagName();
        errmsg += " may not contain text without markup.";
        return;
    }
    if (num >= 0) { // num < 0 means: any number is ok
        if (orMore && count < num) {
            errmsg = "Element of type ";
            errmsg += tagName();
            errmsg += " must contain at least "
                + DOMString::number(num) + " children.";
            valid = false;
            return;
        }
        if (!orMore && count != num) {
            errmsg = "Element of type ";
            errmsg += tagName();
            errmsg += " must contain exactly "
                + DOMString::number(num) + " children.";
            valid = false;
            return;
        }
    }
    // validate all children, this not done before because it is expensive
    // and useless if the number of children is not correct
    // also, stop validating as soon as one element is invalid
    valid = true;
    for (n = first; valid && n; n = getNext(n)) {
        valid = n->validate();
    }
}
