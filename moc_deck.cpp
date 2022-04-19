/****************************************************************************
** Meta object code from reading C++ file 'deck.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "deck.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deck.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_deck_t {
    QByteArrayData data[9];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_deck_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_deck_t qt_meta_stringdata_deck = {
    {
QT_MOC_LITERAL(0, 0, 4), // "deck"
QT_MOC_LITERAL(1, 5, 20), // "refresh_decks_signal"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 9), // "play_deck"
QT_MOC_LITERAL(4, 37, 4), // "QDir"
QT_MOC_LITERAL(5, 42, 13), // "set_deck_name"
QT_MOC_LITERAL(6, 56, 18), // "refresh_decks_slot"
QT_MOC_LITERAL(7, 75, 25), // "on_EditDeckbutton_clicked"
QT_MOC_LITERAL(8, 101, 29) // "on_DeckNamePlayButton_clicked"

    },
    "deck\0refresh_decks_signal\0\0play_deck\0"
    "QDir\0set_deck_name\0refresh_decks_slot\0"
    "on_EditDeckbutton_clicked\0"
    "on_DeckNamePlayButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_deck[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   48,    2, 0x0a /* Public */,
       6,    0,   51,    2, 0x0a /* Public */,
       7,    0,   52,    2, 0x08 /* Private */,
       8,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void deck::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<deck *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refresh_decks_signal(); break;
        case 1: _t->play_deck((*reinterpret_cast< QDir(*)>(_a[1]))); break;
        case 2: _t->set_deck_name((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->refresh_decks_slot(); break;
        case 4: _t->on_EditDeckbutton_clicked(); break;
        case 5: _t->on_DeckNamePlayButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (deck::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&deck::refresh_decks_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (deck::*)(QDir );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&deck::play_deck)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject deck::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_deck.data,
    qt_meta_data_deck,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *deck::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *deck::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_deck.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int deck::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void deck::refresh_decks_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void deck::play_deck(QDir _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
