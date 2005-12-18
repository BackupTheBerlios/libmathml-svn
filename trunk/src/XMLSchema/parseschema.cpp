/* MathML Schema parser and C++ code generator.
 *
 * (c) Jos van den Oever 2003
 *
 * This program reads the MathML Schema specification for the MathML 2.0
 * It has been tested with the 2002 Schema verions by St&#233;phane Dalmas.
 *
 * Purpose:
 * To generate C++ code that describes
 * 1 which elements may contain which attributes
 * 2 contains partial information on how to parse each attribute
 *
 */

#include <QFile>
#include <QFileInfo>
#include <QDomElement>
#include <QDomNode>
#include <QTextStream>
#include <QDir>
#include <iostream>
using std::endl;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <set>
using std::set;
#include <map>
using std::map;
using std::pair;
using std::multimap;
#include <string>
using std::string;
#include <list>
using std::list;

struct attributeinfo {
    QString type;
    QString deflt;
};

struct elementinfo {
    QDomElement type;
    map<QString, attributeinfo> atts;
};

// After parsing the Schema, this map contains all the information from it,
// that we need.
map<QString, elementinfo> elements;

// this list contains information from a file 'custattlist' that links
// each attribute name to its type. Attributes with equal name but belonging
// to different elements are assumed to have the same type. Any differentiation
// has to programmed by hand
map<QString, QString> custattlist;

// to avoid a lot of similar error messages, we remember the attributes, we've
// already complained about in this set
set<QString> notfoundattribs;

// convenient global variable with the dir where the schema files are
QString dir;

QTextStream out(stdout);
QTextStream err(stderr);


