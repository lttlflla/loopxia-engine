#pragma once

#include "loopxia/resource/mesh.h"
#include "loopxia/render/mesh_renderer.h"
#include "loopxia/render/shader.h"
#include "loopxia/render/render_buffer.h"
#include "mesh_render_setup.h"
#include "mesh_shader_animated.h"
#include "mesh_shader_static.h"
#include "../resource/mesh_impl.h"
#include <GL/glew.h>
#include <map>

namespace loopxia
{
    class MeshRendererImpl;
    class MeshRenderInstanceImpl : public MeshRenderInstance
    {
    public:
        MeshRenderInstanceImpl(int instanceId, MeshRendererImpl* pRenderer, std::shared_ptr<Mesh> pMesh);

        Matrix4x4 GetWorldMatrix() override;
        void SetWorldMatrix(Matrix4x4 m) override;

        void SetAnimation(AnimationState& state) override;
        AnimationState GetAnimationState() const override;

        void EvaluateAnimation() override;

        void SetBoneTransformations(const std::vector<Matrix4x4>& boneTransformations) override;
        std::vector<Matrix4x4> GetBoneTransformations() const override;

        std::shared_ptr<Mesh> GetMesh() override;

    private:
        int m_instanceId;
        int m_drawCommandIndex;
        
        Matrix4x4 m_worldMatrix;
        // if instancing, it should be 

        std::vector<Matrix4x4> m_boneTransformations;
        AnimationState m_animationState;

        MeshRendererImpl* m_pRenderer = nullptr;
        std::shared_ptr<Mesh> m_pMesh;
    };

    class MeshRendererImpl : public MeshRenderer
    {
    private:
    public: 
        MeshRendererImpl();

        void BeginRender() override;
        void EndRender() override;

        MeshRenderInstance* AddMesh(const std::shared_ptr<Mesh> mesh) override;
        void RemoveMesh(MeshRenderInstance* instance) override;

        void Render(MeshRenderInstance* instance, Matrix4x4 vpMatrix) override;

        void Init();

        void UpdateBuffer();

    private:
        void p_LoadTexture(const std::shared_ptr<Mesh> mesh, MeshRenderSetup* setup);
        void p_InitInstancing(const std::shared_ptr<Mesh> mesh, MeshRenderSetup* setup, int maxInstances);

        void p_RenderIndirect();


    private:
        bool m_bInitialized = false;

        // all meshes's vertex indices
        std::vector<int> m_indices;

        // buffer for all vertices attributes
        std::vector<Vector3> m_vertices;
        std::vector<Vector3> m_normals;
        std::vector<Vector2> m_uvs;
        std::vector<VertexBoneData> m_boneWeightByVertex;


        std::map<std::shared_ptr<Mesh>, MeshRenderSetup> m_meshToSetupMap;

        bool m_bUseIndirectRender = false;

        //MeshShaderStatic m_staticMeshShader;
        MeshShaderAnimated m_animatedMeshShader;
    };
}