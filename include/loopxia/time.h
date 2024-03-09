#pragma once

namespace loopxia
{
    class GameTime
    {
    public:
        GameTime(uint32_t elapsed, uint64_t total) : m_totalElapsed(total), m_elapsed(elapsed)
        {
        }

        //The amount of elapsed game time milliseconds since the last update.
        uint32_t ElapsedTime() const {
            return m_elapsed;
        }
        
        // milliseconds since game started
        uint64_t TotalTimeElapsed() const {
            return m_totalElapsed;
        }

    private:
        uint64_t m_totalElapsed;
        uint32_t m_elapsed;
    };
}