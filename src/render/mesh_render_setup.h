#pragma once

#include <GL/glew.h>

namespace loopxia
{
    class MeshRenderInstance;
    struct MeshRenderSetup
    {
        uint32_t m_numVertices = 0;
        uint32_t m_numIndices = 0;
        uint32_t m_numUVs = 0;

        GLuint m_textureID = 0;

        // mesh vertices and indices are appended in a contiguous VAO memory
        int m_baseVertex = 0;
        int m_baseIndex = 0;

        // instances of this mesh
        std::vector<MeshRenderInstance*> m_instances;
    };
}
