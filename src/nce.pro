#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T17:36:12
#
#-------------------------------------------------

QT       += core gui
QT       += network
#QT       += phonon
QT       += sql
QT       += multimedia
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
    dictwidget.cpp \
    localdatabase.cpp \
    hunspell/affentry.cxx \
    hunspell/affixmgr.cxx \
    hunspell/csutil.cxx \
    hunspell/dictmgr.cxx \
    hunspell/filemgr.cxx \
    hunspell/hashmgr.cxx \
    hunspell/hunspell.cxx \
    hunspell/hunzip.cxx \
    hunspell/phonet.cxx \
    hunspell/replist.cxx \
    hunspell/suggestmgr.cxx \
    hunspell/utf_info.cxx \
    spell.cpp \
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
    dictwidget.hxx \
    localdatabase.h \
    hunspell/affentry.hxx \
    hunspell/affixmgr.hxx \
    hunspell/atypes.hxx \
    hunspell/baseaffix.hxx \
    hunspell/csutil.hxx \
    hunspell/dictmgr.hxx \
    hunspell/filemgr.hxx \
    hunspell/hashmgr.hxx \
    hunspell/htypes.hxx \
    hunspell/hunspell.h \
    hunspell/hunspell.hxx \
    hunspell/hunvisapi.h \
    hunspell/hunzip.hxx \
    hunspell/langnum.hxx \
    hunspell/phonet.hxx \
    hunspell/replist.hxx \
    hunspell/suggestmgr.hxx \
    hunspell/w_char.hxx \
    spell.h \
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

DISTFILES += \
    hunspell/license.hunspell \
    hunspell/README
