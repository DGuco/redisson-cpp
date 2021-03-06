//
// Created by dguco on 18-12-24.
//

#ifndef EXHIREDIS_REDIS_LOCK_HPP
#define EXHIREDIS_REDIS_LOCK_HPP
#include <cstring>
#include <memory>
#include "rlock.hpp"
#include "exhiredis/connection_manager.h"

using namespace std;
namespace exhiredis
{
class CRedisLock: public IRlock
{
public:
    CRedisLock(shared_ptr<CConnectionManager> &redisClients, string &m_sLockName);
    void Lock() override;
    bool TryLock() override;
    /**
     * @param time ms
     * @return
     */
    bool TryLock(long time) override;
    void Unlock() override;

private:
    void TryLockAsync(long leaseTime, long threadId);
    void UnLockAsync(long threadId);
private:
    shared_ptr<CConnectionManager> m_pConnectionManager;
    string m_sLockName;
};
}
#endif //EXHIREDIS_REDIS_LOCK_HPP
