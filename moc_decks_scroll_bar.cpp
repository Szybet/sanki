/****************************************************************************
** Meta object code from reading C++ file 'decks_scroll_bar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "decks_scroll_bar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'decks_scroll_bar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_decks_scroll_bar_t {
    QByteArrayData data[7];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_decks_scroll_bar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_decks_scroll_bar_t qt_meta_stringdata_decks_scroll_bar = {
    {
QT_MOC_LITERAL(0, 0, 16), // "decks_scroll_bar"
QT_MOC_LITERAL(1, 17, 12), // "remove_decks"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 16), // "play_deck_signal"
QT_MOC_LITERAL(4, 48, 4), // "QDir"
QT_MOC_LITERAL(5, 53, 12), // "update_decks"
QT_MOC_LITERAL(6, 66, 15) // "play_deck_slott"

    },
    "decks_scroll_bar\0remove_decks\0\0"
    "play_deck_signal\0QDir\0update_decks\0"
    "play_deck_slott"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_decks_scroll_bar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x0a /* Public */,
       6,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

       0        // eod
};

void decks_scroll_bar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<decks_scroll_bar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->remove_decks(); break;
        case 1: _t->play_deck_signal((*reinterpret_cast< QDir(*)>(_a[1]))); break;
        case 2: _t->update_decks(); break;
        case 3: _t->play_deck_slott((*reinterpret_cast< QDir(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (decks_scroll_bar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&decks_scroll_bar::remove_decks)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (decks_scroll_bar::*)(QDir );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&decks_scroll_bar::play_deck_signal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject decks_scroll_bar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_decks_scroll_bar.data,
    qt_meta_data_decks_scroll_bar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *decks_scroll_bar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *decks_scroll_bar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_decks_scroll_bar.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int decks_scroll_bar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void decks_scroll_bar::remove_decks()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void decks_scroll_bar::play_deck_signal(QDir _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
