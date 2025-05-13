#pragma once

#include <memory>
#include "loopxia/resource/resource_group.h"

namespace loopxia
{
    class ResourceGroupImpl : public ResourceGroup
    {
    public:
        ResourceGroupImpl(ResourceGroupId id);

        bool LoadAllResources() override;
        // unload all resource
        void UnloadAllResource() override;

        void AddResource(std::shared_ptr<Resource> resource) override;
        bool RemoveResource(std::shared_ptr<Resource> resource) override;

    private:
        ResourceGroupId m_groupId;
        std::unordered_set<std::shared_ptr<Resource>> m_resources;
    };
}