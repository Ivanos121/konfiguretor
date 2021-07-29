#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "model.h"
#include "port.h"
#include "archiverchannel.h"
#include "qcustomplot.h"
#include "checkboxdelegate.h"
#include "comboboxdelegate.h"
#include "comboboxvardelegate.h"
#include "comboboxmodbusdelegate.h"
#include "comboboxerrorarchivedelegate.h"
#include "comboboxbitdelegate.h"
#include "align.h"
#include "checkboxheader.h"
#include <qdebug.h>
#include "paintdelegate.h"
#include "pointcolumndelegate.h"
#include "comboboxcurrentdelegate.h"

#include <QCheckBox>
#include <QMouseEvent>
#include <QMessageBox>
#include <QLinearGradient>
#include <QTableView>
#include <QToolBar>
#include <QHeaderView>
#include <iostream>
#include <fstream>
#include <QPixmap>

static bool header_added = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , disabledCellBackgroundColor(180, 180, 180)
    , changedColumnBackgroundColor(144,238,144)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    createMenus();
    label=new QLabel(this);
    label2=new QLabel(this);
    ui->toolBar->addWidget(label);
    ui->toolBar->addWidget(label2);
    label->setPixmap(QPixmap(":/new/prefix1/img/IM_24_red.png"));
    label2->setText("  Связи нет");
    ui->label_9->setText("Загрузите файл");
    ui->tabWidget->setCurrentIndex(0);
    QString currentTabText = ui->tabWidget->tabText(0);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor"));
    ui->actionSave->setEnabled(false);
    ui->actionSaveAs->setEnabled(false);
    ui->actionClose->setEnabled(false);
    ui->actionprint->setEnabled(false);
    ui->actionPage_Setup->setEnabled(false);
    ui->actionRead->setEnabled(false);
    ui->actionSave_2->setEnabled(false);
    ui->actionPLUS->setEnabled(false);
    ui->actionMINUS->setEnabled(false);
    modifyMenu->setEnabled(false);
    priborMenu->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ui->groupBox->setEnabled(false);

    open_sdb();

    ui->comboBox_2->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
    ui->comboBox_2->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->comboBox_2->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->comboBox_2->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
    ui->comboBox_2->addItem(QLatin1String("Custom"));
    ui->comboBox_2->setCurrentIndex(3);
   // fill data bits
    ui->comboBox_3->addItem(QLatin1String("5"), QSerialPort::Data5);
    ui->comboBox_3->addItem(QLatin1String("6"), QSerialPort::Data6);
    ui->comboBox_3->addItem(QLatin1String("7"), QSerialPort::Data7);
    ui->comboBox_3->addItem(QLatin1String("8"), QSerialPort::Data8);
    ui->comboBox_3->setCurrentIndex(3);
   // fill parity
    ui->comboBox_4->addItem(QLatin1String("None"), QSerialPort::NoParity);
    ui->comboBox_4->addItem(QLatin1String("Even"), QSerialPort::EvenParity);
    ui->comboBox_4->addItem(QLatin1String("Odd"), QSerialPort::OddParity);
    ui->comboBox_4->addItem(QLatin1String("Mark"), QSerialPort::MarkParity);
    ui->comboBox_4->addItem(QLatin1String("Space"), QSerialPort::SpaceParity);
   // fill stop bits
    ui->comboBox_5->addItem(QLatin1String("1"), QSerialPort::OneStop);
    ui->comboBox_5->addItem(QLatin1String("2"), QSerialPort::TwoStop);
    #ifdef Q_OS_WIN
        ui->comboBox_5->addItem(QLatin1String("1.5"), QSerialPort::OneAndHalfStop);
    #endif
   // fill flow control
    ui->comboBox_6->addItem(QLatin1String("None"), QSerialPort::NoFlowControl);
    ui->comboBox_6->addItem(QLatin1String("RTS/CTS"), QSerialPort::HardwareControl);
    ui->comboBox_6->addItem(QLatin1String("XON/XOFF"), QSerialPort::SoftwareControl);

    connect(&timer, &QTimer::timeout, this, &MainWindow::timerTimeout);

//    //индикация работы связи с архиватором
//    label=new QLabel(this);
//    label2=new QLabel(this);
//    ui->toolBar->addWidget(label);
//    ui->toolBar->addWidget(label2);
//    label->setPixmap(QPixmap(":/new/prefix1/img/IM_24_red"));
//    label2->setText("  Связи нет");

//    connect(model, &QSqlTableModel::dataChanged,this, &MainWindow::selectRows);

//    setDisabledCells();

}

MainWindow::~MainWindow()
{
    delete ui;
}

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
}

void AboutDialog::on_pushButton_clicked()
{
    close();
}

Prefer_nastr::Prefer_nastr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preferNastr)
{
    ui->setupUi(this);
}

void Prefer_nastr::on_pushButton_clicked()
{
    close();
}

void MainWindow::open()
{
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Файл"));
    //fileMenu->addAction(newAct);
    fileMenu->addAction(ui->actionNew);
    fileMenu->addAction(ui->actionLoad);
    fileMenu->addAction(ui->actionSave);
    fileMenu->addAction(ui->actionSaveAs);
    fileMenu->addAction(ui->actionClose);
    separatorAct = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
    fileMenu->addAction(recentFileActs[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(ui->actionPage_Setup);
    fileMenu->addAction(ui->actionprint);
    fileMenu->addSeparator();
    fileMenu->addAction(ui->actionExit);
    updateRecentFileActions();

    menuBar()->addSeparator();

    modifyMenu = menuBar()->addMenu(tr("&Редактирование"));
    modifyMenu->addAction(ui->actionPLUS);
    modifyMenu->addAction(ui->actionMINUS);

    menuBar()->addSeparator();

    priborMenu = menuBar()->addMenu(tr("&Программирование прибора"));
    priborMenu->addAction(ui->actionRead);
    priborMenu->addAction(ui->actionSave_2);

    menuBar()->addSeparator();

    ingenerMenu = menuBar()->addMenu(tr("&Инструменты"));
    ingenerMenu->addAction(ui->actionNastr);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Справка"));
    helpMenu->addAction(ui->actionHelp);
    helpMenu->addAction(ui->actionAbout);
}

void MainWindow::createActions()
{
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::open);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::Save);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::SaveAs);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeAllBase);

    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i], &QAction::triggered, this, &MainWindow::openRecentFile);
    }

    connect(ui->actionPage_Setup, &QAction::triggered, this, &MainWindow::pageSetup);
    connect(ui->actionprint, &QAction::triggered, this, &MainWindow::pagePrint);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::closeApp);
    connect(ui->actionPLUS, &QAction::triggered, this, &MainWindow::addRow);
    connect(ui->actionMINUS, &QAction::triggered, this, &MainWindow::removeRow);
    connect(ui->actionRead, &QAction::triggered, this, &MainWindow::readPribor);
    connect(ui->actionSave_2, &QAction::triggered, this, &MainWindow::writePribor);
    connect(ui->actionNastr, &QAction::triggered, this, &MainWindow::settingsPage);
    connect(ui->actionHelp, &QAction::triggered, this, &MainWindow::helpKonf);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::aboutKonf);
}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
    {
        fileName = action->data().toString();
        loadFile(fileName);
        int index = ui->tabWidget->currentIndex();
        QString currentTabText = ui->tabWidget->tabText(index);
        QFileInfo fi(fileName);
        QString base = fi.baseName();
        setWindowTitle(currentTabText + "@" + QString(base) + QString(" - Konfiguretor"));
    }
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowFilePath(curFile);

    QSettings settings("BRU", "konfiguretor");
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
    files.removeLast();

    settings.setValue("recentFileList", files);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin)
            mainWin->updateRecentFileActions();
    }
}

void MainWindow::updateRecentFileActions()
{
    QSettings settings("BRU", "konfiguretor");
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    separatorAct->setVisible(numRecentFiles > 0);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::loadFile(const QString &fileName)
{
    // setWindowTitle(fileName + QString(" - IM View"));
     open_sdb();
     setCurrentFile(fileName);
     ui->actionSave->setEnabled(true);
     ui->actionSaveAs->setEnabled(true);
     ui->actionClose->setEnabled(true);
     ui->actionprint->setEnabled(true);
     ui->actionPage_Setup->setEnabled(true);
     ui->actionRead->setEnabled(true);
     ui->actionSave_2->setEnabled(true);
     ui->actionPLUS->setEnabled(true);
     ui->actionMINUS->setEnabled(true);
     modifyMenu->setEnabled(true);
     priborMenu->setEnabled(true);
     ui->tabWidget->setEnabled(true);
     ui->groupBox->setEnabled(true);

     QFileInfo fi(fileName);
     QString base = fi.baseName();
     ui->label_9->setText(base);
     int index = ui->tabWidget->currentIndex();
     QString currentTabText = ui->tabWidget->tabText(index);
     setWindowTitle(currentTabText + "@" + QString(base) + QString(" - Konfiguretor"));

     connect(ui->tableView->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));
}

