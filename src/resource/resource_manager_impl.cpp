#include "resource_manager_impl.h"
#include "resource_group_impl.h"
#include "mesh_impl.h"

namespace loopxia
{
    ResourceManagerImpl::ResourceManagerImpl()
    {
        CreateResourceGroup(kDefaultResourceGroupName);
    }

    std::shared_ptr<Mesh> ResourceManagerImpl::CreateMesh(const std::string& filePath, const std::string& name, ResourceGroup* grp)
    {
        ResourceGroup* targetResourceGroup = p_GetTargetResourceGroup(grp);

        auto pMesh = std::make_shared<MeshImpl>(filePath, name);
        pMesh->AddToResourceGroup(targetResourceGroup);

        auto pMaterial = CreateMaterial("", name + "_material", grp);
        pMesh->SetMaterial(pMaterial);

        return std::dynamic_pointer_cast<Mesh>(pMesh);
    }

    std::shared_ptr<Texture> ResourceManagerImpl::CreateTexture(const std::string& path, const std::string& name, ResourceGroup* grp)
    {
        return {};
    }
    
    std::shared_ptr<Material> ResourceManagerImpl::CreateMaterial(const std::string& path, const std::string& name, ResourceGroup* grp)
    {
        auto pMaterial = std::make_shared<MaterialImpl>(path, name);
        pMaterial->AddToResourceGroup(p_GetTargetResourceGroup(grp));
        return pMaterial;
    }

    std::shared_ptr<Resource> ResourceManagerImpl::CreateResource(const std::string& path, ResourceLoader* loader, ResourceGroup* grp)
    {
        return {};
    }

    ResourceGroup* ResourceManagerImpl::CreateResourceGroup(const std::string& name)
    {
        if (m_resourceGroupMap.count(name)) {
            return m_resourceGroupMap[name].get();
        }
        
        ResourceGroupId groupId;
        groupId.name = name;

        m_resourceGroupMap[name] = std::move(std::make_unique<ResourceGroupImpl>(groupId));
        return m_resourceGroupMap[name].get();
    }

    ResourceGroup* ResourceManagerImpl::GetDefaultResourceGroup()
    {
        return m_resourceGroupMap[kDefaultResourceGroupName].get();
    }

    int ResourceManagerImpl::TotalMemoryUsed()
    {
        return 0;
    }

    std::vector<ResourceGroup*> ResourceManagerImpl::GetAllResourceGroups()
    {
        std::vector<ResourceGroup*> grps;
        for (auto& pair : m_resourceGroupMap) {
            grps.push_back(pair.second.get());
        }

        return grps;
    }

    ResourceGroup* ResourceManagerImpl::p_GetTargetResourceGroup(ResourceGroup* grp)
    {
        ResourceGroup* targetResourceGroup = grp;
        if (!targetResourceGroup) {
            // add to default group
            targetResourceGroup = GetDefaultResourceGroup();
        }

        return targetResourceGroup;
    }

    ResourceManager* CreateResourceManager()
    {
        return new ResourceManagerImpl;
    }

    void DestroyResourceManager(ResourceManager* mgr)
    {
        delete mgr;
    }
}