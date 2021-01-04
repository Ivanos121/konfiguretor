﻿#include "mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //инициализация базы данных sqlite3
    sdb = QSqlDatabase::addDatabase("QSQLITE"); //объявление базы данных sqlite3
    sdb.setDatabaseName(QFileInfo("netdb.db").absoluteFilePath()); //подключение к базе данных
    model = new Model; //создание модели QSqlTableModel
    model->setTable("Net settings"); //Установка для таблицы базы данных, с которой работает модель, tableName
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //Все изменения будут кэшироваться в модели до тех пор, пока не будет вызван сигнал submitAll()

    //подключение заголовка таблицы
    headerr = new CheckBoxHeader(Qt::Horizontal,ui->tableView);  //создание заголовка tableview
    ui->tableView->setHorizontalHeader(headerr); //установка заголовка tableview и checkbox в первый столбец
    connect(headerr, &CheckBoxHeader::checkBoxClicked1, this, &MainWindow::onCheckBoxHeaderClick1); //подключение головного чекбокса к чекбоксам в первом столбце
    connect(headerr, &CheckBoxHeader::checkBoxClicked2, this, &MainWindow::onCheckBoxHeaderClick2); //подключение головного чекбокса к чекбоксам в первом столбце

    //загрузка данных в таблицу tableview
    model->select(); //Заполняет модель данными из таблицы, которая была установлена ​​с помощью setTable(), используя указанный фильтр и условие сортировки
    ui->tableView->setModel(model); //Устанавливает модель для представления
    ui->tableView->hideColumn(0); //скрытие столбца id

    //делегаты для создания чекбоксов
    CheckBoxDelegate* checkBoxDelegate = new CheckBoxDelegate; //создание делегата для создания чекбоксов
    ui->tableView->setItemDelegateForColumn(1, checkBoxDelegate); //загрузка делегата в первый столбец
    ui->tableView->setItemDelegateForColumn(2, checkBoxDelegate); //загрузка делегата во второй столбец

    //делегаты для создания комбобоксов
    ComboBoxDelegate* comboBoxDelegate = new ComboBoxDelegate; //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(4, comboBoxDelegate); //загрузка делегата в четвертый столбец

    //делегаты для создания комбобоксов
    ComboBoxVarDelegate* comboBoxVarDelegate = new ComboBoxVarDelegate; //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(7, comboBoxVarDelegate); //загрузка делегата в седьмой столбец

    //делегаты для создания комбобоксов
    ComboBoxModbusDelegate* comboboxmodbusdelegate = new ComboBoxModbusDelegate; //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(11, comboboxmodbusdelegate); //загрузка делегата в одиннадцатый столбец

    //делегаты для создания комбобоксов
    ComboBoxBitDelegate* comboboxbitdelegate = new ComboBoxBitDelegate; //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(14, comboboxbitdelegate); //загрузка делегата в одиннадцатый столбец

    //делегаты для создания комбобоксов
    ComboBoxErrorArchiveDelegate* comboboxerrorarchivedelegate = new ComboBoxErrorArchiveDelegate; //создание делегата для создания комбобоксов
    ui->tableView->setItemDelegateForColumn(9, comboboxerrorarchivedelegate); //загрузка делегата в одиннадцатый столбец

    //настройка ширины столбцов
    QHeaderView *headers = ui->tableWidget->horizontalHeader(); //объявление указателя на горизонтальный заголовок
    headers->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме

    //настройки таблицы tableview
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked); //Редактирование начинается при двойном щелчке по элементу
    ui->tableView->setSelectionMode(QAbstractItemView :: NoSelection); //нет выделения ячеек
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

    ui->tableWidget->item(0,1)->setText("Подшипниковый узел справа впереди");
    ui->tableWidget->item(1,1)->setText("Подшипниковый узел слева сзади");
    ui->tableWidget->item(2,1)->setText("Лобовая часть справа сзади");
    ui->tableWidget->item(3,1)->setText("Магнитопровод статора");
    ui->tableWidget->item(4,1)->setText("Станина");
    ui->tableWidget->item(5,1)->setText("Лобовая часть справа впереди");
    ui->tableWidget->item(6,1)->setText("Станина");
    ui->tableWidget->item(7,1)->setText("Момент");
    ui->tableWidget->item(8,1)->setText("Подшипниковый узел справа сзади");
    ui->tableWidget->item(9,1)->setText("Лобовая часть слева впереди");
    ui->tableWidget->item(10,1)->setText("Подшипниковый узел слева впереди");
    ui->tableWidget->item(11,1)->setText("Лобовая часть слева сзади");
    ui->tableWidget->item(12,1)->setText("Скорость вращения ротора");

    ui->tableWidget->item(13,1)->setText("Переменное напряжение фазы А");
    ui->tableWidget->item(14,1)->setText("Переменный ток фазы А");
    ui->tableWidget->item(15,1)->setText("Активная мощность фазы А");
    ui->tableWidget->item(16,1)->setText("Реактивная мощность фазы А");
    ui->tableWidget->item(17,1)->setText("Полная мощность фазы А");
    ui->tableWidget->item(18,1)->setText("Частота фазы А");
    ui->tableWidget->item(19,1)->setText("Коэффициент мощности фазы А");

    ui->tableWidget->item(20,1)->setText("Переменное напряжение фазы B");
    ui->tableWidget->item(21,1)->setText("Переменный ток фазы B");
    ui->tableWidget->item(22,1)->setText("Активная мощность фазы B");
    ui->tableWidget->item(23,1)->setText("Реактивная мощность фазы B");
    ui->tableWidget->item(24,1)->setText("Полная мощность фазы B");
    ui->tableWidget->item(25,1)->setText("Частота фазы B");
    ui->tableWidget->item(26,1)->setText("Коэффициент мощности фазы B");

    ui->tableWidget->item(27,1)->setText("Переменное напряжение фазы C");
    ui->tableWidget->item(28,1)->setText("Переменный ток фазы C");
    ui->tableWidget->item(29,1)->setText("Активная мощность фазы C");
    ui->tableWidget->item(30,1)->setText("Реактивная мощность фазы C");
    ui->tableWidget->item(31,1)->setText("Полная мощность фазы C");
    ui->tableWidget->item(0, 4)->setText("Частота фазы C");
    ui->tableWidget->item(1, 4)->setText("Коэффициент мощности фазы C");

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


    ui->widget_3->setBufferDevicePixelRatio(.5);

    ui->widget_3->setMaximumSize(ui->widget_3->maximumWidth(), ui->widget_3->maximumHeight());
    ui->widget_3->setOpenGl(true);

    ui->widget_3->legend->setVisible(true);
    ui->widget_3->legend->setFont(QFont("Hevlrtika",9));
    ui->widget_3->setLocale(QLocale(QLocale::Russian, QLocale::Russia));
    ui->widget_3->clearGraphs();
    ui->widget_3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->widget_3->setBackground(plotGradient);

    ui->widget_3->setMouseTracking(true);
    ui->widget_3->addGraph();
    ui->widget_3->graph(0)->setName("Подшипниковый узел справа впереди");
    ui->widget_3->graph(0)->setPen(QPen(Qt::blue));
    ui->widget_3->addGraph();
    ui->widget_3->graph(1)->setName("Подшипниковый узел слева сзади");
    ui->widget_3->graph(1)->setPen(QPen(Qt::red));
    ui->widget_3->addGraph();
    ui->widget_3->graph(2)->setName("Лобовая часть справа сзади");
    ui->widget_3->graph(2)->setPen(QPen(Qt::green));
    ui->widget_3->addGraph();
    ui->widget_3->graph(3)->setName("Магнитопровод статора");
    ui->widget_3->graph(3)->setPen(QPen(Qt::cyan));
    ui->widget_3->addGraph();
    ui->widget_3->graph(4)->setName("Станина");
    ui->widget_3->graph(4)->setPen(QPen(QColor(47, 15, 163)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(5)->setName("Лобовая часть справа впереди");
    ui->widget_3->graph(5)->setPen(QPen(QColor(47, 15, 163)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(6)->setName("Станина");
    ui->widget_3->graph(6)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(7)->setName("Момент");
    ui->widget_3->graph(7)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(8)->setName("Подшипниковый узел справа сзади");
    ui->widget_3->graph(8)->setPen(QPen(QColor(103, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(9)->setName("Лобовая часть слева впереди");
    ui->widget_3->graph(9)->setPen(QPen(QColor(104, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(10)->setName("Подшипниковый узел слева впереди");
    ui->widget_3->graph(10)->setPen(QPen(QColor(132, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(11)->setName("Лобовая часть слева сзади");
    ui->widget_3->graph(11)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(12)->setName("Скорость вращения ротора");
    ui->widget_3->graph(12)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(13)->setName("Переменное напряжение фазы А");
    ui->widget_3->graph(13)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(14)->setName("Переменный ток фазы А");
    ui->widget_3->graph(14)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(15)->setName("Активная мощность фазы А");
    ui->widget_3->graph(15)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(16)->setName("Реактивная мощность фазы А");
    ui->widget_3->graph(16)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(17)->setName("Полная мощность фазы А");
    ui->widget_3->graph(17)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(18)->setName("Частота фазы А");
    ui->widget_3->graph(18)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(19)->setName("Коэффициент мощности фазы А");
    ui->widget_3->graph(19)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(20)->setName("Переменное напряжение фазы B");
    ui->widget_3->graph(20)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(21)->setName("Переменный ток фазы B");
    ui->widget_3->graph(21)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(22)->setName("Активная мощность фазы B");
    ui->widget_3->graph(22)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(23)->setName("Реактивная мощность фазы B");
    ui->widget_3->graph(23)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(24)->setName("Полная мощность фазы B");
    ui->widget_3->graph(24)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(25)->setName("Частота фазы B");
    ui->widget_3->graph(25)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(26)->setName("Коэффициент мощности фазы B");
    ui->widget_3->graph(26)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(27)->setName("Переменное напряжение фазы C");
    ui->widget_3->graph(27)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(28)->setName("Переменный ток фазы C");
    ui->widget_3->graph(28)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(29)->setName("Активная мощность фазы C");
    ui->widget_3->graph(29)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(30)->setName("Реактивная мощность фазы C");
    ui->widget_3->graph(30)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(31)->setName("Полная мощность фазы C");
    ui->widget_3->graph(31)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(32)->setName("Частота фазы C");
    ui->widget_3->graph(32)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget_3->addGraph();
    ui->widget_3->graph(33)->setName("Коэффициент мощности фазы C");
    ui->widget_3->graph(33)->setPen(QPen(QColor(102, 245, 7)));


    QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
    timeTicker->setDateTimeFormat("hh:mm:ss");
    ui->widget_3->xAxis->setTicker(timeTicker);
    ui->widget_3->xAxis->setBasePen(QPen(Qt::white, 4));
    ui->widget_3->yAxis->setBasePen(QPen(Qt::white, 4));
    ui->widget_3->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget_3->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget_3->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->widget_3->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->widget_3->xAxis->setTickLabelColor(Qt::white);
    ui->widget_3->yAxis->setTickLabelColor(Qt::white);
    ui->widget_3->xAxis->grid()->setVisible(true);
    ui->widget_3->xAxis->grid()->setSubGridVisible(true);
    ui->widget_3->xAxis->grid()->setAntialiased(true);
    ui->widget_3->xAxis->grid()->setAntialiasedSubGrid(true);
    ui->widget_3->yAxis->setRange(-1.2, 1.2);
    ui->widget_3->xAxis->grid()->setPen(QPen(Qt::white, 1, Qt::SolidLine));
    ui->widget_3->xAxis->grid()->setSubGridPen(QPen(Qt::white, 0.5, Qt::DotLine));
    ui->widget_3->yAxis->grid()->setVisible(true);
    ui->widget_3->yAxis->grid()->setSubGridVisible(true);
    ui->widget_3->yAxis->grid()->setAntialiased(true);
    ui->widget_3->yAxis->grid()->setAntialiasedSubGrid(true);
    ui->widget_3->yAxis->grid()->setPen(QPen(Qt::white, 1, Qt::SolidLine));
    ui->widget_3->yAxis->grid()->setSubGridPen(QPen(Qt::white, 0.5, Qt::DotLine));

    ui->widget_3->xAxis2->setBasePen(QPen(Qt::white, 4));
    ui->widget_3->yAxis2->setBasePen(QPen(Qt::white, 4));
    ui->widget_3->xAxis2->setTickPen(QPen(Qt::white, 1));
    ui->widget_3->yAxis2->setTickPen(QPen(Qt::white, 1));
    ui->widget_3->xAxis2->setSubTickPen(QPen(Qt::white, 1));
    ui->widget_3->yAxis2->setSubTickPen(QPen(Qt::white, 1));
    ui->widget_3->xAxis2->setTickLabelColor(Qt::white);
    ui->widget_3->yAxis2->setTickLabelColor(Qt::white);
    ui->widget_3->yAxis2->grid()->setVisible(true);
    ui->widget_3->yAxis2->grid()->setSubGridVisible(true);
    ui->widget_3->yAxis2->grid()->setAntialiased(true);
    ui->widget_3->yAxis2->grid()->setAntialiasedSubGrid(true);
    ui->widget_3->yAxis2->grid()->setPen(QPen(Qt::white, 1, Qt::SolidLine));
    ui->widget_3->yAxis2->grid()->setSubGridPen(QPen(Qt::white, 0.5, Qt::DotLine));
    ui->widget_3->axisRect()->setupFullAxesBox();

    connect(ui->widget_3->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_3->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_3->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_3->yAxis2, SLOT(setRange(QCPRange)));

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

    //индикация работы связи с архиватором
    label=new QLabel(this);
    label2=new QLabel(this);
    ui->toolBar->addWidget(label);
    ui->toolBar->addWidget(label2);
    //label->setPixmap(QPixmap("IM_24_red"));
    QPixmap pic1 = QPixmap(":resourse/img/IM_24_red.png");
    qDebug() << pic1.load("wall.bmp");
    label->setPixmap(QPixmap(pic1));
    label2->setText("  Связи нет");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->comboBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
          ui->comboBox->addItem(info.portName());
          ui->comboBox->addItem("ttyMP0");
          ui->comboBox->addItem("ttyMP1");
          ui->comboBox->setCurrentIndex(1);
        }
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
        timer.start(1000);
        std::ofstream fout;
        fout.open("result.csv",std::ios::out | std::ios::app);
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QDate currentDate = currentDateTime.date();
        fout << std::endl << "Начало измерений " << currentDate.toString("dd.MM.yyyy").toUtf8().data() << std::endl;

        for (int i=0; i<34; i++)
        {
            if(ui->tableView->model()->index(i,1).data(Qt::CheckStateRole)==Qt::Checked)
            {
                fout << QString("Канал №%1").arg(i+1).toUtf8().data() << " - " << ui->tableView->model()->index(i,3).data().toString().toUtf8().data() << std::endl;
            }
        }

        fout << std::endl;

        fout << "Время;";

        for (int i=0; i<34; i++)
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
        //label->setPixmap(QPixmap("IM_24_red"));
        label->setPixmap(QPixmap(": /img/IM_24_red"));
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
        qDebug() << crc;
        buf[6]=crc & 0x00FF; //сташий байт crc
        buf[7]=(crc & 0xFF00) >> 8; //младший байт crc
        buf[8]=0x00;

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
            QMessageBox::critical(this, tr("Ошибка"), tr("Порт не открыт"));
        }
        port->write(buf, buf.length());
        port->waitForBytesWritten(100);
        port->flush();
        qDebug() << "Tx: "<< buf.toHex();
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
                qDebug() << "total: " << (uint8_t)ansBuf[2];
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
        qDebug() << crc;
        buf[6]=crc & 0x00FF; //сташий байт crc
        buf[7]=(crc & 0xFF00) >> 8; //младший байт crc
        buf[8]=0x00;

        port->write(buf, buf.length());
        port->waitForBytesWritten(100);
        port->flush();
        qDebug() << "Tx: "<< buf.toHex();
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
                qDebug() << "total: " << (uint8_t)ansBuf[2];
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

        qDebug() << "reseived bytes: " << answer.length();
        qDebug() << "Rx: " << answer.toHex();
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
                    RawAndFloat convertedValue;
                    convertedValue.rawValue = rawBEValue;
                    ui->tableWidget->item(i, 2)->setText(QString("%1").arg(QString::number(convertedValue.floatValue, 'f', k)));
                    ui->tableWidget->item(i, 2)->setTextAlignment(Qt::AlignCenter);


                }

                uint32_t rawBEValue = archiverChannels[i].rawValue;
                RawAndFloat convertedValue;
                convertedValue.rawValue = rawBEValue;
                ui->widget_3->graph(i)->addData(currentDateTime.toTime_t(), convertedValue.floatValue);
                ui->widget_3->graph(i)->rescaleValueAxis(true);
                ui->widget_3->xAxis->setRange(currentDateTime.toTime_t(), 8, Qt::AlignRight);
                ui->widget_3->replot();
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
                    uint32_t rawBEValue = archiverChannels[i].rawValue;
                    RawAndFloat convertedValue;
                    convertedValue.rawValue = rawBEValue;
                    ui->tableWidget->item(i-32, 5)->setText(QString("%1").arg(QString::number(convertedValue.floatValue, 'f', 2)));
                    ui->tableWidget->item(i-32, 5)->setTextAlignment(Qt::AlignCenter);


                }

                uint32_t rawBEValue = archiverChannels[i].rawValue;
                RawAndFloat convertedValue;
                convertedValue.rawValue = rawBEValue;
                ui->widget_3->graph(i)->addData(currentDateTime.toTime_t(), convertedValue.floatValue);
                ui->widget_3->graph(i)->rescaleValueAxis(true);
                ui->widget_3->xAxis->setRange(currentDateTime.toTime_t(), 8, Qt::AlignRight);
                ui->widget_3->replot();
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
       // label->setPixmap(QPixmap("IM_24_blue"));
        label->setPixmap(QPixmap(": /img/IM_24_blue"));
        label2->setText("  Связь установлена");
}



void MainWindow::on_actionSave_triggered()
{
    model->database().transaction();
    if(model->submitAll())
        model->database().commit();
    else
        model->database().rollback();
}

void MainWindow::stopGetData()
{
    timer.stop();
    //label->setPixmap(QPixmap("IM_24_red"));
    label->setPixmap(QPixmap(": /img/IM_24_red"));
    label2->setText("  Связи нет");
}

void MainWindow::onCheckBoxHeaderClick1()
{
    if(headerr->isChecked1())
    {
        for (int i=0; i<33; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,1), Qt::Checked, Qt::CheckStateRole);
        }
    }
    else
    {
        for (int i=0; i<33; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,1), Qt::Unchecked, Qt::CheckStateRole);
        }
    }
}

void MainWindow::onCheckBoxHeaderClick2()
{
    if(headerr->isChecked2())
    {
        for (int i=0; i<33; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,2), Qt::Checked, Qt::CheckStateRole);
        }
    }
    else
    {
        for (int i=0; i<33; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,2), Qt::Unchecked, Qt::CheckStateRole);
        }
    }
}
