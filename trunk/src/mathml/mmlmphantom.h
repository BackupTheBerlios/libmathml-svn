#ifndef MMLMPHANTOM_H
#define MMLMPHANTOM_H

#include "mmlmrow.h"

class MMLmphantom : public MMLmrow {
friend	MMLElement *MMLDocument::createElement(const DOMString &);
public:
	void doPaint(MML::Attributes *) const;
private:
	MMLmphantom(MMLDocument *);
};

#endif
