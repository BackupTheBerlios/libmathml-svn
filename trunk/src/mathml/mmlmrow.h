#ifndef MMLMROW_H
#define MMLMROW_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmrow : public MMLElement {
friend MMLElement *MMLDocument::createElement(const DOMString &);
friend MMLmrow *MMLDocument::createInferredmrow(MMLElement *);
public:
	bool validate();
	void doLayout(MML::Attributes *p) const;
	void doPaint(MML::Attributes *) const;
protected:
	MMLmrow(MML::Element, MMLDocument *); // allow mrow to be subclassed
private:

	MMLmrow(MMLDocument *);
};

#endif
