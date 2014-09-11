#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T17:36:12
#
#-------------------------------------------------

QT       += core gui
QT       += network
#QT       += phonon
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += webkit
QT += webkitwidgets

TARGET = nce
TEMPLATE = app
DESTDIR = ../ncebin

QMAKE_INFO_PLIST = Info.plist
SOURCES += main.cpp\
        mainwindow.cpp \
    nce.cpp \
    data.cpp \
    classinfo.cpp \
    json.cpp \
    shanbay.cpp \
    database.cpp \
    article.cpp

HEADERS  += mainwindow.hxx \
    nce.hxx \
    data.hxx \
    classinfo.hxx \
    json.h \
    shanbay.hxx \
    article.hxx \
    database.hxx

FORMS    += mainwindow.ui \
    classinfo.ui \
    import.ui \
    wordinfo.ui

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    readme.md
