#include "mmlmo.h"
#include "mmlmodict.h"
#include "nodegui.h"
using std::map;
using std::list;
#include "mmltext.h"
#include "attributes.h"
#include "mmlpainter.h"
#include <iostream>
using namespace std;

bool MMLmo::madedict = false;
map<DOMString, const MMLAttribute **> MMLmo::dict;

MMLmo::MMLmo(MMLDocument *o)
    : MMLElement(MML::MO, o) {
/*    if (!madedict) {
        makedict();
    }*/
    // initialize the default values for the attributes
    if (!defset[id]) {
        defset[id] = true;
        const MMLAttribute **da = defatt[id];
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
    validated = true;
    // an mo element may only contain MMLtext elements
    if (first != last) {
        errmsg = "An mo element may only contain at most one text "
            "element.";
        valid = false;
        return false;
    }
    if (!first) return true;
    if (!first->isText()) {
        errmsg = "An mo element may only contain one text element.";
        valid = false;
        return false;
    }
    MMLText *i = static_cast<MMLText *>(first);
    lookupOperator(i->data());
    widthset = heightset = false;
    return true;
}
void
MMLmo::lookupOperator(const DOMString &op) {
    MMLmoDict::lookupOperator(op, att);
/*    map<DOMString, const MMLAttribute **>::const_iterator i;
    i = dict.find(op);
    if (i != dict.end()) {
        for (uint j=0; j<MML::moNumAtts; ++j) {
            if (!att[j] && i->second[j]) {
                att[j] = i->second[j];
            }
        }
    }*/
}
void
MMLmo::doLayout(MML::Attributes *a) const {
    if (!first) return;

    // the value of 'form' is a bit complicated. we use 'infix' for now
    //createAttribute(MML::FORM, "infix", id, att);
    // set the default attributes depending on the contents of the
    // element
    float lspace = a->lspace().get(a);
    float rspace = a->rspace().get(a);
    MMLText *m = static_cast<MMLText *>(first);
//    printf("%s: %f, %f\n", m->data().ascii(), lspace, rspace);
    first->layout(a);
    if (a->stretchy()) {
        MMLText *n = static_cast<MMLText *>(first);
//        printf("stretchy operator: %s\n", n->data().ascii());
        if (widthset) {
            gui->width = setwidth;
            n->setWidth(gui->width - lspace - rspace);
        }
        if (heightset) {
            gui->ascent = setascent;
            gui->descent = setdescent;
            n->setHeight(gui->ascent, gui->descent);
        }
    }
    if (!a->stretchy() || !widthset) {
        gui->width = lspace + first->getWidth() + rspace;
    }
    if (!a->stretchy() || !heightset) {
        gui->ascent = first->getAscent();
        gui->descent = first->getDescent();
    }

    first->setX(lspace);
}
void
MMLmo::doPaint(MML::Attributes *a) const {
    if (!first) return;

/*    if (r->att->mathbackground() != MathColor::transparent) {
        r->recordChanges(false);
        MathColor mc = r->mathcolor();
        r->setMathColor(MathColor::transparent);
        r->drawRect(x, y-ascent, width, ascent+descent+1);
        r->setMathColor(mc);
        r->recordChanges(true);
    }*/
    // todo: process other attributes than stretchy

    first->paint(a);
}

// call this function *before* you call 'layout'
// it is used to set the already known dimensions of the mo element
// if the attribute is stretchy, it can adapt to the information
void
MMLmo::setHeight(float sa, float sd) {
    heightset = true;
    setascent = sa;
    setdescent = sd;
}
void
MMLmo::setWidth(float sw) {
    widthset = true;
    setwidth = sw;
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
        const MMLAttribute **a
            = new const MMLAttribute*[MML::moNumAtts];
        for (uint j=0; j<MML::moNumAtts; ++j) {
            a[j] = 0;
        }
        while (*end != '\0') {
            std::string name;
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
            setAttribute(op.utf8(), name, value, a);
        }
//        dict.insert(pair<DOMString, MMLAttribute **>(op, a));
//        DOMString uni = op;
        op.resolveEntities();
//        if (uni != op) {
            dict.insert(pair<DOMString, const MMLAttribute **>
                (op, a));
//        }
    }
}
/* this function sets an attribute in a dictionary entry */
void
MMLmo::setAttribute(const char *op, const std::string &name, const DOMString &v,
        const MMLAttribute **a) {
    int pos = createAttribute(name.c_str(), v, MML::MO, a);
    if (pos == -1) {
        cerr << "internal error in MMLmo::makedict: invalid attribute '"
            << name << "', value invalid: '" << v.utf8()
            << "' for operator '" << op << "'." << endl;
        exit(1);
    }
}