void MainWindow::closeAllBase()
{
    if(isChanged)
    {
        switch (QMessageBox::question(this, "Сохранить документ?", "Сохранить изменения перед закрытием  файла?", QMessageBox::Yes | QMessageBox::No |  QMessageBox::Cancel))
        {
        case QMessageBox::Yes:
            Save();
            sdb.close();
            QSqlDatabase::removeDatabase(fileName);
            model->clear();
            closeAllBase_Yes();
            break;
        case QMessageBox::Cancel:
            closeAllBase_Otmena();
            qDebug() << "bla bla bla";
            break;
        case QMessageBox::No:
            sdb.close();
            QSqlDatabase::removeDatabase(fileName);
            model->clear();
            isChanged=false;
            closeAllBase_No();
            break;
        default:
          break;
        }
    }
    else
    {
        sdb.close();
        QSqlDatabase::removeDatabase(fileName);
        model->clear();
        ui->label_2->setText("Загрузите файл конфигурации прибора");
        ui->tabWidget->setCurrentIndex(0);
        QString currentTabText = ui->tabWidget->tabText(0);
        setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor"));
        ui->tabWidget->setEnabled(false);
        ui->groupBox->setEnabled(false);
    }
}

void MainWindow::closeAllBase_Yes()
{
    ui->label_2->setText("Загрузите файл конфигурации прибора");
    ui->tabWidget->setCurrentIndex(0);
    QString currentTabText = ui->tabWidget->tabText(0);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor"));

    ui->actionSave->setEnabled(false);
    ui->actionSaveAs->setEnabled(false);
    ui->actionClose->setEnabled(false);
    ui->actionprint->setEnabled(false);
    ui->actionPage_Setup->setEnabled(false);
    ui->actionRead->setEnabled(false);
    ui->actionSave_2->setEnabled(false);
    ui->actionPLUS->setEnabled(false);
    ui->actionMINUS->setEnabled(false);
    sdb = QSqlDatabase::addDatabase("QSQLITE"); //объявление базы данных sqlite3
    sdb.setDatabaseName(QFileInfo(fileName).absoluteFilePath()); //подключение к базе данных
    modifyMenu->setEnabled(false);
    priborMenu->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ui->groupBox->setEnabled(false);
}

void MainWindow::closeAllBase_No()
{
    ui->label_2->setText("Загрузите файл конфигурации прибора");
    ui->tabWidget->setCurrentIndex(0);
    QString currentTabText = ui->tabWidget->tabText(0);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor"));
    ui->actionSave->setEnabled(false);
    ui->actionSaveAs->setEnabled(false);
    ui->actionClose->setEnabled(false);
    ui->actionprint->setEnabled(false);
    ui->actionPage_Setup->setEnabled(false);
    ui->actionRead->setEnabled(false);
    ui->actionSave_2->setEnabled(false);
    ui->actionPLUS->setEnabled(false);
    ui->actionMINUS->setEnabled(false);
    sdb = QSqlDatabase::addDatabase("QSQLITE"); //объявление базы данных sqlite3
    sdb.setDatabaseName(QFileInfo(fileName).absoluteFilePath()); //подключение к базе данных
    modifyMenu->setEnabled(false);
    priborMenu->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ui->groupBox->setEnabled(false);
}

void MainWindow::setcolorincell(int row, int column)
{
    if (column == 1)
    {
        row = ui->tableWidget_2->currentRow();
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget_2->item(row, column)->setBackground(chosenColor);
        ui->widget_3->setLineDataColor(row, chosenColor);
    }
}

void MainWindow::closeAllBase_Otmena()
{
    return;

}

void MainWindow::newFile()
{
    QString first="netdb_base.db";
    QString filter = "Файл конфигурации прибора (*.db);;Все файлы (*.*)";
    fileName = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", QDir::homePath(), filter);
    QFile::copy(first,fileName);

    open_sdb();
    int index = ui->tabWidget->currentIndex();
    QString currentTabText = ui->tabWidget->tabText(index);
    QFileInfo fi(fileName);
    QString base = fi.baseName();
    setWindowTitle(currentTabText + "@" + base + QString(" - Konfiguretor"));

    //инициализация базы данных sqlite3
     sdb = QSqlDatabase::addDatabase("QSQLITE"); //объявление базы данных sqlite3
     sdb.setDatabaseName(QFileInfo(fileName).absoluteFilePath()); //подключение к базе данных
     model = new Model; //создание модели QSqlTableModel
     model->setTable("Net settings"); //Установка для таблицы базы данных, с которой работает модель, tableName
     model->setEditStrategy(QSqlTableModel::OnManualSubmit); //Все изменения будут кэшироваться в модели до тех пор, пока не будет вызван сигнал submitAll()

     //загрузка данных в таблицу tableview
     model->select(); //Заполняет модель данными из таблицы, которая была установлена ​​с помощью setTable(), используя указанный фильтр и условие сортировки
     ui->tableView->setModel(model); //Устанавливает модель для представления
     ui->tableView->hideColumn(0); //скрытие столбца id

     ui->actionSave->setEnabled(true);
     ui->actionSaveAs->setEnabled(true);
     ui->actionClose->setEnabled(true);
     ui->actionprint->setEnabled(true);
     ui->actionPage_Setup->setEnabled(true);
     ui->actionRead->setEnabled(true);
     ui->actionSave_2->setEnabled(true);
     ui->actionPLUS->setEnabled(true);
     ui->actionMINUS->setEnabled(true);
     modifyMenu->setEnabled(true);
     priborMenu->setEnabled(true);
     ui->tabWidget->setEnabled(true);
     ui->groupBox->setEnabled(true);
     setCurrentFile(fileName);
     QFileInfo fi2(fileName);
     QString base2 = fi2.baseName();
     ui->label_9->setText(base);
     int index2 = ui->tabWidget->currentIndex();
     QString currentTabText2 = ui->tabWidget->tabText(index2);
     setWindowTitle(currentTabText2 + "@" + QString(base2) + QString(" - Konfiguretor"));

     connect(ui->tableView->model(), &QSqlTableModel::dataChanged, this, &MainWindow::onDataChanged);
     connect(model, &QSqlTableModel::dataChanged,this, &MainWindow::selectRows);
     setDisabledCells();
}

