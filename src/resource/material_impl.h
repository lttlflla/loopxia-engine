#pragma once

#include "loopxia/resource/material.h"
#include "resource_impl.h"
#include <vector>

namespace loopxia
{
    class MaterialImpl : public ResourceImpl<Material> {
    public:
        MaterialImpl(const std::string& name, const std::string filePath);

        std::string GetTextureFilePath(int index) override;
        void SetTextureFilePath(int index, const std::string& textureFilePath) override;

        bool Load() override;

    protected:
        // techniques/passes/texture
        std::vector<std::string> m_textureVector;
    };

}