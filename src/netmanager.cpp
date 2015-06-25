#include "netmanager.h"
NetManager* NetManager::g_single_net_manager_ = 0;
NetManager::NetManager(QObject *parent) : QObject(parent)
{
    Q_ASSERT(!g_single_net_manager_);
    g_single_net_manager_ = this;
}

NetManager::~NetManager()
{
}

