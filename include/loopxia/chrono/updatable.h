#pragma once

#include "loopxia/chrono/time.h"

namespace loopxia
{
    // interface for object that progress / change with time
    class Updatable
    {
    public:
        virtual ~Updatable() = default;

        virtual void Update(const GameTime&) = 0;
    };
}