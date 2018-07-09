/****************************************************************************
** Meta object code from reading C++ file 'swelcomepage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../welcome_page/swelcomepage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'swelcomepage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SWelcomePage_t {
    QByteArrayData data[13];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SWelcomePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SWelcomePage_t qt_meta_stringdata_SWelcomePage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SWelcomePage"
QT_MOC_LITERAL(1, 13, 9), // "createNew"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "openExisting"
QT_MOC_LITERAL(4, 37, 4), // "path"
QT_MOC_LITERAL(5, 42, 21), // "on_buttonOpen_clicked"
QT_MOC_LITERAL(6, 64, 8), // "openFile"
QT_MOC_LITERAL(7, 73, 8), // "fileName"
QT_MOC_LITERAL(8, 82, 13), // "createNewFile"
QT_MOC_LITERAL(9, 96, 17), // "recentFileClicked"
QT_MOC_LITERAL(10, 114, 11), // "clearLayout"
QT_MOC_LITERAL(11, 126, 8), // "QLayout*"
QT_MOC_LITERAL(12, 135, 6) // "layout"

    },
    "SWelcomePage\0createNew\0\0openExisting\0"
    "path\0on_buttonOpen_clicked\0openFile\0"
    "fileName\0createNewFile\0recentFileClicked\0"
    "clearLayout\0QLayout*\0layout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SWelcomePage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   53,    2, 0x08 /* Private */,
       6,    1,   54,    2, 0x08 /* Private */,
       8,    1,   57,    2, 0x08 /* Private */,
       9,    1,   60,    2, 0x08 /* Private */,
      10,    1,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void SWelcomePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SWelcomePage *_t = static_cast<SWelcomePage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createNew(); break;
        case 1: _t->openExisting((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_buttonOpen_clicked(); break;
        case 3: _t->openFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->createNewFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->recentFileClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->clearLayout((*reinterpret_cast< QLayout*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLayout* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SWelcomePage::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SWelcomePage::createNew)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SWelcomePage::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SWelcomePage::openExisting)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SWelcomePage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SWelcomePage.data,
      qt_meta_data_SWelcomePage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SWelcomePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SWelcomePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SWelcomePage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SWelcomePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SWelcomePage::createNew()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SWelcomePage::openExisting(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
