#pragma once

#include <GL/glew.h>
#include <vector>

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
    

    const int kMaxNumBonesPerVertex = 4;
    struct VertexBoneData
    {
        uint32_t boneIDs[kMaxNumBonesPerVertex] = { 0 };
        float weights[kMaxNumBonesPerVertex] = { 0.0f };
        int index = 0;  // slot for the next update

        VertexBoneData()
        {
        }

        void AddBoneData(uint32_t boneID, float weight)
        {
            for (int i = 0; i < index; i++) {
                if (boneIDs[i] == boneID) {
                    return;
                }
            }

            if (weight == 0.0f) {
                return;
            }

            if (index == kMaxNumBonesPerVertex) {
                return;
                assert(0);
            }

            boneIDs[index] = boneID;
            weights[index] = weight;

            index++;
        }
    };
}
