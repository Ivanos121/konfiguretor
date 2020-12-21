#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include "port.h"
#include "archiverchannel.h"
#include "qcustomplot.h"
#include "checkboxdelegate.h"
#include "comboboxdelegate.h"
#include "aligndelegate.h"
#include "checkboxheader.h"
#include <qdebug.h>
#include <QCheckBox>
#include <QMouseEvent>
#include <QMessageBox>
#include <QLinearGradient>
#include <QTableView>
#include <QHeaderView>

#define MODEL_ROWS 64            //Количество строк модели
//#define DELEGATE_COLUMN 1


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(QFileInfo("netdb.db").absoluteFilePath());

    QSqlTableModel *model = new Model;
    model->setTable("Net settings");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);

    CheckBoxDelegate* checkBoxDelegate = new CheckBoxDelegate;
    ui->tableView->setItemDelegateForColumn(0, checkBoxDelegate);
    ui->tableView->setItemDelegateForColumn(1, checkBoxDelegate);

    ComboBoxDelegate* comboBoxDelegate = new ComboBoxDelegate;
    ui->tableView->setItemDelegateForColumn(3, comboBoxDelegate);
    CheckBoxHeader* header = new CheckBoxHeader(Qt::Horizontal, ui->tableView);
    ui->tableView->setHorizontalHeader(header);

    QHeaderView *headers = ui->tableWidget->horizontalHeader();
    headers->setSectionResizeMode(QHeaderView::ResizeToContents);

    //connect(ui->tableView, SIGNAL(clickToCheck(QModelIndex)), this, SLOT(changeStateCheckBox(QModelIndex)));
   // ui->tableView->setItemDelegateForColumn(6, new AlignDelegate(ui->tableView));
ui->tableView->setColumnWidth(0,500);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //выделение строки
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); //выделение одной строки
    ui->tableView->resizeColumnsToContents();


    for (int i=0; i<64; i++)
{
    for (int j=6; j<15; j++)
    {
        //model->setData(model->index(i,j),int(Qt::AlignRight | Qt::AlignCenter), Qt::TextAlignmentRole);
    }
}





    ui->tableWidget->setRowCount(32);
    ui->tableWidget->setColumnCount(6);
    QStringList name;
    name << "№" << "Свойство" << "Значение" << "№" << "Свойство" << "Значение";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->resizeColumnsToContents();
    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
          ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
    }


    ui->tableWidget->item(0,1)->setText("Подшипниковый узел справа спереди");
    ui->tableWidget->item(1,1)->setText("Подшипниковый узел слева сзади");
    ui->tableWidget->item(2,1)->setText("Лобовая часть справа сзади");
    ui->tableWidget->item(3,1)->setText("Магнитопровод статора");
    ui->tableWidget->item(4,1)->setText("Станина");
    ui->tableWidget->item(5,1)->setText("Лобовая часть справа спереди");
    ui->tableWidget->item(6,1)->setText("Станина");
    ui->tableWidget->item(7,1)->setText("Момент");
    ui->tableWidget->item(8,1)->setText("Подшипниковый узел справа сзади");
    ui->tableWidget->item(9,1)->setText("Лобовая часть слева спереди");
    ui->tableWidget->item(10,1)->setText("Подшипниковый узел справа сзади");
    ui->tableWidget->item(11,1)->setText("Лобовая часть слева сзади");
    for (int i=0; i<32; i++)
    {
           if (ui->tableWidget->item(i, 0) != 0)
            {
                 ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
                 ui->tableWidget->item(i,0)->setTextAlignment(Qt::AlignCenter);
            }
           if (ui->tableWidget->item(i, 3) != 0)
            {
                 ui->tableWidget->item(i, 3)->setText(QString("%1").arg(i+33));
                 ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignCenter);
            }
        }

    ui->widget_3->setBufferDevicePixelRatio(.5);

      //  time=new QElapsedTimer();
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
        ui->widget_3->graph(0)->setName("Подшипниковый узел справа спереди");
        ui->widget_3->graph(0)->setPen(QPen(Qt::blue));
        ui->widget_3->addGraph();
        ui->widget_3->graph(1)->setName("Подшипниковый узел слева сзади");
        ui->widget_3->graph(1)->setPen(QPen(Qt::red));
        ui->widget_3->addGraph();
        ui->widget_3->graph(2)->setName("Лобовая часть справа сзади");
        ui->widget_3->graph(2)->setPen(QPen(Qt::green));
        ui->widget_3->addGraph();
        ui->widget_3->graph(3)->setName("Магнитопровод статор");
        ui->widget_3->graph(3)->setPen(QPen(Qt::cyan));
        ui->widget_3->addGraph();
        ui->widget_3->graph(4)->setName("Станина");
        ui->widget_3->graph(4)->setPen(QPen(QColor(47, 15, 163)));
        ui->widget_3->addGraph();
        ui->widget_3->graph(5)->setName("Лобовая часть справа спереди");
        ui->widget_3->graph(5)->setPen(QPen(QColor(47, 15, 163)));
        ui->widget_3->addGraph();
        ui->widget_3->graph(6)->setName("Станина");
        ui->widget_3->graph(6)->setPen(QPen(QColor(102, 245, 7)));
        ui->widget_3->addGraph();
        ui->widget_3->graph(7)->setName("Момент");
        ui->widget_3->graph(7)->setPen(QPen(QColor(102, 245, 7)));
        ui->widget_3->addGraph();
        ui->widget_3->graph(8)->setName("Подшипниковый узел справа сзади");
        ui->widget_3->graph(8)->setPen(QPen(QColor(102, 245, 7)));


        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%h:%m:%s");
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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStateCheckBox(QModelIndex index)
{
    QSqlTableModel *model = new Model;
    int state = index.model()->data(index).toBool();
    QVariant value = !state;
    model->setData(index, value);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->comboBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
          ui->comboBox->addItem(info.portName());
          ui->comboBox->addItem("ttyMP0");
          ui->comboBox->addItem("ttyMP1");
        }
}

void MainWindow::on_pushButton_clicked()
{
savesettings(ui->comboBox->currentText(), ui->comboBox_2->currentText().toInt(),ui->comboBox_3->currentText().toInt(),
             ui->comboBox_4->currentText().toInt(), ui->comboBox_5->currentText().toInt(), ui->comboBox_6->currentText().toInt());
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
    }
    else
    {
        timer.stop();
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
            port->waitForReadyRead(100);
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
            port->waitForReadyRead(100);
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

        for (int i=0; i<64; i++)
        {
            if(ui->tableView->model()->index(i,0).data(Qt::CheckStateRole)==Qt::Checked)
            {
                //запись результата в таблицу
                if (ui->tableWidget->item(i, 1) != 0)
                {
                    uint32_t rawBEValue = archiverChannels[i].rawValue;
                    RawAndFloat convertedValue;
                    convertedValue.rawValue = rawBEValue;
                    ui->tableWidget->item(i, 1)->setText(QString("%1").arg(convertedValue.floatValue));
                    ui->tableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);
                }
            }
        }
}


