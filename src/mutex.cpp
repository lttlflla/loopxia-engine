#include "loopxia/mutex.h"
#include <absl/synchronization/mutex.h>

namespace loopxia
{
    class MutexImpl
    {
    public:
        void Lock()
        {
            m_mutex.Lock();
        }

        void Unlock()
        {
            m_mutex.Unlock();
        }

    private:
        mutable absl::Mutex m_mutex;
    };

    Mutex::Mutex() : m_pMutex(new MutexImpl)
    {
    }

    Mutex::~Mutex()
    {
        delete m_pMutex;
    }

    void Mutex::Lock()
    {
        m_pMutex->Lock();
    }

    void Mutex::Unlock()
    {
        m_pMutex->Unlock();
    }
}
    