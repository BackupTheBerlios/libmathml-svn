#include "domstring.h"
#include "mmldict.h"
#include <iostream>
using std::cerr;
using std::endl;
#include <cstdio>

DOMString::DOMString() {
	cs = 0;
}
DOMString::DOMString(const DOMString &d) {
	data = d.data;
	cs = 0;
}
DOMString::DOMString(const std::wstring &w) {
	data = w;
	cs = 0;
}
DOMString::DOMString(const char *c) {
	cs = 0;
	*this = c;
}
DOMString::~DOMString() {
	deleteascii();
}
DOMString::operator std::wstring() const {
	return data;
}
void
DOMString::deleteascii() {
	if (cs) {
		delete [] cs;
		cs = 0;
	}
}
void
DOMString::operator=(const DOMString &d) {
	deleteascii();
	data = d.data;
}
void
DOMString::operator=(const char *c) {
	deleteascii();
	// determine the number of bytes needed
	int len = mbstowcs(NULL,c,0)+1;
	data.resize(len-1);
	wchar_t *d = (wchar_t *)data.c_str();
	mbstowcs(d, c, len);
}
const char *
DOMString::utf8() const {
	if (cs) return cs;
	// determine the number of bytes needed
	int len = wcstombs(NULL, data.c_str(), 0) + 1;
	cs = new char[len];
	wcstombs(cs, data.c_str(), len);
	return cs;
}
wchar_t
DOMString::operator[](int p) const {
	return data[p];
}
uint
DOMString::length() const {
	return data.size();
}
void
DOMString::resize(uint s) {
	deleteascii();
	data.resize(s);
}
bool
DOMString::operator!=(const char *c) const {
	return !(*this == c);
}
bool
DOMString::operator==(const char *c) const {
	utf8();
	bool equal = strcmp(cs, c) == 0;
	return equal;
}
bool operator==(const char *c, const DOMString &d) {
	return d == c;
}
bool
DOMString::operator==(const DOMString &d) const {
	return data == d.data;
}
bool
DOMString::operator!=(const DOMString &d) const {
	return data != d.data;
}
void
DOMString::operator+=(const DOMString &d) {
	deleteascii();
	data += d.data;
}
void
DOMString::operator+=(const char *c) {
	deleteascii();
	DOMString d(c);
	*this += d;
}
void
DOMString::operator+=(const wchar_t c) {
	deleteascii();
	data += c;
}
bool
DOMString::operator<(const DOMString &d) const {
	return data < d.data;
}
wchar_t &
DOMString::operator[](uint i) {
	return data[i];
}
wchar_t
DOMString::operator[](uint i) const {
	return data[i];
}
const DOMString
operator+(const DOMString &c, const DOMString &d) {
	DOMString n(c);
	n += d;
	return n;
}
const DOMString
operator+(const DOMString &d, const char *c) {
	DOMString n(d);
	n += c;
	return n;
}
const DOMString
operator+(const char *c, const DOMString &d) {
	DOMString n(c);
	n += d;
	return n;
}
void
DOMString::append(const char *c) {
	deleteascii();
	*this += c;
}
void
DOMString::prepend(const char *c) {
	deleteascii();
	DOMString n(c);
	n += *this;
	data = n.data;
}
void
DOMString::resolveEntities() {
	deleteascii();
	int p1=0;
	int p2=-1;
	do {
		p1 = find('&',p1);
		if (p1 != -1) {
			p2 = find(';', p1);
			if (p2 != -1) {
				DOMString ent = substr(p1+1, p2-p1-1);
				wchar_t uni = MMLDict::resolveEntity(ent);
				if (uni) {
					ent = "&"+ent+";";
					replace(ent, uni);
					p1 = -1; // start from the beginning
				}
			}
		} else {
			p2 = -1;
		}
		++p1;
	} while (p2 != -1);
}
DOMString
DOMString::substr(int pos, int nlen) const {
	DOMString nd;
    nd.data = data.substr(pos,nlen);
	return nd;
}
float
DOMString::toFloat(bool &ok) const {
	utf8();
	char *p;
	float f = strtof(cs, &p);
	ok = p != cs;
	return f;
}
int
DOMString::toInt(bool &ok) const {
	utf8();
	char *p;
	int i = strtol(cs, &p, 10);
	ok = p != cs;
	return int(i);
}
int
DOMString::find(char c, uint offset) const {
    uint p = data.find(c, offset);
    if (p == std::wstring::npos) {
        return -1;
    } else {
        return p;
    }
}
int
DOMString::find(const DOMString &d, uint offset) const {
    uint p = data.find(d.data, offset);
    if (p == std::wstring::npos) {
        return -1;
    } else {
        return p;
    }
}
void
DOMString::replace(DOMString d, wchar_t c) {
	deleteascii();
	int pos = find(d);
	uint dlen = d.data.size();
	while (pos != -1) {
		DOMString nd = substr(0, pos);
		nd += c;
		nd += substr(pos+dlen);
		this->data = nd.data;
		pos = find(d);
	}
}
/*In MathML, as in XML, "whitespace" means blanks, tabs, newlines, or carriage returns, i.e. characters with hexadecimal Unicode codes U+0020, U+0009, U+000a, or U+000d, respectively.
All whitespace at the beginning and end is removed. All other whitespace
sequences are replaced with one space.*/
void
DOMString::normalize() {
	deleteascii();
	bool start = true;
	bool white = false;
	std::wstring d;
	std::wstring::const_iterator i;
	for (i=data.begin(); i != data.end(); ++i) {
		if (isWhitespace(*i)) {
			white = true;
		} else {
			if (white && !start) {
				d.push_back(' ');
			}
			white = start = false;
			d.push_back(*i);
		}
	}
	data = d;
}
bool
DOMString::isWhitespace(wchar_t u) {
        return u == 0x0020 || u == 0x0009 || u == 0x000A || u == 0x000D;
}
DOMString
DOMString::number(int i) {
	char buffer[16];
	snprintf(buffer, 16, "%i", i);
	DOMString d(buffer);
	return d;
}
