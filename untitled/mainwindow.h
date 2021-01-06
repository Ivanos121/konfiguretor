#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>
#include "QtSql"
#include "QSqlDatabase"
#include <QSqlError>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QAbstractTableModel>
#include <QString>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>
#include "align.h"
#include <QTableView>
#include <QPushButton>
#include "checkboxheader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void savesettings(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
    void doubleClicked(QModelIndex);

private slots:
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void timerTimeout();
    void on_actionSave_triggered();
    void onCheckBoxHeaderClick1();
    void onCheckBoxHeaderClick2();
    void copyChannelNamesToTableWidget();

private:
    Ui::MainWindow *ui;
    QSqlDatabase sdb;
    QSqlTableModel *model;
    void crc_schet();
    QTimer timer;
    CheckBoxHeader* headerr;
    QLabel* label;
    QLabel* label2;
    QTimer *tmr;

    void stopGetData();
};


#endif // MAINWINDOW_H
