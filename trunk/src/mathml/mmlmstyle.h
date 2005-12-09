#ifndef MMLMSTYLE_H
#define MMLMSTYLE_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmstyle : public MMLElement {
friend MMLElement *MMLDocument::createElement(const DOMString &);
public:
	bool validate();
	void doLayout(MML::Attributes *p) const;
	void doPaint(MML::Attributes *) const;
protected:
	MMLmstyle(MML::Element, MMLDocument *); // allow mstyle to be subclassed
private:
	MMLmstyle(MMLDocument *);
};

#endif
