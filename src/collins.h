#ifndef COLLINS_H
#define COLLINS_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QStringList>

struct CollinsWordInfo
{
    QString word;
    QString html;
    int frequency;
    QStringList morphologyList;

};

class Collins : public QObject
{
    Q_OBJECT
public:
    enum DictType {
        CollinsZH = 0,
        CollinsEN
    };

    explicit Collins(QObject *parent = 0);
    CollinsWordInfo wordInfo(const QString& word);

signals:

public slots:
private:
    void readCollins(const QString& filePath,DictType type);
    QMap<QString, CollinsWordInfo> zhwordInfo_;
    QMap<QString, CollinsWordInfo> enwordInfo_;

//    void saveSQLite
};

#endif // COLLINS_H
