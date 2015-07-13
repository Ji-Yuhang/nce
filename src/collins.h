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
    explicit Collins(QObject *parent = 0);
    CollinsWordInfo wordInfo(const QString& word);

signals:

public slots:
private:
    void readCollins(const QString& filePath);
    QMap<QString, CollinsWordInfo> wordInfo_;
};

#endif // COLLINS_H
