#pragma once

#include <mutex>
#include "macro.h"

namespace loopxia
{
    class MutexImpl;
    class Mutex
    {
        LOOPXIA_NONCOPYABLE(Mutex);

        friend class LockGuard;

    public:
        Mutex();
        ~Mutex();
        void Lock();
        void Unlock();

    private:
        mutable MutexImpl* m_pMutex;
    };

    class LockGuard
    {
    public:
        LockGuard(Mutex& m) : m_mutex(&m)
        {
            m_mutex->Lock();
        }

        ~LockGuard()
        {
            m_mutex->Unlock();
        }

    private:
        Mutex* m_mutex;
    };
}
