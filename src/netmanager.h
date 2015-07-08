#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
//struct WordInfo{
//    QString word;
//    int word_id;
//    int familiarity;
//    WordInfo():word_id(0){}
//};
#include "article.hxx"
class NetManager : public QObject
{
    Q_OBJECT
public:
    explicit NetManager(QObject *parent = 0);
    ~NetManager();
    static NetManager* instance(){return g_single_net_manager_;}
    WordInfo wordInfo(int word_id);
    WordInfo wordInfo(const QString& word);
    WordInfo insertWord(const QString& word);
    WordInfo insertFamiliarity(int word_id);

    WordInfo setWordFamiliarity(int word_id, int familiarity);
    QList<WordInfo> allUnknown();

Q_SIGNALS:

public Q_SLOTS:
//    void async();
private:
    static NetManager* g_single_net_manager_;
    QNetworkAccessManager manager_;
};
#define NET NetManager::instance()

#endif // NETMANAGER_H
