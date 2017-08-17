#include "sh_net_mgr.h"
#include "sh_common.h"
#include "sh_filelog.h"
#include "sh_include.h"

CConnection::CConnection()
{

}

CConnection::~CConnection()
{

}

bool CConnection::is_connected(void)
{
    return true;
}

bool CConnection::send(const char* pBuf, sh::uint32 dwLen, const char* pExBuf, sh::uint32 dwExLen)
{
    return true;
}

sh::int32 CConnection::raw_send(const char* pBuf, sh::int32 nLen)
{
    return 0;
}

void CConnection::dis_connect(void)
{

}

const sh::uint32  CConnection::get_remote_ip(void)
{
    return 0;
}

const char*  CConnection::get_remote_ip_str(void)
{
    return NULL;
}

sh::uint16  CConnection::get_remote_port(void)
{
    return 0;
}

const sh::uint32  CConnection::get_local_ip(void)
{
    return 0;
}

const char*  CConnection::get_local_ip_str(void)
{
    return NULL;
}

sh::uint16  CConnection::get_local_port(void)
{
    return 0;
}


CListener::CListener()
{

}

CListener::~CListener()
{

}


bool  CListener::start(int backlog)
{
    return true;
}

bool  CListener::stop(void)
{
    return true;
}

bool CListener::set_remote_address(const char* pszIP, sh::uint16 wPort)
{
    return true;
}

bool CListener::set_data_buffer_size(sh::uint32 dwRecvBufSize, sh::uint32 dwSendBufSize)
{
    return true;
}


CConnector::CConnector()
{

}

CConnector::~CConnector()
{

}

sh::ISession* CConnector::get_session()
{
    return NULL;
}

void CConnector::set_remote_address(const char* pszIP, sh::uint16 wPort)
{

}

bool CConnector::set_data_buffer_size(sh::uint32 dwRecvBufSize, sh::uint32 dwSendBufSize)
{
    return true;
}

void CConnector::set_auto_reconect_milsecond(sh::uint32 dwAutoReconnectMilSecond)
{

}

bool  CConnector::connect()
{
    return true;
}

bool  CConnector::re_connect(void)
{
    return true;
}

void CConnector::dis_connect()
{

}


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



CSession::CSession()
{
}


CSession::~CSession()
{
}

void  CSession::on_establish(sh::IConnection* poConnection)
{

}

void CSession::on_terminate(sh::IConnection* poConnection)
{

}

bool CSession::on_error(sh::int32 nModuleErr, sh::int32 nSysErr)
{
    return true;
}

void CSession::on_recv(const char* pBuf, sh::uint32 dwLen)
{

}

CSessionFactory::CSessionFactory()
{
}


CSessionFactory::~CSessionFactory()
{
}


sh::ISession* CSessionFactory::create_session()
{
    return NULL;
}

void CSessionFactory::free_session(sh::ISession* pSession)
{

}

