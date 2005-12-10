#include "mmll_unit.h"
#include "domstring.h"
#include "attributes.h"
#include "mmlpainter.h"

const char *l_unit::mathspacenames[7] = { "veryverythinmathspace",
    "verythinmathspace", "thinmathspace", "mediummathspace",
    "thickmathspace", "verythickmathspace", "veryverythickmathspace"};

l_unit::l_unit(bool horizontal)
        : hor(horizontal) {
    value = 0;
    unit = none;
    valid = false;
}
l_unit::l_unit(const float v, Unit u, bool horizontal)
    : hor(horizontal), unit(u), value(v) {
    valid = true;
}
void
l_unit::set(const DOMString &s) {
    uint len=s.length();
    if (len == 0) {
        valid = false;
        return;
    }

    // check if tha value is not a named value
    for (uint i=0; i<7; ++i) {
        if (s == mathspacenames[i]) {
            unit = name;
            value = i;
            valid = true;
            return;
        }
    }
    // a unit in mathml can start with a '-', but not with a '+'
    bool positive = true;
    uint pos=0;

    skipwhitespace(s, pos, len);
    if (s[pos] == '-') {
        positive = false;
        ++pos;
        if (pos == len) {
            valid = false;
            return;
        }
    }
    uint spos = pos;
    while (pos < len && (isdigit(s[pos]) || s[pos] == '.')) {
        ++pos;
    }
    // read numerical value
    bool ok;
    value = s.substr(spos, pos-spos).toFloat(ok);
    if (!ok) {
        valid = false;
        return;
    }
    skipwhitespace(s, pos, len);
    // read unit
    if (pos == len) {
        unit = none;
        valid = true;
        return;
    }
    if (s[pos] == '%') {
        unit = perc;
        value /= 100;
    }
    if (len - pos < 2) {
        valid = false;
        return;
    }
    DOMString u = s.substr(pos, 2);
    pos += 2;
    if (u == "em") unit = em;
    else if (u == "ex") unit = ex;
    else if (u == "px") unit = px;
    else if (u == "in") unit = in;
    else if (u == "cm") unit = cm;
    else if (u == "mm") unit = mm;
    else if (u == "pt") unit = pt;
    else if (u == "pc") unit = pc;
    skipwhitespace(s, pos, len);
    valid = pos == len;
    return;
}
void
l_unit::set(const float f, Unit u) {
    value = f;
    unit = u;
}
void
l_unit::skipwhitespace(const DOMString &s, uint &pos, uint len) const {
    while (pos < len && whitespace(s[pos])) {
        ++pos;
    }
}
bool
l_unit::whitespace(ushort u) const {
    return u == 0x0020 || u == 0x0009 || u == 0x000A || u == 0x000D;
}
bool
l_unit::validate() const {
    return valid;
}
/* Return the conversion factor for the conversion from unit u to pixels */
float
l_unit::getConvFact(const MML::Attributes *a, Unit u) const {
    switch (u) {
    case em:
        return a->p->em();
    case ex:
        return a->p->ex();
    case px:
        return 1;
    case in:
        return a->p->dpi(hor);
    case cm:
        return a->p->dpi(hor)/2.54;
    case mm:
        return a->p->dpi(hor)/25.4;
    case pt:
        return a->p->dpi(hor)/72;
    case pc:
        return a->p->dpi(hor)/6;
    default:
        return 1;
    }
}
float
l_unit::get(const MML::Attributes *a, Unit u) const {
    float nv = value*getConvFact(a, unit)/getConvFact(a, u);
    return nv;
}
float
l_unit::getNamedSpace(const MML::Attributes *a, MathSpace ms) const {
    switch (ms) {
    case VERYVERYTHINMATHSPACE:
        return a->veryverythinmathspace().get(a, px);
    case VERYTHINMATHSPACE:
        return a->verythinmathspace().get(a, px);
    case THINMATHSPACE:
        return a->thinmathspace().get(a, px);
    case MEDIUMMATHSPACE:
        return a->mediummathspace().get(a, px);
    case THICKMATHSPACE:
        return a->thickmathspace().get(a, px);
    case VERYTHICKMATHSPACE:
        return a->verythickmathspace().get(a, px);
    case VERYVERYTHICKMATHSPACE:
        return a->veryverythickmathspace().get(a, px);
    }
    return 0;
}
float
l_unit::get(const MML::Attributes *a, const l_unit &relto) const {
    float r = 1;
    if (relto.unit != none && relto.unit != perc) {
        r = relto.get(a);
    }
    switch (unit) {
    case perc:
        return r*value/100;
    case none: // since there is no unit, the value must be relative
        return r*value;
    case name:
        return getNamedSpace(a, MathSpace(value));
    default:
        float factor = getConvFact(a, unit);
        return value*factor;
    }
}
bool
operator!=(const v_unit &u1, const v_unit &u2) {
    return u1.getValue() != u2.getValue()
        || u1.getUnit() != u2.getUnit();
}
