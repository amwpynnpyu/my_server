#ifndef __SHARE_LISTENER_H__
#define __SHARE_LISTENER_H__

#include "sh_net.h"

class CListener : public sh::IListener
{
public:
    CListener();
    virtual ~CListener();

    // ��������
    // �����������  backlog
    virtual bool  start(int backlog = 5);

    // ֹͣ�������رռ����׽���
    virtual bool  stop(void);

    // ���ñ��ؼ�����ַ
    // ��������������У���pszIP=0.0.0.0
    // ������Ѿ�Start�õ�listner���������������
    // ��ҪStop�ɹ�������Start��ʱ��Ż�ʹ���������õ�ip�Ͷ˿�
    // ���óɹ�����true�����򷵻�false�������ǰlistenerû��Stop���������ã�����false
    virtual bool set_remote_address(const char* pszIP, sh::uint16 wPort);

    // ���ñ����ӵ��������ݵ��շ�����������
    // ������Ѿ������õ����ӵ��������������
    // ��ҪStop�������������Start�ɹ���Ż�ʹ���������õĻ���������
    // �Ϸ������÷���true�����򷵻�false
    virtual bool set_data_buffer_size(sh::uint32 dwRecvBufSize, sh::uint32 dwSendBufSize);
};




#endif //__SHARE_LISTENER_H__