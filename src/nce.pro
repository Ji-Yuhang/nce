#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T17:36:12
#
#-------------------------------------------------

QT       += core gui
QT       += network
#QT       += phonon
QT       += sql
#QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += webkit
QT += webkitwidgets
#QTPLUGIN += QSQLMYSQL
TARGET = nce
TEMPLATE = app
DESTDIR = ../ncebin

macx {
    QMAKE_INFO_PLIST = Info.plist
}
unix {
TARGET = nce-linux
}

SOURCES += main.cpp\
        mainwindow.cpp \
    nce.cpp \
    data.cpp \
    classinfo.cpp \
    json.cpp \
    shanbay.cpp \
    database.cpp \
    article.cpp \
    books.cpp \
    articlewidget.cpp \
    unknownwordlistwidget.cpp \
    dictwidget.cpp
    netmanager.cpp

HEADERS  += mainwindow.hxx \
    nce.hxx \
    data.hxx \
    classinfo.hxx \
    json.h \
    shanbay.hxx \
    article.hxx \
    database.hxx \
    books.hxx \
    articlewidget.h \
    unknownwordlistwidget.hxx \
    dictwidget.hxx
    netmanager.h

FORMS    += mainwindow.ui \
    classinfo.ui \
    import.ui \
    wordinfo.ui \
    books.ui \
    sentence.ui \
    articlewidget.ui \
    unknownwordlistwidget.ui \
    dictwidget.ui

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    readme.md
