#include <libxml/xmlreader.h>
#include "mmlreader.h"
#include <mathml/mmldocument.h>
#include <mathml/mmlelement.h>
#include <mathml/mmltext.h>
#include <iostream>

DOMString
domstring(const xmlChar *s) {
    DOMString d((char *)s);
    return d;
}
MMLReader::MMLReader() {
    doc = 0;
    name = 0;
    value = 0;
}
MMLReader::~MMLReader() {
    freeOld();
    if (doc) {
        delete doc;
    }
}
bool
MMLReader::parse(const DOMString &buf) {
    if (doc) {
        delete doc;
        doc = 0;
    }
    if (buf.length() == 0) {
        err = "buffer is empty";
        return true;
    }
    doc = new MMLDocument();
    cur = doc;
    int ret=0;
    ok = false;

    const char *cb = buf.utf8();
    xmlParserInputBufferPtr b =
            xmlParserInputBufferCreateMem(cb, buf.length(), XML_CHAR_ENCODING_UTF8);
    reader = xmlNewTextReader(b, 0);
    if (reader != NULL) {
        xmlTextReaderSetErrorHandler(reader, MMLReader::errorHandler,
                this);
        ret = xmlTextReaderRead(reader);
        ok = true;
        while (ok && ret == 1) {
//            printf("continue reading\n");
            processNode();
            if (ok) {
                ret = xmlTextReaderRead(reader);
            }
        }
        xmlFreeTextReader(reader);
        if (ret != 0) {
            printf("failed to parse XML: %i\n", ret);
            printf("ok: %i\n", ok);
        }
    }
    xmlFreeParserInputBuffer(b);
    if (ok) {
        ok = doc->validate();
        if (!ok) {
            err = doc->errorMsg();
        }
    }
    return ok;
}
MMLDocument *
MMLReader::document() {
    MMLDocument *d = doc;
    doc = 0;
    return d;
}
void
MMLReader::freeOld() {
    if (name) xmlFree(name);
    if (value) xmlFree(value);
}
void
MMLReader::processNode() {
    /* handling of a node in the tree */
    freeOld();

    name = xmlTextReaderName(reader);
    if (name == NULL) {
        name = xmlStrdup(BAD_CAST "--");
    }
    value = xmlTextReaderValue(reader);
    depth = xmlTextReaderDepth(reader);
    empty = xmlTextReaderIsEmptyElement(reader);
    nodetype = xmlTextReaderNodeType(reader);

    switch (nodetype) {
    case 0: // NONE
        break;
    case 1: // ELEMENT
//        printf("start element %s\n", name);
        ok = startElement();
        break;
    case 2: // ATTRIBUTE
//        printf("attribute %s\n", name);
        ok = attribute();
        break;
    case 3: // TEXT
//        printf("text: %s\n", value);
        ok = text();
        break;
    case 4: // CDATA
        break;
    case 5: // ENTITY_REFERENCE
        break;
    case 6: // ENTITY
        break;
    case 7: // PROCESSING_INSTRUCTION
        break;
    case 8: // COMMENT
        break;
    case 9: // DOCUMENT
        break;
    case 10: // DOCUMENT_TYPE
        break;
    case 11: // DOCUMENT_FRAGMENT
        break;
    case 12: // NOTATION
        break;
    case 13: // WHITESPACE
        break;
    case 14: // SIGNIFICANT_WHITESPACE
        break;
    case 15: // END_ELEMENT
//        printf("end element %s\n", name);
        ok = endElement();
        break;
    case 16: // END_ENTITY
        break;
    case 17: // XML_DECLARATION
        break;
    default:
        break;
    }
    if (!ok) {
        std::cerr << "Error: " << err.utf8() << std::endl;
    }
}
bool
MMLReader::startElement() {
    openel = doc->createElement(domstring(name));
    if (openel) {
        cur->appendChild(openel);
        ok = true;
        while (ok && xmlTextReaderMoveToNextAttribute(reader)) {
            processNode();
        }
        if (openel->attributesValid()) {
            cur = openel;
            ok = true;
        } else {
            ok = false;
            err = openel->errorMsg();
            cur = NULL;
        }
    } else {
        ok = false;
        err = doc->errorMsg();
        printf("error: %s", (const char*)err.utf8());
        // read failed: clear all
        cur = NULL;
    }
    return ok;
}
bool
MMLReader::endElement() {
    bool valid;
    valid = cur->validate();
    if (!valid) {
        err = "Tag '";
        err += (const char*)name;
        err +="' is not valid: ";
        err += cur->errorMsg();
    }
    cur = cur->parentNode();
    return valid;
}
bool
MMLReader::attribute() {
    DOMString ds = domstring(name);
    openel->setAttribute(ds.utf8(), domstring(value));
    return true;
}
bool
MMLReader::text() {
    bool valid = true;
    DOMString ch(domstring(value));
    ch.normalize();
    if (ch.length() > 0) {
        MMLText *t;
        MMLNode *n = cur->lastChild();
        if (n && n->isText()) {
            t = static_cast<MMLText *>(n);
            t->appendData(ch);
        } else {
            t = doc->createTextNode(ch);
            cur->appendChild(t);
        }
        valid = cur->validate();
        if (!valid) {
            err = cur->errorMsg();
        }
    }
    return valid;
}
void
MMLReader::errorHandler(void *arg, const char *msg,
        xmlParserSeverities, xmlTextReaderLocatorPtr) {
    MMLReader *r = static_cast<MMLReader *>(arg);
    r->err = msg;
    printf("XML error: %s\n", r->err.utf8());
}
