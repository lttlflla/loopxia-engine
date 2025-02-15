#include "loopxia/resource/material.h"
#include <vector>

namespace loopxia
{
    class MaterialImpl : public Material {
    public:
        std::string GetTextureFilePath(int index) override;
        void SetTextureFilePath(int index, const std::string& textureFilePath);

    protected:
        // techniques/passes/texture
        std::vector<std::string> m_textureVector;
    };

}