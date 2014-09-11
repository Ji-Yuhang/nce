#include "article.hxx"
#include <QRegExp>
Article::Article(QObject *parent) :
    QObject(parent)
{
}

void Article::parseArticle(const QString &article)
{
    int size = article.size();
    words_ = article.split(QRegExp("\\W+"),QString::SkipEmptyParts);
    foreach (QString w, words_) {
        parseWord(w);
    }
    emit parseFinished();
}

void Article::parseWord(const QString &word)
{
    //TODO: 分析单词的含义，生成每个单词的信息结构体列表。当读完之后，将认识的单词写入认识单词表，不认识的单词写入不认识单词表

}
