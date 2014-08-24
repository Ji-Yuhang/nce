#include "shanbay.hxx"
#include "json.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QSound>
#include <QTemporaryFile>
#include <QSettings>
Shanbay::Shanbay(QObject *parent) :
    QObject(parent),
    webview_(0),
    wordReply_(0),
    audioReply_(0),
    addReply_(0)
{
//    connect(&netManager_, SIGNAL(finished(QNetworkReply*)),this, SLOT(readReply(QNetworkReply*)));
    webview_ = new QWebView;
    // old app key a589ef972d26fa87d58b
    // old app secret fdab01830d958dd4022e06611153839cab1c2cf2
    key_ = "c939b9b845440f2e1334";
    secret_ = "05c4df6894ff18cc16f9e4b8c88fcdb4a5557c19";

    QString path = QDir::currentPath() + "/token.ini";
    QSettings settings(path, QSettings::IniFormat);
    token_ = settings.value("/token/token").toString();
    key_ = settings.value("/token/key").toString();
    secret_ = settings.value("/token/secret").toString();
    QString portStr = settings.value("/server/port").toString();
    long long int portLong = portStr.toLongLong();


    token_ = "OakbBHYBD5BAbVyy3HjCEZrFDqkP1L";

    //QString url = QString("https://api.shanbay.com/oauth2/authorize/?client_id=%1&response_type=%2&state=%3").arg(key_).arg("code").arg(123);

//    webview_->load(QUrl(url));
//    webview_->show();
    connect(webview_, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)) );
}

Shanbay::~Shanbay()
{
    delete webview_;
}

ShanbayWord Shanbay::wordInfo(const QString &word)
{
    QMap<QString, ShanbayWord>::iterator it = wordMap_.find(word);
    if (it != wordMap_.end())
        return it.value();
    else
        return ShanbayWord();
}


void Shanbay::readReply(QNetworkReply *reply)
{
    if (reply == wordReply_) {

        QByteArray block = reply->readAll();
        bool success = false;
        QtJson::JsonObject obj =  QtJson::parse(block, success).toMap();
        QVariant token;
        QVariant type;
        QVariant expire;
        QVariant refresh;
        QVariant scope;
        QVariant msg;
        QVariant data;
        QVariantMap dataMap;
        QVariantMap en_defitions;
        QVariantMap cn_definition;
        QString id;
        QString retention;
        QString definition;
        QString target_retention;
        QVariantMap en_definition;
        QString learning_id;
        QString content;
        QString pronunciation;
        QString audio;
        QString uk_audio;
        QString us_audio;

        if (obj.contains("access_token")) token = obj["access_token"];
        if (obj.contains("token_type")) type = obj["token_type"];
        if (obj.contains("expires_in")) expire = obj["expires_in"];
        if (obj.contains("refresh_token")) refresh = obj["refresh_token"];
        if (obj.contains("scope")) scope = obj["scope"];
        if (obj.contains("msg")) msg = obj["msg"];
        if (obj.contains("data")) data = obj["data"]; {
            dataMap = data.toMap();
            en_defitions = dataMap["en_defitions"].toMap();
            cn_definition = dataMap["cn_definition"].toMap();
            id = dataMap["id"].toString();
            retention = dataMap["retention"].toString();
            definition = dataMap["definition"].toString();
            target_retention = dataMap["target_retention"].toString();
            en_definition = dataMap["en_definition"].toMap();
            learning_id = dataMap["learning_id"].toString();
            content = dataMap["content"].toString();
            pronunciation = dataMap["pronunciation"].toString();
            audio = dataMap["audio"].toString();
            uk_audio = dataMap["uk_audio"].toString();
            us_audio = dataMap["us_audio"].toString();
        }

        qDebug() << block;
    }
    QUrl url = reply->url();
    QUrl redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    QString urlStr = url.toString();
    QString urlRedirectStr = redirect.toString();
    //    if (redirect.isValid())
    //        netManager_.get(QNetworkRequest(QUrl(redirect)));


}


void Shanbay::authSuccess()
{

}

