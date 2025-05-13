#pragma once

#include "loopxia/resource/material.h"
#include "loopxia/resource/resource.h"

namespace loopxia
{
    class Material : public virtual Resource
    {
    public:
        virtual ~Material() = default;

        virtual std::string GetTextureFilePath(int index = 0) = 0;
        virtual void SetTextureFilePath(int index, const std::string& textureFilePath) = 0;
    };
}

