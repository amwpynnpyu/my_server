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

    //把pData指向的数据，压入管道内存
    bool PushData(const char* pData, UINT32 dwLen);

    //把管道内存的数据copy到 pBuf指向的缓冲区
    bool PopData(char* pBuf, UINT32 dwLen);

    //当前管道的数据，从头向后，移除dwLen长度字节
    void RemoveData(UINT32 dwLen);

private:
    char*   m_pBuf;
    char*   m_pHead;
    char*   m_pTail;
    UINT32  m_dwSize;
};
}

#endif //__SHARE_LOOP_BUFFER_H__

