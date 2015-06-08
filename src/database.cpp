#include "database.hxx"
#include <assert.h>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

Database* Database::g_db = 0;
Database::Database(QObject *parent) :
    QObject(parent)
{
    assert(!g_db);
    g_db = this;
    db_ = QSqlDatabase::addDatabase("QMYSQL");

    db_.setDatabaseName("english");
    db_.setHostName("rds1m2iqskhitpx6nmx7u.mysql.rds.aliyuncs.com");
    db_.setUserName("jiyuhang");
    db_.setPassword("jiyuhang8757871");
    bool s = db_.open();
    if (!s) {
        qDebug() << "aliyun database open ERROR";
        QSqlError error = db_.lastError();
        qDebug() << error.text();
    }
}

Database *Database::instance()
{
    return g_db;
}

int Database::haveWord(const QString &word)
{
    QSqlQuery query(db_);
    QString sql = QString("select word_id from wordlist where content='%1'").arg(word);
    if (query.exec(sql)) {
        while (query.next()) {
            int wordid = query.value(0).toInt();
            return wordid;
        }

    } else {
        QString error = query.lastError().text();
        qDebug() << "sql exec error: "<< error;
    }
    return 0;

}

bool Database::insertNewWord(const QString &word, bool &ok)
{
    return false;
}

bool Database::setWordStatus(int word_id, int status)
{
    return false;
}
