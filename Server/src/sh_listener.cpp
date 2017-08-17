#include "sh_listener.h"
#include "sh_common.h"
#include "sh_filelog.h"
#include "sh_include.h"


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


