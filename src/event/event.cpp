#include "event.h"

namespace loopxia
{
    namespace event
    {
        bool HasEvent()
        {
            return SDL_PollEvent(nullptr);
        }

        bool PollEvent(Event& evt)
        {
            evt.timestamp = std::chrono::steady_clock::now();

            // convert sdl event to loopxia event
            SDL_Event sdlEvt;
            SDL_PollEvent(&sdlEvt);
            switch (sdlEvt.type) {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                evt.type = EventType::WINDOW_CLOSE_REQUEST;
                evt.details.window.windowId = sdlEvt.window.windowID;
                return true;
            }

            return false;
        }

        void PostEvent(const Event& evt)
        {
        }

        void RunEventPoller()
        {
            // Process input events
            bool bCloseWindow = false;

            while (!bCloseWindow)
            {
                Event evt;
                while (PollEvent(evt)) {
                    switch (evt.type) {
                    case EventType::WINDOW_CLOSE_REQUEST:
                        // post close request event
                        bCloseWindow = true;
                        break;

                    }

                }
            }
            
        }
    }
}