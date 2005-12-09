#include "mmlmn.h"
#include "nodegui.h"
using std::list;
#include "mathml.h"
#include "mmltext.h"
#include "attributes.h"
#include "mmlpainter.h"
using namespace MML;

MMLmn::MMLmn(MMLDocument *o)
	: MMLElement(MML::MN, o) {
}
bool
MMLmn::validate() {
	if (validated) {
		return valid;
	}
	valid = true;
	validated = true;
	// an mi element may only contain MMLtext elements
	MMLNode *n = first;
	while (valid && n) {
		valid &= n->isText();
		if (!valid) {
			errmsg = "An mn element may contain only text and no elements.";
		}
		n = getNext(n);
	}
	return valid;
}
void
MMLmn::doLayout(MML::Attributes *a) const {
	if (!first) return;

	first->layout(a);
	gui->width = first->getWidth();
	gui->ascent = first->getAscent();
	gui->descent = first->getDescent();
}
void
MMLmn::doPaint(MML::Attributes *a) const {
	if (!first) return;

	first->paint(a);
}
