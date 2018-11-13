//
// Created by dguco on 18-11-7.
// redis master slave manager
//

#ifndef EXHIREDIS_MASTERSLAVEMANAGER_HPP
#define EXHIREDIS_MASTERSLAVEMANAGER_HPP

#include <memory>
#include "connection_manager.hpp"
#include "config/redis_config.hpp"

namespace exhiredis
{
class CMasterSlaveManager: public IConnectionManager
{
public:
    CMasterSlaveManager(const shared_ptr<CRedisConfig> &m_pRedisConfig);
    int CalcSlot(string key) override;
    int CalcSlot(char *key, int len) override;
    shared_ptr<MasterSlaveServersConfig> GetConfig() override;
    shared_ptr<CMasterSlaveEntry> GetEntry(int slot) override;
    void ShutDown() override;
    bool IsShutDown() override;
    shared_ptr<CRedisConfig> &GetRedisConfig() override;
private:
    shared_ptr<CRedisConfig> m_pRedisConfig;
};

CMasterSlaveManager::CMasterSlaveManager(const shared_ptr<CRedisConfig> &m_pRedisConfig)
    : m_pRedisConfig(m_pRedisConfig)
{

}

int CMasterSlaveManager::CalcSlot(string key)
{
    return 0;
}

int CMasterSlaveManager::CalcSlot(char *key, int len)
{
    return 0;
}

shared_ptr<MasterSlaveServersConfig> CMasterSlaveManager::GetConfig()
{
    return nullptr;
}

shared_ptr<CMasterSlaveEntry> CMasterSlaveManager::GetEntry(int slot)
{
    return nullptr;
}

void CMasterSlaveManager::ShutDown()
{

}

bool CMasterSlaveManager::IsShutDown()
{
    return false;
}

shared_ptr<CRedisConfig> &CMasterSlaveManager::GetRedisConfig()
{
    return <#initializer#>;
}
}
#endif //EXHIREDIS_MASTERSLAVEMANAGER_HPP
