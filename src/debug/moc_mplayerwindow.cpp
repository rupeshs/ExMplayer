/****************************************************************************
** Meta object code from reading C++ file 'mplayerwindow.h'
**
** Created: Sun Feb 3 11:29:40 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mplayerwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mplayerwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Screen[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Screen[] = {
    "Screen\0\0checkMousePos()\0"
};

const QMetaObject Screen::staticMetaObject = {
    { &rphLabelEx::staticMetaObject, qt_meta_stringdata_Screen,
      qt_meta_data_Screen, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Screen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Screen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Screen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Screen))
        return static_cast<void*>(const_cast< Screen*>(this));
    return rphLabelEx::qt_metacast(_clname);
}

int Screen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rphLabelEx::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: checkMousePos(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_MplayerLayer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      31,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MplayerLayer[] = {
    "MplayerLayer\0\0playingStarted()\0"
    "playingStopped()\0"
};

const QMetaObject MplayerLayer::staticMetaObject = {
    { &Screen::staticMetaObject, qt_meta_stringdata_MplayerLayer,
      qt_meta_data_MplayerLayer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MplayerLayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MplayerLayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MplayerLayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MplayerLayer))
        return static_cast<void*>(const_cast< MplayerLayer*>(this));
    return Screen::qt_metacast(_clname);
}

int MplayerLayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Screen::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: playingStarted(); break;
        case 1: playingStopped(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_MplayerWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      31,   14,   14,   14, 0x05,
      45,   14,   14,   14, 0x05,
      60,   14,   14,   14, 0x05,
      76,   14,   14,   14, 0x05,
      94,   14,   14,   14, 0x05,
     114,  112,   14,   14, 0x05,
     137,   14,   14,   14, 0x05,
     147,   14,   14,   14, 0x05,
     159,   14,   14,   14, 0x05,
     178,  112,   14,   14, 0x05,
     215,  209,   14,   14, 0x05,
     250,  242,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     271,   14,   14,   14, 0x0a,
     282,   14,   14,   14, 0x0a,
     294,   14,   14,   14, 0x0a,
     303,   14,   14,   14, 0x0a,
     314,   14,   14,   14, 0x0a,
     324,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MplayerWindow[] = {
    "MplayerWindow\0\0doubleClicked()\0"
    "leftClicked()\0rightClicked()\0"
    "middleClicked()\0xbutton1Clicked()\0"
    "xbutton2Clicked()\0e\0keyPressed(QKeyEvent*)\0"
    "wheelUp()\0wheelDown()\0mouseMoved(QPoint)\0"
    "mouseMoveEventsg(QMouseEvent*)\0event\0"
    "mousewheelsg(QWheelEvent*)\0wid,hei\0"
    "resizeVideo(int,int)\0moveLeft()\0"
    "moveRight()\0moveUp()\0moveDown()\0"
    "incZoom()\0decZoom()\0"
};

const QMetaObject MplayerWindow::staticMetaObject = {
    { &Screen::staticMetaObject, qt_meta_stringdata_MplayerWindow,
      qt_meta_data_MplayerWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MplayerWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MplayerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MplayerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MplayerWindow))
        return static_cast<void*>(const_cast< MplayerWindow*>(this));
    return Screen::qt_metacast(_clname);
}

int MplayerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Screen::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: doubleClicked(); break;
        case 1: leftClicked(); break;
        case 2: rightClicked(); break;
        case 3: middleClicked(); break;
        case 4: xbutton1Clicked(); break;
        case 5: xbutton2Clicked(); break;
        case 6: keyPressed((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 7: wheelUp(); break;
        case 8: wheelDown(); break;
        case 9: mouseMoved((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 10: mouseMoveEventsg((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 11: mousewheelsg((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 12: resizeVideo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: moveLeft(); break;
        case 14: moveRight(); break;
        case 15: moveUp(); break;
        case 16: moveDown(); break;
        case 17: incZoom(); break;
        case 18: decZoom(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MplayerWindow::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MplayerWindow::leftClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MplayerWindow::rightClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MplayerWindow::middleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void MplayerWindow::xbutton1Clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MplayerWindow::xbutton2Clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void MplayerWindow::keyPressed(QKeyEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MplayerWindow::wheelUp()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void MplayerWindow::wheelDown()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void MplayerWindow::mouseMoved(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MplayerWindow::mouseMoveEventsg(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MplayerWindow::mousewheelsg(QWheelEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MplayerWindow::resizeVideo(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_END_MOC_NAMESPACE
