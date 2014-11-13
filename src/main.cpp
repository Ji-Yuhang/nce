#include "mainwindow.hxx"
#include <QApplication>
#include <QTextCodec>
#include "books.hxx"
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("New Concept");
    w.show();
    w.init();

//    Books book;
//    book.show();

    return a.exec();
}
