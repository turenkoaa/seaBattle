#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T22:52:25
#
#-------------------------------------------------

QT       += core gui
QT += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        myserver.cpp \
    client.cpp

HEADERS  += myserver.h \
    client.h
