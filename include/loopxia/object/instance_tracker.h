#pragma once

#include <unordered_set>

namespace loopxia
{
    template<typename T>
    class InstanceTracker {
    private:
        // use inline so that multiple include of this template header does not instantiate multiple instances
        inline static std::unordered_set<T*> instances;

    public:
        InstanceTracker() {
            instances.insert(static_cast<T*>(this));
        }

        virtual ~InstanceTracker() {
            instances.erase(static_cast<T*>(this));
        }

        static std::unordered_set<T*> GetInstances() {
            return instances;
        }
    };
}