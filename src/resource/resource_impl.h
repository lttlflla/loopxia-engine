#pragma once

#include "loopxia/resource/resource.h"

namespace loopxia
{
    template <class T>
        class ResourceImpl : public virtual Resource, public virtual T
    {
    public:
        ResourceImpl(const std::string& name, const std::string& type, const std::string filePath);

        std::string ToString() const final override;
        bool IsLoaded() const final override;
        void Unload() override;

        void AddToResourceGroup(ResourceGroup* pResourceGroup) final override;
        void RemoveFromResourceGroup(ResourceGroup* pResourceGroup) final override;

        void RemoveFromAllResourceGroups() final override;
        
        std::string FilePath() final override;

    protected:
        std::string m_name;
        std::string m_type;
        std::string m_filePath;

        bool m_bLoaded = false;
        std::unordered_set<ResourceGroup*> m_resourceGroups;
    };
}