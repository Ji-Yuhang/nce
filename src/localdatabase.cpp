#include "localdatabase.h"

#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QApplication>
LocalDatabase::LocalDatabase(QObject *parent) : QObject(parent)
{
    db_ = QSqlDatabase::addDatabase("QSQLITE","nce");
    QString path = qApp->applicationDirPath();
#ifdef Q_OS_MAC
    path += "/../../..";
#endif
//    QDir::setCurrent(path);
    db_.setDatabaseName(path + "/nce3.db");
    if (db_.open()) {
        Q_ASSERT(db_.isOpen());

    } else {
        Q_ASSERT(false);
    }

}

void LocalDatabase::parse()
{
    if (!db_.isOpen()) return;
    Data::BookData bookdata;
    {
        QString sql = QString("select * from articles");
        QSqlQuery query(db_);
        if (query.exec(sql)) {
            while (query.next()) {
                Data::Article article;
                article.article_id = query.value("article_id").toInt();
                article.title = query.value("title").toString();
                article.content = query.value("content").toString();
                article.addtime = query.value("addtime").toInt();
                article.updatetime = query.value("updatetime").toInt();
                article.word_count = query.value("word_count").toInt();
                article.sentence_count = query.value("sentence_count").toInt();
                article.author = query.value("author").toString();
                article.status = query.value("status").toInt();
                bookdata.articles.insert(article.article_id,article);

//                qDebug() << article.article_id<<" ;"
//                         << article.title<<" ;"
//                         << article.content<<" ;"
//                         << article.addtime<<" ;"
//                         << article.updatetime<<" ;"
//                         << article.word_count<<" ;"
//                         << article.sentence_count<<" ;"
//                         << article.author<<" ;"
//                         << article.status<<" ;";
            }
        }
    }
    {
        QString sql = QString("select * from sentences");
        QSqlQuery query(db_);
        if (query.exec(sql)) {
            while (query.next()) {
                Data::Sentence sentence;
                sentence.sentence_id = query.value("sentence_id").toInt();
                sentence.sentence = query.value("sentence").toString();
                sentence.article_id = query.value("article_id").toInt();
                sentence.addtime = query.value("addtime").toInt();
                sentence.updatetime = query.value("updatetime").toInt();
                sentence.word_count = query.value("word_count").toInt();
//                sentence.sentence_count = query.value("sentence_count").toInt();
//                sentence.author = query.value("author").toString();
                sentence.status = query.value("status").toInt();
                bookdata.sentences.insert(sentence.sentence_id, sentence);
//                qDebug() << sentence.sentence_id<<" ;"
//                         << sentence.sentence<<" ;"
//                         << sentence.article_id<<" ;"
//                         << sentence.addtime<<" ;"
//                         << sentence.updatetime<<" ;"
//                         << sentence.word_count<<" ;"
//                         << sentence.status<<" ;";
            }
        }
    }
    {
        QString sql = QString("select * from words");
        QSqlQuery query(db_);
        if (query.exec(sql)) {
            while (query.next()) {
                Data::Word word;
                word.word_id = query.value("word_id").toInt();
                word.word = query.value("word").toString();
                QStringList sentenceids = query.value("sentence_id_list").toString().split(",");
                Q_FOREACH(QString s, sentenceids) {
                    int id = s.toInt();
                    word.sentence_id_list << id;
                }
                word.frequency = query.value("frequency").toInt();
                word.status = query.value("status").toInt();
                bookdata.words.insert( word.word_id, word);
//                qDebug() << word.word_id<<" ;"
//                         << word.word<<" ;"
//                         << word.sentence_id_list<<" ;"
//                         << word.frequency<<" ;"
//                         << word.status<<" ;";
            }
        }
    }
    bookDataList << bookdata;

}

void LocalDatabase::save()
{

}

