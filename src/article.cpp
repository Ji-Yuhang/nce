#include "article.hxx"
#include <QRegExp>
#include "database.hxx"
#include <QDebug>
Article::Article(QObject *parent) :
    QObject(parent)
{
}

bool Article::known(const QString &word)
{
    QMap<QString,int>::iterator it = wordKnownMap_.find(word);
    if (it == wordKnownMap_.end()) return false;
    if (it.value() == 1) return true;
    else if (it.value() == 0) return false;
}

QStringList Article::unKnownWordList()
{
    QStringList list;
    QMap<QString,int>::iterator it = wordKnownMap_.begin();
    for (; it != wordKnownMap_.end(); ++it) {
        if (it.value() == 0) {
            list.append(it.key());
        }
    }
    return list;
}

void Article::parseArticle(const QString &article)
{
    int size = article.size();
    words_ = article.split(QRegExp("\\W+"),QString::SkipEmptyParts);
    words_.removeDuplicates();
    foreach (QString w, words_) {
        parseWord(w);
    }
    emit parseFinished();
}

void Article::parseWord(const QString &word)
{
    //TODO: 分析单词的含义，生成每个单词的信息结构体列表。当读完之后，将认识的单词写入认识单词表，不认识的单词写入不认识单词表
    qDebug() << "parse : "+word;
    //TODO: know or not
    int wordid = DB->haveWord(word);
    qDebug() <<word<<" id : "<< wordid;
    QMap<QString,int>::iterator it = wordKnownMap_.find(word);
    if (it != wordKnownMap_.end()) {
        it.value() = 0;
    } else {
        wordKnownMap_.insert(word,0);
    }
}
