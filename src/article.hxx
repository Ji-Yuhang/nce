#ifndef ARTICLE_HXX
#define ARTICLE_HXX

#include <QObject>
#include <QStringList>
#include <QMap>
class Article : public QObject
{
    Q_OBJECT
public:
    explicit Article(QObject *parent = 0);
    QStringList allWord() {return words_;}
    bool known(const QString& word);
    QStringList unKnownWordList();

signals:
    void parseFinished();

public slots:
    void parseArticle(const QString& article);

protected:
    void parseWord(const QString& word);
    QMap<QString,int> wordKnownMap_;
    QStringList words_;
    QStringList wordsKnown_;
    QStringList wordsNotKnown_;
};

#endif // ARTICLE_HXX
