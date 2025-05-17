#pragma once

#include "loopxia/render/shader.h"
#include "loopxia/render/render_buffer.h"

#include <GL/glew.h>
#include <memory>

namespace loopxia
{
    const int kNumOfBuffers = 3;
    class MeshRendererShader
    {
    public:
        MeshRendererShader(const std::string& shaderFileVS, const std::string& shaderFileFS);

        void SetupShaderBuffers();

        void BeginRender();
        void EndRender();

        void SetTextureId(GLuint textureId);
        void SetWVP(Matrix4x4 matrix);

        RenderBuffer* GetIndexBuffer();
        RenderBuffer* GetVertexBuffer();
        RenderBuffer* GetNormalBuffer();
        RenderBuffer* GetUVBuffer();

    private:
        // shader for the renderer
        Shader m_meshShader;

        GLuint m_VAO; // vertex array object

        GLuint m_attributeBuffers[kNumOfBuffers];

        // the attributes in the vertex array object
        std::unique_ptr<RenderBuffer> m_indexBuffer;
        std::unique_ptr<RenderBuffer> m_vertexBuffer;
        std::unique_ptr<RenderBuffer> m_normalBuffer;
        std::unique_ptr<RenderBuffer> m_uvBuffer;
    };
}
