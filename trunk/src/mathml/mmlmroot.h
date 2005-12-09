#ifndef MMLMROOT_H
#define MMLMROOT_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmroot : public MMLElement {
friend	MMLElement *MMLDocument::createElement(const DOMString &);
public:
	bool validate();
	void doLayout(MML::Attributes *p) const;
	void doPaint(MML::Attributes *) const;
private:
	MMLmroot(MMLDocument *);
};

#endif
