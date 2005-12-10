#ifndef MMLMSUP_H
#define MMLMSUP_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmsup : public MMLElement {
friend    MMLElement *MMLDocument::createElement(const DOMString &);
public:
    bool validate();
    void doLayout(MML::Attributes *p) const;
    void doPaint(MML::Attributes *) const;
private:
    MMLmsup(MMLDocument *);
};

#endif
