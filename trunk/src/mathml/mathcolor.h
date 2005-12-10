#ifndef MATHCOLOR_H
#define MATHCOLOR_H

class DOMString;
typedef unsigned char uchar;
typedef unsigned short ushort;
class MathColor {
public:
    static const MathColor aqua, black, blue, fuchsia, gray, green, lime,
        maroon, navy, olive, purple, red, silver, teal, white, yellow,
        transparent;

    MathColor();
    MathColor(const DOMString &);
    bool operator==(const MathColor &) const;
    bool operator!=(const MathColor &) const;
    void setRgb(uchar r, uchar g, uchar b);
    bool isTransparent() const;
    bool isValid() const;
    uchar r() const;
    uchar g() const;
    uchar b() const;
private:
    static const MathColor *colortable[17];
    static const char *nametable[17];
    uchar rr, gg, bb;
    bool transp;
    bool valid;

    int getValue(ushort h1);
    int getValue(ushort h1, ushort h2);
};

#endif
