#ifndef ARTICLE_HXX
#define ARTICLE_HXX

#include <QObject>
#include <QStringList>
#include <QMap>
struct WordInfo {
    int word_id;
    QString word;
    int familiarity;
};

class Article : public QObject
{
    Q_OBJECT
public:
    explicit Article(QObject *parent = 0);
//    QStringList allWord() {return words_;}
    bool known(const QString& word);
//    QStringList unKnownWordList();
    QList<WordInfo> unknownWordInfoList() {return unknownWordInfoList_;}
    QList<WordInfo> signedUnknownWordInfoList(){return signedUnknownWordInfoList_;}
    QList<WordInfo> allWordInfoList() {return wordInfoList_;}
    WordInfo wordInfo(int word_id);

//    WordInfo wordInfo();

signals:
    void parseFinished();

public slots:
    void parseArticle(const QString& article);

protected:
    void parseWord(const QString& word);
    QList<WordInfo> wordInfoList_;
    QList<WordInfo> unknownWordInfoList_;
    QList<WordInfo> signedUnknownWordInfoList_;

    QMap<QString,int> wordKnownMap_;
    QStringList words_;
    QStringList wordsKnown_;
    QStringList wordsNotKnown_;
};

#endif // ARTICLE_HXX
