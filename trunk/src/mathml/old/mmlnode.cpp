#include "mmlnode.h"
using std::list;
#include "mmltext.h"
#include <iostream>
using namespace std;

MMLNode::MMLNode(MMLDocument * const o)
		: owner(o) {
	parent = 0;
	prev = next = 0;
	valid = true;
	validated = false;
	x = y = width = ascent = descent = 0;
	inferred = false;
}
MMLNode::~MMLNode() {
}
bool
MMLNode::validate() {
	valid = true;
	list<MMLNode *>::const_iterator n;
	for (n=child.begin(); valid && n != child.end(); ++n) {
		valid = (*n)->validate();
	}
	validated = true;
	return valid;
}
/* return the first child of this node.
   if the first node is inferred but not completely inferred,
   the node's child is returned.
   if a the first node is allinferred, the next one is returned and so on. */
MMLNode *
MMLNode::firstChild() {
	list<MMLNode *>::iterator n;
	MMLNode *node = 0;
	for (n=child.begin(); !node && n!=child.end(); ++n) {
		node = *n;
		if (node->inferred) {
			node = node->firstChild();
		}
	}
	return node;
}
MMLNode *
MMLNode::firstChildfromAll() {
	if (child.size() > 0) return *child.begin();
	return 0;
}

MMLNode *
MMLNode::lastChild() {
	MMLNode *n = 0;
	if (child.size() > 0) {
		n = *child.rbegin();
		if (n->inferred) n = n->previousSibling();
	}
	return n;
}
// return the first 'next' that is not inferred
// if you want the inferred one, just use 'next'
MMLNode *
MMLNode::nextSibling() {
	if (!parent) return 0;
	list<MMLNode *>::iterator n;
	n = find(parent->child.begin(), parent->child.end(), this);
	if (n == parent->child.end()) cerr << "node not in its parent!" <<endl;
	MMLNode *node = 0;
	for (++n; !node && n != parent->child.end(); ++n) {
		node = *n;
		if (node->inferred) {
			node = node->firstChild();
		}
	}
	if (!node && parent->inferred) {
		node = parent->nextSibling();
	}
	return node;
}
MMLNode *
MMLNode::previousSibling() {
	MMLNode *n = prev;
	while (n && n->inferred) {
		MMLNode *c = n->lastChild();
		if (c) {
			n = c;
		} else {
			n = n->prev;
		}
	}
	if (!n && parent && parent->inferred) {
		n = parent->previousSibling();
	}
	return n;
}
MMLNode *
MMLNode::insertBefore(MMLNode *node, MMLNode *ref) {
	if (!node) return 0;
	if (node->owner != owner) {
		errmsg = "Node was created from a different document.";
		valid = false;
		validated = true;
		return node;
	}
	list<MMLNode *>::iterator r = find(child.begin(), child.end(), ref);
	if (r == child.end()) {
		errmsg = "Ref node is no child of this node.";
		valid = false;
		validated = true;
		return node;
	}
	if (node->parent) {
		node->parent->removeChild(node);
	}
	node->parent = this;
	node->prev = *r;
	node->next = (*r)->next;
	(*r)->next = node;
	if (node->next) {
		node->next->prev = node;
	}
	child.push_front(node);
	validated = false;
	return node;
}
MMLNode *
MMLNode::appendChild(MMLNode *node) {
	if (!node) return 0;
	if (node->owner != owner) {
		errmsg = "Node was created from a different document.";
		valid = false;
		validated = true;
		return node;
	}
	if (node->parent) {
		node->parent->removeChild(node);
	}
	node->parent = this;
	node->next = 0;
	if (child.size() > 0) {
		node->prev = *child.rbegin();
	} else {
		node->prev = 0;
	}
	child.push_back(node);
	validated = false;
	return node;
}
MMLNode *
MMLNode::removeChild(MMLNode *node) {
	if (!node) return 0;
	// use function 'previousSibling' instead of 'prev' to filter
	// out inferred nodes (same for nextSibling)
	MMLNode *n = node->next;
	MMLNode *p = node->prev;
	if (n) {
		n->prev = p;
	}
	if (p) {
		p->next = n;
	}
	node->parent = 0;
	node->next = 0;
	node->prev = 0;
	child.remove(node);
	validated = false;
	return node;
}
void
MMLNode::normalize() {
	list<MMLNode *>::iterator p;
	MMLText *t = NULL;
	list<MMLNode *> trash;
	for (p=child.begin(); p != child.end(); ++p) {
		if ((*p)->isText()) {
			MMLText *t2 = static_cast<MMLText *>(*p);
			if (t) {
				t->appendData(t2->data());
				trash.push_back(t2);
			} else {
				t = t2;
			}
		} else {
			t = NULL;
		}
	}
	for (p=child.begin(); p != child.end(); ++p) {
		if ((*p)->isText()) {
			t = static_cast<MMLText *>(*p);
			t->normalize();
		}
	}
	for (p=trash.begin(); p != trash.end(); ++p) {
		removeChild(*p);
	}
	validated = false;
}
MMLNode *
MMLNode::parentNode() const {
	MMLNode *p = parent;
	while (p && p->inferred) {
		p = p->parent;
	}
	return p;
}

void
MMLNode::setX(float x) {
	this->x = x;
}
void
MMLNode::setY(float y) {
	this->y = y;
}
float
MMLNode::getX() const {
	return x;
}
float
MMLNode::getY() const {
	return y;
}
float
MMLNode::getWidth() const {
	return width;
}
float
MMLNode::getHeight() const {
	return ascent + descent;
}
float
MMLNode::getAscent() const {
	return ascent;
}
float
MMLNode::getDescent() const {
	return descent;
}
void
MMLNode::printTree(int level) const {
	list<MMLNode *>::const_iterator n;
	for (int i=0; i<level; ++i) cout << "   ";
	if (inferred) {
		cout << "(" << nodeName() << ")" << endl;
	} else {
		cout << nodeName() << endl;
	}
	for (n=child.begin(); n!=child.end(); ++n) {
		(*n)->printTree(level+1);
	}
}
