#include "mathcursor.h"
#include "mmldocument.h"
#include "mmlelement.h"
#include "mmltext.h"
#include <iostream>
using namespace std;

MathCursor::MathCursor(MMLDocument *o)
	: owner(o), cur(o), sel(o) {
	targetlevel = 0;
	x = y = 0;
	collaps = true;
	curmouse = true;
	start = &cur;
	end = &sel;
}
/* moving can also stop inside text elements e.g.
     <mfrac><mi>abcd<mglyph .../>efg</mi><mo>!</mo>
   this is not common, but it is possible. The cursur can be positioned
     <mfrac>^<mi>^a^b^c^d^<mglyph .../>^e^f^g^</mi>^<mo>^!^</mo>^</mfrac>
   because the texts are in a special text elements, denoted with square
   brackets:
     <mfrac><mi>[ab][cd]<mglyph .../>[efg]</mi><mo>[!]</mo>
   We allow the cursor at these positions:
     <mfrac>^<mi>*[^a^b*]*[^c^d*]^<mglyph .../>
     *[^e^f^g*]^</mi>^<mo>*[^!*]^</mo>^</mfrac>
   The stars give positions that are redundant.
   With two simple rules we can avoid the cursor visiting the redundant
   positions:
    - the cursor may never stop before a MMLText node
    - the cursor may never stop at the last position in a MMLText node
   By defining the rules in this way, we only need to check for the direct
   precence of a MMLText and avoid costly preemptive action such as checking
   all children of a node.
   Adhering to the second rule is easy: just check the value of offset.
   The first rule is a bit more difficult. It can be implemented recursively:
   when the result of 'moveNext' is a text node at ancetry[level+1], do one
   more step. */

/*  move to the next sibling */
MMLNode *
MathCursor::moveNext() {
	do {
		cur.moveNext();
//	cout << "> " << cur.container()->nodeName() << ", " << cur.offset() << endl;
	} while (!cur.atEnd() && unwantedPos(cur));
	collapse();
	curmouse = false;
	return cur.container();
}
void
MathCursor::selectNext() {
	if (collaps) {
		sel.set(cur.container(), cur.offset());
	}
	do {
		cur.moveNext();
//	cout << "> " << cur.container()->nodeName() << ", " << cur.offset() << endl;
	} while (unwantedPos(cur));
	selmouse = curmouse;
	curmouse = false;
	initRange();
}
MMLNode *
MathCursor::movePrevious() {
	do {
		cur.movePrevious();
//	cout << "< " << cur.container()->nodeName() << ", " << cur.offset() << endl;
	} while (unwantedPos(cur));
	collapse();
	curmouse = false;
	return cur.container();
}
void
MathCursor::selectPrevious() {
	if (collaps) {
		sel.set(cur.container(), cur.offset());
	}
	do {
		cur.movePrevious();
//	cout << "< " << cur.container()->nodeName() << ", " << cur.offset() << endl;
	} while (unwantedPos(cur));
	selmouse = curmouse;
	curmouse = false;
	initRange();
}
MMLNode *
MathCursor::moveDown() {
	do {
		cur.moveDown();
//	cout << "- " << cur.container()->nodeName() << ", " << cur.offset() << endl;
	} while (unwantedPos(cur));
	collapse();
	curmouse = false;
	return cur.container();
}
MMLNode *
MathCursor::moveUp() {
	do {
		cur.moveUp();
//	cout << "+ " << cur.container()->nodeName() << ", " << cur.offset() << endl;
	} while (unwantedPos(cur));
	collapse();
	curmouse = false;
	return cur.container();
}
/* when moving from the left to the right, we try to stay at the same level or
   depth. At the extremities, it is allowed to go to the root. */
