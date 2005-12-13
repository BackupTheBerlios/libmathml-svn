#include "attributes.h"
#include "domstring.h"
#include "mmlelement.h"
#include "mmlpainter.h"
#include <iostream>
#include <cassert>
using std::cerr;
using std::endl;
using namespace MML;
int
MML::createAttribute(const char *name, const DOMString &value,
        Element e, const MMLAttribute **att) {
    // find the attribute in the elements attribute list
    int pos = -1;
    const Attribute *elementAttList = attList[e];
    uint max = attListLen[e];
    for (uint i=0; pos == -1 && i<max; ++i) {
        if (!strcmp(attributeTag[elementAttList[i]], name)) {
            pos = i;
        }
    }
    if (pos == -1) {
        return -1; // attribute is not valid for this element
        // ....
    }
    // create a new attribute at the specified position
    Attribute a = elementAttList[pos];
    AttributeType type = attTypes[a];
    att[pos] = attFunc[type](value, a);
    if (!att[pos]) pos = -2; // value is not valid for this attribute
    return pos;
}
int
MML::createAttribute(const Attribute a, const DOMString &value,
        Element e, const MMLAttribute **att) {
    int pos = -1;
    const Attribute *elementAttList = attList[e];
    uint max = attListLen[e];
    for (uint i=0; pos == -1 && i<max; ++i) {
        if (elementAttList[i] == a) {
            pos = i;
        }
    }
    if (pos == -1) {
        cerr << "internal error: invalid attribute for element."
            << endl;
        exit(1);
    }
    AttributeType type = attTypes[a];
    att[pos] = attFunc[type](value, a);
    return pos;
}
MMLAttribute *
MML::createAttribute(const Attribute a, const DOMString &value) {
    AttributeType type = attTypes[a];
    MMLAttribute *att = attFunc[type](value, a);
    att->cleanup = false;
    return att;
}
MMLAttribute *
MML::createBOOL(const DOMString &v, Attribute) {
    bool value;
    if (v == "true") {
        value = true;
    } else if (v == "false") {
        value = false;
    } else {
        return 0;
    }
    MMLbool *b = new MMLbool(value);
    return b;
}
MMLAttribute *
MML::createDOMSTRING(const DOMString &v, Attribute) {
    MMLDOMString *b = new MMLDOMString(v);
    return b;
}
MMLAttribute *
MML::createH_UNIT(const DOMString &v, Attribute) {
    h_unit h;
    h.set(v);
    if (!h.validate()) {
        return 0;
    }
    MMLh_unit *m = new MMLh_unit(h);
    return m;
}
MMLAttribute *
MML::createV_UNIT(const DOMString &v, Attribute) {
    v_unit h;
    h.set(v);
    if (!h.validate()) {
        return 0;
    }
    MMLv_unit *m = new MMLv_unit(h);
    return m;
}
MMLAttribute *
MML::createFLOAT(const DOMString &v, Attribute) {
    bool ok;
    float value = v.toFloat(ok);
    if (!ok) {
        return 0;
    }
    MMLfloat *f = new MMLfloat(value);
    return f;
}
MMLAttribute *
MML::createINT(const DOMString &v, Attribute) {
    bool ok;
    int value = v.toInt(ok);
    if (!ok) {
        return 0;
    }
    MMLint *i = new MMLint(value);
    return i;
}
MMLAttribute *
MML::createMATHVARIANT(const DOMString &v, Attribute) {
    for (uint i=0; i<14; ++i) {
        if (v == mathvariantnames[i]) {
            return new MMLMathVariant(MathVariant(i));
        }
    }
    return 0;
}
MMLAttribute *
MML::createMATHCOLOR(const DOMString &v, Attribute) {
    MathColor mc(v);
    if (mc.isValid()) {
        return new MMLMathColor(mc);
    }
    return 0;
}
Attributes::Attributes() {
    // initialize the attributes that can be set from the environment
    for (uint i = 0; i<numAttributes; ++i) {
        att[i] = 0;
    }
    p = 0;
    ps = new PainterSettings(this);
    save();
    ps->setPainter(0);
}
Attributes::~Attributes() {
    setPainter(0);
    restore();
    assert(changes.empty());
    delete ps;
}
void
Attributes::setPainter(MMLPainter *p) {
//    if (p == this->p) return;
    // cleanup
    if (this->p != 0) {
        PainterSettings *tempps = ps;
        ps = 0;
        restore();
        ps = tempps;
    }
    this->p = p;
    ps->setPainter(p);
    if (p != 0) {
        // setting of a painter should only occur if there are no saved
        // changes
        assert(changes.size() == 1);
        save();
        initDefaults();
    }
}
void
Attributes::initDefaults() {
    assert(p);
    // set ps to 0 so that no MMLPainter 'set' functions are called,
    // when changing the attributes
    PainterSettings *tempps = ps;
    ps = 0;
    // set the default values taken from MathML specification
    // and environment
    setAttribute(CLASS, "");
    setAttribute(STYLE, "");
    setAttribute(ID, "");
    setAttribute(XLINK_HREF, "");
    setAttribute(XREF, "");

    // Mathematics style attributes common to token elements
    setAttribute(MATHCOLOR, p->mathColor());
    setAttribute(MATHBACKGROUND, "transparent");
    v_unit ms;
    ms.set(p->fontSize(), l_unit::pt);
    setAttribute(MATHSIZE, ms);

    // defaults for mo element
    setAttribute(FORM, "infix");
    setAttribute(MATHVARIANT, "normal");
    setAttribute(FENCE, "false");
    setAttribute(SEPARATOR, "false");
    setAttribute(LSPACE, "thickmathspace");
    setAttribute(RSPACE, "thickmathspace");
    setAttribute(STRETCHY, "false");
    setAttribute(SYMMETRIC, "false");
    // set 1000 instead of infinity for now
    setAttribute(MAXSIZE, "1000");
    setAttribute(MINSIZE, "1");
    setAttribute(LARGEOP, false);
    setAttribute(MOVABLELIMITS, false);
    setAttribute(ACCENT, false);

    // mstyle defaults
    setAttribute(SCRIPTLEVEL, 0);
    setAttribute(DISPLAYSTYLE, true);
    setAttribute(SCRIPTSIZEMULTIPLIER, 0.71f);
    setAttribute(SCRIPTMINSIZE, "8pt");
    setAttribute(VERYVERYTHINMATHSPACE, "0.0555556em");
    setAttribute(VERYTHINMATHSPACE, "0.111111em");
    setAttribute(THINMATHSPACE, "0.166667em");
    setAttribute(MEDIUMMATHSPACE, "0.222222em");
    setAttribute(THICKMATHSPACE, "0.277778em");
    setAttribute(VERYTHICKMATHSPACE, "0.333333em");
    setAttribute(VERYVERYTHICKMATHSPACE, "0.388889em");

    // mfrac defaults
    setAttribute(LINETHICKNESS, "1pt");

    ps = tempps;
}
/*void
Attributes::removeDefaults() {
    // delete the default settings from initDefaults
    assert(changes.size() == 1);
    for (uint i=0; i<numAttributes; ++i) {
        if (att[i]) {
            delete att[i];
            att[i] = 0;
        }
    }
} */
void
Attributes::setAttributes(const MMLElement *e) {
    // save the pointers to the current values in the old array
    // shortcut to the list of positions of attributes for this element
    const Attribute *attlist = attList[e->id];
    // shortcut to the number of attributes of this element
    uint len = attListLen[e->id];
    for (uint i=0; i<len; ++i) {
        MML::Attribute a = attlist[i];
        e->tmpatt[i] = att[a];
        if (e->att[i]) {
            att[a] = e->att[i];
            if (ps) ps->set(a);
        } else if (e->defatt[e->id][i]) {
            att[a] = e->defatt[e->id][i];
            if (ps) ps->set(a);
        }
        if (!att[a]
            && a != MML::BACKGROUND
            && a != MML::COLOR) {
            cerr << "Attribute " << attributeTag[a]
                << " has no value for element "
                << elementTag[e->id] << "." << endl;
            exit(1);
        }
    }
    save();
}
void
Attributes::unsetAttributes(const MMLElement *e) {
    restore();
    const Attribute *attlist = attList[e->id];
    uint len = attListLen[e->id];
    for (uint i=0; i<len; ++i) {
        MML::Attribute a = attlist[i];
        if (e->tmpatt[i] != att[a]) {
            att[a] = e->tmpatt[i];
            if (ps) ps->set(a);
        }
    }
}
void
Attributes::setAttribute(MML::Attribute a, const char *c) {
    setAttribute(a, DOMString(c));
}
/**
 * create a new AttributeChanges object in which we can store changes.
 * for each call to save, there must be one call to restore
 */
int callcount=0;
void
Attributes::save() {
//    printf("^^^^^^save() %i\n", ++callcount);
    cur = new AttributeChanges();
    changes.push(cur);
}
/**
 * restore all changes made to the attributes up to the previously saved point
 * for each call to save, there must be one call to restore
 */
void
Attributes::restore() {
//    printf("^^^^^^restore() %i\n", callcount--);
    // revert all the changes
    while (!cur->empty()) {
        AttributeChange ac = cur->pop();
        if (ac.newA->cleanup) {
            delete ac.newA;
        } else {
            printf("ohoh, you forgot some pointers\n");
        }
        att[ac.id] = ac.oldA;
        if (ps) ps->set(Attribute(ac.id));
    }
    delete cur;
    changes.pop();
    if (!changes.empty()) {
        cur = changes.top();
    }
}
