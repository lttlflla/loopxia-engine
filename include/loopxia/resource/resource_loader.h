#pragma once

#include <memory>
#include "resource.h"

namespace loopxia
{
    class ResourceLoader
    {
    public:
        virtual bool LoadResource(std::shared_ptr<Resource> resource) = 0;
    };
}