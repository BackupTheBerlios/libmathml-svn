#ifndef MMLMERROR_H
#define MMLMERROR_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmerror : public MMLElement {
friend	MMLElement *MMLDocument::createElement(const DOMString &);
public:
	bool validate();
	void doLayout(MML::Attributes *p) const;
	void doPaint(MML::Attributes *) const;
private:
	MMLmerror(MMLDocument *);
};

#endif
