#include "aligndelegate.h"

#include <QAbstractTableModel>

AlignDelegate::AlignDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QVariant AlignDelegate::data(const QModelIndex &item, int role) const
{
    if(role==Qt::TextAlignmentRole)
    {
    if(item.column()==5)
    return int(Qt::AlignCenter);
    if(item.column()==7)
    return int(Qt::AlignCenter);
    return Qt::AlignCenter;
    }
        return AlignDelegate::data(item,role);
}

