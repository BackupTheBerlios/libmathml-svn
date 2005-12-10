#ifndef MMLVIEWPORT_H
#define MMLVIEWPORT_H

/* An equation is often rendered in a text context. Situations might occur in
   which the equation does not fit on a line and has to continue on the next
   line. This requirement is met with this class. A viewport is an area with a
   certain width in which part of the equation has to fit.
   If the equation does not fit in a viewport, only part of it is drawn in the
   current viewport and the rest of it is moved to the next viewport. */

#include "boundpoint.h"

class MMLDocument;

class MMLViewPort {
public:
    MMLViewPort();
    MMLViewPort(MMLDocument *);
    void setOwner(MMLDocument *o);
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    void setWidth(float w) { width = w; }
    void setAscent(float a) { ascent = a; }
    void setDescent(float d) { descent = d; }
    void setBegin();
    void setBegin(const BoundPoint &b);
    void setEnd();
    void setEnd(const BoundPoint &e);
    void setMaxWidth(float);
    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getAscent() const { return ascent; }
    float getDescent() const { return descent; }
    const BoundPoint &getBegin() const;
    const BoundPoint &getEnd() const;
    bool isFull() const;
    void translate(float x, float y);
    bool fit(float width, float ascent, float descent) const;
    void add(float width, float ascent, float descent);
private:
    bool full;
    float maxwidth;
    float width, ascent, descent;
    float x, y;
    float lx, ly;
    MMLDocument *owner;
    BoundPoint begin;
    BoundPoint end;
};

#endif
