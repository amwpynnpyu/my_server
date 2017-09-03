#ifndef __SHARE_NET_H__
#define __SHARE_NET_H__

#include "sh_type.h"
#include "sh_define.h"

#define NET_USE_TENG_XU_TGW 

namespace sh
{
//////////////////////////////////////////////////////////////////////////
/// 网络模块
//////////////////////////////////////////////////////////////////////////

enum E_NET_ERROR
{
    NET_SUCCESS  = 0,
    NET_NO_ERROR = NET_SUCCESS,     /// 没有错误
    NET_SEND_ERROR,                 /// 发送错误
    NET_RECEIVE_ERROR,              /// 接收错误
    NET_SEND_BUFFER_OVERFLOW,       /// 发送缓冲区溢出
    NET_RECEIVE_BUFFER_OVERFLOW,    /// 接收缓冲区溢出
    NET_CONNECTION_CLOSE,           /// 连接已经关闭
    NET_SEND_BUFFER_NULL,           /// 发送缓冲区为空
    NET_RECEIVE_BUFFER_NULL,        /// 接收缓冲区为空
    NET_CONNECT_FAIL,               /// 连接失败
    NET_CONNECT_TIMEOUT,            /// 连接超时
    NET_CONNECTION_HAS_DISCONNECTED,/// 连接已经断开
    NET_BIND_FAIL,                  /// 绑定失败
    NET_LISTEN_FAIL,                /// 监听失败
    NET_INVAL_CONNECTIONID,         /// 错误的连接id
    NET_INVAL_CONNECTION,           /// 错误的连接
    NET_INVAL_SESSIONID,            /// 错误会话id
    NET_SESSION_NULL,               /// 传入空session
    NET_SERVER_ADDRESS_FAIL,        /// 错误的服务器地址
    NET_SEND_OR_RECV_BUFFER_SIZE_FAIL, ///错误的发送或接收缓冲区大小
    NET_REQ_SOCKET_FAIL,            /// 申请套接字错误
    NET_INIT_SEND_RECV_BUFFER_FACTORY_FAIL, /// 初始化收发缓冲区工厂失败
    NET_HAS_CONNECTED,              // 正在连接中，如果需要新的连接，请先断开当前连接，再尝试
    NET_HAS_LISTEN,                 //正在连接中，如果需要重新监听，请先停止当前连接,再尝试
    NET_ADD_POLL_EVENT_FAIL,        /// 添加epoll事件失败

    NET_BIG_RECV_BUFFER_PIPE_INIT_FAIL,  //网络接收缓冲区初始化失败
    NET_BIG_RECV_BUFFER_PIPE_OVERFLOW,  //网络接收缓冲区溢出
    NET_BIG_RECV_BUFFER_PIP_READ_FAIL,  //从网络缓冲区读取数据失败

    NET_FIRST_RECV_TGW_ERROR,  //首个数据包长度足够，但是解析不了TGW包头
    
    NET_RECV_HEAD_ERROR, /// 收到的数据连首部长度都不够
    NET_TOO_LARGE_PACKET, /// 一个数据包的长度太大了。超过了std::numeric_limits<int32>::max)()

    SYS_MEMORY_ERROR = 20000,       /// 系统内存不够
    SYS_OTHRE_ERROR,                /// 系统其他错误

    NET_NET_ERROR_MAX_ERRORCODE,    ///最大错误码值
};

/// 根据E_NET_ERROR错误码，返回对应的错误信息
extern const char* get_net_error_msg(E_NET_ERROR errcode);

typedef uint32  ID_TYPE; //id的类型

class INetModule;
class ISession;
class ISessionFactory;
class ICheckIP;


// IConnection 仅仅作为接口使用，不需要用户继承
class IConnection
{
public:
    //检查是否处于连接中
    virtual bool  is_connected(void) = 0;

    // 向连接缓冲区投递数据，准备发送
    // 注意：修改了返回值，投递到发送缓冲区成功，返回true，否则返回false
    // 先从 pBuf 指向的地址取 dwLen 长度的数据，如果有 pExBuf，在从 pExBuf 指向的地址取 dwExLen 长度的数据
    // 组合成一个完成数据包发送
    virtual bool  send(const char* pBuf,uint32 dwLen, const char* pExBuf=NULL, uint32 dwExLen=0) = 0;

