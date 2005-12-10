#ifndef MMLMTEXT_H
#define MMLMTEXT_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmtext : public MMLElement {
friend    MMLElement *MMLDocument::createElement(const DOMString &);
public:
    bool validate();
    void doLayout(MML::Attributes *p) const;
    void doPaint(MML::Attributes *) const;
private:
    MMLmtext(MMLDocument *);
};

#endif
