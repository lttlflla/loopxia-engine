#pragma once

#include <vector>
#include <functional>
#include <memory>
#include <map>
#include <unordered_map>
#include <variant>
#include <chrono>
#include "mutex.h"

namespace loopxia
{
    class EventConnectionImpl
    {
        typedef std::function<void()> func;
        typedef std::function<bool()> checkConnectedFunc;
    public:
        EventConnectionImpl(func connectCall, func disconnectCall, func destroyCall, checkConnectedFunc checkConnect) :
            m_connect(connectCall)
            , m_disconnect(disconnectCall)
            , m_destroy(destroyCall)
            , m_checkConnected(checkConnect)
        {
        }

        ~EventConnectionImpl()
        {
            m_destroy();
        }

        // reconnect
        void Connect()
        {
            m_connect();
        }

        // temporary disconnect
        void Disconnect()
        {
            m_disconnect();
        }

        // distroy the callback
        void Destroy()
        {
            m_destroy();
        }

        bool IsConnected()
        {
            return m_checkConnected();
        }

    private:
        bool m_bIsConnected;
        func m_disconnect;
        func m_connect;
        func m_destroy;
        checkConnectedFunc m_checkConnected;
    };

    class EventConnection
    {
    public:
        EventConnection()
        {
        }

        EventConnection(std::shared_ptr<EventConnectionImpl> impl) : m_impl(impl)
        {
        }

        ~EventConnection()
        {
        }

        // reconnect
        void Connect()
        {
            if (!m_impl) {
                return;
            }

            m_impl->Connect();
        }

        // temporary disconnect
        void Disconnect()
        {
            if (!m_impl) {
                return;
            }

            m_impl->Disconnect();
        }

        // distroy the callback
        void Destroy()
        {
            if (!m_impl) {
                return;
            }

            m_impl->Destroy();
        }

        bool IsConnected()
        {
            if (!m_impl) {
                return false;
            }

            return m_impl->IsConnected();
        }

    private:
        std::shared_ptr<EventConnectionImpl> m_impl;
    };


    template <class ... Args>
    class EventSignal
    {
    public:
        typedef std::function<bool(Args...)> Slot;

        struct SlotEntry
        {
            Slot slot;
            int priority;
            int slotId;
        };

        struct SlotEntryHash
        {
            std::size_t operator()(const SlotEntry& c) const
            {
                return c.slotId;
            }
        };

        bool CmpSlotEntry(SlotEntry const& lhs, SlotEntry const& rhs)
        {
            return lhs.slotId < rhs.slotId;
        }

        EventSignal() : m_impl(new EventSignalImpl)
        {
        }

        EventSignal(const EventSignal<Args...>&) = delete;

        EventConnection connect(Slot const& callback)
        {
            LockGuard l(m_impl->m_cs);
            const int defaultPriority = 100;
            SlotEntry entry;
            entry.slot = callback;
            entry.slotId = m_impl->_GenerateNextSlotId();
            entry.priority = defaultPriority;
            m_impl->m_callbacks.insert(std::pair{defaultPriority, entry});
            return GenerateEventConnection(entry.slotId);
        }

        EventConnection connect(int priority, Slot const& callback)
        {
            LockGuard l(m_impl->m_cs);
            SlotEntry entry;
            entry.slot = callback;
            entry.slotId = m_impl->_GenerateNextSlotId();
            entry.priority = priority;
            m_impl->m_callbacks.insert(std::pair{priority, entry});
            return GenerateEventConnection(entry.slotId);
        }

        EventConnection connect(int priority, int sourceId, Slot const& callback)
        {
            LockGuard l(m_impl->m_cs);
            SlotEntry entry;
            entry.slot = callback;
            entry.slotId = m_impl->_GenerateNextSlotId();
            entry.priority = priority;
            m_impl->m_callbacks.insert(std::pair{priority, entry});
            return GenerateEventConnection(entry.slotId);
        }

        void Signal(Args... args)
        {
            LockGuard l(m_impl->m_cs);
            for (auto& c : m_impl->m_callbacks) {
                c.second.slot(args...);
            }
        }

    private:
        class EventSignalImpl
        {
            friend class EventSignal<Args...>;

            Mutex m_cs;

            // map of priority to slot entry
            std::multimap<int, SlotEntry> m_callbacks;

            // map of slot id to slot entry
            std::unordered_map<int, SlotEntry> m_disconnectedCallbacks;
            int m_nextSlotId = 0;

            int _GenerateNextSlotId()
            {
                return ++m_nextSlotId;
            }

            void _Reconnect(int slotId)
            {
                LockGuard l(m_cs);
                auto it = m_disconnectedCallbacks.find(slotId);
                if (it != m_disconnectedCallbacks.end()) {
                    auto entry = it->second;
                    m_disconnectedCallbacks.erase(it);
                    m_callbacks.insert(std::pair{entry.priority, entry});
                }
            }

            void _Disconnect(int slotId)
            {
                LockGuard l(m_cs);
                auto matchSlot = [slotId](auto const& i) { return i.second.slotId == slotId; };
                auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(), matchSlot);
                if (it != m_callbacks.end()) {
                    m_disconnectedCallbacks.insert(std::pair{it->second.slotId, it->second});
                    m_callbacks.erase(it);
                }
            }

            bool _IsConnected(int slotId)
            {
                LockGuard l(m_cs);
                auto matchSlot = [slotId](auto const& i) { return i.second.slotId == slotId; };
                auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(), matchSlot);
                return it != m_callbacks.end();
            }

            void _Destroy(int slotId)
            {
                LockGuard l(m_cs);
                auto matchSlot = [slotId](auto const& i) { return i.second.slotId == slotId; };
                auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(), matchSlot);
                if (it != m_callbacks.end()) {
                    m_callbacks.erase(it);
                }
            }

        };

        std::shared_ptr<EventSignalImpl> m_impl;

        EventConnection GenerateEventConnection(int slotId)
        {
            std::weak_ptr<EventSignalImpl> pWeakThis = m_impl;
            auto connectFunc = [pWeakThis, slotId] {
                auto pEvent = pWeakThis.lock();
                if (pEvent) {
                    pEvent->_Reconnect(slotId);
                }
            };
            auto disconnectFunc = [pWeakThis, slotId] {
                auto pEvent = pWeakThis.lock();
                if (pEvent) {
                    pEvent->_Disconnect(slotId);
                }
            };
            auto destroyFunc = [pWeakThis, slotId] {
                auto pEvent = pWeakThis.lock();
                if (pEvent) {
                    pEvent->_Destroy(slotId);
                }
            };
            auto checkFunc = [pWeakThis, slotId]() -> bool {
                auto pEvent = pWeakThis.lock();
                if (pEvent) {
                    return pEvent->_IsConnected(slotId);
                }
                return false;
            };
            return EventConnection(std::make_shared<EventConnectionImpl>(connectFunc, disconnectFunc, destroyFunc, checkFunc));
        }
    };

    struct Event
    {
        Event()
        {
        }

        std::chrono::time_point<std::chrono::steady_clock> timestamp;
    };

}