    // 直接发送缓冲数据，不做缓冲，也不加数据长度头。即使先使用Send，再使用RawSend，也有可能RawSend先把数据发送出去。慎用!
    virtual int32 raw_send(const char* pBuf,int32 nLen)=0;

    // 断开连接
    virtual void  dis_connect(void) = 0;

    // 获得连接远端地址32位整数值
    virtual const uint32  get_remote_ip(void) = 0;

    // 获得连接远端地址IP格式的字符串地址
    virtual const char*  get_remote_ip_str(void) = 0;

    // 连接远端地址端口
    virtual uint16  get_remote_port(void) = 0;

    // 获得连接本地地址32位整数值
    virtual const uint32  get_local_ip(void) = 0;

    // 获得连接本地地址IP格式的字符串地址
    virtual const char*  get_local_ip_str(void) = 0;

    // 获得连接本地地址端口
    virtual uint16  get_local_port(void) = 0;
};

/*
*@brief 校验连接的IP是否合法
*/
class ICheckIP
{
public:
    //如果是允许的ip，返回true，否则返回false
    virtual bool check_ip(const char* pszIP)=0;
};

// IListener 仅仅作为接口使用，不需要用户继承
// IListener 指向的对象，拥有与进程相同的生命周期，用户不能手动销毁。
class IListener
{
public:
#ifdef NET_USE_TENG_XU_TGW
    // 设置监听的每个连接忽略第一个 tgw包头
    virtual void ignore_tgw(void)=0;
#endif
    // 启动监听
    // 连接请求队列  backlog
    virtual bool  start(int backlog=5) = 0;

    // 停止监听，关闭监听套接字
    virtual bool  stop(void) = 0;

    // 设置本地监听地址
    // 如果监听本地所有，则pszIP=0.0.0.0
    // 如果对已经Start好的listner调用这个函数，则
    // 需要Stop成功后，重新Start的时候才会使用这里设置的ip和端口
    // 设置成功返回true，否则返回false。如果当前listener没有Stop，则不能设置，返回false
    virtual bool set_remote_address(const char* pszIP, uint16 wPort)=0;

    // 设置本连接的网络数据的收发缓冲区长度
    // 如果对已经建立好的连接调用这个函数，则
    // 需要Stop这个监听后，重新Start成功后才会使用这里设置的缓冲区长度
    // 合法的设置返回true，否则返回false
    virtual bool set_data_buffer_size(uint32 dwRecvBufSize, uint32 dwSendBufSize)=0;
};


// IConnector 仅仅作为接口使用，不需要用户继承
// IConnector 指向的对象，拥有与进程相同的生命周期，用户不能手动销毁。
class IConnector
{
public:
    // 取得关联connector的session
    virtual ISession* get_session()=0;

    // 设置远程地址
    // 如果对已经建立好的连接调用这个函数，则
    // 需要关闭这个连接后，重新Connect的时候才会使用这里设置的ip和端口
    virtual void set_remote_address(const char* pszIP, uint16 wPort)=0;

    // 设置本连接的网络数据的收发缓冲区长度
    // 如果对已经建立好的连接调用这个函数，则
    // 需要关闭这个连接后，重新Connect成功后才会使用这里设置的缓冲区长度
    // 合法的设置返回true，否则返回false
    virtual bool set_data_buffer_size(uint32 dwRecvBufSize, uint32 dwSendBufSize)=0;

