#ifndef DATA_HXX
#define DATA_HXX

#include <QObject>
#include <QMap>
#include <QMultiMap>

#include <QStringList>
struct ClassIndex
{
    QString nce;
    int class_;
};
inline bool operator<(const ClassIndex &my, const ClassIndex &index)
{
    if (my.nce < index.nce)
        return true;
    else if (my.nce ==index.nce) {
        if (my.class_ < index.class_)
            return true;
        else
            return false;
    } else
        return false;
}
inline bool operator==(const ClassIndex &my, const ClassIndex &index)
{
    return (my.nce == index.nce && my.class_ == index.class_);
}

inline bool operator!=(const ClassIndex &my, const ClassIndex &index)
{
    return (my.nce != index.nce || my.class_ != index.class_);
}
struct Word
{
    ClassIndex index;
    QString word;
};
inline bool operator<(const Word &my, const Word &w)
{
    return (my.word < w.word);
}
inline bool operator==(const Word &my, const Word &w)
{
    return (my.word == w.word);
}
struct NceWordInfo
{
    ClassIndex index;
    QStringList sentences;
};
typedef QMultiMap<Word, NceWordInfo> WordMap;
typedef QMultiMap<ClassIndex, WordMap> ClassMap;
typedef QMap<ClassIndex, QString> ClassContent;
typedef QMultiMap<QString, NceWordInfo> WordList;
struct OldData : public QObject
{
    Q_OBJECT
public:
    explicit OldData(QObject *parent = 0);
public:
    static OldData* instance();
    ClassMap classMap_;
    WordList wordList_;
    ClassContent classContent_;
private:
    static OldData* g_data;
signals:

public slots:

};
namespace Data {

struct Article
{
    int article_id;
    QString title;
    QString content;
    int addtime;
    int updatetime;
    int word_count;
    int sentence_count;
    QString author;
    int status;
    Article():article_id(0){}
};
struct Sentence
{
    int sentence_id;
    QString sentence;
    int article_id;
    int addtime;
    int updatetime;
    int word_count;
    int status;
    Sentence():sentence_id(0),article_id(0){}
};
struct Word
{
    int word_id;
    QString word;
    int frequency;
    QList<int> sentence_id_list;
    int status;
    Word():word_id(0){}
};

struct BookData
{
    QString name;
    QMap<int,Article> articles;
    QMap<int,Sentence> sentences;
    QMap<int,Word> words;
    Article article(int article_id);
    Sentence sentence(int sentence_id);
    Word word(int word_id);
    Word word(const QString& word_content);


};


}
#endif // DATA_HXX
