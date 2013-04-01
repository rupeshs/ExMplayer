/****************************************************************************
** Meta object code from reading C++ file 'rphlabelex.h'
**
** Created: Mon Apr 1 19:09:03 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../rphlabelex.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rphlabelex.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_rphLabelEx[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,
      47,   39,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,   12,   11,   11, 0x0a,
      89,   11,   11,   11, 0x0a,
     101,   11,   11,   11, 0x0a,
     113,   11,   11,   11, 0x0a,
     125,   11,   11,   11, 0x0a,
     137,   11,   11,   11, 0x0a,
     151,  147,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_rphLabelEx[] = {
    "rphLabelEx\0\0val\0rectRubberBand(QRect*)\0"
    "wid,hei\0resizeVideo(int,int)\0"
    "showRubberBand(bool)\0animatet1()\0"
    "animatet2()\0animatet3()\0animatet4()\0"
    "drawall()\0tex\0showErrorText(QString)\0"
};

const QMetaObject rphLabelEx::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_rphLabelEx,
      qt_meta_data_rphLabelEx, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &rphLabelEx::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *rphLabelEx::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *rphLabelEx::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_rphLabelEx))
        return static_cast<void*>(const_cast< rphLabelEx*>(this));
    return QLabel::qt_metacast(_clname);
}

int rphLabelEx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: rectRubberBand((*reinterpret_cast< QRect*(*)>(_a[1]))); break;
        case 1: resizeVideo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: showRubberBand((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: animatet1(); break;
        case 4: animatet2(); break;
        case 5: animatet3(); break;
        case 6: animatet4(); break;
        case 7: drawall(); break;
        case 8: showErrorText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void rphLabelEx::rectRubberBand(QRect * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void rphLabelEx::resizeVideo(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
