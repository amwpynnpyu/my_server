#include "sh_win_iocp.h"
#include "sh_common.h"
#include "sh_filelog.h"
#include "sh_include.h"
#include "sh_net_common.h"

CWinIocpModule::CWinIocpModule()
{
	static CInitSock init_sock;

}


CWinIocpModule::~CWinIocpModule()
{
}

bool CWinIocpModule::init(const sh::NetModuleCfg& cfg)
{

    return true;
}

void CWinIocpModule::release()
{

}

sh::IConnector*  CWinIocpModule::create_connector(sh::ISession* pSession,
    sh::uint32 dwRecvBufSize,
    sh::uint32 dwSendBufSize,
    const char* pszIP,
    sh::uint16 wPort,
    sh::uint32 dwAutoReconnectMilSecond
    )
{
    return NULL;
}

sh::IListener*  CWinIocpModule::create_listener(sh::ISessionFactory* pSessionFactory,
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


bool  CWinIocpModule::run()
{
    return true;
}

