#ifndef MODEL2_H
#define MODEL2_H

#include "QSqlDatabase"
#include <QSqlError>
#include "QtSql"

class Model2 : public QSqlTableModel
{
public:
    Model2();
    virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
};

#endif // MODEL2_H
