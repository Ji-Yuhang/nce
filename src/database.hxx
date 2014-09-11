#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    static Database* instance();
    bool haveWord(const QString& word, bool &ok);
signals:

public slots:

private:
    static Database* g_db;
};

#endif // DATABASE_H
