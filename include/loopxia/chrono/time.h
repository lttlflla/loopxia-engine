#pragma once

namespace loopxia
{
    struct GameTime
    {
        std::chrono::time_point<std::chrono::steady_clock> timestamp;
        std::chrono::duration<float, std::milli> elapsedTimeMs;
    };
}