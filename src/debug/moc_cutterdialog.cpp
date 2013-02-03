/****************************************************************************
** Meta object code from reading C++ file 'cutterdialog.h'
**
** Created: Sat Feb 2 22:04:59 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cutterdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cutterdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cutterDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   13,   13,   13, 0x08,
      82,   75,   13,   13, 0x08,
     111,   13,   13,   13, 0x08,
     139,   13,   13,   13, 0x08,
     166,   13,   13,   13, 0x08,
     192,   13,   13,   13, 0x08,
     220,   13,   13,   13, 0x08,
     249,   13,   13,   13, 0x08,
     275,   13,   13,   13, 0x08,
     302,   13,   13,   13, 0x08,
     331,   13,   13,   13, 0x08,
     359,   13,   13,   13, 0x08,
     388,   13,   13,   13, 0x08,
     411,  407,   13,   13, 0x08,
     426,   13,   13,   13, 0x08,
     442,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_cutterDialog[] = {
    "cutterDialog\0\0opt,fn\0showfile(QString,QString)\0"
    "on_pushButtonhelp_clicked()\0action\0"
    "on_seek_actionTriggered(int)\0"
    "on_toolButtonStop_clicked()\0"
    "on_pushButtonpre_clicked()\0"
    "on_pushButtonof_clicked()\0"
    "on_pushButtonStop_pressed()\0"
    "on_pushButtonclose_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButtonCut_clicked()\0"
    "on_pushButtonReset_clicked()\0"
    "on_pushButtonStop_clicked()\0"
    "on_pushButtonStart_clicked()\0"
    "readffmpegoutput()\0val\0completed(int)\0"
    "updateSeekbar()\0updateStatus()\0"
};

const QMetaObject cutterDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_cutterDialog,
      qt_meta_data_cutterDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cutterDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cutterDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cutterDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cutterDialog))
        return static_cast<void*>(const_cast< cutterDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int cutterDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showfile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: on_pushButtonhelp_clicked(); break;
        case 2: on_seek_actionTriggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: on_toolButtonStop_clicked(); break;
        case 4: on_pushButtonpre_clicked(); break;
        case 5: on_pushButtonof_clicked(); break;
        case 6: on_pushButtonStop_pressed(); break;
        case 7: on_pushButtonclose_clicked(); break;
        case 8: on_pushButton_2_clicked(); break;
        case 9: on_pushButtonCut_clicked(); break;
        case 10: on_pushButtonReset_clicked(); break;
        case 11: on_pushButtonStop_clicked(); break;
        case 12: on_pushButtonStart_clicked(); break;
        case 13: readffmpegoutput(); break;
        case 14: completed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: updateSeekbar(); break;
        case 16: updateStatus(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void cutterDialog::showfile(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
