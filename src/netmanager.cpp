#include "netmanager.h"
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "json.h"
NetManager* NetManager::g_single_net_manager_ = 0;
NetManager::NetManager(QObject *parent) : QObject(parent)
{
    Q_ASSERT(!g_single_net_manager_);
    g_single_net_manager_ = this;
}

NetManager::~NetManager()
{
}

WordInfo NetManager::wordInfo(int word_id)
{
    WordInfo info;
    QUrl url = QString("http://0.0.0.0:3000/word?word_id=%1").arg(word_id);
    QNetworkRequest request(url);
    QNetworkReply* re = manager_.get(request);
    QEventLoop loop;
    connect(re,SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

//    if (re->bytesAvailable()) {
        QString all = re->readAll();
        qDebug() << "wordinfo of "<<word_id <<" reply : "<<all;
        bool ok = false;
        QtJson::JsonObject obj =  QtJson::parse(all,ok).toMap();
        if (ok) {
            info.word_id = obj["word_id"].toInt();
            info.word = obj["content"].toString();
            if (obj.contains("familiarity"))
                info.familiarity = obj["familiarity"].toInt();
        }
//    }
    return info;

}

WordInfo NetManager::wordInfo(const QString &word)
{
    WordInfo info;
    QUrl url = QString("http://0.0.0.0:3000/word?word=%1").arg(word);
    QNetworkRequest request(url);
    QNetworkReply* re = manager_.get(request);
    QEventLoop loop;
    connect(re,SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
//    if (re->bytesAvailable()) {
        QString all = re->readAll();
        qDebug() << "wordinfo of "<<word <<" reply : "<<all;

        bool ok = false;
        QtJson::JsonObject obj =  QtJson::parse(all,ok).toMap();
        if (ok) {
            info.word_id = obj["word_id"].toInt();
            info.word = obj["content"].toString();
            if (obj.contains("familiarity"))
                info.familiarity = obj["familiarity"].toInt();
//            info.familiarity = obj["familiarity"].toInt();
        }
//    }
    return info;
}

WordInfo NetManager::insertWord(const QString &word)
{
    WordInfo info;
    QUrl url = QString("http://0.0.0.0:3000/insertword?word=%1").arg(word);
    QNetworkRequest request(url);
    QNetworkReply* re = manager_.get(request);
    QEventLoop loop;
    connect(re,SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

//    if (re->bytesAvailable()) {
        QString all = re->readAll();
        qDebug() << "insertWord of "<<word <<" reply : "<<all;

        bool ok = false;
        QtJson::JsonObject obj =  QtJson::parse(all,ok).toMap();
        if (ok) {
            info.word_id = obj["word_id"].toInt();
            info.word = obj["content"].toString();
            if (obj.contains("familiarity"))
                info.familiarity = obj["familiarity"].toInt();
        }
//    }
    return info;
}

WordInfo NetManager::insertFamiliarity(int word_id)
{
    WordInfo info;
    QUrl url = QString("http://0.0.0.0:3000/insertfamiliarity?word_id=%1").arg(word_id);
    QNetworkRequest request(url);
    QNetworkReply* re = manager_.get(request);
    QEventLoop loop;
    connect(re,SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

//    if (re->bytesAvailable()) {
        QString all = re->readAll();
        qDebug() << "insertFamiliarity of "<<word_id <<" reply : "<<all;

        bool ok = false;
        QtJson::JsonObject obj =  QtJson::parse(all,ok).toMap();
        if (ok) {
            info.word_id = obj["word_id"].toInt();
//            info.word = obj["content"].toString();
            if (obj.contains("familiarity"))
                info.familiarity = obj["familiarity"].toInt();
        }
//    }
    return info;
}

WordInfo NetManager::setWordFamiliarity(int word_id, int familiarity)
{
    WordInfo info;
    QUrl url = QString("http://0.0.0.0:3000/updatefamiliarity?word_id=%1&familiarity=%2").arg(word_id).arg(familiarity);
    QNetworkRequest request(url);
    QNetworkReply* re = manager_.get(request);
    QEventLoop loop;
    connect(re,SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

//    if (re->bytesAvailable()) {
        QString all = re->readAll();
        qDebug() << "setWordFamiliarity of "<<word_id <<" reply : "<<all;

        bool ok = false;
        QtJson::JsonObject obj =  QtJson::parse(all,ok).toMap();
        if (ok) {
            info.word_id = obj["word_id"].toInt();
//            info.word = obj["content"].toString();
            if (obj.contains("familiarity"))
                info.familiarity = obj["familiarity"].toInt();
        }
//    }
        return info;
}

QList<WordInfo> NetManager::allUnknown()
{
    QList<WordInfo> infolist;
    QUrl url = QString("http://0.0.0.0:3000/allunknown");
    QNetworkRequest request(url);
    QNetworkReply* re = manager_.get(request);
    QEventLoop loop;
    connect(re,SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
//    if (re->bytesAvailable()) {
        QString all = re->readAll();
        qDebug() << "allUnknown of ";
        bool ok = false;
        QtJson::JsonArray obj =  QtJson::parse(all,ok).toList();
        if (ok) {
            Q_FOREACH(QVariant v, obj) {
                WordInfo info;

                QtJson::JsonObject one = v.toMap();
                info.word_id = one["word_id"].toInt();
                info.word = one["content"].toString();
                if (obj.contains("familiarity"))
                    info.familiarity = one["familiarity"].toInt();
                infolist.append(info);
            }


        }
//    }
        return infolist;
}

