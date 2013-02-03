/****************************************************************************
** Meta object code from reading C++ file 'winampdspdialog.h'
**
** Created: Sun Jan 27 21:26:38 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../winampdspdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'winampdspdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WinampDspDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   17,   16,   16, 0x05,
      85,   73,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     118,   16,   16,   16, 0x0a,
     134,  131,   16,   16, 0x0a,
     158,   16,   16,   16, 0x08,
     182,   16,   16,   16, 0x08,
     208,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WinampDspDialog[] = {
    "WinampDspDialog\0\0group,key,value\0"
    "settingChanged(QString,QString,QString)\0"
    "enable,path\0enableWinampPlugin(bool,QString)\0"
    "getPlugins()\0se\0dlgsettings(QSettings*)\0"
    "on_buttonBox_accepted()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_clicked()\0"
};

const QMetaObject WinampDspDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WinampDspDialog,
      qt_meta_data_WinampDspDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WinampDspDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WinampDspDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WinampDspDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WinampDspDialog))
        return static_cast<void*>(const_cast< WinampDspDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int WinampDspDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: settingChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: enableWinampPlugin((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: getPlugins(); break;
        case 3: dlgsettings((*reinterpret_cast< QSettings*(*)>(_a[1]))); break;
        case 4: on_buttonBox_accepted(); break;
        case 5: on_pushButton_2_clicked(); break;
        case 6: on_pushButton_clicked(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void WinampDspDialog::settingChanged(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WinampDspDialog::enableWinampPlugin(bool _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
