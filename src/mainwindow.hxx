#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include "ui_mainwindow.h"
#include "nce.hxx"
#include "classinfo.hxx"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Nce nce;
    void init();
public slots:
    void showInfo(int row,int col);
    void showRead();
private:
    Ui::MainWindow ui;
    ClassInfo classInfo_;
};

#endif // MAINWINDOW_HXX
