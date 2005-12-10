#include "mmlmfenced.h"
#include "nodegui.h"
#include "attributes.h"
#include "mmlmrow.h"
#include "mmlmo.h"
#include "mmltext.h"
using std::list;
#include <iostream>
using namespace std;

MMLmfenced::MMLmfenced(MMLDocument *o)
    : MMLElement(MML::MFENCED, o) {

    if (!defset[id]) {
        defset[id] = true;
        const MMLAttribute **da = defatt[id];
        using namespace MML;
        MML::createAttribute(MML::OPEN, "(", id, da);
        MML::createAttribute(MML::CLOSE, ")", id, da);
        MML::createAttribute(MML::SEPARATORS, ",", id, da);
    }
}
#include <list>
bool
MMLmfenced::validate() {
    if (validated) {
        return valid;
    }
    validated = true;
    validateChildren(-1);
    if (!valid) return false;

    // for now, the implementation is rather expensive: instead of checking
    // the existing inferred elements, we just remove all of them and start
    // anew

    // the mfenced element should always have one inferred mrow.
    // if it doesn't have this, we create it
    MMLNode *mrow;
    if (!first || first != last || !first->isInferred()
        || first->nodeName() != MML::elementTag[MML::MROW]) {
        mrow = owner->createInferredmrow(this);
        appendChild(mrow);
    } else {
        mrow = first;
    }

    // the first element must be an inferred mo element and the text in
    // the element must correspond to the attribute 'open'
    MMLmo *mo;
    if (!getFirst(mrow)
        || getFirst(mrow)->nodeName() != MML::elementTag[MML::MO]
        || !mrow->isInferred()) {
        mo = owner->createInferredmo("(");
        mrow->insertBefore(mo, getFirst(mrow));
    }

    // now node points to the last child of mrow
    // this node must be an inferred mo element
    MMLNode *node = getLast(mrow);
    if (!node || !node->isInferred() || node == getFirst(mrow)
        || node->nodeName() != MML::elementTag[MML::MO]) {
        mo = owner->createInferredmo(")");
        mrow->appendChild(mo);
    }

    return valid;
}
ushort
MMLmfenced::getSeparator(short i, const DOMString &s) const {
    uint spos = 0;
    short nsep = -1;
    ushort cursep = ' ';
    for (spos=0; nsep < i && spos < s.length(); ++spos) {
        if (!DOMString::isWhitespace(s[spos])) {
            cursep = s[spos];
            ++nsep;
        }
    }
    return cursep;
}
void
MMLmfenced::setSeparators(const DOMString &s) const {
    short nsep = 0;
    MMLNode *node = getNext(getFirst(first));
    MMLNode *mlast = first->lastChild();
    MMLNode *sep = getNext(node);
    if (DOMString::isWhitespace(getSeparator(nsep, s))) {
        // remove all separator mo elements
        while (node && node != mlast) {
            sep = getNext(node);
            if (node->isInferred()) {
                first->removeChild(node);
                node = sep;
            } else {
                node = getNext(node);
            }
        }
    } else {
        while (node && node != mlast) {
            sep = getNext(node);
            if (node->isInferred()) {
                first->removeChild(node);
                node = sep;
            } else if (!sep->isInferred()) {
                DOMString cs;
                cs += getSeparator(nsep++, s);
                MMLNode *mo = owner->createInferredmo(cs);
                first->insertBefore(mo, sep);
                node = sep;
            } else {
                node = getNext(sep);
            }
        }
    }
}
void
MMLmfenced::doLayout(MML::Attributes *a) const {
    MMLText *text = static_cast<MMLText *>(getFirst(getFirst(first)));
    text->setData(a->open());
    text = static_cast<MMLText *>(getFirst(getLast(first)));
    text->setData(a->close());
    setSeparators(a->separators());
    // if the attribute 'separator' is empty or contains only whitespace,
    // the separator mo elements should be removed

    const MMLNode *n = first;
    n->layout(a);
    gui->width = n->getWidth();
    gui->ascent = n->getAscent();
    gui->descent = n->getDescent();
}
void
MMLmfenced::doPaint(MML::Attributes *a) const {
    first->paint(a);
}
