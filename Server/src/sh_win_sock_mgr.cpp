#include "sh_win_sock_mgr.h"



CWinSocketMgr::CWinSocketMgr()
{
}

CWinSocketMgr::~CWinSocketMgr()
{

}

bool CWinSocketMgr::init(sh::uint32  pool_num)
{
    return m_sock_pool.init(pool_num, false);
}