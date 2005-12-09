#ifndef MMLMSUBSUP_H
#define MMLMSUBSUP_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmsubsup : public MMLElement {
friend	MMLElement *MMLDocument::createElement(const DOMString &);
public:
	bool validate();
	void doLayout(MML::Attributes *p) const;
	void doPaint(MML::Attributes *) const;
private:
	MMLmsubsup(MMLDocument *);
};

#endif
