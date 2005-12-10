#include "mmldocument.h"
using std::list;
using std::vector;
#include "mmlmi.h"
#include "mmlmn.h"
#include "mmltext.h"
#include "mmlmfrac.h"
#include "mmlmo.h"
#include "mmlmtext.h"
#include "mmlmrow.h"
#include "mathcolor.h"
#include "mmlmstyle.h"
#include "mmlmath.h"
#include "mmlmsub.h"
#include "mmlmsup.h"
#include "mmlmsubsup.h"
#include "mmlmerror.h"
#include "mmlmsqrt.h"
#include "mmlmroot.h"
#include "mmlmfenced.h"
#include "mmlmphantom.h"
#include "attributes.h"
#include "mmlpainter.h"
#include "mathcursor.h"
#include "constmathcursor.h"
#include "mmlviewport.h"
#include <iostream>
using std::cerr;
using std::endl;
#include <cassert>

MMLDocument::MMLDocument() : MMLNode(this) {
    root = 0;
    border = 25;
    active = 0;
    mathcursor = new MathCursor(this);
    constmathcursor = new ConstMathCursor(mathcursor);
    a = new MML::Attributes();
    v = new Views;
    v->views.resize(1);
    v->views[0].setOwner(this);
    v->cv = 0;
    v->curview = &(v->views[0]);
}
MMLDocument::~MMLDocument() {
    list<MMLNode *>::iterator it;
    for (it=nodes.begin(); it != nodes.end(); ++it) {
        delete *it;
    }
    delete constmathcursor;
    delete mathcursor;
    delete a;
    delete v;
}
MMLElement *
MMLDocument::createElement(const DOMString &tagName) {
    MMLElement *mmle;
    if (tagName == "mi") {  // ever heard of switch statements?
        mmle = new MMLmi(this);
    } else if (tagName == "mn") {
        mmle = new MMLmn(this);
    } else if (tagName == "mo") {
        mmle = new MMLmo(this);
    } else if (tagName == "mtext") {
        mmle = new MMLmtext(this);
    } else if (tagName == "mfrac") {
        mmle = new MMLmfrac(this);
    } else if (tagName == "mrow") {
        mmle = new MMLmrow(this);
    } else if (tagName == "mphantom") {
        mmle = new MMLmphantom(this);
    } else if (tagName == "msub") {
        mmle = new MMLmsub(this);
    } else if (tagName == "msup") {
        mmle = new MMLmsup(this);
    } else if (tagName == "msubsup") {
        mmle = new MMLmsubsup(this);
    } else if (tagName == "msqrt") {
        mmle = new MMLmsqrt(this);
    } else if (tagName == "mroot") {
        mmle = new MMLmroot(this);
    } else if (tagName == "mfenced") {
        mmle = new MMLmfenced(this);
    } else if (tagName == "mstyle") {
        mmle = new MMLmstyle(this);
    } else if (tagName == "math") {
        mmle = new MMLmath(this);
    } else if (tagName == "merror") {
        mmle = new MMLmerror(this);
    } else {
        bool allowed = false;
        for (uint i=0; !allowed && i<MML::numElements; ++i) {
            allowed = tagName == MML::elementTag[i];
        }
        if (allowed) {
            errmsg = "Tag '" + tagName
                + "' is not available in this implementation.";
        } else {
            errmsg = "Tag '" + tagName
            + "' is not allowed in MathML.";
        }
        valid = false;
        validated = true;
        mmle = NULL;
    }
    if (mmle) {
        nodes.push_back(mmle);
    }
    return mmle;
}
MMLText *
MMLDocument::createTextNode(const DOMString &s) {
    MMLText *mmlt = new MMLText(this);
    mmlt->setData(s);
    if (mmlt) {
        nodes.push_back(mmlt);
    }
    return mmlt;
}
MMLmrow *
MMLDocument::createInferredmrow(MMLElement *e) {
    // create the inferred mrow
    MMLmrow *mrow = new MMLmrow(this);
    mrow->inferred = true;
    nodes.push_back(mrow);

    // move all children of e to the new mrow
    MMLNode *n = e->first;
    while (n) {
        mrow->appendChild(n); // n is automatically removed from e
        n = e->first;
    }
    return mrow;
}
MMLmo *
MMLDocument::createInferredmo(const DOMString &s) {
    // create the inferred mo
    MMLmo *mo = new MMLmo(this);
    mo->inferred = true;
    nodes.push_back(mo);
    MMLText *text = createTextNode(s);
    text->inferred = true;
    mo->appendChild(text);
    return mo;
}
/* This function checks that the document has exactly one node of type
   element. */
