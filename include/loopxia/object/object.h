#pragma once

#include "instance_tracker.h"

namespace loopxia
{
    class Object : public InstanceTracker<Object>
    {
    public:
        Object();
        virtual ~Object();
    };

}