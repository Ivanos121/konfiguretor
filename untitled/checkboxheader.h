#ifndef CHECKBOXHEADER_H
#define CHECKBOXHEADER_H

#include <QHeaderView>
#include <QSplitter>
#include <QMessageBox>


class CheckBoxHeader : public QHeaderView
{
    Q_OBJECT

public:
    CheckBoxHeader(Qt::Orientation orientation, QWidget* parent = 0);

    bool isChecked() const { return isChecked_; }
    void setIsChecked(bool val);
    void mousePressEvent(QMouseEvent* event);

signals:
    void checkBoxClicked(bool state);

protected:
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const;



private:
    bool isChecked_;

    void redrawCheckBox();
};

#endif // CHECKBOXHEADER_H
