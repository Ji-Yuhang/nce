#include "mainwindow.hxx"
#include <QApplication>
#include <QDir>
#include <QTextCodec>
#include "books.hxx"
#include "articlewidget.h"
#include "database.hxx"
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
    QApplication a(argc, argv);
//    QString path = qApp->applicationDirPath();
//#ifdef Q_OS_MAC
//    path += "/../../..";
//#endif
//    QDir::setCurrent(path);
    Database db;
    MainWindow w;
    w.setWindowTitle("New Concept");
    w.show();
//    w.init();
    ArticleWidget aw;
    aw.show();

    return a.exec();
}
