#include "sh_win_sock.h"


CSocket::CSocket()
{
    m_socket = INVALID_SOCKET;
}


CSocket::~CSocket()
{
}


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