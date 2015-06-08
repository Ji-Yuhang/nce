#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    static Database* instance();
    int haveWord(const QString& word);
    bool insertNewWord(const QString& word, bool& ok);
    bool setWordStatus(int word_id, int status);
signals:

public slots:

private:
    static Database* g_db;
    QSqlDatabase db_;
};
#define DB Database::instance()

#endif // DATABASE_H
