#ifndef __SHARE_DATA_BUFFER_H__
#define __SHARE_DATA_BUFFER_H__

#include "sh_common.h"
#include "sh_thread.h"
#include "sh_objpool.h"
#include "sh_ptrlist.h"

namespace share
{

class CDataBufferFactory
{
public:
    //typedef std::list<char*> LIST_POOL;
    typedef ptr_list LIST_POOL;

    void Init(UINT32 dwBufferSize);

    UINT32 GetElemBufferSize()const {return m_dwBufferSize;}

    char* Malloc();

    void Free(char* pBuf);

    CDataBufferFactory();
    ~CDataBufferFactory();

private:
    CDataBufferFactory(const CDataBufferFactory& );
    CDataBufferFactory& operator=(CDataBufferFactory&);

    UINT32                  m_dwBufferSize;
    CLock::CMutex           m_mutex;
    LIST_POOL               m_ListPool;
};

class CDataBufferFactoryMgr : public CSingleton<CDataBufferFactoryMgr>
{
public:
    struct Node
    {
        CDataBufferFactory* pFactory;
        UINT32              dwSize;
    };
    typedef std::list<Node> LIST_POOL_FACTORY;

    CDataBufferFactory* MallocDataBufferFactory(const UINT32 dwBufferSize);
    void FreeDataBufferFactory(CDataBufferFactory* pFactory);

    CDataBufferFactoryMgr();
    ~CDataBufferFactoryMgr();

private:
    LIST_POOL_FACTORY       m_FreeFactorys;
    LIST_POOL_FACTORY       m_UsingFactorys;
    CLock::CMutex           m_mutex;
};


}
#endif //__SHARE_TYPE_H__

