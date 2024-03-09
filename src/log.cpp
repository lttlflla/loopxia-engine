#include "loopxia/log.h"
#include <iostream>

#ifdef LOOPXIA_PLATFORM_WINDOWS
#include <windows.h>
#include <debugapi.h>
#endif

namespace loopxia
{
    namespace
    {
        // trim from start (in place)
        inline void ltrim(std::string& s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
                }));
        }

        // trim from end (in place)
        inline void rtrim(std::string& s) {
            s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
                }).base(), s.end());
        }

        // trim from both ends (in place)
        inline void trim(std::string& s) {
            rtrim(s);
            ltrim(s);
        }

    }

    void LogDebug(const std::string& str)
    {
        auto strCopy = str;
        trim(strCopy);
        strCopy += "\n";

#ifdef LOOPXIA_PLATFORM_WINDOWS
        OutputDebugString(strCopy.c_str() );
#endif
        std::cout << strCopy;
    }

    void LogInfo(const std::string& str)
    {
        auto strCopy = str;
        trim(strCopy);
        strCopy += "\n";

#ifdef LOOPXIA_PLATFORM_WINDOWS
        OutputDebugString(strCopy.c_str());
#endif
        std::cout << strCopy;
    }

    void LogError(const std::string& str)
    {
        auto strCopy = str;
        trim(strCopy);
        strCopy += "\n";

#ifdef LOOPXIA_PLATFORM_WINDOWS
        OutputDebugString(strCopy.c_str());
#endif
        std::cout << strCopy;
    }
}
