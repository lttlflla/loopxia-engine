#include <vector>
#include <functional>
#include <memory>
#include <map>
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

        union EventDetails
        {
            WindowDetails window;
            char data[128];
        };

        class EventConnection;

        template <class ... args>
        struct EventSignal
        {
            typedef callback std::function<bool(args)>;
            static EventConnection connect(callback& callback)
            {
            }

            static EventConnection connect(int priority, callback& callback)
            {
                return {};
            }

            static EventConnection connect(int priority, int sourceId, callback& callback)
            {
                return {};
            }

            static void disconnect(EventConnection& connection)
            {
            }

            static void Signal(args)
            {
            }

            std::multiset
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

        struct Event
        {
            Event()
            {
            }

            std::chrono::time_point<std::chrono::steady_clock> timestamp;
        };

        void PostEvent(const Event& evt);
        bool HasEvent();
        bool PollEvent(Event& evt);
        bool ProbeEvent(Event& evt);
        void RunEventPoller();

        // predefined events
        EventSignal<Event, WindowDetails> WindowQuitRequest;

    }
}