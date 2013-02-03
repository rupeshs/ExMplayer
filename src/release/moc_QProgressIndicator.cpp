/****************************************************************************
** Meta object code from reading C++ file 'QProgressIndicator.h'
**
** Created: Sun Jan 27 21:26:37 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QProgressIndicator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QProgressIndicator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QProgressIndicator[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       3,   39, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      37,   19,   19,   19, 0x0a,
      59,   53,   19,   19, 0x0a,
      88,   82,   19,   19, 0x0a,
     124,  118,   19,   19, 0x0a,

 // properties: name, type, flags
      53,  141, 0x02095003,
     150,  145, 0x01095103,
     118,  171, 0x43095103,

       0        // eod
};

static const char qt_meta_stringdata_QProgressIndicator[] = {
    "QProgressIndicator\0\0startAnimation()\0"
    "stopAnimation()\0delay\0setAnimationDelay(int)\0"
    "state\0setDisplayedWhenStopped(bool)\0"
    "color\0setColor(QColor)\0int\0bool\0"
    "displayedWhenStopped\0QColor\0"
};

const QMetaObject QProgressIndicator::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QProgressIndicator,
      qt_meta_data_QProgressIndicator, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QProgressIndicator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QProgressIndicator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QProgressIndicator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QProgressIndicator))
        return static_cast<void*>(const_cast< QProgressIndicator*>(this));
    return QWidget::qt_metacast(_clname);
}

int QProgressIndicator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: startAnimation(); break;
        case 1: stopAnimation(); break;
        case 2: setAnimationDelay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setDisplayedWhenStopped((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: setColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = animationDelay(); break;
        case 1: *reinterpret_cast< bool*>(_v) = isDisplayedWhenStopped(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = color(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setAnimationDelay(*reinterpret_cast< int*>(_v)); break;
        case 1: setDisplayedWhenStopped(*reinterpret_cast< bool*>(_v)); break;
        case 2: setColor(*reinterpret_cast< QColor*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
