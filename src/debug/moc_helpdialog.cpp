/****************************************************************************
** Meta object code from reading C++ file 'helpdialog.h'
**
** Created: Mon Apr 1 19:09:18 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../helpdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'helpdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_helpDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x0a,
      37,   11,   11,   11, 0x0a,
      51,   12,   11,   11, 0x0a,
      86,   75,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_helpDialog[] = {
    "helpDialog\0\0str\0setHelpText(QString)\0"
    "showContent()\0showcutterHelp(QString)\0"
    "currentRow\0on_listWidgetContent_currentRowChanged(int)\0"
};

const QMetaObject helpDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_helpDialog,
      qt_meta_data_helpDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &helpDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *helpDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *helpDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_helpDialog))
        return static_cast<void*>(const_cast< helpDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int helpDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setHelpText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: showContent(); break;
        case 2: showcutterHelp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: on_listWidgetContent_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
