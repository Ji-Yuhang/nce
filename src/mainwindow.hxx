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
#include "dictwidget.hxx"
//#include <phonon>

#include "articlewidget.h"
#include "spell.h"
#include "ui_sentence.h"
#include "personwordwidget.h"
class UnknownWordListWidget;
class QWebView;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow* instancte() {return g_mainwindow_;}
    Nce nce;
    void init();
public slots:
    void showInfo(int row,int col);
    void showRead();
    void parseArticle();
    void import();
    void sentence();
    void parseSentence();
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
    void searchWord();
    void showUnknownList();
private slots:
    void on_pushButton_clicked();

private:
    static MainWindow* g_mainwindow_;
    Ui::MainWindow ui;
    ClassInfo classInfo_;
    ArticleWidget articleWidget_;
    QWidget import_;
    Ui::ImportUi importUi;
    QString path_;
    QNetworkAccessManager netManager_;
    QWebView* webview_;
    Shanbay * shanbay_;
    QPushButton *infoButton_;
    Ui::WordInfo wordui;
//    Phonon::MediaObject mediaObj_;
//    Phonon::AudioOutput output_;
//    Phonon::MediaSource source_;

    QString lastSelectWord_;
    QTextCursor lastTextCursor_;
    QWidget* sentence_;
    Ui::Sentence* sentenceUi_;
    UnknownWordListWidget* unknownWordListWidget_;
    DictWidget dictWidget_;
    Spell spell_;
    PersonWordWidget personWordWidget_;
};
class Parse
{
public:
    Parse();
    ~Parse();

};
#define MW MainWindow::instancte()
#endif // MAINWINDOW_HXX
