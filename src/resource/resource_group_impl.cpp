#include "resource/resource_group_impl.h"

namespace loopxia
{
    ResourceGroupImpl::ResourceGroupImpl(ResourceGroupId id) : m_groupId(id)
    {
    }

    bool ResourceGroupImpl::LoadAllResources()
    {
        for (auto& r : m_resources) {
            
        }

        return false;
    }

    // unload all resource
    void ResourceGroupImpl::UnloadAllResource()
    {
        for (auto& r : m_resources) {
            r->Unload();
        }
    }

    void ResourceGroupImpl::AddResource(std::shared_ptr<Resource> resource)
    {
        m_resources.insert(resource);
    }

    bool ResourceGroupImpl::RemoveResource(std::shared_ptr<Resource> resource)
    {
        if (!m_resources.count(resource)) {
            return false;
        }

        m_resources.erase(resource);
        return true;
    }
}