#ifndef MATHCURSOR_H
#define MATHCURSOR_H

#include "mmlnode.h"
#include "boundpoint.h"

/* MathCursor implements a cursor that is positioned somewhere in a MathML DOM.

   The specification DOM2-Traversal-Range could also be used for such an object,
   but has a few problems:
   - position in the DOM and text version of a document are not mapped 1 to 1
   - range and traversal are defined seperately, while a cursor usually
     traverses a document and is also placed at a certain position in a document
     The Traversal specification does not specify how to walk through text
     nodes. A cursor in a MathML document would want to do that.
     Even in the Range specification a more fine-grained position specifiation
     is used!
*/

class MathCursor {
public:
    MathCursor(MMLDocument *o);
    MMLNode *movePrevious(); // previous
    MMLNode *moveNext(); // next
    MMLNode *moveUp(); // towards the leaves
    MMLNode *moveDown(); // towards the root
    MMLNode *moveRight();
    MMLNode *moveLeft();
    bool moveTo(float, float);
    void selectNext();
    void selectPrevious();
    bool selectTo(float, float);
    MMLNode *container() const;
    long offset() const;
    MMLNode *leftNode() const;
    MMLNode *rightNode() const;
    void setBeforeNode(MMLNode *);
    void setAfterNode(MMLNode *);
    int nearness(const MMLNode *) const;
    bool isSelected(const MMLNode *) const;
    bool collapsed() const { return collaps; }
    float getX() { return x; }
    float getY() { return y; }
    const BoundPoint &cursor() const;
    const BoundPoint &left() const;
    const BoundPoint &right() const;
private:
    // the node the cursor is in
//    MMLNode *current;
    // the document the cursor belongs to
    MMLDocument *owner;
    BoundPoint cur, sel, *start, *end;
    bool curmouse, selmouse;
//    MMLNode *startLPSA, *endLPSA; // lowest partially selected ancestor
    MMLNode *hca; // highest common ancestor
    bool collaps; // if collapsed is true, sel is equal to cur
    // it's not equal in this class, but setting a bool is quicker than
    // copying the object

    // the depth at which the cursor aims to be
    // this value is changed with moveUp() and moveDown() and help when
    // navigating with moveLeft() and moveRight()
    uint targetlevel;
    // the coordinates the cursor was last sent to
    // these are temporary/debug variables
    float x, y;

    // returns the square of the distance of point x, y to node n.
    // x and y are points in the coordinate system of the parent of n
    float distToNode(float x, float y, MMLNode *n) const;
    // recursively scan all nodes in node n and
    // return the node without child nodes that is nearest to the point x, y
    // x and y are points in the coordinate system of of n
    MMLNode *getNearestNode(float x, float y, MMLNode *n, float &mindist)
        const;
    bool unwantedPos(const BoundPoint &) const;
    bool moveTo(float, float, BoundPoint &) const;
    void collapse();
    void initRange();
    void updateSelection();
};

#endif
