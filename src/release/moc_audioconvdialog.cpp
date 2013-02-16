/****************************************************************************
** Meta object code from reading C++ file 'audioconvdialog.h'
**
** Created: Sun Feb 10 13:00:16 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../audioconvdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audioconvdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_audioconvDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   16,   16,   16, 0x08,
      96,   16,   16,   16, 0x08,
     122,   16,   16,   16, 0x08,
     148,   16,   16,   16, 0x08,
     169,   16,   16,   16, 0x08,
     199,  193,   16,   16, 0x08,
     238,  193,   16,   16, 0x08,
     280,  193,   16,   16, 0x08,
     319,  193,   16,   16, 0x08,
     356,   16,   16,   16, 0x08,
     397,   16,   16,   16, 0x08,
     419,   16,   16,   16, 0x08,
     437,  434,   16,   16, 0x08,
     473,  452,   16,   16, 0x08,
     534,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_audioconvDialog[] = {
    "audioconvDialog\0\0opt,fn\0"
    "showfile(QString,QString)\0"
    "on_comboBoxAfmts_currentIndexChanged(QString)\0"
    "on_pushButtonof_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_btnConv_clicked()\0on_pushButton_clicked()\0"
    "index\0on_comboBoxSr_currentIndexChanged(int)\0"
    "on_comboBoxAfmts_currentIndexChanged(int)\0"
    "on_comboBoxCh_currentIndexChanged(int)\0"
    "on_comboBox_currentIndexChanged(int)\0"
    "on_comboBox_currentIndexChanged(QString)\0"
    "toggleExtension(bool)\0updateStatus()\0"
    "ec\0completed(int)\0cfn,ofn,fmt,sr,ch,br\0"
    "encodeaudio(QString,QString,QString,QString,QString,QString)\0"
    "on_detailsPushButton_clicked()\0"
};

const QMetaObject audioconvDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_audioconvDialog,
      qt_meta_data_audioconvDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &audioconvDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *audioconvDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *audioconvDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_audioconvDialog))
        return static_cast<void*>(const_cast< audioconvDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int audioconvDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showfile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: on_comboBoxAfmts_currentIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: on_pushButtonof_clicked(); break;
        case 3: on_pushButton_2_clicked(); break;
        case 4: on_btnConv_clicked(); break;
        case 5: on_pushButton_clicked(); break;
        case 6: on_comboBoxSr_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: on_comboBoxAfmts_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: on_comboBoxCh_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: on_comboBox_currentIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: toggleExtension((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: updateStatus(); break;
        case 13: completed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: encodeaudio((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 15: on_detailsPushButton_clicked(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void audioconvDialog::showfile(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
