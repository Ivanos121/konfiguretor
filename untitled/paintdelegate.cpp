#include "paintdelegate.h"

#include <QString>
#include <QMouseEvent>
#include <QApplication>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QSqlTableModel>
#include <QSpinBox>

#include "mainwindow.h"

PaintDelegate::PaintDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    mainWindow = (MainWindow*)parent;
}

void PaintDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    if (mainWindow->changedRows.contains(index.row()))
    {
        QColor background = mainWindow->changedColumnBackgroundColor; // RGB value: https://www.rapidtables.com/web/color/blue-color.html
        painter->fillRect(option.rect, background);
    }
    else if (mainWindow->disabledCells.contains(QPoint(index.row(), index.column())))
    {
        QColor background = mainWindow->disabledCellBackgroundColor; // RGB value: https://www.rapidtables.com/web/color/blue-color.html
        painter->fillRect(option.rect, background);
    }


        // Paint text
    QStyledItemDelegate::paint(painter, option, index);
}

QWidget* PaintDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (mainWindow->disabledCells.contains(QPoint(index.row(), index.column())))
    {
        return nullptr;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}
