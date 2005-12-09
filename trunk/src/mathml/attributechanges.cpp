#include "attributechanges.h"

AttributeChanges::AttributeChanges() {
}
void
AttributeChanges::add(short id, const MMLAttribute *newA,
		const MMLAttribute *oldA) {
	AttributeChange ac;
	ac.id = id;
	ac.newA = newA;
	ac.oldA = oldA;
	changes.push(ac);
}
bool
AttributeChanges::empty() const {
	return changes.empty();
}
short
AttributeChanges::size() const {
	return changes.size();
}
AttributeChange
AttributeChanges::pop() {
	AttributeChange ac = changes.top();
	changes.pop();
	return ac;
}
