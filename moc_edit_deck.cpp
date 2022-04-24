/****************************************************************************
** Meta object code from reading C++ file 'edit_deck.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "edit_deck.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'edit_deck.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_edit_deck_t {
    QByteArrayData data[17];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_edit_deck_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_edit_deck_t qt_meta_stringdata_edit_deck = {
    {
QT_MOC_LITERAL(0, 0, 9), // "edit_deck"
QT_MOC_LITERAL(1, 10, 25), // "refresh_decks_edit_signal"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 12), // "provide_text"
QT_MOC_LITERAL(4, 50, 6), // "string"
QT_MOC_LITERAL(5, 57, 6), // "cursor"
QT_MOC_LITERAL(6, 64, 13), // "update_widget"
QT_MOC_LITERAL(7, 78, 11), // "update_deck"
QT_MOC_LITERAL(8, 90, 27), // "on_ButtonRemoveDeck_clicked"
QT_MOC_LITERAL(9, 118, 22), // "on_ButtonReset_clicked"
QT_MOC_LITERAL(10, 141, 27), // "on_ButtonCancelEdit_clicked"
QT_MOC_LITERAL(11, 169, 25), // "on_ButtonSaveExit_clicked"
QT_MOC_LITERAL(12, 195, 41), // "on_lineEditDeckName_cursorPos..."
QT_MOC_LITERAL(13, 237, 4), // "arg1"
QT_MOC_LITERAL(14, 242, 4), // "arg2"
QT_MOC_LITERAL(15, 247, 15), // "keyboard_closed"
QT_MOC_LITERAL(16, 263, 3) // "log"

    },
    "edit_deck\0refresh_decks_edit_signal\0"
    "\0provide_text\0string\0cursor\0update_widget\0"
    "update_deck\0on_ButtonRemoveDeck_clicked\0"
    "on_ButtonReset_clicked\0"
    "on_ButtonCancelEdit_clicked\0"
    "on_ButtonSaveExit_clicked\0"
    "on_lineEditDeckName_cursorPositionChanged\0"
    "arg1\0arg2\0keyboard_closed\0log"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_edit_deck[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    2,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   75,    2, 0x0a /* Public */,
       7,    0,   80,    2, 0x0a /* Public */,
       8,    0,   81,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    2,   85,    2, 0x08 /* Private */,
      15,    0,   90,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      16,    0,   91,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,

       0        // eod
};

void edit_deck::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<edit_deck *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refresh_decks_edit_signal(); break;
        case 1: _t->provide_text((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->update_widget((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->update_deck(); break;
        case 4: _t->on_ButtonRemoveDeck_clicked(); break;
        case 5: _t->on_ButtonReset_clicked(); break;
        case 6: _t->on_ButtonCancelEdit_clicked(); break;
        case 7: _t->on_ButtonSaveExit_clicked(); break;
        case 8: _t->on_lineEditDeckName_cursorPositionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->keyboard_closed(); break;
        case 10: _t->log(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (edit_deck::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&edit_deck::refresh_decks_edit_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (edit_deck::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&edit_deck::provide_text)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject edit_deck::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_edit_deck.data,
    qt_meta_data_edit_deck,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *edit_deck::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *edit_deck::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_edit_deck.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int edit_deck::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void edit_deck::refresh_decks_edit_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void edit_deck::provide_text(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