void MainWindow::open_sdb()
{
    //инициализация базы данных sqlite3
    sdb = QSqlDatabase::addDatabase("QSQLITE"); //объявление базы данных sqlite3
    sdb.setDatabaseName(QFileInfo(fileName).absoluteFilePath()); //подключение к базе данных

    model = new Model; //создание модели QSqlTableModel
    model->setTable("Net settings"); //Установка для таблицы базы данных, с которой работает модель, tableName
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //Все изменения будут кэшироваться в модели до тех пор, пока не будет вызван сигнал submitAll()

    if (!header_added)
    {
        //подключение заголовка таблицы
        headerr = new CheckBoxHeader(Qt::Horizontal,ui->tableView);  //создание заголовка tableview
        ui->tableView->setHorizontalHeader(headerr); //установка заголовка tableview и checkbox в первый столбец
        connect(headerr, &CheckBoxHeader::checkBoxClicked1, this, &MainWindow::onCheckBoxHeaderClick1); //подключение головного чекбокса к чекбоксам в первом столбце
        connect(headerr, &CheckBoxHeader::checkBoxClicked2, this, &MainWindow::onCheckBoxHeaderClick2); //подключение головного чекбокса к чекбоксам в первом столбце
        header_added = true;
    }

    //загрузка данных в таблицу tableview
    model->select(); //Заполняет модель данными из таблицы, которая была установлена ​​с помощью setTable(), используя указанный фильтр и условие сортировки
    ui->tableView->setModel(model); //Устанавливает модель для представления
    ui->tableView->hideColumn(0); //скрытие столбfalseца id

    //делегаты для создания чекбоксов
    CheckBoxDelegate* checkBoxDelegate = new CheckBoxDelegate(this); //создание делегата для создания чекбоксов
    ui->tableView->setItemDelegateForColumn(1, checkBoxDelegate); //загрузка делегата в первый столбец
    ui->tableView->setItemDelegateForColumn(2, checkBoxDelegate); //загрузка делегата во второй столбец

    //делегаты для создания комбобоксов
    ComboBoxDelegate* comboBoxDelegate = new ComboBoxDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(4, comboBoxDelegate); //загрузка делегата в четвертый столбец

    //делегаты для создания комбобоксов
    ComboBoxVarDelegate* comboBoxVarDelegate = new ComboBoxVarDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(7, comboBoxVarDelegate); //загрузка делегата в седьмой столбец

    //делегаты для создания комбобоксов
    ComboBoxModbusDelegate* comboboxmodbusdelegate = new ComboBoxModbusDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(11, comboboxmodbusdelegate); //загрузка делегата в одиннадцатый столбец

    //делегаты для создания комбобоксов
    ComboBoxBitDelegate* comboboxbitdelegate = new ComboBoxBitDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(14, comboboxbitdelegate); //загрузка делегата в одиннадцатый столбец

    //делегаты для создания комбобоксов
    ComboBoxErrorArchiveDelegate* comboboxerrorarchivedelegate = new ComboBoxErrorArchiveDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(9, comboboxerrorarchivedelegate); //загрузка делегата в одиннадцатый столбец

    //делегаты для создания комбобоксов
    ComboBoxCurrentDelegate* comboboxcurrentdelegate = new ComboBoxCurrentDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(17, comboboxcurrentdelegate); //загрузка делегата в одиннадцатый столбец

    PaintDelegate *paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(3, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(5, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(6, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(8, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(10, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(12, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(13, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(15, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(16, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
   // ui->tableView->setItemDelegateForColumn(17, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(18, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(19, paintdelegate);

    paintdelegate = new PaintDelegate(this); //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(20, paintdelegate);

    //настройка ширины столбцов
    QHeaderView *headers = ui->tableWidget->horizontalHeader(); //объявление указателя на горизонтальный заголовок
    headers->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме

    //настройки таблицы tableview
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked); //Редактирование начинается при двойном щелчке по элементу
    ui->tableView->setSelectionMode(QAbstractItemView :: SingleSelection); //нет выделения ячеек
 //  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents(); //Изменяет размер всех столбцов на основе подсказок размера делегата, используемого для визуализации каждого элемента в столбцах

    //настройка таблицы вывода данных
    ui->tableWidget->setRowCount(32); //задание количества строк таблицы
    ui->tableWidget->setColumnCount(6); //задание количества столбцов
    QStringList name; //объявление указателя на тип QStringList
    name << "№" << "Свойство" << "Значение" << "№" << "Свойство" << "Значение"; //перечисление заголовков
    ui->tableWidget->setHorizontalHeaderLabels(name); //установка заголовков в таблицу
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
    ui->tableWidget->setSelectionMode(QAbstractItemView :: NoSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
          ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
    }

    copyChannelNamesToTableWidget();

    for (int i=0; i<32; i++)
    {
           if (ui->tableWidget->item(i, 0) != 0)
            {
                 ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
                 ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
            }
    }
    for (int i=32; i<64; i++)
    {
           if (ui->tableWidget->item(i-32, 3) != 0)
            {
                 ui->tableWidget->item(i-32, 3)->setText(QString("%1").arg(i+1));
                 ui->tableWidget->item(i-32, 3)->setTextAlignment(Qt::AlignCenter);
            }
    }

    ui->widget_3->t_max = 0.1;
    ui->widget_3->U_max = 800.0;
    ui->widget_3->margin_bottom = 40;
    ui->widget_3->margin_left = 100;
    ui->widget_3->reset();

    std::vector<QColor> lineColors(64);

    for (int i = 0; i < 64; i++)
    {
        lineColors[i] = QColor(QRandomGenerator::global()->bounded(255),
                               QRandomGenerator::global()->bounded(255),
                               QRandomGenerator::global()->bounded(255));
        ui->widget_3->addDataLine(lineColors[i], 0);
    }

    ui->comboBox_2->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
    ui->comboBox_2->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->comboBox_2->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->comboBox_2->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
    ui->comboBox_2->addItem(QLatin1String("Custom"));
    ui->comboBox_2->setCurrentIndex(3);
   // fill data bits
    ui->comboBox_3->addItem(QLatin1String("5"), QSerialPort::Data5);
    ui->comboBox_3->addItem(QLatin1String("6"), QSerialPort::Data6);
    ui->comboBox_3->addItem(QLatin1String("7"), QSerialPort::Data7);
    ui->comboBox_3->addItem(QLatin1String("8"), QSerialPort::Data8);
    ui->comboBox_3->setCurrentIndex(3);
   // fill parity
    ui->comboBox_4->addItem(QLatin1String("None"), QSerialPort::NoParity);
    ui->comboBox_4->addItem(QLatin1String("Even"), QSerialPort::EvenParity);
    ui->comboBox_4->addItem(QLatin1String("Odd"), QSerialPort::OddParity);
    ui->comboBox_4->addItem(QLatin1String("Mark"), QSerialPort::MarkParity);
    ui->comboBox_4->addItem(QLatin1String("Space"), QSerialPort::SpaceParity);
   // fill stop bits
    ui->comboBox_5->addItem(QLatin1String("1"), QSerialPort::OneStop);
    ui->comboBox_5->addItem(QLatin1String("2"), QSerialPort::TwoStop);
    #ifdef Q_OS_WIN
        ui->comboBox_5->addItem(QLatin1String("1.5"), QSerialPort::OneAndHalfStop);
    #endif
   // fill flow control
    ui->comboBox_6->addItem(QLatin1String("None"), QSerialPort::NoFlowControl);
    ui->comboBox_6->addItem(QLatin1String("RTS/CTS"), QSerialPort::HardwareControl);
    ui->comboBox_6->addItem(QLatin1String("XON/XOFF"), QSerialPort::SoftwareControl);

    //connect(&timer, &QTimer::timeout, this, &MainWindow::timerTimeout);

//    //индикация работы связи с архиватором
//    label=new QLabel(this);
//    label2=new QLabel(this);
//    ui->toolBar->addWidget(label);
//    ui->toolBar->addWidget(label2);
//    label->setPixmap(QPixmap(":/new/prefix1/img/IM_24_red"));
//    label2->setText("  Связи нет");

    connect(model, &QSqlTableModel::dataChanged,this, &MainWindow::selectRows);

    setDisabledCells();

    //настройка таблицы вывода данных
    ui->tableWidget_2->setRowCount(64); //задание количества строк таблицы
    ui->tableWidget_2->setColumnCount(4); //задание количества столбцов
    QStringList name2; //объявление указателя на тип QStringList
    name2 << "№" << "Цвет" << "Свойство" << "Значение"; //перечисление заголовков
    ui->tableWidget_2->setHorizontalHeaderLabels(name2); //установка заголовков в таблицу
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: NoSelection);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_2->columnCount(); column++)
        {
          ui->tableWidget_2->setItem(row, column, new QTableWidgetItem());
        }

  //  ui->tableWidget_2->item(1, 1)->setBackground(QColor(0,0,255));
    }

    copyChannelNamesToTableWidget();

    for (int i=0; i<64; i++)
    {
        if (ui->tableWidget_2->item(i, 0) != 0)
        {
            ui->tableWidget_2->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_2->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    for (int i = 0; i < 64; i++)
    {
        QString text = model->data(model->index(i,3)).toString();

        if (ui->tableWidget_2->item(i,2) != 0)
        {
            ui->tableWidget_2->item(i,2)->setText(text);
        }
    }

    for (int i = 0; i < 64; i++)
    {
        ui->tableWidget_2->item(i, 1)->setBackground(lineColors[i]);
    }

    progress = new QProgressBar(ui->statusbar);
    progress->setVisible(false);
    ui->statusbar->addWidget(progress,1);
    progress->setTextVisible(false);
    setStyleSheet("QProgressBar {border: 2px solid grey;height: 15px} QProgressBar::chunk {background-color: #55FF55;width: 20px}");

    connect(ui->tableWidget_2, &QTableWidget::cellClicked,this, &MainWindow::setcolorincell);
}

void MainWindow::SaveAs()
{

}

void MainWindow::addRow()
{
    model->insertRow(model->rowCount());

    for(int y = 1; y <= 20; y++)
    {//взять каждую ячейку
        QString myData;
        QModelIndex myIndex, myIndex2;

        myIndex = ui->tableView->model()->index(model->rowCount() - 1, y, QModelIndex()); //Куда копируем
        myIndex2 = ui->tableView->model()->index(0, y, QModelIndex()); //откуда
        myData = ui->tableView->model()->data(myIndex2).toString(); //содержимое (можно QVariant)
        ui->tableView->model()->setData(myIndex, myData); //тадам-с!
    }

     onDataChanged(QModelIndex(), QModelIndex());

}

void MainWindow::removeRow()
{
    int selectRow = ui->tableView->currentIndex().row();
    if (selectRow >=0)
    {
        model->removeRow(selectRow);
    }
}

void MainWindow::pagePrint()
{
    QPrinter printer;
    printTable(&printer, false);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    QString currentTabText = ui->tabWidget->tabText(index);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor"));
    if(sdb.isOpen())
    {
        QFileInfo fi5(fileName);
        QString base5 = fi5.baseName();
        ui->label_2->setText(base5);
        QString currentTabText = ui->tabWidget->tabText(index);
        setWindowTitle(currentTabText + "@" + QString(base5) + QString(" - Konfiguretor"));
    }
}

void MainWindow::pageSetup()
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPageSize(QPageSize::A4));
    printer->setPageOrientation(QPageLayout::Landscape);
    printer->setFullPage(true);

    QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(printer);
    connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printPreview(QPrinter*)));
    printPreview->setWindowTitle("Preview Dialog");
    Qt::WindowFlags flags(Qt::WindowTitleHint);
    printPreview->setWindowFlags(flags);
    printPreview->showMaximized();
    printPreview->exec();
}

void MainWindow::printPreview(QPrinter *printer)
{
    printTable(printer, true);
}

void MainWindow::printTable(QPrinter *printer, bool isPreview)
{
    printer->setPageSize(QPageSize(QPageSize::A4));
    printer->setPageOrientation(QPageLayout::Landscape);
    printer->setFullPage(true);

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg(fileName)
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
            "<table border=1 cellspacing=0 cellpadding=2>\n";

        // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());

    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView->isColumnHidden(column))
                {
                    QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
    out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

    QTextDocument document;
    document.setHtml(strStream);

    if (isPreview)
    {
        document.print(printer);
    }
    else
    {
        QPrintDialog dialog(printer, NULL);
        if (dialog.exec() == QDialog::Accepted) {
            document.print(printer);
        }
    }
}

void MainWindow::settingsPage()
{
    QScreen *screen2 = QGuiApplication::primaryScreen();
        rsc2= new Prefer_nastr(this);
        rsc2->exec();
        rsc2->setGeometry(
            QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            rsc2->size(),
            screen2->geometry()));
}

void MainWindow::helpKonf()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &MainWindow::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("help_v1/index.html").absoluteFilePath()));
    view->setWindowIcon(QIcon::fromTheme("help-contents"));
    view->showMaximized();
}

