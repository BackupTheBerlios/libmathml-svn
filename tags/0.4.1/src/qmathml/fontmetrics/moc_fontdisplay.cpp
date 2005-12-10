/****************************************************************************
** Meta object code from reading C++ file 'fontdisplay.h'
**
** Created: Tue Nov 29 18:12:59 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fontdisplay.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fontdisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_FontDisplay[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      30,   12,   12,   12, 0x0a,
      44,   12,   12,   12, 0x0a,
      65,   60,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FontDisplay[] = {
    "FontDisplay\0\0setText(QString)\0setBold(bool)\0setItalic(bool)\0size\0"
    "setPointSize(int)\0"
};

const QMetaObject FontDisplay::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_FontDisplay,
      qt_meta_data_FontDisplay, 0 }
};

const QMetaObject *FontDisplay::metaObject() const
{
    return &staticMetaObject;
}

void *FontDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FontDisplay))
    return static_cast<void*>(const_cast<FontDisplay*>(this));
    return QLabel::qt_metacast(_clname);
}

int FontDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setText(*(QString*)_a[1]); break;
        case 1: setBold(*(bool*)_a[1]); break;
        case 2: setItalic(*(bool*)_a[1]); break;
        case 3: setPointSize(*(int*)_a[1]); break;
        }
        _id -= 4;
    }
    return _id;
}
