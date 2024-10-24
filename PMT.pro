QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bigpush.cpp \
    littlepush.cpp \
    main.cpp \
    mainwindow.cpp \
    mypushbutton.cpp \
    widget.cpp

HEADERS += \
    bigpush.h \
    littlepush.h \
    mainwindow.h \
    mypushbutton.h \
    widget.h

FORMS += \
    mainwindow.ui
RC_ICONS=PrimIcon_1.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rs.qrc

