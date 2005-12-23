#ifndef MMLDICT
#define MMLDICT

#include "domstring.h"
#include <map>

class MMLDict {
public:
    static ushort resolveEntity(const DOMString &);
private:
    static bool done;
    static void makedict();
    static void makeEntDict();
    /* comparator for determining if s1 < s2 */
    struct ltstr
    {
        bool operator() (const char *s1, const char *s2) const
        {
            return strcmp(s1, s2) < 0;
        }
    };
    static std::map<const char *, ushort, ltstr> ent;
};

#endif
