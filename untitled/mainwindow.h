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
#include <QProgressBar>

#include <QSet>

#include "checkboxheader.h"
#include "paintdelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSet<int> changedRows;
    QSet<QPoint> disabledCells;
    QColor disabledCellBackgroundColor;
    QColor changedColumnBackgroundColor;

signals:
    void savesettings(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
    void doubleClicked(QModelIndex);
    void cellclicked(int row , int column );

private slots:
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void timerTimeout();
    void on_actionSave_triggered();
    void onCheckBoxHeaderClick1();
    void onCheckBoxHeaderClick2();
    void copyChannelNamesToTableWidget();
    void selectRows();
    void setcolorincell(int row, int column);

    void on_action_triggered();

    void on_action_2_triggered();

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

    QProgressBar *progress;

    void stopGetData();
    void setDisabledCells();
    QSerialPort* openArchiverPort();
};

inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}


#endif // MAINWINDOW_H
