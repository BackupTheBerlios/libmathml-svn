#ifndef MMLNODE_H
#define MMLNODE_H

#include "domstring.h"

#include <list>

class MMLDocument;
class MMLPainter;
namespace MML {
	class Attributes;
}
class MMLNode {
friend class MMLDocument;
public:
	virtual ~MMLNode();
	MMLNode *parentNode() const;
	virtual const char *nodeName() const = 0;
	virtual bool validate();
	virtual void layout(MML::Attributes *a) = 0;
	virtual void paint(MML::Attributes *a) = 0;
	void setX(float);
	void setY(float);
	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
	float getAscent() const;
	float getDescent() const;

	virtual bool isDocument() const { return false; }
	virtual bool isElement() const { return false; }
	virtual bool isText() const { return false; }
	virtual bool isInferred() const { return inferred; }
	MMLNode *firstChild();  // return first not inferred child
	MMLNode *firstChildfromAll();  // return first child
	MMLNode *lastChild();
	MMLNode *nextSibling();
	MMLNode *previousSibling();
	MMLNode *appendChild(MMLNode *);
	MMLNode *insertBefore(MMLNode *, MMLNode *);
	MMLNode *removeChild(MMLNode *);
	virtual void appendData(const DOMString &) {};
	virtual void normalize();
	const DOMString errorMsg() const { return errmsg; }
	void printTree(int level=0) const;
protected:
	// coordinates of the element or document
	float x, y;
	float width;
	float ascent;
	float descent;

	bool validated;
	bool valid;
	bool inferred; // if true this node is inferred (doesn't really exist)
	bool allinferred; // if true all of it's children are fata morganas too
	// inferred nodes may _not_ be moved around, because it means nothing.
	// these nodes are created and removed by the 'validate' function of
	// their parent
	MMLNode *parent;
	MMLNode *prev;
	MMLNode *next;
	MMLNode *first;
	MMLNOde *last;
	MMLDocument *owner;
	std::list<MMLNode *> child;
	DOMString errmsg;

	MMLNode(MMLDocument * const);
private:
	MMLNode();
	MMLNode(const MMLNode &);
	void operator=(const MMLNode &);

	void checkInferred() const;
};

#endif