void MainWindow::titleChanged(const QString &title)
{
    view->setWindowTitle(title);
}


void MainWindow::aboutKonf()
{
    QScreen *screen = QGuiApplication::primaryScreen();
        rsc= new AboutDialog(this);
        rsc->exec();
        rsc->setGeometry(
            QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            rsc->size(),
            screen->geometry()));
}

void MainWindow::closeApp()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *event)  // show prompt when user wants to close app
{
    if(isChanged)
    {
        switch (QMessageBox::question(this, "Сохранить документ?", "Сохранить?", QMessageBox::Yes | QMessageBox::No |  QMessageBox::Cancel))
        {
        case QMessageBox::Yes:
            Save();
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        case QMessageBox::No:
            event->accept();
        default:
          break;
        }
    }
    else
    {
        event->accept();
    }
}

void MainWindow::on_actionSaveAs_triggered()
{
    QString filter = "Файл конфигурации прибора (*.db);;Все файлы (*.*)";
    fileName = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", QDir::homePath(), filter);

}


void MainWindow::onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    QFileInfo fi(fileName);
    QString base = fi.baseName();
    int index = ui->tabWidget->currentIndex();
    QString currentTabText = ui->tabWidget->tabText(index);
    setWindowTitle(currentTabText + "@" + base + QString(" - Konfiguretor") + QString("*"));
    isChanged = true;
}



void MainWindow::on_pushButton_7_clicked()
{
    ui->comboBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
          ui->comboBox->addItem(info.portName());
          ui->comboBox->addItem("ttyMP0");
          ui->comboBox->addItem("ttyMP1");
          ui->comboBox->addItem("ttyDUMMY");
          ui->comboBox->setCurrentIndex(1);
        }
}


