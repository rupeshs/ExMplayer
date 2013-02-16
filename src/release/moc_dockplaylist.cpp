/****************************************************************************
** Meta object code from reading C++ file 'dockplaylist.h'
**
** Created: Sun Feb 10 13:00:02 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dockplaylist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dockplaylist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dockPlayList[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x05,
      45,   14,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_dockPlayList[] = {
    "dockPlayList\0\0event\0sgdropEvent(QDropEvent*)\0"
    "sgcontextMenuEvent(QContextMenuEvent*)\0"
};

const QMetaObject dockPlayList::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_dockPlayList,
      qt_meta_data_dockPlayList, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &dockPlayList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *dockPlayList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *dockPlayList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dockPlayList))
        return static_cast<void*>(const_cast< dockPlayList*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int dockPlayList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sgdropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 1: sgcontextMenuEvent((*reinterpret_cast< QContextMenuEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void dockPlayList::sgdropEvent(QDropEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void dockPlayList::sgcontextMenuEvent(QContextMenuEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
