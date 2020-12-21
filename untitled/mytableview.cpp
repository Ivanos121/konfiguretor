#include "mytableview.h"
#include <QMouseEvent>

MyTableView::MyTableView(QObject* /*parent*/)
{

}

void MyTableView::mouseMoveEvent(QMouseEvent* event)
{
    QPoint position = event->pos();
    QModelIndex index = indexAt(position);
    emit mouseHover(index);
}


