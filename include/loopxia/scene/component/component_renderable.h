#pragma once

namespace loopxia
{
    class ComponentRenderable
    {
    public:
        virtual ~ComponentRenderable() = default;

        virtual void Render() = 0;
    };
}