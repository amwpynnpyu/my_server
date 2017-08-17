#ifndef __SHARE_LOOP_BUFFER_H__
#define __SHARE_LOOP_BUFFER_H__

#include "sh_type.h"
#include "sh_include.h"
#include "sh_define.h"
#include "sh_common.h"


namespace share
{

class CLoopBuffer : public noncopyable
{
public:
    CLoopBuffer();
    ~CLoopBuffer();

    bool Init(UINT32 dwBufferSize);

    //��pDataָ������ݣ�ѹ��ܵ��ڴ�
    bool PushData(const char* pData, UINT32 dwLen);

    //�ѹܵ��ڴ������copy�� pBufָ��Ļ�����
    bool PopData(char* pBuf, UINT32 dwLen);

    //��ǰ�ܵ������ݣ���ͷ����Ƴ�dwLen�����ֽ�
    void RemoveData(UINT32 dwLen);

private:
    char*   m_pBuf;
    char*   m_pHead;
    char*   m_pTail;
    UINT32  m_dwSize;
};
}

#endif //__SHARE_LOOP_BUFFER_H__

