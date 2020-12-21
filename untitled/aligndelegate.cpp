#include "aligndelegate.h"

#include <QAbstractTableModel>

AlignDelegate::AlignDelegate(QObject *parent) : QSqlTableModel(parent)
{

}

QVariant AlignDelegate::data(const QModelIndex &item, int role) const
{
    if(role==Qt::TextAlignmentRole)
    {
    if(item.column()==6)
    return int(Qt::AlignCenter);
    if(item.column()==7)
    return int(Qt::AlignCenter);
    return Qt::AlignCenter;
    }
        return QSqlTableModel::data(item,role);
}

