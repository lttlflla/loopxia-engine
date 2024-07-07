#pragma once

#include <functional>

namespace loopxia
{
    class RendererManager
    {
    public:
        virtual ~RendererManager() = default;

        enum RenderPriority
        {
            EDITOR = 1000,
            GAME = 3000,
            GAME_UI = 5000,
            EDITOR_UI = 10000,
        };

        typedef std::function<void()> RenderFunction;

        //void Render(Mesh* mesh, RenderPriority priority = GAME);
        virtual void AddToRenderQueue(RenderPriority priority, const RenderFunction& func) = 0;

        virtual void Render(const GameTime& gameTime) = 0;

        // execute render operations in the queue and clear render queue
        virtual void Present() = 0;
    };
}