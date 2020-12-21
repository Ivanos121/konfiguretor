#ifndef COMBOBOXCHECK_H
#define COMBOBOXCHECK_H

#include <QSqlQueryModel>

class Comboboxcheck : public QSqlQueryModel
{
    Q_OBJECT

    QVariant dataFromParent(QModelIndex index, int column) const;

public:
    Comboboxcheck();
    explicit Comboboxcheck( const QString &columns, const QString &queryTail, QObject *parent = 0 );
    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex &parent) const;
};

#endif // COMBOBOXCHECK_H


