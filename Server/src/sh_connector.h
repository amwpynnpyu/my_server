#ifndef __SHARE_CONNECTOR_H__
#define __SHARE_CONNECTOR_H__

#include "sh_net.h"


class CConnector : public sh::IConnector
{
public:
    CConnector();
    virtual ~CConnector();

    // 取得关联connector的session
    virtual sh::ISession* get_session();

    // 设置远程地址
    // 如果对已经建立好的连接调用这个函数，则
    // 需要关闭这个连接后，重新Connect的时候才会使用这里设置的ip和端口
    virtual void set_remote_address(const char* pszIP, sh::uint16 wPort);

    // 设置本连接的网络数据的收发缓冲区长度
    // 如果对已经建立好的连接调用这个函数，则
    // 需要关闭这个连接后，重新Connect成功后才会使用这里设置的缓冲区长度
    // 合法的设置返回true，否则返回false
    virtual bool set_data_buffer_size(sh::uint32 dwRecvBufSize, sh::uint32 dwSendBufSize);

    // 设置自动重新连接的间隔 单位为毫秒。0xffffffff表示不自动重连
    // 如果对已经建立好的连接调用这个函数，则
    // 需要关闭这个连接后，重新Connect成功后才会使用这里自动重连设置
    virtual void set_auto_reconect_milsecond(sh::uint32 dwAutoReconnectMilSecond = 0xffffffff);

    // 发起连接（异步连接）
    // 调用 Connect 的时候，使用应保证connector 对象还是有效的
    virtual bool  connect();

    // 手动发起重新连接
    // 在创建connector线程 或者是用户创建的其他线程，因为使用者知道 connector的 生命周期，
    // 所以使用保证调用 ReConnect 的时候，connector 是有效
    virtual bool  re_connect(void);

    // 收到发起断开连接, 如果使用这个接口断开连接，
    // 即使设置自动重连，也不会发起重新连接，如果要重新连接，
    // 用户必须手动发起重新连接，即调用ReConnect接口
    // 在创建connector线程 或者是用户创建的其他线程，因为使用者知道 connector的 生命周期，
    // 所以使用保证调用 Disconnect 的时候，connector 是有效
    virtual void dis_connect();
};


#endif //__SHARE_CONNECTOR_H__