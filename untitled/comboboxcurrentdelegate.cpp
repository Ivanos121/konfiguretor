#include "comboboxcurrentdelegate.h"

#include <QString>
#include <QMouseEvent>
#include <QApplication>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QPainter>

#include "mainwindow.h"

ComboBoxCurrentDelegate::ComboBoxCurrentDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    mainWindow = (MainWindow*)parent;
}

QWidget* ComboBoxCurrentDelegate::createEditor(QWidget* parent,
    const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (mainWindow->disabledCells.contains(QPoint(index.row(), index.column())))
    {
        return nullptr;
    }

    if(index.column() == 17)
    {
        QComboBox* editor = new QComboBox(parent);
        editor->insertItem(0, "0..5 мА");
        editor->insertItem(1, "0..20 мА");
        editor->insertItem(2, "4..20 мА");
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ComboBoxCurrentDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if(index.column() == 17)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        if(value == "0..5 мА")
            comboBox->setCurrentIndex(0);
        else if(value == "0..20")
            comboBox->setCurrentIndex(1);
        else if(value == "4..20")
            comboBox->setCurrentIndex(2);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);

    }else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ComboBoxCurrentDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                    const QModelIndex& index) const
{
    if(index.column() == 17)
    {
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value, Qt::EditRole);
    }else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ComboBoxCurrentDelegate::updateEditorGeometry(QWidget* editor,
    const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}

void ComboBoxCurrentDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 17)
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
    }
    QStyledItemDelegate::paint(painter, option, index);
}

