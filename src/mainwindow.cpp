//#include <QWebView>

#include "mainwindow.hxx"
#include <QFileDialog>
#include <map>
#include <QDebug>
#include <QToolTip>
//#include <QWebView>
#include <QWebView>
#include "json.h"

//#include <QSound>
//#include <phonon>
#include <QTextCodec>
#include "article.hxx"
#include "database.hxx"
#include <QProcess>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "unknownwordlistwidget.hxx"

MainWindow* MainWindow::g_mainwindow_ = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  ,sentence_(new QWidget)
  ,sentenceUi_(new Ui::Sentence)
  ,unknownWordListWidget_(new UnknownWordListWidget)
{
    assert(!g_mainwindow_);
    g_mainwindow_ = this;
    ui.setupUi(this);
    importUi.setupUi(&import_);
//    import_.setStyleSheet();
    sentenceUi_->setupUi(sentence_);
    connect(sentenceUi_->parse, SIGNAL(clicked()), this, SLOT(parseSentence()));

    connect(ui.tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(showInfo(int,int)));
    connect(ui.read, SIGNAL(triggered()),this,SLOT(showRead()));
    connect(ui.importFile, SIGNAL(triggered()),this,SLOT(import()));
    connect(ui.parseArticle, SIGNAL(triggered()),this,SLOT(parseArticle()));

    connect(ui.actionSentence, SIGNAL(triggered()),this,SLOT(sentence()));
    connect(ui.actionUnknown_word_list, SIGNAL(triggered()),this,SLOT(showUnknownList()));


    connect(importUi.indent, SIGNAL(clicked()),this, SLOT(indent()));
    connect(importUi.textEdit, SIGNAL(selectionChanged()),this ,SLOT(selectedWord()));
    connect(&netManager_, SIGNAL(finished(QNetworkReply*)),this, SLOT(readReply(QNetworkReply*)));
    webview_ = new QWebView;

    // app key a589ef972d26fa87d58b
    // app secret fdab01830d958dd4022e06611153839cab1c2cf2
    QString key = "c939b9b845440f2e1334";
    QString secret = "05c4df6894ff18cc16f9e4b8c88fcdb4a5557c19";
    QString url = QString("https://api.shanbay.com/oauth2/authorize/?client_id=%1&response_type=%2&state=%3").arg(key).arg("code").arg(123);

//    webview_->load(QUrl(url));
//    webview_->show();
    connect(webview_, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)) );
    shanbay_ = new Shanbay;
    connect(shanbay_, SIGNAL(wordFinished(QString)), this, SLOT(showWord(QString)));
    connect(shanbay_, SIGNAL(mp3Filnished(QString)), this, SLOT(playMp3(QString)));
    infoButton_ = new QPushButton;
    infoButton_->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);


    wordui.setupUi(infoButton_);

    connect(infoButton_, SIGNAL(clicked()), infoButton_, SLOT(close()));
    connect(wordui.add, SIGNAL(clicked()), this, SLOT(addWord()));
    connect(ui.word, SIGNAL(triggered()), this, SLOT(searchWord()));
//    Phonon::createPath(&mediaObj_, &output_);
}
MainWindow::~MainWindow()
{
    delete sentence_;
    delete sentenceUi_;
    delete unknownWordListWidget_;
}

void MainWindow::init() // initilaize
{
    typedef QMultiMap<QString, NceWordInfo> WordList;
    QStringList list;
    typedef QMap<QString,int> ValueMap;
    ValueMap vm;
    WordList& wl = nce.data_.wordList_;
    WordList::iterator it = wl.begin(), iE = wl.end();
    for (; it != iE; ++it) {
        QString w = it.key();
        ValueMap::iterator vit =  vm.find(w);
        if (vit != vm.end())
            vit.value()++;
        else
            vm.insert(w,0);
    }
    typedef std::multimap<int, QString> MapValue;
    MapValue mv;
    ValueMap::iterator vit = vm.begin(), viE = vm.end();
    for (; vit != viE; ++vit) {
        int value = vit.value();
        mv.insert(std::make_pair(value, vit.key()));
    }
    int _vmSize = vm.size();
    ui.tableWidget->setRowCount(_vmSize);
    int row = 0;
    MapValue::reverse_iterator mmit = mv.rbegin(), mmie = mv.rend();
    for (; mmit != mmie; ++mmit) {
        QTableWidgetItem * item0 = new QTableWidgetItem;
        item0->setText(QString::number(mmit->first));
        ui.tableWidget->setItem(row, 0, item0);

        QTableWidgetItem * item1 = new QTableWidgetItem;
        item1->setText(mmit->second);
        ui.tableWidget->setItem(row, 1, item1);

        ++row;
    }
    ui.tableWidget->resizeColumnsToContents();
    ui.tableWidget->setColumnWidth(1,150);

//    classInfo_.init();
}

