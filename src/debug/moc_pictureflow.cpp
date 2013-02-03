/****************************************************************************
** Meta object code from reading C++ file 'pictureflow.h'
**
** Created: Sat Feb 2 09:43:14 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pictureflow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pictureflow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PictureFlow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       4,  184, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x05,
      46,   43,   12,   12, 0x05,
      67,   64,   12,   12, 0x05,
      90,   64,   12,   12, 0x05,
     111,   12,   12,   12, 0x05,
     124,  118,   12,   12, 0x05,
     156,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     170,  167,   12,   12, 0x0a,
     184,   12,   12,   12, 0x0a,
     203,  197,   12,   12, 0x0a,
     227,  220,   12,   12, 0x0a,
     257,  245,   12,   12, 0x0a,
     291,  278,   12,   12, 0x0a,
     313,   13,   12,   12, 0x0a,
     333,   12,   12,   12, 0x0a,
     341,   12,   12,   12, 0x0a,
     356,   12,   12,   12, 0x0a,
     367,   13,   12,   12, 0x0a,
     382,   12,   12,   12, 0x0a,
     391,   12,   12,   12, 0x0a,
     407,   12,   12,   12, 0x0a,
     424,  419,   12,   12, 0x0a,
     443,  419,   12,   12, 0x0a,
     469,   12,   12,   12, 0x0a,
     476,   12,   12,   12, 0x0a,
     501,  491,  483,   12, 0x0a,
     524,   12,   12,   12, 0x0a,
     548,   12,   12,   12, 0x0a,
     568,  565,   12,   12, 0x0a,
     587,   12,   12,   12, 0x0a,
     606,   12,   12,   12, 0x08,
     624,   12,   12,   12, 0x08,
     644,   12,   12,   12, 0x08,
     658,   12,   12,   12, 0x08,

 // properties: name, type, flags
     677,  670, 0x43095103,
     699,  693, 0x15095103,
     713,  709, 0x02095001,
     724,  709, 0x02095103,

       0        // eod
};

static const char qt_meta_stringdata_PictureFlow[] = {
    "PictureFlow\0\0index\0centerIndexChanged(int)\0"
    "fn\0filename(QString)\0fp\0addFoldertoPl(QString)\0"
    "addFiletoPl(QString)\0play()\0event\0"
    "showctxmenu(QContextMenuEvent*)\0"
    "dblclick()\0ev\0finished(int)\0stopAdding()\0"
    "image\0addSlide(QImage)\0pixmap\0"
    "addSlide(QPixmap)\0index,image\0"
    "setSlide(int,QImage)\0index,pixmap\0"
    "setSlide(int,QPixmap)\0setCenterIndex(int)\0"
    "clear()\0showPrevious()\0showNext()\0"
    "showSlide(int)\0render()\0triggerRender()\0"
    "addDrives()\0path\0addFolder(QString)\0"
    "addPictureFolder(QString)\0back()\0"
    "init()\0QString\0long_path\0"
    "shortPathName(QString)\0addcontentstoplaylist()\0"
    "hideBackButton()\0en\0showPictures(bool)\0"
    "createThumbnails()\0updateAnimation()\0"
    "addFolderContents()\0backrelease()\0"
    "backpress()\0QColor\0backgroundColor\0"
    "QSize\0slideSize\0int\0slideCount\0"
    "centerIndex\0"
};

const QMetaObject PictureFlow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PictureFlow,
      qt_meta_data_PictureFlow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PictureFlow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PictureFlow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PictureFlow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PictureFlow))
        return static_cast<void*>(const_cast< PictureFlow*>(this));
    return QWidget::qt_metacast(_clname);
}

int PictureFlow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: centerIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: filename((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: addFoldertoPl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: addFiletoPl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: play(); break;
        case 5: showctxmenu((*reinterpret_cast< QContextMenuEvent*(*)>(_a[1]))); break;
        case 6: dblclick(); break;
        case 7: finished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: stopAdding(); break;
        case 9: addSlide((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 10: addSlide((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 11: setSlide((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QImage(*)>(_a[2]))); break;
        case 12: setSlide((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QPixmap(*)>(_a[2]))); break;
        case 13: setCenterIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: clear(); break;
        case 15: showPrevious(); break;
        case 16: showNext(); break;
        case 17: showSlide((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: render(); break;
        case 19: triggerRender(); break;
        case 20: addDrives(); break;
        case 21: addFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: addPictureFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: back(); break;
        case 24: init(); break;
        case 25: { QString _r = shortPathName((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 26: addcontentstoplaylist(); break;
        case 27: hideBackButton(); break;
        case 28: showPictures((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: createThumbnails(); break;
        case 30: updateAnimation(); break;
        case 31: addFolderContents(); break;
        case 32: backrelease(); break;
        case 33: backpress(); break;
        default: ;
        }
        _id -= 34;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = backgroundColor(); break;
        case 1: *reinterpret_cast< QSize*>(_v) = slideSize(); break;
        case 2: *reinterpret_cast< int*>(_v) = slideCount(); break;
        case 3: *reinterpret_cast< int*>(_v) = centerIndex(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setBackgroundColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: setSlideSize(*reinterpret_cast< QSize*>(_v)); break;
        case 3: setCenterIndex(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PictureFlow::centerIndexChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PictureFlow::filename(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PictureFlow::addFoldertoPl(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PictureFlow::addFiletoPl(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PictureFlow::play()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void PictureFlow::showctxmenu(QContextMenuEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PictureFlow::dblclick()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
