#ifndef __SHARE_OJB_POOL_EX_H__
#define __SHARE_OJB_POOL_EX_H__

#include "sh_ptrlist.h"

namespace share
{

template <typename T>
class CDynamicObjectPool
{
public:
    CDynamicObjectPool()
    {
        m_pmutex = NULL;
        m_last_error_no = POOL_NO_ERROR;
        m_elem_count = 0;
    }

    explicit CDynamicObjectPool(bool bmutex)
    {
        m_pmutex = NULL;
        m_last_error_no = POOL_NO_ERROR;
        m_elem_count = 0;
        if (bmutex)
        {
            set_mutex();
        }
    }

    ~CDynamicObjectPool()
    {
        release_free_elem(0);
        delete m_pmutex;
        m_pmutex = NULL;
    }

    bool set_mutex()
    {
        if (NULL == m_pmutex)
        {
            m_pmutex = new(std::nothrow)CLock::CMutex();
        }
        if (NULL == m_pmutex)
        {
            m_last_error_no = POOL_NOT_ENOUGH_MEMORY;
            return false;
        }
        return true;
    }

    T* malloc()
    {
        T* p = _mutex_malloc();
        if (NULL == p)return p;
        new(p)T; //调用构造函数 
        return p;
    }

    template<typename T1>
    T* malloc(T1 t1)
    {
        T* p = _mutex_malloc();
        if (NULL == p)return p;
        new(p)T(t1);
        return p;
    }

    template<typename T1, typename T2>
    T* malloc(T1 t1, T2 t2)
    {
        T* p = _mutex_malloc();
        if (NULL == p)return p;
        new(p)T(t1);
        return p;
    }

    template<typename T1, typename T2, typename T3>
    T* malloc(T1 t1, T2 t2, T3 t3)
    {
        T* p = _mutex_malloc();
        if (NULL == p)return p;
        new(p)T(t1, t2, t3);
        return p;
    }

    template<typename T1, typename T2, typename T3, typename T4>
    T* malloc(T1 t1, T2 t2, T3 t3, T4 t4)
    {
        T* p = _mutex_malloc();
        if (NULL == p)return p;
        new(p)T(t1, t2, t3, t4);
        return p;
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    T* malloc(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
    {
        T* p = _mutex_malloc();
        if (NULL == p)return p;
        new(p)T(t1, t2, t3, t4, t5);
        return p;
    }

    //想要支持更多的参数，就自己加吧! ^_^ 
    //... 


    void free(T* pt)
    {
        if (NULL == pt)
        {
            m_last_error_no = POOL_FREE_NULL_POINTER;
            return;
        }
        pt->~T();

        if (NULL != m_pmutex)
        {
            CLock lock(*m_pmutex);
            _free(pt);
        }
        else
        {
            _free(pt);
        }
    }

    // 释放空闲对象, 如果n=0，释放所有的空闲，否则尽量释放n个空闲对象
    // 返回实际释放空闲对象的数量
    UINT32 release_free_elem(UINT32 n=0)
    {
        UINT32 free_num = n > 0 ? n : 0xffffffff;
        if (NULL != m_pmutex)
        {
            CLock lock(*m_pmutex);
            return _release_free_elem(free_num);
        }
        else
        {
            return _release_free_elem(free_num);
        }
    }

    MEMORY_POOL_ERROR_NO get_last_error_no() 
    {
        return m_last_error_no;
    }

    void reset_last_error_no() 
    {
        m_last_error_no = POOL_NO_ERROR;
    }

    UINT32 get_using_elem_number()
    {
        return m_elem_count;
    }

    UINT32 get_free_elem_number()
    {
        return m_free_ojb_list.size();
    }

private:
    T* _mutex_malloc()
    {
        if (NULL != m_pmutex)
        {
            CLock lock(*m_pmutex);
            return _malloc();
        }
        else
        {
            return _malloc();
        }
    }

    void _free(T* pt)
    {
        m_free_ojb_list.push_back(pt);
        --m_elem_count;
    }

    T* _malloc()
    {
        if (m_free_ojb_list.size() > 0)
        {
            ++m_elem_count;
            return (T*) m_free_ojb_list.pop_front();
        }
        else
        {
            T* pnew = (T*)::malloc(sizeof(T));
            if (NULL != pnew) ++m_elem_count;
            return pnew;
        }
    }

    UINT32 _release_free_elem(UINT32 n=0)
    {
        UINT32 i=0;
        for (; i<n && m_free_ojb_list.size() >0 ; ++i)
        {
            T* p = (T*)m_free_ojb_list.pop_front();
            ::free(p);
        }
        return i;
    }

private:
    //ptr_list        m_using_ojb_list;
    ptr_list        m_free_ojb_list;
    UINT32          m_elem_count;
    CLock::CMutex*	m_pmutex;
    UINT32          m_last_error_no;

};

}
#endif //__SHARE_OJB_POOL_EX_H__

