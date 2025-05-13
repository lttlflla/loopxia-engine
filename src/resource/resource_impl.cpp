#include "resource_impl.h"
#include "loopxia/resource/resource_group.h"
#include "loopxia/resource/mesh.h"

namespace loopxia
{
    template<class T>
    ResourceImpl<T>::ResourceImpl(const std::string& name, const std::string& type, const std::string filePath) :
        m_name(name)
        , m_type(type)
        , m_filePath(filePath)
    {
    }

    template<class T>
    std::string ResourceImpl<T>::ToString() const
    {
        return m_type + "_" + m_name;
    }

    template<class T>
    bool ResourceImpl<T>::IsLoaded() const
    {
        return m_bLoaded;
    }

    template<class T>
    void ResourceImpl<T>::Unload()
    {
        m_bLoaded = false;
    }

    template<class T>
    void ResourceImpl<T>::AddToResourceGroup(ResourceGroup* pResourceGroup)
    {
        pResourceGroup->AddResource(shared_from_this());
    }

    template<class T>
    void ResourceImpl<T>::RemoveFromResourceGroup(ResourceGroup* pResourceGroup)
    {
        pResourceGroup->RemoveResource(shared_from_this());
    }

    template<class T>
    void ResourceImpl<T>::RemoveFromAllResourceGroups()
    {
        auto pThis = shared_from_this();
        for (auto& grp : m_resourceGroups) {
            grp->RemoveResource(pThis);
        }
    }

    template<class T>
    std::string ResourceImpl<T>::FilePath()
    {
        return m_filePath;
    }

    template class ResourceImpl<Mesh>;
    template class ResourceImpl<Material>;
}