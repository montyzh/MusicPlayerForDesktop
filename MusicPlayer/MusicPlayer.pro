#-------------------------------------------------
#
# Project created by QtCreator 2018-02-07T23:13:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    my_mci.cpp

HEADERS  += mainwindow.h \
    my_mci.h \
    head_file.h \
    define.h

FORMS    += mainwindow.ui

RESOURCES += \
    img_rs.qrc

DISTFILES += \
    css.qss

RC_ICONS =app.ico
