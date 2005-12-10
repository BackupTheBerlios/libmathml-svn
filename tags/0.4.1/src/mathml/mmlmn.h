#ifndef MMLMN_H
#define MMLMN_H

#include "mmlelement.h"
#include "mmldocument.h"
class MMLAttribute;

class MMLmn : public MMLElement {
friend    MMLElement *MMLDocument::createElement(const DOMString &);
public:
    bool validate();
    void doLayout(MML::Attributes *p) const;
    void doPaint(MML::Attributes *) const;
private:
    MMLmn(MMLDocument *);
};

#endif
