#ifndef ALIGNDELEGATE_H
#define ALIGNDELEGATE_H

#include <QString>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>
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

class AlignDelegate: public QSqlTableModel
{
public:
    AlignDelegate(QObject *parent = nullptr);
    virtual QVariant data(const QModelIndex& index, int role) const;
};

#endif // ALIGNDELEGATE_H
