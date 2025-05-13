#pragma once

#include <memory>
#include "loopxia/resource/resource.h"

namespace loopxia
{
    struct ResourceGroupId
    {
        std::string name;
    };

    class ResourceGroup
    {
    public:
        virtual ~ResourceGroup() = default;

        virtual bool LoadAllResources() = 0;
        // unload all resource
        virtual void UnloadAllResource() = 0;
        
        virtual void AddResource(std::shared_ptr<Resource> resource) = 0;
        virtual bool RemoveResource(std::shared_ptr<Resource> resource) = 0;
    };
}