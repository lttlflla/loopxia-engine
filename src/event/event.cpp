#include "event.h"

namespace loopxia
{
    namespace event
    {
        // declare extern
        EventSignal<Event&, WindowDetails&> WindowQuitRequest;
        EventSignal<Event&, WindowDetails&, int, int> WindowResize;

        bool HasEvent()
        {
            return SDL_PollEvent(nullptr);
        }

        bool PollEvent()
        {
            Event evt;
            evt.timestamp = std::chrono::steady_clock::now();

            // convert sdl event to loopxia event
            SDL_Event sdlEvt;
            SDL_PollEvent(&sdlEvt);
            switch (sdlEvt.type) {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                WindowDetails details;
                details.windowId = sdlEvt.window.windowID;
                WindowQuitRequest.Signal(evt, details);
                return true;
            }

            case SDL_EVENT_WINDOW_RESIZED:
            {
                WindowDetails details;
                details.windowId = sdlEvt.window.windowID;
                WindowResize.Signal(evt, details, sdlEvt.window.data1, sdlEvt.window.data2);
                return true;
            }
            }

            return false;
        }

        void PostEvent(const Event& evt)
        {
        }
    }
}