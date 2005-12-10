#ifndef MMLNODE_H
#define MMLNODE_H

#include "domstring.h"

class MMLDocument;
class MMLPainter;
namespace MML {
    class Attributes;
}
struct NodeGUI;
/**
 * The class MMLNode is the equivalent of the interface Node in the DOM
 * specification. It's functionality is extended to encompass GUI functionality.
 */
class MMLNode {
friend class MMLDocument;
public:
    /**
     * Destructor.
     */
    virtual ~MMLNode();

    // DOM inspired functions
    /**
     * returns simple const char * with the node's name
     * The value that is returned is always a pointer to a constant
     * string, hardcoded in the library, generated from the XML Schema
     */
    virtual const char *nodeName() const = 0;
    /**
     * Returns a pointer to the parent node. If the direct parent is an
     * inferred node, its parentNode() is returned. If there is no parent
     * node, the function returns 0.
     * This function never returns an inferred node.
     */
    MMLNode *parentNode() { return parentNode_(); }
    const MMLNode *parentNode() const { return parentNode_(); }
    /**
     * Returns a pointer to the first child node. If the direct first child
     * is an inferred node and its firstChild() is not inferred, this node
     * is returned. If not, the second child is considered and so on.
     * This function never returns an inferred node.
     * If the current node contains no children or all the containing nodes
     * are inferred, the function returns 0.
     */
    MMLNode *firstChild() { return firstChild_(); }
    const MMLNode *firstChild() const { return firstChild_(); }
    /**
     * Returns a pointer to the last child node. If this is inferred, the
     * same reasoning as for firstChild() applies.
     * This function never returns an inferred node.
     */
    MMLNode *lastChild() { return lastChild_(); }
    const MMLNode *lastChild() const { return lastChild_(); }
    MMLNode *nextSibling() { return nextSibling_(); }
    const MMLNode *nextSibling() const { return nextSibling_(); }
    MMLNode *previousSibling() { return previousSibling_(); }
    const MMLNode *previousSibling() const { return previousSibling_(); }
    MMLDocument *ownerDocument() { return owner; }
    const MMLDocument *ownerDocument() const { return owner; }
    MMLNode *insertBefore(MMLNode *, MMLNode *);
    MMLNode *removeChild(MMLNode *);
    MMLNode *appendChild(MMLNode *);

    // layout and drawing functions
    virtual bool validate();
    virtual void layout(MML::Attributes *a) const = 0;
    virtual void paint(MML::Attributes *a) const = 0;
    void setX(float) const;
    void setY(float) const;
    void setSelected(bool) const;
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    float getAscent() const;
    float getDescent() const;
    bool isSelected() const;

    // easy information functions
    virtual bool isDocument() const { return false; }
    virtual bool isElement() const { return false; }
    virtual bool isText() const { return false; }
    virtual bool isInferred() const { return inferred; }
    const DOMString errorMsg() const { return errmsg; }
    bool drawInViewPort(ushort viewport) const;

    // debug functions
    void printTree(int level=0) const;
    bool fit() const;
protected:
    NodeGUI *gui;

    bool validated;
    bool valid;
    bool inferred; // if true this node is inferred (doesn't really exist)

    MMLNode *parent;
    MMLNode *prev;
    MMLNode *next;
    MMLNode *first;
    MMLNode *last;
    MMLDocument *owner;
    DOMString errmsg;

    // these two static functions are needed to work around a restriction
    // of C++ that disallows access to protected members of an other
    // instance of a base class
    // without these functions, we cannot access inferred siblings of
    // other nodes
    static MMLNode *getNext(MMLNode *n) { return (n) ?n->next :0; }
    static MMLNode *getFirst(MMLNode *n) { return (n) ?n->first :0; }
    static MMLNode *getLast(MMLNode *n) { return (n) ?n->last :0; }
    MMLNode(MMLDocument * const);
private:
    MMLNode();
    MMLNode(const MMLNode &);
    void operator=(const MMLNode &);

    // helper functions. These functions are called by the constant and
    // non-constant versions. This saves implementation space.
    MMLNode *parentNode_() const;
    MMLNode *firstChild_() const;
    MMLNode *lastChild_() const;
    MMLNode *nextSibling_() const;
    MMLNode *previousSibling_() const;

    void checkInferred() const;
};

#endif
