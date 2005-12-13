#ifndef MMLMTD_H
#define MMLMTD_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmtd : public MMLElement {
friend MMLElement *MMLDocument::createElement(const DOMString &);
public:
    bool validate();
    void doLayout(MML::Attributes *p) const;
    void doPaint(MML::Attributes *) const;
private:
    MMLmtd(MMLDocument *);
};

#endif
