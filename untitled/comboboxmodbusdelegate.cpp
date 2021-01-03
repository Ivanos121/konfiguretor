#include "comboboxmodbusdelegate.h"

#include <QString>
#include <QMouseEvent>
#include <QApplication>
#include <QComboBox>
#include <QStyledItemDelegate>

ComboBoxModbusDelegate::ComboBoxModbusDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget* ComboBoxModbusDelegate::createEditor(QWidget* parent,
    const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(index.column() == 11)
    {
        QComboBox* editor = new QComboBox(parent);
        editor->insertItem(0, "3");
        editor->insertItem(1, "4");

        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ComboBoxModbusDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if(index.column() == 11)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        if(value == "3")
            comboBox->setCurrentIndex(0);
        else if(value == "4")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ComboBoxModbusDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                    const QModelIndex& index) const
{
    if(index.column() == 11)
    {
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value, Qt::EditRole);
    }else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ComboBoxModbusDelegate::updateEditorGeometry(QWidget* editor,
    const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}



void ComboBoxModbusDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 3) // show combobox only in the second column
    {
        QStyleOptionComboBox box;
        box.state = option.state;

        box.rect = option.rect;
        box.currentText = index.data(Qt::EditRole).toString();

        QApplication::style()->drawComplexControl(QStyle::CC_ComboBox, &box, painter, 0);
        QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel, &box, painter, 0);
        return;
    }
    QStyledItemDelegate::paint(painter, option, index);
}
