#ifndef MMLRANGE_H
#define MMLRANGE_H

class MMLRange {
public:
    MMLNode *startContainer();
    const MMLNode *startContainer();
    long startOffset() const;
    MMLNode *endContainer();
    const MMLNode *endContainer() const;
    long endOffset() const;
    bool collapsed() const;
};

#endif