#ifndef __SHARE_WIN_IOCP_H__
#define __SHARE_WIN_IOCP_H__

#include "sh_net.h"
#include "sh_common.h"

class CWinIocpModule : public sh::INetModule, public sh::noncopyable
{
public:
    CWinIocpModule();
    virtual ~CWinIocpModule();

    /// ��ʼ��������Դ�����á�
    virtual bool init(const sh::NetModuleCfg& cfg);

    /// �ͷ�����ģ��
    virtual void release();

    /**
    * @brief pSession��connector�����ĻỰ����,
    *  NetModuleϵͳ�������Զ�����pSessionָ��Ķ��󣬶��ǵ���������connector,
    *  �����������ں��û��Լ�������ա�
    * @param pSession ָ����connector�����ĻỰ����
    * @param dwRecvBufSize  ���ӵĽ��ջ�����
    * @param dwSendBufSize  ���ӵķ��ͻ�����
    * @param pszIP  Զ�˷�����IP
    * @param wPort  Զ�˷����������˿�
    * @param dwAutoReconnectMilSecond �����Զ��������ӵļ������λΪ���롣0xffffffff��ʾ���Զ�����
    * @return �ɹ�����һ��ָ��Connector�����ָ�룬���򷵻� NULL
    * @note CreateConnector �����Ķ���ӵ���������ͬ���������ڣ��ڽ��������ڼ䣬����������
    */
    virtual sh::IConnector*  create_connector(sh::ISession* pSession,
        sh::uint32 dwRecvBufSize,
        sh::uint32 dwSendBufSize,
        const char* pszIP,
        sh::uint16 wPort,
        sh::uint32 dwAutoReconnectMilSecond = 0xffffffff
        );

    /**
    * @brief pSessionFactory��ΪListenner�ṩsession����,
    *  �����������ӹرպ�listenner ���������ʼ��ʱ�󶨵�pSessionFactory,
    *  ��FreeSession������������������ӹ�����session,sessionfactory ��� FreeSession Ҳ���û�ʵ��
    * @param pSessionFactory ָ����connector�����ĻỰ����
    * @param dwRecvBufSize  ���ӵĽ��ջ�����
    * @param dwSendBufSize  ���ӵķ��ͻ�����
    * @param pszIP  ������IP��ַ
    * @param wPort  �����˿�
    * @param bReUseAddr �Ƿ��õ�ַ�� Ĭ��true bReUseAddr �Ѽ����׽�������ΪSOL_SOCKET��SO_REUSEADDR
    * @param pCheck ����У����������IP�Ƿ�Ϸ��ķ�����Ϊ����ǽ���ã� Ĭ��NULL
    * @return �ɹ�����һ��ָ��IListener�����ָ�룬���򷵻� NULL
    * @note CreateListener �����Ķ���ӵ���������ͬ���������ڣ��ڽ��������ڼ䣬����������
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