/****************************************************************************
** Meta object code from reading C++ file 'midialog.h'
**
** Created: Sat Feb 2 09:43:27 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../midialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'midialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_miDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   25,    9,    9, 0x0a,
      52,   48,    9,    9, 0x0a,
      79,   75,    9,    9, 0x0a,
      97,    9,    9,    9, 0x08,
     117,    9,    9,    9, 0x08,
     143,    9,    9,    9, 0x08,
     167,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_miDialog[] = {
    "miDialog\0\0saveCoverArt()\0tex\0"
    "setMiText(QString)\0val\0setbtnSaveEnable(bool)\0"
    "tit\0setTitle(QString)\0on_btncov_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_clicked()\0on_buttonBox_accepted()\0"
};

const QMetaObject miDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_miDialog,
      qt_meta_data_miDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &miDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *miDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *miDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_miDialog))
        return static_cast<void*>(const_cast< miDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int miDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: saveCoverArt(); break;
        case 1: setMiText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: setbtnSaveEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: setTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: on_btncov_clicked(); break;
        case 5: on_pushButton_3_clicked(); break;
        case 6: on_pushButton_clicked(); break;
        case 7: on_buttonBox_accepted(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void miDialog::saveCoverArt()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
