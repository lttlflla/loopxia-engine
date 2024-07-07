#pragma once

namespace loopxia
{
    class ComponentUpdatable
    {
    public:
        virtual ~ComponentUpdatable() = default;

        virtual void Update(const GameTime&) = 0;
    };
}