MMLNode *
MathCursor::moveRight() {
/*	MMLNode *last = 0;
	MMLNode *node = current;
	char corr;
	bool stop = false;
	do {
		last = node;
		node = moveNext();
		corr = (node->isText()) ?1 :0;
		if (level - corr == targetlevel) {
			stop = true;
		} else if (level - corr < targetlevel) {
			stop = node->isText();
			MMLNode *child = ancestry[level+1];
			stop |= child && child->previousSibling()
				&& child->previousSibling()->isText();
			stop |= !child && node->lastChild()
				&& node->lastChild()->isText();
		}
		stop |= node == last && !node->isText();
	} while (!stop);
	return current;*/
	collapse();
	return cur.container();
}
MMLNode *
MathCursor::moveLeft() {
/*	MMLNode *last = 0;
	MMLNode *node = current;
	char corr;  // a text node doesn't count for the level: we must correct
	bool stop = false;
	do {
		last = node;
		node = movePrevious();
		corr = (node && node->isText()) ?1 :0;
		corr = (node->isText()) ?1 :0;
		if (level - corr == targetlevel) {
			stop = true;
		} else if (level - corr < targetlevel) {
			stop = node->isText();
			MMLNode *child = ancestry[level+1];
			stop |= child && child->previousSibling()
				&& child->previousSibling()->isText();
			stop |= !child && node->lastChild()
				&& node->lastChild()->isText();
		}
		stop |= node == last && !node->isText();
	} while (!stop);
	return current;*/
	collapse();
	return cur.container();
}
int
MathCursor::nearness(const MMLNode *n) const {
//	if (!collapsed) return -1;
	int i = cur.isAncestor(n);
//	if (i > 0 && cur.container()->isText()) {
//		--i;
//	}
	return i;
}
bool
MathCursor::moveTo(float x, float y, BoundPoint &bp) const {
	MMLNode *n = owner->documentElement();
	MMLNode *c = n;
	// find the deepest node in which was clicked
	while (n) {
		if (distToNode(x, y, n) == 0) {
			c = n;
			x -= c->getX();
			y -= c->getY();
			n = n->firstChild();
		} else {
			n = n->nextSibling();
		}
	}
/*	if (!c) {
		if (x < 0) {
			bp.setBefore(owner->firstChild());
		} else {
			bp.setAfter(owner->lastChild());
		}

	}*/
	// if the node has childeren, find the nearest child node without
	// children
/*	float mindist = 10000;
	n = getNearestNode(x + c->getX(), y + c->getY(), c, mindist);
	if (n) {
		MMLNode *m = n;
		while (m != c) {
			x -= m->getX();
			y -= m->getY();
			m = m->parentNode();
		}
		c = n;
	}*/
	// check if the cursor should be placed before, after or in this node
	BoundPoint obp = bp;
	if (c->isText()) {
		const MMLText *t = static_cast<const MMLText *>(c);
		long offset = t->getOffset(x);
		bp.set(c, offset);
	} else if (x >= c->getWidth()/2) {
		bp.setAfter(c);
	} else {
		bp.setBefore(c);
	}
	return bp != obp;
}
bool
MathCursor::moveTo(float x, float y) {
	this->x = x;
	this->y = y;
	bool change = moveTo(x, y, cur);
	change |= !collaps || !curmouse;
	collapse();
	curmouse = true;
	return change;
}
bool
MathCursor::selectTo(float x, float y) {
	// if this function was called from a collapsed state,
	// set the value of sel to that of cur and update cur to the
	// position of the mouse
	if (collaps) {
		sel = cur;
	}
	this->x = x;
	this->y = y;
	bool change = moveTo(x, y, cur);
	selmouse = curmouse;
	curmouse = true;
	if (change) {
		initRange();
	}
	return change;
}
void
MathCursor::collapse() {
	if (!collaps) {
		collaps = true;
		updateSelection();
	}
}
void
MathCursor::initRange() {
//	cout << cur.container()->nodeName() << endl;
	hca = cur.highestCommonAncestor(sel);

	if (cur.isEarlierThan(sel)) {
		start = &cur;
		end = &sel;
	} else {
		start = &sel;
		end = &cur;
	}

	/*if (curmouse) {
		MMLNode *c = cur.container();
		bool changed = true;
		while (c != owner && changed) {
			if (cur.offset() == 0) {
				cur.moveDown();
			} else if (cur.endOfContainer()) {
				cur.setAfter(c);
			} else {
				changed = false;
			}
			c = cur.container();
		}
	}
	if (selmouse) {
		MMLNode *c = sel.container();
		bool changed = true;
		while (c != owner && changed) {
			if (sel.offset() == 0) {
				sel.moveDown();
			} else if (sel.endOfContainer()) {
				sel.setAfter(c);
			} else {
				changed = false;
			}
			c = sel.container();
		}
	}*/
	if (cur == sel) {
		collapse();
	} else {
		collaps = false;
		updateSelection();
	}
}
void
MathCursor::updateSelection() {
	// update the selected state of the nodes
	BoundPoint p(owner);
	bool sel = false;
	while (!p.atEnd()) {
/*		if (p == *start) {
			printf(" <s> ");
		}
		if (p == *end) {
			printf(" <e> ");
		}*/
		if (sel) {
			sel = p != *end;
//			if (!sel) printf(" * ");
		} else if (!collaps) {
			sel = p == *start;
//			if (sel) printf(" * ");
		}
		MMLNode *n = p.rightNode();
		if (n) {
//			printf("%s, ", n->nodeName());
			n->setSelected(sel);
		} else {
			n = p.container();
			if (n->isElement()) {
				n->setSelected(n->isSelected() && sel);
			} else if (n->isText()) {
				n->setSelected(n->isSelected() || sel);
			}
		}
		p.moveNext();
	}
}

