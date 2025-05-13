#pragma once

#include <memory>
#include "resource.h"

namespace loopxia
{
    class ResourceSaver
    {
    public:
        virtual void SaveResource(std::shared_ptr<Resource> resource) = 0;
    };
}