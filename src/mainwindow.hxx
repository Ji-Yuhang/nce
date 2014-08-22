#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include "ui_mainwindow.h"
#include "nce.hxx"
#include "classinfo.hxx"
#include <QTextEdit>
#include "ui_import.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
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
    void import();
    void indent();
    void selectedWord();
    void getWordDescription(const QString & text);
    void showDescription();
    void readReply(QNetworkReply*);
private:
    Ui::MainWindow ui;
    ClassInfo classInfo_;
    QWidget import_;
    Ui::ImportUi importUi;
    QString path_;
    QNetworkAccessManager netManager_;
};

#endif // MAINWINDOW_HXX
