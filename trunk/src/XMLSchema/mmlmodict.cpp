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
const MMLh_unit MMLmoDict::a1_0(DOMString("thinmathspace"), false);
const MMLh_unit MMLmoDict::a1_1(DOMString("verythinmathspace"), false);
const MMLh_unit MMLmoDict::a1_2(DOMString("veryverythinmathspace"), false);
const MMLh_unit MMLmoDict::a1_3(DOMString("thickmathspace"), false);
const MMLh_unit MMLmoDict::a1_4(DOMString("0"), false);
const MMLh_unit MMLmoDict::a1_5(DOMString("0em"), false);
const MMLh_unit MMLmoDict::a1_6(DOMString("mediummathspace"), false);
const MMLh_unit MMLmoDict::a1_7(DOMString("verythickmathspace"), false);
const short MMLmoDict::prepos[6] = {
moFENCE, moLARGEOP, moLSPACE, moMOVABLELIMITS, moRSPACE, moSTRETCHY, 
};
const char *MMLmoDict::presyms[50] = {
"&LeftDoubleBracket;","&CircleMinus;","&OpenCurlyQuote;", //0
"&Wedge;","&amp;","&DifferentialD;", //3
"&Vee;","{","!", //6
"&CounterClockwiseContourIntegral;","&LeftBracketingBar;","&LeftCeiling;", //9
"&ClockwiseContourIntegral;","&NotExists;","&OpenCurlyDoubleQuote;", //12
"+","&Sqrt;","&CapitalDifferentialD;", //15
"&CirclePlus;","&LeftSkeleton;","&PlusMinus;", //18
"lim","&Sum;","&DoubleContourIntegral;", //21
"&LeftDoubleBracketingBar;","&ForAll;","&Intersection;", //24
"&Product;","&PartialD;","&Square;", //27
"[","&ContourIntegral;","&CircleTimes;", //30
"&CircleDot;","&LeftFloor;","&LeftAngleBracket;", //33
"&UnionPlus;","max","&Not;", //36
"&Coproduct;","min","&Del;", //39
"&MinusPlus;","++","-", //42
"&Union;","--","&Exists;", //45
"&Integral;","("};
const MMLAttribute *const MMLmoDict::pre[50][6] = {
{&a0_0, 0, &a1_5, 0, &a1_5, &a0_0, },//0
{0, &a0_0, &a1_5, &a0_0, &a1_0, 0, },//1
{&a0_0, 0, &a1_5, 0, &a1_5, 0, },//2
{0, &a0_0, &a1_5, &a0_0, &a1_0, &a0_0, },//3
{0, 0, &a1_5, 0, &a1_3, 0, },//4
{0, 0, &a1_5, 0, &a1_1, 0, },//5
{0, &a0_0, &a1_5, &a0_0, &a1_0, &a0_0, },//6
{&a0_0, 0, &a1_5, 0, &a1_5, &a0_0, },//7
{0, 0, &a1_5, 0, &a1_3, 0, },//8
{0, &a0_0, &a1_5, 0, &a1_5, &a0_0, },//9
{&a0_0, 0, &a1_5, 0, &a1_5, &a0_0, },//10
{&a0_0, 0, &a1_5, 0, &a1_5, &a0_0, },//11
{0, &a0_0, &a1_5, 0, &a1_5, &a0_0, },//12
{0, 0, &a1_5, 0, &a1_3, 0, },//13
{&a0_0, 0, &a1_5, 0, &a1_5, 0, },//14
{0, 0, &a1_5, 0, &a1_2, 0, },//15
{0, 0, &a1_5, 0, &a1_1, &a0_0, },//16
{0, 0, &a1_5, 0, &a1_1, 0, },//17
{0, &a0_0, &a1_5, &a0_0, &a1_0, 0, },//18
{&a0_0, 0, &a1_5, 0, &a1_5, 0, },//19
{0, 0, &a1_5, 0, &a1_2, 0, },//20
{0, 0, &a1_5, &a0_0, &a1_0, 0, },//21
{0, &a0_0, &a1_5, &a0_0, &a1_0, &a0_0, },//22
{0, &a0_0, &a1_5, 0, &a1_5, &a0_0, },//23
{&a0_0, 0, &a1_5, 0, &a1_5, &a0_0, },//24
{0, 0, &a1_5, 0, &a1_3, 0, },//25
{0, &a0_0, &a1_5, &a0_0, &a1_0, &a0_0, },//26
{0, &a0_0, &a1_5, &a0_0, &a1_0, &a0_0, },//27
{0, 0, &a1_5, 0, &a1_1, 0, },//28
{0, 0, &a1_5, 0, &a1_1, 0, },//29
{&a0_0, 0, &a1_5, 0, &a1_5, &a0_0, },//30
{0, &a0_0, &a1_5, 0, &a1_5, &a0_0, },//31
{0, &a0_0, &a1_5, &a0_0, &a1_0, 0, },//32
{0, &a0_0, &a1_5, &a0_0, &a1_0, 0, },//33
{&a0_0, 0, &a1_5, 0, &a1_5, &a0_0, },//34
{&a0_0, 0, &a1_5, 0, &a1_5, &a0_0, },//35
{0, &a0_0, &a1_5, &a0_0, &a1_0, &a0_0, },//36
{0, 0, &a1_5, &a0_0, &a1_0, 0, },//37
{0, 0, &a1_5, 0, &a1_3, 0, },//38
{0, &a0_0, &a1_5, &a0_0, &a1_0, &a0_0, },//39
{0, 0, &a1_5, &a0_0, &a1_0, 0, },//40
{0, 0, &a1_5, 0, &a1_1, 0, },//41
{0, 0, &a1_5, 0, &a1_2, 0, },//42
{0, 0, &a1_5, 0, &a1_1, 0, },//43
{0, 0, &a1_5, 0, &a1_2, 0, },//44
{0, &a0_0, &a1_5, &a0_0, &a1_0, &a0_0, },//45
{0, 0, &a1_5, 0, &a1_1, 0, },//46
{0, 0, &a1_5, 0, &a1_3, 0, },//47
{0, &a0_0, &a1_5, 0, &a1_5, &a0_0, },//48
{&a0_0, 0, &a1_5, 0, &a1_5, &a0_0, }
};
const short MMLmoDict::inpos[5] = {
moLSPACE, moMINSIZE, moRSPACE, moSEPARATOR, moSTRETCHY, 
};
const char *MMLmoDict::insyms[254] = {
"&UpTeeArrow;","&Precedes;","&NotTildeEqual;", //0
"&GreaterFullEqual;","&LeftRightVector;","&LeftTriangleEqual;", //3
"&SmallCircle;","&Vee;","&LessLess;", //6
"&HumpEqual;","&RightUpVector;","&NotCongruent;", //9
"&NotLeftTriangleBar;","*=","&LeftUpDownVector;", //12
"&RightUpTeeVector;","&LeftTee;","&DoubleRightTee;", //15
"&NotTilde;","&NotPrecedesTilde;","&NotSupersetEqual;", //18
"&NotGreaterTilde;","&PlusMinus;","&NotNestedGreaterGreater;", //21
"&DownRightVector;","&SubsetEqual;","&GreaterGreater;", //24
"&LowerRightArrow;","&NotGreaterEqual;","&Proportion;", //27
"&VerticalBar;","&Cap;","&NotLessSlantEqual;", //30
"/","&Superset;","&CircleDot;", //33
"&ShortDownArrow;","&TildeEqual;","&DownRightVectorBar;", //36
"//","&UnionPlus;","->", //39
"&GreaterSlantEqual;",">=","&And;", //42
"&DoubleLongLeftArrow;","&le;",":", //45
"&DownArrowUpArrow;","&RightUpVectorBar;","&DownArrowBar;", //48
"&DoubleLeftTee;","&RightDownVectorBar;","&NotSquareSupersetEqual;", //51
"&LeftUpVectorBar;","&GreaterEqualLess;","&DownArrow;", //54
"&NotTildeFullEqual;","@","&TildeFullEqual;", //57
"&NotLeftTriangle;","||","&DoubleUpArrow;", //60
"?","&DownLeftTeeVector;","&HorizontalLine;", //63
"&NotNestedLessLess;","&NotLessGreater;","&RightDownTeeVector;", //66
"&NotVerticalBar;","&Equal;","|", //69
"&LeftTeeVector;","&NotSucceedsTilde;","/=", //72
"&ReverseUpEquilibrium;","&Wedge;","&NotReverseElement;", //75
"&DoubleUpDownArrow;","&LongLeftRightArrow;","&Assign;", //78
"&LowerLeftArrow;","&PrecedesSlantEqual;","&UpperRightArrow;", //81
"&RightDownVector;","&LessFullEqual;","&NotEqualTilde;", //84
"&LessTilde;","!=",":=", //87
"&SquareIntersection;","&GreaterLess;","&DoubleLongLeftRightArrow;", //90
"&NotPrecedesSlantEqual;","&lt;=","=", //93
"&NotLeftTriangleEqual;","&lt;","&SucceedsTilde;", //96
"&NotSubsetEqual;","&Cross;","&LessGreater;", //99
"&RightArrow;","&DownRightTeeVector;","&LessEqualGreater;", //102
"&HumpDownHump;","&CircleTimes;","&NotEqual;", //105
"&EqualTilde;","&ReverseElement;","&NotHumpEqual;", //108
"_","&Coproduct;","&VerticalTilde;", //111
"&LessSlantEqual;","&ShortUpArrow;","-", //114
"&LeftArrowRightArrow;","&Union;","&DownLeftVector;", //117
"&NotSubset;","&ReverseEquilibrium;","&amp;&amp;", //120
"&Star;","&DotEqual;","**", //123
"&SquareSubset;","&InvisibleComma;","&DownLeftRightVector;", //126
"&UpperLeftArrow;","&NotSquareSubsetEqual;","&GreaterTilde;", //129
"&amp;","&RoundImplies;","&LeftVectorBar;", //132
"&ShortRightArrow;","&NotLessFullEqual;","&LeftUpVector;", //135
"&NotGreaterLess;","&RightTeeArrow;","&UpArrowBar;", //138
"&NotGreater;","+","&NotPrecedesEqual;", //141
"&Backslash;","&NotSquareSubset;","&NotSuperset;", //144
"&NotTildeTilde;","&Therefore;","&NotSucceedsEqual;", //147
"&Proportional;","&CupCap;","^", //150
"&LeftUpTeeVector;","&Intersection;","&NotLessLess;", //153
"&LeftTeeArrow;","&NotDoubleVerticalBar;","&NotSquareSuperset;", //156
"&NotLessEqual;","&Colon;","&LeftArrow;", //159
"&LeftArrowBar;","&NotPrecedes;","&NotGreaterFullEqual;", //162
"&MinusPlus;","&Succeeds;","&RightArrowLeftArrow;", //165
"&LeftRightArrow;","&SucceedsEqual;","&NotHumpDownHump;", //168
"&LeftDownVectorBar;","&Cup;","&NotGreaterGreater;", //171
"&RightVectorBar;","&RightTriangleEqual;","&DoubleRightArrow;", //174
";","&LeftTriangle;","&SquareUnion;", //177
"&NotRightTriangleEqual;","&Implies;","&TildeTilde;", //180
"&SuchThat;","&RightTeeVector;","&ApplyFunction;", //183
"&SquareSupersetEqual;","*","&SquareSubsetEqual;", //186
"&SupersetEqual;","&DoubleVerticalBar;","&RightUpDownVector;", //189
"&CircleMinus;","&NotLessTilde;","&UpArrow;", //192
"&SucceedsSlantEqual;","&DownTeeArrow;","==", //195
"&VerticalLine;","&LeftVector;","&lt;>", //198
"&NotCupCap;","&Element;","&DownTee;", //201
"&VerticalSeparator;","&DoubleLongRightArrow;","&NotGreaterSlantEqual;", //204
"&GreaterEqual;","&NestedGreaterGreater;","&Tilde;", //207
"&DoubleDownArrow;","&InvisibleTimes;","&CirclePlus;", //210
"&NotElement;","&DownLeftVectorBar;",",", //213
"&NestedLessLess;","&Subset;","&DoubleLeftRightArrow;", //216
"-=","&PrecedesTilde;","&DoubleLeftArrow;", //219
".","&Diamond;","&NotRightTriangle;", //222
"&NotLess;","&LeftTriangleBar;","&RightVector;", //225
"&Congruent;","&RightTriangleBar;","&Equilibrium;", //228
"~","&LongRightArrow;","&SquareSuperset;", //231
"&Because;","&RightArrowBar;","&LongLeftArrow;", //234
"&UpDownArrow;","&RightTriangle;",">", //237
"&Or;","&ShortLeftArrow;","&LeftDownVector;", //240
"&LeftDownTeeVector;","&PrecedesEqual;","&UpTee;", //243
"&UpArrowDownArrow;","&UpEquilibrium;","&NotSucceedsSlantEqual;", //246
"&RightTee;","&NotRightTriangleBar;","+=", //249
"&CenterDot;","&NotSucceeds;"};
const MMLAttribute *const MMLmoDict::in[254][5] = {
{&a1_1, 0, &a1_1, 0, &a0_0, },//0
{&a1_3, 0, &a1_3, 0, 0, },//1
{&a1_3, 0, &a1_3, 0, 0, },//2
{&a1_3, 0, &a1_3, 0, 0, },//3
{&a1_3, 0, &a1_3, 0, &a0_0, },//4
{&a1_3, 0, &a1_3, 0, 0, },//5
{&a1_1, 0, &a1_1, 0, 0, },//6
{&a1_0, 0, &a1_0, 0, 0, },//7
{&a1_3, 0, &a1_3, 0, 0, },//8
{&a1_3, 0, &a1_3, 0, 0, },//9
{&a1_1, 0, &a1_1, 0, &a0_0, },//10
{&a1_3, 0, &a1_3, 0, 0, },//11
{&a1_3, 0, &a1_3, 0, 0, },//12
{&a1_3, 0, &a1_3, 0, 0, },//13
{&a1_1, 0, &a1_1, 0, &a0_0, },//14
{&a1_1, 0, &a1_1, 0, &a0_0, },//15
{&a1_3, 0, &a1_3, 0, 0, },//16
{&a1_3, 0, &a1_3, 0, 0, },//17
{&a1_3, 0, &a1_3, 0, 0, },//18
{&a1_3, 0, &a1_3, 0, 0, },//19
{&a1_3, 0, &a1_3, 0, 0, },//20
{&a1_3, 0, &a1_3, 0, 0, },//21
{&a1_6, 0, &a1_6, 0, 0, },//22
{&a1_3, 0, &a1_3, 0, 0, },//23
{&a1_3, 0, &a1_3, 0, &a0_0, },//24
{&a1_3, 0, &a1_3, 0, 0, },//25
{&a1_3, 0, &a1_3, 0, 0, },//26
{&a1_3, 0, &a1_3, 0, &a0_0, },//27
{&a1_3, 0, &a1_3, 0, 0, },//28
{&a1_3, 0, &a1_3, 0, 0, },//29
{&a1_3, 0, &a1_3, 0, 0, },//30
{&a1_0, 0, &a1_0, 0, 0, },//31
{&a1_3, 0, &a1_3, 0, 0, },//32
{&a1_0, 0, &a1_0, 0, &a0_0, },//33
{&a1_3, 0, &a1_3, 0, 0, },//34
{&a1_1, 0, &a1_1, 0, 0, },//35
{&a1_1, 0, &a1_1, 0, 0, },//36
{&a1_3, 0, &a1_3, 0, 0, },//37
{&a1_3, 0, &a1_3, 0, &a0_0, },//38
{&a1_3, 0, &a1_3, 0, 0, },//39
{&a1_6, 0, &a1_6, 0, &a0_0, },//40
{&a1_3, 0, &a1_3, 0, 0, },//41
{&a1_3, 0, &a1_3, 0, 0, },//42
{&a1_3, 0, &a1_3, 0, 0, },//43
{&a1_6, 0, &a1_6, 0, &a0_0, },//44
{&a1_1, 0, &a1_1, 0, &a0_0, },//45
{&a1_3, 0, &a1_3, 0, 0, },//46
{&a1_3, 0, &a1_3, 0, 0, },//47
{&a1_1, 0, &a1_1, 0, &a0_0, },//48
{&a1_1, 0, &a1_1, 0, &a0_0, },//49
{&a1_1, 0, &a1_1, 0, &a0_0, },//50
{&a1_3, 0, &a1_3, 0, 0, },//51
{&a1_1, 0, &a1_1, 0, &a0_0, },//52
{&a1_3, 0, &a1_3, 0, 0, },//53
{&a1_1, 0, &a1_1, 0, &a0_0, },//54
{&a1_3, 0, &a1_3, 0, 0, },//55
{&a1_1, 0, &a1_1, 0, &a0_0, },//56
{&a1_3, 0, &a1_3, 0, 0, },//57
{&a1_1, 0, &a1_1, 0, 0, },//58
{&a1_3, 0, &a1_3, 0, 0, },//59
{&a1_3, 0, &a1_3, 0, 0, },//60
{&a1_6, 0, &a1_6, 0, 0, },//61
{&a1_1, 0, &a1_1, 0, &a0_0, },//62
{&a1_1, 0, &a1_1, 0, 0, },//63
{&a1_3, 0, &a1_3, 0, &a0_0, },//64
{&a1_5, &a1_4, &a1_5, 0, &a0_0, },//65
{&a1_3, 0, &a1_3, 0, 0, },//66
{&a1_3, 0, &a1_3, 0, 0, },//67
{&a1_1, 0, &a1_1, 0, &a0_0, },//68
{&a1_3, 0, &a1_3, 0, 0, },//69
{&a1_3, 0, &a1_3, 0, 0, },//70
{&a1_3, 0, &a1_3, 0, &a0_0, },//71
{&a1_3, 0, &a1_3, 0, &a0_0, },//72
{&a1_3, 0, &a1_3, 0, 0, },//73
{&a1_3, 0, &a1_3, 0, 0, },//74
{&a1_1, 0, &a1_1, 0, &a0_0, },//75
{&a1_0, 0, &a1_0, 0, 0, },//76
{&a1_3, 0, &a1_3, 0, 0, },//77
{&a1_1, 0, &a1_1, 0, &a0_0, },//78
{&a1_1, 0, &a1_1, 0, &a0_0, },//79
{&a1_3, 0, &a1_3, 0, 0, },//80
{&a1_3, 0, &a1_3, 0, &a0_0, },//81
{&a1_3, 0, &a1_3, 0, 0, },//82
{&a1_3, 0, &a1_3, 0, &a0_0, },//83
{&a1_1, 0, &a1_1, 0, &a0_0, },//84
{&a1_3, 0, &a1_3, 0, 0, },//85
{&a1_3, 0, &a1_3, 0, 0, },//86
{&a1_3, 0, &a1_3, 0, 0, },//87
{&a1_3, 0, &a1_3, 0, 0, },//88
{&a1_3, 0, &a1_3, 0, 0, },//89
{&a1_6, 0, &a1_6, 0, &a0_0, },//90
{&a1_3, 0, &a1_3, 0, 0, },//91
{&a1_1, 0, &a1_1, 0, &a0_0, },//92
{&a1_3, 0, &a1_3, 0, 0, },//93
{&a1_3, 0, &a1_3, 0, 0, },//94
{&a1_3, 0, &a1_3, 0, 0, },//95
{&a1_3, 0, &a1_3, 0, 0, },//96
{&a1_3, 0, &a1_3, 0, 0, },//97
{&a1_3, 0, &a1_3, 0, 0, },//98
{&a1_3, 0, &a1_3, 0, 0, },//99
{&a1_1, 0, &a1_1, 0, 0, },//100
{&a1_3, 0, &a1_3, 0, 0, },//101
{&a1_3, 0, &a1_3, 0, &a0_0, },//102
{&a1_3, 0, &a1_3, 0, &a0_0, },//103
{&a1_3, 0, &a1_3, 0, 0, },//104
{&a1_3, 0, &a1_3, 0, 0, },//105
{&a1_0, 0, &a1_0, 0, 0, },//106
{&a1_3, 0, &a1_3, 0, 0, },//107
{&a1_3, 0, &a1_3, 0, 0, },//108
{&a1_3, 0, &a1_3, 0, 0, },//109
{&a1_3, 0, &a1_3, 0, 0, },//110
{&a1_1, 0, &a1_1, 0, 0, },//111
{&a1_0, 0, &a1_0, 0, 0, },//112
{&a1_0, 0, &a1_0, 0, 0, },//113
{&a1_3, 0, &a1_3, 0, 0, },//114
{&a1_1, 0, &a1_1, 0, 0, },//115
{&a1_6, 0, &a1_6, 0, 0, },//116
{&a1_3, 0, &a1_3, 0, &a0_0, },//117
{&a1_6, 0, &a1_6, 0, &a0_0, },//118
{&a1_3, 0, &a1_3, 0, &a0_0, },//119
{&a1_3, 0, &a1_3, 0, 0, },//120
{&a1_3, 0, &a1_3, 0, &a0_0, },//121
{&a1_3, 0, &a1_3, 0, 0, },//122
{&a1_0, 0, &a1_0, 0, 0, },//123
{&a1_3, 0, &a1_3, 0, 0, },//124
{&a1_1, 0, &a1_1, 0, 0, },//125
{&a1_3, 0, &a1_3, 0, 0, },//126
{&a1_5, 0, &a1_5, &a0_0, 0, },//127
{&a1_3, 0, &a1_3, 0, &a0_0, },//128
{&a1_3, 0, &a1_3, 0, &a0_0, },//129
{&a1_3, 0, &a1_3, 0, 0, },//130
{&a1_3, 0, &a1_3, 0, 0, },//131
{&a1_3, 0, &a1_3, 0, 0, },//132
{&a1_3, 0, &a1_3, 0, 0, },//133
{&a1_3, 0, &a1_3, 0, &a0_0, },//134
{&a1_3, 0, &a1_3, 0, 0, },//135
{&a1_3, 0, &a1_3, 0, 0, },//136
{&a1_1, 0, &a1_1, 0, &a0_0, },//137
{&a1_3, 0, &a1_3, 0, 0, },//138
{&a1_3, 0, &a1_3, 0, &a0_0, },//139
{&a1_1, 0, &a1_1, 0, &a0_0, },//140
{&a1_3, 0, &a1_3, 0, 0, },//141
{&a1_6, 0, &a1_6, 0, 0, },//142
{&a1_3, 0, &a1_3, 0, 0, },//143
{&a1_0, 0, &a1_0, 0, &a0_0, },//144
{&a1_3, 0, &a1_3, 0, 0, },//145
{&a1_3, 0, &a1_3, 0, 0, },//146
{&a1_3, 0, &a1_3, 0, 0, },//147
{&a1_3, 0, &a1_3, 0, 0, },//148
{&a1_3, 0, &a1_3, 0, 0, },//149
{&a1_3, 0, &a1_3, 0, 0, },//150
{&a1_3, 0, &a1_3, 0, 0, },//151
{&a1_1, 0, &a1_1, 0, 0, },//152
{&a1_1, 0, &a1_1, 0, &a0_0, },//153
{&a1_6, 0, &a1_6, 0, &a0_0, },//154
{&a1_3, 0, &a1_3, 0, 0, },//155
{&a1_3, 0, &a1_3, 0, &a0_0, },//156
{&a1_3, 0, &a1_3, 0, 0, },//157
{&a1_3, 0, &a1_3, 0, 0, },//158
{&a1_3, 0, &a1_3, 0, 0, },//159
{&a1_3, 0, &a1_3, 0, 0, },//160
{&a1_3, 0, &a1_3, 0, &a0_0, },//161
{&a1_3, 0, &a1_3, 0, &a0_0, },//162
{&a1_3, 0, &a1_3, 0, 0, },//163
{&a1_3, 0, &a1_3, 0, 0, },//164
{&a1_6, 0, &a1_6, 0, 0, },//165
{&a1_3, 0, &a1_3, 0, 0, },//166
{&a1_3, 0, &a1_3, 0, &a0_0, },//167
{&a1_3, 0, &a1_3, 0, &a0_0, },//168
{&a1_3, 0, &a1_3, 0, 0, },//169
{&a1_3, 0, &a1_3, 0, 0, },//170
{&a1_1, 0, &a1_1, 0, &a0_0, },//171
{&a1_0, 0, &a1_0, 0, 0, },//172
{&a1_3, 0, &a1_3, 0, 0, },//173
{&a1_3, 0, &a1_3, 0, &a0_0, },//174
{&a1_3, 0, &a1_3, 0, 0, },//175
{&a1_3, 0, &a1_3, 0, &a0_0, },//176
{&a1_5, 0, &a1_3, &a0_0, 0, },//177
{&a1_3, 0, &a1_3, 0, 0, },//178
{&a1_6, 0, &a1_6, 0, &a0_0, },//179
{&a1_3, 0, &a1_3, 0, 0, },//180
{&a1_3, 0, &a1_3, 0, &a0_0, },//181
{&a1_3, 0, &a1_3, 0, 0, },//182
{&a1_3, 0, &a1_3, 0, 0, },//183
{&a1_3, 0, &a1_3, 0, &a0_0, },//184
{&a1_5, 0, &a1_5, 0, 0, },//185
{&a1_3, 0, &a1_3, 0, 0, },//186
{&a1_0, 0, &a1_0, 0, 0, },//187
{&a1_3, 0, &a1_3, 0, 0, },//188
{&a1_3, 0, &a1_3, 0, 0, },//189
{&a1_3, 0, &a1_3, 0, 0, },//190
{&a1_1, 0, &a1_1, 0, &a0_0, },//191
{&a1_0, 0, &a1_0, 0, 0, },//192
{&a1_3, 0, &a1_3, 0, 0, },//193
{&a1_1, 0, &a1_1, 0, &a0_0, },//194
{&a1_3, 0, &a1_3, 0, 0, },//195
{&a1_1, 0, &a1_1, 0, &a0_0, },//196
{&a1_3, 0, &a1_3, 0, 0, },//197
{&a1_5, &a1_4, &a1_5, 0, &a0_0, },//198
{&a1_3, 0, &a1_3, 0, &a0_0, },//199
{&a1_1, 0, &a1_1, 0, 0, },//200
{&a1_3, 0, &a1_3, 0, 0, },//201
{&a1_3, 0, &a1_3, 0, 0, },//202
{&a1_3, 0, &a1_3, 0, 0, },//203
{&a1_3, 0, &a1_3, 0, &a0_0, },//204
{&a1_1, 0, &a1_1, 0, &a0_0, },//205
{&a1_3, 0, &a1_3, 0, 0, },//206
{&a1_3, 0, &a1_3, 0, 0, },//207
{&a1_3, 0, &a1_3, 0, 0, },//208
{&a1_3, 0, &a1_3, 0, 0, },//209
{&a1_1, 0, &a1_1, 0, &a0_0, },//210
{&a1_5, 0, &a1_5, 0, 0, },//211
{&a1_0, 0, &a1_0, 0, 0, },//212
{&a1_3, 0, &a1_3, 0, 0, },//213
{&a1_3, 0, &a1_3, 0, &a0_0, },//214
{&a1_5, 0, &a1_7, &a0_0, 0, },//215
{&a1_3, 0, &a1_3, 0, 0, },//216
{&a1_3, 0, &a1_3, 0, 0, },//217
{&a1_3, 0, &a1_3, 0, &a0_0, },//218
{&a1_3, 0, &a1_3, 0, 0, },//219
{&a1_3, 0, &a1_3, 0, 0, },//220
{&a1_3, 0, &a1_3, 0, &a0_0, },//221
{&a1_5, 0, &a1_5, 0, 0, },//222
{&a1_0, 0, &a1_0, 0, 0, },//223
{&a1_3, 0, &a1_3, 0, 0, },//224
{&a1_3, 0, &a1_3, 0, 0, },//225
{&a1_3, 0, &a1_3, 0, 0, },//226
{&a1_3, 0, &a1_3, 0, &a0_0, },//227
{&a1_3, 0, &a1_3, 0, 0, },//228
{&a1_3, 0, &a1_3, 0, 0, },//229
{&a1_3, 0, &a1_3, 0, &a0_0, },//230
{&a1_1, 0, &a1_1, 0, 0, },//231
{&a1_1, 0, &a1_1, 0, &a0_0, },//232
{&a1_3, 0, &a1_3, 0, 0, },//233
{&a1_3, 0, &a1_3, 0, 0, },//234
{&a1_3, 0, &a1_3, 0, &a0_0, },//235
{&a1_1, 0, &a1_1, 0, &a0_0, },//236
{&a1_1, 0, &a1_1, 0, &a0_0, },//237
{&a1_3, 0, &a1_3, 0, 0, },//238
{&a1_3, 0, &a1_3, 0, 0, },//239
{&a1_6, 0, &a1_6, 0, &a0_0, },//240
{&a1_3, 0, &a1_3, 0, 0, },//241
{&a1_1, 0, &a1_1, 0, &a0_0, },//242
{&a1_1, 0, &a1_1, 0, &a0_0, },//243
{&a1_3, 0, &a1_3, 0, 0, },//244
{&a1_3, 0, &a1_3, 0, 0, },//245
{&a1_1, 0, &a1_1, 0, &a0_0, },//246
{&a1_1, 0, &a1_1, 0, &a0_0, },//247
{&a1_3, 0, &a1_3, 0, 0, },//248
{&a1_3, 0, &a1_3, 0, 0, },//249
{&a1_3, 0, &a1_3, 0, 0, },//250
{&a1_3, 0, &a1_3, 0, 0, },//251
{&a1_0, 0, &a1_0, 0, 0, },//252
{&a1_3, 0, &a1_3, 0, 0, }
};
const short MMLmoDict::postpos[6] = {
moACCENT, moFENCE, moLSPACE, moRSPACE, moSEPARATOR, moSTRETCHY, 
};
const char *MMLmoDict::postsyms[47] = {
"&OverBracket;","'","&RightCeiling;", //0
"&amp;","&DiacriticalGrave;","!", //3
"&DiacriticalDot;","&UnderParenthesis;","]", //6
"&UnderBrace;","&DoubleDot;","&DiacriticalAcute;", //9
"&DiacriticalDoubleAcute;","&OverBar;","&RightFloor;", //12
"&DiacriticalTilde;","&RightSkeleton;","..", //15
"&Breve;","&DownBreve;","&Hacek;", //18
"...","&DiacriticalLeftRightVector;","&UnderBracket;", //21
"}","&UnderBar;","&RightDoubleBracket;", //24
"&DiacriticalLeftArrow;","&DiacriticalRightArrow;","&Cedilla;", //27
"&DiacriticalRightVector;","&OverBrace;","++", //30
"&CloseCurlyQuote;","&CloseCurlyDoubleQuote;","&DiacriticalLeftRightArrow;", //33
"--",")","&DiacriticalLeftVector;", //36
"&OverParenthesis;",";","&RightBracketingBar;", //39
"&Hat;","&TripleDot;","&RightDoubleBracketingBar;", //42
"!!","&RightAngleBracket;"};
const MMLAttribute *const MMLmoDict::post[47][6] = {
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//0
{0, 0, &a1_1, &a1_5, 0, 0, },//1
{0, &a0_0, &a1_5, &a1_5, 0, &a0_0, },//2
{0, 0, &a1_3, &a1_5, 0, 0, },//3
{&a0_0, 0, &a1_5, &a1_5, 0, 0, },//4
{0, 0, &a1_1, &a1_5, 0, 0, },//5
{&a0_0, 0, &a1_5, &a1_5, 0, 0, },//6
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//7
{0, &a0_0, &a1_5, &a1_5, 0, &a0_0, },//8
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//9
{&a0_0, 0, &a1_5, &a1_5, 0, 0, },//10
{&a0_0, 0, &a1_5, &a1_5, 0, 0, },//11
{&a0_0, 0, &a1_5, &a1_5, 0, 0, },//12
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//13
{0, &a0_0, &a1_5, &a1_5, 0, &a0_0, },//14
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//15
{0, &a0_0, &a1_5, &a1_5, 0, 0, },//16
{0, 0, &a1_6, &a1_5, 0, 0, },//17
{&a0_0, 0, &a1_5, &a1_5, 0, 0, },//18
{&a0_0, 0, &a1_5, &a1_5, 0, 0, },//19
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//20
{0, 0, &a1_6, &a1_5, 0, 0, },//21
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//22
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//23
{0, &a0_0, &a1_5, &a1_5, 0, &a0_0, },//24
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//25
{0, &a0_0, &a1_5, &a1_5, 0, &a0_0, },//26
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//27
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//28
{&a0_0, 0, &a1_5, &a1_5, 0, 0, },//29
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//30
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//31
{0, 0, &a1_1, &a1_5, 0, 0, },//32
{0, &a0_0, &a1_5, &a1_5, 0, 0, },//33
{0, &a0_0, &a1_5, &a1_5, 0, 0, },//34
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//35
{0, 0, &a1_1, &a1_5, 0, 0, },//36
{0, &a0_0, &a1_5, &a1_5, 0, &a0_0, },//37
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//38
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//39
{0, 0, &a1_5, &a1_5, &a0_0, 0, },//40
{0, &a0_0, &a1_5, &a1_5, 0, &a0_0, },//41
{&a0_0, 0, &a1_5, &a1_5, 0, &a0_0, },//42
{&a0_0, 0, &a1_5, &a1_5, 0, 0, },//43
{0, &a0_0, &a1_5, &a1_5, 0, &a0_0, },//44
{0, 0, &a1_1, &a1_5, 0, 0, },//45
{0, &a0_0, &a1_5, &a1_5, 0, &a0_0, }
};
