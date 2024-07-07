#pragma once

#include <typeinfo>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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


    class Object : public InstanceTracker<Object>
    {
    public:
        Object();
        ~Object();
    };

}