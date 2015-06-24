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
    if (!db_.isOpen())db_.open();
    QSqlQuery query(db_);
    QString sql = QString("select word_id from wordlists where content='%1'").arg(word);
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
    if (!db_.isOpen())db_.open();
    QSqlQuery query(db_);
    QString sql = QString("insert into wordlists (content) values('%1')").arg(word);
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
    if (!db_.isOpen())db_.open();

    QSqlQuery query(db_);
    QString sql = QString("select unknown_id,familiarity from unknownwords  where word_id=%1").arg(word_id);
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
    if (!db_.isOpen())db_.open();

    QSqlQuery query(db_);
    QString sql = QString("select unknown_id,familiarity from unknownwords  where word_id=%1").arg(word_id);
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
    if (!db_.isOpen())db_.open();

    QSqlQuery query(db_);
    QString sql = QString("insert into unknownwords  (word_id,familiarity) values(%1,0)").arg(word_id);
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
    if (!db_.isOpen())db_.open();

    QSqlQuery query(db_);
    QString sql = QString("update unknownwords  set familiarity= %1 where word_id=%2").arg(familiarity).arg(word_id);
    if (query.exec(sql)) {
        return true;
    } else {
        QString error = query.lastError().text();
        qDebug() << "sql exec error: "<< error;
        return false;
    }
    return false;
}

QList<WordInfo> Database::getAllUnknown()
{
    if (!db_.isOpen())db_.open();

    QList<WordInfo> all;
    QSqlQuery query(db_);
    QString sql = QString("select *from wordlists where word_id in (select word_id from unknownwords  where familiarity=0)");
    if (query.exec(sql)) {
        while (query.next()) {
            int wordid = query.value(0).toInt();
            QString word = query.value(1).toString();
            int familiarity = 0;
            WordInfo info;
            info.word_id = wordid;
            info.word = word;
            info.familiarity = familiarity;
            all.append(info);
        }
    } else {
        QString error = query.lastError().text();
        qDebug() << "sql exec error: "<< error;
    }
    return all;
}
