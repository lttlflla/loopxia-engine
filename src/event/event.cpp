#include <SDL_events.h>
#include "loopxia_event.h"

namespace loopxia
{
    namespace event
    {
        void PostEvent(const Event* evt)
        {

        }

        void PollLoop()
        {
            // Process input events
            bool bCloseWindow = false;

            while (!bCloseWindow)
            {
                SDL_Event evt;
                while (SDL_PollEvent(&evt)) {
                    switch (evt.type) {

                    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                        // post close request event
                        evt.window.windowID
                        bCloseWindow = true;
                        break;

                    }

                }
            }
            
        }
    }
}