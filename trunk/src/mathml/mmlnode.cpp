#include "mmlnode.h"
#include "nodegui.h"
#include "mmltext.h"
#include "mmlviewport.h"
#include <iostream>
using namespace std;
#include <cassert>

/* states of a node:
   - unvalidated
   - invalid
   - valid (not layed out)
   - drawn (layout() has been called)

   What can be validated in a node?
   - attribute tags
   - attribute content
   - number of child elements
   - child elements
   - content of character data

   Each item that can be validated can be changed. For each of the changable
   items a function determning in advance if a change will result in a valid
   node is desirable for user interfaces: an action that could result in an
   invalid DOM shoulc be disabled.
   Ideally, invalid content should be stopped at the gates, but this is not
   always possible. For example, if a certain node requires two children,
   one has to be added first, creating an invalid element, until the second one
   is added.
*/

MMLNode::MMLNode(MMLDocument * const o)
        : owner(o) {
    parent = 0;
    prev = next = 0;
    first = last = 0;
    valid = true;
    validated = false;
    inferred = false;

    gui = new NodeGUI;
    gui->x = gui->y = gui->width = gui->ascent = gui->descent = 0;
    gui->selected = false;
    gui->firstviewport = gui->lastviewport = -1;
}
MMLNode::~MMLNode() {
    delete gui;
}
bool
MMLNode::validate() {
    valid = true;
    if (!first || validated) return valid;
    validated = true;

    MMLNode *node = first;
    do {
        valid = node->validate();
    } while (valid && node++ != last);
    return valid;
}
MMLNode *
MMLNode::parentNode_() const {
    MMLNode *p = parent;
    while (p && p->inferred) {
        p = p->parent;
    }
    return p;
}
/* return the first child of this node.
   if the first node is inferred but not completely inferred,
   the node's firstChild() is returned.
   if a the first node is allinferred, the next one is returned and so on. */