MMLNode *
MathCursor::getNearestNode(float x, float y, MMLNode *n, float &mindist) const {
	if (!n) return n;
	MMLNode *m = n->firstChild();
	x -= n->getX();
	y -= n->getY();
	n = 0;
	while (m) {
		if (m->firstChild()) {
			MMLNode *nn = getNearestNode(x, y, m, mindist);
			if (nn) n = nn;
		} else {
			float dist = distToNode(x, y, m);
			if (dist < mindist) {
				n = m;
				mindist = dist;
			}
		}
		m = m->nextSibling();
	}
	return n;
}
float
MathCursor::distToNode(float x, float y, MMLNode *n) const {
	float nx = n->getX();
	float dx;
	if (x < nx) {
		dx = nx - x;
	} else if (x > nx + n->getWidth()) {
		dx = x - nx - n->getWidth();
	} else {
		dx = 0;
	}
	float ny = n->getY();
	float dy;
	if (y < ny - n->getAscent()) {
		dy = ny - n->getAscent() - y;
	} else if (y > ny + n->getDescent()) {
		dy = y - ny - n->getDescent();
	} else {
		dy = 0;
	}
	return dx*dx + dy*dy;
}
void
MathCursor::setBeforeNode(MMLNode *n) {
	cur.setBefore(n);
	collaps = true;
}
void
MathCursor::setAfterNode(MMLNode *n) {
	cur.setAfter(n);
	collaps = true;
}
bool
MathCursor::unwantedPos(const BoundPoint &) const {
/*	MMLNode *n = cur.leftNode();
	if (n && n->isText()) {
		const MMLText *t = static_cast<const MMLText *>(n);
		if (cur.offset() == long(t->data().length())) {
			return true;
		}
	} else {
		MMLNode *n = cur.rightNode();
		if (n && n->isText()) {
			return true;
		}
	}*/
	return false;
}
MMLNode *
MathCursor::container() const {
	return cur.container();
}
long
MathCursor::offset() const {
	return cur.offset();
}
MMLNode *
MathCursor::leftNode() const {
	return cur.leftNode();
}
MMLNode *
MathCursor::rightNode() const {
	return cur.rightNode();
}
bool
MathCursor::isSelected(const MMLNode *n) const {
	return n->isSelected();
}
/*
	if (collaps || !n || n->isInferred() || n->ownerDocument() != owner) {
		return false;
	}

	cout << "=\nisSelected, begin: " << start->container()->nodeName()
		<< " end: " << end->container()->nodeName() << endl;

	// a node is selected if it is completely between the two boundpoints
	// find out if the highest common ancestor of the selection is in
	// the nodes heratige
	cout << "hca: " << hca->nodeName() << " " << "n: " << n->nodeName() << endl;
//	cout << "np: " << n->parentNode()->nodeName() << endl;
	const MMLNode *a = n;
	while (a && a != hca) {
		a = a->parentNode();
	}

	// if hca is not an ancestor of n, a is not selected
	// if n is hca, it is not selected, since the bounding points are not
	// around it
	if (a != hca || n == hca) return false;

//	cout << "startLPSA: " << startLPSA->nodeName() <<
//		" endLPSA: " << endLPSA->nodeName() << endl;
	// find the lowest uncommon ancestor with start
	a = start->lowestUncommonAncestor(n);
	if (!a) {
		// handle the fact that there is no lowest uncommon ancestor
		return false;
	}
	MMLNode *sa = start->higherAncestor(a->parentNode());
	if (!sa) {
		sa = start->container();
	}
	// a and sa are siblings, we check to see which one is first
	cout << a->nodeName() << flush;
	cout << " " << sa->nodeName() << endl;
	while (a) {
		if (a == sa) return false;
		a = a->nextSibling();
	}

	a = end->lowestUncommonAncestor(n);
	sa = end->higherAncestor(a->parentNode());
	if (!sa) {
		sa = end->container();
	}
	// a and sa are siblings, we check to see which one is first
	cout << a->nodeName() << flush;
	cout << " " << sa->nodeName() << endl;
	while (a) {
		if (a == sa) return false;
		a = a->previousSibling();
	}
	return true;
}
*/
const BoundPoint &
MathCursor::cursor() const {
	return cur;
}
const BoundPoint &
MathCursor::left() const {
	return *start;
}
const BoundPoint &
MathCursor::right() const {
	return *end;
}
