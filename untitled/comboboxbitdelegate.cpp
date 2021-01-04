#include "comboboxbitdelegate.h"

#include <QString>
#include <QMouseEvent>
#include <QApplication>
#include <QComboBox>
#include <QStyledItemDelegate>

ComboBoxBitDelegate::ComboBoxBitDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget* ComboBoxBitDelegate::createEditor(QWidget* parent,
    const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(index.column() == 14)
    {
        QComboBox* editor = new QComboBox(parent);
        editor->insertItem(0, "8 бит");
        editor->insertItem(1, "11 бит");
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ComboBoxBitDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if(index.column() == 14)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        if(value == "8 бит")
            comboBox->setCurrentIndex(0);
        else if(value == "11 бит")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);

    }else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ComboBoxBitDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                    const QModelIndex& index) const
{
    if(index.column() == 14)
    {
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value, Qt::EditRole);
    }else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ComboBoxBitDelegate::updateEditorGeometry(QWidget* editor,
    const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}

void ComboBoxBitDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
