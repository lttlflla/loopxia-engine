#include <SDL.h>
#include "loopxia/game/render_manager.h"
#include "loopxia/log.h"
#include <format>
#include <map>

namespace loopxia
{
    namespace impl
    {
        class RendererImpl
        {
        public:
            RendererImpl(SDL_Window* window)
            {
                m_renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            }

            ~RendererImpl()
            {
                SDL_DestroyRenderer(m_renderer);
            }

            void AddToRenderQueue(Renderer::RenderPriority priority, const Renderer::RenderFunction& func)
            {
                m_queue.emplace(priority, std::move(func));
            }

            // 
            void Present()
            {
                for (auto& r : m_queue) {
                    r.second();
                }

                m_queue.clear();
            }


        private:
            SDL_Renderer* m_renderer;
            std::multimap<Renderer::RenderPriority, Renderer::RenderFunction> m_queue;
        };
    }

    Renderer::Renderer()
    {

    }

    Renderer::~Renderer()
    {

    }

    void Renderer::AddToRenderQueue(RenderPriority priority, const RenderFunction& func)
    {

    }
}