uint16_t CRC16 (QByteArray nData, int wLength)
{
static const uint16_t wCRCTable[] = {
   0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
   0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
   0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
   0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
   0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
   0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
   0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
   0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
   0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
   0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
   0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
   0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
   0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
   0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
   0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
   0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
   0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
   0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
   0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
   0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
   0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
   0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
   0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
   0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
   0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
   0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
   0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
   0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
   0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
   0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
   0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
   0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

uint8_t nTemp;
uint16_t wCRCWord = 0xFFFF;
int index = 0;

   while (wLength--)
   {
      nTemp = nData[index] ^ wCRCWord;
      wCRCWord >>= 8;
      wCRCWord  ^= wCRCTable[nTemp];
      index++;
   }
   return wCRCWord;
}

uint CRC16_2(QByteArray buf, int len)
{
  uint crc = 0xFFFF;

  for (int pos = 0; pos < len; pos++)
  {
    crc ^= (uint)buf[pos];          // XOR byte into least sig. byte of crc

    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;
}

void MainWindow::on_pushButton_9_clicked()
{
    if (ui->pushButton_9->isChecked())
    {
        copyChannelNamesToTableWidget();
        timer.start(1000);
        std::ofstream fout;
        fout.open("result.csv",std::ios::out | std::ios::app);
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QDate currentDate = currentDateTime.date();
        fout << std::endl << "Начало измерений " << currentDate.toString("dd.MM.yyyy").toUtf8().data() << std::endl;

        for (int i=0; i<64; i++)
        {
            if(ui->tableView->model()->index(i,1).data(Qt::CheckStateRole)==Qt::Checked)
            {
                fout << QString("Канал №%1").arg(i+1).toUtf8().data() << " - " << ui->tableView->model()->index(i,3).data().toString().toUtf8().data() << std::endl;
            }
        }

        fout << std::endl;

        fout << "Время;";

        for (int i=0; i<64; i++)
        {
            if(ui->tableView->model()->index(i,1).data(Qt::CheckStateRole)==Qt::Checked)
            {
                fout << QString("Канал №%1").arg(i+1).toUtf8().data() << ";";
            }
        }

        fout << std::endl;

        fout.close();
    }
    else
    {
        timer.stop();
        label->setPixmap(QPixmap(":/new/prefix1/img/IM_24_red"));
        label2->setText("  Связи нет");
    }
}

void MainWindow::timerTimeout()
{
    QByteArray buf;
    buf.resize(9);
    uint16_t  crc; //контрольная сумма

        buf[0]=0x38; //адрес устройства
        buf[1]=0x03; //код команды(чтение регистров)
        buf[2]=0x20; //старший байт адреса начального регистра
        buf[3]=0x00; //младший байт адреса начального регистра
        buf[4]=0x00; //старший байт количества регистров для чтения
        buf[5]=0x78; //младший байт количества регистров для чтения
        crc = CRC16_2(buf, 6); //считаем сумму - считаем сумму по заполненому
        //qDebug() << crc;
        buf[6]=crc & 0x00FF; //сташий байт crc
        buf[7]=(crc & 0xFF00) >> 8; //младший байт crc
        buf[8]=0x00;

        QSerialPort *port = openArchiverPort();

        if (port == nullptr)
        {
            timer.stop();
            ui->pushButton_9->setChecked(false);
            return;
        }

        port->write(buf, buf.length());
        port->waitForBytesWritten(100);
        port->flush();
        //qDebug() << "Tx: "<< buf.toHex();
        int answerLength = 0;
        QByteArray answer;
        do
        {
            if (!port->waitForReadyRead(100))
            {
                stopGetData();
                port->close();
                return;
            }
            QByteArray ansBuf = port->readAll();

            if (answerLength == 0)
            {
                answerLength = (uint8_t)ansBuf[2] - ansBuf.length() + 3 + 2;
                //qDebug() << "total: " << (uint8_t)ansBuf[2];
                answer.append(ansBuf.remove(0,3));
            }
            else
            {
                answerLength -= ansBuf.length();
                answer.append(ansBuf);
            }
        } while (answerLength != 0);
        uint16_t answer_crc = answer[answer.length() - 1] << 8 + answer[answer.length() - 2];
        answer.remove(240, answer.length() - 1);

        port->flush();

        buf[0]=0x38; //адрес устройства
        buf[1]=0x03; //код команды(чтение регистров)
        buf[2]=0x20; //старший байт адреса начального регистра
        buf[3]=0x78; //младший байт адреса начального регистра
        buf[4]=0x00; //старший байт количества регистров для чтения
        buf[5]=0x48; //младший байт количества регистров для чтения
        crc = CRC16_2(buf, 6); //считаем сумму - считаем сумму по заполненому
        //qDebug() << crc;
        buf[6]=crc & 0x00FF; //сташий байт crc
        buf[7]=(crc & 0xFF00) >> 8; //младший байт crc
        buf[8]=0x00;

        port->write(buf, buf.length());
        port->waitForBytesWritten(100);
        port->flush();
        //qDebug() << "Tx: "<< buf.toHex();
        answerLength = 0;

        do
        {
            if (!port->waitForReadyRead(100))
            {
                stopGetData();
                port->close();
                return;
            }
            QByteArray ansBuf = port->readAll();

            if (answerLength == 0)
            {
                answerLength = (uint8_t)ansBuf[2] - ansBuf.length() + 3 + 2;
                //qDebug() << "total: " << (uint8_t)ansBuf[2];
                answer.append(ansBuf.remove(0,3));
            }
            else
            {
                answerLength -= ansBuf.length();
                answer.append(ansBuf);
            }
        } while (answerLength != 0);
        answer_crc = answer[answer.length() - 1] << 8 + answer[answer.length() - 2];
        answer.remove(384, answer.length() - 1);

        //qDebug() << "reseived bytes: " << answer.length();
        //qDebug() << "Rx: " << answer.toHex();
        port->close();

        QVector<ArchiverChannel> archiverChannels(64);

        for (int i = 0; i < archiverChannels.size(); i++)
        {
            archiverChannels[i].rawStatus = (((uint8_t)answer[i*3*2]) << 8) + (uint8_t)answer[i*3*2+1];
            archiverChannels[i].rawValue = (((uint8_t)answer[i*3*2+2]) << 24) +
                    ((uint8_t)answer[i*3*2+3] << 16) +
                    ((uint8_t)answer[i*3*2+4] << 8) +
                    (uint8_t)answer[i*3*2+5];
        }

        QDateTime currentDateTime = QDateTime::currentDateTime();
        QTime currentTime = currentDateTime.time();

        QString key = currentTime.toString("hh:mm:ss");

        std::ofstream fout;
        fout.open("result.csv",std::ios::out | std::ios::app);
        fout << key.toUtf8().data();
        fout.close();

        for (int i=0; i<32; i++)
        {
            if(ui->tableView->model()->index(i,1).data(Qt::CheckStateRole)==Qt::Checked)
            {

                //запись результата в таблицу
                if (ui->tableWidget->item(i, 2) != 0)
                {
                    int k=ui->tableView->model()->data(ui->tableView->model()->index(i, 8) ).toInt();
                    uint32_t rawBEValue = archiverChannels[i].rawValue;
                    //qDebug() << i << "=" << archiverChannels[i].rawValue;

                    QString value = ui->tableView->model()->data(ui->tableView->model()->index(i, 7) ).toString();

                    if(value == "INT16(Little-endian)")
                    {}
                    else if(value == "WORD16(Little-endian)")
                    {}
                    else if(value == "LONGINT32(Little-endian)")
                    {
                        ui->tableWidget->item(i, 2)->setText(QString("%1").arg(QString::number((double)rawBEValue / pow(10,k), 'f', k)));
                        ui->tableWidget_2->item(i, 3)->setText(QString("%1").arg(QString::number((double)rawBEValue / pow(10,k), 'f', k)));
                    }
                    else if(value == "DWORD32(Little-endian)")
                    {}
                    else if(value == "FLOAT32(Little-endian)")
                    {
                        RawAndFloat convertedValue;
                        convertedValue.rawValue = rawBEValue;
                        ui->tableWidget->item(i, 2)->setText(QString("%1").arg(QString::number(convertedValue.floatValue, 'f', k)));
                        ui->tableWidget_2->item(i, 3)->setText(QString("%1").arg(QString::number(convertedValue.floatValue, 'f', k)));
                    }
                    else if(value == "INT16(Big-endian)")
                    {}
                    else if(value == "WORD16(Big-endian)")
                    {}
                    else if(value == "LONGINT32(Big-endian)")
                    {}
                    else if(value == "DWORD32(Big-endian)")
                    {}
                    else if(value == "FLOAT32(Big-endian)")
                    {}
                    else if(value == "LONGINT32(Middle-endian)")
                    {}
                    else if(value == "DWORD32(Middle-endian)")
                    {}
                    else if(value == "FLOAT32(Middle-endian)")
                    {}

                    ui->tableWidget->item(i, 2)->setTextAlignment(Qt::AlignCenter);
                    ui->tableWidget_2->item(i, 3)->setTextAlignment(Qt::AlignCenter);
                }

                uint32_t rawBEValue = archiverChannels[i].rawValue;
                RawAndFloat convertedValue;
                convertedValue.rawValue = rawBEValue;
                ui->widget_3->addPoint(i, currentDateTime.toTime_t(), convertedValue.floatValue);

                std::ofstream fout;
                fout.open("result.csv",std::ios::out | std::ios::app);
                fout << ";" << convertedValue.floatValue;
                fout.close();

            }
        }

        for (int i=32; i<64; i++)
        {
            if(ui->tableView->model()->index(i,1).data(Qt::CheckStateRole)==Qt::Checked)
            {
                //запись результата в таблицу
                if (ui->tableWidget->item(i-32, 5) != 0)
               {
                   int k2=ui->tableView->model()->data(ui->tableView->model()->index(i, 8) ).toInt();
                   uint32_t rawBEValue2 = archiverChannels[i].rawValue;
                   QString value2 = ui->tableView->model()->data(ui->tableView->model()->index(i, 7) ).toString();
//
                if(value2 == "INT16(Little-endian)")
                                    {}
                                    else if(value2 == "WORD16(Little-endian)")
                                    {}
                                    else if(value2 == "LONGINT32(Little-endian)")
                                    {
                                        ui->tableWidget->item(i-32, 5)->setText(QString("%1").arg(QString::number((double)rawBEValue2 / pow(10,k2), 'f', k2)));
                                        ui->tableWidget_2->item(i, 3)->setText(QString("%1").arg(QString::number((double)rawBEValue2 / pow(10,k2), 'f', k2)));
                                    }
                                    else if(value2 == "DWORD32(Little-endian)")
                                    {}
                                    else if(value2 == "FLOAT32(Little-endian)")
                                    {
                                        RawAndFloat convertedValue;
                                        convertedValue.rawValue = rawBEValue2;
                                        ui->tableWidget->item(i-32, 5)->setText(QString("%1").arg(QString::number(convertedValue.floatValue, 'f', k2)));
                                        ui->tableWidget_2->item(i, 3)->setText(QString("%1").arg(QString::number(convertedValue.floatValue, 'f', k2)));
                                    }
                                    else if(value2 == "INT16(Big-endian)")
                                    {}
                                    else if(value2 == "WORD16(Big-endian)")
                                    {}
                                    else if(value2 == "LONGINT32(Big-endian)")
                                    {}
                                    else if(value2 == "DWORD32(Big-endian)")
                                    {}
                                    else if(value2 == "FLOAT32(Big-endian)")
                                    {}
                                    else if(value2 == "LONGINT32(Middle-endian)")
                                    {}
                                    else if(value2 == "DWORD32(Middle-endian)")
                                    {}
                                    else if(value2 == "FLOAT32(Middle-endian)")
                                    {}
                ui->tableWidget->item(i-32, 5)->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->item(i, 3)->setTextAlignment(Qt::AlignCenter);

                }

                uint32_t rawBEValue = archiverChannels[i].rawValue;
                RawAndFloat convertedValue;
                convertedValue.rawValue = rawBEValue;
                ui->widget_3->addPoint(i, currentDateTime.toTime_t(), convertedValue.floatValue);

                std::ofstream fout;
                fout.open("result.csv",std::ios::out | std::ios::app);
                fout << ";" << convertedValue.floatValue;
                fout.close();

            }
        }

        fout.open("result.csv",std::ios::out | std::ios::app);
        fout << std::endl;
        fout.close();

        label->clear();
        label->setPixmap(QPixmap(":/new/prefix1/img/IM_24_blue"));
        label2->setText("  Связь установлена");

        delete port;
}

void MainWindow::Save()
{
    model->database().transaction();
    if(model->submitAll())
        model->database().commit();
    else
        model->database().rollback();

    changedRows.clear();
    disabledCells.clear();
    setDisabledCells();

    QFileInfo fi(fileName);
    QString base = fi.baseName();
    int index = ui->tabWidget->currentIndex();
    QString currentTabText = ui->tabWidget->tabText(index);
    setWindowTitle(currentTabText + "@" + base + QString(" - Konfiguretor"));
    isChanged = false;
}

void MainWindow::stopGetData()
{
    timer.stop();
    label->setPixmap(QPixmap(":/new/prefix1/img/IM_24_red"));
    label2->setText("  Связи нет");
}

void MainWindow::onCheckBoxHeaderClick1()
{
    if(headerr->isChecked1())
    {
        for (int i=0; i<64; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,1), Qt::Checked, Qt::CheckStateRole);
        }
    }
    else
    {
        for (int i=0; i<64; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,1), Qt::Unchecked, Qt::CheckStateRole);
        }
    }
}

void MainWindow::onCheckBoxHeaderClick2()
{
    if(headerr->isChecked2())
    {
        for (int i=0; i<64; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,2), Qt::Checked, Qt::CheckStateRole);
        }
    }
    else
    {
        for (int i=0; i<64; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,2), Qt::Unchecked, Qt::CheckStateRole);
        }
    }
}

void MainWindow::copyChannelNamesToTableWidget()
{
    for (int i = 0; i < 32; i++)
    {
        QString text = model->data(model->index(i,3)).toString();

        if (ui->tableWidget->item(i,1) != 0)
        {
            ui->tableWidget->item(i,1)->setText(text);
        }
    }

    for (int i = 32; i < 64; i++)
    {
        QString text = model->data(model->index(i,3)).toString();

        if (ui->tableWidget->item(i-32,4) != 0)
        {
            ui->tableWidget->item(i-32,4)->setText(text);
        }
    }
}

void MainWindow::selectRows()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    changedRows << row;
}

