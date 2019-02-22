#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T14:10:02
#
#-------------------------------------------------


QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = championDatabase
TEMPLATE = app

CONFIG += c++
SOURCES += main.cpp\
        mainwindow.cpp \
    champion.cpp

HEADERS  += mainwindow.h \
    champion.h

FORMS    += mainwindow.ui

QMAKE_LFLAGS += -static-libgcc -static-libstdc++
