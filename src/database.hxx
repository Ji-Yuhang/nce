#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include "article.hxx"
#include "localdatabase.h"
#include "netmanager.h"
class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    static Database* instance();
    int haveWord(const QString& word);
    bool insertNewWord(const QString& word);
//    bool setWordStatus(int word_id, int status);
//    int knowWord(int word_id);
    int unKnowWord(int word_id);
    int wordFamiliarity(int word_id);
    bool insertNewFamiliarity(int word_id);
    bool setWordFamiliarity(int word_id, int familiarity);
    QList<WordInfo> getAllUnknown();
    QList<WordInfo> getAllKnown();
    QList<Data::BookData>& bookData() {return localDb_.bookDataList;}


signals:

public slots:

private:
    static Database* g_db;
    QSqlDatabase db_;
    LocalDatabase localDb_;
    NetManager net_;
};
#define DB Database::instance()

#endif // DATABASE_H
