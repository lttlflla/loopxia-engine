#pragma once

#include <chrono>

namespace loopxia
{
    class GameTime
    {
    public:
        GameTime(std::chrono::nanoseconds elapsed, std::chrono::steady_clock::time_point timeNow) : m_timeNow(timeNow), m_elapsed(elapsed)
        {
        }

        //The amount of elapsed time since last update cycle
        uint64_t ElapsedTimeNanosec() const {
            return m_elapsed.count();
        }
        
        uint64_t ElapsedTimeMilliseconds() const {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(m_elapsed);

            // Extract the integer value of the milliseconds
            uint64_t ms_int = static_cast<uint64_t>(ms.count());
            return ms_int;
        }

        float ElapsedTimeSeconds() const {
            return (float)ElapsedTimeMilliseconds() / 1000;
        }

        // nanoseconds since game started
        std::chrono::steady_clock::time_point TimeNow() const {
            return m_timeNow;
        }

    private:
        std::chrono::steady_clock::time_point m_timeNow; // total active time
        std::chrono::nanoseconds m_elapsed; // how much time has elapsed since last cycle
    };
}