#include "resource/material_impl.h"
#include "material_loader_impl.h"

namespace loopxia
{
    const std::string kMaterialType = "Material";

    MaterialImpl::MaterialImpl(const std::string& name, const std::string filePath) :
        ResourceImpl<Material>(name, kMaterialType, filePath)
    {

    }

    std::string MaterialImpl::GetTextureFilePath(int index)
    {
        if (m_textureVector.size() <= index) {
            return {};
        }

        return m_textureVector[index];
    };

    void MaterialImpl::SetTextureFilePath(int index, const std::string& textureFilePath)
    {
        if (m_textureVector.size() <= index) {
            m_textureVector.resize(index + 1);
        }

        m_textureVector[index] = textureFilePath;
    }

    bool MaterialImpl::Load()
    {
        if (m_bLoaded) {
            return true;
        }

        MaterialLoader loader;
        return loader.LoadResource(shared_from_this());
    }
}