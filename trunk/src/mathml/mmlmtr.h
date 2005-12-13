#ifndef MMLMTR_H
#define MMLMTR_H

#include "mmlelement.h"
#include "mmldocument.h"
#include "mmlmtable.h"

class MMLmtr : public MMLElement {
friend MMLElement *MMLDocument::createElement(const DOMString &);
friend void MMLmtable::doLayout(MML::Attributes *a) const;
public:
    bool validate();
    void doLayout(MML::Attributes *) const;
    void doPaint(MML::Attributes *) const;
private:
    MMLmtr(MMLDocument *);
};

#endif
