#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableView>

class MyTableView : public QTableView
{
    Q_OBJECT

public:
    MyTableView(QObject* parent = 0);

    void mouseMoveEvent(QMouseEvent* event) override;

signals:
    void mouseHover(QModelIndex index);
};

#endif // MYTABLEVIEW_H
