#ifndef BOUNDPOINT_H
#define BOUNDPOINT_H

#include "mmlnode.h"
#include <vector>

class BoundPoint {
public:
    BoundPoint(MMLDocument *o);
    MMLNode *container() const;
    long offset() const;
    bool endOfContainer() const;
    MMLNode *leftNode() const;
    MMLNode *rightNode() const;
    int isAncestor(const MMLNode *) const;
    bool atStart() const;
    bool atEnd() const;

    void set(MMLNode *, long offset);
    void setBefore(MMLNode *);
    void setAfter(MMLNode *);
    MMLNode *movePrevious();
    MMLNode *moveNext();
    MMLNode *moveUp();
    MMLNode *moveDown();
    MMLNode *highestCommonAncestor(const BoundPoint &) const;
//    const MMLNode *lowestUncommonAncestor(const MMLNode *) const;
    MMLNode *higherAncestor(const MMLNode *) const;
    bool isEarlierThan(const BoundPoint &b) const;
    bool operator==(const BoundPoint &) const;
    bool operator!=(const BoundPoint &) const;
private:
    // a list with all the ancestor containers of the cursor/boundary points
    std::vector<MMLNode *> ancestry;
    // the number of ancestor entries (not the size of the ancestry)
//    uint asize;
    uint level;
    mutable long offs;

    void reset();
    void setBeforeClean(MMLNode *node);
//    MMLNode *getCurChild() const;
    void setCurChild(MMLNode *);
    MMLNode *findPrev(uint &nextlevel) const;
    MMLNode *findNext(uint &prevlevel) const;
    void printancestry() const;
};

#endif
