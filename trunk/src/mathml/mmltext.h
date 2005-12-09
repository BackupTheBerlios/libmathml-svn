#ifndef MMLTEXT_H
#define MMLTEXT_H

#include "mmlnode.h"
#include "mmldocument.h"

class MMLPainter;
class MMLText : public MMLNode {
friend	MMLText *MMLDocument::createTextNode(const DOMString &);
public:
	const char *nodeName() const { return "MMLText"; }
	bool validate() const { return true; }
	bool isText() const { return true; };
	DOMString data() const;
	void layout(MML::Attributes *) const;
	void paint(MML::Attributes *) const;
	void appendData(const DOMString &);
	void setData(const DOMString &);
	void normalize();
	void setWidth(float) const;
	void setHeight(float ascent, float descent) const;
	long getOffset(float x) const;
private:
	DOMString d;
	DOMString conv;

	mutable bool widthset, heightset;
	/* this vector contains the positions for each characters to start
	the size is equal to the size of 'd' minus 1, since the first and
	last coordinate are known.*/
	mutable std::vector<float> charends;

	float getCursorX(uint offset) const;
	MMLText(MMLDocument *);
};

#endif
