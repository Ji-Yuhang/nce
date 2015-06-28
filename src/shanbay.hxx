#ifndef SHANBAY_HXX
#define SHANBAY_HXX

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWebView>
#include <QNetworkReply>
struct ShanbayWord {
    QString status_code;
    QString msg;
    QMap<QString, QVariant> data;

    // data:
    QMap<QString, QVariant> en_definitions;
    QMap<QString, QVariant> cn_definition;
    QString id;
    QString retention;
    QString definition;
    QString target_retention;
    QMap<QString, QVariant> en_definition;
    QString learning_id;
    QString content;
    QString pronunciation;
    QString audio;
    QString uk_audio;
    QString us_audio;
};
class Shanbay : public QObject
{
    Q_OBJECT
public:
    explicit Shanbay(QObject *parent = 0);
    ~Shanbay();
    ShanbayWord wordInfo(const QString&);
    static Shanbay* instance(){return g_single_shabay_;}
protected:
    QNetworkAccessManager netManager_;
    QWebView* webview_;
    QNetworkReply* wordReply_;
    QNetworkReply* audioReply_;
    QNetworkReply* addReply_;
    QMap<QString, ShanbayWord> wordMap_;

private:
    QString key_;
    QString secret_;
    QString token_;
    QString code_;
    QString redirect_uri_;

    static Shanbay* g_single_shabay_;
private:
    void saveTaken();
signals:
    void wordFinished(QString);
    void mp3Filnished(QString);

public slots:

    void readReply(QNetworkReply*);

    void authSuccess();
    void urlChanged(QUrl);
    void getToken();
    void asyncGetWord(const QString & text);
    void readWord();
    void readMp3();
    void addWord(const QString & text);
    void addReply();

};
#define SHANBAY Shanbay::instance()
#endif // SHANBAY_HXX
