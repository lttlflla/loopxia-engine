#include <SDL.h>
#include "loopxia/render/renderer.h"
#include "loopxia/log.h"
#include <format>

namespace loopxia
{
    namespace impl
    {
        class RendererImpl
        {
        public:
            RendererImpl(SDL_Window* window)
            {
                m_renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED);
            }

            ~RendererImpl()
            {
                SDL_DestroyRenderer(m_renderer);
            }

            // 
            void Present()
            {

            }


        private:
            SDL_Renderer* m_renderer;
        };
    }

    Renderer::Renderer()
    {

    }

    Renderer::~Renderer()
    {

    }

}