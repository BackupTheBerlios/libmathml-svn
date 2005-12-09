#ifndef MMLMO_H
#define MMLMO_H

#include "mmlelement.h"
#include "mmldocument.h"
#include "mmldict.h"
#include <map>
#include <string>

class MMLmo : public MMLElement {
friend MMLElement *MMLDocument::createElement(const DOMString &);
friend MMLmo *MMLDocument::createInferredmo(const DOMString &);
public:
	bool validate();
	void doLayout(MML::Attributes *p) const;
	void doPaint(MML::Attributes *) const;
	bool isStretchy(MML::Attributes *);
	void setHeight(float a, float d);
	void setWidth(float);
protected:
	void lookupOperator(const DOMString &op);
private:
	bool widthset, heightset;
	float setwidth, setascent, setdescent;
	static bool madedict;
	static const char *rawopdict[351];
	static std::map<DOMString, const MMLAttribute **> dict;
	void makedict();
	void setAttribute(const char *op, const std::string &name,
		const DOMString &v, const MMLAttribute **a);

	MMLmo(MMLDocument *);
};

#endif
