#ifndef PAINTDELEGATE_H
#define PAINTDELEGATE_H

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

class MainWindow;

class PaintDelegate : public QStyledItemDelegate
{
public:
    PaintDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
    MainWindow* mainWindow;
};

#endif // PAINTDELEGATE_H
