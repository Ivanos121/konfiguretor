/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_preferNastr
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *preferNastr)
    {
        if (preferNastr->objectName().isEmpty())
            preferNastr->setObjectName(QString::fromUtf8("preferNastr"));
        preferNastr->resize(598, 384);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/img/IM_24_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        preferNastr->setWindowIcon(icon);
        pushButton = new QPushButton(preferNastr);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(260, 330, 85, 33));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setFocusPolicy(Qt::NoFocus);

        retranslateUi(preferNastr);

        QMetaObject::connectSlotsByName(preferNastr);
    } // setupUi

    void retranslateUi(QWidget *preferNastr)
    {
        preferNastr->setWindowTitle(QCoreApplication::translate("preferNastr", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        pushButton->setText(QCoreApplication::translate("preferNastr", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class preferNastr: public Ui_preferNastr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
