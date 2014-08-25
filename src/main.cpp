#include "mainwindow.hxx"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("New Concept");
    w.show();
    w.init();


    return a.exec();
}
