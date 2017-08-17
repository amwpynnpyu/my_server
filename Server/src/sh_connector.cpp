#include "sh_connector.h"
#include "sh_common.h"
#include "sh_filelog.h"
#include "sh_include.h"




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