void Shanbay::urlChanged(QUrl url)
{
    QString urlStr = url.toString();
    qDebug()<<"Url changed:"<< urlStr;
    int index = urlStr.lastIndexOf("#");
    if (index != -1) {
        QString tokenStr = urlStr.mid(index+1);
        int index2 = tokenStr.indexOf("=");
        int index3 = tokenStr.indexOf("&");
        if (index2 != -1 && index3 != -1) {
            token_ = tokenStr.mid(index2 +1,index3 - index2 - 1);
        } else if (index2 != -1 && index3 == -1) {
            token_ = tokenStr.mid(index2 +1);
        }
    }

    //code = TuqHGUy5jM4HxA369iihI8bC8tYJtA
}

void Shanbay::getToken()
{

    QString url = "https://api.shanbay.com/oauth2/token/";
    QtJson::JsonObject obj;
    QString key = "c939b9b845440f2e1334";
    QString secret = "05c4df6894ff18cc16f9e4b8c88fcdb4a5557c19";
    QString tokenUrl = "https://api.shanbay.com/oauth2/authorize/?client_id=c939b9b845440f2e1334&response_type=token&redirect_uri=https://api.shanbay.com/oauth2/auth/success/";
    //https://api.shanbay.com/oauth2/auth/success/#access_token=OakbBHYBD5BAbVyy3HjCEZrFDqkP1L&token_type=Bearer&state=&expires_in=2592000&scope=read+write
    webview_->load(QUrl(tokenUrl));
    webview_->show();
    QString access_token = "OakbBHYBD5BAbVyy3HjCEZrFDqkP1L";
    QString tokenType = "Bearer";
    QString expires_in = "2592000";
    QString scope = "read+write";
    obj["client_id"] = key;
    obj["client_secret"] = secret;
    obj["grant_type"] = "authorization-code";
    obj["code"] = "TuqHGUy5jM4HxA369iihI8bC8tYJtA";
    obj["redirect_uri"] = "https://api.shanbay.com/oauth2/auth/success/";

    QByteArray data = QtJson::serialize(obj);
//    netManager_.post(QNetworkRequest(QUrl(url)), data);

    // https://api.shanbay.com/oauth2/authorize/?client_id=c939b9b845440f2e1334&response_type=token&redirect_uri=https://api.shanbay.com/oauth2/auth/success/
}

void Shanbay::getWord(const QString & text)
{
    if (wordMap_.contains(text)) {
        emit wordFinished(text);
        return;
    }
 // https://api.shanbay.com/bdc/search/?word={word};
    QString url = QString("https://api.shanbay.com/bdc/search/?word=%1").arg(text);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QString tokenStr = QString("Bearer %1").arg(token_);
    request.setRawHeader("Authorization",tokenStr.toLatin1());
    wordReply_ =  netManager_.get(request);
    connect(wordReply_, SIGNAL(finished()), this, SLOT(readWord()));
}

