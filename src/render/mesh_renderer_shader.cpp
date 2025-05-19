#include "mesh_renderer_shader.h"
#include <glm/gtc/type_ptr.hpp>
#include "mesh_render_setup.h"

namespace loopxia
{
    MeshRendererShader::MeshRendererShader(const std::string& shaderFileVS, const std::string& shaderFileFS)
    {
        m_meshShader.LoadFromFile(shaderFileVS, Shader::ShaderType::kVertex);
        m_meshShader.LoadFromFile(shaderFileFS, Shader::ShaderType::kFragment);
        m_meshShader.Link();

        m_meshShader.Begin();
        SetupShaderBuffers(); 
        m_meshShader.End();
    }

    void MeshRendererShader::BeginRender()
    {
        static bool bCalled = false;
        m_meshShader.Begin();

        glBindVertexArray(m_VAO);
        if (m_indexBuffer) {
            // bind index buffer
            m_indexBuffer->Bind();
        }
    }

    void MeshRendererShader::EndRender()
    {
        m_meshShader.End();
        glBindVertexArray(0);
    }

    void MeshRendererShader::SetTextureId(GLuint textureId)
    {
        if (m_textureAttribute == -1) {
            m_textureAttribute = m_meshShader.GetUniformLocation("textureSampler");
        }
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glUniform1i(m_textureAttribute, 0);
    }

    void MeshRendererShader::SetWVP(Matrix4x4 matrix)
    {
        if (m_wvpAttribute == -1) {
            m_wvpAttribute = m_meshShader.GetUniformLocation("gWvp");
        }

        glUniformMatrix4fv(m_wvpAttribute, 1, GL_FALSE /*whether transposed*/, glm::value_ptr(matrix));
    }

    void MeshRendererShader::SetupShaderBuffers()
    {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        //VBO data
        // generate vbo buffers
        glGenBuffers(kNumOfBuffers, m_attributeBuffers);

        m_indexBuffer.reset(new RenderBuffer(m_attributeBuffers[0], RenderBufferDataType::kIndexBuffer));

        m_vertexBuffer.reset(new RenderBuffer(m_attributeBuffers[1], RenderBufferDataType::kVertexBuffer));
        m_vertexBuffer->Bind();

        // tell opengl that this vertex buffer maps to "pos" attribute
        m_posAttribute = m_meshShader.GetAttribute("pos");
        glVertexAttribPointer(m_posAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 /*offset*/);
        glEnableVertexAttribArray(m_posAttribute);

        m_uvBuffer.reset(new RenderBuffer(m_attributeBuffers[2], RenderBufferDataType::kUVBuffer));
        m_uvBuffer->Bind();

        // tell opengl that this uv buffer maps to "uv" attribute
        m_uvAttribute = m_meshShader.GetAttribute("uv");
        glVertexAttribPointer(m_uvAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0 /*offset*/);
        glEnableVertexAttribArray(m_uvAttribute);

        m_normalBuffer.reset(new RenderBuffer(m_attributeBuffers[3], RenderBufferDataType::kNormalBuffer));
        m_normalBuffer->Bind();

        // tell opengl that this normal buffer maps to "normal" attribute
        m_normalAttribute = m_meshShader.GetAttribute("normal");
        glVertexAttribPointer(m_normalAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 /*offset*/);
        glEnableVertexAttribArray(m_normalAttribute);

        //m_boneIDBuffer.reset(new RenderBuffer(m_attributeBuffers[4], RenderBufferDataType::kBoneIdBuffer));

        //m_boneIdAttribute = m_meshShader.GetAttribute("boneIDs");
        //glVertexAttribIPointer(m_boneIdAttribute, kMaxNumBonesPerVertex, GL_INT, sizeof(VertexBoneData), (const GLvoid*) 0/*offset*/);
        //glEnableVertexAttribArray(m_boneIdAttribute);
        //
        //m_boneWeightBuffer.reset(new RenderBuffer(m_attributeBuffers[5], RenderBufferDataType::kBoneWeightBuffer));

        //m_boneWeightAttribute = m_meshShader.GetAttribute("boneWeights");
        //glVertexAttribPointer(m_boneWeightAttribute, kMaxNumBonesPerVertex, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData),
        //    (const GLvoid*)(kMaxNumBonesPerVertex * sizeof(int32_t)));
        //glEnableVertexAttribArray(m_boneWeightAttribute);

        glBindVertexArray(0);
    }
    
    RenderBuffer* MeshRendererShader::GetIndexBuffer()
    {
        return m_indexBuffer.get();
    }

    RenderBuffer* MeshRendererShader::GetVertexBuffer()
    {
        return m_vertexBuffer.get();
    }

    RenderBuffer* MeshRendererShader::GetNormalBuffer()
    {
        return m_normalBuffer.get();
    }

    RenderBuffer* MeshRendererShader::GetUVBuffer()
    {
        return m_uvBuffer.get();
    }

    RenderBuffer* MeshRendererShader::GetBoneIdBuffer()
    {
        return m_boneIDBuffer.get();
    }

    RenderBuffer* MeshRendererShader::GetBoneWeightBuffer()
    {
        return m_boneWeightBuffer.get();
    }
}