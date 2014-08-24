#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include "ui_mainwindow.h"
#include "nce.hxx"
#include "classinfo.hxx"
#include <QTextEdit>
#include "ui_import.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "shanbay.hxx"
#include "ui_wordinfo.h"
#include <phonon>
class QWebView;
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

    void authSuccess();
    void urlChanged(QUrl);
    void getToken();
    void getWord(const QString & text);
    void showWord(const QString & text);
    void playMp3(const QString & text);
    void addWord();
private:

    Ui::MainWindow ui;
    ClassInfo classInfo_;
    QWidget import_;
    Ui::ImportUi importUi;
    QString path_;
    QNetworkAccessManager netManager_;
    QWebView* webview_;
    Shanbay * shanbay_;
    QPushButton *infoButton_;
    Ui::WordInfo wordui;
    Phonon::MediaObject mediaObj_;
    Phonon::AudioOutput output_;
    Phonon::MediaSource source_;
};

#endif // MAINWINDOW_HXX