void Shanbay::readWord()
{
    ShanbayWord word;
    QByteArray block = wordReply_->readAll();
    bool success = false;
    QtJson::JsonObject obj =  QtJson::parse(block, success).toMap();
    if (!success) {
        QMessageBox::critical(0,"json error",block);
        return;
    }
    word.status_code = obj["status_code"].toString();
    word.msg = obj["msg"].toString();
    word.data = obj["data"].toMap();
    QMap<QString, QVariant> &dataMap = word.data;
    word.en_definitions = dataMap["en_definitions"].toMap();
    word.cn_definition = dataMap["cn_definition"].toMap();
    word.id = dataMap["id"].toString();
    word.retention = dataMap["retention"].toInt();
    word.definition = dataMap["definition"].toString();
    word.target_retention = dataMap["target_retention"].toString();
    word.en_definition = dataMap["en_definition"].toMap();
    word.learning_id = dataMap["learning_id"].toString();
    word.content = dataMap["content"].toString();
    word.pronunciation = dataMap["pronunciation"].toString();
    word.audio = dataMap["audio"].toString();
    word.uk_audio = dataMap["uk_audio"].toString();
    word.us_audio = dataMap["us_audio"].toString();
    QVariant token;
    QVariant type;
    QVariant expire;
    QVariant refresh;
    QVariant scope;
    QVariant msg;
    QVariant data;
    QVariantMap dataMap1;
    QVariantMap en_defitions;
    QVariantMap cn_definition;
    QString id;
    QString retention;
    QString definition;
    QString target_retention;
    QVariantMap en_definition;
    QString learning_id;
    QString content;
    QString pronunciation;
    QString audio;
    QString uk_audio;
    QString us_audio;

    if (obj.contains("access_token")) token = obj["access_token"];
    if (obj.contains("token_type")) type = obj["token_type"];
    if (obj.contains("expires_in")) expire = obj["expires_in"];
    if (obj.contains("refresh_token")) refresh = obj["refresh_token"];
    if (obj.contains("scope")) scope = obj["scope"];
    if (obj.contains("msg")) msg = obj["msg"];
    if (obj.contains("data")) data = obj["data"]; {
        QVariantMap dataMap;
        dataMap = data.toMap();
        en_defitions = dataMap["en_defitions"].toMap();
        cn_definition = dataMap["cn_definition"].toMap();
        id = dataMap["id"].toString();
        retention = dataMap["retention"].toString();
        definition = dataMap["definition"].toString();
        target_retention = dataMap["target_retention"].toString();
        en_definition = dataMap["en_definition"].toMap();
        learning_id = dataMap["learning_id"].toString();
        content = dataMap["content"].toString();
        pronunciation = dataMap["pronunciation"].toString();
        audio = dataMap["audio"].toString();
        uk_audio = dataMap["uk_audio"].toString();
        us_audio = dataMap["us_audio"].toString();
    }
    wordMap_.insert(word.content, word);

    emit wordFinished(word.content);
    {
        int index = audio.lastIndexOf("/");
        QString name = audio.mid(index + 1);
        QString path = QDir::currentPath()+"/mp3/"+name;
        QFileInfo fileInfo;
        fileInfo.setFile(path);
        if (fileInfo.exists())
            emit mp3Filnished(name);
        else {
            audioReply_ = netManager_.get(QNetworkRequest(QUrl(audio)));
            connect(audioReply_, SIGNAL(finished()), this, SLOT(readMp3()));
        }
    }
    qDebug() << block;
    wordReply_->deleteLater();
    wordReply_ = 0;
}

void Shanbay::readMp3()
{
    QUrl url = audioReply_->url();
    QString urlString = url.toString();
    int index = urlString.lastIndexOf("/");
    QString name = urlString.mid(index + 1);


    QByteArray block = audioReply_->readAll();
    QFile file;
    QString path = QDir::currentPath()+"/mp3/"+name;
    file.setFileName(path);
    if (!file.open(QIODevice::WriteOnly)){
        qDebug() << "open file Error"<<name;
        return;
    }
    file.write(block);
    file.close();
    emit mp3Filnished(name);

    qDebug() <<"current dir"<<QDir::currentPath()<< "mp3 file paht"<<path;
//    QSound::play(QDir::currentPath()+"/"+path);
    audioReply_->deleteLater();;
    audioReply_ = 0;

}

void Shanbay::addWord(const QString &text)
{
    static bool flag = true;
    if (flag) {
        getToken();
        flag = false;
    }
    if (webview_->isVisible()) return;
    // https://api.shanbay.com/bdc/learning/
    QString url = "https://api.shanbay.com/bdc/learning/";
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QString tokenStr = QString("Bearer %1").arg(token_);
    request.setRawHeader("Authorization",tokenStr.toLatin1());
    ShanbayWord word = wordInfo(text);
    QtJson::JsonObject obj;
    obj["id"] = word.id;
    QByteArray json = QtJson::serialize(obj);

    webview_->load(request,QNetworkAccessManager::PostOperation, json);
    webview_->show();
//    addReply_ =  netManager_.post(request,json);
//    connect(addReply_, SIGNAL(finished()), this, SLOT(addReply()));

}

void Shanbay::addReply()
{
    QUrl url = addReply_->url();
    QByteArray block = addReply_->readAll();
    bool success = false;
    QtJson::JsonObject obj =  QtJson::parse(block,success).toMap();
    QString msg = obj["msg"].toString();
    if (msg == "UNAUTHORIZED") {
        getToken();
        QMessageBox::critical(0,"msg UNAUTHORIZED","UNAUTHORIZED token");
        return;
    }
    QString status_code = obj["status_code"].toString();
    QVariantMap data = obj["data"].toMap();
    QString id = data["id"].toString();
    long long lid = data["id"].toLongLong();
    if (msg == "SUCCESS"){
        QMessageBox::information(0,"add word success",QString(" %1 learning id %2").arg("todo").arg(id));
    }
}
