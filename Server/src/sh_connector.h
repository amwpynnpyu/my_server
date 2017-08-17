#ifndef __SHARE_CONNECTOR_H__
#define __SHARE_CONNECTOR_H__

#include "sh_net.h"


class CConnector : public sh::IConnector
{
public:
    CConnector();
    virtual ~CConnector();

    // ȡ�ù���connector��session
    virtual sh::ISession* get_session();

    // ����Զ�̵�ַ
    // ������Ѿ������õ����ӵ��������������
    // ��Ҫ�ر�������Ӻ�����Connect��ʱ��Ż�ʹ���������õ�ip�Ͷ˿�
    virtual void set_remote_address(const char* pszIP, sh::uint16 wPort);

    // ���ñ����ӵ��������ݵ��շ�����������
    // ������Ѿ������õ����ӵ��������������
    // ��Ҫ�ر�������Ӻ�����Connect�ɹ���Ż�ʹ���������õĻ���������
    // �Ϸ������÷���true�����򷵻�false
    virtual bool set_data_buffer_size(sh::uint32 dwRecvBufSize, sh::uint32 dwSendBufSize);

    // �����Զ��������ӵļ�� ��λΪ���롣0xffffffff��ʾ���Զ�����
    // ������Ѿ������õ����ӵ��������������
    // ��Ҫ�ر�������Ӻ�����Connect�ɹ���Ż�ʹ�������Զ���������
    virtual void set_auto_reconect_milsecond(sh::uint32 dwAutoReconnectMilSecond = 0xffffffff);

    // �������ӣ��첽���ӣ�
    // ���� Connect ��ʱ��ʹ��Ӧ��֤connector ��������Ч��
    virtual bool  connect();

    // �ֶ�������������
    // �ڴ���connector�߳� �������û������������̣߳���Ϊʹ����֪�� connector�� �������ڣ�
    // ����ʹ�ñ�֤���� ReConnect ��ʱ��connector ����Ч
    virtual bool  re_connect(void);

    // �յ�����Ͽ�����, ���ʹ������ӿڶϿ����ӣ�
    // ��ʹ�����Զ�������Ҳ���ᷢ���������ӣ����Ҫ�������ӣ�
    // �û������ֶ������������ӣ�������ReConnect�ӿ�
    // �ڴ���connector�߳� �������û������������̣߳���Ϊʹ����֪�� connector�� �������ڣ�
    // ����ʹ�ñ�֤���� Disconnect ��ʱ��connector ����Ч
    virtual void dis_connect();
};


#endif //__SHARE_CONNECTOR_H__