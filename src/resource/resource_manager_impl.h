#include "loopxia/resource/resource_manager.h"
#include <unordered_map>
#include "resource_group_impl.h"
#include <memory>

namespace loopxia
{
    class ResourceManagerImpl : public ResourceManager {
    public:
        ResourceManagerImpl();

        virtual std::shared_ptr<Mesh> CreateMesh(const std::string& path, const std::string& name, ResourceGroup* grp = nullptr) override;
        virtual std::shared_ptr<Texture> CreateTexture(const std::string& path, const std::string& name, ResourceGroup* grp = nullptr) override;
        virtual std::shared_ptr<Material> CreateMaterial(const std::string& path, const std::string& name, ResourceGroup* grp = nullptr) override;

        // for loading generic custom resource
        virtual std::shared_ptr<Resource> CreateResource(const std::string& path, ResourceLoader* loader, ResourceGroup* grp = nullptr) override;

        virtual ResourceGroup* CreateResourceGroup(const std::string& name) override;

        /**
        * Default resource group must always exist.
        * resources created without specifying the resource group will be added to the default resource group
        */
        virtual ResourceGroup* GetDefaultResourceGroup() override;

        virtual int TotalMemoryUsed() override;

        virtual std::vector<ResourceGroup*> GetAllResourceGroups() override;

    private:
        ResourceGroup* p_GetTargetResourceGroup(ResourceGroup* grp);

    private:
        // map of resource group name to resource group
        std::unordered_map<std::string, std::unique_ptr<ResourceGroup>> m_resourceGroupMap;
    };
}