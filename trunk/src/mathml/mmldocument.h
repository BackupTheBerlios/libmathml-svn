#ifndef MMLDOCUMENT_H
#define MMLDOCUMENT_H

#include "mmlnode.h"
#include <vector>
#include <list>
class MMLElement;
class MMLText;
class MMLPainter;
class MMLmrow;
class MMLmo;
class MathCursor;
class ConstMathCursor;
class MMLViewPort;
class MMLDocument : public MMLNode {
public:
	MMLDocument();
	~MMLDocument();
	const char *nodeName() const { return "MMLDocument"; }
	bool validate();
	bool validate() const;
	void setPainter(MMLPainter *) const;
	void layout() const;
	void paint() const;
	bool setMaxViewWidth(float maxwidth) const;
	bool isDocument() const { return true; };
	MMLElement *createElement(const DOMString &);
	MMLmrow *createInferredmrow(MMLElement *);
	MMLmo *createInferredmo(const DOMString & ="");
	MMLText *createTextNode(const DOMString &);
	DOMString createDOMString(const char * =0) const;
	MMLElement *documentElement();
	const MMLElement *documentElement() const;

	MathCursor *cursor();
	ConstMathCursor *constcursor() const;

	uint countViewPorts() const;
	void setCurrentView(ushort) const;
	MMLViewPort *currentView() const { return v->curview; }
	ushort currentViewNo() const { return v->cv; }

	// overloaded functions from MMLNode: one must access the current view
	void setX(float) const;
	void setY(float) const;
	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
	float getAscent() const;
	float getDescent() const;
private:
	MML::Attributes *a;
	void layout(MML::Attributes *) const;
	void paint(MML::Attributes *) const {}
	mutable MMLElement *root;
	MMLElement *active;
	int border;
	MathCursor *mathcursor;
	ConstMathCursor *constmathcursor;

	// a list of all the nodes: these must be deleted when the document
	// is deleted
	std::list<MMLNode *> nodes;
	// copy of the node for quick access
	void checkRoot();

	struct Views {
		ushort cv;
		MMLViewPort *curview;
		std::vector<MMLViewPort> views;
	};
	Views *v;
};
#endif
