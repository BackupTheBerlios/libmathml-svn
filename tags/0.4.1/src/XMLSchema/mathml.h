// this file was automatically generated by 'parseschema'
#ifndef MATHML_H
#define MATHML_H
typedef unsigned int uint;
#include "elements.h"
#include "mathtypes.h"
namespace MML {
enum AttributeType {
    BOOL_T, DOMSTRING_T, FLOAT_T, H_UNIT_T, INT_T, MATHCOLOR_T, 
    MATHVARIANT_T, V_UNIT_T
};
enum Attribute {
    ACCENT, ACCENTUNDER, ACTIONTYPE, ALIGN, ALIGNMENTSCOPE, ALT, ALTIMG, 
    ALTTEXT, BACKGROUND, BASE, BASELINE, BEVELLED, CLASS, CLOSE, CLOSURE, 
    COLOR, COLUMNALIGN, COLUMNLINES, COLUMNSPACING, COLUMNSPAN, 
    COLUMNWIDTH, DEFINITIONURL, DENOMALIGN, DEPTH, DISPLAY, DISPLAYSTYLE, 
    EDGE, ENCODING, EQUALCOLUMNS, EQUALROWS, FENCE, FONTFAMILY, FORM, 
    FRAME, FRAMESPACING, GROUPALIGN, HEIGHT, ID, INDEX, LARGEOP, LINEBREAK, 
    LINETHICKNESS, LQUOTE, LSPACE, MACROS, MATHBACKGROUND, MATHCOLOR, 
    MATHSIZE, MATHVARIANT, MAXSIZE, MEDIUMMATHSPACE, MINLABELSPACING, 
    MINSIZE, MOVABLELIMITS, NAME, NARGS, NOTATION, NUMALIGN, OCCURRENCE, 
    OPEN, ORDER, OVERFLOW, ROWALIGN, ROWLINES, ROWSPACING, ROWSPAN, RQUOTE, 
    RSPACE, SCOPE, SCRIPTLEVEL, SCRIPTMINSIZE, SCRIPTSIZEMULTIPLIER, 
    SELECTION, SEPARATOR, SEPARATORS, SIDE, STRETCHY, STYLE, 
    SUBSCRIPTSHIFT, SUPERSCRIPTSHIFT, SYMMETRIC, THICKMATHSPACE, 
    THINMATHSPACE, TYPE, VERYTHICKMATHSPACE, VERYTHINMATHSPACE, 
    VERYVERYTHICKMATHSPACE, VERYVERYTHINMATHSPACE, WIDTH, XLINK_HREF, XREF
};
}
class MMLAttribute {
public:
    virtual ~MMLAttribute() {}
    bool cleanup;
};
class MMLDOMString : public MMLAttribute {
public:
    MMLDOMString(DOMString, bool c=true);
    DOMString value;
};
class MMLMathColor : public MMLAttribute {
public:
    MMLMathColor(MathColor, bool c=true);
    MathColor value;
};
class MMLMathVariant : public MMLAttribute {
public:
    MMLMathVariant(MathVariant, bool c=true);
    MathVariant value;
};
class MMLbool : public MMLAttribute {
public:
    MMLbool(bool, bool c=true);
    bool value;
};
class MMLfloat : public MMLAttribute {
public:
    MMLfloat(float, bool c=true);
    float value;
};
class MMLh_unit : public MMLAttribute {
public:
    MMLh_unit(h_unit, bool c=true);
    h_unit value;
};
class MMLint : public MMLAttribute {
public:
    MMLint(int, bool c=true);
    int value;
};
class MMLv_unit : public MMLAttribute {
public:
    MMLv_unit(v_unit, bool c=true);
    v_unit value;
};
namespace MML {
enum absAtt {
    absCLASS, absDEFINITIONURL, absENCODING, absID, absSTYLE, 
    absXLINK_HREF, absXREF
};
enum andAtt {
    andCLASS, andDEFINITIONURL, andENCODING, andID, andSTYLE, 
    andXLINK_HREF, andXREF
};
enum annotationAtt {
    annotationCLASS, annotationENCODING, annotationID, annotationSTYLE, 
    annotationXLINK_HREF, annotationXREF
};
enum annotation_xmlAtt {
    annotation_xmlCLASS, annotation_xmlENCODING, annotation_xmlID, 
    annotation_xmlSTYLE, annotation_xmlXLINK_HREF, annotation_xmlXREF
};
enum applyAtt {
    applyCLASS, applyID, applySTYLE, applyXLINK_HREF, applyXREF
};
enum approxAtt {
    approxCLASS, approxDEFINITIONURL, approxENCODING, approxID, 
    approxSTYLE, approxXLINK_HREF, approxXREF
};
enum arccosAtt {
    arccosCLASS, arccosDEFINITIONURL, arccosENCODING, arccosID, 
    arccosSTYLE, arccosXLINK_HREF, arccosXREF
};
enum arccoshAtt {
    arccoshCLASS, arccoshDEFINITIONURL, arccoshENCODING, arccoshID, 
    arccoshSTYLE, arccoshXLINK_HREF, arccoshXREF
};
enum arccotAtt {
    arccotCLASS, arccotDEFINITIONURL, arccotENCODING, arccotID, 
    arccotSTYLE, arccotXLINK_HREF, arccotXREF
};
enum arccothAtt {
    arccothCLASS, arccothDEFINITIONURL, arccothENCODING, arccothID, 
    arccothSTYLE, arccothXLINK_HREF, arccothXREF
};
enum arccscAtt {
    arccscCLASS, arccscDEFINITIONURL, arccscENCODING, arccscID, 
    arccscSTYLE, arccscXLINK_HREF, arccscXREF
};
enum arccschAtt {
    arccschCLASS, arccschDEFINITIONURL, arccschENCODING, arccschID, 
    arccschSTYLE, arccschXLINK_HREF, arccschXREF
};
enum arcsecAtt {
    arcsecCLASS, arcsecDEFINITIONURL, arcsecENCODING, arcsecID, 
    arcsecSTYLE, arcsecXLINK_HREF, arcsecXREF
};
enum arcsechAtt {
    arcsechCLASS, arcsechDEFINITIONURL, arcsechENCODING, arcsechID, 
    arcsechSTYLE, arcsechXLINK_HREF, arcsechXREF
};
enum arcsinAtt {
    arcsinCLASS, arcsinDEFINITIONURL, arcsinENCODING, arcsinID, 
    arcsinSTYLE, arcsinXLINK_HREF, arcsinXREF
};
enum arcsinhAtt {
    arcsinhCLASS, arcsinhDEFINITIONURL, arcsinhENCODING, arcsinhID, 
    arcsinhSTYLE, arcsinhXLINK_HREF, arcsinhXREF
};
enum arctanAtt {
    arctanCLASS, arctanDEFINITIONURL, arctanENCODING, arctanID, 
    arctanSTYLE, arctanXLINK_HREF, arctanXREF
};
enum arctanhAtt {
    arctanhCLASS, arctanhDEFINITIONURL, arctanhENCODING, arctanhID, 
    arctanhSTYLE, arctanhXLINK_HREF, arctanhXREF
};
enum argAtt {
    argCLASS, argDEFINITIONURL, argENCODING, argID, argSTYLE, 
    argXLINK_HREF, argXREF
};
enum bvarAtt {
    bvarCLASS, bvarID, bvarSTYLE, bvarXLINK_HREF, bvarXREF
};
enum cardAtt {
    cardCLASS, cardDEFINITIONURL, cardENCODING, cardID, cardSTYLE, 
    cardXLINK_HREF, cardXREF
};
enum cartesianproductAtt {
    cartesianproductCLASS, cartesianproductDEFINITIONURL, 
    cartesianproductENCODING, cartesianproductID, cartesianproductSTYLE, 
    cartesianproductXLINK_HREF, cartesianproductXREF
};
enum ceilingAtt {
    ceilingCLASS, ceilingDEFINITIONURL, ceilingENCODING, ceilingID, 
    ceilingSTYLE, ceilingXLINK_HREF, ceilingXREF
};
enum ciAtt {
    ciCLASS, ciDEFINITIONURL, ciENCODING, ciID, ciSTYLE, ciTYPE, 
    ciXLINK_HREF, ciXREF
};
enum cnAtt {
    cnBASE, cnCLASS, cnDEFINITIONURL, cnENCODING, cnID, cnSTYLE, cnTYPE, 
    cnXLINK_HREF, cnXREF
};
enum codomainAtt {
    codomainCLASS, codomainDEFINITIONURL, codomainENCODING, codomainID, 
    codomainSTYLE, codomainXLINK_HREF, codomainXREF
};
enum complexesAtt {
    complexesCLASS, complexesDEFINITIONURL, complexesENCODING, complexesID, 
    complexesSTYLE, complexesXLINK_HREF, complexesXREF
};
enum composeAtt {
    composeCLASS, composeDEFINITIONURL, composeENCODING, composeID, 
    composeSTYLE, composeXLINK_HREF, composeXREF
};
enum conditionAtt {
    conditionDEFINITIONURL, conditionENCODING
};
enum conjugateAtt {
    conjugateCLASS, conjugateDEFINITIONURL, conjugateENCODING, conjugateID, 
    conjugateSTYLE, conjugateXLINK_HREF, conjugateXREF
};
enum cosAtt {
    cosCLASS, cosDEFINITIONURL, cosENCODING, cosID, cosSTYLE, 
    cosXLINK_HREF, cosXREF
};
enum coshAtt {
    coshCLASS, coshDEFINITIONURL, coshENCODING, coshID, coshSTYLE, 
    coshXLINK_HREF, coshXREF
};
enum cotAtt {
    cotCLASS, cotDEFINITIONURL, cotENCODING, cotID, cotSTYLE, 
    cotXLINK_HREF, cotXREF
};
enum cothAtt {
    cothCLASS, cothDEFINITIONURL, cothENCODING, cothID, cothSTYLE, 
    cothXLINK_HREF, cothXREF
};
enum cscAtt {
    cscCLASS, cscDEFINITIONURL, cscENCODING, cscID, cscSTYLE, 
    cscXLINK_HREF, cscXREF
};
enum cschAtt {
    cschCLASS, cschDEFINITIONURL, cschENCODING, cschID, cschSTYLE, 
    cschXLINK_HREF, cschXREF
};
enum csymbolAtt {
    csymbolCLASS, csymbolDEFINITIONURL, csymbolENCODING, csymbolID, 
    csymbolSTYLE, csymbolXLINK_HREF, csymbolXREF
};
enum curlAtt {
    curlCLASS, curlDEFINITIONURL, curlENCODING, curlID, curlSTYLE, 
    curlXLINK_HREF, curlXREF
};
enum declareAtt {
    declareDEFINITIONURL, declareENCODING, declareNARGS, declareOCCURRENCE, 
    declareSCOPE, declareTYPE
};
enum degreeAtt {
    degreeCLASS, degreeID, degreeSTYLE, degreeXLINK_HREF, degreeXREF
};
enum determinantAtt {
    determinantCLASS, determinantDEFINITIONURL, determinantENCODING, 
    determinantID, determinantSTYLE, determinantXLINK_HREF, 
    determinantXREF
};
enum diffAtt {
    diffCLASS, diffDEFINITIONURL, diffENCODING, diffID, diffSTYLE, 
    diffXLINK_HREF, diffXREF
};
enum divergenceAtt {
    divergenceCLASS, divergenceDEFINITIONURL, divergenceENCODING, 
    divergenceID, divergenceSTYLE, divergenceXLINK_HREF, divergenceXREF
};
enum divideAtt {
    divideCLASS, divideDEFINITIONURL, divideENCODING, divideID, 
    divideSTYLE, divideXLINK_HREF, divideXREF
};
enum domainAtt {
    domainCLASS, domainDEFINITIONURL, domainENCODING, domainID, 
    domainSTYLE, domainXLINK_HREF, domainXREF
};
enum domainofapplicationAtt {
    domainofapplicationCLASS, domainofapplicationDEFINITIONURL, 
    domainofapplicationENCODING, domainofapplicationID, 
    domainofapplicationSTYLE, domainofapplicationXLINK_HREF, 
    domainofapplicationXREF
};
enum emptysetAtt {
    emptysetCLASS, emptysetDEFINITIONURL, emptysetENCODING, emptysetID, 
    emptysetSTYLE, emptysetXLINK_HREF, emptysetXREF
};
enum eqAtt {
    eqCLASS, eqDEFINITIONURL, eqENCODING, eqID, eqSTYLE, eqXLINK_HREF, 
    eqXREF
};
enum equivalentAtt {
    equivalentCLASS, equivalentDEFINITIONURL, equivalentENCODING, 
    equivalentID, equivalentSTYLE, equivalentXLINK_HREF, equivalentXREF
};
enum eulergammaAtt {
    eulergammaCLASS, eulergammaDEFINITIONURL, eulergammaENCODING, 
    eulergammaID, eulergammaSTYLE, eulergammaXLINK_HREF, eulergammaXREF
};
enum existsAtt {
    existsCLASS, existsDEFINITIONURL, existsENCODING, existsID, 
    existsSTYLE, existsXLINK_HREF, existsXREF
};
enum expAtt {
    expCLASS, expDEFINITIONURL, expENCODING, expID, expSTYLE, 
    expXLINK_HREF, expXREF
};
enum exponentialeAtt {
    exponentialeCLASS, exponentialeDEFINITIONURL, exponentialeENCODING, 
    exponentialeID, exponentialeSTYLE, exponentialeXLINK_HREF, 
    exponentialeXREF
};
enum factorialAtt {
    factorialCLASS, factorialDEFINITIONURL, factorialENCODING, factorialID, 
    factorialSTYLE, factorialXLINK_HREF, factorialXREF
};
enum factorofAtt {
    factorofCLASS, factorofDEFINITIONURL, factorofENCODING, factorofID, 
    factorofSTYLE, factorofXLINK_HREF, factorofXREF
};
enum falseAtt {
    falseCLASS, falseDEFINITIONURL, falseENCODING, falseID, falseSTYLE, 
    falseXLINK_HREF, falseXREF
};
enum floorAtt {
    floorCLASS, floorDEFINITIONURL, floorENCODING, floorID, floorSTYLE, 
    floorXLINK_HREF, floorXREF
};
enum forallAtt {
    forallCLASS, forallDEFINITIONURL, forallENCODING, forallID, 
    forallSTYLE, forallXLINK_HREF, forallXREF
};
enum gcdAtt {
    gcdCLASS, gcdDEFINITIONURL, gcdENCODING, gcdID, gcdSTYLE, 
    gcdXLINK_HREF, gcdXREF
};
enum geqAtt {
    geqCLASS, geqDEFINITIONURL, geqENCODING, geqID, geqSTYLE, 
    geqXLINK_HREF, geqXREF
};
enum gradAtt {
    gradCLASS, gradDEFINITIONURL, gradENCODING, gradID, gradSTYLE, 
    gradXLINK_HREF, gradXREF
};
enum gtAtt {
    gtCLASS, gtDEFINITIONURL, gtENCODING, gtID, gtSTYLE, gtXLINK_HREF, 
    gtXREF
};
enum identAtt {
    identCLASS, identDEFINITIONURL, identENCODING, identID, identSTYLE, 
    identXLINK_HREF, identXREF
};
enum imageAtt {
    imageCLASS, imageDEFINITIONURL, imageENCODING, imageID, imageSTYLE, 
    imageXLINK_HREF, imageXREF
};
enum imaginaryAtt {
    imaginaryCLASS, imaginaryDEFINITIONURL, imaginaryENCODING, imaginaryID, 
    imaginarySTYLE, imaginaryXLINK_HREF, imaginaryXREF
};
enum imaginaryiAtt {
    imaginaryiCLASS, imaginaryiDEFINITIONURL, imaginaryiENCODING, 
    imaginaryiID, imaginaryiSTYLE, imaginaryiXLINK_HREF, imaginaryiXREF
};
enum impliesAtt {
    impliesCLASS, impliesDEFINITIONURL, impliesENCODING, impliesID, 
    impliesSTYLE, impliesXLINK_HREF, impliesXREF
};
enum inAtt {
    inCLASS, inDEFINITIONURL, inENCODING, inID, inSTYLE, inXLINK_HREF, 
    inXREF
};
enum infinityAtt {
    infinityCLASS, infinityDEFINITIONURL, infinityENCODING, infinityID, 
    infinitySTYLE, infinityXLINK_HREF, infinityXREF
};
enum intAtt {
    intCLASS, intDEFINITIONURL, intENCODING, intID, intSTYLE, 
    intXLINK_HREF, intXREF
};
enum integersAtt {
    integersCLASS, integersDEFINITIONURL, integersENCODING, integersID, 
    integersSTYLE, integersXLINK_HREF, integersXREF
};
enum intersectAtt {
    intersectCLASS, intersectDEFINITIONURL, intersectENCODING, intersectID, 
    intersectSTYLE, intersectXLINK_HREF, intersectXREF
};
enum intervalAtt {
    intervalCLASS, intervalCLOSURE, intervalID, intervalSTYLE, 
    intervalXLINK_HREF, intervalXREF
};
enum inverseAtt {
    inverseCLASS, inverseDEFINITIONURL, inverseENCODING, inverseID, 
    inverseSTYLE, inverseXLINK_HREF, inverseXREF
};
enum lambdaAtt {
    lambdaCLASS, lambdaID, lambdaSTYLE, lambdaXLINK_HREF, lambdaXREF
};
enum laplacianAtt {
    laplacianCLASS, laplacianDEFINITIONURL, laplacianENCODING, laplacianID, 
    laplacianSTYLE, laplacianXLINK_HREF, laplacianXREF
};
enum lcmAtt {
    lcmCLASS, lcmDEFINITIONURL, lcmENCODING, lcmID, lcmSTYLE, 
    lcmXLINK_HREF, lcmXREF
};
enum leqAtt {
    leqCLASS, leqDEFINITIONURL, leqENCODING, leqID, leqSTYLE, 
    leqXLINK_HREF, leqXREF
};
enum limitAtt {
    limitCLASS, limitDEFINITIONURL, limitENCODING, limitID, limitSTYLE, 
    limitXLINK_HREF, limitXREF
};
enum listAtt {
    listCLASS, listID, listORDER, listSTYLE, listXLINK_HREF, listXREF
};
enum lnAtt {
    lnCLASS, lnDEFINITIONURL, lnENCODING, lnID, lnSTYLE, lnXLINK_HREF, 
    lnXREF
};
enum logAtt {
    logCLASS, logDEFINITIONURL, logENCODING, logID, logSTYLE, 
    logXLINK_HREF, logXREF
};
enum logbaseAtt {
    logbaseCLASS, logbaseID, logbaseSTYLE, logbaseXLINK_HREF, logbaseXREF
};
enum lowlimitAtt {
    lowlimitCLASS, lowlimitDEFINITIONURL, lowlimitENCODING, lowlimitID, 
    lowlimitSTYLE, lowlimitXLINK_HREF, lowlimitXREF
};
enum ltAtt {
    ltCLASS, ltDEFINITIONURL, ltENCODING, ltID, ltSTYLE, ltXLINK_HREF, 
    ltXREF
};
enum mactionAtt {
    mactionACTIONTYPE, mactionCLASS, mactionID, mactionSELECTION, 
    mactionSTYLE, mactionXLINK_HREF, mactionXREF
};
enum maligngroupAtt {
    maligngroupCLASS, maligngroupGROUPALIGN, maligngroupID, 
    maligngroupSTYLE, maligngroupXLINK_HREF, maligngroupXREF
};
enum malignmarkAtt {
    malignmarkCLASS, malignmarkEDGE, malignmarkID, malignmarkSTYLE, 
    malignmarkXLINK_HREF, malignmarkXREF
};
enum mathAtt {
    mathALTIMG, mathALTTEXT, mathBASELINE, mathCLASS, mathDISPLAY, 
    mathHEIGHT, mathID, mathMACROS, mathNAME, mathOVERFLOW, mathSTYLE, 
    mathTYPE, mathWIDTH, mathXLINK_HREF, mathXREF
};
enum matrixAtt {
    matrixCLASS, matrixID, matrixSTYLE, matrixXLINK_HREF, matrixXREF
};
enum matrixrowAtt {
    matrixrowCLASS, matrixrowID, matrixrowSTYLE, matrixrowXLINK_HREF, 
    matrixrowXREF
};
enum maxAtt {
    maxCLASS, maxDEFINITIONURL, maxENCODING, maxID, maxSTYLE, 
    maxXLINK_HREF, maxXREF
};
enum meanAtt {
    meanCLASS, meanDEFINITIONURL, meanENCODING, meanID, meanSTYLE, 
    meanXLINK_HREF, meanXREF
};
enum medianAtt {
    medianCLASS, medianDEFINITIONURL, medianENCODING, medianID, 
    medianSTYLE, medianXLINK_HREF, medianXREF
};
enum mencloseAtt {
    mencloseCLASS, mencloseID, mencloseNOTATION, mencloseSTYLE, 
    mencloseXLINK_HREF, mencloseXREF
};
enum merrorAtt {
    merrorCLASS, merrorID, merrorSTYLE, merrorXLINK_HREF, merrorXREF
};
enum mfencedAtt {
    mfencedCLASS, mfencedCLOSE, mfencedID, mfencedOPEN, mfencedSEPARATORS, 
    mfencedSTYLE, mfencedXLINK_HREF, mfencedXREF
};
enum mfracAtt {
    mfracBEVELLED, mfracCLASS, mfracDENOMALIGN, mfracID, 
    mfracLINETHICKNESS, mfracNUMALIGN, mfracSTYLE, mfracXLINK_HREF, 
    mfracXREF
};
enum mglyphAtt {
    mglyphALT, mglyphFONTFAMILY, mglyphINDEX
};
enum miAtt {
    miCLASS, miID, miMATHBACKGROUND, miMATHCOLOR, miMATHSIZE, 
    miMATHVARIANT, miSTYLE, miXLINK_HREF, miXREF
};
enum minAtt {
    minCLASS, minDEFINITIONURL, minENCODING, minID, minSTYLE, 
    minXLINK_HREF, minXREF
};
enum minusAtt {
    minusCLASS, minusDEFINITIONURL, minusENCODING, minusID, minusSTYLE, 
    minusXLINK_HREF, minusXREF
};
enum mlabeledtrAtt {
    mlabeledtrCLASS, mlabeledtrCOLUMNALIGN, mlabeledtrGROUPALIGN, 
    mlabeledtrID, mlabeledtrROWALIGN, mlabeledtrSTYLE, 
    mlabeledtrXLINK_HREF, mlabeledtrXREF
};
enum mmultiscriptsAtt {
    mmultiscriptsCLASS, mmultiscriptsID, mmultiscriptsSTYLE, 
    mmultiscriptsXLINK_HREF, mmultiscriptsXREF
};
enum mnAtt {
    mnCLASS, mnID, mnMATHBACKGROUND, mnMATHCOLOR, mnMATHSIZE, 
    mnMATHVARIANT, mnSTYLE, mnXLINK_HREF, mnXREF
};
enum moAtt {
    moACCENT, moCLASS, moFENCE, moFORM, moID, moLARGEOP, moLSPACE, 
    moMATHBACKGROUND, moMATHCOLOR, moMATHSIZE, moMATHVARIANT, moMAXSIZE, 
    moMINSIZE, moMOVABLELIMITS, moRSPACE, moSEPARATOR, moSTRETCHY, moSTYLE, 
    moSYMMETRIC, moXLINK_HREF, moXREF
};
enum modeAtt {
    modeCLASS, modeDEFINITIONURL, modeENCODING, modeID, modeSTYLE, 
    modeXLINK_HREF, modeXREF
};
enum momentAtt {
    momentCLASS, momentDEFINITIONURL, momentENCODING, momentID, 
    momentSTYLE, momentXLINK_HREF, momentXREF
};
enum momentaboutAtt {
    momentaboutCLASS, momentaboutDEFINITIONURL, momentaboutENCODING, 
    momentaboutID, momentaboutSTYLE, momentaboutXLINK_HREF, 
    momentaboutXREF
};
enum moverAtt {
    moverACCENT, moverCLASS, moverID, moverSTYLE, moverXLINK_HREF, 
    moverXREF
};
enum mpaddedAtt {
    mpaddedCLASS, mpaddedDEPTH, mpaddedHEIGHT, mpaddedID, mpaddedLSPACE, 
    mpaddedSTYLE, mpaddedWIDTH, mpaddedXLINK_HREF, mpaddedXREF
};
enum mphantomAtt {
    mphantomCLASS, mphantomID, mphantomSTYLE, mphantomXLINK_HREF, 
    mphantomXREF
};
enum mprescriptsAtt {
    
};
enum mrootAtt {
    mrootCLASS, mrootID, mrootSTYLE, mrootXLINK_HREF, mrootXREF
};
enum mrowAtt {
    mrowCLASS, mrowID, mrowSTYLE, mrowXLINK_HREF, mrowXREF
};
enum msAtt {
    msCLASS, msID, msLQUOTE, msMATHBACKGROUND, msMATHCOLOR, msMATHSIZE, 
    msMATHVARIANT, msRQUOTE, msSTYLE, msXLINK_HREF, msXREF
};
enum mspaceAtt {
    mspaceCLASS, mspaceDEPTH, mspaceHEIGHT, mspaceID, mspaceLINEBREAK, 
    mspaceSTYLE, mspaceWIDTH, mspaceXLINK_HREF, mspaceXREF
};
enum msqrtAtt {
    msqrtCLASS, msqrtID, msqrtSTYLE, msqrtXLINK_HREF, msqrtXREF
};
enum mstyleAtt {
    mstyleACCENT, mstyleBACKGROUND, mstyleCLASS, mstyleCOLOR, 
    mstyleDISPLAYSTYLE, mstyleFENCE, mstyleFORM, mstyleID, mstyleLARGEOP, 
    mstyleLINETHICKNESS, mstyleLSPACE, mstyleMATHBACKGROUND, 
    mstyleMATHCOLOR, mstyleMATHSIZE, mstyleMATHVARIANT, mstyleMAXSIZE, 
    mstyleMEDIUMMATHSPACE, mstyleMINSIZE, mstyleMOVABLELIMITS, 
    mstyleRSPACE, mstyleSCRIPTLEVEL, mstyleSCRIPTMINSIZE, 
    mstyleSCRIPTSIZEMULTIPLIER, mstyleSEPARATOR, mstyleSTRETCHY, 
    mstyleSTYLE, mstyleSYMMETRIC, mstyleTHICKMATHSPACE, 
    mstyleTHINMATHSPACE, mstyleVERYTHICKMATHSPACE, mstyleVERYTHINMATHSPACE, 
    mstyleVERYVERYTHICKMATHSPACE, mstyleVERYVERYTHINMATHSPACE, 
    mstyleXLINK_HREF, mstyleXREF
};
enum msubAtt {
    msubCLASS, msubID, msubSTYLE, msubSUBSCRIPTSHIFT, msubXLINK_HREF, 
    msubXREF
};
enum msubsupAtt {
    msubsupCLASS, msubsupID, msubsupSTYLE, msubsupSUBSCRIPTSHIFT, 
    msubsupSUPERSCRIPTSHIFT, msubsupXLINK_HREF, msubsupXREF
};
enum msupAtt {
    msupCLASS, msupID, msupSTYLE, msupSUPERSCRIPTSHIFT, msupXLINK_HREF, 
    msupXREF
};
enum mtableAtt {
    mtableALIGN, mtableALIGNMENTSCOPE, mtableCLASS, mtableCOLUMNALIGN, 
    mtableCOLUMNLINES, mtableCOLUMNSPACING, mtableCOLUMNWIDTH, 
    mtableDISPLAYSTYLE, mtableEQUALCOLUMNS, mtableEQUALROWS, mtableFRAME, 
    mtableFRAMESPACING, mtableGROUPALIGN, mtableID, mtableMINLABELSPACING, 
    mtableROWALIGN, mtableROWLINES, mtableROWSPACING, mtableSIDE, 
    mtableSTYLE, mtableWIDTH, mtableXLINK_HREF, mtableXREF
};
enum mtdAtt {
    mtdCLASS, mtdCOLUMNALIGN, mtdCOLUMNSPAN, mtdGROUPALIGN, mtdID, 
    mtdROWALIGN, mtdROWSPAN, mtdSTYLE, mtdXLINK_HREF, mtdXREF
};
enum mtextAtt {
    mtextCLASS, mtextID, mtextMATHBACKGROUND, mtextMATHCOLOR, 
    mtextMATHSIZE, mtextMATHVARIANT, mtextSTYLE, mtextXLINK_HREF, 
    mtextXREF
};
enum mtrAtt {
    mtrCLASS, mtrCOLUMNALIGN, mtrGROUPALIGN, mtrID, mtrROWALIGN, mtrSTYLE, 
    mtrXLINK_HREF, mtrXREF
};
enum munderAtt {
    munderACCENTUNDER, munderCLASS, munderID, munderSTYLE, 
    munderXLINK_HREF, munderXREF
};
enum munderoverAtt {
    munderoverACCENT, munderoverACCENTUNDER, munderoverCLASS, munderoverID, 
    munderoverSTYLE, munderoverXLINK_HREF, munderoverXREF
};
enum naturalnumbersAtt {
    naturalnumbersCLASS, naturalnumbersDEFINITIONURL, 
    naturalnumbersENCODING, naturalnumbersID, naturalnumbersSTYLE, 
    naturalnumbersXLINK_HREF, naturalnumbersXREF
};
enum neqAtt {
    neqCLASS, neqDEFINITIONURL, neqENCODING, neqID, neqSTYLE, 
    neqXLINK_HREF, neqXREF
};
enum noneAtt {
    
};
enum notAtt {
    notCLASS, notDEFINITIONURL, notENCODING, notID, notSTYLE, 
    notXLINK_HREF, notXREF
};
enum notanumberAtt {
    notanumberCLASS, notanumberDEFINITIONURL, notanumberENCODING, 
    notanumberID, notanumberSTYLE, notanumberXLINK_HREF, notanumberXREF
};
enum notinAtt {
    notinCLASS, notinDEFINITIONURL, notinENCODING, notinID, notinSTYLE, 
    notinXLINK_HREF, notinXREF
};
enum notprsubsetAtt {
    notprsubsetCLASS, notprsubsetDEFINITIONURL, notprsubsetENCODING, 
    notprsubsetID, notprsubsetSTYLE, notprsubsetXLINK_HREF, 
    notprsubsetXREF
};
enum notsubsetAtt {
    notsubsetCLASS, notsubsetDEFINITIONURL, notsubsetENCODING, notsubsetID, 
    notsubsetSTYLE, notsubsetXLINK_HREF, notsubsetXREF
};
enum orAtt {
    orCLASS, orDEFINITIONURL, orENCODING, orID, orSTYLE, orXLINK_HREF, 
    orXREF
};
enum otherwiseAtt {
    otherwiseCLASS, otherwiseID, otherwiseSTYLE, otherwiseXLINK_HREF, 
    otherwiseXREF
};
enum outerproductAtt {
    outerproductCLASS, outerproductDEFINITIONURL, outerproductENCODING, 
    outerproductID, outerproductSTYLE, outerproductXLINK_HREF, 
    outerproductXREF
};
enum partialdiffAtt {
    partialdiffCLASS, partialdiffDEFINITIONURL, partialdiffENCODING, 
    partialdiffID, partialdiffSTYLE, partialdiffXLINK_HREF, 
    partialdiffXREF
};
enum piAtt {
    piCLASS, piDEFINITIONURL, piENCODING, piID, piSTYLE, piXLINK_HREF, 
    piXREF
};
enum pieceAtt {
    
};
enum piecewiseAtt {
    piecewiseCLASS, piecewiseID, piecewiseSTYLE, piecewiseXLINK_HREF, 
    piecewiseXREF
};
enum plusAtt {
    plusCLASS, plusDEFINITIONURL, plusENCODING, plusID, plusSTYLE, 
    plusXLINK_HREF, plusXREF
};
enum powerAtt {
    powerCLASS, powerDEFINITIONURL, powerENCODING, powerID, powerSTYLE, 
    powerXLINK_HREF, powerXREF
};
enum primesAtt {
    primesCLASS, primesDEFINITIONURL, primesENCODING, primesID, 
    primesSTYLE, primesXLINK_HREF, primesXREF
};
enum productAtt {
    productCLASS, productDEFINITIONURL, productENCODING, productID, 
    productSTYLE, productXLINK_HREF, productXREF
};
enum prsubsetAtt {
    prsubsetCLASS, prsubsetDEFINITIONURL, prsubsetENCODING, prsubsetID, 
    prsubsetSTYLE, prsubsetXLINK_HREF, prsubsetXREF
};
enum quotientAtt {
    quotientCLASS, quotientDEFINITIONURL, quotientENCODING, quotientID, 
    quotientSTYLE, quotientXLINK_HREF, quotientXREF
};
enum rationalsAtt {
    rationalsCLASS, rationalsDEFINITIONURL, rationalsENCODING, rationalsID, 
    rationalsSTYLE, rationalsXLINK_HREF, rationalsXREF
};
enum realAtt {
    realCLASS, realDEFINITIONURL, realENCODING, realID, realSTYLE, 
    realXLINK_HREF, realXREF
};
enum realsAtt {
    realsCLASS, realsDEFINITIONURL, realsENCODING, realsID, realsSTYLE, 
    realsXLINK_HREF, realsXREF
};
enum remAtt {
    remCLASS, remDEFINITIONURL, remENCODING, remID, remSTYLE, 
    remXLINK_HREF, remXREF
};
enum rootAtt {
    rootCLASS, rootDEFINITIONURL, rootENCODING, rootID, rootSTYLE, 
    rootXLINK_HREF, rootXREF
};
enum scalarproductAtt {
    scalarproductCLASS, scalarproductDEFINITIONURL, scalarproductENCODING, 
    scalarproductID, scalarproductSTYLE, scalarproductXLINK_HREF, 
    scalarproductXREF
};
enum sdevAtt {
    sdevCLASS, sdevDEFINITIONURL, sdevENCODING, sdevID, sdevSTYLE, 
    sdevXLINK_HREF, sdevXREF
};
enum secAtt {
    secCLASS, secDEFINITIONURL, secENCODING, secID, secSTYLE, 
    secXLINK_HREF, secXREF
};
enum sechAtt {
    sechCLASS, sechDEFINITIONURL, sechENCODING, sechID, sechSTYLE, 
    sechXLINK_HREF, sechXREF
};
enum selectorAtt {
    selectorCLASS, selectorDEFINITIONURL, selectorENCODING, selectorID, 
    selectorSTYLE, selectorXLINK_HREF, selectorXREF
};
enum semanticsAtt {
    semanticsCLASS, semanticsDEFINITIONURL, semanticsENCODING, semanticsID, 
    semanticsSTYLE, semanticsXLINK_HREF, semanticsXREF
};
enum sepAtt {
    
};
enum setAtt {
    setCLASS, setID, setSTYLE, setTYPE, setXLINK_HREF, setXREF
};
enum setdiffAtt {
    setdiffCLASS, setdiffDEFINITIONURL, setdiffENCODING, setdiffID, 
    setdiffSTYLE, setdiffXLINK_HREF, setdiffXREF
};
enum sinAtt {
    sinCLASS, sinDEFINITIONURL, sinENCODING, sinID, sinSTYLE, 
    sinXLINK_HREF, sinXREF
};
enum sinhAtt {
    sinhCLASS, sinhDEFINITIONURL, sinhENCODING, sinhID, sinhSTYLE, 
    sinhXLINK_HREF, sinhXREF
};
enum subsetAtt {
    subsetCLASS, subsetDEFINITIONURL, subsetENCODING, subsetID, 
    subsetSTYLE, subsetXLINK_HREF, subsetXREF
};
enum sumAtt {
    sumCLASS, sumDEFINITIONURL, sumENCODING, sumID, sumSTYLE, 
    sumXLINK_HREF, sumXREF
};
enum tanAtt {
    tanCLASS, tanDEFINITIONURL, tanENCODING, tanID, tanSTYLE, 
    tanXLINK_HREF, tanXREF
};
enum tanhAtt {
    tanhCLASS, tanhDEFINITIONURL, tanhENCODING, tanhID, tanhSTYLE, 
    tanhXLINK_HREF, tanhXREF
};
enum tendstoAtt {
    tendstoCLASS, tendstoDEFINITIONURL, tendstoENCODING, tendstoID, 
    tendstoSTYLE, tendstoTYPE, tendstoXLINK_HREF, tendstoXREF
};
enum timesAtt {
    timesCLASS, timesDEFINITIONURL, timesENCODING, timesID, timesSTYLE, 
    timesXLINK_HREF, timesXREF
};
enum transposeAtt {
    transposeCLASS, transposeDEFINITIONURL, transposeENCODING, transposeID, 
    transposeSTYLE, transposeXLINK_HREF, transposeXREF
};
enum trueAtt {
    trueCLASS, trueDEFINITIONURL, trueENCODING, trueID, trueSTYLE, 
    trueXLINK_HREF, trueXREF
};
enum unionAtt {
    unionCLASS, unionDEFINITIONURL, unionENCODING, unionID, unionSTYLE, 
    unionXLINK_HREF, unionXREF
};
enum uplimitAtt {
    uplimitCLASS, uplimitDEFINITIONURL, uplimitENCODING, uplimitID, 
    uplimitSTYLE, uplimitXLINK_HREF, uplimitXREF
};
enum varianceAtt {
    varianceCLASS, varianceDEFINITIONURL, varianceENCODING, varianceID, 
    varianceSTYLE, varianceXLINK_HREF, varianceXREF
};
enum vectorAtt {
    vectorCLASS, vectorID, vectorSTYLE, vectorXLINK_HREF, vectorXREF
};
enum vectorproductAtt {
    vectorproductCLASS, vectorproductDEFINITIONURL, vectorproductENCODING, 
    vectorproductID, vectorproductSTYLE, vectorproductXLINK_HREF, 
    vectorproductXREF
};
enum xorAtt {
    xorCLASS, xorDEFINITIONURL, xorENCODING, xorID, xorSTYLE, 
    xorXLINK_HREF, xorXREF
};
const uint numAttTypes = 8;
const uint numAttributes = 91;
extern const char * const elementTag[numElements];
extern const Attribute * const attList[numElements];
extern const uint attListLen[numElements];
extern const char * const attributeTag[numAttributes];
extern const AttributeType attTypes[91];
const uint absNumAtts = 7;
extern const Attribute absAtts[7];
const uint andNumAtts = 7;
extern const Attribute andAtts[7];
const uint annotationNumAtts = 6;
extern const Attribute annotationAtts[6];
const uint annotation_xmlNumAtts = 6;
extern const Attribute annotation_xmlAtts[6];
const uint applyNumAtts = 5;
extern const Attribute applyAtts[5];
const uint approxNumAtts = 7;
extern const Attribute approxAtts[7];
const uint arccosNumAtts = 7;
extern const Attribute arccosAtts[7];
const uint arccoshNumAtts = 7;
extern const Attribute arccoshAtts[7];
const uint arccotNumAtts = 7;
extern const Attribute arccotAtts[7];
const uint arccothNumAtts = 7;
extern const Attribute arccothAtts[7];
const uint arccscNumAtts = 7;
extern const Attribute arccscAtts[7];
const uint arccschNumAtts = 7;
extern const Attribute arccschAtts[7];
const uint arcsecNumAtts = 7;
extern const Attribute arcsecAtts[7];
const uint arcsechNumAtts = 7;
extern const Attribute arcsechAtts[7];
const uint arcsinNumAtts = 7;
extern const Attribute arcsinAtts[7];
const uint arcsinhNumAtts = 7;
extern const Attribute arcsinhAtts[7];
const uint arctanNumAtts = 7;
extern const Attribute arctanAtts[7];
const uint arctanhNumAtts = 7;
extern const Attribute arctanhAtts[7];
const uint argNumAtts = 7;
extern const Attribute argAtts[7];
const uint bvarNumAtts = 5;
extern const Attribute bvarAtts[5];
const uint cardNumAtts = 7;
extern const Attribute cardAtts[7];
const uint cartesianproductNumAtts = 7;
extern const Attribute cartesianproductAtts[7];
const uint ceilingNumAtts = 7;
extern const Attribute ceilingAtts[7];
const uint ciNumAtts = 8;
extern const Attribute ciAtts[8];
const uint cnNumAtts = 9;
extern const Attribute cnAtts[9];
const uint codomainNumAtts = 7;
extern const Attribute codomainAtts[7];
const uint complexesNumAtts = 7;
extern const Attribute complexesAtts[7];
const uint composeNumAtts = 7;
extern const Attribute composeAtts[7];
const uint conditionNumAtts = 2;
extern const Attribute conditionAtts[2];
const uint conjugateNumAtts = 7;
extern const Attribute conjugateAtts[7];
const uint cosNumAtts = 7;
extern const Attribute cosAtts[7];
const uint coshNumAtts = 7;
extern const Attribute coshAtts[7];
const uint cotNumAtts = 7;
extern const Attribute cotAtts[7];
const uint cothNumAtts = 7;
extern const Attribute cothAtts[7];
const uint cscNumAtts = 7;
extern const Attribute cscAtts[7];
const uint cschNumAtts = 7;
extern const Attribute cschAtts[7];
const uint csymbolNumAtts = 7;
extern const Attribute csymbolAtts[7];
const uint curlNumAtts = 7;
extern const Attribute curlAtts[7];
const uint declareNumAtts = 6;
extern const Attribute declareAtts[6];
const uint degreeNumAtts = 5;
extern const Attribute degreeAtts[5];
const uint determinantNumAtts = 7;
extern const Attribute determinantAtts[7];
const uint diffNumAtts = 7;
extern const Attribute diffAtts[7];
const uint divergenceNumAtts = 7;
extern const Attribute divergenceAtts[7];
const uint divideNumAtts = 7;
extern const Attribute divideAtts[7];
const uint domainNumAtts = 7;
extern const Attribute domainAtts[7];
const uint domainofapplicationNumAtts = 7;
extern const Attribute domainofapplicationAtts[7];
const uint emptysetNumAtts = 7;
extern const Attribute emptysetAtts[7];
const uint eqNumAtts = 7;
extern const Attribute eqAtts[7];
const uint equivalentNumAtts = 7;
extern const Attribute equivalentAtts[7];
const uint eulergammaNumAtts = 7;
extern const Attribute eulergammaAtts[7];
const uint existsNumAtts = 7;
extern const Attribute existsAtts[7];
const uint expNumAtts = 7;
extern const Attribute expAtts[7];
const uint exponentialeNumAtts = 7;
extern const Attribute exponentialeAtts[7];
const uint factorialNumAtts = 7;
extern const Attribute factorialAtts[7];
const uint factorofNumAtts = 7;
extern const Attribute factorofAtts[7];
const uint falseNumAtts = 7;
extern const Attribute falseAtts[7];
const uint floorNumAtts = 7;
extern const Attribute floorAtts[7];
const uint forallNumAtts = 7;
extern const Attribute forallAtts[7];
const uint gcdNumAtts = 7;
extern const Attribute gcdAtts[7];
const uint geqNumAtts = 7;
extern const Attribute geqAtts[7];
const uint gradNumAtts = 7;
extern const Attribute gradAtts[7];
const uint gtNumAtts = 7;
extern const Attribute gtAtts[7];
const uint identNumAtts = 7;
extern const Attribute identAtts[7];
const uint imageNumAtts = 7;
extern const Attribute imageAtts[7];
const uint imaginaryNumAtts = 7;
extern const Attribute imaginaryAtts[7];
const uint imaginaryiNumAtts = 7;
extern const Attribute imaginaryiAtts[7];
const uint impliesNumAtts = 7;
extern const Attribute impliesAtts[7];
const uint inNumAtts = 7;
extern const Attribute inAtts[7];
const uint infinityNumAtts = 7;
extern const Attribute infinityAtts[7];
const uint intNumAtts = 7;
extern const Attribute intAtts[7];
const uint integersNumAtts = 7;
extern const Attribute integersAtts[7];
const uint intersectNumAtts = 7;
extern const Attribute intersectAtts[7];
const uint intervalNumAtts = 6;
extern const Attribute intervalAtts[6];
const uint inverseNumAtts = 7;
extern const Attribute inverseAtts[7];
const uint lambdaNumAtts = 5;
extern const Attribute lambdaAtts[5];
const uint laplacianNumAtts = 7;
extern const Attribute laplacianAtts[7];
const uint lcmNumAtts = 7;
extern const Attribute lcmAtts[7];
const uint leqNumAtts = 7;
extern const Attribute leqAtts[7];
const uint limitNumAtts = 7;
extern const Attribute limitAtts[7];
const uint listNumAtts = 6;
extern const Attribute listAtts[6];
const uint lnNumAtts = 7;
extern const Attribute lnAtts[7];
const uint logNumAtts = 7;
extern const Attribute logAtts[7];
const uint logbaseNumAtts = 5;
extern const Attribute logbaseAtts[5];
const uint lowlimitNumAtts = 7;
extern const Attribute lowlimitAtts[7];
const uint ltNumAtts = 7;
extern const Attribute ltAtts[7];
const uint mactionNumAtts = 7;
extern const Attribute mactionAtts[7];
const uint maligngroupNumAtts = 6;
extern const Attribute maligngroupAtts[6];
const uint malignmarkNumAtts = 6;
extern const Attribute malignmarkAtts[6];
const uint mathNumAtts = 15;
extern const Attribute mathAtts[15];
const uint matrixNumAtts = 5;
extern const Attribute matrixAtts[5];
const uint matrixrowNumAtts = 5;
extern const Attribute matrixrowAtts[5];
const uint maxNumAtts = 7;
extern const Attribute maxAtts[7];
const uint meanNumAtts = 7;
extern const Attribute meanAtts[7];
const uint medianNumAtts = 7;
extern const Attribute medianAtts[7];
const uint mencloseNumAtts = 6;
extern const Attribute mencloseAtts[6];
const uint merrorNumAtts = 5;
extern const Attribute merrorAtts[5];
const uint mfencedNumAtts = 8;
extern const Attribute mfencedAtts[8];
const uint mfracNumAtts = 9;
extern const Attribute mfracAtts[9];
const uint mglyphNumAtts = 3;
extern const Attribute mglyphAtts[3];
const uint miNumAtts = 9;
extern const Attribute miAtts[9];
const uint minNumAtts = 7;
extern const Attribute minAtts[7];
const uint minusNumAtts = 7;
extern const Attribute minusAtts[7];
const uint mlabeledtrNumAtts = 8;
extern const Attribute mlabeledtrAtts[8];
const uint mmultiscriptsNumAtts = 5;
extern const Attribute mmultiscriptsAtts[5];
const uint mnNumAtts = 9;
extern const Attribute mnAtts[9];
const uint moNumAtts = 21;
extern const Attribute moAtts[21];
const uint modeNumAtts = 7;
extern const Attribute modeAtts[7];
const uint momentNumAtts = 7;
extern const Attribute momentAtts[7];
const uint momentaboutNumAtts = 7;
extern const Attribute momentaboutAtts[7];
const uint moverNumAtts = 6;
extern const Attribute moverAtts[6];
const uint mpaddedNumAtts = 9;
extern const Attribute mpaddedAtts[9];
const uint mphantomNumAtts = 5;
extern const Attribute mphantomAtts[5];
const uint mprescriptsNumAtts = 0;
extern const Attribute mprescriptsAtts[1];
const uint mrootNumAtts = 5;
extern const Attribute mrootAtts[5];
const uint mrowNumAtts = 5;
extern const Attribute mrowAtts[5];
const uint msNumAtts = 11;
extern const Attribute msAtts[11];
const uint mspaceNumAtts = 9;
extern const Attribute mspaceAtts[9];
const uint msqrtNumAtts = 5;
extern const Attribute msqrtAtts[5];
const uint mstyleNumAtts = 35;
extern const Attribute mstyleAtts[35];
const uint msubNumAtts = 6;
extern const Attribute msubAtts[6];
const uint msubsupNumAtts = 7;
extern const Attribute msubsupAtts[7];
const uint msupNumAtts = 6;
extern const Attribute msupAtts[6];
const uint mtableNumAtts = 23;
extern const Attribute mtableAtts[23];
const uint mtdNumAtts = 10;
extern const Attribute mtdAtts[10];
const uint mtextNumAtts = 9;
extern const Attribute mtextAtts[9];
const uint mtrNumAtts = 8;
extern const Attribute mtrAtts[8];
const uint munderNumAtts = 6;
extern const Attribute munderAtts[6];
const uint munderoverNumAtts = 7;
extern const Attribute munderoverAtts[7];
const uint naturalnumbersNumAtts = 7;
extern const Attribute naturalnumbersAtts[7];
const uint neqNumAtts = 7;
extern const Attribute neqAtts[7];
const uint noneNumAtts = 0;
extern const Attribute noneAtts[1];
const uint notNumAtts = 7;
extern const Attribute notAtts[7];
const uint notanumberNumAtts = 7;
extern const Attribute notanumberAtts[7];
const uint notinNumAtts = 7;
extern const Attribute notinAtts[7];
const uint notprsubsetNumAtts = 7;
extern const Attribute notprsubsetAtts[7];
const uint notsubsetNumAtts = 7;
extern const Attribute notsubsetAtts[7];
const uint orNumAtts = 7;
extern const Attribute orAtts[7];
const uint otherwiseNumAtts = 5;
extern const Attribute otherwiseAtts[5];
const uint outerproductNumAtts = 7;
extern const Attribute outerproductAtts[7];
const uint partialdiffNumAtts = 7;
extern const Attribute partialdiffAtts[7];
const uint piNumAtts = 7;
extern const Attribute piAtts[7];
const uint pieceNumAtts = 0;
extern const Attribute pieceAtts[1];
const uint piecewiseNumAtts = 5;
extern const Attribute piecewiseAtts[5];
const uint plusNumAtts = 7;
extern const Attribute plusAtts[7];
const uint powerNumAtts = 7;
extern const Attribute powerAtts[7];
const uint primesNumAtts = 7;
extern const Attribute primesAtts[7];
const uint productNumAtts = 7;
extern const Attribute productAtts[7];
const uint prsubsetNumAtts = 7;
extern const Attribute prsubsetAtts[7];
const uint quotientNumAtts = 7;
extern const Attribute quotientAtts[7];
const uint rationalsNumAtts = 7;
extern const Attribute rationalsAtts[7];
const uint realNumAtts = 7;
extern const Attribute realAtts[7];
const uint realsNumAtts = 7;
extern const Attribute realsAtts[7];
const uint remNumAtts = 7;
extern const Attribute remAtts[7];
const uint rootNumAtts = 7;
extern const Attribute rootAtts[7];
const uint scalarproductNumAtts = 7;
extern const Attribute scalarproductAtts[7];
const uint sdevNumAtts = 7;
extern const Attribute sdevAtts[7];
const uint secNumAtts = 7;
extern const Attribute secAtts[7];
const uint sechNumAtts = 7;
extern const Attribute sechAtts[7];
const uint selectorNumAtts = 7;
extern const Attribute selectorAtts[7];
const uint semanticsNumAtts = 7;
extern const Attribute semanticsAtts[7];
const uint sepNumAtts = 0;
extern const Attribute sepAtts[1];
const uint setNumAtts = 6;
extern const Attribute setAtts[6];
const uint setdiffNumAtts = 7;
extern const Attribute setdiffAtts[7];
const uint sinNumAtts = 7;
extern const Attribute sinAtts[7];
const uint sinhNumAtts = 7;
extern const Attribute sinhAtts[7];
const uint subsetNumAtts = 7;
extern const Attribute subsetAtts[7];
const uint sumNumAtts = 7;
extern const Attribute sumAtts[7];
const uint tanNumAtts = 7;
extern const Attribute tanAtts[7];
const uint tanhNumAtts = 7;
extern const Attribute tanhAtts[7];
const uint tendstoNumAtts = 8;
extern const Attribute tendstoAtts[8];
const uint timesNumAtts = 7;
extern const Attribute timesAtts[7];
const uint transposeNumAtts = 7;
extern const Attribute transposeAtts[7];
const uint trueNumAtts = 7;
extern const Attribute trueAtts[7];
const uint unionNumAtts = 7;
extern const Attribute unionAtts[7];
const uint uplimitNumAtts = 7;
extern const Attribute uplimitAtts[7];
const uint varianceNumAtts = 7;
extern const Attribute varianceAtts[7];
const uint vectorNumAtts = 5;
extern const Attribute vectorAtts[5];
const uint vectorproductNumAtts = 7;
extern const Attribute vectorproductAtts[7];
const uint xorNumAtts = 7;
extern const Attribute xorAtts[7];
int createAttribute(const char *, const DOMString &value, Element e, const MMLAttribute **att);
int createAttribute(const Attribute, const DOMString &value, Element e, const MMLAttribute **att);
MMLAttribute *createAttribute(const Attribute a, const DOMString &value);
MMLAttribute *createBOOL(const DOMString &, Attribute);
MMLAttribute *createDOMSTRING(const DOMString &, Attribute);
MMLAttribute *createFLOAT(const DOMString &, Attribute);
MMLAttribute *createH_UNIT(const DOMString &, Attribute);
MMLAttribute *createINT(const DOMString &, Attribute);
MMLAttribute *createMATHCOLOR(const DOMString &, Attribute);
MMLAttribute *createMATHVARIANT(const DOMString &, Attribute);
MMLAttribute *createV_UNIT(const DOMString &, Attribute);
extern MMLAttribute * (* const attFunc[numAttTypes])(const DOMString &, Attribute);
}
#endif
