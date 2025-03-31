#include "loopxia/resource/resource_manager.h"

namespace loopxia
{
    class ResourceManagerImpl : public ResourceManager {
    public:
        virtual std::shared_ptr<Mesh> CreateMesh(const std::string& path, ResourceGroup* grp = nullptr) override;
        virtual std::shared_ptr<Texture> CreateTexture(const std::string& path, ResourceGroup* grp = nullptr) override;

        // for loading generic custom resource
        virtual std::shared_ptr<Resource> CreateResource(const std::string& path, ResourceLoader* loader, ResourceGroup* grp = nullptr) override;

        virtual ResourceGroup* CreateResourceGroup(const std::string& name) override;

        /**
        * Default resource group must always exist.
        * resources created without specifying the resource group will be added to the default resource group
        */
        virtual ResourceGroup* GetDefaultResourceGroup() = 0;

        virtual int TotalMemoryUsed() = 0;

        virtual std::vector<ResourceGroup*> GetAllResourceGroups() = 0;
    };

}