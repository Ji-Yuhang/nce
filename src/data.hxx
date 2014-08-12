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
struct WordInfo
{
    ClassIndex index;
    QStringList sentences;
};
typedef QMultiMap<Word, WordInfo> WordMap;
typedef QMultiMap<ClassIndex, WordMap> ClassMap;
typedef QMap<ClassIndex, QString> ClassContent;
typedef QMultiMap<QString, WordInfo> WordList;
struct Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = 0);
public:
    static Data* instance();
    ClassMap classMap_;
    WordList wordList_;
    ClassContent classContent_;
private:
    static Data* g_data;
signals:

public slots:

};

#endif // DATA_HXX
