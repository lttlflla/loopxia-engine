#pragma once

#include <memory>
#include "mesh.h"
#include "texture.h"
#include "resource_group.h"
#include "resource_loader.h"

namespace loopxia
{
    const static std::string kDefaultResourceGroupName = "LOOPXIA_DEFAULT_RESOURCE_GROUP";

    class ResourceManager {
    public:
        virtual ~ResourceManager() = default;

        virtual std::shared_ptr<Mesh> CreateMesh(const std::string& path, const std::string& name, ResourceGroup* grp = nullptr) = 0;
        virtual std::shared_ptr<Texture> CreateTexture(const std::string& path, const std::string& name, ResourceGroup* grp = nullptr) = 0;
        virtual std::shared_ptr<Material> CreateMaterial(const std::string& path, const std::string& name, ResourceGroup* grp = nullptr) = 0;

        // for loading generic custom resource
        virtual std::shared_ptr<Resource> CreateResource(const std::string& path, ResourceLoader* loader, ResourceGroup* grp = nullptr) = 0;

        virtual ResourceGroup* CreateResourceGroup(const std::string& name) = 0;

        /**
        * Default resource group must always exist.
        * resources created without specifying the resource group will be added to the default resource group
        */
        virtual ResourceGroup* GetDefaultResourceGroup() = 0;

        virtual int TotalMemoryUsed() = 0;

        virtual std::vector<ResourceGroup*> GetAllResourceGroups() = 0;
    };

    ResourceManager* CreateResourceManager();
    void DestroyResourceManager(ResourceManager* mgr);
}

