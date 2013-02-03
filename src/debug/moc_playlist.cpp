/****************************************************************************
** Meta object code from reading C++ file 'playlist.h'
**
** Created: Sat Feb 2 09:43:15 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_playList[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   10,    9,    9, 0x05,
      37,    9,    9,    9, 0x05,
      52,   10,    9,    9, 0x05,
      77,    9,    9,    9, 0x05,
      92,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     109,   10,    9,    9, 0x0a,
     146,  126,    9,    9, 0x0a,
     186,    9,    9,    9, 0x0a,
     198,    9,    9,    9, 0x0a,
     224,  219,    9,    9, 0x0a,
     261,    9,    9,    9, 0x0a,
     276,    9,    9,    9, 0x0a,
     295,    9,    9,    9, 0x0a,
     311,    9,    9,    9, 0x0a,
     329,    9,    9,    9, 0x0a,
     352,    9,  344,    9, 0x0a,
     372,  366,  344,    9, 0x0a,
     390,  385,    9,    9, 0x0a,
     409,  385,    9,    9, 0x0a,
     426,  385,    9,    9, 0x0a,
     445,  385,    9,    9, 0x0a,
     466,  462,    9,    9, 0x0a,
     488,  485,    9,    9, 0x0a,
     499,  485,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_playList[] = {
    "playList\0\0path\0playThisfile(QString)\0"
    "clearingList()\0showPictureFlow(QString)\0"
    "addingfilesg()\0removingfilesg()\0"
    "addFile(QString)\0root,filters,parent\0"
    "addFolder(QString,QStringList,QWidget*)\0"
    "clearList()\0removeSelectedFile()\0item\0"
    "itemDoubleClicked(QTableWidgetItem*)\0"
    "playNextFile()\0playPreviousFile()\0"
    "playFirstFile()\0playCurrentFile()\0"
    "playLastFile()\0QString\0getNextFile()\0"
    "index\0getFile(int)\0file\0saveasM3u(QString)\0"
    "loadM3u(QString)\0saveasPls(QString)\0"
    "loadPls(QString)\0dur\0setDuration(float)\0"
    "en\0loop(bool)\0shuffle(bool)\0"
};

const QMetaObject playList::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_playList,
      qt_meta_data_playList, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &playList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *playList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *playList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_playList))
        return static_cast<void*>(const_cast< playList*>(this));
    return QObject::qt_metacast(_clname);
}

int playList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: playThisfile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: clearingList(); break;
        case 2: showPictureFlow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: addingfilesg(); break;
        case 4: removingfilesg(); break;
        case 5: addFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: addFolder((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< QWidget*(*)>(_a[3]))); break;
        case 7: clearList(); break;
        case 8: removeSelectedFile(); break;
        case 9: itemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 10: playNextFile(); break;
        case 11: playPreviousFile(); break;
        case 12: playFirstFile(); break;
        case 13: playCurrentFile(); break;
        case 14: playLastFile(); break;
        case 15: { QString _r = getNextFile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: { QString _r = getFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: saveasM3u((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: loadM3u((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: saveasPls((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: loadPls((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: setDuration((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: loop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: shuffle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void playList::playThisfile(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void playList::clearingList()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void playList::showPictureFlow(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void playList::addingfilesg()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void playList::removingfilesg()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
