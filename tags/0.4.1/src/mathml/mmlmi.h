#ifndef MMLMI_H
#define MMLMI_H

/* <mi> is a relatively simple MathML element. It cannot contain any
 * subelements according to the MathML schema. */

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmi : public MMLElement {
friend    MMLElement *MMLDocument::createElement(const DOMString &);
public:
    bool validate();
    void doLayout(MML::Attributes *p) const;
    void doPaint(MML::Attributes *) const;
private:
    MMLmi(MMLDocument *);
};

#endif
