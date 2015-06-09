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
    db_ = QSqlDatabase::addDatabase("QMYSQL","english");

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

bool Database::insertNewWord(const QString &word)
{
    QSqlQuery query(db_);
    QString sql = QString("insert into wordlist (content) values('%1')").arg(word);
    if (query.exec(sql)) {
        return true;
    } else {
        QString error = query.lastError().text();
        qDebug() << "sql exec error: "<< error;
        return false;
    }
    return false;
}

//bool Database::setWordStatus(int word_id, int status)
//{
//    return false;
//}

int Database::unKnowWord(int word_id)
{
    QSqlQuery query(db_);
    QString sql = QString("select unknown_id,familiarity from unknown_word where word_id=%1").arg(word_id);
    if (query.exec(sql)) {
        while (query.next()) {
            int wordid = query.value(0).toInt();
            int familiarity = query.value(1).toInt();
            return wordid;
        }
    } else {
        QString error = query.lastError().text();
        qDebug() << "sql exec error: "<< error;
    }
    return 0;
}

int Database::wordFamiliarity(int word_id)
{
    QSqlQuery query(db_);
    QString sql = QString("select unknown_id,familiarity from unknown_word where word_id=%1").arg(word_id);
    if (query.exec(sql)) {
        while (query.next()) {
            int wordid = query.value(0).toInt();
            int familiarity = query.value(1).toInt();
            return familiarity;
        }
    } else {
        QString error = query.lastError().text();
        qDebug() << "sql exec error: "<< error;
    }
    return -1;
}

bool Database::insertNewFamiliarity(int word_id)
{
    QSqlQuery query(db_);
    QString sql = QString("insert into unknown_word (word_id,familiarity) values(%1,0)").arg(word_id);
    if (query.exec(sql)) {
        return true;
    } else {
        QString error = query.lastError().text();
        qDebug() << "sql exec error: "<< error;
        return false;
    }
    return false;
}

bool Database::setWordFamiliarity(int word_id, int familiarity)
{
    QSqlQuery query(db_);
    QString sql = QString("update unknown_word set familiarity= %1 where word_id=%2").arg(familiarity).arg(word_id);
    if (query.exec(sql)) {
        return true;
    } else {
        QString error = query.lastError().text();
        qDebug() << "sql exec error: "<< error;
        return false;
    }
    return false;
}
