
#include "loopxia_ui.h"

// OpenGL functionality required
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_events.h>

namespace ui = loopxia::ui;

namespace ui
{
    class LoopxiaWindow : public Window
    {
    public:
        LoopxiaWindow(const std::string& title)
        {
            // Init window
            m_pWindow = SDL_CreateWindow(title, 640, 480, SDL_WINDOW_OPENGL);

            // Init OpenGL context
            SDL_GLContext glcontext = SDL_GL_CreateContext(m_pWindow);
        }
    private:
        SDL_Window* m_pWindow;
    };

    Window* ui::CreateWindow(const std::string& title)
    {
        return new LoopxiaWindow(title);
    }

    void CreateLayout()
    {

    }

    void ui::Init()
    {
        SDL_Init(SDL_INIT_VIDEO);
    }
}

