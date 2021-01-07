#include "paintdelegate.h"

#include <QString>
#include <QMouseEvent>
#include <QApplication>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QSqlTableModel>
#include <QSpinBox>

PaintDelegate::PaintDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void PaintDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    QColor background = QColor(0,250,0); // RGB value: https://www.rapidtables.com/web/color/blue-color.html
        painter->fillRect(option.rect, background);

        // Paint text
        QStyledItemDelegate::paint(painter, option, index);
}

QWidget* PaintDelegate::createEditor(QWidget* parent,
    const QStyleOptionViewItem& option, const QModelIndex& index) const
{
        QSpinBox *editor = new QSpinBox(parent);

        editor->setMinimum(-99999);
        editor->setMaximum(99999);

        return editor;
    }


