#pragma once

#include "loopxia/game/game.h"

namespace loopxia
{
    class Renderer
    {
    public:
        virtual ~Renderer() = default;

        virtual void Render(const GameTime&) = 0;
    };
}