#ifndef MMLL_UNIT_H
#define MMLL_UNIT_H

namespace MML {
    class Attributes;
}
class DOMString;
typedef unsigned int uint;
typedef unsigned short ushort;

class l_unit {
public:
    enum MathSpace { VERYVERYTHINMATHSPACE, VERYTHINMATHSPACE,
    THINMATHSPACE, MEDIUMMATHSPACE, THICKMATHSPACE,
    VERYTHICKMATHSPACE, VERYVERYTHICKMATHSPACE};
    enum Unit {none, em, ex, px, in, cm, mm, pt, pc, perc, name};
    static const char *mathspacenames[7];
    l_unit(bool horizontal=true);
    l_unit(const float, Unit u, bool horizontal=true);
    void set(const DOMString &s);
    void set(const float, Unit u);
    float get(const MML::Attributes *a, const l_unit &relto = 1) const;
    float get(const MML::Attributes *a, Unit) const;
    float getNamedSpace(const MML::Attributes *a, MathSpace ms) const;
    bool validate() const;
    bool horizontal() const { return hor; }
    Unit getUnit() const { return unit; }
    float getValue() const { return value; }
    bool operator==(const l_unit &l) const {
        return value == l.value && unit == l.unit;
    }
protected:
    bool valid;
    bool hor;
    Unit unit;
    float value;
    void skipwhitespace(const DOMString &s, uint &pos, uint len) const;
    bool whitespace(ushort) const;
    float getConvFact(const MML::Attributes *a, Unit u) const;
};

class h_unit : public l_unit {
public:
    h_unit() : l_unit(true)  {}
    h_unit(const DOMString &d) : l_unit(true) { set(d); }
    h_unit(const float v, Unit u)
        : l_unit(v, u, true) {}
};
class v_unit : public l_unit {
public:
    v_unit() : l_unit(false)  {}
    v_unit(const float v, Unit u)
        : l_unit(v, u, false) {}
};
bool operator!=(const v_unit &u1, const v_unit &u2);

#endif