MMLNode *
MMLNode::firstChild_() const {
    MMLNode *node = first;
    MMLNode *fc = 0;
    // if a node is inferred, maybe one of it's children is not
    for (node = first; !fc && node; node = node->next) {
        fc = node;
        if (fc && fc->inferred) {
            fc = fc->firstChild();
        }
    }
    return fc;
}
MMLNode *
MMLNode::lastChild_() const {
    MMLNode *node = last;
    MMLNode *lc = 0;

    // if a node is inferred, maybe one of it's children is not
    for (node = last; !lc && node; node = node->prev) {
        lc = node;
        if (lc && lc->inferred) {
            lc = lc->lastChild();
        }
    }

    return lc;
}
// return the first 'next' that is not inferred
// if you want the inferred one, just use 'next'
MMLNode *
MMLNode::nextSibling_() const {
    const MMLNode *node = this;
    MMLNode *ns;

    // first look on this level
    do {
        node = ns = node->next;
        if (ns && ns->inferred) {
            ns = ns->firstChild();
        }
    } while (!ns && node);

    // and if the parent is inferred, on one level lower
    if (!ns && parent && parent->inferred) {
        ns = parent->nextSibling();
    }

    return ns;
}
MMLNode *
MMLNode::previousSibling_() const {
    const MMLNode *node = this;
    MMLNode *ps;

    // first look on this level
    do {
        node = ps = node->prev;
        if (ps && ps->inferred) {
            ps = ps->lastChild();
        }
    } while (!ps && node);

    if (!ps && parent && parent->inferred) {
        ps = parent->previousSibling();
    }
    return ps;
}
MMLNode *
MMLNode::insertBefore(MMLNode *newChild, MMLNode *refChild) {
    if (!newChild) return 0;
    // whatever happens next, this node is changed and needs to be
    // revalidated
    validated = false;
    // If refChild is null, insert newChild at the end of the list of children.
    if (!refChild) {
        appendChild(newChild);
        return newChild;
    }
    if (newChild->owner != owner) {
        // WRONG_DOCUMENT_ERR
        errmsg = "Node was created from a different document.";
        valid = false;
        validated = true;
        return newChild;
    }
    if (refChild->parent != this) {
        // NOT_FOUND_ERR
        errmsg = "Ref node is no child of this node.";
        valid = false;
        validated = true;
        return newChild;
    }
    // If the newChild is already in the tree, it is first removed.
    if (newChild->parent) {
        newChild->parent->removeChild(newChild);
    }
    // update relevant pointers
    newChild->parent = this;
    newChild->next = refChild;
    newChild->prev = refChild->prev;
    if (first == refChild) {
        first = newChild;
    } else {
        refChild->prev->next = newChild;
    }
    refChild->prev = newChild;
    return newChild;
}
MMLNode *
MMLNode::appendChild(MMLNode *newChild) {
    if (!newChild) return 0;
    if (newChild->owner != owner) {
        // WRONG_DOCUMENT_ERR
        errmsg = "Node was created from a different document.";
        assert(0);
        valid = false;
        validated = true;
        return newChild;
    }
    validated = false;
    if (newChild->parent) {
        newChild->parent->removeChild(newChild);
    }
    newChild->parent = this;
    newChild->next = 0;
    if (last) {
        newChild->prev = last;
        last->next = newChild;
        last = newChild;
    } else {
        newChild->prev = 0;
        first = last = newChild;
    }
    return newChild;
}
MMLNode *
MMLNode::removeChild(MMLNode *oldChild) {
    if (!oldChild) return 0;
    if (oldChild->parent != this) {
        // NOT_FOUND_ERR
        errmsg = "Node is no child of this node.";
        valid = false;
        validated = true;
        return oldChild;
    }
    validated = false;
    MMLNode *n = oldChild->next;
    MMLNode *p = oldChild->prev;

    if (p) {
        p->next = n;
    } else {
        first = n;
    }
    if (n) {
        n->prev = p;
    } else {
        last = p;
    }
    oldChild->parent = 0;
    oldChild->next = 0;
    oldChild->prev = 0;
    return oldChild;
}
void
MMLNode::setX(float x) const {
    gui->x = x;
}
void
MMLNode::setY(float y) const {
    gui->y = y;
}
void
MMLNode::setSelected(bool sel) const {
    gui->selected = sel;
}
/* return x position relative to non-inferred parent */
float
MMLNode::getX() const {
    MMLNode *p;
    p = this->parent;
    float gx = gui->x;
    while (p && p->isInferred()) {
        gx += p->gui->x;
        p = p->parent;
    }
    return gx;
}
/* return y position relative to non-inferred parent */
float
MMLNode::getY() const {
    MMLNode *p;
    p = this->parent;
    float gy = gui->y;
    while (p && p->isInferred()) {
        gy += p->gui->y;
        p = p->parent;
    }
    return gy;
}
float
MMLNode::getWidth() const {
    return gui->width;
}
float
MMLNode::getHeight() const {
    return gui->ascent + gui->descent;
}
float
MMLNode::getAscent() const {
    return gui->ascent;
}
float
MMLNode::getDescent() const {
    return gui->descent;
}
bool
MMLNode::isSelected() const {
    return gui->selected;
}
void
MMLNode::printTree(int level) const {
    for (int i=0; i<level; ++i) cout << "   ";
    if (inferred) {
        cout << "(" << nodeName() << ")";
    } else {
        cout << nodeName();
    }
    if (isText()) {
        const MMLText *t = static_cast<const MMLText *>(this);
        cout << ": '" << t->data().utf8() << "'";
    }
    cout << endl;
    for (MMLNode *n = first; n; n = n->next) {
        n->printTree(level+1);
    }
}
bool
MMLNode::drawInViewPort(ushort v) const {
    return gui->firstviewport == -1 || gui->lastviewport == -1
        || (v >= gui->firstviewport && v <= gui->lastviewport);
}
bool
MMLNode::fit() const {
    MMLViewPort *vp = owner->currentView();
    vp->translate(gui->x, gui->y);
    bool fit = true;
    if (!first) { // no children
        fit = vp->fit(gui->width, gui->ascent, gui->descent);
        if (fit) {
            vp->add(gui->width, gui->ascent, gui->descent);
            gui->firstviewport =
                gui->lastviewport = owner->currentViewNo();
        }
    } else { // try to fit all children
        MMLNode *n;
        for (n = first; fit && n; n = n->next) {
            // if not completely fitted in any viewport yet
            if (n->gui->lastviewport == -1) {
                fit = n->fit();
            }
        }
        gui->firstviewport = first->gui->firstviewport;
        gui->lastviewport = last->gui->lastviewport;
    }
    vp->translate(-gui->x, -gui->y);
    return fit;
}
