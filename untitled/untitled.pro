QT       += core gui serialport sql printsupport webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG+=debug

DEFINES += QCUSTOMPLOT_USE_OPENGL

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    align.cpp \
    archiverchannel.cpp \
    checkboxdelegate.cpp \
    checkboxheader.cpp \
    comboboxbitdelegate.cpp \
    comboboxcurrentdelegate.cpp \
    comboboxdelegate.cpp \
    comboboxerrorarchivedelegate.cpp \
    comboboxmodbusdelegate.cpp \
    comboboxvardelegate.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    paintdelegate.cpp \
    plot.cpp \
    pointcolumndelegate.cpp \
    qcustomplot.cpp

HEADERS += \
    align.h \
    archiverchannel.h \
    checkboxdelegate.h \
    checkboxheader.h \
    comboboxbitdelegate.h \
    comboboxcurrentdelegate.h \
    comboboxdelegate.h \
    comboboxerrorarchivedelegate.h \
    comboboxmodbusdelegate.h \
    comboboxvardelegate.h \
    mainwindow.h \
    model.h \
    paintdelegate.h \
    plot.h \
    pointcolumndelegate.h \
    qcustomplot.h

FORMS += \
    about_dialog.ui \
    mainwindow.ui \
    plot.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
