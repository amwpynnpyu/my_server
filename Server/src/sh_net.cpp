#include "sh_net.h"
#include "sh_win_iocp.h"


const char* get_net_error_msg(sh::E_NET_ERROR errcode)
{
	return "";
}

/// ����ָ������ģ������ָ��
sh::INetModule* create_net_module()
{
    return new CWinIocpModule();
}