#ifndef MMLREADER_H
#define MMLREADER_H

#include <QString>

class MMLDocument;
class MMLErrorHandler;
class MMLContentHandler;
class MMLEntityResolver;
class QIODevice;
class QXmlInputSource;

class MMLReader {
public:
    MMLReader();
    ~MMLReader();
    bool parse(const QString &);
    bool parse(QIODevice &);
    bool parse(const QXmlInputSource &);
    MMLDocument *document();
    const MMLDocument *document() const;
    QString error() const;
private:
    MMLDocument *doc;
    MMLErrorHandler *errorHandler;
    MMLContentHandler *contentHandler;
    MMLEntityResolver *entityResolver;
};

#endif
