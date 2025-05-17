#include "mesh_renderer_shader.h"
#include <glm/gtc/type_ptr.hpp>

namespace loopxia
{
    MeshRendererShader::MeshRendererShader(const std::string& shaderFileVS, const std::string& shaderFileFS)
    {
        m_meshShader.LoadFromFile(shaderFileVS, Shader::ShaderType::kVertex);
        m_meshShader.LoadFromFile(shaderFileFS, Shader::ShaderType::kFragment);
        m_meshShader.Link();
        
        BeginRender();
        SetupShaderBuffers(); 
        EndRender();
    }

    void MeshRendererShader::BeginRender()
    {
        glBindVertexArray(m_VAO);
        m_meshShader.Begin();

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
        auto textureLocation = m_meshShader.GetUniformLocation("textureSampler");
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glUniform1i(textureLocation, 0);
    }

    void MeshRendererShader::SetWVP(Matrix4x4 matrix)
    {
        auto attribute = m_meshShader.GetUniformLocation("mvp");
        glUniformMatrix4fv(attribute, 1, GL_FALSE /*whether transposed*/, glm::value_ptr(matrix));
    }

    void MeshRendererShader::SetupShaderBuffers()
    {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        //VBO data
        glGenBuffers(kNumOfBuffers, m_attributeBuffers);
        m_indexBuffer.reset(new RenderBuffer(m_attributeBuffers[0], RenderBufferDataType::kIndexBuffer));

        m_vertexBuffer.reset(new RenderBuffer(m_attributeBuffers[1], RenderBufferDataType::kVertexBuffer));
        m_vertexBuffer->Bind();

        // tell opengl that this vertex buffer maps to "aPos" attribute
        unsigned int positionPos = m_meshShader.GetAttribute("aPos");
        glVertexAttribPointer(positionPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 /*offset*/);
        glEnableVertexAttribArray(positionPos);

        m_uvBuffer.reset(new RenderBuffer(m_attributeBuffers[2], RenderBufferDataType::kUVBuffer));
        m_uvBuffer->Bind();

        // tell opengl that this uv buffer maps to "uv" attribute
        unsigned int uv_position = m_meshShader.GetAttribute("uv");
        glVertexAttribPointer(uv_position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0 /*offset*/);
        glEnableVertexAttribArray(uv_position);

        //m_normalBuffer.reset(new RenderBuffer(m_attributeBuffers[3], RenderBufferDataType::kNormalBuffer));
        //m_normalBuffer->Bind();

        // tell opengl that this normal buffer maps to "normal" attribute
        // int normal_position = m_meshShader.GetAttribute("normal");
       // glVertexAttribPointer(normal_position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 /*offset*/);
       // glEnableVertexAttribArray(normal_position);

        //GLfloat vertexData[] =
        //{
        //    -0.5f, -0.5f, 0,
        //     0.5f, -0.5f, 0,
        //     0.5f,  0.5f, 0,
        //    -0.5f,  0.5f, 0
        //};

        ////IBO data
        //GLuint indexData[] = { 0, 1, 2, 3 };
        //m_numVertices = 4;
        //m_numIndices = 4;
        //m_vertexBuffer.SetData(RenderBufferDataType::VERTEX_BUFFER, (void*)vertexData, 3 * 4 * sizeof(float));
        //m_indexBuffer.SetData(RenderBufferDataType::INDEX_BUFFER, (void*)indexData, 4 * sizeof(int));

        //setup->m_vertexBuffer.SetData(RenderBufferDataType::kVertexBuffer, (void*)&vertices[0], 3 * setup->m_numVertices * sizeof(float));


        //setup->m_indexBuffer.SetData(RenderBufferDataType::kIndexBuffer, (void*)&indices[0], setup->m_numIndices * sizeof(int));

       // auto& uvs = mesh->UV();
        //setup->m_numUVs = uvs.size();
        //setup->m_uvBuffer.SetData(RenderBufferDataType::kUVBuffer, (void*)&uvs[0], 2 * setup->m_numUVs * sizeof(float));


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
}