void MainWindow::showInfo(int row,int col)
{
    QString word = ui.tableWidget->item(row,1)->text();
    WordList::iterator it =  nce.data_.wordList_.find(word);
    if (it == nce.data_.wordList_.end())
        return;
    NceWordInfo info = it.value();
    QString text;
    text += info.index.nce + " " + QString::number(info.index.class_) + ":\n";
    foreach (QString s, info.sentences) {
        text += "\t"+s +"\n";
    }
    ui.plainTextEdit->setPlainText(text);
}

void MainWindow::showRead()
{
    classInfo_.showNormal();
}

void MainWindow::parseArticle()
{
  articleWidget_.showNormal();
}

void MainWindow::import()
{
    path_ = QFileDialog::getOpenFileName();
    if (path_.isEmpty()) return;
    QFile file;
    file.setFileName(path_);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Read File Error!"+ path_;
        return ;
    }
    QTextStream stream(&file);
    stream.setCodec(QTextCodec::codecForName("GBK"));
    QString content = stream.readAll();
    file.close();

    content.replace("\uA3AC", ",");
    content.replace("\uA3AE", ".");
//    content.replace("？", "?");
//    content.replace("！", "!");
//    content.replace("！", "!");
//    content.replace("－", "-");
    content.insert(0,"<html><head><style type=\"text/css\">body{line-height:140%;word-spacing: 3px; font-family:Georgia,Times,\"Times New Roman\",Arial,serif ;font-size:20px;}</style></head><body>");
    content.append("</body></html>");
//    importUi.textEdit->setPlainText(content);
    importUi.textEdit->setHtml(content);
    import_.setWindowTitle(path_);
    import_.showNormal();

}

void MainWindow::sentence()
{
    sentence_->showNormal();
}

void MainWindow::parseSentence()
{

    QString text = sentenceUi_->textEdit->toPlainText();
    qDebug() << text<<endl;
    QStringList words;
    words = text.split(QRegExp("\\W+"),QString::SkipEmptyParts);
    QTableWidget* table = sentenceUi_->tableWidget;
    table->clearContents();
    table->clear();
    table->setColumnCount(words.size());
    table->setRowCount(3);
    int col = 0;
    QStringList vList;
    foreach (QString w, words) {
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText(w);
        table->setItem(0,col,item);

        QProcess process;
        QString program = "I:/qtworkspace/build-dict-Desktop_Qt_5_3_0_MinGW_32bit-Release/release/dict.exe";
        QStringList argument;
        argument << w;
        process.start(program,argument);
        QString cn;
        if (process.waitForFinished(3000))
        {
            QByteArray block = process.readAllStandardOutput();

            qDebug() << block<<endl;
            cn = block;
            if (cn.contains("v.") || cn.contains("vt."))
                vList.append(w);
        } else {
            qDebug() << "process fail"<<endl;
        }

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(cn);
        table->setItem(1,col,item2);


        col++;
    }
    table->setShowGrid(false);
    table->adjustSize();
    table->resizeColumnsToContents();

    QString html = text;
    foreach (QString w, vList) {
        html.replace(w,"<font color=\"red\">" + w + "</font>");
    }
    sentenceUi_->textEdit->setHtml(html);
}


void MainWindow::indent()
{
    QString content = importUi.textEdit->toPlainText();
    content.replace("-\r\n", "");
    content.replace("-\n", "");
    content.replace("\r\n"," ");
    content.replace("\n", "");
    content.replace("- ", "-");
    content.replace("- ", "-");
    QStringList sentenceList = content.split(QRegExp("[\\.!\\?]"),QString::SkipEmptyParts);
    int i = 0;
    for (int i = 0; i < sentenceList.size(); ++i)
        sentenceList[i].trimmed();

    QString newString = sentenceList.join(".\n");
    importUi.textEdit->setPlainText(newString);
    /*
    QFile file;
    file.setFileName(path_);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Read File Error!"+ path_;
        return ;
    }

    file.write(newString.toLatin1());
    file.close();
    */
}

void MainWindow::selectedWord()
{
    if (infoButton_->isVisible()) return;
    QTextCursor cursor =  importUi.textEdit->textCursor();
    QString text = cursor.selectedText();

    int pos = cursor.position();
    int posInBlock = cursor.positionInBlock();
    qDebug()<< pos << posInBlock;
    if (!lastTextCursor_.isNull()) {
        int lastpos = lastTextCursor_.position();
        int diffPos = qAbs(lastpos - pos);
        if (diffPos == 0) return;
        else if (diffPos == 1) {
            QString lastSelect = lastTextCursor_.selectedText();
            if (lastSelect == text) return;
        }
    }

    text.trimmed();
    if (text.isEmpty()) return;
//    if (text.contains(QRegExp("\s"))) return;
    if (text.contains(QRegExp("[^A-Za-z]"))) return;
    if (text == lastSelectWord_) return;
    qDebug() << "selected text: "<<text;
    QPoint p = QCursor::pos();
    getWordDescription(text);
    lastSelectWord_ = text;
    lastTextCursor_ = cursor;

}

