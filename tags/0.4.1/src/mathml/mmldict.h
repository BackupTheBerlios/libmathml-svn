#ifndef MMLDICT
#define MMLDICT

#include "domstring.h"
#include <map>

class MMLDict {
public:
    static ushort resolveEntity(DOMString);
private:
    static bool done;
    static void makedict();
    static void makeEntDict();
    static std::map<DOMString, ushort> ent;
};

#endif
