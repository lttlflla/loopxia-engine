#include <string>

namespace loopxia
{
    namespace impl
    {
        class LoggerImpl;
    }

    void LogDebug(const std::string& str);
    void LogInfo(const std::string& str);
    void LogError(const std::string& str);
}