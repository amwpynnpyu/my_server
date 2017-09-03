#ifndef __SHARE_WIN_SOCK_MGR_H__
#define __SHARE_WIN_SOCK_MGR_H__

#include "sh_include.h"
#include "sh_net.h"
#include "sh_win_sock.h"
#include "sh_common.h"
#include "sh_ptrlist.h"



class CWinSocketMgr :public sh::CSingleton<CWinSocketMgr>
{
public:
    CWinSocketMgr();
    virtual ~CWinSocketMgr();

    bool init(sh::uint32  pool_num);

private:
    //SOCKET   m_socket;
    sh::CPool<CWinSocket>     m_sock_pool;
};


#endif //__SHARE_WIN_SOCK_MGR_H__