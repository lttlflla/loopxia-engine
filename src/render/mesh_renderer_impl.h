#pragma once

#include "loopxia/resource/mesh.h"
#include "loopxia/render/mesh_renderer.h"
#include "loopxia/render/shader.h"
#include "loopxia/render/render_buffer.h"
#include <GL/glew.h>

namespace loopxia
{
    class MeshRendererImpl : public MeshRenderer
    {
    public: 
        MeshRendererImpl();

        void BeginRender() override;
        void EndRender() override;

        int AddMesh(const Mesh* mesh) override;
        void RemoveMesh(int meshId) override;

        // for animation based on animation data in the mesh
        void Render(int meshId, Matrix4x4 wvpMatrix) override;
        void Render(int meshId, Matrix4x4 wvpMatrix, int animationIndex) override;
        void Render(int meshId, Matrix4x4 wvpMatrix, int animationIndex1, int animationIndex2, float animationProgress) override;

    private:
        void p_LoadTexture(const Mesh* mesh);

    private:
        // set up the shader
        Shader m_meshShader;

        RenderBuffer m_vertexBuffer;
        RenderBuffer m_indexBuffer;

        RenderBuffer m_normalBuffer;
        RenderBuffer m_uvBuffer;

        int m_numVertices = 0;
        int m_numIndices = 0;
        int m_numUVs = 0;
        GLuint m_VAO; // vertex array object

        GLuint m_textureID;

        Matrix4x4 m_wvp;
    };
}