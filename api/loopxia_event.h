#include <vector>
#include <functional>
#include <memory>

namespace loopxia
{
    namespace event
    {
        enum class EventType
        {
            EVENT_WINDOW_CLOSE_REQUEST
        };

        enum class EventHandlerId;

        class EventDescriptor
        {
        public:
            virtual std::vector<EventDescriptor> GetReducedDescriptors() = 0;
            virtual std::vector<EventDescriptor> GetAllReducedDescriptors() = 0;
        };

        class Event
        {
        public:
            virtual EventType Type() = 0;
            virtual EventDescriptor Descriptor() = 0;
        };

        typedef std::function<void()> Callback;
        class EventHandler
        {
        public:
            virtual EventHandler& operator+(std::shared_ptr<Callback> callback) = 0;
            virtual EventHandler& operator-(std::shared_ptr<Callback> callback) = 0;

            virtual bool SetEnable(bool bEnable) = 0;
            virtual void ClearCallbacks() = 0;
        };

        void PostEvent(const Event* evt);
        bool PollEvent(const Event* evt);
        void RunEvent();

        EventHandler CreateEventHandler(const EventDescriptor& descriptor);
        void DeleteEventHandler(EventHandler& handler);

    }
}