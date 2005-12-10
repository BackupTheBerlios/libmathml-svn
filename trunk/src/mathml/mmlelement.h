#ifndef MMLELEMENT_H
#define MMLELEMENT_H

#include "mmlnode.h"
#include "elements.h"

class MMLAttribute;
class MMLPainter;
class MMLElement : public MMLNode {
friend class MML::Attributes;
public:
    virtual ~MMLElement();
    const MML::Element id;
    bool isElement() const { return true; };
    const char *nodeName() const {return tagName();}
    const char *tagName() const;
    bool attributesValid() const { return attributesvalid; }
    virtual void setAttribute(const char *, const DOMString &v);
    virtual void doLayout(MML::Attributes *a) const = 0;
    virtual void doPaint(MML::Attributes *a) const = 0;
    void normalize();
protected:
    MMLElement(MML::Element, MMLDocument *);
    void invalidAttribute(const char *name);
    void invalidValue(const char *name, const DOMString &value);
    void validateChildren(int num, bool orMore = false);

    // generic attribute arrays
    // numAtts is the number of attributes and is set by
    // each subclassed element before calling initAtts or deleteAtts
    // these function allocate and delete space for numAtts attribute
    // pointers
    short numAtts;
    // attributes as set in the specified element
    const MMLAttribute **att;
    // temporary storage of attributes from the environment
    const MMLAttribute **tmpatt;
    static const MMLAttribute **defatt[MML::numElements];
    static bool defset[MML::numElements];
    static uint count;  // ????
    void initAtts();
    void deleteAtts();
private:
    bool attributesvalid;
    static const char *mathvariantnames[14];
    void layout(MML::Attributes *a) const;
    void paint(MML::Attributes *a) const;
};

#endif
