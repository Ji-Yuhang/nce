#include "mainwindow.hxx"
#include <QApplication>
#include "nce.hxx"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Nce nce;

    return a.exec();
}
