#include "sh_net.h"
#include "sh_win_iocp.h"


const char* get_net_error_msg(sh::E_NET_ERROR errcode)
{
	return "";
}

/// 返回指向网络模块对象的指针
sh::INetModule* create_net_module()
{
    return new CWinIocpModule();
}