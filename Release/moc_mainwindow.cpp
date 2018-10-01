/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Desktop/HDRProject/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      36,   11,   11,   11, 0x08,
      59,   11,   11,   11, 0x08,
      80,   11,   11,   11, 0x08,
     101,   11,   11,   11, 0x08,
     134,   11,   11,   11, 0x08,
     172,  167,   11,   11, 0x08,
     206,   11,   11,   11, 0x08,
     231,   11,   11,   11, 0x08,
     257,   11,   11,   11, 0x08,
     282,  276,   11,   11, 0x08,
     310,   11,   11,   11, 0x08,
     330,   11,   11,   11, 0x08,
     352,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_pushButton_clicked()\0"
    "on_createHDR_clicked()\0on_saveHDR_clicked()\0"
    "on_tonemap_clicked()\0"
    "on_viewTonemappedImage_clicked()\0"
    "on_saveTonemappedImage_clicked()\0arg1\0"
    "on_lMaxCheckBox_stateChanged(int)\0"
    "on_openHdrFile_clicked()\0"
    "on_localTonemap_clicked()\0on_listX_clicked()\0"
    "index\0removeFromLdrImageList(int)\0"
    "on_listUp_clicked()\0on_listDown_clicked()\0"
    "on_actionQuit_triggered()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_createHDR_clicked(); break;
        case 2: _t->on_saveHDR_clicked(); break;
        case 3: _t->on_tonemap_clicked(); break;
        case 4: _t->on_viewTonemappedImage_clicked(); break;
        case 5: _t->on_saveTonemappedImage_clicked(); break;
        case 6: _t->on_lMaxCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_openHdrFile_clicked(); break;
        case 8: _t->on_localTonemap_clicked(); break;
        case 9: _t->on_listX_clicked(); break;
        case 10: _t->removeFromLdrImageList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_listUp_clicked(); break;
        case 12: _t->on_listDown_clicked(); break;
        case 13: _t->on_actionQuit_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
