#include "sh_win_iocp.h"
#include "sh_common.h"
#include "sh_filelog.h"
#include "sh_include.h"
#include "sh_net_common.h"
#include "sh_win_sock_mgr.h"

CWinIocpModule::CWinIocpModule()
{
	static CInitSock init_sock;

}


CWinIocpModule::~CWinIocpModule()
{
}

bool CWinIocpModule::init(const sh::NetModuleCfg& cfg)
{
    if (!CWinSocketMgr::instance_ex().init(cfg.connection_pool_init_number)) {
        SHARE_LOG_ERROR("CWinSocketMgr::init() fail"); assert(false);
        return false; 
    }

    if (!m_conter_pool.init(cfg.connector_pool_init_number, false)) {
        SHARE_LOG_ERROR("m_conter_pool::init() fail"); assert(false);
        return false;
    }

    if (!m_listen_pool.init(cfg.listener_pool_init_number, false)) {
        SHARE_LOG_ERROR("m_conter_pool::init() fail"); assert(false);
        return false;
    }

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

