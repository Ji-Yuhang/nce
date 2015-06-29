#ifndef LOCALDATABASE_H
#define LOCALDATABASE_H

#include <QObject>
#include <QSqlDatabase>

class LocalDatabase : public QObject
{
    Q_OBJECT
public:
    explicit LocalDatabase(QObject *parent = 0);
    void save();

signals:

public slots:
private:
    QSqlDatabase db_;
};

#endif // LOCALDATABASE_H
