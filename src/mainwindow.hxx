#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private:
    Ui::MainWindow ui;
};

#endif // MAINWINDOW_HXX
