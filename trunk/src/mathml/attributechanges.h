#ifndef ATTRIBUTECHANGES
#define ATTRIBUTECHANGES

#include <stack>

class MMLAttribute;
struct AttributeChange {
	short id;
	const MMLAttribute *newA;
	const MMLAttribute *oldA;
};

class AttributeChanges {
public:
	AttributeChanges();
	void add(short id, const MMLAttribute *newA, const MMLAttribute *oldA);
	bool empty() const;
	short size() const;
	AttributeChange pop();
private:
	std::stack<AttributeChange> changes;
};

#endif
