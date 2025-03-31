#pragma once

#include <memory>
#include "resource.h"

namespace loopxia
{
    class ResourceLoader
    {
    public:
        virtual void LoadResource(std::shared_ptr<Resource> resource) = 0;
    };
}