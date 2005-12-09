#include "mathcolor.h"
#include "domstring.h"

const MathColor MathColor::aqua("#00FFFF");
const MathColor MathColor::black("#000000");
const MathColor MathColor::blue("#0000FF");
const MathColor MathColor::fuchsia("#FF00FF");
const MathColor MathColor::gray("#808080");
const MathColor MathColor::green("#008000");
const MathColor MathColor::lime("#00FF00");
const MathColor MathColor::maroon("#800000");
const MathColor MathColor::navy("#000080");
const MathColor MathColor::olive("#808000");
const MathColor MathColor::purple("#800080");
const MathColor MathColor::red("#FF0000");
const MathColor MathColor::silver("#C0C0C0");
const MathColor MathColor::teal("#008080");
const MathColor MathColor::white("#FFFFFF");
const MathColor MathColor::yellow("#FFFF00");
const MathColor MathColor::transparent;

const char *MathColor::nametable[17] = {"aqua", "black", "blue", "fuchsia",
	"gray", "green", "lime", "maroon", "navy", "olive", "purple", "red",
	"silver", "teal", "white", "yellow", "transparent"};
const MathColor *MathColor::colortable[17] = {&aqua, &black, &blue, &fuchsia,
	&gray, &green, &lime, &maroon, &navy, &olive, &purple, &red, &silver,
	&teal, &white, &yellow, &transparent};

MathColor::MathColor() {
	transp = valid = true;
}
MathColor::MathColor(const DOMString &d) {
	// check for a predefined color
	for (uint i=0; i<17; ++i) {
		if (!strcasecmp(d.utf8(), nametable[i])) {
			*this = *colortable[i];
			return;
		}
	}
	// convert RGB color
	uint len = d.length();
	if ((len != 4 && len != 7) || d[0] != '#') {
		valid = false;
		return;
	}
	valid = true;
	transp = false;
	if (len == 4) {
		rr = 16*getValue(d[1]);
		gg = 16*getValue(d[2]);
		bb = 16*getValue(d[3]);
	} else {
		rr = getValue(d[1], d[2]);
		gg = getValue(d[3], d[4]);
		bb = getValue(d[5], d[6]);
	}
}
bool
MathColor::operator==(const MathColor &m) const {
	if (!valid && !m.valid) return true;
	if (!valid || !m.valid) return false;
	if (transp && m.transp) return true;
	if (transp || m.transp) return false;
	return rr == m.rr && gg == m.gg && bb == m.bb;
}
bool
MathColor::operator!=(const MathColor &m) const {
	return !(*this == m);
}
bool
MathColor::isTransparent() const {
	return !valid || transp;
}
bool
MathColor::isValid() const {
	return valid;
}
int
MathColor::getValue(ushort h) {
	if (h >= '0' && h <= '9') {
		return h - '0';
	}
	if (h >= 'a' && h <= 'f') {
		return 10 + h - 'a';
	}
	if (h >= 'A' && h <= 'F') {
		return 10 + h - 'A';
	}
	valid = false;
	return -1;
}
int
MathColor::getValue(ushort h1, ushort h2) {
	return 16*getValue(h1) + getValue(h2);
}
void
MathColor::setRgb(uchar r, uchar g, uchar b) {
	rr = r; gg = g; bb = b;
	valid = true;
	transp = false;
}
uchar
MathColor::r() const {
	return rr;
}
uchar
MathColor::g() const {
	return gg;
}
uchar
MathColor::b() const {
	return bb;
}
