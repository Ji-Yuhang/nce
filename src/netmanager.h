#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QObject>

class NetManager : public QObject
{
    Q_OBJECT
public:
    explicit NetManager(QObject *parent = 0);
    ~NetManager();
    static NetManager* instance(){return g_single_net_manager_;}

Q_SIGNALS:

public Q_SLOTS:
//    void async();
private:
    static NetManager* g_single_net_manager_;
};
#define NET NetManager::instance()

#endif // NETMANAGER_H
