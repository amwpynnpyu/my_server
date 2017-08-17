#ifndef __SHARE_NET_MGR_H__
#define __SHARE_NET_MGR_H__

#include "sh_net.h"

class CConnection: public sh::IConnection
{
public:
    CConnection();
    virtual ~CConnection();

    //����Ƿ���������
    virtual bool  is_connected(void);

    // �����ӻ�����Ͷ�����ݣ�׼������
    // ע�⣺�޸��˷���ֵ��Ͷ�ݵ����ͻ������ɹ�������true�����򷵻�false
    // �ȴ� pBuf ָ��ĵ�ַȡ dwLen ���ȵ����ݣ������ pExBuf���ڴ� pExBuf ָ��ĵ�ַȡ dwExLen ���ȵ�����
    // ��ϳ�һ��������ݰ�����
    virtual bool  send(const char* pBuf, sh::uint32 dwLen, const char* pExBuf = NULL, sh::uint32 dwExLen = 0);

    // ֱ�ӷ��ͻ������ݣ��������壬Ҳ�������ݳ���ͷ����ʹ��ʹ��Send����ʹ��RawSend��Ҳ�п���RawSend�Ȱ����ݷ��ͳ�ȥ������!
    virtual sh::int32 raw_send(const char* pBuf, sh::int32 nLen);

    // �Ͽ�����
    virtual void  dis_connect(void);

    // �������Զ�˵�ַ32λ����ֵ
    virtual const sh::uint32  get_remote_ip(void);

    // �������Զ�˵�ַIP��ʽ���ַ�����ַ
    virtual const char*  get_remote_ip_str(void);

    // ����Զ�˵�ַ�˿�
    virtual sh::uint16  get_remote_port(void);

    // ������ӱ��ص�ַ32λ����ֵ
    virtual const sh::uint32  get_local_ip(void);

    // ������ӱ��ص�ַIP��ʽ���ַ�����ַ
    virtual const char*  get_local_ip_str(void);

    // ������ӱ��ص�ַ�˿�
    virtual sh::uint16  get_local_port(void);
};

class CListener : public sh::IListener
{
public:
    CListener();
    virtual ~CListener();

    // ��������
    // �����������  backlog
    virtual bool  start(int backlog = 5) = 0;

    // ֹͣ�������رռ����׽���
    virtual bool  stop(void) = 0;

    // ���ñ��ؼ�����ַ
    // ��������������У���pszIP=0.0.0.0
    // ������Ѿ�Start�õ�listner���������������
    // ��ҪStop�ɹ�������Start��ʱ��Ż�ʹ���������õ�ip�Ͷ˿�
    // ���óɹ�����true�����򷵻�false�������ǰlistenerû��Stop���������ã�����false
    virtual bool set_remote_address(const char* pszIP, sh::uint16 wPort) = 0;

    // ���ñ����ӵ��������ݵ��շ�����������
    // ������Ѿ������õ����ӵ��������������
    // ��ҪStop�������������Start�ɹ���Ż�ʹ���������õĻ���������
    // �Ϸ������÷���true�����򷵻�false
    virtual bool set_data_buffer_size(sh::uint32 dwRecvBufSize, sh::uint32 dwSendBufSize) = 0;
};


class CConnector : public sh::IConnector
{
public:
    CConnector();
    virtual ~CConnector();

    // ȡ�ù���connector��session
    virtual sh::ISession* get_session() = 0;

    // ����Զ�̵�ַ
    // ������Ѿ������õ����ӵ��������������
    // ��Ҫ�ر�������Ӻ�����Connect��ʱ��Ż�ʹ���������õ�ip�Ͷ˿�
    virtual void set_remote_address(const char* pszIP, sh::uint16 wPort) = 0;

    // ���ñ����ӵ��������ݵ��շ�����������
    // ������Ѿ������õ����ӵ��������������
    // ��Ҫ�ر�������Ӻ�����Connect�ɹ���Ż�ʹ���������õĻ���������
    // �Ϸ������÷���true�����򷵻�false
    virtual bool set_data_buffer_size(sh::uint32 dwRecvBufSize, sh::uint32 dwSendBufSize) = 0;

