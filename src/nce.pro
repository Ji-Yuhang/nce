#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T17:36:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nce
TEMPLATE = app
DESTDIR = ../ncebin

SOURCES += main.cpp\
        mainwindow.cpp \
    nce.cpp \
    data.cpp \
    classinfo.cpp

HEADERS  += mainwindow.hxx \
    nce.hxx \
    data.hxx \
    classinfo.hxx

FORMS    += mainwindow.ui \
    classinfo.ui
