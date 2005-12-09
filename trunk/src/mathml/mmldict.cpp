#include "mmldict.h"
using std::map;
#include "mmlmo.h"
using std::pair;

bool MMLDict::done = false;
ushort
MMLDict::resolveEntity(DOMString s) {
	if (!done) {
		makeEntDict();
	}
	map<DOMString, ushort>::const_iterator i;
	i = ent.find(s);
	if (i == ent.end()) {
		return 0;
	}
	return i->second;
}
const char *MMLmo::rawopdict[351] = {
"( form=prefix fence=true stretchy=true lspace=0em rspace=0em",
") form=postfix fence=true stretchy=true lspace=0em rspace=0em",
"[ form=prefix fence=true stretchy=true lspace=0em rspace=0em",
"] form=postfix fence=true stretchy=true lspace=0em rspace=0em",
"{ form=prefix fence=true stretchy=true lspace=0em rspace=0em",
"} form=postfix fence=true stretchy=true lspace=0em rspace=0em",

"&CloseCurlyDoubleQuote; form=postfix fence=true lspace=0em rspace=0em",
"&CloseCurlyQuote; form=postfix fence=true lspace=0em rspace=0em",
"&LeftAngleBracket; form=prefix fence=true stretchy=true lspace=0em rspace=0em",
"&LeftBracketingBar; form=prefix fence=true stretchy=true lspace=0em rspace=0em",
"&LeftCeiling; form=prefix fence=true stretchy=true lspace=0em rspace=0em",
"&LeftDoubleBracket; form=prefix fence=true stretchy=true lspace=0em rspace=0em",
"&LeftDoubleBracketingBar; form=prefix fence=true stretchy=true lspace=0em rspace=0em",
"&LeftFloor; form=prefix fence=true stretchy=true lspace=0em rspace=0em",
"&OpenCurlyDoubleQuote; form=prefix fence=true lspace=0em rspace=0em",
"&OpenCurlyQuote; form=prefix fence=true lspace=0em rspace=0em",
"&RightAngleBracket; form=postfix fence=true stretchy=true lspace=0em rspace=0em",
"&RightBracketingBar; form=postfix fence=true stretchy=true lspace=0em rspace=0em",
"&RightCeiling; form=postfix fence=true stretchy=true lspace=0em rspace=0em",
"&RightDoubleBracket; form=postfix fence=true stretchy=true lspace=0em rspace=0em",
"&RightDoubleBracketingBar; form=postfix fence=true stretchy=true lspace=0em rspace=0em",
"&RightFloor; form=postfix fence=true stretchy=true lspace=0em rspace=0em",
"&LeftSkeleton; form=prefix fence=true lspace=0em rspace=0em",
"&RightSkeleton; form=postfix fence=true lspace=0em rspace=0em",

"&InvisibleComma; form=infix separator=true lspace=0em rspace=0em",

", form=infix separator=true lspace=0em rspace=verythickmathspace",

"&HorizontalLine; form=infix stretchy=true minsize=0 lspace=0em rspace=0em",
"&VerticalLine; form=infix stretchy=true minsize=0 lspace=0em rspace=0em",

"; form=infix separator=true lspace=0em rspace=thickmathspace",
"; form=postfix separator=true lspace=0em rspace=0em",

":= form=infix lspace=thickmathspace rspace=thickmathspace",
"&Assign; form=infix lspace=thickmathspace rspace=thickmathspace",

"&Because; form=infix lspace=thickmathspace rspace=thickmathspace",
"&Therefore; form=infix lspace=thickmathspace rspace=thickmathspace",

"&VerticalSeparator; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",

"// form=infix lspace=thickmathspace rspace=thickmathspace",

"&Colon; form=infix lspace=thickmathspace rspace=thickmathspace",

"&amp; form=prefix lspace=0em rspace=thickmathspace",
"&amp; form=postfix lspace=thickmathspace rspace=0em",

"*= form=infix lspace=thickmathspace rspace=thickmathspace",
"-= form=infix lspace=thickmathspace rspace=thickmathspace",
"+= form=infix lspace=thickmathspace rspace=thickmathspace",
"/= form=infix lspace=thickmathspace rspace=thickmathspace",

"-> form=infix lspace=thickmathspace rspace=thickmathspace",

": form=infix lspace=thickmathspace rspace=thickmathspace",

".. form=postfix lspace=mediummathspace rspace=0em",
"... form=postfix lspace=mediummathspace rspace=0em",

"&SuchThat; form=infix lspace=thickmathspace rspace=thickmathspace",

"&DoubleLeftTee; form=infix lspace=thickmathspace rspace=thickmathspace",
"&DoubleRightTee; form=infix lspace=thickmathspace rspace=thickmathspace",
"&DownTee; form=infix lspace=thickmathspace rspace=thickmathspace",
"&LeftTee; form=infix lspace=thickmathspace rspace=thickmathspace",
"&RightTee; form=infix lspace=thickmathspace rspace=thickmathspace",

"&Implies; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&RoundImplies; form=infix lspace=thickmathspace rspace=thickmathspace",

"| form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"|| form=infix lspace=mediummathspace rspace=mediummathspace",
"&Or; form=infix stretchy=true lspace=mediummathspace rspace=mediummathspace",

"&amp;&amp; form=infix lspace=thickmathspace rspace=thickmathspace",
"&And; form=infix stretchy=true lspace=mediummathspace rspace=mediummathspace",

"&amp; form=infix lspace=thickmathspace rspace=thickmathspace",

"! form=prefix lspace=0em rspace=thickmathspace",
"&Not; form=prefix lspace=0em rspace=thickmathspace",

"&Exists; form=prefix lspace=0em rspace=thickmathspace",
"&ForAll; form=prefix lspace=0em rspace=thickmathspace",
"&NotExists; form=prefix lspace=0em rspace=thickmathspace",

"&Element; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotElement; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotReverseElement; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSquareSubset; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSquareSubsetEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSquareSuperset; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSquareSupersetEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSubset; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSubsetEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSuperset; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSupersetEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&ReverseElement; form=infix lspace=thickmathspace rspace=thickmathspace",
"&SquareSubset; form=infix lspace=thickmathspace rspace=thickmathspace",
"&SquareSubsetEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&SquareSuperset; form=infix lspace=thickmathspace rspace=thickmathspace",
"&SquareSupersetEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&Subset; form=infix lspace=thickmathspace rspace=thickmathspace",
"&SubsetEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&Superset; form=infix lspace=thickmathspace rspace=thickmathspace",
"&SupersetEqual; form=infix lspace=thickmathspace rspace=thickmathspace",

"&DoubleLeftArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&DoubleLeftRightArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&DoubleRightArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&DownLeftRightVector; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&DownLeftTeeVector; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&DownLeftVector; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&DownLeftVectorBar; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&DownRightTeeVector; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&DownRightVector; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&DownRightVectorBar; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LeftArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LeftArrowBar; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LeftArrowRightArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LeftRightArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LeftRightVector; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LeftTeeArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LeftTeeVector; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LeftVector; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LeftVectorBar; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LowerLeftArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&LowerRightArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&RightArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&RightArrowBar; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&RightArrowLeftArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&RightTeeArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&RightTeeVector; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&RightVector; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&RightVectorBar; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&ShortLeftArrow; form=infix lspace=thickmathspace rspace=thickmathspace",
"&ShortRightArrow; form=infix lspace=thickmathspace rspace=thickmathspace",
"&UpperLeftArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&UpperRightArrow; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",

"= form=infix lspace=thickmathspace rspace=thickmathspace",
"&lt; form=infix lspace=thickmathspace rspace=thickmathspace",
"> form=infix lspace=thickmathspace rspace=thickmathspace",
"!= form=infix lspace=thickmathspace rspace=thickmathspace",
"== form=infix lspace=thickmathspace rspace=thickmathspace",
"&lt;= form=infix lspace=thickmathspace rspace=thickmathspace",
">= form=infix lspace=thickmathspace rspace=thickmathspace",
"&Congruent; form=infix lspace=thickmathspace rspace=thickmathspace",
"&CupCap; form=infix lspace=thickmathspace rspace=thickmathspace",
"&DotEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&DoubleVerticalBar; form=infix lspace=thickmathspace rspace=thickmathspace",
"&Equal; form=infix lspace=thickmathspace rspace=thickmathspace",
"&EqualTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&Equilibrium; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&GreaterEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&GreaterEqualLess; form=infix lspace=thickmathspace rspace=thickmathspace",
"&GreaterFullEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&GreaterGreater; form=infix lspace=thickmathspace rspace=thickmathspace",
"&GreaterLess; form=infix lspace=thickmathspace rspace=thickmathspace",
"&GreaterSlantEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&GreaterTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&HumpDownHump; form=infix lspace=thickmathspace rspace=thickmathspace",
"&HumpEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&LeftTriangle; form=infix lspace=thickmathspace rspace=thickmathspace",
"&LeftTriangleBar; form=infix lspace=thickmathspace rspace=thickmathspace",
"&LeftTriangleEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&le; form=infix lspace=thickmathspace rspace=thickmathspace",
"&LessEqualGreater; form=infix lspace=thickmathspace rspace=thickmathspace",
"&LessFullEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&LessGreater; form=infix lspace=thickmathspace rspace=thickmathspace",
"&LessLess; form=infix lspace=thickmathspace rspace=thickmathspace",
"&LessSlantEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&LessTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NestedGreaterGreater; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NestedLessLess; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotCongruent; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotCupCap; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotDoubleVerticalBar; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotEqualTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotGreater; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotGreaterEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotGreaterFullEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotGreaterGreater; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotGreaterLess; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotGreaterSlantEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotGreaterTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotHumpDownHump; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotHumpEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotLeftTriangle; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotLeftTriangleBar; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotLeftTriangleEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotLess; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotLessEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotLessFullEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotLessGreater; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotLessLess; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotLessSlantEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotLessTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotNestedGreaterGreater; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotNestedLessLess; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotPrecedes; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotPrecedesEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotPrecedesSlantEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotPrecedesTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotRightTriangle; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotRightTriangleBar; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotRightTriangleEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSucceeds; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSucceedsEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSucceedsSlantEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotSucceedsTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotTildeEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotTildeFullEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotTildeTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&NotVerticalBar; form=infix lspace=thickmathspace rspace=thickmathspace",
"&Precedes; form=infix lspace=thickmathspace rspace=thickmathspace",
"&PrecedesEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&PrecedesSlantEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&PrecedesTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&Proportion; form=infix lspace=thickmathspace rspace=thickmathspace",
"&Proportional; form=infix lspace=thickmathspace rspace=thickmathspace",
"&ReverseEquilibrium; form=infix stretchy=true lspace=thickmathspace rspace=thickmathspace",
"&RightTriangle; form=infix lspace=thickmathspace rspace=thickmathspace",
"&RightTriangleBar; form=infix lspace=thickmathspace rspace=thickmathspace",
"&RightTriangleEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&Succeeds; form=infix lspace=thickmathspace rspace=thickmathspace",
"&SucceedsEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&SucceedsSlantEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&SucceedsTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&Tilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&TildeEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&TildeFullEqual; form=infix lspace=thickmathspace rspace=thickmathspace",
"&TildeTilde; form=infix lspace=thickmathspace rspace=thickmathspace",
"&UpTee; form=infix lspace=thickmathspace rspace=thickmathspace",
"&VerticalBar; form=infix lspace=thickmathspace rspace=thickmathspace",

"&SquareUnion; form=infix stretchy=true lspace=mediummathspace rspace=mediummathspace",
"&Union; form=infix stretchy=true lspace=mediummathspace rspace=mediummathspace",
"&UnionPlus; form=infix stretchy=true lspace=mediummathspace rspace=mediummathspace",

"- form=infix lspace=mediummathspace rspace=mediummathspace",
"+ form=infix lspace=mediummathspace rspace=mediummathspace",
"&Intersection; form=infix stretchy=true lspace=mediummathspace rspace=mediummathspace",
"&MinusPlus; form=infix lspace=mediummathspace rspace=mediummathspace",
"&PlusMinus; form=infix lspace=mediummathspace rspace=mediummathspace",
"&SquareIntersection; form=infix stretchy=true lspace=mediummathspace rspace=mediummathspace",

"&Vee; form=prefix largeop=true movablelimits=true stretchy=true lspace=0em rspace=thinmathspace",
"&CircleMinus; form=prefix largeop=true movablelimits=true lspace=0em rspace=thinmathspace",
"&CirclePlus; form=prefix largeop=true movablelimits=true lspace=0em rspace=thinmathspace",
"&Sum; form=prefix largeop=true movablelimits=true stretchy=true lspace=0em rspace=thinmathspace",
"&Union; form=prefix largeop=true movablelimits=true stretchy=true lspace=0em rspace=thinmathspace",
"&UnionPlus; form=prefix largeop=true movablelimits=true stretchy=true lspace=0em rspace=thinmathspace",
"lim form=prefix movablelimits=true lspace=0em rspace=thinmathspace",
"max form=prefix movablelimits=true lspace=0em rspace=thinmathspace",
"min form=prefix movablelimits=true lspace=0em rspace=thinmathspace",

"&CircleMinus; form=infix lspace=thinmathspace rspace=thinmathspace",
"&CirclePlus; form=infix lspace=thinmathspace rspace=thinmathspace",

"&ClockwiseContourIntegral; form=prefix largeop=true stretchy=true lspace=0em rspace=0em",
"&ContourIntegral; form=prefix largeop=true stretchy=true lspace=0em rspace=0em",
"&CounterClockwiseContourIntegral; form=prefix largeop=true stretchy=true lspace=0em rspace=0em",
"&DoubleContourIntegral; form=prefix largeop=true stretchy=true lspace=0em rspace=0em",
"&Integral; form=prefix largeop=true stretchy=true lspace=0em rspace=0em",

"&Cup; form=infix lspace=thinmathspace rspace=thinmathspace",

"&Cap; form=infix lspace=thinmathspace rspace=thinmathspace",

"&VerticalTilde; form=infix lspace=thinmathspace rspace=thinmathspace",

"&Wedge; form=prefix largeop=true movablelimits=true stretchy=true lspace=0em rspace=thinmathspace",
"&CircleTimes; form=prefix largeop=true movablelimits=true lspace=0em rspace=thinmathspace",
"&Coproduct; form=prefix largeop=true movablelimits=true stretchy=true lspace=0em rspace=thinmathspace",
"&Product; form=prefix largeop=true movablelimits=true stretchy=true lspace=0em rspace=thinmathspace",
"&Intersection; form=prefix largeop=true movablelimits=true stretchy=true lspace=0em rspace=thinmathspace",

"&Coproduct; form=infix lspace=thinmathspace rspace=thinmathspace",

"&Star; form=infix lspace=thinmathspace rspace=thinmathspace",

"&CircleDot; form=prefix largeop=true movablelimits=true lspace=0em rspace=thinmathspace",

"* form=infix lspace=thinmathspace rspace=thinmathspace",
"&InvisibleTimes; form=infix lspace=0em rspace=0em",

"&CenterDot; form=infix lspace=thinmathspace rspace=thinmathspace",

"&CircleTimes; form=infix lspace=thinmathspace rspace=thinmathspace",

"&Vee; form=infix lspace=thinmathspace rspace=thinmathspace",

"&Wedge; form=infix lspace=thinmathspace rspace=thinmathspace",

"&Diamond; form=infix lspace=thinmathspace rspace=thinmathspace",

"&Backslash; form=infix stretchy=true lspace=thinmathspace rspace=thinmathspace",

"/ form=infix stretchy=true lspace=thinmathspace rspace=thinmathspace",

"- form=prefix lspace=0em rspace=veryverythinmathspace",
"+ form=prefix lspace=0em rspace=veryverythinmathspace",
"&MinusPlus; form=prefix lspace=0em rspace=veryverythinmathspace",
"&PlusMinus; form=prefix lspace=0em rspace=veryverythinmathspace",

". form=infix lspace=0em rspace=0em",

"&Cross; form=infix lspace=verythinmathspace rspace=verythinmathspace",

"** form=infix lspace=verythinmathspace rspace=verythinmathspace",

"&CircleDot; form=infix lspace=verythinmathspace rspace=verythinmathspace",

"&SmallCircle; form=infix lspace=verythinmathspace rspace=verythinmathspace",

"&Square; form=prefix lspace=0em rspace=verythinmathspace",

"&Del; form=prefix lspace=0em rspace=verythinmathspace",
"&PartialD; form=prefix lspace=0em rspace=verythinmathspace",

"&CapitalDifferentialD; form=prefix lspace=0em rspace=verythinmathspace",
"&DifferentialD; form=prefix lspace=0em rspace=verythinmathspace",

"&Sqrt; form=prefix stretchy=true lspace=0em rspace=verythinmathspace",

"&DoubleDownArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&DoubleLongLeftArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&DoubleLongLeftRightArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&DoubleLongRightArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&DoubleUpArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&DoubleUpDownArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&DownArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&DownArrowBar; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&DownArrowUpArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&DownTeeArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&LeftDownTeeVector; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&LeftDownVector; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&LeftDownVectorBar; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&LeftUpDownVector; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&LeftUpTeeVector; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&LeftUpVector; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&LeftUpVectorBar; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&LongLeftArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&LongLeftRightArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&LongRightArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&ReverseUpEquilibrium; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&RightDownTeeVector; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&RightDownVector; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&RightDownVectorBar; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&RightUpDownVector; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&RightUpTeeVector; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&RightUpVector; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&RightUpVectorBar; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&ShortDownArrow; form=infix lspace=verythinmathspace rspace=verythinmathspace",
"&ShortUpArrow; form=infix lspace=verythinmathspace rspace=verythinmathspace",
"&UpArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&UpArrowBar; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&UpArrowDownArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&UpDownArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&UpEquilibrium; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",
"&UpTeeArrow; form=infix stretchy=true lspace=verythinmathspace rspace=verythinmathspace",

"^ form=infix lspace=verythinmathspace rspace=verythinmathspace",

"&lt;> form=infix lspace=verythinmathspace rspace=verythinmathspace",

"' form=postfix lspace=verythinmathspace rspace=0em",

"! form=postfix lspace=verythinmathspace rspace=0em",
"!! form=postfix lspace=verythinmathspace rspace=0em",

"~ form=infix lspace=verythinmathspace rspace=verythinmathspace",

"@ form=infix lspace=verythinmathspace rspace=verythinmathspace",

"-- form=postfix lspace=verythinmathspace rspace=0em",
"-- form=prefix lspace=0em rspace=verythinmathspace",
"++ form=postfix lspace=verythinmathspace rspace=0em",
"++ form=prefix lspace=0em rspace=verythinmathspace",

"&ApplyFunction; form=infix lspace=0em rspace=0em",

"? form=infix lspace=verythinmathspace rspace=verythinmathspace",

"_ form=infix lspace=verythinmathspace rspace=verythinmathspace",

"&Breve; form=postfix accent=true lspace=0em rspace=0em",
"&Cedilla; form=postfix accent=true lspace=0em rspace=0em",
"&DiacriticalGrave; form=postfix accent=true lspace=0em rspace=0em",
"&DiacriticalDot; form=postfix accent=true lspace=0em rspace=0em",
"&DiacriticalDoubleAcute; form=postfix accent=true lspace=0em rspace=0em",
"&DiacriticalLeftArrow; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&DiacriticalLeftRightArrow; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&DiacriticalLeftRightVector; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&DiacriticalLeftVector; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&DiacriticalAcute; form=postfix accent=true lspace=0em rspace=0em",
"&DiacriticalRightArrow; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&DiacriticalRightVector; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&DiacriticalTilde; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&DoubleDot; form=postfix accent=true lspace=0em rspace=0em",
"&DownBreve; form=postfix accent=true lspace=0em rspace=0em",
"&Hacek; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&Hat; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&OverBar; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&OverBrace; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&OverBracket; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&OverParenthesis; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&TripleDot; form=postfix accent=true lspace=0em rspace=0em",
"&UnderBar; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&UnderBrace; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&UnderBracket; form=postfix accent=true stretchy=true lspace=0em rspace=0em",
"&UnderParenthesis; form=postfix accent=true stretchy=true lspace=0em rspace=0em"};

