
#include "loopxia/ui.h"

// OpenGL functionality required
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_events.h>

namespace ui = loopxia::ui;

namespace loopxia
{
    namespace ui
    {

        class LoopxiaWindow : public Window
        {
        public:
            LoopxiaWindow(const std::string& title)
            {
                // Init window
                m_pWindow = SDL_CreateWindow(title.c_str(), 640, 480, SDL_WINDOW_OPENGL);

                // Init OpenGL context
                m_glContext = SDL_GL_CreateContext(m_pWindow);
            }            

            ~LoopxiaWindow()
            {
                SDL_GL_DeleteContext(m_glContext);
            }

            void Show() override
            {

            }

            void Hide() override
            {

            }
        private:
            SDL_Window* m_pWindow;
            SDL_GLContext m_glContext;
        };

        Window* CreateUIWindow(const std::string& title)
        {
            return new LoopxiaWindow(title);
        }

        void CreateLayout()
        {

        }
    }

}

