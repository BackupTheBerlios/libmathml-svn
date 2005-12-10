#include "boundpoint.h"
#include "mmldocument.h"
#include "mmltext.h"
#include <iostream>
using namespace std;

BoundPoint::BoundPoint(MMLDocument *o) {
    // initally, the boundary points are positioned at the beginning of the
    // corresponding document
    ancestry.resize(2);
    ancestry[0] = o;
    reset();
}
// position boundary at begining of document
void
BoundPoint::reset() {
    ancestry.resize(2);
    if (ancestry[0]) {
        ancestry[1] = ancestry[0]->firstChild();
    } else {
        ancestry[1] = 0;
    }
    level = 0;
    offs = 0;
}
MMLNode *
BoundPoint::container() const {
    return ancestry[level];
}
long
BoundPoint::offset() const {
    // if offs < 0, it has changed and needs to be recalculated
    if (offs < 0) {
        offs = 0;
        MMLNode *c = ancestry[level+1];
        MMLNode *n = ancestry[level]->firstChild();
        while (c != n) {
            offs++;
            n = n->nextSibling();
        }
    }
    return offs;
}
bool
BoundPoint::endOfContainer() const {
    bool end;
    MMLNode *c = container();
    if (c->isText()) {
        const MMLText *t = static_cast<const MMLText *>(c);
        end = t->data().length() == uint(offset());
    } else {
        end = rightNode() == 0;
    }
    return end;
}
/* return the child of containter which is to the right of the bounding point */
MMLNode *
BoundPoint::leftNode() const {
    if (ancestry[level+1]) {
        return ancestry[level+1]->nextSibling();
    } else {
        return ancestry[level]->lastChild();
    }
}
MMLNode *
BoundPoint::rightNode() const {
    return ancestry[level+1];
}
/* return the nearness of node n to the current node.
   return value:
     0  n is the container
     1  n is the parent of the container
     2  n is the grandparent of the container etc.
    -1  n is not an ancestor of the current boundpoint
*/
int
BoundPoint::isAncestor(const MMLNode *n) const {
    if (!n || n->isInferred()) return -1;
    // walk along the ancestry line to find node n
    int size = ancestry.size();
    int pos = size;
    for (int i=0; i<size && pos == size; ++i) {
        if (n == ancestry[i]) {
            pos = i;
        }
    }
    pos = level - pos;
    if (pos < -1) pos = -1;
    return pos;
}
void
BoundPoint::setBefore(MMLNode *node) {
    if (!node) {
        reset();
        return;
    }
    // try to keep memory: if node is in ancestry, only change the level
    uint i = 0;
    uint asize = ancestry.size();
    uint newlevel = asize;
    for (i=0; i<asize; ++i) {
        if (ancestry[i] == node) {
            newlevel = i-1;
            i = asize;
        }
    }
    if (newlevel == asize) { // node was not found
        setBeforeClean(node);
    } else if (newlevel != level) {
        offs = -1; // offs has changed
        level = newlevel;
    }
}
void
BoundPoint::setBeforeClean(MMLNode *node) {
    // internal function: we know that node != 0
    // count the number of levels
    uint newsize = 0;
    MMLNode *p = node;
    while (p) {
        ++newsize;
        p = p->parentNode();
    }
    if (ancestry.size() < newsize) {
        ancestry.resize(newsize);
    }
    uint i = newsize;
    p = node;
    while (i) {
        ancestry[--i] = p;
        p = p->parentNode();
    }
    level = newsize - 2;
    offs = -1; // offs has changed
}
void
BoundPoint::set(MMLNode *node, long offset) {
    if (!node) {
        reset();
        return;
    }

    if (node->isText()) {
        const MMLText *t = static_cast<const MMLText *>(node);
        if (offset > long(t->data().length()+1)) {
            // INDEX_SIZE_ERR
            return;
        }
        setBeforeClean(node);
        level++;
        ancestry.resize(level+2);
        ancestry[level+1] = 0;
        offs = offset;
        return;
    }

    // find the node before which to stand
    MMLNode *bf = node->firstChild();
    while (offset--) {
        bf = bf->nextSibling();
        if (!bf) {
            // INDEX_SIZE_ERR
            return;
        }
    }
    setBefore(bf);
    offs = offset;
}
void
BoundPoint::setAfter(MMLNode *node) {
    setBefore(node);
    ancestry[level+1] = ancestry[level+1]->nextSibling();
}
/*  move to the next bounding point position*/
MMLNode *
BoundPoint::moveNext() {
    MMLNode *current = ancestry[level];

    uint nextlevel;
    MMLNode *nextnode = findNext(nextlevel);

    if (nextlevel < level) {
        ancestry.resize(level+1);
        ancestry[level] = current->nextSibling();
        offs = -1;
    } else if (nextlevel > level) {
        ancestry.resize(level+3);
        ancestry[level+2] = nextnode->firstChild();
        offs = 0;
    } else if (current->isText()) {
        offs++;
    }
    current = ancestry[nextlevel] = nextnode;
    level = nextlevel;
    nextnode = findNext(nextlevel);
//    printancestry();
    return current;
}
/*  move to the previous bounding point position*/
MMLNode *
BoundPoint::movePrevious() {
    MMLNode *current = ancestry[level];

    uint prevlevel;
    MMLNode *prevnode = findPrev(prevlevel);

    if (prevlevel < level) {
        offs = -1;
    } else if (prevlevel > level) {
        ancestry.resize(level+3);
        ancestry[level+2] = 0;
        if (prevnode->isText()) {
            const MMLText *t = static_cast<const MMLText *>(prevnode);
            offs = long(t->data().length());
        } else {
            offs = -1;
        }
    } else if (current->isText()) {
        offs--;
    }
    current = ancestry[prevlevel] = prevnode;
    level = prevlevel;
    prevnode = findPrev(prevlevel);
//    printancestry();
    return current;
}
void
BoundPoint::printancestry() const {
    for (uint i=0; i<ancestry.size(); ++i) {
        if (ancestry[i]) {
            cout << ancestry[i]->nodeName() << " "
             << isAncestor(ancestry[i]) << "->";
        } else {
            cout << "0";
        }
    }
    cout << endl;
}
MMLNode *
BoundPoint::moveUp() {
    MMLNode *current = ancestry[level];

    // if we are at the last position in the current node, start moving up
    // from the last child
    MMLNode *node = ancestry[level+1];
    if (!node) {
        node = current->lastChild();
        ancestry[level+1] = node;
    }

    // only move up if there is something to move up to
    if (node) {
        ++level;
        offs = -1;
        if (ancestry.size() < level + 2) {
            ancestry.resize(level+2);
            ancestry[level+1] = ancestry[level]->firstChild();
        }
    }
//    printancestry();
    return ancestry[level];
}
MMLNode *
BoundPoint::moveDown() {
    if (level == 0) return ancestry[level];
    --level;
    offs = -1;
//    printancestry();
    return ancestry[level];
}
void
BoundPoint::setCurChild(MMLNode *n) {
    if (ancestry.size() < level + 2) {
        ancestry.resize(level+2);
    }
    ancestry[level+1] = n;
}
bool
BoundPoint::atStart() const {
    return level == 0 && ancestry[1] == ancestry[0]->firstChild();
}
bool
BoundPoint::atEnd() const {
    return level == 0 && ancestry[1] == 0;
}
MMLNode *
BoundPoint::findNext(uint &nextlevel) const {
    MMLNode *current = ancestry[level];
    // if the cursor is positioned at the end, just return current
    if (atEnd()) {
        nextlevel = 0;
        return current;
    }
    // if the current container is a text, move inside it
    if (current->isText()) {
        // if we can still move within the text node, the next node
        // is the text node
        const MMLText *t = static_cast<const MMLText *>(current);
        if (offs+1 <= long(t->data().length())) {
            nextlevel = level;
            return current;
        }
    }

    // try to move inside the child before which we are standing
    MMLNode *node = ancestry[level+1];
    if (node) {
        nextlevel = level+1;
    } else { // if we cannot walk up, we walk down
        nextlevel = level-1;
        node = ancestry[nextlevel];
    }
    return node;
}
MMLNode *
BoundPoint::findPrev(uint &prevlevel) const {
    MMLNode *current = ancestry[level];
    // if the cursor is positioned at the begining, just return current
    if (atStart()) {
        prevlevel = 0;
        return current;
    }
    // if the current node is a text node, move within the text node
    if (current->isText() &&  offs > 0) {
        prevlevel = level;
        return current;
    }

    // the node mentioned in the ancestry at level+1 is the one to the
    // right of the current point. We need the one to the left of it.
    MMLNode *prev = ancestry[level+1];
    if (prev) {
        prev = prev->previousSibling();
    } else {
        prev = current->lastChild();
    }
    if (prev) {
        // if there is a previous node, go to it
        // set the node to the now current level
        prevlevel = level+1;
    } else {
        prevlevel = level-1;
        prev = ancestry[prevlevel];
    }
    return prev;
}
/**
 * Return the highest common ancestor of the current node with the node bp.
 * The value returned is only 0 if the BoundPoints do not have a common
 * ancestor.
 */
