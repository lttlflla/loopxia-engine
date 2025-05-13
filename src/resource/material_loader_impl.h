#pragma once

#include "loopxia/resource/resource_loader.h"
#include "resource_impl.h"
#include <vector>

namespace loopxia
{
    class MaterialLoader : public ResourceLoader {
    public:
        bool LoadResource(std::shared_ptr<Resource> resource) override;
    };
}