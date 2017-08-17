#ifndef __SHARE_LISTENER_H__
#define __SHARE_LISTENER_H__

#include "sh_net.h"

class CListener : public sh::IListener
{
public:
    CListener();
    virtual ~CListener();

    // 启动监听
    // 连接请求队列  backlog
    virtual bool  start(int backlog = 5);

    // 停止监听，关闭监听套接字
    virtual bool  stop(void);

    // 设置本地监听地址
    // 如果监听本地所有，则pszIP=0.0.0.0
    // 如果对已经Start好的listner调用这个函数，则
    // 需要Stop成功后，重新Start的时候才会使用这里设置的ip和端口
    // 设置成功返回true，否则返回false。如果当前listener没有Stop，则不能设置，返回false
    virtual bool set_remote_address(const char* pszIP, sh::uint16 wPort);

    // 设置本连接的网络数据的收发缓冲区长度
    // 如果对已经建立好的连接调用这个函数，则
    // 需要Stop这个监听后，重新Start成功后才会使用这里设置的缓冲区长度
    // 合法的设置返回true，否则返回false
    virtual bool set_data_buffer_size(sh::uint32 dwRecvBufSize, sh::uint32 dwSendBufSize);
};




#endif //__SHARE_LISTENER_H__