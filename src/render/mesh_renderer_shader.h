#pragma once

#include "loopxia/render/shader.h"
#include "loopxia/render/render_buffer.h"

#include <GL/glew.h>
#include <memory>

namespace loopxia
{
    const int kNumOfBuffers = 6;
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

        RenderBuffer* GetBoneIdBuffer();
        RenderBuffer* GetBoneWeightBuffer();

    private:
        // shader for the renderer
        Shader m_meshShader;

        GLuint m_VAO; // vertex array object

        GLuint m_attributeBuffers[kNumOfBuffers];

        // the attributes in the vertex array object
        std::unique_ptr<RenderBuffer> m_indexBuffer;
        std::unique_ptr<RenderBuffer> m_vertexBuffer; // vertex position buffer
        std::unique_ptr<RenderBuffer> m_normalBuffer;
        std::unique_ptr<RenderBuffer> m_uvBuffer;

        std::unique_ptr<RenderBuffer> m_boneIDBuffer;
        std::unique_ptr<RenderBuffer> m_boneWeightBuffer;

        int m_posAttribute = -1;
        int m_uvAttribute = -1;
        int m_normalAttribute = -1;
        int m_textureAttribute = -1;

        int m_boneIdAttribute = -1;
        int m_boneWeightAttribute = -1;

        int m_wvpAttribute = -1;
    };
}
