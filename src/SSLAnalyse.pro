#-------------------------------------------------
#
# Project created by QtCreator 2022-05-17T08:59:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SSLAnalyse
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        net/net_util.cpp \
        net/analyze_ssl_util.cpp \
        net/analyze_http_util.cpp \
    ui/select_net_dev_dialog.cpp \
    net/net_util_thread.cpp \
    tool/log_tools.cpp \
    net/analyze_util.cpp

HEADERS += \
        mainwindow.h \
        net/net_util.h \
        net/analyze_ssl_util.h \
        net/analyze_http_util.h \
    ui/select_net_dev_dialog.h \
    net/net_util_thread.h \
     net/net_common.h \
    tool/log_tools.h \
    net/analyze_util.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_RPATHDIR += /usr/lib/x86_64-linux-gnu/

LIBS += /usr/lib/x86_64-linux-gnu/libcrypto.a /usr/lib/x86_64-linux-gnu/libssl.a /usr/lib/x86_64-linux-gnu/libpcap.a

