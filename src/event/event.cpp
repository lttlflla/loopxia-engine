#include <SDL_events.h>

namespace loopxia
{
    namespace event
    {
        void RunEvent()
        {
            // Process input events
            SDL_Event evt;
            while (SDL_PollEvent(&evt)) {
                switch (evt.type) {

                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:

                    bCloseWindow = true;
                    break;

                }

            }
        }
    }
}