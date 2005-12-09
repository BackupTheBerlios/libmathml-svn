#ifndef MMLREADER_H
#define MMLREADER_H

#include <libxml/xmlreader.h>
#include <mathml/domstring.h>

// these definitions conflict with <mathml/elements.h>
#undef DOMAIN
#undef INFINITY
#undef FALSE
#undef TRUE
class MMLDocument;
class MMLNode;
class MMLElement;
class MMLReader {
public:
	MMLReader();
	~MMLReader();
	bool parse(const DOMString &);
	MMLDocument *document();
	DOMString error() { return err; }
	static void errorHandler(void *arg, const char *msg,
		xmlParserSeverities severity, xmlTextReaderLocatorPtr locator);
private:
	MMLNode *cur;
	MMLElement *openel;
	MMLDocument *doc;
	xmlTextReader *reader;
	xmlChar *name, *value;
	bool empty;
	int depth, nodetype;
	DOMString err;
	bool ok;

	void freeOld();
	void processNode();
	bool startElement();
	bool endElement();
	bool attribute();
	bool text();
};

#endif
