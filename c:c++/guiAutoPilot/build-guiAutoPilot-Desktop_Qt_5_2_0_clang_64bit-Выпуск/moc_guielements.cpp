/****************************************************************************
** Meta object code from reading C++ file 'guielements.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../guiAutoPilot/guielements.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guielements.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HeightLevelWidget_t {
    QByteArrayData data[4];
    char stringdata[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_HeightLevelWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_HeightLevelWidget_t qt_meta_stringdata_HeightLevelWidget = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 10),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 6)
    },
    "HeightLevelWidget\0set_height\0\0height\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HeightLevelWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void HeightLevelWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HeightLevelWidget *_t = static_cast<HeightLevelWidget *>(_o);
        switch (_id) {
        case 0: _t->set_height((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject HeightLevelWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HeightLevelWidget.data,
      qt_meta_data_HeightLevelWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *HeightLevelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HeightLevelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HeightLevelWidget.stringdata))
        return static_cast<void*>(const_cast< HeightLevelWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int HeightLevelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_HeadingAngleWidget_t {
    QByteArrayData data[4];
    char stringdata[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_HeadingAngleWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_HeadingAngleWidget_t qt_meta_stringdata_HeadingAngleWidget = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 9),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 5)
    },
    "HeadingAngleWidget\0set_angle\0\0angle\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HeadingAngleWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void HeadingAngleWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HeadingAngleWidget *_t = static_cast<HeadingAngleWidget *>(_o);
        switch (_id) {
        case 0: _t->set_angle((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject HeadingAngleWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HeadingAngleWidget.data,
      qt_meta_data_HeadingAngleWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *HeadingAngleWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HeadingAngleWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HeadingAngleWidget.stringdata))
        return static_cast<void*>(const_cast< HeadingAngleWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int HeadingAngleWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_StateButton_t {
    QByteArrayData data[1];
    char stringdata[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_StateButton_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_StateButton_t qt_meta_stringdata_StateButton = {
    {
QT_MOC_LITERAL(0, 0, 11)
    },
    "StateButton\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StateButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void StateButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject StateButton::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StateButton.data,
      qt_meta_data_StateButton,  qt_static_metacall, 0, 0}
};


const QMetaObject *StateButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StateButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateButton.stringdata))
        return static_cast<void*>(const_cast< StateButton*>(this));
    return QWidget::qt_metacast(_clname);
}

int StateButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
