#ifndef MMLMSQRT_H
#define MMLMSQRT_H

#include "mmlelement.h"
#include "mmldocument.h"

class MMLmsqrt : public MMLElement {
friend	MMLElement *MMLDocument::createElement(const DOMString &);
public:
	bool validate();
	void doLayout(MML::Attributes *p) const;
	void doPaint(MML::Attributes *) const;
	static void rootPoints(float *, float *, float *, float *, float *);
private:
	MMLmsqrt(MMLDocument *);
};

#endif
