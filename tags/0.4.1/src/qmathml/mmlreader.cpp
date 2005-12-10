#include "mmlreader.h"
#include "mmlcontenthandler.h"
#include <mathml/mmldocument.h>
#include <QXmlEntityResolver>
#include <QXmlInputSource>

class
MMLEntityResolver : public QXmlEntityResolver {
public:
    virtual ~MMLEntityResolver() {}
    bool resolveEntity(const QString &, const QString &, QXmlInputSource*&);
    QString errorString() const { return ""; }
};
bool
MMLEntityResolver::resolveEntity(const QString &publicID, const QString &systemID, QXmlInputSource *&/*ret*/) {
    qDebug("read entity");
    qDebug("publicID: %s, systemID: %s",
            (const char*)publicID.toUtf8(),
            (const char*)systemID.toUtf8());
    return true;
}

class
MMLErrorHandler : public QXmlErrorHandler {
public:
    virtual ~MMLErrorHandler() {}
    bool warning ( const QXmlParseException &e) {
        err = e.message();
        return false;
    }
    bool error (const QXmlParseException &e) {
        err = e.message();
        return false;
    }
    bool fatalError(const QXmlParseException &e) {
        err = e.message();
        return false;
    }
    QString errorString() const { return err; }
private:
    QString err;
};

MMLReader::MMLReader() {
    contentHandler = new MMLContentHandler();
    errorHandler = new MMLErrorHandler();
    entityResolver = new MMLEntityResolver();
    doc = NULL;
}
MMLReader::~MMLReader() {
    delete contentHandler;
    delete errorHandler;
    delete entityResolver;
    if (doc) {
        delete doc;
    }
}
bool
MMLReader::parse(QIODevice &inputdevice) {
    QXmlInputSource in(&inputdevice);
    return parse(in);
}
bool
MMLReader::parse(const QString &s) {
    QXmlInputSource in;
    in.setData(s);
    return parse(in);
}
bool
MMLReader::parse(const QXmlInputSource &in) {
    QXmlSimpleReader p;
    // if the previous document was not retrieved, delete it
    if (doc) {
        delete doc;
    }
    doc = new MMLDocument();
    contentHandler->setDocument(doc);
    p.setContentHandler(contentHandler);
    p.setErrorHandler(errorHandler);
    p.setEntityResolver(entityResolver);
    return p.parse(in);
}
MMLDocument *
MMLReader::document() {
    // give ou the document and remove the reference to it
    // it's the responsibility of the requester to delete it
    MMLDocument *d = doc;
    doc = NULL;
    return d;
}
const MMLDocument *
MMLReader::document() const {
    return doc;
}
QString
MMLReader::error() const {
    return errorHandler->errorString();
}
