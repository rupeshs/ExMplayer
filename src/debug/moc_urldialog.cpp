/****************************************************************************
** Meta object code from reading C++ file 'urldialog.h'
**
** Created: Sat Feb 2 09:43:21 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../urldialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'urldialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UrlDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   10,   10,   10, 0x08,
      56,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UrlDialog[] = {
    "UrlDialog\0\0url\0playurl(QString)\0"
    "on_buttonBox_accepted()\0"
    "on_lineEdit_returnPressed()\0"
};

const QMetaObject UrlDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UrlDialog,
      qt_meta_data_UrlDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UrlDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UrlDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UrlDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UrlDialog))
        return static_cast<void*>(const_cast< UrlDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int UrlDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: playurl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: on_buttonBox_accepted(); break;
        case 2: on_lineEdit_returnPressed(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void UrlDialog::playurl(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
