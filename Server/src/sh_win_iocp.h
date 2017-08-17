#ifndef __SHARE_WIN_IOCP_H__
#define __SHARE_WIN_IOCP_H__

#include "sh_net.h"
#include "sh_common.h"

class CWinIocpModule : public sh::INetModule, public sh::noncopyable
{
public:
    CWinIocpModule();
    virtual ~CWinIocpModule();

    /// 初始化网络资源、配置。
    virtual bool init(const sh::NetModuleCfg& cfg);

    /// 释放网络模块
    virtual void release();

    /**
    * @brief pSession与connector关联的会话对象,
    *  NetModule系统并不会自动回收pSession指向的对象，而是等她关联的connector,
    *  结束生命周期后，用户自己负责回收。
    * @param pSession 指向与connector关联的会话对象
    * @param dwRecvBufSize  连接的接收缓冲区
    * @param dwSendBufSize  连接的发送缓冲区
    * @param pszIP  远端服务器IP
    * @param wPort  远端服务器监听端口
    * @param dwAutoReconnectMilSecond 设置自动重新连接的间隔。单位为毫秒。0xffffffff表示不自动重连
    * @return 成功返回一个指向Connector对象的指针，否则返回 NULL
    * @note CreateConnector 创建的对象拥有与进程相同的生命周期，在进程运行期间，不允许销毁
    */
    virtual sh::IConnector*  create_connector(sh::ISession* pSession,
        sh::uint32 dwRecvBufSize,
        sh::uint32 dwSendBufSize,
        const char* pszIP,
        sh::uint16 wPort,
        sh::uint32 dwAutoReconnectMilSecond = 0xffffffff
        );

    /**
    * @brief pSessionFactory与为Listenner提供session工厂,
    *  当关联的连接关闭后，listenner 会调用她初始化时绑定的pSessionFactory,
    *  的FreeSession方法来回收与关联连接关联的session,sessionfactory 里的 FreeSession 也是用户实现
    * @param pSessionFactory 指向与connector关联的会话对象
    * @param dwRecvBufSize  连接的接收缓冲区
    * @param dwSendBufSize  连接的发送缓冲区
    * @param pszIP  监听的IP地址
    * @param wPort  监听端口
    * @param bReUseAddr 是否复用地址， 默认true bReUseAddr 把监听套接字设置为SOL_SOCKET，SO_REUSEADDR
    * @param pCheck 设置校验连接连接IP是否合法的方法作为防火墙作用， 默认NULL
    * @return 成功返回一个指向IListener对象的指针，否则返回 NULL
    * @note CreateListener 创建的对象拥有与进程相同的生命周期，在进程运行期间，不允许销毁
    */
    virtual sh::IListener*  create_listener(sh::ISessionFactory* pSessionFactory,
        sh::uint32 dwRecvBufSize,
        sh::uint32 dwSendBufSize,
        const char* pszIP,
        sh::uint16 wPort,
        bool bReUseAddr = true,
        sh::ICheckIP* pCheck = NULL
        );

    virtual bool  run();
};

#endif //__SHARE_WIN_IOCP_H__