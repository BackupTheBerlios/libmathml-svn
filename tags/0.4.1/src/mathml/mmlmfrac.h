#ifndef MMLMFRAC_H
#define MMLMFRAC_H

#include "mmlelement.h"
#include "mmldocument.h"
#include "mmll_unit.h"
class MMLmfrac : public MMLElement {
friend    MMLElement *MMLDocument::createElement(const DOMString &);
public:
    bool validate();
    void doLayout(MML::Attributes *) const;
    void doPaint(MML::Attributes *) const;
    static v_unit defLineThickness;
private:
    MMLmfrac(MMLDocument *);
};

#endif