    // 设置自动重新连接的间隔 单位为毫秒。0xffffffff表示不自动重连
    // 如果对已经建立好的连接调用这个函数，则
    // 需要关闭这个连接后，重新Connect成功后才会使用这里自动重连设置
    virtual void set_auto_reconect_milsecond(uint32 dwAutoReconnectMilSecond = 0xffffffff)=0;

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


/*
*@brief 一个网络组件初始化需要的信息
*/
struct NetModuleCfg
{
    NetModuleCfg(){
        a_net_packet_max_size = 102 * 1024;
        net_packet_max_number = 10;
        all_net_packets_max_size = 16 * 102 * 1024;
        connection_pool_init_number = 1;
        connector_pool_init_number = 1;
        listener_pool_init_number = 1;
        net_event_pool_init_number = 100;
        net_req_pool_init_number = 100;
        connect_req_pool_init_number = 10;
        epoll_event_max_number = 100;
        net_recv_send_thread_number = 1;
    }
    uint32  a_net_packet_max_size;          //一个网络包的最大长度 (eg. 1024*64)
    uint32  net_packet_max_number;          //网络包缓冲池的个数,每个网络包的大少是 a_net_packet_max_size (eg.2),数量越多，越能减少取数据时加锁的次数。
    uint32  all_net_packets_max_size;       //接收该网络模块里所有连接的数据的网络缓冲区的最大长度 (eg. 1024*1024)，根据具体需要设置
    uint32  connection_pool_init_number;    //关联连接内存池初始化数量 (eg. 1000)
    uint32  connector_pool_init_number;     //主动连接内存池初始化数量 (eg. 10)
    uint32  listener_pool_init_number;      //监听者内存池初始化数量 (eg. 10)
    uint32  net_event_pool_init_number;     //网络事件内存池初始化数量 (eg. 1000)
    uint32  net_req_pool_init_number;       //网络请求（例如 SNetListenReq, SNetConnectReq）内存池初始化数量 (eg.1000)
    uint32  connect_req_pool_init_number;   //请求连接事件内存池初始化数量 (eg.100)
    uint32  epoll_event_max_number;         //如果使用了epoll网络模型，则要设置epoll最大监听值。max_fd_size
    uint32  net_recv_send_thread_number;    //网络收发线程的数量，具体数量应该根据CPU的数量而定
};


// INetModule 仅仅作为接口使用，不需要用户继承
class INetModule
{
public:
    /// 初始化网络资源、配置。
    virtual bool init(const NetModuleCfg& cfg)=0;

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
    virtual IConnector*  create_connector(ISession* pSession,
                                         uint32 dwRecvBufSize, 
                                         uint32 dwSendBufSize,
                                         const char* pszIP, 
                                         uint16 wPort,
                                         uint32 dwAutoReconnectMilSecond = 0xffffffff
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
    virtual IListener*  create_listener(ISessionFactory* pSessionFactory,
                                       uint32 dwRecvBufSize, 
                                       uint32 dwSendBufSize,
                                       const char* pszIP, 
                                       uint16 wPort, 
                                       bool bReUseAddr = true,
                                       ICheckIP* pCheck = NULL
                                       ) = 0;

    virtual bool  run() = 0;
};


// ISession 需要用户继承，派生自己需要的实现
class ISession
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 下面四个函数都是在用户处理网络网络数据的地方调用。
	// 传入的有效链接的指针 IConnection* 也只能在这个线程使用的时候，才是安全的

    // 当连接建立后，会回调该函数
	// 传入一个有效的链接指针
	// 用户自行保存这个指针
    virtual void  on_establish(IConnection* poConnection) = 0;

    // 当连接断开，会回调该函数
	// 传入一个 NULL 来使用用户原来保存有效连接指针无效
	// 用户必须使用传入的 参数， 为原来保存有效连接指针赋值，使其无效
    virtual void  on_terminate(IConnection* poConnection) = 0;

    // 当连接发生错误，会回调该函数
    virtual bool  on_error(int32 nModuleErr, int32 nSysErr) = 0;

    // 当收到网络数据包时，会回调。
    virtual void  on_recv(const char* pBuf, uint32 dwLen) = 0;
};

// ISessionFactory 需要用户继承，派生自己需要的实现
// 会话对象工厂器
// CreateSession, FreeSession 需要多线程安全
class ISessionFactory
{
public:
    // 创建一个会话对象. 用户只要实现这个接口，系统会自动调用它来分配
    virtual ISession*  create_session() = 0;
    // 回收一个回话对象。 用户只要实现这个接口，系统会自动调用它来释放
    virtual void free_session(ISession* pSession) = 0;
};

/// 返回指向网络模块对象的指针
INetModule* create_net_module();


}

#endif //__SHARE_NET_H__

