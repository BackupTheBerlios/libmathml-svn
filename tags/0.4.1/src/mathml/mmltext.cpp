#include "mmltext.h"
#include "nodegui.h"
#include "mathcolor.h"
#include "mmlpainter.h"
#include "attributes.h"
#include "mathcursor.h"
#include <iostream>
using std::cerr;
using std::endl;

MMLText::MMLText(MMLDocument *owner)
    : MMLNode(owner) {
}
DOMString
MMLText::data() const {
    return d;
}
void
MMLText::appendData(const DOMString &s) {
    d += s;
    conv = d;
}
void
MMLText::setData(const DOMString &s) {
    d = s;
    d.normalize();
    conv = d;
}
void
MMLText::normalize() {
    d.normalize();
    conv = d;
}
void
MMLText::layout(MML::Attributes *a) const {
    // check for entities
/*    conv = d;
    conv.resolveEntities();*/
    gui->ascent = a->p->fontAscent();
    gui->descent = a->p->fontDescent();
    gui->width = a->p->stringWidth(conv);
    widthset = heightset = false;

    // update the charens vector
    uint size = d.length();
    charends.resize(size);
    for (uint i=0; i<size; i++) {
        DOMString before = d.substr(0, i+1);
        charends[i] = a->p->stringWidth(before);
    }
}
void
MMLText::paint(MML::Attributes *a) const {
    a->p->translate(gui->x, gui->y);
    int nearness = -1;
    MathCursor *mc = owner->cursor();
    nearness = mc->nearness(this);
    bool selected = mc->isSelected(this);
    if (selected) {
        // the node can be completely or partially selected
        float x1 = 0;
        float x2 = gui->width;
//        printf("selected!");
        if (mc->left().container() == this) {
//            printf(" o1: %i,", mc->left().offset());
            // the side to the right of offset is selected
            x1 = getCursorX(mc->left().offset());
        }
        if (mc->right().container() == this) {
            // the side to the left of offset is selected
            x2 = getCursorX(mc->right().offset());
//            printf(" o2: %i,", mc->right().offset());
        }
        a->p->fillRect(x1, -gui->ascent, x2-x1, gui->ascent + gui->descent,
            a->p->selectionColor());
//        printf("\n");
    } else if (nearness >= 0 && mc->collapsed()) {
        MathColor mb = a->p->highlightColor(nearness);
        a->p->fillRect(0, -gui->ascent, gui->width,
            gui->ascent + gui->descent, mb);
    }
    if (widthset) {
        if (heightset) {
            a->p->drawText(conv, gui->width, gui->ascent,
                gui->descent);
        } else {
            a->p->drawText(conv, gui->width);
        }
    } else {
        if (heightset) {
            a->p->drawText(conv, gui->ascent, gui->descent);
        } else {
            a->p->drawText(conv);
        }
    }
    if (nearness == 0) {
        float cx = getCursorX(mc->offset());
        a->p->drawLine(cx, -gui->ascent, cx, gui->descent, 2);
    }
    a->p->translate(-gui->x, -gui->y);
}
float
MMLText::getCursorX(uint offset) const {
    float cx;
    if (offset == 0) {
        cx = 0;
    } else if (offset == d.length()) {
        cx = gui->width;
    } else {
        cx = charends[offset-1];
    }
    return cx;
}
void
MMLText::setWidth(float w) const {
    gui->width = w;
    widthset = true;
}
void
MMLText::setHeight(float a, float d) const {
    gui->ascent = a;
    gui->descent = d;
    heightset = true;
}
long
MMLText::getOffset(float x) const {
    uint size = charends.size();
    float mid = 0;
    for (uint i=0; i<size; i++) {
        mid = mid + (charends[i]-mid)/2;
        if (x < mid) return i;
        mid = charends[i];
    }
    mid = mid + (gui->width-mid)/2;
    if (gui->x < mid) return size;
    return size+1;
}
