// this file was automatically generated by 'parseschema'
#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H
#include "mathml.h"
#include "attributechanges.h"
#include "paintersettings.h"
#include <stack>
class MMLElement;
class MMLViewPort;
namespace MML {
class Attributes {
public:
    Attributes();
    ~Attributes();
    void setPainter(MMLPainter *);
    void setAttributes(const MMLElement *e);
    void unsetAttributes(const MMLElement *e);
    const bool &accent() const;
    const bool &accentunder() const;
    const DOMString &actiontype() const;
    const DOMString &align() const;
    const DOMString &alignmentscope() const;
    const DOMString &alt() const;
    const DOMString &altimg() const;
    const DOMString &alttext() const;
    const MathColor &background() const;
    const int &base() const;
    const DOMString &baseline() const;
    const bool &bevelled() const;
    const DOMString &class_() const;
    const DOMString &close() const;
    const DOMString &closure() const;
    const MathColor &color() const;
    const DOMString &columnalign() const;
    const DOMString &columnlines() const;
    const DOMString &columnspacing() const;
    const int &columnspan() const;
    const DOMString &columnwidth() const;
    const DOMString &definitionURL() const;
    const DOMString &denomalign() const;
    const h_unit &depth() const;
    const DOMString &display() const;
    const bool &displaystyle() const;
    const DOMString &edge() const;
    const DOMString &encoding() const;
    const bool &equalcolumns() const;
    const bool &equalrows() const;
    const bool &fence() const;
    const DOMString &fontfamily() const;
    const DOMString &form() const;
    const DOMString &frame() const;
    const DOMString &framespacing() const;
    const DOMString &groupalign() const;
    const v_unit &height() const;
    const DOMString &id() const;
    const int &index() const;
    const bool &largeop() const;
    const DOMString &linebreak() const;
    const v_unit &linethickness() const;
    const DOMString &lquote() const;
    const h_unit &lspace() const;
    const DOMString &macros() const;
    const MathColor &mathbackground() const;
    const MathColor &mathcolor() const;
    const v_unit &mathsize() const;
    const MathVariant &mathvariant() const;
    const h_unit &maxsize() const;
    const h_unit &mediummathspace() const;
    const h_unit &minlabelspacing() const;
    const h_unit &minsize() const;
    const bool &movablelimits() const;
    const DOMString &name() const;
    const int &nargs() const;
    const DOMString &notation() const;
    const DOMString &numalign() const;
    const DOMString &occurrence() const;
    const DOMString &open() const;
    const DOMString &order() const;
    const DOMString &overflow() const;
    const DOMString &rowalign() const;
    const DOMString &rowlines() const;
    const DOMString &rowspacing() const;
    const int &rowspan() const;
    const DOMString &rquote() const;
    const h_unit &rspace() const;
    const DOMString &scope() const;
    const int &scriptlevel() const;
    const v_unit &scriptminsize() const;
    const float &scriptsizemultiplier() const;
    const int &selection() const;
    const bool &separator() const;
    const DOMString &separators() const;
    const DOMString &side() const;
    const bool &stretchy() const;
    const DOMString &style() const;
    const h_unit &subscriptshift() const;
    const h_unit &superscriptshift() const;
    const bool &symmetric() const;
    const h_unit &thickmathspace() const;
    const h_unit &thinmathspace() const;
    const DOMString &type() const;
    const h_unit &verythickmathspace() const;
    const h_unit &verythinmathspace() const;
    const h_unit &veryverythickmathspace() const;
    const h_unit &veryverythinmathspace() const;
    const h_unit &width() const;
    const DOMString &xlink_href() const;
    const DOMString &xref() const;
    void setAttribute(MML::Attribute , const DOMString &);
    void setAttribute(MML::Attribute , const MathColor &);
    void setAttribute(MML::Attribute , const MathVariant &);
    void setAttribute(MML::Attribute , const bool &);
    void setAttribute(MML::Attribute , const float &);
    void setAttribute(MML::Attribute , const h_unit &);
    void setAttribute(MML::Attribute , const int &);
    void setAttribute(MML::Attribute , const v_unit &);
    void setAttribute(MML::Attribute, const char*);
    MMLPainter *p;
    MMLViewPort *view;
private:
    const MMLAttribute *att[MML::numAttributes];
    static const char *defstr[MML::numAttributes];
    static const MMLAttribute *defatt[MML::numAttributes];
    AttributeChanges *cur;
    std::stack<AttributeChanges *> changes;
    PainterSettings *ps;
    void save();
    void restore();
    void initDefaults();
    void removeDefaults();
};
}
#endif