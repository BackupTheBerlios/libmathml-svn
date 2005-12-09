#include "mmlmsub.h"
#include "attributes.h"
#include "nodegui.h"

MMLmsub::MMLmsub(MMLDocument *o)
	: MMLElement(MML::MSUB, o) {

	if (!defset[id]) {
		defset[id] = true;
		const MMLAttribute **da = defatt[id];
		using namespace MML;
		MML::createAttribute(MML::SUBSCRIPTSHIFT, "0.7ex", id, da);
	}
}
bool
MMLmsub::validate() {
	if (validated) {
		return valid;
	}
	validated = true;
	validateChildren(2);
	return valid;
}
void
MMLmsub::doLayout(MML::Attributes *a) const {
	MMLNode *base = first;
	MMLNode *sub = last;
	// read metrics for current font
	base->layout(a);
	a->setAttribute(MML::DISPLAYSTYLE, false);
	int sl = a->scriptlevel()+1;
	a->setAttribute(MML::SCRIPTLEVEL, sl);
	sub->layout(a);

	float shift = a->subscriptshift().get(a);
	if (shift == 0) {
		shift = base->getDescent()-sub->getDescent();
	}
	sub->setX(base->getWidth());
	sub->setY(shift);

	gui->width = base->getWidth() + sub->getWidth();
	gui->ascent = base->getAscent();
	gui->descent = base->getDescent();
}
void
MMLmsub::doPaint(MML::Attributes *a) const {
	MMLNode *base = first;
	MMLNode *sub = last;
	base->paint(a);
	a->setAttribute(MML::DISPLAYSTYLE, false);
	int sl = a->scriptlevel()+1;
	a->setAttribute(MML::SCRIPTLEVEL, sl);
	sub->paint(a);
}
