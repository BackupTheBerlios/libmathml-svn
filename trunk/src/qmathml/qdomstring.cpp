#include "qdomstring.h"

QString
qstring(const DOMString &d) {
	return QString::fromStdWString(d);
}
DOMString
domstring(const QString &s) {
    return s.toStdWString();
}
