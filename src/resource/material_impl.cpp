#include "resource/material_impl.h"

namespace loopxia
{
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

    Material* CreateMaterialFromTextureFilePath(const std::string& textureFilePath)
    {
        auto material = new MaterialImpl();
        material->SetTextureFilePath(0, textureFilePath);
        return material;
    }

    Material* CreateMaterialFromMaterialFile(const std::string& materialFilePath)
    {
        return new MaterialImpl();
    }
}