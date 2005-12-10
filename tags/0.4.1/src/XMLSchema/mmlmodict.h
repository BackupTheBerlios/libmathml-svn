#ifndef MMLMODICT_H
#define MMLMODICT_H

#include "mathml.h"
#include <map>
class MMLmoDict {
public:
	static void lookupOperator(const DOMString &, const MMLAttribute **att);
private:
	static bool ready;
	static void init();
	static const MMLbool a0_0;

	static const MMLh_unit a1_0;
	static const MMLh_unit a1_1;
	static const MMLh_unit a1_2;
	static const MMLh_unit a1_3;
	static const MMLh_unit a1_4;
	static const MMLh_unit a1_5;
	static const MMLh_unit a1_6;
	static const MMLh_unit a1_7;

	static const short presize;
	static const short insize;
	static const short postsize;
	static const short prepos[6];
	static const short inpos[5];
	static const short postpos[6];
	static const char * presyms[50];
	static const char * insyms[254];
	static const char * postsyms[47];
	static const MMLAttribute *const pre[50][6];
	static const MMLAttribute *const in[254][5];
	static const MMLAttribute *const post[47][6];
	static std::map<DOMString, short> prerefs;
	static std::map<DOMString, short> inrefs;
	static std::map<DOMString, short> postrefs;
	static void setPre(const MMLAttribute **a, short row);
	static void setIn(const MMLAttribute **a, short row);
	static void setPost(const MMLAttribute **a, short row);
};
#endif
