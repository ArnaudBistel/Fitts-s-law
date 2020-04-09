/****************************************************************************
** Meta object code from reading C++ file 'homepage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../homepage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'homepage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HomePage_t {
    QByteArrayData data[14];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HomePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HomePage_t qt_meta_stringdata_HomePage = {
    {
QT_MOC_LITERAL(0, 0, 8), // "HomePage"
QT_MOC_LITERAL(1, 9, 15), // "changeInterface"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "name"
QT_MOC_LITERAL(4, 31, 11), // "launch_test"
QT_MOC_LITERAL(5, 43, 4), // "setA"
QT_MOC_LITERAL(6, 48, 1), // "a"
QT_MOC_LITERAL(7, 50, 4), // "setB"
QT_MOC_LITERAL(8, 55, 1), // "b"
QT_MOC_LITERAL(9, 57, 15), // "setTargetNumber"
QT_MOC_LITERAL(10, 73, 1), // "n"
QT_MOC_LITERAL(11, 75, 17), // "setTargetSizeMini"
QT_MOC_LITERAL(12, 93, 1), // "m"
QT_MOC_LITERAL(13, 95, 16) // "setTargetSizeMax"

    },
    "HomePage\0changeInterface\0\0name\0"
    "launch_test\0setA\0a\0setB\0b\0setTargetNumber\0"
    "n\0setTargetSizeMini\0m\0setTargetSizeMax"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HomePage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x0a /* Public */,
       5,    1,   53,    2, 0x0a /* Public */,
       7,    1,   56,    2, 0x0a /* Public */,
       9,    1,   59,    2, 0x0a /* Public */,
      11,    1,   62,    2, 0x0a /* Public */,
      13,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void HomePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HomePage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeInterface((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->launch_test(); break;
        case 2: _t->setA((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->setB((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->setTargetNumber((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setTargetSizeMini((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setTargetSizeMax((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HomePage::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HomePage::changeInterface)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HomePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_HomePage.data,
    qt_meta_data_HomePage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HomePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HomePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HomePage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int HomePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void HomePage::changeInterface(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
