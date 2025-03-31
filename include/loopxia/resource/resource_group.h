#pragma once

#include <memory>

namespace loopxia
{
    struct ResourceGroupId
    {
        std::string name;
    };

    class ResourceGroup
    {
    public:
        virtual bool LoadAllResources() = 0;
        virtual bool LoadResource(std::shared_ptr<Resource> resource) = 0;
        virtual bool LoadResourceAsync(std::shared_ptr<Resource> resource) = 0;

        // unload all resource
        virtual void UnloadAllResource() = 0;
    };
}