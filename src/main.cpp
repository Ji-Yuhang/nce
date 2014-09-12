#include "mainwindow.hxx"
#include <QApplication>
#include "books.hxx"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("New Concept");
    w.show();
    w.init();

    Books book;
    book.show();

    return a.exec();
}
