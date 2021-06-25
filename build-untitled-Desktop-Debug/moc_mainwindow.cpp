/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../untitled/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AboutDialog_t {
    QByteArrayData data[3];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AboutDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AboutDialog_t qt_meta_stringdata_AboutDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AboutDialog"
QT_MOC_LITERAL(1, 12, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 34, 0) // ""

    },
    "AboutDialog\0on_pushButton_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AboutDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void AboutDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AboutDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject AboutDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_AboutDialog.data,
    qt_meta_data_AboutDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AboutDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AboutDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AboutDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AboutDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_Prefer_nastr_t {
    QByteArrayData data[3];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Prefer_nastr_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Prefer_nastr_t qt_meta_stringdata_Prefer_nastr = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Prefer_nastr"
QT_MOC_LITERAL(1, 13, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 35, 0) // ""

    },
    "Prefer_nastr\0on_pushButton_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Prefer_nastr[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Prefer_nastr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Prefer_nastr *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject Prefer_nastr::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Prefer_nastr.data,
    qt_meta_data_Prefer_nastr,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Prefer_nastr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Prefer_nastr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Prefer_nastr.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Prefer_nastr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[58];
    char stringdata0[745];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "savesettings"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "name"
QT_MOC_LITERAL(4, 30, 8), // "baudrate"
QT_MOC_LITERAL(5, 39, 8), // "DataBits"
QT_MOC_LITERAL(6, 48, 6), // "Parity"
QT_MOC_LITERAL(7, 55, 8), // "StopBits"
QT_MOC_LITERAL(8, 64, 11), // "FlowControl"
QT_MOC_LITERAL(9, 76, 13), // "doubleClicked"
QT_MOC_LITERAL(10, 90, 11), // "QModelIndex"
QT_MOC_LITERAL(11, 102, 11), // "cellclicked"
QT_MOC_LITERAL(12, 114, 3), // "row"
QT_MOC_LITERAL(13, 118, 6), // "column"
QT_MOC_LITERAL(14, 125, 7), // "newFile"
QT_MOC_LITERAL(15, 133, 4), // "open"
QT_MOC_LITERAL(16, 138, 4), // "Save"
QT_MOC_LITERAL(17, 143, 6), // "SaveAs"
QT_MOC_LITERAL(18, 150, 12), // "closeAllBase"
QT_MOC_LITERAL(19, 163, 9), // "pageSetup"
QT_MOC_LITERAL(20, 173, 9), // "pagePrint"
QT_MOC_LITERAL(21, 183, 8), // "closeApp"
QT_MOC_LITERAL(22, 192, 6), // "addRow"
QT_MOC_LITERAL(23, 199, 9), // "removeRow"
QT_MOC_LITERAL(24, 209, 10), // "readPribor"
QT_MOC_LITERAL(25, 220, 11), // "writePribor"
QT_MOC_LITERAL(26, 232, 12), // "settingsPage"
QT_MOC_LITERAL(27, 245, 8), // "helpKonf"
QT_MOC_LITERAL(28, 254, 9), // "aboutKonf"
QT_MOC_LITERAL(29, 264, 14), // "openRecentFile"
QT_MOC_LITERAL(30, 279, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(31, 307, 5), // "index"
QT_MOC_LITERAL(32, 313, 12), // "printPreview"
QT_MOC_LITERAL(33, 326, 9), // "QPrinter*"
QT_MOC_LITERAL(34, 336, 7), // "printer"
QT_MOC_LITERAL(35, 344, 14), // "setCurrentFile"
QT_MOC_LITERAL(36, 359, 8), // "fileName"
QT_MOC_LITERAL(37, 368, 23), // "updateRecentFileActions"
QT_MOC_LITERAL(38, 392, 12), // "strippedName"
QT_MOC_LITERAL(39, 405, 12), // "fullFileName"
QT_MOC_LITERAL(40, 418, 10), // "printTable"
QT_MOC_LITERAL(41, 429, 9), // "isPreview"
QT_MOC_LITERAL(42, 439, 8), // "loadFile"
QT_MOC_LITERAL(43, 448, 13), // "onDataChanged"
QT_MOC_LITERAL(44, 462, 7), // "topLeft"
QT_MOC_LITERAL(45, 470, 11), // "bottomRight"
QT_MOC_LITERAL(46, 482, 25), // "on_actionSaveAs_triggered"
QT_MOC_LITERAL(47, 508, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(48, 532, 23), // "on_pushButton_9_clicked"
QT_MOC_LITERAL(49, 556, 12), // "timerTimeout"
QT_MOC_LITERAL(50, 569, 22), // "onCheckBoxHeaderClick1"
QT_MOC_LITERAL(51, 592, 22), // "onCheckBoxHeaderClick2"
QT_MOC_LITERAL(52, 615, 29), // "copyChannelNamesToTableWidget"
QT_MOC_LITERAL(53, 645, 10), // "selectRows"
QT_MOC_LITERAL(54, 656, 14), // "setcolorincell"
QT_MOC_LITERAL(55, 671, 23), // "on_actionPLUS_triggered"
QT_MOC_LITERAL(56, 695, 25), // "on_actionSave_2_triggered"
QT_MOC_LITERAL(57, 721, 23) // "on_actionRead_triggered"

    },
    "MainWindow\0savesettings\0\0name\0baudrate\0"
    "DataBits\0Parity\0StopBits\0FlowControl\0"
    "doubleClicked\0QModelIndex\0cellclicked\0"
    "row\0column\0newFile\0open\0Save\0SaveAs\0"
    "closeAllBase\0pageSetup\0pagePrint\0"
    "closeApp\0addRow\0removeRow\0readPribor\0"
    "writePribor\0settingsPage\0helpKonf\0"
    "aboutKonf\0openRecentFile\0"
    "on_tabWidget_currentChanged\0index\0"
    "printPreview\0QPrinter*\0printer\0"
    "setCurrentFile\0fileName\0updateRecentFileActions\0"
    "strippedName\0fullFileName\0printTable\0"
    "isPreview\0loadFile\0onDataChanged\0"
    "topLeft\0bottomRight\0on_actionSaveAs_triggered\0"
    "on_pushButton_7_clicked\0on_pushButton_9_clicked\0"
    "timerTimeout\0onCheckBoxHeaderClick1\0"
    "onCheckBoxHeaderClick2\0"
    "copyChannelNamesToTableWidget\0selectRows\0"
    "setcolorincell\0on_actionPLUS_triggered\0"
    "on_actionSave_2_triggered\0"
    "on_actionRead_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    6,  209,    2, 0x06 /* Public */,
       9,    1,  222,    2, 0x06 /* Public */,
      11,    2,  225,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,  230,    2, 0x08 /* Private */,
      15,    0,  231,    2, 0x08 /* Private */,
      16,    0,  232,    2, 0x08 /* Private */,
      17,    0,  233,    2, 0x08 /* Private */,
      18,    0,  234,    2, 0x08 /* Private */,
      19,    0,  235,    2, 0x08 /* Private */,
      20,    0,  236,    2, 0x08 /* Private */,
      21,    0,  237,    2, 0x08 /* Private */,
      22,    0,  238,    2, 0x08 /* Private */,
      23,    0,  239,    2, 0x08 /* Private */,
      24,    0,  240,    2, 0x08 /* Private */,
      25,    0,  241,    2, 0x08 /* Private */,
      26,    0,  242,    2, 0x08 /* Private */,
      27,    0,  243,    2, 0x08 /* Private */,
      28,    0,  244,    2, 0x08 /* Private */,
      29,    0,  245,    2, 0x08 /* Private */,
      30,    1,  246,    2, 0x08 /* Private */,
      32,    1,  249,    2, 0x08 /* Private */,
      35,    1,  252,    2, 0x08 /* Private */,
      37,    0,  255,    2, 0x08 /* Private */,
      38,    1,  256,    2, 0x08 /* Private */,
      40,    2,  259,    2, 0x08 /* Private */,
      42,    1,  264,    2, 0x08 /* Private */,
      43,    2,  267,    2, 0x08 /* Private */,
      46,    0,  272,    2, 0x08 /* Private */,
      47,    0,  273,    2, 0x08 /* Private */,
      48,    0,  274,    2, 0x08 /* Private */,
      49,    0,  275,    2, 0x08 /* Private */,
      50,    0,  276,    2, 0x08 /* Private */,
      51,    0,  277,    2, 0x08 /* Private */,
      52,    0,  278,    2, 0x08 /* Private */,
      53,    0,  279,    2, 0x08 /* Private */,
      54,    2,  280,    2, 0x08 /* Private */,
      55,    0,  285,    2, 0x08 /* Private */,
      56,    0,  286,    2, 0x08 /* Private */,
      57,    0,  287,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,

 // slots: parameters
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, 0x80000000 | 33,   34,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString,   39,
    QMetaType::Void, 0x80000000 | 33, QMetaType::Bool,   34,   41,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,   44,   45,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->savesettings((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 1: _t->doubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->cellclicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->newFile(); break;
        case 4: _t->open(); break;
        case 5: _t->Save(); break;
        case 6: _t->SaveAs(); break;
        case 7: _t->closeAllBase(); break;
        case 8: _t->pageSetup(); break;
        case 9: _t->pagePrint(); break;
        case 10: _t->closeApp(); break;
        case 11: _t->addRow(); break;
        case 12: _t->removeRow(); break;
        case 13: _t->readPribor(); break;
        case 14: _t->writePribor(); break;
        case 15: _t->settingsPage(); break;
        case 16: _t->helpKonf(); break;
        case 17: _t->aboutKonf(); break;
        case 18: _t->openRecentFile(); break;
        case 19: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->printPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 21: _t->setCurrentFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->updateRecentFileActions(); break;
        case 23: { QString _r = _t->strippedName((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 24: _t->printTable((*reinterpret_cast< QPrinter*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 25: _t->loadFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: _t->onDataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 27: _t->on_actionSaveAs_triggered(); break;
        case 28: _t->on_pushButton_7_clicked(); break;
        case 29: _t->on_pushButton_9_clicked(); break;
        case 30: _t->timerTimeout(); break;
        case 31: _t->onCheckBoxHeaderClick1(); break;
        case 32: _t->onCheckBoxHeaderClick2(); break;
        case 33: _t->copyChannelNamesToTableWidget(); break;
        case 34: _t->selectRows(); break;
        case 35: _t->setcolorincell((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 36: _t->on_actionPLUS_triggered(); break;
        case 37: _t->on_actionSave_2_triggered(); break;
        case 38: _t->on_actionRead_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString , int , int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::savesettings)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QModelIndex );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::doubleClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::cellclicked)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 39;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::savesettings(QString _t1, int _t2, int _t3, int _t4, int _t5, int _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::doubleClicked(QModelIndex _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::cellclicked(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
