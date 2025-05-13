#include "mesh_renderer_indirect.h"

namespace loopxia
{
    //void MeshRendererIndirect::p_InitDrawCommandsBuffer()
    //{
    //    glCreateBuffers(1, &m_drawCmdBuffer);
    //}

    //void MeshRendererIndirect::p_UpdateDrawCommandsBuffer()
    //{
    //    if (m_drawCommands.empty()) {
    //        return;
    //    }

    //    glNamedBufferStorage(m_drawCmdBuffer, sizeof(m_drawCommands[0]) * m_drawCommands.size(),
    //        (const void*)m_drawCommands.data(), GL_DYNAMIC_STORAGE_BIT);
    //}

    //void MeshRendererIndirect::p_InitPerObjectBuffer()
    //{
    //    glCreateBuffers(1, &m_perObjectBuffer);
    //    glNamedBufferStorage(m_perObjectBuffer, sizeof(PerObjectData) * Meshes.size(),
    //        NULL, GL_DYNAMIC_STORAGE_BIT);
    //}

    //void MeshRendererIndirect::p_UpdatePerObjectBuffer()
    //{
    //    glNamedBufferSubData(m_perObjectBuffer, 0, ARRAY_SIZE_IN_BYTES(PerObjectDataVector),
    //        PerObjectDataVector.data());
    //}

    //void MeshRendererIndirect::p_UpdateSSBOs()
    //{
    //    std::vector<PerObjectData> PerObjectDataVector;
    //    PerObjectDataVector.resize(m_meshToSetupMap.size());

    //    for (int i = 0; i < m_meshes.size(); i++) {
    //        // TODO: move to math3d
    //        Matrix4f FinalWorldMatrix = ObjectMatrix * m_meshes[i].m_transformation;
    //        Matrix4f WorldInverse = FinalWorldMatrix.Inverse();
    //        Matrix4f WorldInverseTranspose = WorldInverse.Transpose();

    //        PerObjectDataVector[i].WorldMatrix = FinalWorldMatrix;
    //        PerObjectDataVector[i].NormalMatrix = WorldInverseTranspose;
    //        PerObjectDataVector[i].MaterialIndex.x = m_meshes[i].m_materialIndex;
    //    }

    //    glNamedBufferSubData(m_perObjectBuffer, 0, ARRAY_SIZE_IN_BYTES(PerObjectDataVector),
    //        PerObjectDataVector.data());

    //    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, SSBO_INDEX_PER_OBJ_DATA, m_perObjectBuffer);
    //    //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, SSBO_INDEX_MATERIAL_COLORS, m_colorsBuffer);
    //   // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, SSBO_INDEX_DIFFUSE_MAPS, m_diffuseMapBuffer);
    //   // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, SSBO_INDEX_NORMAL_MAPS, m_normalMapBuffer);
    //}

    //void MeshRendererIndirect::RenderIndirect(std::vector<MeshRenderSetup*> meshSetups)
    //{
    //    UpdatePerObjectData(ObjectMatrix);

    //    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_drawCmdBuffer);

    //    glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, NULL,
    //        (GLsizei)m_meshes.size(), 0);

    //    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);


    //    std::vector<DrawElementsIndirectCommand> DrawCommands;
    //    DrawCommands.resize(Meshes.size());

    //    for (int i = 0; i < Meshes.size(); i++) {
    //        DrawElementsIndirectCommand Cmd;
    //        Cmd.Count = Meshes[i].NumIndices;
    //        Cmd.InstanceCount = 1;
    //        Cmd.FirstIndex = Meshes[i].BaseIndex;
    //        Cmd.BaseVertex = Meshes[i].BaseVertex;
    //        Cmd.BaseInstance = 0;

    //        DrawCommands[i] = Cmd;
    //    }

    //    glCreateBuffers(1, &m_drawCmdBuffer);
    //    glNamedBufferStorage(m_drawCmdBuffer, sizeof(DrawCommands[0]) * DrawCommands.size(),
    //        (const void*)DrawCommands.data(), 0);
    //}


}