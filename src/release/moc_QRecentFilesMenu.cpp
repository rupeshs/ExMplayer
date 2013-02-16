/****************************************************************************
** Meta object code from reading C++ file 'QRecentFilesMenu.h'
**
** Created: Sun Feb 10 13:00:06 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QRecentFilesMenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QRecentFilesMenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QRecentFilesMenu[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       2,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   56,   17,   17, 0x0a,
      88,   17,   17,   17, 0x0a,
     100,   17,   17,   17, 0x0a,
     117,   17,   17,   17, 0x08,
     141,   17,   17,   17, 0x08,

 // properties: name, type, flags
     171,  167, 0x02095103,
     188,  180, 0x0a095103,

       0        // eod
};

static const char qt_meta_stringdata_QRecentFilesMenu[] = {
    "QRecentFilesMenu\0\0filename\0"
    "recentFileTriggered(QString)\0fileName\0"
    "addRecentFile(QString)\0clearMenu()\0"
    "setMaxCount(int)\0menuTriggered(QAction*)\0"
    "updateRecentFileActions()\0int\0maxCount\0"
    "QString\0format\0"
};

const QMetaObject QRecentFilesMenu::staticMetaObject = {
    { &QMenu::staticMetaObject, qt_meta_stringdata_QRecentFilesMenu,
      qt_meta_data_QRecentFilesMenu, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QRecentFilesMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QRecentFilesMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QRecentFilesMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QRecentFilesMenu))
        return static_cast<void*>(const_cast< QRecentFilesMenu*>(this));
    return QMenu::qt_metacast(_clname);
}

int QRecentFilesMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: recentFileTriggered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: addRecentFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: clearMenu(); break;
        case 3: setMaxCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: menuTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 5: updateRecentFileActions(); break;
        default: ;
        }
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = maxCount(); break;
        case 1: *reinterpret_cast< QString*>(_v) = format(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setMaxCount(*reinterpret_cast< int*>(_v)); break;
        case 1: setFormat(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QRecentFilesMenu::recentFileTriggered(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
