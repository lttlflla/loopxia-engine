#pragma once
#include <vector>
#include "loopxia/math.h"
#include "mesh_render_setup.h"

namespace loopxia
{
    class MeshRendererIndirect
    {
    public:
        void RenderIndirect(std::vector<MeshRenderSetup*> meshSetups);

    private:
        void p_InitDrawCommandsBuffer();
        void p_UpdateDrawCommandsBuffer();

        void p_InitPerObjectBuffer();
        void p_UpdatePerObjectBuffer();

        void p_UpdateSSBOs();

        struct PerObjectData {
            Matrix4x4 WorldMatrix;
            Matrix4x4 NormalMatrix;
            glm::ivec4 MaterialIndex = glm::ivec4(0);
        };


        // this must always be the same as the definition in opengl extension
        struct DrawElementsIndirectCommand {
            unsigned int count;         // Num elements (vertices)
            unsigned int instanceCount; // Number of instances to draw (a.k.a primcount)
            unsigned int firstIndex;    // Specifies a byte offset (cast to a pointer type) into the buffer bound to GL_ELEMENT_ARRAY_BUFFER to start reading indices from.
            int baseVertex;    // Specifies a constant that should be added to each element of indices when chosing elements from the enabled vertex arrays.
            unsigned int baseInstance;  // Specifies the base instance for use in fetching instanced vertex attributes.
        };

        // draw commands for all meshes and their instances
        std::vector<DrawElementsIndirectCommand> m_drawCommands;
        GLuint m_drawCmdBuffer = 0;

        GLuint m_perObjectBuffer = 0;
    };
}