map<DOMString, ushort> MMLDict::ent;

void
MMLDict::makeEntDict() {
	done = true;
	ent.insert(pair<DOMString, ushort>("angle", 0x02220));
	ent.insert(pair<DOMString, ushort>("ApplyFunction", 0x02061));
	ent.insert(pair<DOMString, ushort>("approx", 0x02248));
	ent.insert(pair<DOMString, ushort>("approxeq", 0x0224A));
	ent.insert(pair<DOMString, ushort>("Assign", 0x02254));
	ent.insert(pair<DOMString, ushort>("backcong", 0x0224C));
	ent.insert(pair<DOMString, ushort>("backepsilon", 0x003F6));
	ent.insert(pair<DOMString, ushort>("backprime", 0x02035));
	ent.insert(pair<DOMString, ushort>("backsim", 0x0223D));
	ent.insert(pair<DOMString, ushort>("backsimeq", 0x022CD));
	ent.insert(pair<DOMString, ushort>("Backslash", 0x02216));
	ent.insert(pair<DOMString, ushort>("barwedge", 0x022BC));
	ent.insert(pair<DOMString, ushort>("because", 0x02235));
	ent.insert(pair<DOMString, ushort>("Because", 0x02235));
	ent.insert(pair<DOMString, ushort>("Bernoullis", 0x0212C));
	ent.insert(pair<DOMString, ushort>("between", 0x0226C));
	ent.insert(pair<DOMString, ushort>("bigcap", 0x022C2));
	ent.insert(pair<DOMString, ushort>("bigcirc", 0x025EF));
	ent.insert(pair<DOMString, ushort>("bigcup", 0x022C3));
	ent.insert(pair<DOMString, ushort>("bigodot", 0x02299));
	ent.insert(pair<DOMString, ushort>("bigoplus", 0x02295));
	ent.insert(pair<DOMString, ushort>("bigotimes", 0x02297));
	ent.insert(pair<DOMString, ushort>("bigsqcup", 0x02294));
	ent.insert(pair<DOMString, ushort>("bigstar", 0x02605));
	ent.insert(pair<DOMString, ushort>("bigtriangledown", 0x025BD));
	ent.insert(pair<DOMString, ushort>("bigtriangleup", 0x025B3));
	ent.insert(pair<DOMString, ushort>("biguplus", 0x0228E));
	ent.insert(pair<DOMString, ushort>("bigvee", 0x022C1));
	ent.insert(pair<DOMString, ushort>("bigwedge", 0x022C0));
	ent.insert(pair<DOMString, ushort>("bkarow", 0x0290D));
	ent.insert(pair<DOMString, ushort>("blacklozenge", 0x029EB));
	ent.insert(pair<DOMString, ushort>("blacksquare", 0x025AA));
	ent.insert(pair<DOMString, ushort>("blacktriangle", 0x025B4));
	ent.insert(pair<DOMString, ushort>("blacktriangledown", 0x025BE));
	ent.insert(pair<DOMString, ushort>("blacktriangleleft", 0x025C2));
	ent.insert(pair<DOMString, ushort>("blacktriangleright", 0x025B8));
	ent.insert(pair<DOMString, ushort>("bot", 0x022A5));
	ent.insert(pair<DOMString, ushort>("boxminus", 0x0229F));
	ent.insert(pair<DOMString, ushort>("boxplus", 0x0229E));
	ent.insert(pair<DOMString, ushort>("boxtimes", 0x022A0));
	ent.insert(pair<DOMString, ushort>("Breve", 0x002D8));
	ent.insert(pair<DOMString, ushort>("bullet", 0x02022));
	ent.insert(pair<DOMString, ushort>("bumpeq", 0x0224F));
	ent.insert(pair<DOMString, ushort>("Bumpeq", 0x0224E));
	ent.insert(pair<DOMString, ushort>("CapitalDifferentialD", 0x02145));
	ent.insert(pair<DOMString, ushort>("Cayleys", 0x0212D));
	ent.insert(pair<DOMString, ushort>("Cedilla", 0x000B8));
	ent.insert(pair<DOMString, ushort>("centerdot", 0x000B7));
	ent.insert(pair<DOMString, ushort>("CenterDot", 0x000B7));
	ent.insert(pair<DOMString, ushort>("checkmark", 0x02713));
	ent.insert(pair<DOMString, ushort>("circeq", 0x02257));
	ent.insert(pair<DOMString, ushort>("circlearrowleft", 0x021BA));
	ent.insert(pair<DOMString, ushort>("circlearrowright", 0x021BB));
	ent.insert(pair<DOMString, ushort>("circledast", 0x0229B));
	ent.insert(pair<DOMString, ushort>("circledcirc", 0x0229A));
	ent.insert(pair<DOMString, ushort>("circleddash", 0x0229D));
	ent.insert(pair<DOMString, ushort>("CircleDot", 0x02299));
	ent.insert(pair<DOMString, ushort>("circledR", 0x000AE));
	ent.insert(pair<DOMString, ushort>("circledS", 0x024C8));
	ent.insert(pair<DOMString, ushort>("CircleMinus", 0x02296));
	ent.insert(pair<DOMString, ushort>("CirclePlus", 0x02295));
	ent.insert(pair<DOMString, ushort>("CircleTimes", 0x02297));
	ent.insert(pair<DOMString, ushort>("ClockwiseContourIntegral", 0x02232));
	ent.insert(pair<DOMString, ushort>("CloseCurlyDoubleQuote", 0x0201D));
	ent.insert(pair<DOMString, ushort>("CloseCurlyQuote", 0x02019));
	ent.insert(pair<DOMString, ushort>("clubsuit", 0x02663));
	ent.insert(pair<DOMString, ushort>("coloneq", 0x02254));
	ent.insert(pair<DOMString, ushort>("complement", 0x02201));
	ent.insert(pair<DOMString, ushort>("complexes", 0x02102));
	ent.insert(pair<DOMString, ushort>("Congruent", 0x02261));
	ent.insert(pair<DOMString, ushort>("ContourIntegral", 0x0222E));
	ent.insert(pair<DOMString, ushort>("Coproduct", 0x02210));
	ent.insert(pair<DOMString, ushort>("CounterClockwiseContourIntegral", 0x02233));
	ent.insert(pair<DOMString, ushort>("CupCap", 0x0224D));
	ent.insert(pair<DOMString, ushort>("curlyeqprec", 0x022DE));
	ent.insert(pair<DOMString, ushort>("curlyeqsucc", 0x022DF));
	ent.insert(pair<DOMString, ushort>("curlyvee", 0x022CE));
	ent.insert(pair<DOMString, ushort>("curlywedge", 0x022CF));
	ent.insert(pair<DOMString, ushort>("curvearrowleft", 0x021B6));
	ent.insert(pair<DOMString, ushort>("curvearrowright", 0x021B7));
	ent.insert(pair<DOMString, ushort>("dbkarow", 0x0290F));
	ent.insert(pair<DOMString, ushort>("ddagger", 0x02021));
	ent.insert(pair<DOMString, ushort>("ddotseq", 0x02A77));
	ent.insert(pair<DOMString, ushort>("Del", 0x02207));
	ent.insert(pair<DOMString, ushort>("DiacriticalAcute", 0x000B4));
	ent.insert(pair<DOMString, ushort>("DiacriticalDot", 0x002D9));
	ent.insert(pair<DOMString, ushort>("DiacriticalDoubleAcute", 0x002DD));
	ent.insert(pair<DOMString, ushort>("DiacriticalGrave", 0x00060));
	ent.insert(pair<DOMString, ushort>("DiacriticalTilde", 0x002DC));
	ent.insert(pair<DOMString, ushort>("diamond", 0x022C4));
	ent.insert(pair<DOMString, ushort>("Diamond", 0x022C4));
	ent.insert(pair<DOMString, ushort>("diamondsuit", 0x02666));
	ent.insert(pair<DOMString, ushort>("DifferentialD", 0x02146));
	ent.insert(pair<DOMString, ushort>("digamma", 0x003DC));
	ent.insert(pair<DOMString, ushort>("div", 0x000F7));
	ent.insert(pair<DOMString, ushort>("divideontimes", 0x022C7));
	ent.insert(pair<DOMString, ushort>("doteq", 0x02250));
	ent.insert(pair<DOMString, ushort>("doteqdot", 0x02251));
	ent.insert(pair<DOMString, ushort>("DotEqual", 0x02250));
	ent.insert(pair<DOMString, ushort>("dotminus", 0x02238));
	ent.insert(pair<DOMString, ushort>("dotplus", 0x02214));
	ent.insert(pair<DOMString, ushort>("dotsquare", 0x022A1));
	ent.insert(pair<DOMString, ushort>("doublebarwedge", 0x02306));
	ent.insert(pair<DOMString, ushort>("DoubleContourIntegral", 0x0222F));
	ent.insert(pair<DOMString, ushort>("DoubleDot", 0x000A8));
	ent.insert(pair<DOMString, ushort>("DoubleDownArrow", 0x021D3));
	ent.insert(pair<DOMString, ushort>("DoubleLeftArrow", 0x021D0));
	ent.insert(pair<DOMString, ushort>("DoubleLeftRightArrow", 0x021D4));
	ent.insert(pair<DOMString, ushort>("DoubleLeftTee", 0x02AE4));
	ent.insert(pair<DOMString, ushort>("DoubleLongLeftArrow", 0x0F579));
	ent.insert(pair<DOMString, ushort>("DoubleLongLeftRightArrow", 0x0F57B));
	ent.insert(pair<DOMString, ushort>("DoubleLongRightArrow", 0x0F57A));
	ent.insert(pair<DOMString, ushort>("DoubleRightArrow", 0x021D2));
	ent.insert(pair<DOMString, ushort>("DoubleRightTee", 0x022A8));
	ent.insert(pair<DOMString, ushort>("DoubleUpArrow", 0x021D1));
	ent.insert(pair<DOMString, ushort>("DoubleUpDownArrow", 0x021D5));
	ent.insert(pair<DOMString, ushort>("DoubleVerticalBar", 0x02225));
	ent.insert(pair<DOMString, ushort>("downarrow", 0x02193));
	ent.insert(pair<DOMString, ushort>("Downarrow", 0x021D3));
	ent.insert(pair<DOMString, ushort>("DownArrow", 0x02193));
	ent.insert(pair<DOMString, ushort>("DownArrowUpArrow", 0x021F5));
	ent.insert(pair<DOMString, ushort>("downdownarrows", 0x021CA));
	ent.insert(pair<DOMString, ushort>("downharpoonleft", 0x021C3));
	ent.insert(pair<DOMString, ushort>("downharpoonright", 0x021C2));
	ent.insert(pair<DOMString, ushort>("DownLeftVector", 0x021BD));
	ent.insert(pair<DOMString, ushort>("DownRightVector", 0x021C1));
	ent.insert(pair<DOMString, ushort>("DownTee", 0x022A4));
	ent.insert(pair<DOMString, ushort>("DownTeeArrow", 0x021A7));
	ent.insert(pair<DOMString, ushort>("drbkarow", 0x02910));
	ent.insert(pair<DOMString, ushort>("Element", 0x02208));
	ent.insert(pair<DOMString, ushort>("emptyset", 0x02205));
	ent.insert(pair<DOMString, ushort>("eqcirc", 0x02256));
	ent.insert(pair<DOMString, ushort>("eqcolon", 0x02255));
	ent.insert(pair<DOMString, ushort>("eqsim", 0x02242));
	ent.insert(pair<DOMString, ushort>("eqslantgtr", 0x022DD));
	ent.insert(pair<DOMString, ushort>("eqslantless", 0x022DC));
	ent.insert(pair<DOMString, ushort>("EqualTilde", 0x02242));
	ent.insert(pair<DOMString, ushort>("Equilibrium", 0x021CC));
	ent.insert(pair<DOMString, ushort>("Exists", 0x02203));
	ent.insert(pair<DOMString, ushort>("expectation", 0x02130));
	ent.insert(pair<DOMString, ushort>("exponentiale", 0x02147));
	ent.insert(pair<DOMString, ushort>("ExponentialE", 0x02147));
	ent.insert(pair<DOMString, ushort>("fallingdotseq", 0x02252));
	ent.insert(pair<DOMString, ushort>("ForAll", 0x02200));
	ent.insert(pair<DOMString, ushort>("Fouriertrf", 0x02131));
	ent.insert(pair<DOMString, ushort>("geq", 0x02265));
	ent.insert(pair<DOMString, ushort>("geqq", 0x02267));
	ent.insert(pair<DOMString, ushort>("geqslant", 0x02A7E));
	ent.insert(pair<DOMString, ushort>("gg", 0x0226B));
	ent.insert(pair<DOMString, ushort>("ggg", 0x022D9));
	ent.insert(pair<DOMString, ushort>("gnapprox", 0x02A8A));
	ent.insert(pair<DOMString, ushort>("gneq", 0x02269));
	ent.insert(pair<DOMString, ushort>("gneqq", 0x02269));
	ent.insert(pair<DOMString, ushort>("GreaterEqual", 0x02265));
	ent.insert(pair<DOMString, ushort>("GreaterEqualLess", 0x022DB));
	ent.insert(pair<DOMString, ushort>("GreaterFullEqual", 0x02267));
	ent.insert(pair<DOMString, ushort>("GreaterLess", 0x02277));
	ent.insert(pair<DOMString, ushort>("GreaterSlantEqual", 0x02A7E));
	ent.insert(pair<DOMString, ushort>("GreaterTilde", 0x02273));
	ent.insert(pair<DOMString, ushort>("gtrapprox", 0x02273));
	ent.insert(pair<DOMString, ushort>("gtrdot", 0x022D7));
	ent.insert(pair<DOMString, ushort>("gtreqless", 0x022DB));
	ent.insert(pair<DOMString, ushort>("gtreqqless", 0x022DB));
	ent.insert(pair<DOMString, ushort>("gtrless", 0x02277));
	ent.insert(pair<DOMString, ushort>("gtrsim", 0x02273));
	ent.insert(pair<DOMString, ushort>("gvertneqq", 0x02269));
	ent.insert(pair<DOMString, ushort>("Hacek", 0x002C7));
	ent.insert(pair<DOMString, ushort>("Hat", 0x00302));
	ent.insert(pair<DOMString, ushort>("hbar", 0x0210F));
	ent.insert(pair<DOMString, ushort>("heartsuit", 0x02661));
	ent.insert(pair<DOMString, ushort>("HilbertSpace", 0x0210B));
	ent.insert(pair<DOMString, ushort>("hksearow", 0x02925));
	ent.insert(pair<DOMString, ushort>("hkswarow", 0x02926));
	ent.insert(pair<DOMString, ushort>("hookleftarrow", 0x021A9));
	ent.insert(pair<DOMString, ushort>("hookrightarrow", 0x021AA));
	ent.insert(pair<DOMString, ushort>("hslash", 0x0210F));
	ent.insert(pair<DOMString, ushort>("HumpDownHump", 0x0224E));
	ent.insert(pair<DOMString, ushort>("HumpEqual", 0x0224F));
	ent.insert(pair<DOMString, ushort>("iiiint", 0x02A0C));
	ent.insert(pair<DOMString, ushort>("iiint", 0x0222D));
	ent.insert(pair<DOMString, ushort>("Im", 0x02111));
	ent.insert(pair<DOMString, ushort>("ImaginaryI", 0x02148));
	ent.insert(pair<DOMString, ushort>("imagline", 0x02110));
	ent.insert(pair<DOMString, ushort>("imagpart", 0x02111));
	ent.insert(pair<DOMString, ushort>("Implies", 0x021D2));
	ent.insert(pair<DOMString, ushort>("in", 0x02208));
	ent.insert(pair<DOMString, ushort>("integers", 0x02124));
	ent.insert(pair<DOMString, ushort>("Integral", 0x0222B));
	ent.insert(pair<DOMString, ushort>("intercal", 0x022BA));
	ent.insert(pair<DOMString, ushort>("Intersection", 0x022C2));
	ent.insert(pair<DOMString, ushort>("intprod", 0x02A3C));
	ent.insert(pair<DOMString, ushort>("InvisibleComma", 0x0200B));
	ent.insert(pair<DOMString, ushort>("InvisibleTimes", 0x02062));
	ent.insert(pair<DOMString, ushort>("langle", 0x02329));
	ent.insert(pair<DOMString, ushort>("Laplacetrf", 0x02112));
	ent.insert(pair<DOMString, ushort>("lbrace", 0x0007B));
	ent.insert(pair<DOMString, ushort>("lbrack", 0x0005B));
	ent.insert(pair<DOMString, ushort>("LeftAngleBracket", 0x02329));
	ent.insert(pair<DOMString, ushort>("leftarrow", 0x02190));
	ent.insert(pair<DOMString, ushort>("Leftarrow", 0x021D0));
	ent.insert(pair<DOMString, ushort>("LeftArrow", 0x02190));
	ent.insert(pair<DOMString, ushort>("LeftArrowBar", 0x021E4));
	ent.insert(pair<DOMString, ushort>("LeftArrowRightArrow", 0x021C6));
	ent.insert(pair<DOMString, ushort>("leftarrowtail", 0x021A2));
	ent.insert(pair<DOMString, ushort>("LeftCeiling", 0x02308));
	ent.insert(pair<DOMString, ushort>("LeftDoubleBracket", 0x0301A));
	ent.insert(pair<DOMString, ushort>("LeftDownVector", 0x021C3));
	ent.insert(pair<DOMString, ushort>("LeftFloor", 0x0230A));
	ent.insert(pair<DOMString, ushort>("leftharpoondown", 0x021BD));
	ent.insert(pair<DOMString, ushort>("leftharpoonup", 0x021BC));
	ent.insert(pair<DOMString, ushort>("leftleftarrows", 0x021C7));
	ent.insert(pair<DOMString, ushort>("leftrightarrow", 0x02194));
	ent.insert(pair<DOMString, ushort>("Leftrightarrow", 0x021D4));
	ent.insert(pair<DOMString, ushort>("LeftRightArrow", 0x02194));
	ent.insert(pair<DOMString, ushort>("leftrightarrows", 0x021C6));
	ent.insert(pair<DOMString, ushort>("leftrightharpoons", 0x021CB));
	ent.insert(pair<DOMString, ushort>("leftrightsquigarrow", 0x021AD));
	ent.insert(pair<DOMString, ushort>("LeftTee", 0x022A3));
	ent.insert(pair<DOMString, ushort>("LeftTeeArrow", 0x021A4));
	ent.insert(pair<DOMString, ushort>("leftthreetimes", 0x022CB));
	ent.insert(pair<DOMString, ushort>("LeftTriangle", 0x022B2));
	ent.insert(pair<DOMString, ushort>("LeftTriangleEqual", 0x022B4));
	ent.insert(pair<DOMString, ushort>("LeftUpVector", 0x021BF));
	ent.insert(pair<DOMString, ushort>("LeftVector", 0x021BC));
	ent.insert(pair<DOMString, ushort>("leq", 0x02264));
	ent.insert(pair<DOMString, ushort>("leqq", 0x02266));
	ent.insert(pair<DOMString, ushort>("leqslant", 0x02A7D));
	ent.insert(pair<DOMString, ushort>("lessapprox", 0x02272));
	ent.insert(pair<DOMString, ushort>("lessdot", 0x022D6));
	ent.insert(pair<DOMString, ushort>("lesseqgtr", 0x022DA));
	ent.insert(pair<DOMString, ushort>("lesseqqgtr", 0x022DA));
	ent.insert(pair<DOMString, ushort>("LessEqualGreater", 0x022DA));
	ent.insert(pair<DOMString, ushort>("LessFullEqual", 0x02266));
	ent.insert(pair<DOMString, ushort>("LessGreater", 0x02276));
	ent.insert(pair<DOMString, ushort>("lessgtr", 0x02276));
	ent.insert(pair<DOMString, ushort>("lesssim", 0x02272));
	ent.insert(pair<DOMString, ushort>("LessSlantEqual", 0x02A7D));
	ent.insert(pair<DOMString, ushort>("LessTilde", 0x02272));
	ent.insert(pair<DOMString, ushort>("ll", 0x0226A));
	ent.insert(pair<DOMString, ushort>("llcorner", 0x0231E));
	ent.insert(pair<DOMString, ushort>("Lleftarrow", 0x021DA));
	ent.insert(pair<DOMString, ushort>("lmoustache", 0x023B0));
	ent.insert(pair<DOMString, ushort>("lnapprox", 0x02A89));
	ent.insert(pair<DOMString, ushort>("lneq", 0x02268));
	ent.insert(pair<DOMString, ushort>("lneqq", 0x02268));
	ent.insert(pair<DOMString, ushort>("longleftarrow", 0x0F576));
	ent.insert(pair<DOMString, ushort>("Longleftarrow", 0x0F579));
	ent.insert(pair<DOMString, ushort>("LongLeftArrow", 0x0F576));
	ent.insert(pair<DOMString, ushort>("longleftrightarrow", 0x0F578));
	ent.insert(pair<DOMString, ushort>("Longleftrightarrow", 0x0F57B));
	ent.insert(pair<DOMString, ushort>("LongLeftRightArrow", 0x0F578));
	ent.insert(pair<DOMString, ushort>("longmapsto", 0x0F57D));
	ent.insert(pair<DOMString, ushort>("longrightarrow", 0x0F577));
	ent.insert(pair<DOMString, ushort>("Longrightarrow", 0x0F57A));
	ent.insert(pair<DOMString, ushort>("LongRightArrow", 0x0F577));
	ent.insert(pair<DOMString, ushort>("looparrowleft", 0x021AB));
	ent.insert(pair<DOMString, ushort>("looparrowright", 0x021AC));
	ent.insert(pair<DOMString, ushort>("LowerLeftArrow", 0x02199));
	ent.insert(pair<DOMString, ushort>("LowerRightArrow", 0x02198));
	ent.insert(pair<DOMString, ushort>("lozenge", 0x025CA));
	ent.insert(pair<DOMString, ushort>("lrcorner", 0x0231F));
	ent.insert(pair<DOMString, ushort>("Lsh", 0x021B0));
	ent.insert(pair<DOMString, ushort>("lvertneqq", 0x02268));
	ent.insert(pair<DOMString, ushort>("maltese", 0x02720));
	ent.insert(pair<DOMString, ushort>("mapsto", 0x021A6));
	ent.insert(pair<DOMString, ushort>("measuredangle", 0x02221));
	ent.insert(pair<DOMString, ushort>("Mellintrf", 0x02133));
	ent.insert(pair<DOMString, ushort>("MinusPlus", 0x02213));
	ent.insert(pair<DOMString, ushort>("mp", 0x02213));
	ent.insert(pair<DOMString, ushort>("multimap", 0x022B8));
	ent.insert(pair<DOMString, ushort>("napprox", 0x02249));
	ent.insert(pair<DOMString, ushort>("natural", 0x0266E));
	ent.insert(pair<DOMString, ushort>("naturals", 0x02115));
	ent.insert(pair<DOMString, ushort>("nearrow", 0x02197));
	ent.insert(pair<DOMString, ushort>("NestedGreaterGreater", 0x0226B));
	ent.insert(pair<DOMString, ushort>("NestedLessLess", 0x0226A));
	ent.insert(pair<DOMString, ushort>("nexists", 0x02204));
	ent.insert(pair<DOMString, ushort>("ngeq", 0x02271));
	ent.insert(pair<DOMString, ushort>("ngeqq", 0x02271));
	ent.insert(pair<DOMString, ushort>("ngeqslant", 0x02271));
	ent.insert(pair<DOMString, ushort>("ngtr", 0x0226F));
	ent.insert(pair<DOMString, ushort>("nleftarrow", 0x0219A));
	ent.insert(pair<DOMString, ushort>("nLeftarrow", 0x021CD));
	ent.insert(pair<DOMString, ushort>("nleftrightarrow", 0x021AE));
	ent.insert(pair<DOMString, ushort>("nLeftrightarrow", 0x021CE));
	ent.insert(pair<DOMString, ushort>("nleq", 0x02270));
	ent.insert(pair<DOMString, ushort>("nleqq", 0x02270));
	ent.insert(pair<DOMString, ushort>("nleqslant", 0x02270));
	ent.insert(pair<DOMString, ushort>("nless", 0x0226E));
	ent.insert(pair<DOMString, ushort>("NonBreakingSpace", 0x000A0));
	ent.insert(pair<DOMString, ushort>("NotCongruent", 0x02262));
	ent.insert(pair<DOMString, ushort>("NotDoubleVerticalBar", 0x02226));
	ent.insert(pair<DOMString, ushort>("NotElement", 0x02209));
	ent.insert(pair<DOMString, ushort>("NotEqual", 0x02260));
	ent.insert(pair<DOMString, ushort>("NotEqualTilde", 0x02242));
	ent.insert(pair<DOMString, ushort>("NotExists", 0x02204));
	ent.insert(pair<DOMString, ushort>("NotGreater", 0x0226F));
	ent.insert(pair<DOMString, ushort>("NotGreaterEqual", 0x02271));
	ent.insert(pair<DOMString, ushort>("NotGreaterFullEqual", 0x02270));
	ent.insert(pair<DOMString, ushort>("NotGreaterGreater", 0x0226B));
	ent.insert(pair<DOMString, ushort>("NotGreaterLess", 0x02279));
	ent.insert(pair<DOMString, ushort>("NotGreaterSlantEqual", 0x02271));
	ent.insert(pair<DOMString, ushort>("NotGreaterTilde", 0x02275));
	ent.insert(pair<DOMString, ushort>("NotHumpDownHump", 0x0224E));
	ent.insert(pair<DOMString, ushort>("NotLeftTriangle", 0x022EA));
	ent.insert(pair<DOMString, ushort>("NotLeftTriangleEqual", 0x022EC));
	ent.insert(pair<DOMString, ushort>("NotLess", 0x0226E));
	ent.insert(pair<DOMString, ushort>("NotLessEqual", 0x02270));
	ent.insert(pair<DOMString, ushort>("NotLessGreater", 0x02278));
	ent.insert(pair<DOMString, ushort>("NotLessLess", 0x0226A));
	ent.insert(pair<DOMString, ushort>("NotLessSlantEqual", 0x02270));
	ent.insert(pair<DOMString, ushort>("NotLessTilde", 0x02274));
	ent.insert(pair<DOMString, ushort>("NotPrecedes", 0x02280));
	ent.insert(pair<DOMString, ushort>("NotPrecedesEqual", 0x02AAF));
	ent.insert(pair<DOMString, ushort>("NotPrecedesSlantEqual", 0x022E0));
	ent.insert(pair<DOMString, ushort>("NotReverseElement", 0x0220C));
	ent.insert(pair<DOMString, ushort>("NotRightTriangle", 0x022EB));
	ent.insert(pair<DOMString, ushort>("NotRightTriangleEqual", 0x022ED));
	ent.insert(pair<DOMString, ushort>("NotSquareSubsetEqual", 0x022E2));
	ent.insert(pair<DOMString, ushort>("NotSquareSupersetEqual", 0x022E3));
	ent.insert(pair<DOMString, ushort>("NotSubset", 0x02284));
	ent.insert(pair<DOMString, ushort>("NotSubsetEqual", 0x02288));
	ent.insert(pair<DOMString, ushort>("NotSucceeds", 0x02281));
	ent.insert(pair<DOMString, ushort>("NotSucceedsEqual", 0x02AB0));
	ent.insert(pair<DOMString, ushort>("NotSucceedsSlantEqual", 0x022E1));
	ent.insert(pair<DOMString, ushort>("NotSuperset", 0x02285));
	ent.insert(pair<DOMString, ushort>("NotSupersetEqual", 0x02289));
	ent.insert(pair<DOMString, ushort>("NotTilde", 0x02241));
	ent.insert(pair<DOMString, ushort>("NotTildeEqual", 0x02244));
	ent.insert(pair<DOMString, ushort>("NotTildeFullEqual", 0x02247));
	ent.insert(pair<DOMString, ushort>("NotTildeTilde", 0x02249));
	ent.insert(pair<DOMString, ushort>("NotVerticalBar", 0x02224));
	ent.insert(pair<DOMString, ushort>("nparallel", 0x02226));
	ent.insert(pair<DOMString, ushort>("nprec", 0x02280));
	ent.insert(pair<DOMString, ushort>("npreceq", 0x02AAF));
	ent.insert(pair<DOMString, ushort>("nrightarrow", 0x0219B));
	ent.insert(pair<DOMString, ushort>("nRightarrow", 0x021CF));
	ent.insert(pair<DOMString, ushort>("nshortmid", 0x02224));
	ent.insert(pair<DOMString, ushort>("nshortparallel", 0x02226));
	ent.insert(pair<DOMString, ushort>("nsimeq", 0x02244));
	ent.insert(pair<DOMString, ushort>("nsubset", 0x02284));
	ent.insert(pair<DOMString, ushort>("nsubseteq", 0x02288));
	ent.insert(pair<DOMString, ushort>("nsubseteqq", 0x02288));
	ent.insert(pair<DOMString, ushort>("nsucc", 0x02281));
	ent.insert(pair<DOMString, ushort>("nsucceq", 0x02AB0));
	ent.insert(pair<DOMString, ushort>("nsupset", 0x02285));
	ent.insert(pair<DOMString, ushort>("nsupseteq", 0x02289));
	ent.insert(pair<DOMString, ushort>("nsupseteqq", 0x02289));
	ent.insert(pair<DOMString, ushort>("ntriangleleft", 0x022EA));
	ent.insert(pair<DOMString, ushort>("ntrianglelefteq", 0x022EC));
	ent.insert(pair<DOMString, ushort>("ntriangleright", 0x022EB));
	ent.insert(pair<DOMString, ushort>("ntrianglerighteq", 0x022ED));
	ent.insert(pair<DOMString, ushort>("nwarrow", 0x02196));
	ent.insert(pair<DOMString, ushort>("oint", 0x0222E));
	ent.insert(pair<DOMString, ushort>("OpenCurlyDoubleQuote", 0x0201C));
	ent.insert(pair<DOMString, ushort>("OpenCurlyQuote", 0x02018));
	ent.insert(pair<DOMString, ushort>("orderof", 0x02134));
	ent.insert(pair<DOMString, ushort>("parallel", 0x02225));
	ent.insert(pair<DOMString, ushort>("PartialD", 0x02202));
	ent.insert(pair<DOMString, ushort>("pitchfork", 0x022D4));
	ent.insert(pair<DOMString, ushort>("PlusMinus", 0x000B1));
	ent.insert(pair<DOMString, ushort>("pm", 0x000B1));
	ent.insert(pair<DOMString, ushort>("Poincareplane", 0x0210C));
	ent.insert(pair<DOMString, ushort>("prec", 0x0227A));
	ent.insert(pair<DOMString, ushort>("precapprox", 0x0227E));
	ent.insert(pair<DOMString, ushort>("preccurlyeq", 0x0227C));
	ent.insert(pair<DOMString, ushort>("Precedes", 0x0227A));
	ent.insert(pair<DOMString, ushort>("PrecedesEqual", 0x02AAF));
	ent.insert(pair<DOMString, ushort>("PrecedesSlantEqual", 0x0227C));
	ent.insert(pair<DOMString, ushort>("PrecedesTilde", 0x0227E));
	ent.insert(pair<DOMString, ushort>("preceq", 0x02AAF));
	ent.insert(pair<DOMString, ushort>("precnapprox", 0x022E8));
	ent.insert(pair<DOMString, ushort>("precneqq", 0x02AB5));
	ent.insert(pair<DOMString, ushort>("precnsim", 0x022E8));
	ent.insert(pair<DOMString, ushort>("precsim", 0x0227E));
	ent.insert(pair<DOMString, ushort>("primes", 0x02119));
	ent.insert(pair<DOMString, ushort>("Proportion", 0x02237));
	ent.insert(pair<DOMString, ushort>("Proportional", 0x0221D));
	ent.insert(pair<DOMString, ushort>("propto", 0x0221D));
	ent.insert(pair<DOMString, ushort>("quaternions", 0x0210D));
	ent.insert(pair<DOMString, ushort>("questeq", 0x0225F));
	ent.insert(pair<DOMString, ushort>("rangle", 0x0232A));
	ent.insert(pair<DOMString, ushort>("rationals", 0x0211A));
	ent.insert(pair<DOMString, ushort>("rbrace", 0x0007D));
	ent.insert(pair<DOMString, ushort>("rbrack", 0x0005D));
	ent.insert(pair<DOMString, ushort>("Re", 0x0211C));
	ent.insert(pair<DOMString, ushort>("realine", 0x0211B));
	ent.insert(pair<DOMString, ushort>("realpart", 0x0211C));
	ent.insert(pair<DOMString, ushort>("reals", 0x0211D));
	ent.insert(pair<DOMString, ushort>("ReverseElement", 0x0220B));
	ent.insert(pair<DOMString, ushort>("ReverseEquilibrium", 0x021CB));
	ent.insert(pair<DOMString, ushort>("ReverseUpEquilibrium", 0x0296F));
	ent.insert(pair<DOMString, ushort>("RightAngleBracket", 0x0232A));
	ent.insert(pair<DOMString, ushort>("rightarrow", 0x02192));
	ent.insert(pair<DOMString, ushort>("Rightarrow", 0x021D2));
	ent.insert(pair<DOMString, ushort>("RightArrow", 0x02192));
	ent.insert(pair<DOMString, ushort>("RightArrowBar", 0x021E5));
	ent.insert(pair<DOMString, ushort>("RightArrowLeftArrow", 0x021C4));
	ent.insert(pair<DOMString, ushort>("rightarrowtail", 0x021A3));
	ent.insert(pair<DOMString, ushort>("RightCeiling", 0x02309));
	ent.insert(pair<DOMString, ushort>("RightDoubleBracket", 0x0301B));
	ent.insert(pair<DOMString, ushort>("RightDownVector", 0x021C2));
	ent.insert(pair<DOMString, ushort>("RightFloor", 0x0230B));
	ent.insert(pair<DOMString, ushort>("rightharpoondown", 0x021C1));
	ent.insert(pair<DOMString, ushort>("rightharpoonup", 0x021C0));
	ent.insert(pair<DOMString, ushort>("rightleftarrows", 0x021C4));
	ent.insert(pair<DOMString, ushort>("rightleftharpoons", 0x021CC));
	ent.insert(pair<DOMString, ushort>("rightrightarrows", 0x021C9));
	ent.insert(pair<DOMString, ushort>("rightsquigarrow", 0x0219D));
	ent.insert(pair<DOMString, ushort>("RightTee", 0x022A2));
	ent.insert(pair<DOMString, ushort>("RightTeeArrow", 0x021A6));
	ent.insert(pair<DOMString, ushort>("rightthreetimes", 0x022CC));
	ent.insert(pair<DOMString, ushort>("RightTriangle", 0x022B3));
	ent.insert(pair<DOMString, ushort>("RightTriangleEqual", 0x022B5));
	ent.insert(pair<DOMString, ushort>("RightUpVector", 0x021BE));
	ent.insert(pair<DOMString, ushort>("RightVector", 0x021C0));
	ent.insert(pair<DOMString, ushort>("risingdotseq", 0x02253));
	ent.insert(pair<DOMString, ushort>("rmoustache", 0x023B1));
	ent.insert(pair<DOMString, ushort>("Rrightarrow", 0x021DB));
	ent.insert(pair<DOMString, ushort>("Rsh", 0x021B1));
	ent.insert(pair<DOMString, ushort>("searrow", 0x02198));
	ent.insert(pair<DOMString, ushort>("setminus", 0x02216));
	ent.insert(pair<DOMString, ushort>("ShortLeftArrow", 0x02190));
	ent.insert(pair<DOMString, ushort>("shortmid", 0x02223));
	ent.insert(pair<DOMString, ushort>("shortparallel", 0x02225));
	ent.insert(pair<DOMString, ushort>("ShortRightArrow", 0x02192));
	ent.insert(pair<DOMString, ushort>("simeq", 0x02243));
	ent.insert(pair<DOMString, ushort>("SmallCircle", 0x02218));
	ent.insert(pair<DOMString, ushort>("smallsetminus", 0x02216));
	ent.insert(pair<DOMString, ushort>("spadesuit", 0x02660));
	ent.insert(pair<DOMString, ushort>("Sqrt", 0x0221A));
	ent.insert(pair<DOMString, ushort>("sqsubset", 0x0228F));
	ent.insert(pair<DOMString, ushort>("sqsubseteq", 0x02291));
	ent.insert(pair<DOMString, ushort>("sqsupset", 0x02290));
	ent.insert(pair<DOMString, ushort>("sqsupseteq", 0x02292));
	ent.insert(pair<DOMString, ushort>("Square", 0x025A1));
	ent.insert(pair<DOMString, ushort>("SquareIntersection", 0x02293));
	ent.insert(pair<DOMString, ushort>("SquareSubset", 0x0228F));
	ent.insert(pair<DOMString, ushort>("SquareSubsetEqual", 0x02291));
	ent.insert(pair<DOMString, ushort>("SquareSuperset", 0x02290));
	ent.insert(pair<DOMString, ushort>("SquareSupersetEqual", 0x02292));
	ent.insert(pair<DOMString, ushort>("SquareUnion", 0x02294));
	ent.insert(pair<DOMString, ushort>("Star", 0x022C6));
	ent.insert(pair<DOMString, ushort>("straightepsilon", 0x003B5));
	ent.insert(pair<DOMString, ushort>("straightphi", 0x003C6));
	ent.insert(pair<DOMString, ushort>("subset", 0x02282));
	ent.insert(pair<DOMString, ushort>("Subset", 0x022D0));
	ent.insert(pair<DOMString, ushort>("subseteq", 0x02286));
	ent.insert(pair<DOMString, ushort>("subseteqq", 0x02286));
	ent.insert(pair<DOMString, ushort>("SubsetEqual", 0x02286));
	ent.insert(pair<DOMString, ushort>("subsetneq", 0x0228A));
	ent.insert(pair<DOMString, ushort>("subsetneqq", 0x0228A));
	ent.insert(pair<DOMString, ushort>("succ", 0x0227B));
	ent.insert(pair<DOMString, ushort>("succapprox", 0x0227F));
	ent.insert(pair<DOMString, ushort>("succcurlyeq", 0x0227D));
	ent.insert(pair<DOMString, ushort>("Succeeds", 0x0227B));
	ent.insert(pair<DOMString, ushort>("SucceedsEqual", 0x0227D));
	ent.insert(pair<DOMString, ushort>("SucceedsSlantEqual", 0x0227D));
	ent.insert(pair<DOMString, ushort>("SucceedsTilde", 0x0227F));
	ent.insert(pair<DOMString, ushort>("succeq", 0x0227D));
	ent.insert(pair<DOMString, ushort>("succnapprox", 0x022E9));
	ent.insert(pair<DOMString, ushort>("succneqq", 0x02AB6));
	ent.insert(pair<DOMString, ushort>("succnsim", 0x022E9));
	ent.insert(pair<DOMString, ushort>("succsim", 0x0227F));
	ent.insert(pair<DOMString, ushort>("SuchThat", 0x0220B));
	ent.insert(pair<DOMString, ushort>("Sum", 0x02211));
	ent.insert(pair<DOMString, ushort>("Superset", 0x02283));
	ent.insert(pair<DOMString, ushort>("SupersetEqual", 0x02287));
	ent.insert(pair<DOMString, ushort>("supset", 0x02283));
	ent.insert(pair<DOMString, ushort>("Supset", 0x022D1));
	ent.insert(pair<DOMString, ushort>("supseteq", 0x02287));
	ent.insert(pair<DOMString, ushort>("supseteqq", 0x02287));
	ent.insert(pair<DOMString, ushort>("supsetneq", 0x0228B));
	ent.insert(pair<DOMString, ushort>("supsetneqq", 0x0228B));
	ent.insert(pair<DOMString, ushort>("swarrow", 0x02199));
	ent.insert(pair<DOMString, ushort>("therefore", 0x02234));
	ent.insert(pair<DOMString, ushort>("Therefore", 0x02234));
	ent.insert(pair<DOMString, ushort>("thickapprox", 0x02248));
	ent.insert(pair<DOMString, ushort>("thicksim", 0x0223C));
	ent.insert(pair<DOMString, ushort>("ThinSpace", 0x02009));
	ent.insert(pair<DOMString, ushort>("Tilde", 0x0223C));
	ent.insert(pair<DOMString, ushort>("TildeEqual", 0x02243));
	ent.insert(pair<DOMString, ushort>("TildeFullEqual", 0x02245));
	ent.insert(pair<DOMString, ushort>("TildeTilde", 0x02248));
	ent.insert(pair<DOMString, ushort>("toea", 0x02928));
	ent.insert(pair<DOMString, ushort>("tosa", 0x02929));
	ent.insert(pair<DOMString, ushort>("triangle", 0x025B5));
	ent.insert(pair<DOMString, ushort>("triangledown", 0x025BF));
	ent.insert(pair<DOMString, ushort>("triangleleft", 0x025C3));
	ent.insert(pair<DOMString, ushort>("trianglelefteq", 0x022B4));
	ent.insert(pair<DOMString, ushort>("triangleq", 0x0225C));
	ent.insert(pair<DOMString, ushort>("triangleright", 0x025B9));
	ent.insert(pair<DOMString, ushort>("trianglerighteq", 0x022B5));
	ent.insert(pair<DOMString, ushort>("TripleDot", 0x020DB));
	ent.insert(pair<DOMString, ushort>("twoheadleftarrow", 0x0219E));
	ent.insert(pair<DOMString, ushort>("twoheadrightarrow", 0x021A0));
	ent.insert(pair<DOMString, ushort>("ulcorner", 0x0231C));
	ent.insert(pair<DOMString, ushort>("Union", 0x022C3));
	ent.insert(pair<DOMString, ushort>("UnionPlus", 0x0228E));
	ent.insert(pair<DOMString, ushort>("uparrow", 0x02191));
	ent.insert(pair<DOMString, ushort>("Uparrow", 0x021D1));
	ent.insert(pair<DOMString, ushort>("UpArrow", 0x02191));
	ent.insert(pair<DOMString, ushort>("UpArrowDownArrow", 0x021C5));
	ent.insert(pair<DOMString, ushort>("updownarrow", 0x02195));
	ent.insert(pair<DOMString, ushort>("Updownarrow", 0x021D5));
	ent.insert(pair<DOMString, ushort>("UpDownArrow", 0x02195));
	ent.insert(pair<DOMString, ushort>("UpEquilibrium", 0x0296E));
	ent.insert(pair<DOMString, ushort>("upharpoonleft", 0x021BF));
	ent.insert(pair<DOMString, ushort>("upharpoonright", 0x021BE));
	ent.insert(pair<DOMString, ushort>("UpperLeftArrow", 0x02196));
	ent.insert(pair<DOMString, ushort>("UpperRightArrow", 0x02197));
	ent.insert(pair<DOMString, ushort>("upsilon", 0x003C5));
	ent.insert(pair<DOMString, ushort>("Upsilon", 0x003D2));
	ent.insert(pair<DOMString, ushort>("UpTee", 0x022A5));
	ent.insert(pair<DOMString, ushort>("UpTeeArrow", 0x021A5));
	ent.insert(pair<DOMString, ushort>("upuparrows", 0x021C8));
	ent.insert(pair<DOMString, ushort>("urcorner", 0x0231D));
	ent.insert(pair<DOMString, ushort>("varepsilon", 0x0025B));
	ent.insert(pair<DOMString, ushort>("varkappa", 0x003F0));
	ent.insert(pair<DOMString, ushort>("varnothing", 0x02205));
	ent.insert(pair<DOMString, ushort>("varphi", 0x003D5));
	ent.insert(pair<DOMString, ushort>("varpi", 0x003D6));
	ent.insert(pair<DOMString, ushort>("varpropto", 0x0221D));
	ent.insert(pair<DOMString, ushort>("varrho", 0x003F1));
	ent.insert(pair<DOMString, ushort>("varsigma", 0x003C2));
	ent.insert(pair<DOMString, ushort>("varsubsetneq", 0x0228A));
	ent.insert(pair<DOMString, ushort>("varsubsetneqq", 0x0228A));
	ent.insert(pair<DOMString, ushort>("varsupsetneq", 0x0228B));
	ent.insert(pair<DOMString, ushort>("varsupsetneqq", 0x0228B));
	ent.insert(pair<DOMString, ushort>("vartheta", 0x003D1));
	ent.insert(pair<DOMString, ushort>("vartriangleleft", 0x022B2));
	ent.insert(pair<DOMString, ushort>("vartriangleright", 0x022B3));
	ent.insert(pair<DOMString, ushort>("vee", 0x02228));
	ent.insert(pair<DOMString, ushort>("Vee", 0x022C1));
	ent.insert(pair<DOMString, ushort>("vert", 0x0007C));
	ent.insert(pair<DOMString, ushort>("Vert", 0x02016));
	ent.insert(pair<DOMString, ushort>("VerticalBar", 0x02223));
	ent.insert(pair<DOMString, ushort>("VerticalTilde", 0x02240));
	ent.insert(pair<DOMString, ushort>("VeryThinSpace", 0x0200A));
	ent.insert(pair<DOMString, ushort>("wedge", 0x02227));
	ent.insert(pair<DOMString, ushort>("Wedge", 0x022C0));
	ent.insert(pair<DOMString, ushort>("wp", 0x02118));
	ent.insert(pair<DOMString, ushort>("wr", 0x02240));
	ent.insert(pair<DOMString, ushort>("zeetrf", 0x02128));
	ent.insert(pair<DOMString, ushort>("ZeroWidthSpace", 0x0200B));
}
