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
#include "paintdelegate.h"
#include "pointcolumndelegate.h"
#include "comboboxcurrentdelegate.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , disabledCellBackgroundColor(180, 180, 180)
    , changedColumnBackgroundColor(144,238,144)
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
    ui->tableView->setItemDelegateForColumn(17, paintdelegate);

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


    ui->widget_3->setBufferDevicePixelRatio(.5);

    ui->widget_3->setMaximumSize(ui->widget_3->maximumWidth(), ui->widget_3->maximumHeight());
    ui->widget_3->setOpenGl(true);

    ui->widget_3->legend->setVisible(false);
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
    QColor currentColor0 = QColor(75,0,130);
    ui->widget_3->graph(0)->setName("Подшипниковый узел справа впереди");
    ui->widget_3->graph(0)->setPen(QPen(QColor(currentColor0)));

    ui->widget_3->addGraph();
    QColor currentColor1 = QColor(138,43,226);
    ui->widget_3->graph(1)->setName("Подшипниковый узел слева сзади");
    ui->widget_3->graph(1)->setPen(QPen(QColor(currentColor1)));

    ui->widget_3->addGraph();
    QColor currentColor2 = QColor(0,0,255);
    ui->widget_3->graph(2)->setName("Лобовая часть справа сзади");
    ui->widget_3->graph(2)->setPen(QPen(QColor(currentColor2)));

    ui->widget_3->addGraph();
    QColor currentColor3 = QColor(95,158,160);
    ui->widget_3->graph(3)->setName("Магнитопровод статора");
    ui->widget_3->graph(3)->setPen(QPen(QColor(currentColor3)));

    ui->widget_3->addGraph();
    QColor currentColor4 = QColor(100,149,237);
    ui->widget_3->graph(4)->setName("Станина");
    ui->widget_3->graph(4)->setPen(QPen(QColor(currentColor4)));

    ui->widget_3->addGraph();
    QColor currentColor5 = QColor(0,191,255);
    ui->widget_3->graph(5)->setName("Лобовая часть справа впереди");
    ui->widget_3->graph(5)->setPen(QPen(QColor(currentColor5)));

    ui->widget_3->addGraph();
    QColor currentColor6 = QColor(135,206,250);
    ui->widget_3->graph(6)->setName("Станина");
    ui->widget_3->graph(6)->setPen(QPen(QColor(currentColor6)));

    ui->widget_3->addGraph();
    QColor currentColor7 = QColor(244,164,96);
    ui->widget_3->graph(7)->setName("Момент");
    ui->widget_3->graph(7)->setPen(QPen(QColor(currentColor7)));

    ui->widget_3->addGraph();
    QColor currentColor8 = QColor(128,0,0);
    ui->widget_3->graph(8)->setName("Подшипниковый узел справа сзади");
    ui->widget_3->graph(8)->setPen(QPen(QColor(currentColor8)));

    ui->widget_3->addGraph();
    QColor currentColor9 = QColor(160,82,45);
    ui->widget_3->graph(9)->setName("Лобовая часть слева впереди");
    ui->widget_3->graph(9)->setPen(QPen(QColor(currentColor9)));

    ui->widget_3->addGraph();
    QColor currentColor10 = QColor(210,105,30);
    ui->widget_3->graph(10)->setName("Подшипниковый узел слева впереди");
    ui->widget_3->graph(10)->setPen(QPen(QColor(currentColor10)));

    ui->widget_3->addGraph();
    QColor currentColor11 = QColor(244,164,96);
    ui->widget_3->graph(11)->setName("Лобовая часть слева сзади");
    ui->widget_3->graph(11)->setPen(QPen(QColor(currentColor11)));

    ui->widget_3->addGraph();
    QColor currentColor12 = QColor(188,143,143);
    ui->widget_3->graph(12)->setName("Скорость вращения ротора");
    ui->widget_3->graph(12)->setPen(QPen(QColor(currentColor12)));

    ui->widget_3->addGraph();
    QColor currentColor13 = QColor(255,223,0);
    ui->widget_3->graph(13)->setName("Переменное напряжение фазы А");
    ui->widget_3->graph(13)->setPen(QPen(QColor(currentColor13)));

    ui->widget_3->addGraph();
    QColor currentColor14 = QColor(102, 245, 7);
    ui->widget_3->graph(14)->setName("Переменный ток фазы А");
    ui->widget_3->graph(14)->setPen(QPen(QColor(currentColor14)));

    ui->widget_3->addGraph();
    QColor currentColor15 = QColor(255,255,0);
    ui->widget_3->graph(15)->setName("Активная мощность фазы А");
    ui->widget_3->graph(15)->setPen(QPen(QColor(currentColor15)));

    ui->widget_3->addGraph();
    QColor currentColor16 = QColor(173,255,47);
    ui->widget_3->graph(16)->setName("Реактивная мощность фазы А");
    ui->widget_3->graph(16)->setPen(QPen(QColor(currentColor16)));

    ui->widget_3->addGraph();
    QColor currentColor17 = QColor(240,230,140);
    ui->widget_3->graph(17)->setName("Полная мощность фазы А");
    ui->widget_3->graph(17)->setPen(QPen(QColor(currentColor17)));

    ui->widget_3->addGraph();
    QColor currentColor18 = QColor(219,112,147);
    ui->widget_3->graph(18)->setName("Частота фазы А");
    ui->widget_3->graph(18)->setPen(QPen(QColor(currentColor18)));

    ui->widget_3->addGraph();
    QColor currentColor19 = QColor(255,160,122);
    ui->widget_3->graph(19)->setName("Коэффициент мощности фазы А");
    ui->widget_3->graph(19)->setPen(QPen(QColor(currentColor19)));

    ui->widget_3->addGraph();
    QColor currentColor20 = QColor(205,92,92);
    ui->widget_3->graph(20)->setName("Переменное напряжение фазы B");
    ui->widget_3->graph(20)->setPen(QPen(QColor(currentColor20)));

    ui->widget_3->addGraph();
    QColor currentColor21 = QColor(255,140,0);
    ui->widget_3->graph(21)->setName("Переменный ток фазы B");
    ui->widget_3->graph(21)->setPen(QPen(QColor(currentColor21)));

    ui->widget_3->addGraph();
    QColor currentColor22 = QColor(255,99,71);
    ui->widget_3->graph(22)->setName("Активная мощность фазы B");
    ui->widget_3->graph(22)->setPen(QPen(QColor(currentColor22)));

    ui->widget_3->addGraph();
    QColor currentColor23 = QColor(255,192,203);
    ui->widget_3->graph(23)->setName("Реактивная мощность фазы B");
    ui->widget_3->graph(23)->setPen(QPen(QColor(currentColor23)));

    ui->widget_3->addGraph();
    QColor currentColor24 = QColor(255,105,180);
    ui->widget_3->graph(24)->setName("Полная мощность фазы B");
    ui->widget_3->graph(24)->setPen(QPen(QColor(currentColor24)));

    ui->widget_3->addGraph();
    QColor currentColor25 = QColor(128,0,128);
    ui->widget_3->graph(25)->setName("Частота фазы B");
    ui->widget_3->graph(25)->setPen(QPen(QColor(currentColor25)));

    ui->widget_3->addGraph();
    QColor currentColor26 = QColor(160,82,45);
    ui->widget_3->graph(26)->setName("Коэффициент мощности фазы B");
    ui->widget_3->graph(26)->setPen(QPen(QColor(currentColor26)));

    ui->widget_3->addGraph();
    QColor currentColor27 = QColor(245,245,220);
    ui->widget_3->graph(27)->setName("Переменное напряжение фазы C");
    ui->widget_3->graph(27)->setPen(QPen(QColor(currentColor27)));

    ui->widget_3->addGraph();
    QColor currentColor28 = QColor(240,255,255);
    ui->widget_3->graph(28)->setName("Переменный ток фазы C");
    ui->widget_3->graph(28)->setPen(QPen(QColor(currentColor28)));

    ui->widget_3->addGraph();
    QColor currentColor29 = QColor(245,245,220);
    ui->widget_3->graph(29)->setName("Активная мощность фазы C");
    ui->widget_3->graph(29)->setPen(QPen(QColor(currentColor29)));

    ui->widget_3->addGraph();
    QColor currentColor30 = QColor(255,222,173);
    ui->widget_3->graph(30)->setName("Реактивная мощность фазы C");
    ui->widget_3->graph(30)->setPen(QPen(QColor(currentColor30)));

    ui->widget_3->addGraph();
    QColor currentColor31 = QColor(135,206,250);
    ui->widget_3->graph(31)->setName("Полная мощность фазы C");
    ui->widget_3->graph(31)->setPen(QPen(QColor(currentColor31)));

    ui->widget_3->addGraph();
    QColor currentColor32 = QColor(95,158,160);
    ui->widget_3->graph(32)->setName("Частота фазы C");
    ui->widget_3->graph(32)->setPen(QPen(QColor(currentColor32)));

    ui->widget_3->addGraph();
    QColor currentColor33 = QColor(75,0,130);
    ui->widget_3->graph(33)->setName("Коэффициент мощности фазы C");
    ui->widget_3->graph(33)->setPen(QPen(QColor(currentColor33)));

    ui->widget_3->addGraph();
    QColor currentColor34 = QColor(75,0,130);
    ui->widget_3->graph(34)->setName("Подшипниковый узел справа впереди");
    ui->widget_3->graph(34)->setPen(QPen(QColor(currentColor34)));

    ui->widget_3->addGraph();
    QColor currentColor35 = QColor(138,43,226);
    ui->widget_3->graph(35)->setName("Подшипниковый узел слева сзади");
    ui->widget_3->graph(35)->setPen(QPen(QColor(currentColor35)));

    ui->widget_3->addGraph();
    QColor currentColor36 = QColor(0,0,255);
    ui->widget_3->graph(36)->setName("Лобовая часть справа сзади");
    ui->widget_3->graph(36)->setPen(QPen(QColor(currentColor36)));

    ui->widget_3->addGraph();
    QColor currentColor37 = QColor(95,158,160);
    ui->widget_3->graph(37)->setName("Магнитопровод статора");
    ui->widget_3->graph(37)->setPen(QPen(QColor(currentColor37)));

    ui->widget_3->addGraph();
    QColor currentColor38 = QColor(100,149,237);
    ui->widget_3->graph(38)->setName("Станина");
    ui->widget_3->graph(38)->setPen(QPen(QColor(currentColor38)));

    ui->widget_3->addGraph();
    QColor currentColor39 = QColor(0,191,255);
    ui->widget_3->graph(39)->setName("Лобовая часть справа впереди");
    ui->widget_3->graph(39)->setPen(QPen(QColor(currentColor39)));

    ui->widget_3->addGraph();
    QColor currentColor40 = QColor(135,206,250);
    ui->widget_3->graph(40)->setName("Станина");
    ui->widget_3->graph(40)->setPen(QPen(QColor(currentColor40)));

    ui->widget_3->addGraph();
    QColor currentColor41 = QColor(244,164,96);
    ui->widget_3->graph(41)->setName("Момент");
    ui->widget_3->graph(41)->setPen(QPen(QColor(currentColor41)));

    ui->widget_3->addGraph();
    QColor currentColor42 = QColor(128,0,0);
    ui->widget_3->graph(42)->setName("Подшипниковый узел справа сзади");
    ui->widget_3->graph(42)->setPen(QPen(QColor(currentColor42)));

    ui->widget_3->addGraph();
    QColor currentColor43 = QColor(160,82,45);
    ui->widget_3->graph(43)->setName("Лобовая часть слева впереди");
    ui->widget_3->graph(43)->setPen(QPen(QColor(currentColor43)));

    ui->widget_3->addGraph();
    QColor currentColor44 = QColor(210,105,30);
    ui->widget_3->graph(44)->setName("Подшипниковый узел слева впереди");
    ui->widget_3->graph(44)->setPen(QPen(QColor(currentColor44)));

    ui->widget_3->addGraph();
    QColor currentColor45 = QColor(244,164,96);
    ui->widget_3->graph(45)->setName("Лобовая часть слева сзади");
    ui->widget_3->graph(45)->setPen(QPen(QColor(currentColor45)));

    ui->widget_3->addGraph();
    QColor currentColor46 = QColor(188,143,143);
    ui->widget_3->graph(46)->setName("Скорость вращения ротора");
    ui->widget_3->graph(46)->setPen(QPen(QColor(currentColor46)));

    ui->widget_3->addGraph();
    QColor currentColor47 = QColor(255,223,0);
    ui->widget_3->graph(47)->setName("Переменное напряжение фазы А");
    ui->widget_3->graph(47)->setPen(QPen(QColor(currentColor47)));

    ui->widget_3->addGraph();
    QColor currentColor48 = QColor(102, 245, 7);
    ui->widget_3->graph(48)->setName("Переменный ток фазы А");
    ui->widget_3->graph(48)->setPen(QPen(QColor(currentColor48)));

    ui->widget_3->addGraph();
    QColor currentColor49 = QColor(255,255,0);
    ui->widget_3->graph(49)->setName("Активная мощность фазы А");
    ui->widget_3->graph(49)->setPen(QPen(QColor(currentColor49)));

    ui->widget_3->addGraph();
    QColor currentColor50 = QColor(173,255,47);
    ui->widget_3->graph(50)->setName("Реактивная мощность фазы А");
    ui->widget_3->graph(50)->setPen(QPen(QColor(currentColor50)));

    ui->widget_3->addGraph();
    QColor currentColor51 = QColor(240,230,140);
    ui->widget_3->graph(51)->setName("Полная мощность фазы А");
    ui->widget_3->graph(51)->setPen(QPen(QColor(currentColor51)));

    ui->widget_3->addGraph();
    QColor currentColor52 = QColor(219,112,147);
    ui->widget_3->graph(52)->setName("Частота фазы А");
    ui->widget_3->graph(52)->setPen(QPen(QColor(currentColor52)));

    ui->widget_3->addGraph();
    QColor currentColor53 = QColor(255,160,122);
    ui->widget_3->graph(53)->setName("Коэффициент мощности фазы А");
    ui->widget_3->graph(53)->setPen(QPen(QColor(currentColor53)));

    ui->widget_3->addGraph();
    QColor currentColor54 = QColor(205,92,92);
    ui->widget_3->graph(54)->setName("Переменное напряжение фазы B");
    ui->widget_3->graph(54)->setPen(QPen(QColor(currentColor54)));

    ui->widget_3->addGraph();
    QColor currentColor55 = QColor(255,140,0);
    ui->widget_3->graph(55)->setName("Переменный ток фазы B");
    ui->widget_3->graph(55)->setPen(QPen(QColor(currentColor55)));

    ui->widget_3->addGraph();
    QColor currentColor56 = QColor(255,99,71);
    ui->widget_3->graph(56)->setName("Активная мощность фазы B");
    ui->widget_3->graph(56)->setPen(QPen(QColor(currentColor22)));

    ui->widget_3->addGraph();
    QColor currentColor57 = QColor(255,192,203);
    ui->widget_3->graph(57)->setName("Реактивная мощность фазы B");
    ui->widget_3->graph(57)->setPen(QPen(QColor(currentColor57)));

    ui->widget_3->addGraph();
    QColor currentColor58 = QColor(255,105,180);
    ui->widget_3->graph(58)->setName("Полная мощность фазы B");
    ui->widget_3->graph(58)->setPen(QPen(QColor(currentColor58)));

    ui->widget_3->addGraph();
    QColor currentColor59 = QColor(128,0,128);
    ui->widget_3->graph(59)->setName("Частота фазы B");
    ui->widget_3->graph(59)->setPen(QPen(QColor(currentColor59)));

    ui->widget_3->addGraph();
    QColor currentColor60 = QColor(160,82,45);
    ui->widget_3->graph(60)->setName("Коэффициент мощности фазы B");
    ui->widget_3->graph(60)->setPen(QPen(QColor(currentColor60)));

    ui->widget_3->addGraph();
    QColor currentColor61 = QColor(245,245,220);
    ui->widget_3->graph(61)->setName("Переменное напряжение фазы C");
    ui->widget_3->graph(61)->setPen(QPen(QColor(currentColor61)));

    ui->widget_3->addGraph();
    QColor currentColor62 = QColor(240,255,255);
    ui->widget_3->graph(62)->setName("Переменный ток фазы C");
    ui->widget_3->graph(62)->setPen(QPen(QColor(currentColor62)));

    ui->widget_3->addGraph();
    QColor currentColor63 = QColor(245,245,220);
    ui->widget_3->graph(63)->setName("Активная мощность фазы C");
    ui->widget_3->graph(63)->setPen(QPen(QColor(currentColor63)));

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
    label->setPixmap(QPixmap(":/new/prefix1/img/IM_24_red"));
    label2->setText("  Связи нет");

    connect(model, &QSqlTableModel::dataChanged,this, &MainWindow::selectRows);

    setDisabledCells();

    //настройка таблицы вывода данных
    ui->tableWidget_2->setRowCount(64); //задание количества строк таблицы
    ui->tableWidget_2->setColumnCount(4); //задание количества столбцов
    QStringList name2; //объявление указателя на тип QStringList
    name2 << "№" << "Цвет" << "Свойство" << "Значение"; //перечисление заголовков
    ui->tableWidget_2->setHorizontalHeaderLabels(name2); //установка заголовков в таблицу
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
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

    ui->tableWidget_2->item(0, 1)->setBackground(currentColor0);
    ui->tableWidget_2->item(1, 1)->setBackground(currentColor1);
    ui->tableWidget_2->item(2, 1)->setBackground(currentColor2);
    ui->tableWidget_2->item(3, 1)->setBackground(currentColor3);
    ui->tableWidget_2->item(4, 1)->setBackground(currentColor4);
    ui->tableWidget_2->item(5, 1)->setBackground(currentColor5);
    ui->tableWidget_2->item(6, 1)->setBackground(currentColor6);
    ui->tableWidget_2->item(7, 1)->setBackground(currentColor7);
    ui->tableWidget_2->item(8, 1)->setBackground(currentColor8);
    ui->tableWidget_2->item(9, 1)->setBackground(currentColor9);

    ui->tableWidget_2->item(10, 1)->setBackground(currentColor10);
    ui->tableWidget_2->item(11, 1)->setBackground(currentColor11);
    ui->tableWidget_2->item(12, 1)->setBackground(currentColor12);
    ui->tableWidget_2->item(13, 1)->setBackground(currentColor13);
    ui->tableWidget_2->item(14, 1)->setBackground(currentColor14);
    ui->tableWidget_2->item(15, 1)->setBackground(currentColor15);
    ui->tableWidget_2->item(16, 1)->setBackground(currentColor16);
    ui->tableWidget_2->item(17, 1)->setBackground(currentColor17);
    ui->tableWidget_2->item(18, 1)->setBackground(currentColor18);
    ui->tableWidget_2->item(19, 1)->setBackground(currentColor19);

    ui->tableWidget_2->item(20, 1)->setBackground(currentColor20);
    ui->tableWidget_2->item(21, 1)->setBackground(currentColor21);
    ui->tableWidget_2->item(22, 1)->setBackground(currentColor22);
    ui->tableWidget_2->item(23, 1)->setBackground(currentColor23);
    ui->tableWidget_2->item(24, 1)->setBackground(currentColor24);
    ui->tableWidget_2->item(25, 1)->setBackground(currentColor25);
    ui->tableWidget_2->item(26, 1)->setBackground(currentColor26);
    ui->tableWidget_2->item(27, 1)->setBackground(currentColor27);
    ui->tableWidget_2->item(28, 1)->setBackground(currentColor28);
    ui->tableWidget_2->item(29, 1)->setBackground(currentColor29);

    ui->tableWidget_2->item(30, 1)->setBackground(currentColor30);
    ui->tableWidget_2->item(31, 1)->setBackground(currentColor31);
    ui->tableWidget_2->item(32, 1)->setBackground(currentColor32);
    ui->tableWidget_2->item(33, 1)->setBackground(currentColor33);
    ui->tableWidget_2->item(34, 1)->setBackground(currentColor34);
    ui->tableWidget_2->item(35, 1)->setBackground(currentColor35);
    ui->tableWidget_2->item(36, 1)->setBackground(currentColor36);
    ui->tableWidget_2->item(37, 1)->setBackground(currentColor37);
    ui->tableWidget_2->item(38, 1)->setBackground(currentColor38);
    ui->tableWidget_2->item(39, 1)->setBackground(currentColor39);

    ui->tableWidget_2->item(40, 1)->setBackground(currentColor40);
    ui->tableWidget_2->item(41, 1)->setBackground(currentColor41);
    ui->tableWidget_2->item(42, 1)->setBackground(currentColor42);
    ui->tableWidget_2->item(43, 1)->setBackground(currentColor43);
    ui->tableWidget_2->item(44, 1)->setBackground(currentColor44);
    ui->tableWidget_2->item(45, 1)->setBackground(currentColor45);
    ui->tableWidget_2->item(46, 1)->setBackground(currentColor46);
    ui->tableWidget_2->item(47, 1)->setBackground(currentColor47);
    ui->tableWidget_2->item(48, 1)->setBackground(currentColor48);
    ui->tableWidget_2->item(49, 1)->setBackground(currentColor49);

    ui->tableWidget_2->item(50, 1)->setBackground(currentColor50);
    ui->tableWidget_2->item(51, 1)->setBackground(currentColor51);
    ui->tableWidget_2->item(52, 1)->setBackground(currentColor52);
    ui->tableWidget_2->item(53, 1)->setBackground(currentColor53);
    ui->tableWidget_2->item(54, 1)->setBackground(currentColor54);
    ui->tableWidget_2->item(55, 1)->setBackground(currentColor55);
    ui->tableWidget_2->item(56, 1)->setBackground(currentColor56);
    ui->tableWidget_2->item(57, 1)->setBackground(currentColor57);
    ui->tableWidget_2->item(58, 1)->setBackground(currentColor58);
    ui->tableWidget_2->item(59, 1)->setBackground(currentColor59);

    ui->tableWidget_2->item(60, 1)->setBackground(currentColor60);
    ui->tableWidget_2->item(61, 1)->setBackground(currentColor61);
    ui->tableWidget_2->item(62, 1)->setBackground(currentColor62);
    ui->tableWidget_2->item(63, 1)->setBackground(currentColor63);

    connect(ui->tableWidget_2, &QTableWidget::cellClicked,this, &MainWindow::setcolorincell);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setcolorincell(int row, int column)
{
    if (column == 1)
    {
        row = ui->tableWidget_2->currentRow();
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget_2->item(row, column)->setBackground(chosenColor);
        ui->widget_3->graph(row)->setPen(QPen(chosenColor));
        ui->widget_3->replot();
    }
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

        for (int i=0; i<64; i++)
        {
            if(ui->tableView->model()->index(i,1).data(Qt::CheckStateRole)==Qt::Checked)
            {

                //запись результата в таблицу
                if (ui->tableWidget->item(i, 2) != 0)
                {
                    int k=ui->tableView->model()->data(ui->tableView->model()->index(i, 8) ).toInt();
                    uint32_t rawBEValue = archiverChannels[i].rawValue;

                    QString value = ui->tableView->model()->data(ui->tableView->model()->index(i, 7) ).toString();

                    if(value == "INT16(Little-endian)")
                    {}
                    else if(value == "WORD16(Little-endian)")
                    {}
                    else if(value == "LONGINT32(Little-endian)")
                    {
                        ui->tableWidget->item(i, 2)->setText(QString("%1").arg(QString::number((double)rawBEValue / pow(10,k), 'f', k)));
                       // ui->tableWidget_2->item(i, 3)->setText(QString("%1").arg(QString::number((double)rawBEValue / pow(10,k), 'f', k)));
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
                                        ui->tableWidget->item(i-32, 2)->setText(QString("%1").arg(QString::number(convertedValue.floatValue, 'f', k2)));
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
        label->setPixmap(QPixmap(":/new/prefix1/img/IM_24_blue"));
        label2->setText("  Связь установлена");
}

void MainWindow::on_actionSave_triggered()
{
    model->database().transaction();
    if(model->submitAll())
        model->database().commit();
    else
        model->database().rollback();

    changedRows.clear();
    disabledCells.clear();
    setDisabledCells();
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
    }
}
