#include "mainwindow.hxx"
#include <QApplication>
#include <QTextCodec>
#include "books.hxx"
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("New Concept");
    w.show();
    w.init();

//    Books book;
//    book.show();

    return a.exec();
}
