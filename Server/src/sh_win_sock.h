#ifndef __SHARE_WIN_SOCK_H__
#define __SHARE_WIN_SOCK_H__

#include "sh_include.h"
#include "sh_net.h"


class CSocket
{
public:
    CSocket();
    ~CSocket();

private:
    SOCKET   m_socket;
};


class CConnection : public sh::IConnection
{
public:
    CConnection();
    virtual ~CConnection();

    //检查是否处于连接中
    virtual bool  is_connected(void);

    // 向连接缓冲区投递数据，准备发送
    // 注意：修改了返回值，投递到发送缓冲区成功，返回true，否则返回false
    // 先从 pBuf 指向的地址取 dwLen 长度的数据，如果有 pExBuf，在从 pExBuf 指向的地址取 dwExLen 长度的数据
    // 组合成一个完成数据包发送
    virtual bool  send(const char* pBuf, sh::uint32 dwLen, const char* pExBuf = NULL, sh::uint32 dwExLen = 0);

    // 直接发送缓冲数据，不做缓冲，也不加数据长度头。即使先使用Send，再使用RawSend，也有可能RawSend先把数据发送出去。慎用!
    virtual sh::int32 raw_send(const char* pBuf, sh::int32 nLen);

    // 断开连接
    virtual void  dis_connect(void);

    // 获得连接远端地址32位整数值
    virtual const sh::uint32  get_remote_ip(void);

    // 获得连接远端地址IP格式的字符串地址
    virtual const char*  get_remote_ip_str(void);

    // 连接远端地址端口
    virtual sh::uint16  get_remote_port(void);

    // 获得连接本地地址32位整数值
    virtual const sh::uint32  get_local_ip(void);

    // 获得连接本地地址IP格式的字符串地址
    virtual const char*  get_local_ip_str(void);

    // 获得连接本地地址端口
    virtual sh::uint16  get_local_port(void);

private:
    CSocket   m_socket;
};


#endif //__SHARE_WIN_SOCK_H__