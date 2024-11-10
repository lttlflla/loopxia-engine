#pragma once

namespace loopxia
{
    class Renderable
    {
    public:
        virtual ~Renderable() = default;

        virtual void Render() = 0;
    };
}