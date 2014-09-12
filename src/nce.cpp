#include "nce.hxx"
#include <QApplication>
#include <QFileInfo>
#include <QStringList>
#include <QDebug>
#include <QRegExp>
#include <QProgressDialog>
#include <QMessagebox>

QString simpleChange(const QString& text)
{
    QString temp = text;

    temp.replace("\r\n"," ");
    temp.replace("\n", " ");
    temp.replace("- ", "-");
    temp.replace("- ", "-");
    return temp;
}
Nce::Nce(QObject *parent) :
    QObject(parent)
{
    QStringList nces;
    nces << "nce1" << "nce2" << "nce3"<<"nce4";
    for (int i = 0; i < 4; ++i) {
        QString nce = nces[i];
        for (int j = 1; j < 100; ++j) {
            parseFile(nce, j);
            //replaceFile(nce, j);
        }
    }
    //replaceFile("nce3", 1);
    //QMessageBox::information(0,"ok","replace completed!");
    //parseWord();
}

bool Nce::parseFile(const QString &nce, int _class)
{
    QString path = qApp->applicationDirPath();
#ifdef Q_OS_MAC
    path += "/../../..";
#endif
    path += "/nce/";
    path += nce + "/";
    QString classStr = QString::number(_class);
    if (_class < 10) classStr = "0" + QString::number(_class);
    path += classStr;
    QFileInfo fileInfo(path + ".txt");
    if (!fileInfo.exists())
        path += ".TXT";
    else
        path += ".txt";
    file_.setFileName(path);
    if (!file_.open(QIODevice::ReadOnly)) {
        qDebug() << "Read File Error!"+ path;
        return false;
    }
    QString text = file_.readAll();
    if (file_.isOpen())
        file_.close();
    text = simpleChange(text);

    QStringList sentenceList = text.split(QRegExp("[\\.!\\?]"),QString::SkipEmptyParts);
    int sentenceSize = sentenceList.size();

    ClassIndex index;
    index.nce = nce;
    index.class_ = _class;
    data_.classContent_.insert(index,text);
    WordMap wordMap;
    foreach (QString sentence, sentenceList) {
        QStringList wordList;
        wordList = sentence.split(QRegExp("\\W+"), QString::SkipEmptyParts);
        WordInfo wordInfo;
        wordInfo.index = index;
//        wordInfo.sentences.push_back(sentence);
        foreach (QString w, wordList) {
            Word word;
            word.index = index;
            word.word = w;
            wordMap.insert(word,wordInfo);
            for (WordMap::iterator it = wordMap.begin(), ie = wordMap.end();
                 it != ie; ++it){
                if (it.key() == word) {
                    WordInfo& info = it.value();
                    info.sentences.push_back(sentence);
                    info.sentences.removeDuplicates();
                }
            }
        }
    }


    //Todo:

    data_.classMap_.insert(index, wordMap);


    return true;


}

bool Nce::parseWord()
{
    QProgressDialog dialog;
    dialog.setModal(true);
    dialog.setLabelText(" i am reading from every class...");
    dialog.setRange(0, data_.classMap_.size());
    dialog.show();
    int process = 0;
    ClassMap::iterator it = data_.classMap_.begin(), iE = data_.classMap_.end();
    for (;it != iE; ++it) {
        ClassIndex index =  it.key();
        WordMap& wordMap = it.value();
        dialog.setValue(++process);
        WordMap::iterator wit = wordMap.begin(), wiE = wordMap.end();
        for (; wit != wiE; ++wit) {
            Word word = wit.key();
            WordInfo info = wit.value();
            QString w = word.word;
            QStringList wl = info.sentences;
            data_.wordList_.insert(w,info);
            // This is buggy!!!
            // must change!!!
            for(WordList::iterator it= data_.wordList_.begin(),
                ie = data_.wordList_.end();
                it != ie;
                ++it) {
                if (it.key() == w) {
                    it.value().sentences.append(wl);
                    it.value().sentences.removeDuplicates();
                }
            }
        }

    }
    return true;
}

bool Nce::replaceFile(const QString &nce, int _class)
{
    QString path = qApp->applicationDirPath()+"/nce/";
    path += nce + "/";
    QString classStr = QString::number(_class);
    if (_class < 10) classStr = "0" + QString::number(_class);
    path += classStr;
    QFileInfo fileInfo(path + ".txt");
    if (!fileInfo.exists())
        path += ".TXT";
    else
        path += ".txt";
    file_.setFileName(path);
    if (!file_.open(QIODevice::ReadOnly)) {
        qDebug() << "Read File Error!"+ path;
        return false;
    }
    QString text = file_.readAll();
    if (file_.isOpen())
        file_.close();
    text = simpleChange(text);
    QStringList sentenceList = text.split(QRegExp("[\\.!\\?]"),QString::SkipEmptyParts);
    QString newString = sentenceList.join("\n");
    if (!file_.open(QIODevice::WriteOnly)) {
        qDebug() << "Read File Error!"+ path;
        return false;
    }
    file_.write(newString.toLatin1());
    file_.close();
}
