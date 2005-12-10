#ifndef MMLMSUB_H
#define MMLMSUB_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmsub : public MMLElement {
friend    MMLElement *MMLDocument::createElement(const DOMString &);
public:
    bool validate();
    void doLayout(MML::Attributes *p) const;
    void doPaint(MML::Attributes *) const;
private:
    MMLmsub(MMLDocument *);
};

#endif
