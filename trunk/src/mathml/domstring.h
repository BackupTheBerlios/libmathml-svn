#ifndef DOMSTRING_H
#define DOMSTRING_H

#include <string>
// in 'string' the macros DOMAIN, INFINITY and OVERFLOW are defined. It
// interferes with with enumeration values from mathml.h, so they are undefined.
#undef DOMAIN
#undef INFINITY
#undef OVERFLOW

class DOMString {
public:
    DOMString();
    DOMString(const DOMString &);
    DOMString(const std::wstring &);
    DOMString(const char *);
    ~DOMString();
    void operator=(const DOMString &);
    void operator=(const char *);
    operator std::wstring() const;
    const char *utf8() const;
    wchar_t operator[](int) const;
    bool operator!=(const char *) const;
    bool operator!=(const DOMString &) const;
    bool operator==(const char *) const;
    bool operator==(const DOMString &) const;
    bool operator<(const DOMString &) const;
    void operator+=(const DOMString &);
    void operator+=(const char *c);
    void operator+=(const wchar_t);
    wchar_t &operator[](uint);
    wchar_t operator[](uint) const;
    uint length() const;
    void resize(uint);
    void resolveEntities();
    DOMString substr(int pos, int len=-1) const;
    float toFloat(bool &) const;
    int toInt(bool &) const;
    void append(const char *);
    void prepend(const char *);
    int find(char, uint) const;
    int find(const DOMString &, uint=0) const;
    void replace(DOMString, wchar_t);
    void normalize();
    static bool isWhitespace(wchar_t u);
    static DOMString number(int i);
private:
    std::wstring data;
    mutable char *cs;
    void deleteascii();
    // this function must be private because else a DOMString with
    // impl = 0 may be created
};
bool operator==(const char *, const DOMString &);
const DOMString operator+(const DOMString &, const DOMString &);
const DOMString operator+(const DOMString &, const char *);
const DOMString operator+(const char *, const DOMString&);

#endif
