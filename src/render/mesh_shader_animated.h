#pragma once

#include "loopxia/render/shader.h"
#include "loopxia/render/render_buffer.h"

#include <GL/glew.h>
#include <memory>
#include <vector>
#include "loopxia/math.h"
#include "mesh_shader_static.h"

namespace loopxia
{
    class MeshShaderAnimated : public MeshShaderStatic
    {
    public:
        MeshShaderAnimated(const std::string& shaderFileVS, const std::string& shaderFileFS);

        RenderBuffer* GetBoneBuffer();
        
        void SetupShaderBuffers() override;
        
        void SetBoneTransformations(const std::vector<Matrix4x4>& transformation);

    private:
        // the attributes in the vertex array object
        std::unique_ptr<RenderBuffer> m_boneBuffer; // buffer that contains the bone id and weights

        int m_boneIdAttribute = -1;
        int m_boneWeightAttribute = -1;

        int m_bonesAttribute = -1;
    };
}
