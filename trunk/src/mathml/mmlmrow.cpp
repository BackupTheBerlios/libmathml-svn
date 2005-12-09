#include "mmlmrow.h"
#include "mmlmo.h"
#include "attributes.h"
#include "nodegui.h"

MMLmrow::MMLmrow(MMLDocument *o)
	: MMLElement(MML::MROW, o) {
}
// this constructor allows other elements such as mphantom to subclass mrow
// this constructor is called from the inheriting elements constructor
// this constructor is needed because the elements identification
// (MML::Element must be passed on to the MMLElement constructor)
MMLmrow::MMLmrow(MML::Element e, MMLDocument *o)
	: MMLElement(e, o) {
}
bool
MMLmrow::validate() {
	if (validated) {
		return valid;
	}
	validated = true;
	validateChildren(-1);
	return valid;
}
void
MMLmrow::doLayout(MML::Attributes *a) const {
	if (!first) return;
	float cw, ca, cd;
	cw = ca = cd = 0;

	MMLNode *n;
	for (n = first; n; n = getNext(n)) {
		if (n->nodeName() != MML::elementTag[MML::MO]) {
			n->layout(a);
			if (n->getAscent() > ca) {
				ca = n->getAscent();
			}
			if (n->getDescent() > cd) {
				cd = n->getDescent();
			}
		}
	}
	for (n = first; n; n = getNext(n)) {
		if (n->nodeName() == MML::elementTag[MML::MO]) {
			MMLmo *mo = static_cast<MMLmo *>(n);
			mo->setHeight(ca, cd);
			n->layout(a);
		}
		n->setX(cw);
		cw += n->getWidth();
	}
	gui->width = cw;
	gui->ascent = ca;
	gui->descent = cd;
}
void
MMLmrow::doPaint(MML::Attributes *a) const {
	if (!first) return;
	MMLNode *n;
	for (n = first; n; n = getNext(n)) {
		n->paint(a);
	}
}
