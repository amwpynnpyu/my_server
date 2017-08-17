#ifndef __SHARE_NET_MGR_H__
#define __SHARE_NET_MGR_H__

#include "sh_net.h"

class CConnection: public sh::IConnection
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
};

class CListener : public sh::IListener
{
public:
    CListener();
    virtual ~CListener();

    // 启动监听
    // 连接请求队列  backlog
    virtual bool  start(int backlog = 5) = 0;

    // 停止监听，关闭监听套接字
    virtual bool  stop(void) = 0;

    // 设置本地监听地址
    // 如果监听本地所有，则pszIP=0.0.0.0
    // 如果对已经Start好的listner调用这个函数，则
    // 需要Stop成功后，重新Start的时候才会使用这里设置的ip和端口
    // 设置成功返回true，否则返回false。如果当前listener没有Stop，则不能设置，返回false
    virtual bool set_remote_address(const char* pszIP, sh::uint16 wPort) = 0;

    // 设置本连接的网络数据的收发缓冲区长度
    // 如果对已经建立好的连接调用这个函数，则
    // 需要Stop这个监听后，重新Start成功后才会使用这里设置的缓冲区长度
    // 合法的设置返回true，否则返回false
    virtual bool set_data_buffer_size(sh::uint32 dwRecvBufSize, sh::uint32 dwSendBufSize) = 0;
};


class CConnector : public sh::IConnector
{
public:
    CConnector();
    virtual ~CConnector();

    // 取得关联connector的session
    virtual sh::ISession* get_session() = 0;

    // 设置远程地址
    // 如果对已经建立好的连接调用这个函数，则
    // 需要关闭这个连接后，重新Connect的时候才会使用这里设置的ip和端口
    virtual void set_remote_address(const char* pszIP, sh::uint16 wPort) = 0;

    // 设置本连接的网络数据的收发缓冲区长度
    // 如果对已经建立好的连接调用这个函数，则
    // 需要关闭这个连接后，重新Connect成功后才会使用这里设置的缓冲区长度
    // 合法的设置返回true，否则返回false
    virtual bool set_data_buffer_size(sh::uint32 dwRecvBufSize, sh::uint32 dwSendBufSize) = 0;

    // 设置自动重新连接的间隔 单位为毫秒。0xffffffff表示不自动重连
    // 如果对已经建立好的连接调用这个函数，则
    // 需要关闭这个连接后，重新Connect成功后才会使用这里自动重连设置
    virtual void set_auto_reconect_milsecond(sh::uint32 dwAutoReconnectMilSecond = 0xffffffff) = 0;

    // 发起连接（异步连接）
    // 调用 Connect 的时候，使用应保证connector 对象还是有效的
    virtual bool  connect() = 0;

    // 手动发起重新连接
    // 在创建connector线程 或者是用户创建的其他线程，因为使用者知道 connector的 生命周期，
    // 所以使用保证调用 ReConnect 的时候，connector 是有效
    virtual bool  re_connect(void) = 0;

    // 收到发起断开连接, 如果使用这个接口断开连接，
    // 即使设置自动重连，也不会发起重新连接，如果要重新连接，
    // 用户必须手动发起重新连接，即调用ReConnect接口
    // 在创建connector线程 或者是用户创建的其他线程，因为使用者知道 connector的 生命周期，
    // 所以使用保证调用 Disconnect 的时候，connector 是有效
    virtual void dis_connect() = 0;
};

class CNetModule : public sh::INetModule
{
public:
    CNetModule();
    virtual ~CNetModule();

    /// 初始化网络资源、配置。
    virtual bool init(const sh::NetModuleCfg& cfg) = 0;

    /// 释放网络模块
    virtual void release() = 0;

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
        ) = 0;

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
        ) = 0;

    virtual bool  run() = 0;
};

// ISession 需要用户继承，派生自己需要的实现
class CSession: public sh::ISession
{
public:
    CSession();
    virtual ~CSession();

    //////////////////////////////////////////////////////////////////////////
    // 下面四个函数都是在用户处理网络网络数据的地方调用。
    // 传入的有效链接的指针 IConnection* 也只能在这个线程使用的时候，才是安全的

    // 当连接建立后，会回调该函数
    // 传入一个有效的链接指针
    // 用户自行保存这个指针
    virtual void  on_establish(sh::IConnection* poConnection) = 0;

    // 当连接断开，会回调该函数
    // 传入一个 NULL 来使用用户原来保存有效连接指针无效
    // 用户必须使用传入的 参数， 为原来保存有效连接指针赋值，使其无效
    virtual void  on_terminate(sh::IConnection* poConnection) = 0;

    // 当连接发生错误，会回调该函数
    virtual bool  on_error(sh::int32 nModuleErr, sh::int32 nSysErr) = 0;

    // 当收到网络数据包时，会回调。
    virtual void  on_recv(const char* pBuf, sh::uint32 dwLen) = 0;
};

// ISessionFactory 需要用户继承，派生自己需要的实现
// 会话对象工厂器
// CreateSession, FreeSession 需要多线程安全
class CSessionFactory : public sh::ISessionFactory
{
public:
    CSessionFactory();
    virtual ~CSessionFactory();

    // 创建一个会话对象. 用户只要实现这个接口，系统会自动调用它来分配
    virtual sh::ISession*  create_session() = 0;
    // 回收一个回话对象。 用户只要实现这个接口，系统会自动调用它来释放
    virtual void free_session(sh::ISession* pSession) = 0;
};

#endif //__SHARE_NET_MGR_H__