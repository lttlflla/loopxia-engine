#pragma once

#include <vector>
#include <functional>
#include <memory>
#include <map>
#include <unordered_map>
#include <variant>
#include <chrono>

namespace loopxia
{
    namespace event
    {
        enum class EventType
        {
            NONE,
            WINDOW_CLOSE_REQUEST
        };

        // predefined events
        struct WindowDetails
        {
            uint32_t windowId;
        };


        class EventConnection
        {
            typedef std::function<void()> func;
            typedef std::function<bool()> checkConnectedFunc;
        public:
            EventConnection(func disconnectCall, func connectCall, func destroyCall, checkConnectedFunc checkConnect) :
                m_disconnect(disconnectCall)
                , m_connect(connectCall)
                , m_destroy(destroyCall)
                , m_checkConnected(checkConnect)
            {
            }

            ~EventConnection()
            {
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

            EventConnection connect(Slot const& callback)
            {
                const int defaultPriority = 100;
                SlotEntry entry;
                entry.slot = callback;
                entry.slotId = _GenerateNextSlotId();
                entry.priority = defaultPriority;
                m_callbacks.insert(std::pair{defaultPriority, entry});
                return GenerateEventConnection(entry.slotId);
            }

            EventConnection connect(int priority, Slot const& callback)
            {
                SlotEntry entry;
                entry.slot = callback;
                entry.slotId = _GenerateNextSlotId();
                entry.priority = priority;
                m_callbacks.insert(std::pair{priority, entry});
                return GenerateEventConnection(entry.slotId);
            }

            EventConnection connect(int priority, int sourceId, Slot const& callback)
            {
                SlotEntry entry;
                entry.slot = callback;
                entry.slotId = _GenerateNextSlotId();
                entry.priority = priority;
                m_callbacks.insert(std::pair{priority, entry});
                return GenerateEventConnection(entry.slotId);
            }

            void Signal(Args... args)
            {
                for (auto& c : m_callbacks) {
                    c.second.slot(args...);
                }
            }

            private:
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
                    auto it = m_disconnectedCallbacks.find(slotId);
                    if (it != m_disconnectedCallbacks.end()) {
                        auto entry = it->second;
                        m_disconnectedCallbacks.erase(it);
                        m_callbacks.insert(std::pair{entry.priority, entry});
                    }
                }
                
                void _Disconnect(int slotId)
                {
                    auto matchSlot = [slotId](auto const& i) { return i.second.slotId == slotId; };
                    auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(), matchSlot);
                    if (it != m_callbacks.end()) {
                        m_disconnectedCallbacks.insert(std::pair{it->second.slotId, it->second});
                        m_callbacks.erase(it);
                    }
                }

                bool _IsConnected(int slotId)
                {
                    auto matchSlot = [slotId](auto const& i) { return i.second.slotId == slotId; };
                    auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(), matchSlot);
                    return it != m_callbacks.end();
                }

                void _Destroy(int slotId)
                {
                    auto matchSlot = [slotId](auto const& i) { return i.second.slotId == slotId; };
                    auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(), matchSlot);
                    if (it != m_callbacks.end()) {
                        m_callbacks.erase(it);
                    }
                }

                EventConnection GenerateEventConnection(int slotId)
                {
                    auto connectFunc = std::bind(&EventSignal<Args...>::_Reconnect, this, slotId);
                    auto disconnectFunc = std::bind(&EventSignal<Args...>::_Disconnect, this, slotId);
                    auto destroyFunc = std::bind(&EventSignal<Args...>::_Destroy, this, slotId);
                    auto checkFunc = std::bind(&EventSignal<Args...>::_IsConnected, this, slotId);
                    return EventConnection(connectFunc, disconnectFunc, destroyFunc, checkFunc);
                }
        };

        struct Event
        {
            Event()
            {
            }

            std::chrono::time_point<std::chrono::steady_clock> timestamp;
        };

        void PostEvent(const Event& evt);
        bool HasEvent();
        bool PollEvent();
        bool ProbeEvent(Event& evt);

        // predefined events
        extern EventSignal<Event&, WindowDetails&> WindowQuitRequest;

    }
}