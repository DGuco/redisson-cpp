//
// Created by dguco on 19-1-4.
//

#include <exhiredis/rstl/rscript.h>
#include "redis_clients.h"

namespace exhiredis
{
    CRedisClients::CRedisClients(shared_ptr<CConnectionManager> connManager)
            : m_pConnectionManager(connManager)
    {

    }

    shared_ptr<exhiredis::CRedisClients> CRedisClients::CreateInstance(const string& host,
                                                                       int port,
                                                                       const string passwd,
                                                                       int poolSize,
                                                                       int asyncPoolSize)
    {
        shared_ptr<CConnectionManager> conManager = make_shared<CConnectionManager>();
        conManager->Init(host,port,passwd,poolSize,asyncPoolSize);
        return make_shared<CRedisClients>(std::move(conManager));
    }

    RScript CRedisClients::GetScript()
    {
        return std::move(RScript(m_pConnectionManager));
    }
}