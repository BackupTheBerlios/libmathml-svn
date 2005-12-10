/***************************************************************************
 *   Copyright (C) 2004 by Jos van den Oever                               *
 *   jos@vandenoever.info                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "mmlmath.h"
#include "nodegui.h"
#include "mmlmrow.h"
#include "mathml.h"

MMLmath::MMLmath(MMLDocument *o) : MMLElement(MML::MATH, o) {
    // initialize the default values for the attributes
    if (!defset[id]) {
        defset[id] = true;
        const MMLAttribute **da = defatt[id];
        using namespace MML;
        createAttribute(ALTIMG, "", id, da);
        createAttribute(ALTTEXT, "", id, da);
        createAttribute(BASELINE, "", id, da);
        createAttribute(DISPLAY, "inline", id, da);
        createAttribute(HEIGHT, "0", id, da);
        createAttribute(MACROS, "", id, da);
        createAttribute(NAME, "", id, da);
        createAttribute(OVERFLOW, "scroll", id, da);
        createAttribute(TYPE, "", id, da);
        createAttribute(WIDTH, "0", id, da);
    }
}
bool
MMLmath::validate() {
    if (validated) {
        return valid;
    }
    validated = true;
    validateChildren(0, true);
    if (!valid) return false;

    // if there are more than one children: construct an inferred mrow
    if (first && first != last) {
        MMLNode *mrow = owner->createInferredmrow(this);
        appendChild(mrow);
    }

    return valid;
}
void
MMLmath::doLayout(MML::Attributes *a) const {
    if (!first) return;

    MMLNode *n = first;
    n->layout(a);
    gui->width = n->getWidth();
    gui->ascent = n->getAscent();
    gui->descent = n->getDescent();
}
void
MMLmath::doPaint(MML::Attributes *a) const {
    if (!first) return;
    first->paint(a);
}
