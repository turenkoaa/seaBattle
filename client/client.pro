#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T22:06:57
#
#-------------------------------------------------

QT       += core gui
QT += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp \
    seabattle.cpp \
    startpage.cpp \
    Player.cpp \
    disconnectionpage.cpp \
    help.cpp \
    about.cpp \
    centralwidget.cpp \
    chooseenemypage.cpp \
    exitdialog.cpp \
    levelofgame.cpp

HEADERS  += client.h \
    seabattle.h \
    startpage.h \
    Player.h \
    disconnectionpage.h \
    help.h \
    about.h \
    centralwidget.h \
    chooseenemypage.h \
    exitdialog.h \
    levelofgame.h

FORMS    += client.ui \
    seabattle.ui \
    startpage.ui \
    disconnectionpage.ui \
    help.ui \
    about.ui \
    centralwidget.ui \
    chooseenemypage.ui \
    exitdialog.ui \
    levelofgame.ui
