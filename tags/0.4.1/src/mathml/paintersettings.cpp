//
// Author: Jos van den Oever <jos@vandenoever.info>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "paintersettings.h"
#include "attributes.h"
#include "mmlpainter.h"
#include "mmlmfrac.h"
#include <iostream>
using std::cerr;
using std::endl;
#include <cmath>
#include <cassert>

PainterSettings::PainterSettings(MML::Attributes *a)
        : att(a) {
    for (uint i=0; i<MML::numAttributes; ++i) {
        changeMMLPainter[i] = false;
    }
    changeMMLPainter[MML::MATHVARIANT] = true;
    changeMMLPainter[MML::MATHCOLOR] = true;
    changeMMLPainter[MML::MATHBACKGROUND] = true;
    changeMMLPainter[MML::SCRIPTLEVEL] = true;
    changeMMLPainter[MML::MATHSIZE] = true;
    changeMMLPainter[MML::SCRIPTMINSIZE] = true;
    changeMMLPainter[MML::SCRIPTSIZEMULTIPLIER] = true;
    changeMMLPainter[MML::LINETHICKNESS] = true;

    fontmultiplier = 1;
    oldscriptlevel = 0;
}
void
PainterSettings::setPainter(MMLPainter *p) {
    this->p = p;
}
bool
PainterSettings::isPainterSetting(MML::Attribute a) const {
    return changeMMLPainter[a];
}
void
PainterSettings::set(MML::Attribute a) {
    assert(p);
    if (!isPainterSetting(a)) return;
    switch (a) {
    case MML::MATHVARIANT:
        p->setMathVariant(att->mathvariant());
        break;
    case MML::MATHCOLOR:
        p->setMathColor(att->mathcolor());
        break;
    case MML::MATHBACKGROUND:
        p->setMathBackground(att->mathbackground());
        break;
    case MML::SCRIPTLEVEL:
        setScriptLevel();
    case MML::MATHSIZE:
    case MML::SCRIPTMINSIZE:
    case MML::SCRIPTSIZEMULTIPLIER:
        setFontSize();
        break;
    case MML::LINETHICKNESS:
        p->setLineThickness(att->linethickness().get(att,
            MMLmfrac::defLineThickness));
        break;
    default:
        cerr << "setting of attribute '" << MML::attributeTag[a]
            << "' is not handled in PainterSettings::set." << endl;
        exit(1);
    }
}
void
PainterSettings::setScriptLevel() {
    int scriptlevel = att->scriptlevel();
    fontmultiplier *= pow(att->scriptsizemultiplier(),
        scriptlevel-oldscriptlevel);
    oldscriptlevel = scriptlevel;
}
void
PainterSettings::setFontSize() {
    float ms = att->mathsize().get(att, l_unit::pt);
    float fontsize = fontmultiplier*ms;
    float sms = att->scriptminsize().get(att, l_unit::pt);
    if (fontsize < sms) {
        fontsize = sms;
    }
    p->setFontSize(fontsize);
}