// debugging function that prints the attributes of an element
void
printAttributes(QDomElement e, uint level) {
    QDomNamedNodeMap m = e.attributes();
    for (uint i=0; i<m.length(); ++i) {
        for (uint j=0; j<level; ++j) out << ' ';
        QDomNode n = m.item(i);
        out << "+"<<n.nodeName() << ": "
            << n.nodeValue() << endl;
    }
}
// debugging function that visualises the xml structure
void
printNode(QDomNode n, uint level) {
    while (!n.isNull()) {
        for (uint i=0; i<level; ++i) out << ' ';
        out << n.nodeName() << endl;
        if (n.isElement()) {
            QDomElement e = n.toElement();
            printAttributes(e, level+2);
        }
        if (n.hasChildNodes()) {
            printNode(n.firstChild(), level+1);
        }
        n = n.nextSibling();
    }
}
// function that loads an XML document into a QDomDocument object
QDomDocument
loadDocument(QString p) {
    QFile f(p);
    f.open(QIODevice::ReadOnly);
    QDomDocument d;
    QString err;
    d.setContent(&f, true);
    return d;
}
// function that parses an XML DOM for 'xs:include' directives and loads
// and inserts the mentioned documents into it
void
load(QDomNode n) {
    while (!n.isNull()) {
        if (n.hasChildNodes()) {
            load(n.firstChild());
        }
        if (n.nodeName() == "xs:include") {
            QString f = n.toElement().attribute("schemaLocation");
            QDomDocument d = loadDocument(dir+"/"+f);
            QDomDocument o = n.ownerDocument();
            QDomNode newn = o.importNode(d.documentElement(), true);
            QDomNode p = n.parentNode();
            QDomNode old = n;
            n = n.nextSibling();
            p.removeChild(old);
            while (!newn.firstChild().isNull()) {
                p.insertBefore(newn.firstChild(), n);
            }
        } else {
            n = n.nextSibling();
        }
    }
}
// function that looks for an XML element with the attribute 'name' that has
// the wanted value. When the element is found it is copied into argument 't'
// and the rest of the tree is parsed. When more elements with the name
// are found an error is reported
void
findTypeElement(QString type, QDomNode n, QDomElement &t) {
    while (!n.isNull()) {
        if (n.toElement().attribute("name") == type) {
            if (t.isNull()) {
                t = n.toElement();
            } else {
                err << "Hmm, there are more elements with"
                    << "name=\"" << type << "\"." << endl;
            }
        }
        if (n.hasChildNodes()) {
            findTypeElement(type, n.firstChild(), t);
        }
        n = n.nextSibling();
    }
}
// in Schema, the 'type' attribute can be more complicated than a single string
// This functions harvests this more complicated information by concatenating
// all relevant strings describing the type.
QString
makeType(QDomElement e) {
    QString type;
    if (e.tagName() != "simpleType") {
        err << "not a simple type!!" << endl;
    } else {
        QDomNode n = e.firstChild();
        e = n.toElement();
        if (e.isNull()) {
            err << "Hmm, this simpleType is empty." << endl;
        }
        if (e.tagName() == "union") {
            type = e.attribute("memberTypes");
        } else {
            if (e.tagName() != "restriction") {
                err << "Hmm, I expected a restriction element."
                    << endl;
            }
            QDomNode tn = e.firstChild();
            while (!tn.isNull()) {
                if (tn.isElement()) {
                    if (type != "") {
                        type += " | ";
                    }
                    type += tn.toElement().attribute("value");
                }
                tn = tn.nextSibling();
            }
        }
        if (!n.nextSibling().isNull()) {
            err << "Hmm, I expected only one child. Info might be"
                << " lost." << endl;
        }
    }
    return type;
}
// function that tries to extract a type from an 'attribute' element
// either the elements defines the type itself, or it is defined elsewhere
// in that case, the attribute 'ref' points to the node containing the
// definition
QDomElement
findAttElement(QDomElement e) {
    QDomNode d = e.ownerDocument().documentElement();
    QString ref = e.attribute("ref");
    QDomElement t;
    if (ref.isNull()) {
        // the element has no ref attribute: we scan it's children
        t = e;
        QString type = makeType(e.firstChild().toElement());
        if (type.isNull()) {
            err << "did not find a type" << endl;
        }
        t.setAttribute("type", type);
    } else {
        findTypeElement(ref, d, t);
        if (t.isNull()) {
            if (notfoundattribs.find("name") ==
                    notfoundattribs.end()) {
                err << "Hmm, no element with name '" << ref
                    << "' was found." << endl;
                notfoundattribs.insert("name");
            }
            t = e;
            t.setAttribute("name", ref);
        }
    }
    return t;
}
// recursive function that scans the DOM for attribute tags and stores their
// name, type and default value in a global variable
void
collectAttributes(QDomNode n, map<QString, attributeinfo> &l) {
    while (!n.isNull()) {
        if (n.isElement()
            && n.toElement().tagName() == "attributeGroup") {
            QString name = n.toElement().attribute("ref");
            if (name.isNull()) {
                err << "Hmm, this group has a ref without a "
                    << "defined element." << endl;
            }
            QDomElement g;
            findTypeElement(name,
                n.ownerDocument().documentElement(), g);
            if (g.isNull()) {
                err << "Hmm, no element with name=\""
                    <<name<<"\" was found." << endl;
            }
            collectAttributes(g.firstChild(), l);
        } else if (n.toElement().tagName() == "attribute") {
            QDomElement e = n.toElement();
            QString type = e.attribute("type");
            if (type.isNull()) {
                e = findAttElement(e);
                type = e.attribute("type");
            }
            QString name = e.attribute("name");
            pair<QString, attributeinfo> ai;
            ai.first = name;
            ai.second.type = type;
            ai.second.deflt = e.attribute("default");
            if (name.isNull()) {
                err << "grr. still no name or type" << endl;
            }
            l.insert(ai);
        }
        n = n.nextSibling();
    }
}
// function that scans the DOM for all 'attribute' elements
void
findAttributeElements(QDomElement e) {
    // in the mathml spec, e never has children
    if (!e.firstChild().isNull()) {
        err << "Hmm, I did not expect childeren." << endl;
    }
    // check that there are only two attributes: name and type
    if (e.attributes().length() != 2 || !e.hasAttribute("type")) {
        err << "Hmm, I expected two children for element elements."
            << endl;
    }
    QString type = e.attribute("type");
    // find the element with the name type
    QDomElement typee;
    findTypeElement(type, e.ownerDocument().documentElement(),
            typee);
    if (typee.isNull()) {
        err << "Hmm, no element with name=\""<<type<<"\" was found."
            << endl;
    }
    elements[e.attribute("name")].type = typee;
    collectAttributes(typee.firstChild(),
            elements[e.attribute("name")].atts);
    //pmrintAttributes(e, 10);
}
// function that scans the DOM for all 'element' elements.
void
findElements(QDomDocument d) {
    QDomNodeList l = d.elementsByTagName("element");
    for (uint i=0; i<l.length(); ++i) {
        QDomElement e = l.item(i).toElement();
        if (e.hasAttribute("name")) {
            findAttributeElements(e);
        }
    }
}
#include <ios>
// function for printing a list of all attribute types encountered in the Schema
void
printAttributeTypes() {
    set<QString> types;
    map<QString, elementinfo>::iterator i;
    for (i=elements.begin(); i!=elements.end(); ++i) {
        map<QString, attributeinfo>::iterator j;
        for (j=i->second.atts.begin(); j!=i->second.atts.end(); ++j) {
            types.insert(j->second.type);
        }
    }
    set<QString>::iterator s;
    out << "attribute list" << endl;
    for (s = types.begin(); s != types.end(); ++s) {
        out << *s << endl;
    }
}
// function that prints a lines with an attribute name and its type
void
printAttributes() {
    multimap<QString, QString> atts;
    map<QString, elementinfo>::iterator i;
    // collect all data
    for (i=elements.begin(); i!=elements.end(); ++i) {
        map<QString, attributeinfo>::iterator j;
        for (j=i->second.atts.begin(); j!=i->second.atts.end(); ++j) {
            atts.insert(pair<QString, QString>(j->first,
                        j->second.type));
        }
    }
    // print the data
    multimap<QString, QString>::iterator s;
    for (s = atts.begin(); s != atts.end(); ++s) {
        out << s->first << '\t' << s->second << endl;
    }
}
using std::ios_base;
void
printData() {
    map<QString, elementinfo>::iterator i;
    for (i=elements.begin(); i!=elements.end(); ++i) {
        out << i->first << ":\n";
        map<QString, attributeinfo>::iterator j;
        for (j=i->second.atts.begin(); j!=i->second.atts.end(); ++j) {
            out << "\t";
            out.setFieldWidth(24);
            out.setFieldAlignment(QTextStream::AlignLeft);
            if (!j->first.isNull()) {
                out << j->first;
            } else {
                out << "";
            }
            out.setFieldAlignment(QTextStream::AlignRight);
            if (!j->second.type.isNull()) {
                out << j->second.type;
            } else {
                out << "";
            }
            out.setFieldWidth(0);
            if (!j->second.deflt.isNull()) {
                out << j->second.deflt;
            } else {
                out << "";
            }
            out << endl;
        }
    }
}
void
printList(const QString &pre, const QString &post, list<QString> &l,
        QTextStream &f) {
    f << "\t";
    list<QString>::const_iterator i;
    int left = 72;
    int d = 2 + pre.length() + post.length();
    for (i=l.begin(); i!=l.end(); ) {
        int len = i->length() + d;
        if (left < len) {
            f << "\n\t";
            left = 72;
        }
        f << pre << *i << post;
        if (++i != l.end()) {
            left -= len;
            f << ", ";
        }
    }
}
void
printList(const QString &pre, const QString &post, set<QString> &s,
        QTextStream &f) {
    set<QString>::const_iterator i;
    list<QString> l;
    for (i=s.begin(); i!=s.end(); ++i) {
        l.push_back(*i);
    }
    printList(pre, post, l, f);
}
QString
mkvar(const QString &s) {
    return s.toUpper().replace('-', '_').replace(':', '_');
}
void
writeCode() {
    set<QString> el;
    set<QString> ucel;
    set<QString> at;
    list<QString> defat;
    set<QString> ucat;
    map<QString, set<QString> > ucelat;
    map<QString, elementinfo>::iterator i;
    set<QString> atty;
    list<QString> ucatty;
    set<QString> ucats;
    for (i=elements.begin(); i!=elements.end(); ++i) {
        el.insert(i->first);
        ucel.insert(mkvar(i->first));
        QString elname = i->first;
        elname.replace("-", "_");
        set<QString> locelat;
        map<QString, attributeinfo>::iterator j;
        for (j=i->second.atts.begin(); j != i->second.atts.end(); ++j) {
            at.insert(j->first);
            ucat.insert(mkvar(j->first));
            locelat.insert(mkvar(j->first));
        }
        ucelat.insert(pair<QString, set<QString> >(elname, locelat));
    }
    set<QString>::iterator l;
    for (l = at.begin(); l != at.end(); ++l) {
        map<QString,QString>::iterator m = custattlist.find(*l);
        if (m != custattlist.end()) {
            atty.insert(m->second);
            QString uq = m->second;
            uq.remove(QRegExp(".*::"));
            uq = mkvar(uq);
            ucatty.push_back(uq);
            ucats.insert(mkvar(uq));
        } else {
            pair<QString, QString> p(*l, "DOMString");
            custattlist.insert(p);
            ucatty.push_back("DOMSTRING");
            ucats.insert("DOMSTRING");
        }
        defat.push_back("");
    }

    // print to public mathml.h file (the one that will be exported)
    // (since i forgot this file's purpose, i'm commenting it out)
    //ofstream f;
/*    f.open("elements.h");
    f << "// this file was automatically generated by 'parseschema'" << endl;
    f << "#ifndef ELEMENTS_H" << endl;
    f << "#define ELEMENTS_H" << endl;
    f << "namespace MML {" << endl;
    f << "enum Element {" << endl;
    printList("", "", ucel, f);
    f << "\n};" << endl;
    f << "const unsigned int numElements = " << el.size() << ";" << endl;
    f << "class Attributes;" << endl;
    f << "}" << endl;
    f << "#endif" << endl;
    f.close();*/

    // print to second, internal file: mathml.h
    //f.open("mathml.h");
    QFile file("mathml.h");
    file.open(QFile::WriteOnly  | QFile::Truncate);
    QTextStream f(&file);
    f << "// this file was automatically generated by 'parseschema'" << endl;
    f << "#ifndef MATHML_H" << endl;
    f << "#define MATHML_H" << endl;
    f << "typedef unsigned int uint;" << endl;
    f << "#include \"elements.h\"" << endl;
    f << "#include \"mathtypes.h\"" << endl;
    f << "namespace MML {" << endl;

    f << "enum AttributeType {" << endl;
    printList("", "_T", ucats, f);
    f << "\n};" << endl;

    f << "enum Attribute {" << endl;
    printList("", "", ucat, f);
    f << "\n};" << endl;
    f << "}" << endl;

    f << "class MMLAttribute {" << endl;
    f << "public:" << endl;
    f << "\tvirtual ~MMLAttribute() {}" << endl;
    f << "\tbool cleanup;" << endl;
//    f << "\tvirtual MMLAttribute *copy() const = 0;" << endl;
    f << "};" << endl;
    for (l = atty.begin(); l != atty.end(); ++l) {
        QString uq = *l;
        uq.remove(QRegExp(".*::"));
        f << "class MML" << uq << " : public MMLAttribute {" << endl;
        f << "public:" << endl;
        f << "\tMML" << uq << "(" << *l << ", bool c=true);" << endl;
        f << "\t" << *l << " value;" << endl;
//        f << "\tMML" << *l << "*copy() const;" << endl;
        f << "};" << endl;
    }

    f << "namespace MML {" << endl;
    map<QString, set<QString> >::iterator k;
    for (k = ucelat.begin(); k != ucelat.end(); ++k) {
        f << "enum " << k->first << "Att {" << endl;
        printList(k->first, "", k->second, f);
        f << "\n};" << endl;
    }
    f << "const uint numAttTypes = " << ucats.size() << ";"<<endl;
    f << "const uint numAttributes = " << at.size() << ";" << endl;
    f << "extern const char * const elementTag[numElements];" << endl;
    f << "extern const Attribute * const attList[numElements];" << endl;
    f << "extern const uint attListLen[numElements];" << endl;
    f << "extern const char * const attributeTag[numAttributes];"<< endl;
    f << "extern const AttributeType attTypes["
        << ucatty.size() << "];" << endl;
    for (k = ucelat.begin(); k != ucelat.end(); ++k) {
        uint size = k->second.size();
        f << "const uint " << k->first << "NumAtts = "
            << size << ";" <<endl;
        f << "extern const Attribute " << k->first << "Atts["
            << (size ?size :1) << "];" << endl;
    }
    f << "int createAttribute(const char *, "
        "const DOMString &value, Element e, const MMLAttribute **att);"
        << endl;
    f << "int createAttribute(const Attribute, "
        "const DOMString &value, Element e, const MMLAttribute **att);"
        << endl;
    f << "MMLAttribute *createAttribute(const Attribute a, "
        "const DOMString &value);" << endl;
    for (l = ucats.begin(); l != ucats.end(); ++l) {
        QString uq = *l;
        uq.remove(QRegExp(".*__"));
        f << "MMLAttribute *create" << uq
            << "(const DOMString &, Attribute);" << endl;
    }
    f << "extern MMLAttribute * (* const attFunc[numAttTypes])("
        "const DOMString &, Attribute);" << endl;
    f << "}" << endl;
    f << "#endif" << endl;
    f.flush();
    file.close();

    file.setFileName("mathml.cpp");
    file.open(QFile::WriteOnly  | QFile::Truncate);
    f.setDevice(&file);
    f << "// this file was automatically generated by 'parseschema'" << endl;
    f << "#include \"elements.h\"" << endl;
    f << "#include \"mathml.h\"" << endl;
    f << "using namespace MML;" << endl;
    for (l = atty.begin(); l != atty.end(); ++l) {
        QString uq = *l;
        uq.remove(QRegExp(".*::"));
        f << "MML" << uq << "::MML" << uq << "(" << *l
            << " v, bool c)\n\t\t: value(v) {cleanup=c;\n}" << endl;
//        f << "MML" << *l << " *" << endl;
//        f << "MML" << *l << "::copy() const {" << endl;
//        f << "\treturn new MML" << *l << "(value);" << endl;
//        f << "}" << endl;
    }
    f << "const char * const MML::elementTag[" << el.size() << "] = {"<<endl;
    printList("\"", "\"", el, f);
    f << "\n};" << endl;
    f << "const char * const MML::attributeTag["<<at.size()<<"] = {" <<endl;
    printList("\"", "\"", at, f);
    f << "\n};" << endl;
    f << "const AttributeType MML::attTypes[" << at.size()
        << "] = {"<<endl;
    printList("", "_T", ucatty, f);
    f << "\n};" << endl;
    set<QString> attList;
    list<QString> attListLen;
    for (k = ucelat.begin(); k != ucelat.end(); ++k) {
        uint size = k->second.size();
        f << "const Attribute MML::" << k->first << "Atts["
            << (size ?size :1) << "] = {" << endl;
        printList("", "", k->second, f);
        f << "\n};" << endl;
        attList.insert(k->first+"Atts");
        attListLen.push_back(QString::number(k->second.size()));
    }
    f << "const Attribute * const MML::attList[numElements] = {" << endl;
    printList("", "", attList, f);
    f << "\n};" << endl;
    f << "const uint MML::attListLen[numElements] = {" << endl;
    printList("", "", attListLen, f);
    f << "\n};" << endl;
    f << "MMLAttribute * (* const MML::attFunc[numAttTypes])("
        "const DOMString &, Attribute) = {" << endl;
    printList("create", "", ucats, f);
    f << "\n};" << endl;
    f.flush();
    file.close();

    // define class Attributes which contains a default instance of each
    // attribute that can be modified
    file.setFileName("attributes.h");
    file.open(QFile::WriteOnly  | QFile::Truncate);
    f.setDevice(&file);
    f << "// this file was automatically generated by 'parseschema'" << endl;
    f << "#ifndef ATTRIBUTES_H" << endl;
    f << "#define ATTRIBUTES_H" << endl;
    f << "#include \"mathml.h\"" << endl;
    f << "#include \"attributechanges.h\"" << endl;
    f << "#include \"paintersettings.h\"" << endl;
    f << "#include <stack>" << endl;
    f << "class MMLElement;" << endl;
    f << "class MMLViewPort;" << endl;
    f << "namespace MML {" << endl;
    f << "class Attributes {" << endl;
    f << "public:" << endl;
    f << "\tAttributes();" << endl;
    f << "\t~Attributes();" << endl;
    f << "\tvoid setPainter(MMLPainter *);" << endl;
    f << "\tvoid setAttributes(const MMLElement *e);" << endl;
    f << "\tvoid unsetAttributes(const MMLElement *e);"
        << endl;
    for (l = at.begin(); l != at.end(); ++l) {
        map<QString,QString>::iterator m = custattlist.find(*l);
        QString s = *l;
        if (s == "class") s = "class_";
        s = s.replace(':', '_');
        f << "\tconst " << m->second << " &" << s << "() const;"
            << endl;
    }
    for (l = atty.begin(); l != atty.end(); ++l) {
        f << "\tvoid setAttribute(MML::Attribute , "
            << "const " << *l << " &);" << endl;
    }
    f << "\tvoid setAttribute(MML::Attribute, const char*);" << endl;
    f << "\tMMLPainter *p;" << endl;
    f << "\tMMLViewPort *view;" << endl;
    f << "private:" << endl;
    f << "\tconst MMLAttribute *att[MML::numAttributes];" << endl;
    f << "\tstatic const char *defstr[MML::numAttributes];" << endl;
    f << "\tstatic const MMLAttribute *defatt[MML::numAttributes];" << endl;
    f << "\tAttributeChanges *cur;" << endl;
    f << "\tstd::stack<AttributeChanges *> changes;" << endl;
    f << "\tPainterSettings *ps;" << endl;
    f << "\tvoid save();" << endl;
    f << "\tvoid restore();" << endl;
    f << "\tvoid initDefaults();" << endl;
    f << "\tvoid removeDefaults();" << endl;
    f << "};" << endl;
    f << "}" << endl;
    f << "#endif" << endl;
    f.flush();
    file.close();

    file.setFileName("attributes.cpp");
    file.open(QFile::WriteOnly  | QFile::Truncate);
    f.setDevice(&file);
    f << "#include \"attributes.h\"" << endl;
    f << "using namespace MML;" << endl;
    f << "// this file was automatically generated by 'parseschema'" << endl;
    f << "const char *Attributes::defstr[numAttributes] = {"<< endl;
    printList("\"", "\"", defat, f);
    f << "\n};" << endl;
    f << "const MMLAttribute *Attributes::defatt[numAttributes];" << endl;
    uint count=0;
    for (l = at.begin(); l != at.end(); ++l) {
        map<QString,QString>::iterator m = custattlist.find(*l);
        QString s = *l;
        if (s == "class") s = "class_";
        s = s.replace(':', '_');
        QString uq = m->second;
        uq.remove(QRegExp(".*::"));
        f << "const " << m->second << " &\nAttributes::" << s
            << "() const {\n\treturn static_cast<const MML"
            << uq
            << "*>(att[" << count++ << "])->value;\n}" << endl;
    }

    f << "#include <iostream>" << endl;
    f << "using std::endl;" << endl;
    f << "using std::cerr;" << endl;
    // generate functions for setting the attributes
    // DOMString must be treated with care: if the desired type is also
    // DOMSting then it can simply set, if not, it is not an error as with
    // mismatching types in the other functions, but the DOMString should
    // be interpreted as a string argument
    for (l = atty.begin(); l != atty.end(); ++l) {
        f << "void" << endl;
        f << "Attributes::setAttribute(MML::Attribute a, const ";
        f << *l << " &value) {" << endl;
        f << "\tconst MMLAttribute *newA;" << endl;
        QString uq = *l;
        uq.remove(QRegExp(".*::"));
        f << "\tif (attTypes[a] != " << mkvar(uq) << "_T) {\n";
        if (*l == "DOMString") {

            f << "\t\tAttributeType type = attTypes[a];" << endl;
            f << "\t\tnewA = attFunc[type](value, a);" << endl;
            f << "\t\tif (!newA) {" << endl;
            f << "\t\t\tcerr << \"error in creating attribute  '\""
                "<<attributeTag[a]<<\"' with value '\" "
                "<< value.utf8() << \"'\" << endl;" << endl;
            f << "\t\t}" << endl;
        } else {
            f << "\t\tcerr << \"Attribute \" << attributeTag[a]\n";
            f << "\t\t\t<< \" is not of type " << *l << ".\" << endl;\n";
            f << "\t\texit(1);" << endl;
        }
        f << "\t} else {" << endl;
        f << "\t\tnewA = new MML" << uq << "(value);\n";
        f << "\t}" << endl;
        f << "\tcur->add(a, newA, att[a]);" << endl;
        f << "\tatt[a] = newA;" << endl;
        f << "\tif (ps) ps->set(a);" << endl;
        f << "}\n" << endl;
    }
    f.flush();
    file.close();
}
#include <qstringlist.h>
void
readCustAttList() {
    QString filepath = dir+"/../custattlist";
    QFile file(filepath);
    file.open(QFile::ReadOnly);
    QTextStream f(&file);
    QString line;
    while (!f.atEnd()) {
        line = f.readLine();
        QStringList l = line.split('\t');
        QString att, type, def;
        if (l.count() > 0) {
            att = l[0];
            if (l.count() > 1) {
                type = l[1];
                if (l.count() > 2) {
                    def = l[2];
                } else {
                    def = "";
                }
            } else {
                type = "";
            }
        } else {
            att = "";
        }
        pair<QString, QString> p(att, type);
        custattlist.insert(p);
    }
}
int
main(int argc, char **argv) {
    if (argc < 2) {
        printf("specify directory\n");
        return 1;
    }
    QString adir(argv[1]);
    QFileInfo f(adir+"/mathml2/mathml2.xsd");
    dir = f.absolutePath();
    QDomDocument d = loadDocument(f.filePath());
    load(d);
    findElements(d);
    if (argc == 2) {
        // this is the normal mode of operation
        readCustAttList();
        writeCode();
    } else {
        // can't remember what this did
        readCustAttList();
        printAttributes();
        printAttributeTypes();
    }

    return 0;
}