void MainWindow::setDisabledCells()
{
    //НАСТРОЙКА ЦВЕТНОСТИ РТУ
    if(sdb.isOpen()){
    for (int i=0; i<64; i++)
    {
        QString valuee = ui->tableView->model()->data(ui->tableView->model()->index(i, 4) ).toString();
        if(valuee == "RTU")
        {
            disabledCells << QPoint(i, 10) << QPoint(i, 14) << QPoint(i, 15) << QPoint(i, 16)
                          << QPoint(i, 17) << QPoint(i, 18) << QPoint(i, 19) << QPoint(i, 20);
        }
        else if(valuee == "ASCII")
        {
            disabledCells << QPoint(i, 10) << QPoint(i, 14) << QPoint(i, 15) << QPoint(i, 16)
                          << QPoint(i, 17) << QPoint(i, 18) << QPoint(i, 19) << QPoint(i, 20);
        }
        else if(valuee == "ОВЕН")
        {
            disabledCells << QPoint(i, 10) << QPoint(i, 11) << QPoint(i, 12) << QPoint(i, 13)
                          << QPoint(i, 17) << QPoint(i, 18) << QPoint(i, 19) << QPoint(i, 20);
        }
        else if(valuee == "Токовый вход 1")
        {
            disabledCells << QPoint(i, 5)  << QPoint(i, 6)  << QPoint(i, 7)  << QPoint(i, 11) << QPoint(i, 12)
                          << QPoint(i, 13) << QPoint(i, 14) << QPoint(i, 15) << QPoint(i, 16);
        }
        else if(valuee == "Токовый вход 2")
        {
            disabledCells << QPoint(i, 5)  << QPoint(i, 6)  << QPoint(i, 7)  << QPoint(i, 11) << QPoint(i, 12)
                          << QPoint(i, 13) << QPoint(i, 14) << QPoint(i, 15) << QPoint(i, 16);
        }
        else if(valuee == "Токовый вход 3")
        {
            disabledCells << QPoint(i, 5)  << QPoint(i, 6)  << QPoint(i, 7)  << QPoint(i, 11) << QPoint(i, 12)
                          << QPoint(i, 13) << QPoint(i, 14) << QPoint(i, 15) << QPoint(i, 16);
        }
        else if(valuee == "Токовый вход 4")
        {
            disabledCells << QPoint(i, 5)  << QPoint(i, 6)  << QPoint(i, 7)  << QPoint(i, 11) << QPoint(i, 12)
                          << QPoint(i, 13) << QPoint(i, 14) << QPoint(i, 15) << QPoint(i, 16);
        }
    }}
}

void MainWindow::writePribor()
{
    QSerialPort* port = openArchiverPort();

    if (port == nullptr)
    {
        return;
    }

    port->flush();

    progress->setVisible(true);
    progress->setRange(0, 64 - 1);
    progress->reset();

    CurrentChannelParams currentChannelParams[4];
    for (int i = 0; i < 4; i++)
    {
        currentChannelParams[i].diapazon = 1;
        currentChannelParams[i].filter = 100;
        currentChannelParams[i].minimum = 0;
        currentChannelParams[i].maximum = 100;
    }

    for (int i = 0; i < 64; i++)
    {
        progress->setValue(i);

        QByteArray buf;
        buf.resize(31 * 2 + 7 + 2);
        buf.fill(0);
        buf[0] = 0x38;
        buf[1] = 0x10;

        uint16_t address = 0x0100 + i * 64;

        buf[2] = (uint8_t)((address & 0xFF00) >> 8);
        buf[3] = (uint8_t)(address & 0x00FF);

        buf[4] = 0x00;
        buf[5] = 0x1F;

        buf[6] = 62;

        buf[7] = 0;
        buf[8] = ui->tableView->model()->data(ui->tableView->model()->index(i, 2)).toInt() + ((ui->tableView->model()->data(ui->tableView->model()->index(i, 2)).toInt() << 1));

        QString channelName = ui->tableView->model()->data(ui->tableView->model()->index(i, 3) ).toString();
        channelName.truncate(31);

        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QByteArray channelNameBuffer = codec->fromUnicode(channelName);

        for (int pos = 0; pos < channelNameBuffer.size(); pos++)
        {
            buf[9 + pos] = channelNameBuffer[pos];
        }

        buf[40] = 0;

        buf[41] = 0;

        QString protocolName = ui->tableView->model()->data(ui->tableView->model()->index(i, 4) ).toString();

        int protocolCode = 0;
        if(protocolName == "RTU")
            protocolCode = 0;
        else if(protocolName == "ASCII")
            protocolCode = 1;
        else if(protocolName == "ОВЕН")
            protocolCode = 2;
        else if(protocolName == "Токовый вход 1")
            protocolCode = 3;
        else if(protocolName == "Токовый вход 2")
            protocolCode = 4;
        else if(protocolName == "Токовый вход 3")
            protocolCode = 5;
        else if(protocolName == "Токовый вход 4")
            protocolCode = 6;

        // Если канал токовый - сохранить его параметры

        QString diapazonText = ui->tableView->model()->data(ui->tableView->model()->index(i, 17)).toString();
        if (diapazonText == "4..20 мА")
        {
            currentChannelParams[protocolCode - 3].diapazon = 0;
        }
        else if (diapazonText == "0..20 мА")
        {
            currentChannelParams[protocolCode - 3].diapazon = 1;
        }
        else if (diapazonText == "0..5 мА")
        {
            currentChannelParams[protocolCode - 3].diapazon = 2;
        }

        currentChannelParams[protocolCode - 3].filter = ui->tableView->model()->data(ui->tableView->model()->index(i, 18)).toInt();
        currentChannelParams[protocolCode - 3].minimum = ui->tableView->model()->data(ui->tableView->model()->index(i, 19)).toFloat();
        currentChannelParams[protocolCode - 3].maximum = ui->tableView->model()->data(ui->tableView->model()->index(i, 20)).toFloat();

        buf[42] = protocolCode;

        uint16_t netAddress = ui->tableView->model()->data(ui->tableView->model()->index(i, 5) ).toInt();
        buf[43] = (uint8_t)((netAddress & 0xFF00) >> 8);
        buf[44] = (uint8_t)(netAddress & 0x00FF);

        uint16_t timeout = ui->tableView->model()->data(ui->tableView->model()->index(i, 6) ).toInt();
        buf[45] = (uint8_t)((timeout & 0xFF00) >> 8);
        buf[46] = (uint8_t)(timeout & 0x00FF);

        int dataType = 0;
        QString dataTypeStr = ui->tableView->model()->data(ui->tableView->model()->index(i, 7) ).toString();

        if(dataTypeStr == "INT16(Little-endian)")
            dataType = 0;
        else if(dataTypeStr == "WORD16(Little-endian)")
            dataType = 1;
        else if(dataTypeStr == "LONGINT32(Little-endian)")
            dataType = 2;
        else if(dataTypeStr == "DWORD32(Little-endian)")
            dataType = 3;
        else if(dataTypeStr == "FLOAT32(Little-endian)")
            dataType = 4;
        else if(dataTypeStr == "INT16(Big-endian)")
            dataType = 5;
        else if(dataTypeStr == "WORD16(Big-endian)")
            dataType = 6;
        else if(dataTypeStr == "LONGINT32(Big-endian)")
            dataType = 7;
        else if(dataTypeStr == "DWORD32(Big-endian)")
            dataType = 8;
        else if(dataTypeStr == "FLOAT32(Big-endian)")
            dataType = 9;
        else if(dataTypeStr == "LONGINT32(Middle-endian)")
            dataType = 10;
        else if(dataTypeStr == "DWORD32(Middle-endian)")
            dataType = 11;
        else if(dataTypeStr == "FLOAT32(Middle-endian)")
            dataType = 12;

        buf[47] = 0;
        buf[48] = dataType;

        buf[49] = 0;
        buf[50] = ui->tableView->model()->data(ui->tableView->model()->index(i, 8) ).toInt();

        QString errorArchiveStr = ui->tableView->model()->data(ui->tableView->model()->index(i, 9) ).toString();
        int errorArchive = 0;

        if(errorArchiveStr == "выкл")
            errorArchive = 0;
        else if(errorArchiveStr == "вкл")
            errorArchive = 1;

        buf[51] = 0;
        buf[52] = errorArchive;

        RawAndFloat errorarchiveThreshold;
        errorarchiveThreshold.floatValue = ui->tableView->model()->data(ui->tableView->model()->index(i, 10) ).toFloat();
        buf[53] = (errorarchiveThreshold.rawValue & 0xFF000000) >> 24;
        buf[54] = (errorarchiveThreshold.rawValue & 0x00FF0000) >> 16;
        buf[55] = (errorarchiveThreshold.rawValue & 0x0000FF00) >> 8;
        buf[56] = (errorarchiveThreshold.rawValue & 0x000000FF);

        buf[57] = 0;
        if (ui->tableView->model()->data(ui->tableView->model()->index(i, 11) ).toInt() == 3)
        {
            buf[58] = 0;
        } else if (ui->tableView->model()->data(ui->tableView->model()->index(i, 11) ).toInt() == 4)
        {
            buf[58] = 1;
        }

        QString resgisterAddressString = ui->tableView->model()->data(ui->tableView->model()->index(i, 12) ).toString();
        uint16_t registerAddress = resgisterAddressString.toInt(nullptr, 16);
        buf[59] = (uint8_t)((registerAddress & 0xFF00) >> 8);
        buf[60] = (uint8_t)(registerAddress & 0x00FF);

        uint16_t groupNumber = ui->tableView->model()->data(ui->tableView->model()->index(i, 13) ).toInt();
        buf[61] = (uint8_t)((groupNumber & 0xFF00) >> 8);
        buf[62] = (uint8_t)(groupNumber & 0x00FF);

        QString addressLenghtStr = ui->tableView->model()->data(ui->tableView->model()->index(i, 14) ).toString();
        int addressLength = 0;

        if(addressLenghtStr == "8 бит")
            addressLength = 0;
        else if(addressLenghtStr == "11 бит")
            addressLength = 1;

        buf[63] = 0;
        buf[64] = addressLength;

        QString hashStr = ui->tableView->model()->data(ui->tableView->model()->index(i, 15) ).toString();
        bool ok;
        uint16_t hash = hashStr.toInt(&ok, 16);
        buf[65] = (uint8_t)((hash & 0xFF00) >> 8);
        buf[66] = (uint8_t)(hash & 0x00FF);

        uint16_t index = ui->tableView->model()->data(ui->tableView->model()->index(i, 16) ).toInt();
        buf[67] = (uint8_t)((index & 0xFF00) >> 8);
        buf[68] = (uint8_t)(index & 0x00FF);


        /*uint8_t package[] = { 0x38, 0x10, 0x01, 0x00, 0x00, 0x1F, 0x3E, 0x00, 0x02, 0x50, 0x55, 0x5F, 0x72, 0x69, 0x67, 0x68,
        0x74, 0x5F, 0x66, 0x72, 0x6F, 0x6E, 0x74, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0xF4, 0x00,
        0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x09, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x00, 0xFF, 0xFF};*/

        /*for (int kkk = 0; kkk < 69; kkk++)
        {
            buf[kkk] = package[kkk];
        }*/

        uint16_t crc = CRC16(buf, buf.size() - 2);

        buf[69]=crc & 0x00FF;
        buf[70]=(crc & 0xFF00) >> 8;

        //QString debug_crc = QString("%1").arg(crc, 0, 16);
        //qDebug() << "crc: " << debug_crc;

        port->write(buf, buf.length());
        port->waitForBytesWritten(1000);
        port->flush();

        int answerLength = 0;
        QByteArray answer;
        do
        {
            if (!port->waitForReadyRead(100))
            {
                break;
            }
            QByteArray ansBuf = port->readAll();

            if (answerLength == 0)
            {
                answerLength = (uint8_t)ansBuf[2] - ansBuf.length() + 3 + 2;
                //qDebug() << "total: " << (uint8_t)ansBuf[2];
                answer.append(ansBuf.remove(0,3));
            }
            else
            {
                answerLength -= ansBuf.length();
                answer.append(ansBuf);
            }
        } while (answerLength != 0);

         QThread::msleep(100);
         qDebug() << "End channel " << i;
    }

    // Запись настроек токовых каналов

    QByteArray buf;
    buf.resize(24 * 2 + 7 + 2); // 24 регистра, 7 байт заголовка, 2 байта CRC
    buf.fill(0);
    buf[0] = 0x38;
    buf[1] = 0x10;

    uint16_t address = 0x1100;

    buf[2] = (uint8_t)((address & 0xFF00) >> 8);
    buf[3] = (uint8_t)(address & 0x00FF);

    buf[4] = 0x00;
    buf[5] = 0x18;

    buf[6] = 48;

    for (int i = 0; i < 4; i++)
    {
        buf[7 + i*12] = (currentChannelParams[i].diapazon & 0xFF00) >> 8;
        buf[8 + i*12] = currentChannelParams[i].diapazon & 0x00FF;

        buf[9 + i*12] = (currentChannelParams[i].filter & 0xFF00) >> 8;
        buf[10 + i*12] = currentChannelParams[i].filter & 0x00FF;

        RawAndFloat minimum;
        minimum.floatValue = currentChannelParams[i].minimum;
        buf[11 + i*12] = (minimum.rawValue & 0xFF000000) >> 24;
        buf[12 + i*12] = (minimum.rawValue & 0x00FF0000) >> 16;
        buf[13 + i*12] = (minimum.rawValue & 0x0000FF00) >> 8;
        buf[14 + i*12] = minimum.rawValue & 0x000000FF;

        RawAndFloat maximum;
        maximum.floatValue = currentChannelParams[i].maximum;
        buf[15 + i*12] = (maximum.rawValue & 0xFF000000) >> 24;
        buf[16 + i*12] = (maximum.rawValue & 0x00FF0000) >> 16;
        buf[17 + i*12] = (maximum.rawValue & 0x0000FF00) >> 8;
        buf[18 + i*12] = maximum.rawValue & 0x000000FF;
    }

    uint16_t crc = CRC16(buf, buf.size() - 2);

    buf[55]=crc & 0x00FF;
    buf[56]=(crc & 0xFF00) >> 8;

    port->write(buf, buf.length());
    port->waitForBytesWritten(1000);
    port->flush();

    int answerLength = 0;
    QByteArray answer;
    do
    {
        if (!port->waitForReadyRead(100))
        {
            break;
        }
        QByteArray ansBuf = port->readAll();

        if (answerLength == 0)
        {
            answerLength = (uint8_t)ansBuf[2] - ansBuf.length() + 3 + 2;
            //qDebug() << "total: " << (uint8_t)ansBuf[2];
            answer.append(ansBuf.remove(0,3));
        }
        else
        {
            answerLength -= ansBuf.length();
            answer.append(ansBuf);
        }
    } while (answerLength != 0);

    port->close();
    delete port;

    QMessageBox::information(this, "Завершено", "Запись данных завершена!");
    progress->setVisible(false);
}

