
#include "loopxia/ui.h"

// OpenGL functionality required
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_events.h>
#include "loopxia/log.h"

namespace loopxia
{
    namespace impl
    {
        class WindowImpl
        {
        public:
            WindowImpl(const std::string& title)
            {
                int width = 640;
                int height = 480;

                float x, y;
                
                SDL_GetGlobalMouseState(&x, &y);
                SDL_Point mousePt = { (int)x, (int)y };
                
                auto displayId = SDL_GetDisplayForPoint(&mousePt);
                auto dm = SDL_GetCurrentDisplayMode(displayId);
                if (!dm) {
                    LogError(std::string("Failed to get Current display mode ") + SDL_GetError());
                } else {
                    width = dm->w * 0.9;
                    height = dm->h * 0.9;
                }

                m_pWindow = SDL_CreateWindow(title.c_str(), width, height,  SDL_WINDOW_OPENGL |
                    SDL_WINDOW_RESIZABLE |  SDL_WINDOW_MAXIMIZED);

                if (!m_pWindow) {
                    LogError(std::string("Failed to create window ") + SDL_GetError());
                }

                m_glContext = SDL_GL_CreateContext(m_pWindow);
            }

            ~WindowImpl()
            {
                SDL_DestroyWindow(m_pWindow);
            }

            void* GetNativeHandle()
            {
                return m_pWindow;
            }

            void Show()
            {
                SDL_ShowWindow(m_pWindow);
            }

            void Hide()
            {
                SDL_HideWindow(m_pWindow);
            }

            void Swap()
            {
                SDL_GL_SwapWindow(m_pWindow);
            }

        protected:
            SDL_Window* m_pWindow;
            SDL_GLContext m_glContext;
        };
    }

    Window::Window(const std::string& title)
    {
        m_impl = new impl::WindowImpl(title);
    }

    Window::~Window()
    {
        delete m_impl;
    }

    void* Window::GetNativeHandle()
    {
        return m_impl->GetNativeHandle();
    }

    void Window::Show()
    {
        m_impl->Show();
    }

    void Window::Hide()
    {
        m_impl->Hide();
    }

    void Window::Swap()
    {
        m_impl->Swap();
    }

    Window* CreateUIWindow(const std::string& title)
    {
        return new Window(title);
    }

    void CreateLayout()
    {

    }

}