void MainWindow::getWordDescription(const QString &text)
{

//    getToken();
    getWord(text);

}

void MainWindow::showDescription()
{

}

void MainWindow::readReply(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QUrl redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    QString urlStr = url.toString();
    QString urlRedirectStr = redirect.toString();
    QByteArray block = reply->readAll();
    if (redirect.isValid())
        netManager_.get(QNetworkRequest(QUrl(redirect)));


    QString ss = block;

    bool success = false;
    QtJson::JsonObject obj =  QtJson::parse(ss, success).toMap();
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
    int i = ss.size();
    i++;
}

void MainWindow::authSuccess()
{

}

void MainWindow::urlChanged(QUrl url)
{
    QString urlStr = url.toString();
    qDebug()<<"Url changed:"<< urlStr;
    //code = TuqHGUy5jM4HxA369iihI8bC8tYJtA
}

void MainWindow::getToken()
{
    QString url = "https://api.shanbay.com/oauth2/token/";
    QtJson::JsonObject obj;
    QString key = "c939b9b845440f2e1334";
    QString secret = "05c4df6894ff18cc16f9e4b8c88fcdb4a5557c19";
//https://api.shanbay.com/oauth2/authorize/?client_id=c939b9b845440f2e1334&response_type=token&redirect_uri=https://api.shanbay.com/oauth2/auth/success/
    https://api.shanbay.com/oauth2/auth/success/#access_token=OakbBHYBD5BAbVyy3HjCEZrFDqkP1L&token_type=Bearer&state=&expires_in=2592000&scope=read+write

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

void MainWindow::getWord(const QString & text)
{
    shanbay_->asyncGetWord(text);
    /*
 // https://api.shanbay.com/bdc/search/?word={word};
    QString url = QString("https://api.shanbay.com/bdc/search/?word=%1").arg(text);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("Authorization","Bearer OakbBHYBD5BAbVyy3HjCEZrFDqkP1L");
    netManager_.get(request);
    */
}
void setText(QWidget * w, const QString& name, const QString& text)
{
    QLabel* label =  w->findChild<QLabel*>(name);
    if (label) {
        label->setText(text);
    }
}
void MainWindow::showWord(const QString &text)
{
    infoButton_->close();
    QPoint point = QCursor::pos();
    point.ry() += 10;
    infoButton_->move(point);
    ShanbayWord wordInfo = shanbay_->wordInfo(text);

//    connect(ui.uk, SIGNAL(clicked()), w, SLOT(close()));
//    connect(w, SIGNAL(clicked()), w, SLOT(close()));
    setText(infoButton_, "word", wordInfo.content);
    QString yinbiao = wordInfo.pronunciation;
    yinbiao.insert(0,"<font face='Arial'>[");
    yinbiao.append("]</font>");
    setText(infoButton_, "yinbiao", yinbiao);
    QString definition = wordInfo.definition;
    definition.insert(0,"<p>");
    definition.append("</p>");
    setText(infoButton_, "cn", wordInfo.definition);

    //QSound::play(wordInfo.audio);
//    setText(w, "word", wordInfo.content);
//    setText(w, "word", wordInfo.content);
//    if (lastWidget) lastWidget->close();
    infoButton_->showNormal();
    //    lastWidget = w;
}

void MainWindow::playMp3(const QString &text)
{
#ifdef Q_OS_MAC
    QString path = QDir::currentPath() + "/../../..";
#else
    QString path = QDir::currentPath();
#endif
    QString soucrePath = path +"/mp3/"+ text;
//    Phonon::MediaSource source(soucrePath);
//    mediaObj_.setCurrentSource(source);
//    mediaObj_.play();

    QString command = QString("/usr/local/bin/mplayer ") + soucrePath ;//+ QString(" > /dev/null");
//    system(command.toUtf8().data());
    popen(command.toUtf8().data(), "r");

}

void MainWindow::addWord()
{
    QString word = wordui.word->text();
    shanbay_->addWord(word);
}

void MainWindow::searchWord()
{
    dictWidget_.show();
    dictWidget_.activateWindow();
}

void MainWindow::showUnknownList()
{
    unknownWordListWidget_->show();
    unknownWordListWidget_->activateWindow();
    unknownWordListWidget_->getUnknownWord();

}
