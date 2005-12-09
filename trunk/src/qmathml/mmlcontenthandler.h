#ifndef MMLCONTENTHANDLER_H
#define MMLCONTENTHANDLER_H

#include <QXmlContentHandler>

class MMLDocument;
class MMLNode;

class MMLContentHandler : public QXmlContentHandler {
public:
	MMLContentHandler();
	virtual ~MMLContentHandler();
	void setDocument(MMLDocument *);

	// SAX2 functions
	void setDocumentLocator(QXmlLocator *locator);
	bool startDocument();
	bool endDocument();
	bool startPrefixMapping(const QString &prefix,
		const QString &uri);
	bool endPrefixMapping(const QString &prefix);
	bool startElement(const QString &namespaceURI,
		const QString &localName, const QString &qName,
		const QXmlAttributes &atts);
	bool endElement(const QString &namespaceURI, const QString &localName,
			const QString &qName);
	bool characters(const QString &ch);
	bool ignorableWhitespace(const QString &ch);
	bool processingInstruction(const QString &target, const QString &data);
	bool skippedEntity( const QString & name );
	QString errorString() const;
private:
	bool debug;
	QString err;
	MMLDocument *doc;
	MMLNode *cur;
};

#endif
