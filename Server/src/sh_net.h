#ifndef __SHARE_NET_H__
#define __SHARE_NET_H__

#include "sh_type.h"
#include "sh_define.h"

#define NET_USE_TENG_XU_TGW 

namespace sh
{
//////////////////////////////////////////////////////////////////////////
/// ����ģ��
//////////////////////////////////////////////////////////////////////////

enum E_NET_ERROR
{
    NET_SUCCESS  = 0,
    NET_NO_ERROR = NET_SUCCESS,     /// û�д���
    NET_SEND_ERROR,                 /// ���ʹ���
    NET_RECEIVE_ERROR,              /// ���մ���
    NET_SEND_BUFFER_OVERFLOW,       /// ���ͻ��������
    NET_RECEIVE_BUFFER_OVERFLOW,    /// ���ջ��������
    NET_CONNECTION_CLOSE,           /// �����Ѿ��ر�
    NET_SEND_BUFFER_NULL,           /// ���ͻ�����Ϊ��
    NET_RECEIVE_BUFFER_NULL,        /// ���ջ�����Ϊ��
    NET_CONNECT_FAIL,               /// ����ʧ��
    NET_CONNECT_TIMEOUT,            /// ���ӳ�ʱ
    NET_CONNECTION_HAS_DISCONNECTED,/// �����Ѿ��Ͽ�
    NET_BIND_FAIL,                  /// ��ʧ��
    NET_LISTEN_FAIL,                /// ����ʧ��
    NET_INVAL_CONNECTIONID,         /// ���������id
    NET_INVAL_CONNECTION,           /// ���������
    NET_INVAL_SESSIONID,            /// ����Ựid
    NET_SESSION_NULL,               /// �����session
    NET_SERVER_ADDRESS_FAIL,        /// ����ķ�������ַ
    NET_SEND_OR_RECV_BUFFER_SIZE_FAIL, ///����ķ��ͻ���ջ�������С
    NET_REQ_SOCKET_FAIL,            /// �����׽��ִ���
    NET_INIT_SEND_RECV_BUFFER_FACTORY_FAIL, /// ��ʼ���շ�����������ʧ��
    NET_HAS_CONNECTED,              // ���������У������Ҫ�µ����ӣ����ȶϿ���ǰ���ӣ��ٳ���
    NET_HAS_LISTEN,                 //���������У������Ҫ���¼���������ֹͣ��ǰ����,�ٳ���
    NET_ADD_POLL_EVENT_FAIL,        /// ���epoll�¼�ʧ��

    NET_BIG_RECV_BUFFER_PIPE_INIT_FAIL,  //������ջ�������ʼ��ʧ��
    NET_BIG_RECV_BUFFER_PIPE_OVERFLOW,  //������ջ��������
    NET_BIG_RECV_BUFFER_PIP_READ_FAIL,  //�����绺������ȡ����ʧ��

    NET_FIRST_RECV_TGW_ERROR,  //�׸����ݰ������㹻�����ǽ�������TGW��ͷ
    
    NET_RECV_HEAD_ERROR, /// �յ����������ײ����ȶ�����
    NET_TOO_LARGE_PACKET, /// һ�����ݰ��ĳ���̫���ˡ�������std::numeric_limits<int32>::max)()

    SYS_MEMORY_ERROR = 20000,       /// ϵͳ�ڴ治��
    SYS_OTHRE_ERROR,                /// ϵͳ��������

    NET_NET_ERROR_MAX_ERRORCODE,    ///��������ֵ
};

/// ����E_NET_ERROR�����룬���ض�Ӧ�Ĵ�����Ϣ
extern const char* get_net_error_msg(E_NET_ERROR errcode);

typedef uint32  ID_TYPE; //id������

class INetModule;
class ISession;
class ISessionFactory;
class ICheckIP;


// IConnection ������Ϊ�ӿ�ʹ�ã�����Ҫ�û��̳�
class IConnection
{
public:
    //����Ƿ���������
    virtual bool  is_connected(void) = 0;