    // �����Զ��������ӵļ�� ��λΪ���롣0xffffffff��ʾ���Զ�����
    // ������Ѿ������õ����ӵ��������������
    // ��Ҫ�ر�������Ӻ�����Connect�ɹ���Ż�ʹ�������Զ���������
    virtual void set_auto_reconect_milsecond(sh::uint32 dwAutoReconnectMilSecond = 0xffffffff) = 0;

    // �������ӣ��첽���ӣ�
    // ���� Connect ��ʱ��ʹ��Ӧ��֤connector ��������Ч��
    virtual bool  connect() = 0;

    // �ֶ�������������
    // �ڴ���connector�߳� �������û������������̣߳���Ϊʹ����֪�� connector�� �������ڣ�
    // ����ʹ�ñ�֤���� ReConnect ��ʱ��connector ����Ч
    virtual bool  re_connect(void) = 0;

    // �յ�����Ͽ�����, ���ʹ������ӿڶϿ����ӣ�
    // ��ʹ�����Զ�������Ҳ���ᷢ���������ӣ����Ҫ�������ӣ�
    // �û������ֶ������������ӣ�������ReConnect�ӿ�
    // �ڴ���connector�߳� �������û������������̣߳���Ϊʹ����֪�� connector�� �������ڣ�
    // ����ʹ�ñ�֤���� Disconnect ��ʱ��connector ����Ч
    virtual void dis_connect() = 0;
};

class CNetModule : public sh::INetModule
{
public:
    CNetModule();
    virtual ~CNetModule();

    /// ��ʼ��������Դ�����á�
    virtual bool init(const sh::NetModuleCfg& cfg) = 0;

    /// �ͷ�����ģ��
    virtual void release() = 0;

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
        ) = 0;

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
        ) = 0;

    virtual bool  run() = 0;
};

// ISession ��Ҫ�û��̳У������Լ���Ҫ��ʵ��
class CSession: public sh::ISession
{
public:
    CSession();
    virtual ~CSession();

    //////////////////////////////////////////////////////////////////////////
    // �����ĸ������������û����������������ݵĵط����á�
    // �������Ч���ӵ�ָ�� IConnection* Ҳֻ��������߳�ʹ�õ�ʱ�򣬲��ǰ�ȫ��

    // �����ӽ����󣬻�ص��ú���
    // ����һ����Ч������ָ��
    // �û����б������ָ��
    virtual void  on_establish(sh::IConnection* poConnection) = 0;

    // �����ӶϿ�����ص��ú���
    // ����һ�� NULL ��ʹ���û�ԭ��������Ч����ָ����Ч
    // �û�����ʹ�ô���� ������ Ϊԭ��������Ч����ָ�븳ֵ��ʹ����Ч
    virtual void  on_terminate(sh::IConnection* poConnection) = 0;

    // �����ӷ������󣬻�ص��ú���
    virtual bool  on_error(sh::int32 nModuleErr, sh::int32 nSysErr) = 0;

    // ���յ��������ݰ�ʱ����ص���
    virtual void  on_recv(const char* pBuf, sh::uint32 dwLen) = 0;
};

// ISessionFactory ��Ҫ�û��̳У������Լ���Ҫ��ʵ��
// �Ự���󹤳���
// CreateSession, FreeSession ��Ҫ���̰߳�ȫ
class CSessionFactory : public sh::ISessionFactory
{
public:
    CSessionFactory();
    virtual ~CSessionFactory();

    // ����һ���Ự����. �û�ֻҪʵ������ӿڣ�ϵͳ���Զ�������������
    virtual sh::ISession*  create_session() = 0;
    // ����һ���ػ����� �û�ֻҪʵ������ӿڣ�ϵͳ���Զ����������ͷ�
    virtual void free_session(sh::ISession* pSession) = 0;
};

#endif //__SHARE_NET_MGR_H__