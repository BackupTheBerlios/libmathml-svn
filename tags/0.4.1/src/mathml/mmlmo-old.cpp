#include "mmlmo.h"
#include "mmltext.h"
#include "renderer.h"
#include <iostream>
using std::cerr;
using std::endl;
using std::pair;

bool MMLmo::madedict = false;
map<DOMString, MMLAttribute **> MMLmo::dict;

MMLmo::MMLmo(MMLDocument *o)
    : MMLElement(MML::MO, o) {
    if (!madedict) {
        makedict();
    }
    swidth = sascent = sdescent = 0;
    // initialize the default values for the attributes
    if (!defset[id]) {
        defset[id] = true;
        MMLAttribute **da = defatt[id];
        using namespace MML;
        createAttribute(MATHVARIANT, "normal", id, da);
        createAttribute(FENCE, "false", id, da);
        createAttribute(SEPARATOR, "false", id, da);
        createAttribute(LSPACE, "thickmathspace", id, da);
        createAttribute(RSPACE, "thickmathspace", id, da);
        createAttribute(STRETCHY, "false", id, da);
        createAttribute(SYMMETRIC, "false", id, da);
        // set 1000 instead of infinity for now
        createAttribute(MAXSIZE, "1000", id, da);
        createAttribute(MINSIZE, "1", id, da);
        createAttribute(LARGEOP, "false", id, da);
        createAttribute(MOVABLELIMITS, "false", id, da);
        createAttribute(ACCENT, "false", id, da);
    }
}
bool
MMLmo::validate() {
    if (validated) {
        return valid;
    } 
    valid = true;
    // an mo element may only contain MMLtext elements
    list<MMLNode *>::const_iterator n = child.begin();
    for (n=child.begin(); valid && n != child.end(); ++n) {
        valid &= (*n)->isText();
        if (!valid) {
            errmsg = "An mo element may contain only text and no elements.";
        }
    }
    validated = true;
    return valid;
}
void
MMLmo::lookupOperator(const DOMString &op) {
    map<DOMString, MMLAttribute **>::const_iterator i;
    i = dict.find(op);
    if (i != dict.end()) {
        for (uint j=0; j<moNumAtts; ++j) {
            if (!att[j]) {
                att[j] = i->second[j];
            }
        }
    }
}
void
MMLmo::doLayout(MML::Attributes *a) const {
    if (child.size() == 0) {
        width = ascent = descent = 0;
        return;
    }
    // make sure that there's only one text node
    normalize();
    MMLText *n = static_cast<MMLText *>(*child.begin());
    // the value of 'form' is a bit complicated. we use 'infix' for now
    createAttribute(MML::FORM, "infix", id, att);
    // set the default attributes depending on the contents of the
    // element
    lookupOperator(n->data());

    r->setEnv(this);

    applyTokenAtts(r);
    // todo: process operator attributes
    n->layout(r);
    width = r->att->lspace().get(r)+n->getWidth()+r->att->rspace().get(r);
    ascent = n->getAscent();
    descent = n->getDescent();

    r->unsetEnv(this);
}
void
MMLmo::doPaint(MML::Attributes *a, Attributes *) {
    int ty = 0;
    if (child.size() == 0) {
        return;
    }
    r->setEnv(this);

    applyTokenAtts(r);
    MMLText *n = static_cast<MMLText *>(*child.begin());
    // todo: process other attributes than stretchy
    if (r->att->stretchy()) {
        bool stretched;
        if (sascent) {
            float fact = float(sascent+1+sdescent)/getHeight();
            cerr << "setstretchv: "<<fact<< endl;
            stretched = r->setFontStretch(fact, true);
        } else {
            cerr << "setstretchh: "<<float(swidth)/width<< endl;
            stretched = r->setFontStretch(float(swidth)/width,
                false);
        }
        n->layout(r);
        ty = n->getAscent();
        if (stretched) {
            ty -= sascent;
        } else {
            ty = ascent;
        }
    }
    r->translate(x+r->att->lspace().get(r), y+ty);
    n->paint(r, 0);

    r->unsetEnv(this);
}
// this function may only be called after calling layout
// so that the attribute values are set
bool
MMLmo::isStretchy(MMLPainter *r) {
    bool stretchy;
    r->att->setAttributes(this);
    stretchy = r->att->stretchy();
    r->att->unsetAttributes(this);
    return stretchy;
}
void
MMLmo::setHeight(int a, int d) {
    sascent = a;
    sdescent = d;
    swidth = 0;
}
void
MMLmo::setWidth(int w) {
    swidth = w;
    sascent = 0;
    sdescent = 0;
}

// static functions for initializing the operator dictionary

void
MMLmo::makedict() {
    madedict = true;
    for (int i=0; i<351; ++i) {
        const char *end;
        const char *start = rawopdict[i];
        const char *send = start+strlen(start);
        end = strchr(start, ' ');
        DOMString op;
        for (const char *j=start; j!=end; ++j) {
            op += *j;
        }
        MMLAttribute **a = new MMLAttribute*[moNumAtts];
        for (uint j=0; j<moNumAtts; ++j) {
            a[j] = 0;
        }
        while (*end != '\0') {
            DOMString name;
            start = end+1;
            end = strchr(start, '=');
            for (const char *j=start; j!=end; ++j) {
                name += *j;
            }
            start = end+1;
            end = strchr(start, ' ');
            if (!end) end = send;
            DOMString value;
            for (const char *j=start; j!=end; ++j) {
                value += *j;
            }
            setAttribute(op.ascii(), name.ascii(), value, a);
        }
        dict.insert(pair<DOMString, MMLAttribute **>(op, a));
        DOMString uni = op;
        uni.resolveEntities();
        if (uni != op) {
/*        ushort uni = 0;
        if (op.left(1) == "&" && op.right(1) == ";") {
            uni = MMLDict::resolveEntity(op.mid(1,op.length()-2));
        }
        if (uni) {*/
            dict.insert(pair<DOMString, MMLAttribute **>(uni, a));
        }
    }
}
/* this function sets an attribute in a dictionary entry */
void
MMLmo::setAttribute(const char *op, const char *name, const DOMString &v,
        MMLAttribute **a) {
    int pos = createAttribute(name, v, MML::MO, a);
    if (pos == -1) {
        cerr << "internal error in MMLmo::makedict: invalid attribute '"
            << name << "', value invalid: '" << v.ascii()
            << "' for operator '" << op << "'." << endl;
        exit(1);
    }
}
