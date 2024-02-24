#include "loopxia/loopxia.h"
#include <SDL.h>

namespace loopxia
{
    void InitEngine()
    {
        SDL_Init(SDL_INIT_VIDEO);

    }

    void ShutdownEngine()
    {
        SDL_Quit();
    }
}