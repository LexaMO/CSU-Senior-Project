/****************************************************************************
** Meta object code from reading C++ file 'imageedit.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ImageEdit/imageedit.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageEdit_t {
    const uint offsetsAndSize[34];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ImageEdit_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ImageEdit_t qt_meta_stringdata_ImageEdit = {
    {
QT_MOC_LITERAL(0, 9), // "ImageEdit"
QT_MOC_LITERAL(10, 14), // "setCircleColor"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 3), // "hue"
QT_MOC_LITERAL(30, 7), // "setText"
QT_MOC_LITERAL(38, 7), // "newText"
QT_MOC_LITERAL(46, 4), // "open"
QT_MOC_LITERAL(51, 6), // "saveAs"
QT_MOC_LITERAL(58, 4), // "copy"
QT_MOC_LITERAL(63, 5), // "paste"
QT_MOC_LITERAL(69, 6), // "zoomIn"
QT_MOC_LITERAL(76, 7), // "zoomOut"
QT_MOC_LITERAL(84, 10), // "normalSize"
QT_MOC_LITERAL(95, 10), // "doubleSize"
QT_MOC_LITERAL(106, 13), // "quadrupleSize"
QT_MOC_LITERAL(120, 11), // "fitToWindow"
QT_MOC_LITERAL(132, 11) // "circleColor"

    },
    "ImageEdit\0setCircleColor\0\0hue\0setText\0"
    "newText\0open\0saveAs\0copy\0paste\0zoomIn\0"
    "zoomOut\0normalSize\0doubleSize\0"
    "quadrupleSize\0fitToWindow\0circleColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageEdit[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       1,  102, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   86,    2, 0x0a,    2 /* Public */,
       4,    1,   89,    2, 0x0a,    4 /* Public */,
       6,    0,   92,    2, 0x08,    6 /* Private */,
       7,    0,   93,    2, 0x08,    7 /* Private */,
       8,    0,   94,    2, 0x08,    8 /* Private */,
       9,    0,   95,    2, 0x08,    9 /* Private */,
      10,    0,   96,    2, 0x08,   10 /* Private */,
      11,    0,   97,    2, 0x08,   11 /* Private */,
      12,    0,   98,    2, 0x08,   12 /* Private */,
      13,    0,   99,    2, 0x08,   13 /* Private */,
      14,    0,  100,    2, 0x08,   14 /* Private */,
      15,    0,  101,    2, 0x08,   15 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      16, QMetaType::Int, 0x00015103, uint(-1), 0,

       0        // eod
};

void ImageEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageEdit *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setCircleColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->open(); break;
        case 3: _t->saveAs(); break;
        case 4: _t->copy(); break;
        case 5: _t->paste(); break;
        case 6: _t->zoomIn(); break;
        case 7: _t->zoomOut(); break;
        case 8: _t->normalSize(); break;
        case 9: _t->doubleSize(); break;
        case 10: _t->quadrupleSize(); break;
        case 11: _t->fitToWindow(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ImageEdit *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->circleColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ImageEdit *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCircleColor(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject ImageEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ImageEdit.offsetsAndSize,
    qt_meta_data_ImageEdit,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ImageEdit_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<ImageEdit, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ImageEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageEdit.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ImageEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
