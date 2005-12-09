#include "mmlmtext.h"
#include "nodegui.h"

MMLmtext::MMLmtext(MMLDocument *o)
	: MMLElement(MML::MTEXT, o) {
}
bool
MMLmtext::validate() {
	if (validated) {
		return valid;
	}
	validated = true;
	valid = true;
	// an mi element may only contain MMLtext elements
	MMLNode *n;
	for (n = first; valid && n; n = getNext(n)) {
		valid = n->isText();
	}
	if (!valid) {
		errmsg = "An mtext element may contain only text and no elements.";
	}
	return valid;
}
void
MMLmtext::doLayout(MML::Attributes *a) const {
	if (!first) return;

	MMLNode *n = first;
	n->layout(a);
	gui->width = n->getWidth();
	gui->ascent = n->getAscent();
	gui->descent = n->getDescent();
}
void
MMLmtext::doPaint(MML::Attributes *a) const {
	if (!first) return;
	first->paint(a);
}
