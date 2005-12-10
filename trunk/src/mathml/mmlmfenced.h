#ifndef MMLMFENCED_H
#define MMLMFENCED_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmfenced : public MMLElement {
friend MMLElement *MMLDocument::createElement(const DOMString &);
public:
    bool validate();
    void doLayout(MML::Attributes *p) const;
    void doPaint(MML::Attributes *) const;
private:
    MMLmfenced(MMLDocument *);

    void setSeparators(const DOMString &s) const;
    ushort getSeparator(short i, const DOMString &s) const;
};

#endif
