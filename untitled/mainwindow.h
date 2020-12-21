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
#include "mytableview.h"
#include <QTableView>

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

private slots:
    void on_pushButton_7_clicked();
    void on_pushButton_clicked();
    void on_pushButton_9_clicked();
    void changeStateCheckBox(QModelIndex index);
    void timerTimeout();

private:
    Ui::MainWindow *ui;
    QSqlDatabase sdb;
    MyTableView *tableViews;
    void crc_schet();
    QTimer timer;
};


#endif // MAINWINDOW_H