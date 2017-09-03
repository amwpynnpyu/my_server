#include "sh_win_sock.h"



CWinSocket::CWinSocket()
{
    m_socket = INVALID_SOCKET;
}

CWinSocket::~CWinSocket()
{

}

bool CWinSocket::is_connected(void)
{
    return true;
}

bool CWinSocket::send(const char* pBuf, sh::uint32 dwLen, const char* pExBuf, sh::uint32 dwExLen)
{
    return true;
}

sh::int32 CWinSocket::raw_send(const char* pBuf, sh::int32 nLen)
{
    return 0;
}

void CWinSocket::dis_connect(void)
{

}

const sh::uint32  CWinSocket::get_remote_ip(void)
{
    return 0;
}

const char*  CWinSocket::get_remote_ip_str(void)
{
    return NULL;
}

sh::uint16  CWinSocket::get_remote_port(void)
{
    return 0;
}

const sh::uint32  CWinSocket::get_local_ip(void)
{
    return 0;
}

const char*  CWinSocket::get_local_ip_str(void)
{
    return NULL;
}

sh::uint16  CWinSocket::get_local_port(void)
{
    return 0;
}