#ifndef COMBOBOXMODBUSDELEGATE_H
#define COMBOBOXMODBUSDELEGATE_H

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

class ComboBoxModbusDelegate : public QStyledItemDelegate
{
public:
    ComboBoxModbusDelegate(QObject *parent = nullptr);
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void changedComboBox(int /*index*/);

private:
    MainWindow *mainWindow;
};

#endif // COMBOBOXMODBUSDELEGATE_H
