#ifndef ARTICLE_HXX
#define ARTICLE_HXX

#include <QObject>
#include <QStringList>
class Article : public QObject
{
    Q_OBJECT
public:
    explicit Article(QObject *parent = 0);

signals:
    void parseFinished();

public slots:
    void parseArticle(const QString& article);

protected:
    void parseWord(const QString& word);
    QStringList words_;
    QStringList wordsKnown_;
    QStringList wordsNotKnown_;
};

#endif // ARTICLE_HXX
