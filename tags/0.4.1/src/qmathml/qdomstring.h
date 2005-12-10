#ifndef QDOMSTRING
#define QDOMSTRING

#include <QString>
#include <mathml/domstring.h>

QString qstring(const DOMString &);
DOMString domstring(const QString &);

#endif
