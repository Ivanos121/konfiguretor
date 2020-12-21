QT       += core gui serialport sql webkitwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG+=debug

DEFINES += QCUSTOMPLOT_USE_OPENGL

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aligndelegate.cpp \
    archiverchannel.cpp \
    checkboxdelegate.cpp \
    checkboxheader.cpp \
    comboboxdelegate.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    qcustomplot.cpp

HEADERS += \
    aligndelegate.h \
    archiverchannel.h \
    checkboxdelegate.h \
    checkboxheader.h \
    comboboxdelegate.h \
    mainwindow.h \
    model.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