QSerialPort* MainWindow::openArchiverPort()
{
    QSerialPort *port = new QSerialPort (ui->comboBox->currentText());
    port->setBaudRate(ui->comboBox_2->currentText().toInt());
    switch (ui->comboBox_3->currentIndex())
    {
        case 0:
           port->setDataBits(QSerialPort::Data5);
        break;
        case 1:
           port->setDataBits(QSerialPort::Data6);
        break;
        case 2:
           port->setDataBits(QSerialPort::Data7);
        break;
        case 3:
           port->setDataBits(QSerialPort::Data8);
        break;
    }

    switch (ui->comboBox_4->currentIndex())
    {
        case 0:
           port->setParity(QSerialPort::NoParity);
        break;
        case 1:
           port->setParity(QSerialPort::EvenParity);
        break;
        case 2:
           port->setParity(QSerialPort::OddParity);
        break;
        case 3:
           port->setParity(QSerialPort::MarkParity);
        break;
        case 4:
           port->setParity(QSerialPort::SpaceParity);
        break;
    }

    switch (ui->comboBox_5->currentIndex())
    {
        case 0:
           port->setStopBits(QSerialPort::OneStop);
        break;
        case 1:
           port->setStopBits(QSerialPort::TwoStop);
        break;
        case 2:
           port->setStopBits(QSerialPort::OneAndHalfStop);
        break;
    }

    switch (ui->comboBox_6->currentIndex())
    {
        case 0:
           port->setFlowControl(QSerialPort::NoFlowControl);
        break;
        case 1:
           port->setFlowControl(QSerialPort::HardwareControl);
        break;
        case 2:
           port->setFlowControl(QSerialPort::SoftwareControl);
        break;
    }

    //port->setDataBits(ui->comboBox_3->currentText().toInt());
    if (!port->open(QIODevice::ReadWrite))
    {
        delete port;
        QMessageBox::critical(this, tr("Ошибка"), tr("Порт не открыт"));
        return nullptr;
    }

    return port;
}

