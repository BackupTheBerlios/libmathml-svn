#include "mmlmodict.h"
using namespace MML;
bool MMLmoDict::ready = false;
const short MMLmoDict::presize = 6;
const short MMLmoDict::insize = 5;
const short MMLmoDict::postsize = 6;
std::map<DOMString, short> MMLmoDict::prerefs;
std::map<DOMString, short> MMLmoDict::inrefs;
std::map<DOMString, short> MMLmoDict::postrefs;
/* If the operator does not occur in the dictionary with the specified form,
   the renderer should use one of the forms that is available there, in the 
   order of preference: infix, postfix, prefix; */
void
MMLmoDict::lookupOperator(const DOMString &op, const MMLAttribute **a) {
	if (!ready) {
		init();
	}
	std::map<DOMString, short>::const_iterator i;
        i = inrefs.find(op);
        if (i != inrefs.end()) {
		setIn(a, i->second);
	} else {
		i = postrefs.find(op);
		if (i != postrefs.end()) {
			setPost(a, i->second);
		} else {
			i = prerefs.find(op);
			if (i != prerefs.end()) {
				setPre(a, i->second);
			}
		}
	}
}
void
MMLmoDict::setPre(const MMLAttribute **a, short row) {
	for (short i=0; i<presize; ++i) {
		a[prepos[i]] = pre[row][i];
	}
}
void
MMLmoDict::setIn(const MMLAttribute **a, short row) {
	for (short i=0; i<insize; ++i) {
		a[inpos[i]] = in[row][i];
	}
}
void
MMLmoDict::setPost(const MMLAttribute **a, short row) {
	for (short i=0; i<postsize; ++i) {
		a[postpos[i]] = post[row][i];
	}
}
void
MMLmoDict::init() {
	ready = true;
	for (short i=0; i<50; ++i) {
		DOMString op = presyms[i];
		op.resolveEntities();
		prerefs.insert(std::pair<DOMString, short>(op, i));
	}
	for (short i=0; i<254; ++i) {
		DOMString op = insyms[i];
		op.resolveEntities();
		inrefs.insert(std::pair<DOMString, short>(op, i));
	}
	for (short i=0; i<47; ++i) {
		DOMString op = postsyms[i];
		op.resolveEntities();
		postrefs.insert(std::pair<DOMString, short>(op, i));
	}
}
const MMLbool MMLmoDict::a0_0(true, false);
const MMLh_unit MMLmoDict::a1_0(DOMString("verythickmathspace"), false);
const MMLh_unit MMLmoDict::a1_1(DOMString("verythinmathspace"), false);
const MMLh_unit MMLmoDict::a1_2(DOMString("veryverythinmathspace"), false);
const MMLh_unit MMLmoDict::a1_3(DOMString("0"), false);
const MMLh_unit MMLmoDict::a1_4(DOMString("mediummathspace"), false);
const MMLh_unit MMLmoDict::a1_5(DOMString("thickmathspace"), false);
const MMLh_unit MMLmoDict::a1_6(DOMString("thinmathspace"), false);
const MMLh_unit MMLmoDict::a1_7(DOMString("0em"), false);
const short MMLmoDict::prepos[6] = {
moFENCE, moLARGEOP, moLSPACE, moMOVABLELIMITS, moRSPACE, moSTRETCHY, 
};
const char *MMLmoDict::presyms[50] = {
"&PlusMinus;","&LeftDoubleBracket;","max", //0
"&Union;","&LeftSkeleton;","++", //3
"&Sqrt;","&Exists;","&Product;", //6
"&CirclePlus;","&UnionPlus;","&Vee;", //9
"&CircleTimes;","&DoubleContourIntegral;","&LeftBracketingBar;", //12
"&ClockwiseContourIntegral;","&Del;","&Not;", //15
"&LeftAngleBracket;","&CounterClockwiseContourIntegral;","(", //18
"&Intersection;","&CapitalDifferentialD;","&ForAll;", //21
"&OpenCurlyDoubleQuote;","&Coproduct;","-", //24
"--","&PartialD;","lim", //27
"&ContourIntegral;","&Sum;","&LeftCeiling;", //30
"[","&Square;","!", //33
"&CircleDot;","&LeftDoubleBracketingBar;","&NotExists;", //36
"{","min","&CircleMinus;", //39
"&OpenCurlyQuote;","&Integral;","&DifferentialD;", //42
"+","&amp;","&MinusPlus;", //45
"&Wedge;","&LeftFloor;"};
const MMLAttribute *const MMLmoDict::pre[50][6] = {
{0, 0, &a1_7, 0, &a1_2, 0, },//0
{&a0_0, 0, &a1_7, 0, &a1_7, &a0_0, },//1
{0, 0, &a1_7, &a0_0, &a1_6, 0, },//2
{0, &a0_0, &a1_7, &a0_0, &a1_6, &a0_0, },//3
{&a0_0, 0, &a1_7, 0, &a1_7, 0, },//4
{0, 0, &a1_7, 0, &a1_1, 0, },//5
{0, 0, &a1_7, 0, &a1_1, &a0_0, },//6
{0, 0, &a1_7, 0, &a1_5, 0, },//7
{0, &a0_0, &a1_7, &a0_0, &a1_6, &a0_0, },//8
{0, &a0_0, &a1_7, &a0_0, &a1_6, 0, },//9
{0, &a0_0, &a1_7, &a0_0, &a1_6, &a0_0, },//10
{0, &a0_0, &a1_7, &a0_0, &a1_6, &a0_0, },//11
{0, &a0_0, &a1_7, &a0_0, &a1_6, 0, },//12
{0, &a0_0, &a1_7, 0, &a1_7, &a0_0, },//13
{&a0_0, 0, &a1_7, 0, &a1_7, &a0_0, },//14
{0, &a0_0, &a1_7, 0, &a1_7, &a0_0, },//15
{0, 0, &a1_7, 0, &a1_1, 0, },//16
{0, 0, &a1_7, 0, &a1_5, 0, },//17
{&a0_0, 0, &a1_7, 0, &a1_7, &a0_0, },//18
{0, &a0_0, &a1_7, 0, &a1_7, &a0_0, },//19
{&a0_0, 0, &a1_7, 0, &a1_7, &a0_0, },//20
{0, &a0_0, &a1_7, &a0_0, &a1_6, &a0_0, },//21
{0, 0, &a1_7, 0, &a1_1, 0, },//22
{0, 0, &a1_7, 0, &a1_5, 0, },//23
{&a0_0, 0, &a1_7, 0, &a1_7, 0, },//24
{0, &a0_0, &a1_7, &a0_0, &a1_6, &a0_0, },//25
{0, 0, &a1_7, 0, &a1_2, 0, },//26
{0, 0, &a1_7, 0, &a1_1, 0, },//27
{0, 0, &a1_7, 0, &a1_1, 0, },//28
{0, 0, &a1_7, &a0_0, &a1_6, 0, },//29
{0, &a0_0, &a1_7, 0, &a1_7, &a0_0, },//30
{0, &a0_0, &a1_7, &a0_0, &a1_6, &a0_0, },//31
{&a0_0, 0, &a1_7, 0, &a1_7, &a0_0, },//32
{&a0_0, 0, &a1_7, 0, &a1_7, &a0_0, },//33
{0, 0, &a1_7, 0, &a1_1, 0, },//34
{0, 0, &a1_7, 0, &a1_5, 0, },//35
{0, &a0_0, &a1_7, &a0_0, &a1_6, 0, },//36
{&a0_0, 0, &a1_7, 0, &a1_7, &a0_0, },//37
{0, 0, &a1_7, 0, &a1_5, 0, },//38
{&a0_0, 0, &a1_7, 0, &a1_7, &a0_0, },//39
{0, 0, &a1_7, &a0_0, &a1_6, 0, },//40
{0, &a0_0, &a1_7, &a0_0, &a1_6, 0, },//41
{&a0_0, 0, &a1_7, 0, &a1_7, 0, },//42
{0, &a0_0, &a1_7, 0, &a1_7, &a0_0, },//43
{0, 0, &a1_7, 0, &a1_1, 0, },//44
{0, 0, &a1_7, 0, &a1_2, 0, },//45
{0, 0, &a1_7, 0, &a1_5, 0, },//46
{0, 0, &a1_7, 0, &a1_2, 0, },//47
{0, &a0_0, &a1_7, &a0_0, &a1_6, &a0_0, },//48
{&a0_0, 0, &a1_7, 0, &a1_7, &a0_0, }
};
const short MMLmoDict::inpos[5] = {
moLSPACE, moMINSIZE, moRSPACE, moSEPARATOR, moSTRETCHY, 
};
const char *MMLmoDict::insyms[254] = {
"&LeftTriangleBar;","&amp;&amp;","/", //0
"&NotGreater;","&NotGreaterGreater;","&RightVectorBar;", //3
"&Or;","&And;","&GreaterSlantEqual;", //6
"&TildeFullEqual;","&PrecedesEqual;","&UpEquilibrium;", //9
"&LongLeftArrow;","&NotNestedLessLess;","&LeftVector;", //12
"&RightTeeArrow;","&Diamond;",">=", //15
"&DownRightTeeVector;","&LeftUpVector;","==", //18
"&UpTeeArrow;","&ShortUpArrow;","&GreaterLess;", //21
"&EqualTilde;","&Congruent;","/=", //24
"&LongLeftRightArrow;","^","&Backslash;", //27
"&DownLeftVector;","&NotSquareSubset;","&DoubleUpArrow;", //30
"&NotSquareSupersetEqual;","&NotSucceedsEqual;","&NotTildeTilde;", //33
"&LeftUpVectorBar;","&NotElement;","+=", //36
"-","&DownArrow;","&NotSucceedsTilde;", //39
"&SuchThat;","&DownTeeArrow;","&HorizontalLine;", //42
"*=","&LowerRightArrow;","&NotGreaterFullEqual;", //45
"&SquareUnion;","&NotLessTilde;","&LowerLeftArrow;", //48
"&RoundImplies;","&DownArrowBar;","&HumpEqual;", //51
"&ShortDownArrow;","&NotSucceeds;","&RightArrowLeftArrow;", //54
"&NotSubsetEqual;","&Wedge;","&Proportion;", //57
"&Precedes;","&NotPrecedesSlantEqual;","&Assign;", //60
"&DownLeftRightVector;","&SquareIntersection;","&PlusMinus;", //63
"&PrecedesTilde;","=","&Union;", //66
"&lt;","&SquareSupersetEqual;","&UpArrowDownArrow;", //69
"&NotHumpDownHump;","&Because;","&UnionPlus;", //72
"&NotCupCap;","&CircleTimes;","&UpArrow;", //75
"&InvisibleTimes;","&NotGreaterTilde;","&RightDownVectorBar;", //78
"&NotLessGreater;","&NotLeftTriangle;","?", //81
"&DoubleLeftArrow;","&Implies;","&RightUpTeeVector;", //84
"**","&CupCap;","&NotHumpEqual;", //87
":=","&lt;=","&DoubleRightArrow;", //90
"&GreaterEqual;",":","*", //93
"&NotPrecedesEqual;","&RightUpVector;","&Equilibrium;", //96
"&LessLess;","&CenterDot;","&Star;", //99
"&LongRightArrow;","@","&Subset;", //102
"&LeftArrowBar;","&LeftVectorBar;","&Element;", //105
"&RightUpDownVector;","&Tilde;","&NotTilde;", //108
"&RightVector;","&NotLessLess;","&NotDoubleVerticalBar;", //111
"&CircleMinus;","&NotRightTriangleBar;","&UpperLeftArrow;", //114
"&NotLessFullEqual;","&LessTilde;","&MinusPlus;", //117
"&HumpDownHump;","&DoubleLongRightArrow;","&SquareSubset;", //120
"&NotVerticalBar;","&NotReverseElement;","&DoubleRightTee;", //123
",","&LessSlantEqual;","&DoubleLongLeftRightArrow;", //126
"//","&SquareSuperset;","&DownRightVectorBar;", //129
"&NotSquareSubsetEqual;","&LessGreater;","&NotRightTriangleEqual;", //132
"&Cross;","&LeftTeeArrow;","&RightDownTeeVector;", //135
"&ApplyFunction;","&CirclePlus;","&LessFullEqual;", //138
"&DoubleLeftTee;","&TildeEqual;","|", //141
"||","&LeftTeeVector;","&ReverseEquilibrium;", //144
"&DownArrowUpArrow;","&LeftTee;","&LeftArrowRightArrow;", //147
"&SubsetEqual;","&NotLess;","&GreaterFullEqual;", //150
"&Cap;","&NotNestedGreaterGreater;","&Colon;", //153
"&LeftUpDownVector;","&SucceedsSlantEqual;","&RightTee;", //156
"&NestedGreaterGreater;","&RightTriangleEqual;","&RightUpVectorBar;", //159
"&LeftTriangle;","&DownLeftTeeVector;","&Coproduct;", //162
"&GreaterGreater;","~","&DoubleDownArrow;", //165
"&RightTeeVector;","&UpTee;","&Therefore;", //168
"&NestedLessLess;","&NotLeftTriangleBar;","&NotSuperset;", //171
"&DotEqual;","&CircleDot;","-=", //174
"&NotTildeFullEqual;","&NotLessEqual;","&LeftRightArrow;", //177
"&ReverseUpEquilibrium;","&NotEqualTilde;","&Proportional;", //180
"&DoubleLeftRightArrow;","&NotEqual;","_", //183
"&NotGreaterLess;","&RightDownVector;","+", //186
"&amp;","&NotCongruent;","&DownRightVector;", //189
"&Cup;","&SucceedsTilde;","&NotGreaterSlantEqual;", //192
"&TildeTilde;","&Equal;","&UpDownArrow;", //195
"&NotPrecedes;","&LeftDownVector;","&NotLeftTriangleEqual;", //198
"&VerticalLine;","&InvisibleComma;","&DownTee;", //201
"&LeftDownVectorBar;","&Vee;","&Superset;", //204
"&NotSubset;","&DoubleVerticalBar;","&NotRightTriangle;", //207
"&LeftRightVector;","&GreaterEqualLess;","&RightTriangle;", //210
"&NotSupersetEqual;","&SupersetEqual;","&RightArrow;", //213
">","&DoubleLongLeftArrow;","&LessEqualGreater;", //216
"&LeftDownTeeVector;","&SucceedsEqual;","&LeftTriangleEqual;", //219
"&NotLessSlantEqual;","&NotTildeEqual;","->", //222
"&VerticalSeparator;","&Intersection;","&ReverseElement;", //225
"&VerticalTilde;","&RightArrowBar;","&NotGreaterEqual;", //228
"&le;","&NotPrecedesTilde;",".", //231
"&LeftArrow;","&NotSucceedsSlantEqual;",";", //234
"!=","&DoubleUpDownArrow;","&Succeeds;", //237
"&ShortLeftArrow;","&RightTriangleBar;","&SmallCircle;", //240
"&SquareSubsetEqual;","&UpperRightArrow;","&LeftUpTeeVector;", //243
"&PrecedesSlantEqual;","&NotSquareSuperset;","&UpArrowBar;", //246
"&VerticalBar;","&DownLeftVectorBar;","&ShortRightArrow;", //249
"&lt;>","&GreaterTilde;"};
const MMLAttribute *const MMLmoDict::in[254][5] = {
{&a1_5, 0, &a1_5, 0, 0, },//0
{&a1_5, 0, &a1_5, 0, 0, },//1
{&a1_6, 0, &a1_6, 0, &a0_0, },//2
{&a1_5, 0, &a1_5, 0, 0, },//3
{&a1_5, 0, &a1_5, 0, 0, },//4
{&a1_5, 0, &a1_5, 0, &a0_0, },//5
{&a1_4, 0, &a1_4, 0, &a0_0, },//6
{&a1_4, 0, &a1_4, 0, &a0_0, },//7
{&a1_5, 0, &a1_5, 0, 0, },//8
{&a1_5, 0, &a1_5, 0, 0, },//9
{&a1_5, 0, &a1_5, 0, 0, },//10
{&a1_1, 0, &a1_1, 0, &a0_0, },//11
{&a1_1, 0, &a1_1, 0, &a0_0, },//12
{&a1_5, 0, &a1_5, 0, 0, },//13
{&a1_5, 0, &a1_5, 0, &a0_0, },//14
{&a1_5, 0, &a1_5, 0, &a0_0, },//15
{&a1_6, 0, &a1_6, 0, 0, },//16
{&a1_5, 0, &a1_5, 0, 0, },//17
{&a1_5, 0, &a1_5, 0, &a0_0, },//18
{&a1_1, 0, &a1_1, 0, &a0_0, },//19
{&a1_5, 0, &a1_5, 0, 0, },//20
{&a1_1, 0, &a1_1, 0, &a0_0, },//21
{&a1_1, 0, &a1_1, 0, 0, },//22
{&a1_5, 0, &a1_5, 0, 0, },//23
{&a1_5, 0, &a1_5, 0, 0, },//24
{&a1_5, 0, &a1_5, 0, 0, },//25
{&a1_5, 0, &a1_5, 0, 0, },//26
{&a1_1, 0, &a1_1, 0, &a0_0, },//27
{&a1_1, 0, &a1_1, 0, 0, },//28
{&a1_6, 0, &a1_6, 0, &a0_0, },//29
{&a1_5, 0, &a1_5, 0, &a0_0, },//30
{&a1_5, 0, &a1_5, 0, 0, },//31
{&a1_1, 0, &a1_1, 0, &a0_0, },//32
{&a1_5, 0, &a1_5, 0, 0, },//33
{&a1_5, 0, &a1_5, 0, 0, },//34
{&a1_5, 0, &a1_5, 0, 0, },//35
{&a1_1, 0, &a1_1, 0, &a0_0, },//36
{&a1_5, 0, &a1_5, 0, 0, },//37
{&a1_5, 0, &a1_5, 0, 0, },//38
{&a1_4, 0, &a1_4, 0, 0, },//39
{&a1_1, 0, &a1_1, 0, &a0_0, },//40
{&a1_5, 0, &a1_5, 0, 0, },//41
{&a1_5, 0, &a1_5, 0, 0, },//42
{&a1_1, 0, &a1_1, 0, &a0_0, },//43
{&a1_7, &a1_3, &a1_7, 0, &a0_0, },//44
{&a1_5, 0, &a1_5, 0, 0, },//45
{&a1_5, 0, &a1_5, 0, &a0_0, },//46
{&a1_5, 0, &a1_5, 0, 0, },//47
{&a1_4, 0, &a1_4, 0, &a0_0, },//48
{&a1_5, 0, &a1_5, 0, 0, },//49
{&a1_5, 0, &a1_5, 0, &a0_0, },//50
{&a1_5, 0, &a1_5, 0, 0, },//51
{&a1_1, 0, &a1_1, 0, &a0_0, },//52
{&a1_5, 0, &a1_5, 0, 0, },//53
{&a1_1, 0, &a1_1, 0, 0, },//54
{&a1_5, 0, &a1_5, 0, 0, },//55
{&a1_5, 0, &a1_5, 0, &a0_0, },//56
{&a1_5, 0, &a1_5, 0, 0, },//57
{&a1_6, 0, &a1_6, 0, 0, },//58
{&a1_5, 0, &a1_5, 0, 0, },//59
{&a1_5, 0, &a1_5, 0, 0, },//60
{&a1_5, 0, &a1_5, 0, 0, },//61
{&a1_5, 0, &a1_5, 0, 0, },//62
{&a1_5, 0, &a1_5, 0, &a0_0, },//63
{&a1_4, 0, &a1_4, 0, &a0_0, },//64
{&a1_4, 0, &a1_4, 0, 0, },//65
{&a1_5, 0, &a1_5, 0, 0, },//66
{&a1_5, 0, &a1_5, 0, 0, },//67
{&a1_4, 0, &a1_4, 0, &a0_0, },//68
{&a1_5, 0, &a1_5, 0, 0, },//69
{&a1_5, 0, &a1_5, 0, 0, },//70
{&a1_1, 0, &a1_1, 0, &a0_0, },//71
{&a1_5, 0, &a1_5, 0, 0, },//72
{&a1_5, 0, &a1_5, 0, 0, },//73
{&a1_4, 0, &a1_4, 0, &a0_0, },//74
{&a1_5, 0, &a1_5, 0, 0, },//75
{&a1_6, 0, &a1_6, 0, 0, },//76
{&a1_1, 0, &a1_1, 0, &a0_0, },//77
{&a1_7, 0, &a1_7, 0, 0, },//78
{&a1_5, 0, &a1_5, 0, 0, },//79
{&a1_1, 0, &a1_1, 0, &a0_0, },//80
{&a1_5, 0, &a1_5, 0, 0, },//81
{&a1_5, 0, &a1_5, 0, 0, },//82
{&a1_1, 0, &a1_1, 0, 0, },//83
{&a1_5, 0, &a1_5, 0, &a0_0, },//84
{&a1_5, 0, &a1_5, 0, &a0_0, },//85
{&a1_1, 0, &a1_1, 0, &a0_0, },//86
{&a1_1, 0, &a1_1, 0, 0, },//87
{&a1_5, 0, &a1_5, 0, 0, },//88
{&a1_5, 0, &a1_5, 0, 0, },//89
{&a1_5, 0, &a1_5, 0, 0, },//90
{&a1_5, 0, &a1_5, 0, 0, },//91
{&a1_5, 0, &a1_5, 0, &a0_0, },//92
{&a1_5, 0, &a1_5, 0, 0, },//93
{&a1_5, 0, &a1_5, 0, 0, },//94
{&a1_6, 0, &a1_6, 0, 0, },//95
{&a1_5, 0, &a1_5, 0, 0, },//96
{&a1_1, 0, &a1_1, 0, &a0_0, },//97
{&a1_5, 0, &a1_5, 0, &a0_0, },//98
{&a1_5, 0, &a1_5, 0, 0, },//99
{&a1_6, 0, &a1_6, 0, 0, },//100
{&a1_6, 0, &a1_6, 0, 0, },//101
{&a1_1, 0, &a1_1, 0, &a0_0, },//102
{&a1_1, 0, &a1_1, 0, 0, },//103
{&a1_5, 0, &a1_5, 0, 0, },//104
{&a1_5, 0, &a1_5, 0, &a0_0, },//105
{&a1_5, 0, &a1_5, 0, &a0_0, },//106
{&a1_5, 0, &a1_5, 0, 0, },//107
{&a1_1, 0, &a1_1, 0, &a0_0, },//108
{&a1_5, 0, &a1_5, 0, 0, },//109
{&a1_5, 0, &a1_5, 0, 0, },//110
{&a1_5, 0, &a1_5, 0, &a0_0, },//111
{&a1_5, 0, &a1_5, 0, 0, },//112
{&a1_5, 0, &a1_5, 0, 0, },//113
{&a1_6, 0, &a1_6, 0, 0, },//114
{&a1_5, 0, &a1_5, 0, 0, },//115
{&a1_5, 0, &a1_5, 0, &a0_0, },//116
{&a1_5, 0, &a1_5, 0, 0, },//117
{&a1_5, 0, &a1_5, 0, 0, },//118
{&a1_4, 0, &a1_4, 0, 0, },//119
{&a1_5, 0, &a1_5, 0, 0, },//120
{&a1_1, 0, &a1_1, 0, &a0_0, },//121
{&a1_5, 0, &a1_5, 0, 0, },//122
{&a1_5, 0, &a1_5, 0, 0, },//123
{&a1_5, 0, &a1_5, 0, 0, },//124
{&a1_5, 0, &a1_5, 0, 0, },//125
{&a1_7, 0, &a1_0, &a0_0, 0, },//126
{&a1_5, 0, &a1_5, 0, 0, },//127
{&a1_1, 0, &a1_1, 0, &a0_0, },//128
{&a1_5, 0, &a1_5, 0, 0, },//129
{&a1_5, 0, &a1_5, 0, 0, },//130
{&a1_5, 0, &a1_5, 0, &a0_0, },//131
{&a1_5, 0, &a1_5, 0, 0, },//132
{&a1_5, 0, &a1_5, 0, 0, },//133
{&a1_5, 0, &a1_5, 0, 0, },//134
{&a1_1, 0, &a1_1, 0, 0, },//135
{&a1_5, 0, &a1_5, 0, &a0_0, },//136
{&a1_1, 0, &a1_1, 0, &a0_0, },//137
{&a1_7, 0, &a1_7, 0, 0, },//138
{&a1_6, 0, &a1_6, 0, 0, },//139
{&a1_5, 0, &a1_5, 0, 0, },//140
{&a1_5, 0, &a1_5, 0, 0, },//141
{&a1_5, 0, &a1_5, 0, 0, },//142
{&a1_5, 0, &a1_5, 0, &a0_0, },//143
{&a1_4, 0, &a1_4, 0, 0, },//144
{&a1_5, 0, &a1_5, 0, &a0_0, },//145
{&a1_5, 0, &a1_5, 0, &a0_0, },//146
{&a1_1, 0, &a1_1, 0, &a0_0, },//147
{&a1_5, 0, &a1_5, 0, 0, },//148
{&a1_5, 0, &a1_5, 0, &a0_0, },//149
{&a1_5, 0, &a1_5, 0, 0, },//150
{&a1_5, 0, &a1_5, 0, 0, },//151
{&a1_5, 0, &a1_5, 0, 0, },//152
{&a1_6, 0, &a1_6, 0, 0, },//153
{&a1_5, 0, &a1_5, 0, 0, },//154
{&a1_5, 0, &a1_5, 0, 0, },//155
{&a1_1, 0, &a1_1, 0, &a0_0, },//156
{&a1_5, 0, &a1_5, 0, 0, },//157
{&a1_5, 0, &a1_5, 0, 0, },//158
{&a1_5, 0, &a1_5, 0, 0, },//159
{&a1_5, 0, &a1_5, 0, 0, },//160
{&a1_1, 0, &a1_1, 0, &a0_0, },//161
{&a1_5, 0, &a1_5, 0, 0, },//162
{&a1_5, 0, &a1_5, 0, &a0_0, },//163
{&a1_6, 0, &a1_6, 0, 0, },//164
{&a1_5, 0, &a1_5, 0, 0, },//165
{&a1_1, 0, &a1_1, 0, 0, },//166
{&a1_1, 0, &a1_1, 0, &a0_0, },//167
{&a1_5, 0, &a1_5, 0, &a0_0, },//168
{&a1_5, 0, &a1_5, 0, 0, },//169
{&a1_5, 0, &a1_5, 0, 0, },//170
{&a1_5, 0, &a1_5, 0, 0, },//171
{&a1_5, 0, &a1_5, 0, 0, },//172
{&a1_5, 0, &a1_5, 0, 0, },//173
{&a1_5, 0, &a1_5, 0, 0, },//174
{&a1_1, 0, &a1_1, 0, 0, },//175
{&a1_5, 0, &a1_5, 0, 0, },//176
{&a1_5, 0, &a1_5, 0, 0, },//177
{&a1_5, 0, &a1_5, 0, 0, },//178
{&a1_5, 0, &a1_5, 0, &a0_0, },//179
{&a1_1, 0, &a1_1, 0, &a0_0, },//180
{&a1_5, 0, &a1_5, 0, 0, },//181
{&a1_5, 0, &a1_5, 0, 0, },//182
{&a1_5, 0, &a1_5, 0, &a0_0, },//183
{&a1_5, 0, &a1_5, 0, 0, },//184
{&a1_1, 0, &a1_1, 0, 0, },//185
{&a1_5, 0, &a1_5, 0, 0, },//186
{&a1_1, 0, &a1_1, 0, &a0_0, },//187
{&a1_4, 0, &a1_4, 0, 0, },//188
{&a1_5, 0, &a1_5, 0, 0, },//189
{&a1_5, 0, &a1_5, 0, 0, },//190
{&a1_5, 0, &a1_5, 0, &a0_0, },//191
{&a1_6, 0, &a1_6, 0, 0, },//192
{&a1_5, 0, &a1_5, 0, 0, },//193
{&a1_5, 0, &a1_5, 0, 0, },//194
{&a1_5, 0, &a1_5, 0, 0, },//195
{&a1_5, 0, &a1_5, 0, 0, },//196
{&a1_1, 0, &a1_1, 0, &a0_0, },//197
{&a1_5, 0, &a1_5, 0, 0, },//198
{&a1_1, 0, &a1_1, 0, &a0_0, },//199
{&a1_5, 0, &a1_5, 0, 0, },//200
{&a1_7, &a1_3, &a1_7, 0, &a0_0, },//201
{&a1_7, 0, &a1_7, &a0_0, 0, },//202
{&a1_5, 0, &a1_5, 0, 0, },//203
{&a1_1, 0, &a1_1, 0, &a0_0, },//204
{&a1_6, 0, &a1_6, 0, 0, },//205
{&a1_5, 0, &a1_5, 0, 0, },//206
{&a1_5, 0, &a1_5, 0, 0, },//207
{&a1_5, 0, &a1_5, 0, 0, },//208
{&a1_5, 0, &a1_5, 0, 0, },//209
{&a1_5, 0, &a1_5, 0, &a0_0, },//210
{&a1_5, 0, &a1_5, 0, 0, },//211
{&a1_5, 0, &a1_5, 0, 0, },//212
{&a1_5, 0, &a1_5, 0, 0, },//213
{&a1_5, 0, &a1_5, 0, 0, },//214
{&a1_5, 0, &a1_5, 0, &a0_0, },//215
{&a1_5, 0, &a1_5, 0, 0, },//216
{&a1_1, 0, &a1_1, 0, &a0_0, },//217
{&a1_5, 0, &a1_5, 0, 0, },//218
{&a1_1, 0, &a1_1, 0, &a0_0, },//219
{&a1_5, 0, &a1_5, 0, 0, },//220
{&a1_5, 0, &a1_5, 0, 0, },//221
{&a1_5, 0, &a1_5, 0, 0, },//222
{&a1_5, 0, &a1_5, 0, 0, },//223
{&a1_5, 0, &a1_5, 0, 0, },//224
{&a1_5, 0, &a1_5, 0, &a0_0, },//225
{&a1_4, 0, &a1_4, 0, &a0_0, },//226
{&a1_5, 0, &a1_5, 0, 0, },//227
{&a1_6, 0, &a1_6, 0, 0, },//228
{&a1_5, 0, &a1_5, 0, &a0_0, },//229
{&a1_5, 0, &a1_5, 0, 0, },//230
{&a1_5, 0, &a1_5, 0, 0, },//231
{&a1_5, 0, &a1_5, 0, 0, },//232
{&a1_7, 0, &a1_7, 0, 0, },//233
{&a1_5, 0, &a1_5, 0, &a0_0, },//234
{&a1_5, 0, &a1_5, 0, 0, },//235
{&a1_7, 0, &a1_5, &a0_0, 0, },//236
{&a1_5, 0, &a1_5, 0, 0, },//237
{&a1_1, 0, &a1_1, 0, &a0_0, },//238
{&a1_5, 0, &a1_5, 0, 0, },//239
{&a1_5, 0, &a1_5, 0, 0, },//240
{&a1_5, 0, &a1_5, 0, 0, },//241
{&a1_1, 0, &a1_1, 0, 0, },//242
{&a1_5, 0, &a1_5, 0, 0, },//243
{&a1_5, 0, &a1_5, 0, &a0_0, },//244
{&a1_1, 0, &a1_1, 0, &a0_0, },//245
{&a1_5, 0, &a1_5, 0, 0, },//246
{&a1_5, 0, &a1_5, 0, 0, },//247
{&a1_1, 0, &a1_1, 0, &a0_0, },//248
{&a1_5, 0, &a1_5, 0, 0, },//249
{&a1_5, 0, &a1_5, 0, &a0_0, },//250
{&a1_5, 0, &a1_5, 0, 0, },//251
{&a1_1, 0, &a1_1, 0, 0, },//252
{&a1_5, 0, &a1_5, 0, 0, }
};
const short MMLmoDict::postpos[6] = {
moACCENT, moFENCE, moLSPACE, moRSPACE, moSEPARATOR, moSTRETCHY, 
};
const char *MMLmoDict::postsyms[47] = {
"&DiacriticalGrave;","&DownBreve;","&DiacriticalLeftArrow;", //0
"&Hat;","&Breve;","&CloseCurlyDoubleQuote;", //3
"&OverBracket;","&UnderParenthesis;","++", //6
"&DiacriticalDot;","&TripleDot;","&RightBracketingBar;", //9
"&RightDoubleBracket;","&DiacriticalAcute;","&DiacriticalTilde;", //12
"!!","&RightAngleBracket;","&RightCeiling;", //15
"&RightFloor;","&DiacriticalLeftRightVector;","&Hacek;", //18
"&CloseCurlyQuote;","...","&DiacriticalRightVector;", //21
"--","&RightSkeleton;","&DoubleDot;", //24
";","&OverParenthesis;","!", //27
"&UnderBracket;","&DiacriticalLeftRightArrow;","]", //30
"..","&amp;","&DiacriticalRightArrow;", //33
"&DiacriticalLeftVector;","&Cedilla;","&RightDoubleBracketingBar;", //36
")","&UnderBar;","&UnderBrace;", //39
"&OverBar;","'","&DiacriticalDoubleAcute;", //42
"}","&OverBrace;"};
const MMLAttribute *const MMLmoDict::post[47][6] = {
{&a0_0, 0, &a1_7, &a1_7, 0, 0, },//0
{&a0_0, 0, &a1_7, &a1_7, 0, 0, },//1
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//2
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//3
{&a0_0, 0, &a1_7, &a1_7, 0, 0, },//4
{0, &a0_0, &a1_7, &a1_7, 0, 0, },//5
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//6
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//7
{0, 0, &a1_1, &a1_7, 0, 0, },//8
{&a0_0, 0, &a1_7, &a1_7, 0, 0, },//9
{&a0_0, 0, &a1_7, &a1_7, 0, 0, },//10
{0, &a0_0, &a1_7, &a1_7, 0, &a0_0, },//11
{0, &a0_0, &a1_7, &a1_7, 0, &a0_0, },//12
{&a0_0, 0, &a1_7, &a1_7, 0, 0, },//13
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//14
{0, 0, &a1_1, &a1_7, 0, 0, },//15
{0, &a0_0, &a1_7, &a1_7, 0, &a0_0, },//16
{0, &a0_0, &a1_7, &a1_7, 0, &a0_0, },//17
{0, &a0_0, &a1_7, &a1_7, 0, &a0_0, },//18
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//19
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//20
{0, &a0_0, &a1_7, &a1_7, 0, 0, },//21
{0, 0, &a1_4, &a1_7, 0, 0, },//22
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//23
{0, 0, &a1_1, &a1_7, 0, 0, },//24
{0, &a0_0, &a1_7, &a1_7, 0, 0, },//25
{&a0_0, 0, &a1_7, &a1_7, 0, 0, },//26
{0, 0, &a1_7, &a1_7, &a0_0, 0, },//27
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//28
{0, 0, &a1_1, &a1_7, 0, 0, },//29
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//30
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//31
{0, &a0_0, &a1_7, &a1_7, 0, &a0_0, },//32
{0, 0, &a1_4, &a1_7, 0, 0, },//33
{0, 0, &a1_5, &a1_7, 0, 0, },//34
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//35
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//36
{&a0_0, 0, &a1_7, &a1_7, 0, 0, },//37
{0, &a0_0, &a1_7, &a1_7, 0, &a0_0, },//38
{0, &a0_0, &a1_7, &a1_7, 0, &a0_0, },//39
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//40
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//41
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, },//42
{0, 0, &a1_1, &a1_7, 0, 0, },//43
{&a0_0, 0, &a1_7, &a1_7, 0, 0, },//44
{0, &a0_0, &a1_7, &a1_7, 0, &a0_0, },//45
{&a0_0, 0, &a1_7, &a1_7, 0, &a0_0, }
};
