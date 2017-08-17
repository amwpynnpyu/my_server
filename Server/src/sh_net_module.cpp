#include "sh_net_module.h"
#include "sh_common.h"
#include "sh_filelog.h"
#include "sh_include.h"

CNetModule::CNetModule()
{

}

CNetModule::~CNetModule()
{

}

bool CNetModule::init(const sh::NetModuleCfg& cfg)
{
    return true;
}

void CNetModule::release()
{

}

sh::IConnector*  CNetModule::create_connector(sh::ISession* pSession,
    sh::uint32 dwRecvBufSize,
    sh::uint32 dwSendBufSize,
    const char* pszIP,
    sh::uint16 wPort,
    sh::uint32 dwAutoReconnectMilSecond 
    )
{
    return NULL;
}

sh::IListener*  CNetModule::create_listener(sh::ISessionFactory* pSessionFactory,
    sh::uint32 dwRecvBufSize,
    sh::uint32 dwSendBufSize,
    const char* pszIP,
    sh::uint16 wPort,
    bool bReUseAddr,
    sh::ICheckIP* pCheck
    )
{
    return NULL;
}


bool  CNetModule::run()
{
    return true;
}