    // �����ӻ�����Ͷ�����ݣ�׼������
    // ע�⣺�޸��˷���ֵ��Ͷ�ݵ����ͻ������ɹ�������true�����򷵻�false
    // �ȴ� pBuf ָ��ĵ�ַȡ dwLen ���ȵ����ݣ������ pExBuf���ڴ� pExBuf ָ��ĵ�ַȡ dwExLen ���ȵ�����
    // ��ϳ�һ��������ݰ�����
    virtual bool  send(const char* pBuf,uint32 dwLen, const char* pExBuf=NULL, uint32 dwExLen=0) = 0;

    // ֱ�ӷ��ͻ������ݣ��������壬Ҳ�������ݳ���ͷ����ʹ��ʹ��Send����ʹ��RawSend��Ҳ�п���RawSend�Ȱ����ݷ��ͳ�ȥ������!
    virtual int32 raw_send(const char* pBuf,int32 nLen)=0;

    // �Ͽ�����
    virtual void  dis_connect(void) = 0;

    // �������Զ�˵�ַ32λ����ֵ
    virtual const uint32  get_remote_ip(void) = 0;

    // �������Զ�˵�ַIP��ʽ���ַ�����ַ
    virtual const char*  get_remote_ip_str(void) = 0;

    // ����Զ�˵�ַ�˿�
    virtual uint16  get_remote_port(void) = 0;

    // ������ӱ��ص�ַ32λ����ֵ
    virtual const uint32  get_local_ip(void) = 0;

    // ������ӱ��ص�ַIP��ʽ���ַ�����ַ
    virtual const char*  get_local_ip_str(void) = 0;

    // ������ӱ��ص�ַ�˿�
    virtual uint16  get_local_port(void) = 0;
};

/*
*@brief У�����ӵ�IP�Ƿ�Ϸ�
*/
class ICheckIP
{
public:
    //����������ip������true�����򷵻�false
    virtual bool check_ip(const char* pszIP)=0;
};

// IListener ������Ϊ�ӿ�ʹ�ã�����Ҫ�û��̳�
// IListener ָ��Ķ���ӵ���������ͬ���������ڣ��û������ֶ����١�
class IListener
{
public:
#ifdef NET_USE_TENG_XU_TGW
    // ���ü�����ÿ�����Ӻ��Ե�һ�� tgw��ͷ
    virtual void ignore_tgw(void)=0;
#endif
    // ��������
    // �����������  backlog
    virtual bool  start(int backlog=5) = 0;

    // ֹͣ�������رռ����׽���
    virtual bool  stop(void) = 0;

    // ���ñ��ؼ�����ַ
    // ��������������У���pszIP=0.0.0.0
    // ������Ѿ�Start�õ�listner���������������
    // ��ҪStop�ɹ�������Start��ʱ��Ż�ʹ���������õ�ip�Ͷ˿�
    // ���óɹ�����true�����򷵻�false�������ǰlistenerû��Stop���������ã�����false
    virtual bool set_remote_address(const char* pszIP, uint16 wPort)=0;

    // ���ñ����ӵ��������ݵ��շ�����������
    // ������Ѿ������õ����ӵ��������������
    // ��ҪStop�������������Start�ɹ���Ż�ʹ���������õĻ���������
    // �Ϸ������÷���true�����򷵻�false
    virtual bool set_data_buffer_size(uint32 dwRecvBufSize, uint32 dwSendBufSize)=0;
};


// IConnector ������Ϊ�ӿ�ʹ�ã�����Ҫ�û��̳�
// IConnector ָ��Ķ���ӵ���������ͬ���������ڣ��û������ֶ����١�
class IConnector
{
public:
    // ȡ�ù���connector��session
    virtual ISession* get_session()=0;

    // ����Զ�̵�ַ
    // ������Ѿ������õ����ӵ��������������
    // ��Ҫ�ر�������Ӻ�����Connect��ʱ��Ż�ʹ���������õ�ip�Ͷ˿�
    virtual void set_remote_address(const char* pszIP, uint16 wPort)=0;

    // ���ñ����ӵ��������ݵ��շ�����������
    // ������Ѿ������õ����ӵ��������������
    // ��Ҫ�ر�������Ӻ�����Connect�ɹ���Ż�ʹ���������õĻ���������
    // �Ϸ������÷���true�����򷵻�false
    virtual bool set_data_buffer_size(uint32 dwRecvBufSize, uint32 dwSendBufSize)=0;

