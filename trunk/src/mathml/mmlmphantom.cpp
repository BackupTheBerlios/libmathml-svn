#include "mmlmphantom.h"

MMLmphantom::MMLmphantom(MMLDocument *o)
    : MMLmrow(MML::MPHANTOM, o) {
}
void
MMLmphantom::doPaint(MML::Attributes *) const {
}
