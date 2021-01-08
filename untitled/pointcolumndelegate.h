#ifndef POINTCOLUMNDELEGATE_H
#define POINTCOLUMNDELEGATE_H

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

class PointColumnDelegate : public QStyledItemDelegate
{
public:
    PointColumnDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};


#endif // POINTCOLUMNDELEGATE_H