MMLNode *
BoundPoint::highestCommonAncestor(const BoundPoint &bp) const {
    // if the nodes being compared do not have the same root, return 0
    if (ancestry[0] != bp.ancestry[0]) return 0;
    // determine which of the boundpoints has the lowest hierchy level
    uint l = level;
    if (l > bp.level) {
        l = bp.level;
    }
    uint i=1;
    while (i <= l && ancestry[i] == bp.ancestry[i]) ++i;
    return ancestry[i-1];
}
/*const MMLNode *
BoundPoint::lowestUncommonAncestor(const MMLNode *n) const {
    if (!n || ancestry[0] != n->ownerDocument()) return 0;
    // determine level of n
    uint nl = 0;
    const MMLNode *a = n;
    while (a->parentNode()) {
        a = a->parentNode();
        nl++;
    }
    uint l = level;
    a = n;
    while (nl > l) {
        a = a->parentNode();
        nl--;
    }
    if (nl < l) {
        l = nl;
    }
    while (l && a->parentNode() != ancestry[l-1]) {
        a = a->parentNode();
        --l;
    }
    if (l) return a;
    return 0;
}*/
MMLNode *
BoundPoint::higherAncestor(const MMLNode *n) const {
    if (!n || ancestry[0] != n->ownerDocument()) return 0;
    MMLNode *a = 0;
    uint i = 0;
    while (i <= level && ancestry[i] != n) ++i;
    if (i <= level) {
        a = ancestry[i+1];
        if (!a) a = ancestry[i];
    }
    return a;
}
bool
BoundPoint::operator==(const BoundPoint &bp) const {
    return ancestry[level] == bp.ancestry[bp.level]
            && offset() == bp.offset();
}
bool
BoundPoint::operator!=(const BoundPoint &bp) const {
    return !(*this == bp);
}
/**
 * Determine which of the two nodes appears first in the DOM tree.
 * If the current node appears earlier in the tree, true is returned.
 * If not, or the answer is undetermined, return false;
 */
bool
BoundPoint::isEarlierThan(const BoundPoint &b) const {
    // find the highest common ancestor of the two boundpoints
    const MMLNode *hca = highestCommonAncestor(b);
    if (!hca) return false;

    // find the hightest ancestor for a and b that is not equal
    const MMLNode *an = higherAncestor(hca);
    const MMLNode *bn = b.higherAncestor(hca);
    bool earlier;
    if (an == bn) {
        if (level != b.level) {
            earlier = level < b.level;
        } else {
            earlier = offset() < b.offset();
        }
    } else {
        // try to find if 'nb' is present after 'an'
        while (an && an != bn) {
            an = an->nextSibling();
        }
        earlier = an == bn;
    }
    return earlier;
}
