#include "article.hxx"
#include <QRegExp>
#include "database.hxx"
#include <QDebug>
#include <assert.h>
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

WordInfo Article::wordInfo(int word_id)
{
    WordInfo empty;
    empty.word_id = 0;
    Q_FOREACH(WordInfo info, wordInfoList_) {
        if (info.word_id == word_id)
            return info;
    }
    return empty;

}

//QStringList Article::unKnownWordList()
//{
//    QStringList list;
//    QMap<QString,int>::iterator it = wordKnownMap_.begin();
//    for (; it != wordKnownMap_.end(); ++it) {
//        if (it.value() == 0) {
//            list.append(it.key());
//        }
//    }
//    return list;
//}

void Article::parseArticle(const QString &article)
{
    wordInfoList_.clear();
    unknownWordInfoList_.clear();
    int size = article.size();
    words_ = article.split(QRegExp("\\W+"),QString::SkipEmptyParts);
    words_.removeDuplicates();
    foreach (QString w, words_) {
        parseWord(w.toLower());
    }
    emit parseFinished();
}

void Article::parseWord(const QString &word)
{
    //TODO: 分析单词的含义，生成每个单词的信息结构体列表。当读完之后，将认识的单词写入认识单词表，不认识的单词写入不认识单词表
    qDebug() << "parse : "+word;
    //TODO: save to word database
    assert(!word.isEmpty());
    int wordid = DB->haveWord(word);
    if (wordid  == 0) DB->insertNewWord(word);
    wordid = DB->haveWord(word);
    // TODO: know or not
    assert(wordid > 0);

    int familiarity = DB->wordFamiliarity(wordid);

    if (familiarity < 0) {
        DB->insertNewFamiliarity(wordid);
        familiarity = DB->wordFamiliarity(wordid);
        assert(familiarity >= 0);
    }
    qDebug() <<word<<" id : "<< wordid << "     familiarity : "<<familiarity;

    WordInfo info;
    info.word_id = wordid;
    info.word = word;
    info.familiarity = familiarity;
    wordInfoList_.append(info);
    if (info.familiarity  == 0)
        unknownWordInfoList_.append(info);

}
