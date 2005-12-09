#include "mmlviewport.h"
#include "attributes.h"
#include "mmldocument.h"
#include "mmlelement.h"
using MML::Attributes;

MMLViewPort::MMLViewPort()
	: begin(0), end(0) {
	owner = 0;
	full = false;
	width = ascent = descent = x = y = 0;
}

MMLViewPort::MMLViewPort(MMLDocument *o)
	: begin(o), end(o) {
	full = false;
}
void
MMLViewPort::setOwner(MMLDocument *o) {
	owner = o;
	begin = BoundPoint(o);
	end = BoundPoint(o);
}
const BoundPoint &
MMLViewPort::getBegin() const {
	return begin;
}
const BoundPoint &
MMLViewPort::getEnd() const {
	return end;
}
/* the point is set to the first position in the root element */
void
MMLViewPort::setBegin() {
	begin.set(owner->documentElement(), 0);
}
void
MMLViewPort::setBegin(const BoundPoint &b) {
	begin = b;
}
void
MMLViewPort::setEnd() {
	end.setAfter(owner->documentElement()->lastChild());
}
void
MMLViewPort::setEnd(const BoundPoint &e) {
	end = e;
}
void
MMLViewPort::setMaxWidth(float w) {
	maxwidth = w;
}
bool
MMLViewPort::isFull() const {
	return full;
}
void
MMLViewPort::translate(float dx, float dy) {
	lx += dx;
	ly += dy;
}
bool
MMLViewPort::fit(float /*w*/, float /*a*/, float /*d*/) const {
	return true;
}
void
MMLViewPort::add(float w, float a, float d) {
	width = (width > lx+w) ?width : lx+w;
	ascent = (ascent > a-ly) ?ascent :a-ly;
	descent = (descent > ly+d) ?descent : ly+d;
}
