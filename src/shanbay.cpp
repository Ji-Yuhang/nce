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
#ifdef Q_OS_MAC
    QString path = QDir::currentPath() + "/../../../token.ini";
#else
    QString path = QDir::currentPath() + "/token.ini";
#endif
    QSettings settings(path, QSettings::IniFormat);
    token_ = settings.value("/token/token").toString();
    key_ = settings.value("/token/key").toString();
    secret_ = settings.value("/token/secret").toString();
    code_ = settings.value("/token/code").toString();
    redirect_uri_ = settings.value("/token/redirect_uri").toString();

    qDebug()<< path << token_;
//    token_ = "OakbBHYBD5BAbVyy3HjCEZrFDqkP1L";
    connect(webview_, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)) );
}

Shanbay::~Shanbay()
{
    QString path = QDir::currentPath() + "/token.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.setValue("/token/token",QVariant(token_));
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
}

void Shanbay::getToken()
{
    QString url = "https://api.shanbay.com/oauth2/token/";
    QtJson::JsonObject obj;
    QString key = key_;
    QString secret = secret_;
    QString tokenUrl = QString("https://api.shanbay.com/oauth2/authorize/?client_id=%1&response_type=token&redirect_uri=https://api.shanbay.com/oauth2/auth/success/").arg(key_);
    webview_->load(QUrl(tokenUrl));
    webview_->show();
}

void Shanbay::getWord(const QString & text)
{
    if (wordReply_) return;
    if (wordMap_.contains(text)) {
        emit wordFinished(text);
        QString audio = wordMap_[text].audio;
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
        return;
    }
 // https://api.shanbay.com/bdc/search/?word={word};
    QString url = QString("https://api.shanbay.com/bdc/search/?word=%1").arg(text);
    QNetworkRequest request;
    QString codeurl = "https://api.shanbay.com/oauth2/token/?client_id=a589ef972d26fa87d58b&client_secret=fdab01830d958dd4022e06611153839cab1c2cf2&grant_type=authorization_code&code=WllzU1ZtrMJNw1fyEEWI4LuEg9yTXN&redirect_uri=https://api.shanbay.com/oauth2/auth/success/";
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
    if(block.isEmpty()){
        qDebug()<<"read word return is empty";
        return;
    }
    bool success = false;
    QtJson::JsonObject obj =  QtJson::parse(block, success).toMap();
    if (!success) {
        qDebug()<<"Error!!! json pare Error!"<<block;
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
    QString path = QDir::currentPath();
#ifdef Q_OS_MAC
    path += "/../../../mp3/" + name;
#else
    path += "/mp3/" + name;
#endif
    file.setFileName(path);
    if (!file.open(QIODevice::WriteOnly)){
        qDebug() << "open file Error"<<name;
        return;
    }
    file.write(block);
    file.close();
    emit mp3Filnished(name);
    audioReply_->deleteLater();;
    audioReply_ = 0;

}

void Shanbay::addWord(const QString &text)
{
//    QString codeurl = "https://api.shanbay.com/oauth2/token/?client_id=a589ef972d26fa87d58b&client_secret=fdab01830d958dd4022e06611153839cab1c2cf2&grant_type=authorization_code&code=WllzU1ZtrMJNw1fyEEWI4LuEg9yTXN&redirect_uri=https://api.shanbay.com/oauth2/auth/success/";
//    QString codeurl1 = "https://api.shanbay.com/oauth2/token/?client_id=a589ef972d26fa87d58b";
    if (webview_->isVisible()) return;
    // https://api.shanbay.com/bdc/learning/
    QString url = "https://api.shanbay.com/bdc/learning/";
//    qDebug() << "get word url:"<<url;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QString tokenStr = QString("Bearer %1").arg(token_);
    request.setRawHeader("Authorization",tokenStr.toLatin1());
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setRawHeader("Cache-Control","no-store");
    request.setRawHeader("Pragma","no-cache");
    ShanbayWord word = wordInfo(text);
    QtJson::JsonObject obj;
    obj["id"] = word.id;
    obj["access_token"] = token_;
    obj["token_type"] = "Bearer";
    obj["expires_in"] = 2592000;
    QByteArray json = QtJson::serialize(obj);

    addReply_ =  netManager_.post(request,json);
    connect(addReply_, SIGNAL(finished()), this, SLOT(addReply()));

}

void Shanbay::addReply()
{
    QUrl url = addReply_->url();
    QByteArray block = addReply_->readAll();
    qDebug()<< "add word reply:"<<block;
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
    } else {

            getToken();

    }
}