void
MMLDocument::checkRoot() {
    if (!valid) return;
    MMLNode *n = first;
    valid = false;
    while (n) {
        if (n->isElement()) {
            // if root is not yet set or points to a removed element
            if (!root || root->parentNode() != this) {
                root = static_cast<MMLElement *>(n);
                valid = true;
            } else if (root != n) {
                errmsg = "MMLDocument must contain exactly "
                        "one math element.";
                valid = false;
            }
        }
        n = n->next;
    }
}
const MMLElement *
MMLDocument::documentElement() const {
    return root;
}
MMLElement *
MMLDocument::documentElement() {
    return root;
}
bool
MMLDocument::validate() {
    if (!validated) {
        checkRoot();
        if (valid) {
            if (!root->validate()) {
                errmsg = root->errorMsg();
                valid = false;
            } else {
                valid = true;
            }
        }
        validated = true;
    }
    return valid;
}
bool
MMLDocument::validate() const {
    return validated && valid;
}
void
MMLDocument::layout(MML::Attributes *a) const {
    root->doLayout(a);
    root->setX(0);
    root->setY(0);
    v->curview->setWidth(root->getWidth());
    v->curview->setAscent(root->getAscent());
    v->curview->setDescent(root->getDescent());
}
void
MMLDocument::setPainter(MMLPainter *p) const {
    a->setPainter(p);
}
void
MMLDocument::layout() const {
    if (a->p && validate()) {
        layout(a);
        // initialize the viewport
        v->views.resize(1);
        v->curview = &(v->views[0]);
        v->curview->setBegin();
        v->curview->setEnd();
    }
}
bool
MMLDocument::setMaxViewWidth(float maxwidth) const {
    v->curview->setMaxWidth(maxwidth);
    MMLNode *n = v->curview->getBegin().rightNode();
    // walk tree until width is overrun
    float width = 0;
/*    do {
    } while (width < maxwidth);
    if (width > maxwidth) {
    }*/
    return false;
}
void
MMLDocument::paint() const {
    if (a->p && validate()) {
        float x = getX();
        float y = getY();
        a->p->translate(x,y);
        root->doPaint(a);
        // debug code: we draw the point the cursor was last set to
        if (mathcursor) {
            float cy = mathcursor->getY();
            float cx = mathcursor->getX();
            a->p->drawLine(cx, cy, cx, cy);
        }
        a->p->translate(-x,-y);
    }
}
MathCursor *
MMLDocument::cursor() {
    return mathcursor;
}
ConstMathCursor *
MMLDocument::constcursor() const {
    return constmathcursor;
}
uint
MMLDocument::countViewPorts() const {
    return v->views.size();
}
void
MMLDocument::setCurrentView(ushort cv) const{
    assert(cv < v->views.size());
    v->cv = cv;
    v->curview = &(v->views[cv]);
}
void
MMLDocument::setX(float x) const {
    v->curview->setX(x);
}
void
MMLDocument::setY(float y) const {
    v->curview->setY(y);
}
float
MMLDocument::getX() const {
    return v->curview->getX();
}
float
MMLDocument::getY() const {
    return v->curview->getY();
}
// TODO fix the name of this function because it's unintuitive
float
MMLDocument::getWidth() const {
    return v->curview->getWidth();
}
// TODO fix the name of this function because it's unintuitive
float
MMLDocument::getHeight() const {
    return getAscent()+getDescent();
}
float
MMLDocument::getAscent() const {
    return v->curview->getAscent();
}
float
MMLDocument::getDescent() const {
    return v->curview->getDescent();
}
