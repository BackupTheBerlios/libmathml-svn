#include "mathcursor.h"
#include "mmldocument.h"
#include "mmlelement.h"
#include "mmltext.h"
#include <iostream>
using namespace std;

MathCursor::MathCursor(MMLDocument *o)
	: owner(o) {
	current = owner->documentElement();
	ancestry.resize(32, 0);
	ancestry[0] = current;
	int i = 0;
	MMLNode *n;
	do {
		n = ancestry[i]->firstChild();
		ancestry[++i] = n;
	} while (n);
	level = 0;
	targetlevel = 0;
	offset = 0;
}
/* move to the next sibling */
MMLNode *
MathCursor::moveNext() {
	if (current->isText()) {
		const MMLText *t = static_cast<const MMLText *>(current);
		if (offset < t->data().length()) {
			++offset;
			return current;
		}
	}
	MMLNode *node = 0;
	if (ancestry[level+1]) {
		node = ancestry[++level];
		// set the offset in the next level to the right
		ancestry[level+1] = node->firstChild();
	} else {
		if (level == 0) return current;
		node = ancestry[--level];
		ancestry[level+1] = ancestry[level+1]->nextSibling();
	}
	current = node;
	offset = 0;
	return current;
}
MMLNode *
MathCursor::movePrevious() {
	if (current->isText()) {
		if (offset > 0) {
			--offset;
			return current;
		}
	}
	MMLNode *node = 0;

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
		node = prev;
		// set the node to the now current level
		ancestry[++level] = node;
		// set the offset in the next level to the left
		ancestry[level+1] = 0;
	} else {
		// else descend one level, if possible
		if (level == 0) return current;
		node = ancestry[--level];
		//ancestry[level+1] = ancestry[level+1]->previousSibling();
	}
	current = node;
	if (current->isText()) {
		const MMLText *t = static_cast<const MMLText *>(current);
		offset = t->data().length();
	}
	return current;
}
MMLNode *
MathCursor::moveDown() {
	if (level == 0) return current;
	--level;
	targetlevel = level;
	cerr << "down:" << level << '\t' << targetlevel << endl;
	current = ancestry[level];
	return current;
}
MMLNode *
MathCursor::moveUp() {
	targetlevel++;
	MMLNode *node = ancestry[level+1];
	if (!node) {
		node = current->lastChild();
	}
	if (node) {
		current = ancestry[++level] = node;
		if (!ancestry[level+1]) {
			ancestry[level+1] = current->firstChild();
		}
	}
	cerr << "up:" << level << '\t' << targetlevel << endl;
	return current;
}
MMLNode *
MathCursor::moveRight() {
	MMLNode *last = 0;
	MMLNode *node = current;
	do {
		last = node;
		node = moveNext();
	} while ((node != last || node->isText())
			&& (node->firstChild() || level > targetlevel)
			&& level != targetlevel
			|| hasTextChildren(node));
	return current;
}
MMLNode *
MathCursor::moveLeft() {
	MMLNode *last = 0;
	MMLNode *node = current;
	do {
		last = node;
		node = movePrevious();
	} while ((node != last || node->isText())
			&& (node->firstChild() || level > targetlevel)
			&& level != targetlevel
			|| hasTextChildren(node));
	return current;
}
bool
MathCursor::hasTextChildren(const MMLNode *node) const {
	if (!node) return false;
	const MMLNode *child = node->firstChild();
	while (child) {
		if (child->isText()) return true;
		child = child->nextSibling();
	}
	return false;
}
int
MathCursor::nearness(const MMLNode *n) const {
	int i;
	for (i=0; i<=int(level) && ancestry[level-i] != n; ++i);
	if (i > int(level)) i = -1;
	return i;
}
bool
MathCursor::beforeNode(const MMLNode *n) const {
	return ancestry[level+1] == n;
}
bool
MathCursor::afterNode(const MMLNode *n) const {
	return ancestry[level+1] == 0 && n == current->lastChild();
}
