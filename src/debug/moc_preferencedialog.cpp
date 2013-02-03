/****************************************************************************
** Meta object code from reading C++ file 'preferencedialog.h'
**
** Created: Sat Feb 2 09:43:19 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../preferencedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'preferencedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_preferenceDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,   18,   17,   17, 0x05,
      74,   17,   17,   17, 0x05,
      91,   17,   17,   17, 0x05,
     111,   17,   17,   17, 0x05,
     121,   17,   17,   17, 0x05,
     133,   17,   17,   17, 0x05,
     143,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     170,  161,   17,   17, 0x0a,
     196,  194,   17,   17, 0x0a,
     212,   17,   17,   17, 0x08,
     236,   17,   17,   17, 0x08,
     268,   17,   17,   17, 0x08,
     294,   17,   17,   17, 0x08,
     320,   17,   17,   17, 0x08,
     346,   17,   17,   17, 0x08,
     372,   17,   17,   17, 0x08,
     393,   17,   17,   17, 0x08,
     427,  419,   17,   17, 0x08,
     450,   17,   17,   17, 0x08,
     479,  474,   17,   17, 0x08,
     524,  474,   17,   17, 0x08,
     563,   17,   17,   17, 0x08,
     607,  596,   17,   17, 0x08,
     651,  644,   17,   17, 0x08,
     690,   17,   17,   17, 0x08,
     713,  708,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_preferenceDialog[] = {
    "preferenceDialog\0\0group,key,value\0"
    "settingChanged(QString,QString,QString)\0"
    "reloadshortcut()\0setmousewheelrole()\0"
    "restart()\0disableSS()\0setAqua()\0"
    "restartComplete()\0settings\0"
    "setSettings(QSettings*)\0w\0setSc(QWidget*)\0"
    "on_buttonBox_accepted()\0"
    "on_listWidget_viewportEntered()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_chScDir_clicked()\0on_pushButton_2_clicked()\0"
    "checked\0on_rbVol_toggled(bool)\0"
    "on_pushButton_clicked()\0item\0"
    "on_twsc_itemDoubleClicked(QTableWidgetItem*)\0"
    "on_twsc_itemClicked(QTableWidgetItem*)\0"
    "on_cbEnableAEq_stateChanged(int)\0"
    "currentRow\0on_listWidget_currentRowChanged(int)\0"
    "button\0on_buttonBox_clicked(QAbstractButton*)\0"
    "saveActionToXml()\0arg1\0"
    "on_comboBoxStyle_activated(QString)\0"
};

const QMetaObject preferenceDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_preferenceDialog,
      qt_meta_data_preferenceDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &preferenceDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *preferenceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *preferenceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_preferenceDialog))
        return static_cast<void*>(const_cast< preferenceDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int preferenceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: settingChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: reloadshortcut(); break;
        case 2: setmousewheelrole(); break;
        case 3: restart(); break;
        case 4: disableSS(); break;
        case 5: setAqua(); break;
        case 6: restartComplete(); break;
        case 7: setSettings((*reinterpret_cast< QSettings*(*)>(_a[1]))); break;
        case 8: setSc((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 9: on_buttonBox_accepted(); break;
        case 10: on_listWidget_viewportEntered(); break;
        case 11: on_pushButton_6_clicked(); break;
        case 12: on_pushButton_5_clicked(); break;
        case 13: on_pushButton_4_clicked(); break;
        case 14: on_pushButton_3_clicked(); break;
        case 15: on_chScDir_clicked(); break;
        case 16: on_pushButton_2_clicked(); break;
        case 17: on_rbVol_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: on_pushButton_clicked(); break;
        case 19: on_twsc_itemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 20: on_twsc_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 21: on_cbEnableAEq_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: on_buttonBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 24: saveActionToXml(); break;
        case 25: on_comboBoxStyle_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void preferenceDialog::settingChanged(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void preferenceDialog::reloadshortcut()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void preferenceDialog::setmousewheelrole()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void preferenceDialog::restart()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void preferenceDialog::disableSS()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void preferenceDialog::setAqua()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void preferenceDialog::restartComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
