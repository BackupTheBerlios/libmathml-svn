#include "mmlcontenthandler.h"
#include <mathml/mmldocument.h>
#include <mathml/mmlelement.h>
#include <mathml/mmltext.h>
#include "qdomstring.h"

MMLContentHandler::MMLContentHandler() {
    debug = false;
    doc = NULL;
    cur = NULL;
}
MMLContentHandler::~MMLContentHandler() {
}
void
MMLContentHandler::setDocument(MMLDocument *d) {
    doc = d;
    cur = NULL;
}
void
MMLContentHandler::setDocumentLocator(QXmlLocator * /*locator*/) {
}
bool
MMLContentHandler::startDocument() {
    if (debug) qDebug("\nmmlch: start doc");
    cur = doc;
    return true;
}
bool
MMLContentHandler::endDocument() {
    if (debug) qDebug("mmlch: end doc");
    return true;
}
bool
MMLContentHandler::startPrefixMapping(const QString &/*prefix*/,
        const QString & /*uri*/ ) {
    return true;
}
bool
MMLContentHandler::endPrefixMapping(const QString &/*prefix*/) {
    return true;
}
bool
MMLContentHandler::startElement(const QString &/*namespaceURI*/,
        const QString & localName, const QString &/*qName*/,
        const QXmlAttributes &atts ) {
    if (debug) qDebug("startElement '%s'", (const char*)localName.toUtf8());
    // the root element must be a 'math' element, it this is absent,
    // we create one
    if (cur == doc && localName != "math") {
        MMLElement *e = doc->createElement("math");
        cur->appendChild(e);
        cur = e;
    }
    bool ok = false;
    MMLElement *e = doc->createElement(domstring(localName));
    if (e) {
        cur->appendChild(e);
        for (int i=0; e->attributesValid() && i<atts.length(); ++i) {
            QString v = atts.value(i).simplified();
            e->setAttribute(atts.localName(i).toUtf8(),
            domstring(v));
        }
        if (e->attributesValid()) {
            cur = e;
            ok = true;
        } else {
            err = qstring(e->errorMsg());
            cur = NULL;
        }
    } else {
        err = qstring(doc->errorMsg());
        qDebug("error: %s", (const char*)err.toUtf8());
        // read failed: clear all
        cur = NULL;
    }
    return ok;
}
bool
MMLContentHandler::endElement(const QString &/*namespaceURI*/,
        const QString &localName, const QString &/*qName*/) {
    if (debug) qDebug("endElement '%s'", (const char*)localName.toUtf8());
    bool valid;
    valid = cur->validate();
    if (!valid) {
        err = QString("Tag '")+localName+"' is not valid: "
            + qstring(cur->errorMsg());
    }
    cur = cur->parentNode();
    return valid;
}
bool
MMLContentHandler::characters(const QString &ch) {
    if (debug) qDebug("characters: %s", (const char*)ch.toUtf8());
    bool valid = true;
    if (!ch.simplified().isEmpty()) {
        MMLText *t;
        MMLNode *n = cur->lastChild();
        if (n && n->isText()) {
            t = static_cast<MMLText *>(n);
            t->appendData(domstring(ch));
        } else {
            t = doc->createTextNode(domstring(ch));
            cur->appendChild(t);
        }
        valid = cur->validate();
        if (!valid) {
            err = qstring(cur->errorMsg());
        }
    }
    return valid;
}
bool
MMLContentHandler::ignorableWhitespace(const QString & /*ch*/) {
    if (debug) qDebug("mmlch: ignoreableWhitespace");
    return true;
}
bool
MMLContentHandler::processingInstruction( const QString & /*target*/,
        const QString & /*data*/ ) {
    return true;
}
bool
MMLContentHandler::skippedEntity( const QString & name ) {
    if (debug) qDebug("skippedEntity: %s", (const char*)name.toUtf8());
    characters("&"+name+";");
    return true;
}
QString
MMLContentHandler::errorString() const {
    if (debug) qDebug("MMLContentHandler::errorString() %s",
        (const char*)err.toUtf8());
    return err;
}
