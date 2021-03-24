#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>
#include <QMainWindow>
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
#include <QLabel>
#include <QSqlTableModel>
#include <QPrinter>
#include <QSet>
#include <QWebEngineView>

#include "checkboxheader.h"
#include "paintdelegate.h"
#include "ui_about_dialog.h"
#include "ui_settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);

private slots:
    void on_pushButton_clicked();

private:
    Ui::aboutDialog *ui;
};

class Prefer_nastr : public QDialog
{
    Q_OBJECT

public:
    explicit Prefer_nastr(QWidget *parent = nullptr);

private slots:
    void on_pushButton_clicked();

private:
    Ui::preferNastr *ui;
};

struct CurrentChannelParams
{
    uint16_t diapazon;
    uint16_t filter;
    float minimum;
    float maximum;
};

class QAction;
class QMenu;
class QTextEdit;
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
    void newFile();
    void open();
    void Save();
    void SaveAs();
    void closeAllBase();
    void pageSetup();
    void pagePrint();
    void closeApp();
    void addPage();
    void removePage();
    void readPribor();
    void writePribor();
    void settingsPage();
    void helpKonf();
    void aboutKonf();

    void openRecentFile();
    void on_tabWidget_currentChanged(int index);
    void printPreview(QPrinter *printer);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);
    void printTable(QPrinter *printer, bool isPreview);
    void loadFile(const QString &fileName);
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
    void on_actionSaveAs_triggered();

    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void timerTimeout();
    void onCheckBoxHeaderClick1();
    void onCheckBoxHeaderClick2();
    void copyChannelNamesToTableWidget();
    void selectRows();
    void setcolorincell(int row, int column);

    void on_actionPLUS_triggered();

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

    QString curFile;
    QAction *separatorAct;
    QMenu *fileMenu;
    QMenu *modifyMenu;
    QMenu *priborMenu;
    QMenu *ingenerMenu;
    QMenu *recentFilesMenu;
    QMenu *helpMenu;
    bool isChanged = false;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];
    QString fileName;
    AboutDialog *rsc;
    Prefer_nastr *rsc2;
    QWebEngineView * view;


    void stopGetData();
    void setDisabledCells();
    QSerialPort* openArchiverPort();
    void createActions();
    void createMenus();
    void closeAllBase_Yes();
    void closeAllBase_No();
    void closeAllBase_Otmena();
    void closeEvent(QCloseEvent *event);
    void titleChanged(const QString &title);
    void open_sdb();

};

inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}


#endif // MAINWINDOW_H
