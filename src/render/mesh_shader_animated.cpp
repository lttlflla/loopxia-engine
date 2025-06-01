#include "mesh_shader_animated.h"
#include <glm/gtc/type_ptr.hpp>
#include "mesh_render_setup.h"
#include "../resource/mesh_impl.h"

namespace loopxia
{
    MeshShaderAnimated::MeshShaderAnimated(const std::string& shaderFileVS, const std::string& shaderFileFS) :
        MeshShaderStatic(shaderFileVS, shaderFileFS)
    {
    }

    void MeshShaderAnimated::SetBoneTransformations(const std::vector<Matrix4x4>& transformations)
    {
        if (transformations.empty()) {
            return;
        }

        if (m_bonesAttribute == -1) {
            m_bonesAttribute = m_meshShader.GetUniformLocation("gBones");
        }

        glUniformMatrix4fv(m_bonesAttribute, transformations.size(), GL_FALSE /*whether transposed*/, glm::value_ptr(transformations[0]));
    }

    void MeshShaderAnimated::SetupShaderBuffers()
    {
        MeshShaderStatic::SetupShaderBuffers();

        m_meshShader.Begin();
        glBindVertexArray(m_VAO);

        m_boneBuffer.reset(new RenderBuffer(m_attributeBuffers[4], RenderBufferDataType::kBoneBuffer));
        m_boneBuffer->Bind();
        m_boneIdAttribute = m_meshShader.GetAttribute("boneIDs");
        glVertexAttribIPointer(m_boneIdAttribute, kMaxNumBonesPerVertex, GL_INT, sizeof(VertexBoneData) /*stride*/, (const GLvoid*)0/*offset*/);
        glEnableVertexAttribArray(m_boneIdAttribute);
        m_boneWeightAttribute = m_meshShader.GetAttribute("boneWeights");
        glVertexAttribPointer(m_boneWeightAttribute, kMaxNumBonesPerVertex, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData) /*stride*/,
            (const GLvoid*)(kMaxNumBonesPerVertex * sizeof(int32_t)));
        glEnableVertexAttribArray(m_boneWeightAttribute);

        glBindVertexArray(0);
        m_meshShader.End();
    }

    RenderBuffer* MeshShaderAnimated::GetBoneBuffer()
    {
        return m_boneBuffer.get();
    }

}