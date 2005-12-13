#ifndef MMLMTABLE_H
#define MMLMTABLE_H

#include "mmlelement.h"
#include "mmldocument.h"
class MMLmtable : public MMLElement {
friend    MMLElement *MMLDocument::createElement(const DOMString &);
public:
    bool validate();
    void doLayout(MML::Attributes *) const;
    void doPaint(MML::Attributes *) const;
private:
    MMLmtable(MMLDocument *);
};

#endif
