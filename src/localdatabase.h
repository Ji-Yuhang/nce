#ifndef LOCALDATABASE_H
#define LOCALDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include "data.hxx"

class LocalDatabase : public QObject
{
    Q_OBJECT
public:
    explicit LocalDatabase(QObject *parent = 0);
    void parse(QSqlDatabase db);
    void save();
    QList<Data::BookData> bookDataList;


signals:

public slots:
private:
    QSqlDatabase nce_db_;
    QSqlDatabase willpower_db_;

};

#endif // LOCALDATABASE_H