    // �����Զ��������ӵļ�� ��λΪ���롣0xffffffff��ʾ���Զ�����
    // ������Ѿ������õ����ӵ��������������
    // ��Ҫ�ر�������Ӻ�����Connect�ɹ���Ż�ʹ�������Զ���������
    virtual void set_auto_reconect_milsecond(uint32 dwAutoReconnectMilSecond = 0xffffffff)=0;

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


/*
*@brief һ�����������ʼ����Ҫ����Ϣ
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
    uint32  a_net_packet_max_size;          //һ�����������󳤶� (eg. 1024*64)
    uint32  net_packet_max_number;          //���������صĸ���,ÿ��������Ĵ����� a_net_packet_max_size (eg.2),����Խ�࣬Խ�ܼ���ȡ����ʱ�����Ĵ�����
    uint32  all_net_packets_max_size;       //���ո�����ģ�����������ӵ����ݵ����绺��������󳤶� (eg. 1024*1024)�����ݾ�����Ҫ����
    uint32  connection_pool_init_number;    //���������ڴ�س�ʼ������ (eg. 1000)
    uint32  connector_pool_init_number;     //���������ڴ�س�ʼ������ (eg. 10)
    uint32  listener_pool_init_number;      //�������ڴ�س�ʼ������ (eg. 10)
    uint32  net_event_pool_init_number;     //�����¼��ڴ�س�ʼ������ (eg. 1000)
    uint32  net_req_pool_init_number;       //������������ SNetListenReq, SNetConnectReq���ڴ�س�ʼ������ (eg.1000)
    uint32  connect_req_pool_init_number;   //���������¼��ڴ�س�ʼ������ (eg.100)
    uint32  epoll_event_max_number;         //���ʹ����epoll����ģ�ͣ���Ҫ����epoll������ֵ��max_fd_size
    uint32  net_recv_send_thread_number;    //�����շ��̵߳���������������Ӧ�ø���CPU����������
};


// INetModule ������Ϊ�ӿ�ʹ�ã�����Ҫ�û��̳�
class INetModule
{
public:
    /// ��ʼ��������Դ�����á�
    virtual bool init(const NetModuleCfg& cfg)=0;

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
    virtual IConnector*  create_connector(ISession* pSession,
                                         uint32 dwRecvBufSize, 
                                         uint32 dwSendBufSize,
                                         const char* pszIP, 
                                         uint16 wPort,
                                         uint32 dwAutoReconnectMilSecond = 0xffffffff
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


// ISession ��Ҫ�û��̳У������Լ���Ҫ��ʵ��
class ISession
{
public:
	//////////////////////////////////////////////////////////////////////////
	// �����ĸ������������û����������������ݵĵط����á�
	// �������Ч���ӵ�ָ�� IConnection* Ҳֻ��������߳�ʹ�õ�ʱ�򣬲��ǰ�ȫ��

    // �����ӽ����󣬻�ص��ú���
	// ����һ����Ч������ָ��
	// �û����б������ָ��
    virtual void  on_establish(IConnection* poConnection) = 0;

    // �����ӶϿ�����ص��ú���
	// ����һ�� NULL ��ʹ���û�ԭ��������Ч����ָ����Ч
	// �û�����ʹ�ô���� ������ Ϊԭ��������Ч����ָ�븳ֵ��ʹ����Ч
    virtual void  on_terminate(IConnection* poConnection) = 0;

    // �����ӷ������󣬻�ص��ú���
    virtual bool  on_error(int32 nModuleErr, int32 nSysErr) = 0;

    // ���յ��������ݰ�ʱ����ص���
    virtual void  on_recv(const char* pBuf, uint32 dwLen) = 0;
};

// ISessionFactory ��Ҫ�û��̳У������Լ���Ҫ��ʵ��
// �Ự���󹤳���
// CreateSession, FreeSession ��Ҫ���̰߳�ȫ
class ISessionFactory
{
public:
    // ����һ���Ự����. �û�ֻҪʵ������ӿڣ�ϵͳ���Զ�������������
    virtual ISession*  create_session() = 0;
    // ����һ���ػ����� �û�ֻҪʵ������ӿڣ�ϵͳ���Զ����������ͷ�
    virtual void free_session(ISession* pSession) = 0;
};

/// ����ָ������ģ������ָ��
INetModule* create_net_module();


}

#endif //__SHARE_NET_H__

