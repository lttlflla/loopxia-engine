#pragma once

#include <string>
#include <string_view>
#include <format>

namespace loopxia
{
    namespace impl
    {
        class LoggerImpl;
    }

    // Non-template base implementations
    void LogDebugImpl(const std::string& str);
    void LogInfoImpl(const std::string& str);
    void LogErrorImpl(const std::string& str);

    // Template-based formatted logging
    template<typename... Args>
    auto LogDebug(std::format_string<Args...> fmt, Args&&... args) {
        LogDebugImpl(std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void LogInfo(std::format_string<Args...> fmt, Args&&... args) {
        LogInfoImpl(std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void LogError(std::format_string<Args...> fmt, Args&&... args) {
        LogErrorImpl(std::format(fmt, std::forward<Args>(args)...));
    }

    // Optional: Overloads to log plain strings directly (instead of formatting)
    inline void LogDebug(const std::string& msg) { LogDebugImpl(msg); }
    inline void LogInfo(const std::string& msg) { LogInfoImpl(msg); }
    inline void LogError(const std::string& msg) { LogErrorImpl(msg); }

}
