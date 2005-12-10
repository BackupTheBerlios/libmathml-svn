#ifndef MATHCURSOR_H
#define MATHCURSOR_H

#include "mmlnode.h"
#include <vector>

class MathCursor {
public:
    MathCursor(MMLDocument *o);
    MMLNode *movePrevious(); // previous
    MMLNode *moveNext(); // next
    MMLNode *moveUp(); // towards the leaves
    MMLNode *moveDown(); // towards the root
    MMLNode *moveRight();
    MMLNode *moveLeft();
    MMLNode *currentNode() { return current; }
    int nearness(const MMLNode *) const;
    bool beforeNode(const MMLNode *) const;
    bool afterNode(const MMLNode *) const;
    uint textOffset() const {return offset;}
private:
    MMLNode *current;
    MMLDocument *owner;
    uint level;
    uint targetlevel;
    // for text nodes, remember the offset
    uint offset;
    std::vector<MMLNode *> ancestry;
    bool hasTextChildren(const MMLNode *node) const;
};

#endif
