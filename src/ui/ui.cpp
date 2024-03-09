
#include "loopxia/ui.h"

// OpenGL functionality required
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_events.h>

namespace loopxia
{
    namespace impl
    {
        class WindowImpl
        {
        public:
            WindowImpl(const std::string& title)
            {
                m_pWindow = SDL_CreateWindow(title.c_str(), 640, 480, SDL_WINDOW_OPENGL);
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

