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

private:
    CSocket   m_socket;
};


#endif //__SHARE_WIN_SOCK_H__