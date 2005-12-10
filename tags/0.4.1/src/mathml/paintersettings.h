//
// C++ Interface: doPaintersettings
//
// Description:
//
//
// Author: Jos van den Oever <jos@vandenoever.info>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PAINTERSETTINGS_H
#define PAINTERSETTINGS_H
#include "mathml.h"
class MMLPainter;
class PainterSettings {
public:
    PainterSettings(MML::Attributes *);
    bool isPainterSetting(MML::Attribute) const;
    void setPainter(MMLPainter *p);
    void set(MML::Attribute);
private:
    bool changeMMLPainter[MML::numAttributes];
    MMLPainter *p;
    const MML::Attributes *att;

    float fontmultiplier;
    int oldscriptlevel;
    void setFontSize();
    void setScriptLevel();
};

#endif