void MainWindow::readPribor()
{
    QSerialPort* port = openArchiverPort();

    if (port == nullptr)
    {
        return;
    }

    port->flush();

    progress->setVisible(true);
    progress->setRange(0, 64 - 1);
    progress->reset();

    // Чтение данных токовых каналов
    QByteArray buf;
    buf.resize(9);

    buf[0]=0x38; //адрес устройства
    buf[1]=0x03; //код команды(чтение регистров)

    uint16_t address = 0x1100;

    buf[2] = (uint8_t)((address & 0xFF00) >> 8);
    buf[3] = (uint8_t)(address & 0x00FF);

    //Читаем 24 регистра, 6*4 канала
    buf[4] = 0x00;
    buf[5] = 0x18;

    uint16_t crc = CRC16(buf, 6); //считаем сумму - считаем сумму по заполненому

    buf[6]=crc & 0x00FF; //сташий байт crc
    buf[7]=(crc & 0xFF00) >> 8; //младший байт crc
    buf[8]=0x00;

    port->write(buf, buf.length());
    port->waitForBytesWritten(100);
    port->flush();

    int answerLength = 0;
    QByteArray answer;

    do
    {
        if (!port->waitForReadyRead(100))
        {
            port->close();
            delete port;
            return;
        }
        QByteArray ansBuf = port->readAll();

        if (answerLength == 0)
        {
            answerLength = (uint8_t)ansBuf[2] - ansBuf.length() + 3 + 2;
            answer.append(ansBuf);
        }
        else
        {
            answerLength -= ansBuf.length();
            answer.append(ansBuf);
        }
    } while (answerLength != 0);
    uint16_t answer_crc = answer[answer.length() - 1] << 8 + answer[answer.length() - 2];

    answer.remove(0,3);
    CurrentChannelParams currentChannelParams[4];

    for (int i = 0; i < 4; i++)
    {
        currentChannelParams[i].diapazon = ((uint8_t)answer[0+i*12] << 8) + (uint8_t)answer[1+i*12];
        currentChannelParams[i].filter = ((uint8_t)answer[2+i*12] << 8) + (uint8_t)answer[3+i*12];
        RawAndFloat minimum;
        minimum.rawValue = ((uint8_t)answer[4+i*12] << 24) + ((uint8_t)answer[5+i*12] << 16) + ((uint8_t)answer[6+i*12] << 8) + (uint8_t)answer[7+i*12];
        currentChannelParams[i].minimum = minimum.floatValue;
        RawAndFloat maximum;
        maximum.rawValue = ((uint8_t)answer[8+i*12] << 24) + ((uint8_t)answer[9+i*12] << 16) + ((uint8_t)answer[10+i*12] << 8) + (uint8_t)answer[11+i*12];
        currentChannelParams[i].maximum = maximum.floatValue;
    }

    for (int i = 0; i < 64; i++)
    {
        progress->setValue(i);

        QByteArray buf;
        buf.resize(9);

        buf[0]=0x38; //адрес устройства
        buf[1]=0x03; //код команды(чтение регистров)

        uint16_t address = 0x0100 + i * 64;

        buf[2] = (uint8_t)((address & 0xFF00) >> 8);
        buf[3] = (uint8_t)(address & 0x00FF);

        //Читаем 31 регистр
        buf[4] = 0x00;
        buf[5] = 0x1F;

        uint16_t crc = CRC16(buf, 6); //считаем сумму - считаем сумму по заполненому

        buf[6]=crc & 0x00FF; //сташий байт crc
        buf[7]=(crc & 0xFF00) >> 8; //младший байт crc
        buf[8]=0x00;

        port->write(buf, buf.length());
        port->waitForBytesWritten(100);
        port->flush();

        int answerLength = 0;
        QByteArray answer;
        answer.append(4, 0);
        do
        {
            if (!port->waitForReadyRead(100))
            {
                port->close();
                delete port;
                return;
            }
            QByteArray ansBuf = port->readAll();

            if (answerLength == 0)
            {
                answerLength = (uint8_t)ansBuf[2] - ansBuf.length() + 3 + 2;
                answer.append(ansBuf);
            }
            else
            {
                answerLength -= ansBuf.length();
                answer.append(ansBuf);
            }
        } while (answerLength != 0);
        uint16_t answer_crc = answer[answer.length() - 1] << 8 + answer[answer.length() - 2];

        ui->tableView->model()->setData(ui->tableView->model()->index(i, 2), answer[8] & 0x01);

        QByteArray channelNameBuffer;
        int pos = 0;

        while (((int)answer[9 + pos] != 0) && (pos < 31))
        {
            channelNameBuffer.append(answer[9 + pos]);
            pos++;
        }

        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QString channelName = codec->toUnicode(channelNameBuffer);
        ui->tableView->model()->setData(ui->tableView->model()->index(i, 3), channelName);

        int protocolCode = answer[42];

        QString protocolName;

        switch (protocolCode)
        {
        case 0:
           protocolName = "RTU";
        break;
        case 1:
            protocolName = "ASCII";
        break;
        case 2:
            protocolName = "ОВЕН";
        break;
        case 3:
            protocolName = "Токовый вход 1";
        break;
        case 4:
            protocolName = "Токовый вход 2";
        break;
        case 5:
            protocolName = "Токовый вход 3";
        break;
        case 6:
            protocolName = "Токовый вход 4";
        break;
        }

        // Если канал токовый - применить его настройки
        if ((protocolCode >= 3) && (protocolCode <= 6))
        {
            int channelNumber = protocolCode - 3;
            QString diapazonText;
            switch (currentChannelParams[channelNumber].diapazon)
            {
            case 0:
                diapazonText = "4..20 мА";
                break;
            case 1:
                diapazonText = "0..20 мА";
                break;
            case 2:
                diapazonText = "0..5 мА";
                break;
            }

            ui->tableView->model()->setData(ui->tableView->model()->index(i, 17), diapazonText);

            ui->tableView->model()->setData(ui->tableView->model()->index(i, 18), currentChannelParams[channelNumber].filter);

            ui->tableView->model()->setData(ui->tableView->model()->index(i, 19), currentChannelParams[channelNumber].minimum);
            ui->tableView->model()->setData(ui->tableView->model()->index(i, 20), currentChannelParams[channelNumber].maximum);
        }

        ui->tableView->model()->setData(ui->tableView->model()->index(i, 4), protocolName);

        uint16_t netAddress = ((uint8_t)answer[43] << 8) + (uint8_t)answer[44];
        ui->tableView->model()->setData(ui->tableView->model()->index(i, 5), netAddress);

        uint16_t timeout = ((uint8_t)answer[45] << 8) + (uint8_t)answer[46];
        ui->tableView->model()->setData(ui->tableView->model()->index(i, 6), timeout);

        int dataType = (uint8_t)answer[48];
        QString dataTypeStr;
        switch(dataType)
        {
        case 0:
            dataTypeStr = "INT16(Little-endian)";
        break;
        case 1:
            dataTypeStr = "WORD16(Little-endian)";
        break;
        case 2:
            dataTypeStr = "LONGINT32(Little-endian)";
        break;
        case 3:
            dataTypeStr = "DWORD32(Little-endian)";
        break;
        case 4:
            dataTypeStr = "FLOAT32(Little-endian)";
        break;
        case 5:
            dataTypeStr = "INT16(Big-endian)";
        break;
        case 6:
            dataTypeStr = "WORD16(Big-endian)";
        break;
        case 7:
            dataTypeStr = "LONGINT32(Big-endian)";
        break;
        case 8:
            dataTypeStr = "DWORD32(Big-endian)";
        break;
        case 9:
            dataTypeStr = "FLOAT32(Big-endian)";
        break;
        case 10:
            dataTypeStr = "LONGINT32(Middle-endian)";
        break;
        case 11:
            dataTypeStr = "DWORD32(Middle-endian)";
        break;
        case 12:
            dataTypeStr = "FLOAT32(Middle-endian)";
        break;
        }

        ui->tableView->model()->setData(ui->tableView->model()->index(i, 7), dataTypeStr);

        ui->tableView->model()->setData(ui->tableView->model()->index(i, 8), (int)answer[50]);

        QString errorArchiveStr;
        int errorArchive = answer[52];

        switch(errorArchive)
        {
        case 0:
            errorArchiveStr = "выкл";
        break;
        case 1:
            errorArchiveStr = "вкл";
        break;
        }

        ui->tableView->model()->setData(ui->tableView->model()->index(i, 9), errorArchiveStr);

        RawAndFloat errorarchiveThreshold;
        errorarchiveThreshold.rawValue = ((uint8_t)answer[53] << 24) + ((uint8_t)answer[54] << 16) + ((uint8_t)answer[55] << 8) + (uint8_t)answer[56];
        ui->tableView->model()->setData(ui->tableView->model()->index(i, 10), errorarchiveThreshold.floatValue);

        if ((int)answer[58] == 0)
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i, 11), 3);
        } else
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i, 11), 4);
        }

        uint16_t registerAddress = ((uint8_t)answer[59] << 8) + (uint8_t)answer[60];
        QString resgisterAddressString = QString("0x%1").arg(registerAddress, 0, 16);
        ui->tableView->model()->setData(ui->tableView->model()->index(i, 12), resgisterAddressString);

        ui->tableView->model()->setData(ui->tableView->model()->index(i, 13), ((uint8_t)answer[61] << 8) + (uint8_t)answer[62]);

        QString addressLenghtStr;
        int addressLength = answer[64];

        switch(addressLength)
        {
        case 0:
            addressLenghtStr = "8 бит";
            break;
        case 1:
            addressLenghtStr = "11 бит";
            break;
        }

        ui->tableView->model()->setData(ui->tableView->model()->index(i, 14), addressLenghtStr);

        uint16_t hash = (answer[65] << 8) + answer[66];
        QString hashStr = QString("0x%1").arg(hash, 0, 16);
        ui->tableView->model()->setData(ui->tableView->model()->index(i, 15), hashStr);

        uint16_t index = ((uint8_t)answer[67] << 8) + (uint8_t)answer[68];
        ui->tableView->model()->setData(ui->tableView->model()->index(i, 16), (int16_t)index);

        QThread::msleep(100);
    }

    port->close();
    delete port;

    QMessageBox::information(this, "Завершено", "Чтение данных завершено!");
    progress->setVisible(false);
}

void MainWindow::on_actionPLUS_triggered()
{

}

void MainWindow::on_actionSave_2_triggered()
{

}


void MainWindow::on_actionRead_triggered()
{

}

