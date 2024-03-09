#include "loopxia/loopxia.h"
#include <SDL.h>

namespace loopxia
{
    void InitEngine()
    {
        SDL_Init(SDL_INIT_VIDEO);

        //Use OpenGL 3.1 core
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }

    void ShutdownEngine()
    {
        SDL_Quit();
    }
}