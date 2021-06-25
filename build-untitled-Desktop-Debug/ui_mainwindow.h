/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionSave_2;
    QAction *actionRead;
    QAction *actionNew;
    QAction *actionLoad;
    QAction *actionPLUS;
    QAction *actionSaveAs;
    QAction *actionMINUS;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionprint;
    QAction *actionPage_Setup;
    QAction *actionNastr;
    QAction *actionClose;
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;
    QWidget *tab_3;
    QGridLayout *gridLayout_8;
    QCustomPlot *widget_3;
    QTableWidget *tableWidget_2;
    QWidget *widget_2;
    QLabel *label_8;
    QLabel *label_9;
    QGroupBox *groupBox;
    QLabel *label_4;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_6;
    QPushButton *pushButton_7;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_9;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QLabel *label_5;
    QComboBox *comboBox_4;
    QLabel *label_6;
    QComboBox *comboBox_5;
    QLabel *label_7;
    QComboBox *comboBox_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1153, 1058);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/img/IM_48x48.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/img/document-save.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionSave_2 = new QAction(MainWindow);
        actionSave_2->setObjectName(QString::fromUtf8("actionSave_2"));
        QIcon icon2;
        QString iconThemeName = QString::fromUtf8("document-export");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/new/prefix1/img/document-export.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionSave_2->setIcon(icon2);
        actionRead = new QAction(MainWindow);
        actionRead->setObjectName(QString::fromUtf8("actionRead"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("document-import");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/new/prefix1/img/document-import.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionRead->setIcon(icon3);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon4;
        iconThemeName = QString::fromUtf8("document-new");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionNew->setIcon(icon4);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        QIcon icon5;
        iconThemeName = QString::fromUtf8("document-open");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionLoad->setIcon(icon5);
        actionPLUS = new QAction(MainWindow);
        actionPLUS->setObjectName(QString::fromUtf8("actionPLUS"));
        QIcon icon6;
        iconThemeName = QString::fromUtf8("archive-insert");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionPLUS->setIcon(icon6);
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        QIcon icon7;
        iconThemeName = QString::fromUtf8("document-save-as");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon7 = QIcon::fromTheme(iconThemeName);
        } else {
            icon7.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionSaveAs->setIcon(icon7);
        actionMINUS = new QAction(MainWindow);
        actionMINUS->setObjectName(QString::fromUtf8("actionMINUS"));
        QIcon icon8;
        iconThemeName = QString::fromUtf8("archive-remove");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon8 = QIcon::fromTheme(iconThemeName);
        } else {
            icon8.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionMINUS->setIcon(icon8);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon9;
        iconThemeName = QString::fromUtf8("system-help");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon9 = QIcon::fromTheme(iconThemeName);
        } else {
            icon9.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionHelp->setIcon(icon9);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/new/prefix1/img/IM_24_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon10);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon11;
        iconThemeName = QString::fromUtf8("application-exit");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon11 = QIcon::fromTheme(iconThemeName);
        } else {
            icon11.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionExit->setIcon(icon11);
        actionprint = new QAction(MainWindow);
        actionprint->setObjectName(QString::fromUtf8("actionprint"));
        QIcon icon12;
        iconThemeName = QString::fromUtf8("document-print");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon12 = QIcon::fromTheme(iconThemeName);
        } else {
            icon12.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionprint->setIcon(icon12);
        actionPage_Setup = new QAction(MainWindow);
        actionPage_Setup->setObjectName(QString::fromUtf8("actionPage_Setup"));
        QIcon icon13;
        iconThemeName = QString::fromUtf8("document-preview-archive");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon13 = QIcon::fromTheme(iconThemeName);
        } else {
            icon13.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionPage_Setup->setIcon(icon13);
        actionNastr = new QAction(MainWindow);
        actionNastr->setObjectName(QString::fromUtf8("actionNastr"));
        QIcon icon14;
        iconThemeName = QString::fromUtf8("configure");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon14 = QIcon::fromTheme(iconThemeName);
        } else {
            icon14.addFile(QString::fromUtf8(":/new/prefix1/img/configure_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionNastr->setIcon(icon14);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/new/prefix1/img/document-close_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose->setIcon(icon15);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView = new QTableView(tab);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMouseTracking(true);
        tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::CurrentChanged|QAbstractItemView::EditKeyPressed);

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableWidget = new QTableWidget(tab_2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_8 = new QGridLayout(tab_3);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        widget_3 = new QCustomPlot(tab_3);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(0, 0));
        widget_3->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_8->addWidget(widget_3, 0, 2, 1, 1);

        tableWidget_2 = new QTableWidget(tab_3);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setMinimumSize(QSize(450, 0));
        tableWidget_2->setMaximumSize(QSize(450, 16777215));

        gridLayout_8->addWidget(tableWidget_2, 0, 3, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 2, 1);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(300, 23));
        widget_2->setMaximumSize(QSize(350, 23));
        label_8 = new QLabel(widget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(0, 0, 81, 21));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_8->setFont(font);
        label_9 = new QLabel(widget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(80, 0, 351, 21));
        label_9->setFont(font);

        gridLayout_3->addWidget(widget_2, 0, 1, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(300, 0));
        groupBox->setMaximumSize(QSize(300, 16777215));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 20, 161, 17));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 60, 271, 339));
        gridLayout_6 = new QGridLayout(layoutWidget);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        pushButton_7 = new QPushButton(layoutWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setFocusPolicy(Qt::NoFocus);

        gridLayout_6->addWidget(pushButton_7, 0, 0, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButton_9 = new QPushButton(layoutWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setFocusPolicy(Qt::NoFocus);
        pushButton_9->setCheckable(true);

        gridLayout_5->addWidget(pushButton_9, 1, 0, 1, 2);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_4->addWidget(comboBox, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(layoutWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout_4->addWidget(comboBox_2, 1, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 2, 0, 1, 1);

        comboBox_3 = new QComboBox(layoutWidget);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        gridLayout_4->addWidget(comboBox_3, 2, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 3, 0, 1, 1);

        comboBox_4 = new QComboBox(layoutWidget);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        gridLayout_4->addWidget(comboBox_4, 3, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 4, 0, 1, 1);

        comboBox_5 = new QComboBox(layoutWidget);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));

        gridLayout_4->addWidget(comboBox_5, 4, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 5, 0, 1, 1);

        comboBox_6 = new QComboBox(layoutWidget);
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));

        gridLayout_4->addWidget(comboBox_6, 5, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 2);


        gridLayout_6->addLayout(gridLayout_5, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1153, 29));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setIconSize(QSize(22, 22));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionNew);
        toolBar->addAction(actionLoad);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSaveAs);
        toolBar->addAction(actionClose);
        toolBar->addAction(actionPage_Setup);
        toolBar->addAction(actionprint);
        toolBar->addSeparator();
        toolBar->addAction(actionPLUS);
        toolBar->addAction(actionMINUS);
        toolBar->addSeparator();
        toolBar->addAction(actionRead);
        toolBar->addAction(actionSave_2);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        comboBox_2->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\202\320\276\321\200 \320\270\320\267\320\274\320\265\321\200\320\270\321\202\320\265\320\273\321\214\320\275\321\213\321\205 \320\277\321\200\320\270\320\261\320\276\321\200\320\276\320\262", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\204\320\260\320\271\320\273 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\204\320\260\320\271\320\273 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_2->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265 ", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_2->setToolTip(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265 ", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_2->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+W", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRead->setText(QCoreApplication::translate("MainWindow", "\320\241\321\207\320\270\321\202\320\260\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
#if QT_CONFIG(tooltip)
        actionRead->setToolTip(QCoreApplication::translate("MainWindow", "\320\241\321\207\320\270\321\202\320\260\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionRead->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew->setText(QCoreApplication::translate("MainWindow", "C\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("MainWindow", "C\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoad->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\260\320\271\320\273 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
#if QT_CONFIG(tooltip)
        actionLoad->setToolTip(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\260\320\271\320\273 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionLoad->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPLUS->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", nullptr));
#if QT_CONFIG(tooltip)
        actionPLUS->setToolTip(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionPLUS->setShortcut(QCoreApplication::translate("MainWindow", "Shift+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSaveAs->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\204\320\260\320\271\320\273 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\272\320\260\320\272", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveAs->setToolTip(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\204\320\260\320\271\320\273 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\272\320\260\320\272", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSaveAs->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMINUS->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", nullptr));
#if QT_CONFIG(tooltip)
        actionMINUS->setToolTip(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionMINUS->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionHelp->setText(QCoreApplication::translate("MainWindow", "\320\240\321\203\320\272\320\276\320\262\320\276\320\264\321\201\321\202\320\262\320\276 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
#if QT_CONFIG(tooltip)
        actionHelp->setToolTip(QCoreApplication::translate("MainWindow", "\320\240\321\203\320\272\320\276\320\262\320\276\320\264\321\201\321\202\320\262\320\276 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionHelp->setShortcut(QCoreApplication::translate("MainWindow", "F1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
#if QT_CONFIG(tooltip)
        actionAbout->setToolTip(QCoreApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
#if QT_CONFIG(tooltip)
        actionExit->setToolTip(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionprint->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\207\320\260\321\202\321\214 \321\204\320\260\320\271\320\273\320\260 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
#if QT_CONFIG(tooltip)
        actionprint->setToolTip(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\207\320\260\321\202\321\214 \321\204\320\260\320\271\320\273\320\260 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionprint->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPage_Setup->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\201\320\274\320\276\321\202\321\200 \320\277\321\200\320\265\320\264\320\262\320\260\321\200\320\270\321\202\320\265\320\273\321\214\320\275\320\276\320\271 \320\277\320\265\321\207\320\260\321\202\320\270", nullptr));
#if QT_CONFIG(tooltip)
        actionPage_Setup->setToolTip(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\201\320\274\320\276\321\202\321\200 \320\277\321\200\320\265\320\264\320\262\320\260\321\200\320\270\321\202\320\265\320\273\321\214\320\275\320\276\320\271 \320\277\320\265\321\207\320\260\321\202\320\270", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionPage_Setup->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNastr->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
#if QT_CONFIG(tooltip)
        actionNastr->setToolTip(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNastr->setShortcut(QCoreApplication::translate("MainWindow", "Alt+F12", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClose->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
#if QT_CONFIG(tooltip)
        actionClose->setToolTip(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionClose->setShortcut(QCoreApplication::translate("MainWindow", "Esc", nullptr));
#endif // QT_CONFIG(shortcut)
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\272\320\260\320\275\320\260\320\273\320\276\320\262", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\275\321\213\321\205 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \320\263\321\200\320\260\321\204\320\270\320\272\320\276\320\262", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\237\320\240\320\230\320\221\320\236\320\240", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "textLabel1", nullptr));
        groupBox->setTitle(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276\321\200\321\202\320\276\320\262", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\201\320\272/\320\241\321\202\320\276\320\277", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200 \320\277\320\276\321\200\321\202\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 (\320\261\320\270\321\202/\321\201)", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\221\320\270\321\202\321\213 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\247\320\265\321\202\320\275\320\276\321\201\321\202\321\214", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\277\320\276\320\262\321\213\320\265 \320\261\320\270\321\202\321\213", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\276\321\202\320\276\320\272\320\276\320\274", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
