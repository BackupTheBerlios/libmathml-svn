#include "mathenums.h"
#include "mathml.h"

const char *linebreaknames[6] = {"auto", "newline", "indentingnewline", "nobreak", "goodbreak", "badbreak"};
MMLAttribute *
MML::createLINEBREAK(const DOMString &v, Attribute) {
    for (uint i=0; i<6; ++i) {
        if (v == linebreaknames[i]) {
            return new MMLLinebreak(linebreak::Linebreak(i));
        }
    }
    return 0;
}
const char *formnames[3] = {"prefix", "infix", "postfix"};
MMLAttribute *
MML::createFORM(const DOMString &v, Attribute) {
    for (uint i=0; i<3; ++i) {
        if (v == formnames[i]) {
            return new MMLForm(form::Form(i));
        }
    }
    return 0;
}
const char *closurenames[4] = {"closed", "open", "open_closed", "closed_open"};
MMLAttribute *
MML::createCLOSURE(const DOMString &v, Attribute) {
    for (uint i=0; i<4; ++i) {
        if (v == closurenames[i]) {
            return new MMLClosure(closure::Closure(i));
        }
    }
    return 0;
}
const char *framenames[3] = {"none", "solid", "dashed"};
MMLAttribute *
MML::createFRAME(const DOMString &v, Attribute) {
    for (uint i=0; i<3; ++i) {
        if (v == framenames[i]) {
            return new MMLFrame(frame::Frame(i));
        }
    }
    return 0;
}
const char *notationnames[3] = {"actuarial", "longdiv", "radical"};
MMLAttribute *
MML::createNOTATION(const DOMString &v, Attribute) {
    for (uint i=0; i<3; ++i) {
        if (v == notationnames[i]) {
            return new MMLNotation(notation::Notation(i));
        }
    }
    return 0;
}
const char *displaynames[2] = {"block", "inline"};
MMLAttribute *
MML::createDISPLAY(const DOMString &v, Attribute) {
    for (uint i=0; i<2; ++i) {
        if (v == displaynames[i]) {
            return new MMLDisplay(display::Display(i));
        }
    }
    return 0;
}
const char *occurrencenames[3] = {"prefix", "infix", "function_model"};
MMLAttribute *
MML::createOCCURRENCE(const DOMString &v, Attribute) {
    for (uint i=0; i<3; ++i) {
        if (v == occurrencenames[i]) {
            return new MMLOccurrence(occurrence::Occurrence(i));
        }
    }
    return 0;
}
const char *mathvariantnames[14] = {"normal", "bold", "italic", "bold_italic", "double_struck", "bold_fraktur", "script", "bold_script", "fraktur", "sans_serif", "bold_sans_serif", "sans_serif_italic", "sans_serif_bold_italic", "monospace"};
MMLAttribute *
MML::createMATHVARIANT(const DOMString &v, Attribute) {
    for (uint i=0; i<14; ++i) {
        if (v == mathvariantnames[i]) {
            return new MMLMathvariant(mathvariant::Mathvariant(i));
        }
    }
    return 0;
}
const char *sidenames[4] = {"left", "right", "leftoverlap", "rightoverlap"};
MMLAttribute *
MML::createSIDE(const DOMString &v, Attribute) {
    for (uint i=0; i<4; ++i) {
        if (v == sidenames[i]) {
            return new MMLSide(side::Side(i));
        }
    }
    return 0;
}
const char *ordernames[2] = {"lexicographic", "numeric"};
MMLAttribute *
MML::createORDER(const DOMString &v, Attribute) {
    for (uint i=0; i<2; ++i) {
        if (v == ordernames[i]) {
            return new MMLOrder(order::Order(i));
        }
    }
    return 0;
}
const char *edgenames[2] = {"left", "right"};
MMLAttribute *
MML::createEDGE(const DOMString &v, Attribute) {
    for (uint i=0; i<2; ++i) {
        if (v == edgenames[i]) {
            return new MMLEdge(edge::Edge(i));
        }
    }
    return 0;
}
const char *overflownames[4] = {"scroll", "elide", "truncate", "scale"};
MMLAttribute *
MML::createOVERFLOW(const DOMString &v, Attribute) {
    for (uint i=0; i<4; ++i) {
        if (v == overflownames[i]) {
            return new MMLOverflow(overflow::Overflow(i));
        }
    }
    return 0;
}
const char *groupalignnames[4] = {"left", "center", "right", "decimalpoint"};
MMLAttribute *
MML::createGROUPALIGN(const DOMString &v, Attribute) {
    for (uint i=0; i<4; ++i) {
        if (v == groupalignnames[i]) {
            return new MMLGroupalign(groupalign::Groupalign(i));
        }
    }
    return 0;
}
