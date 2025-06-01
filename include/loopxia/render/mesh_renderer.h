#pragma once

#include "loopxia/resource/mesh.h"
#include "loopxia/render/renderable.h"

namespace loopxia
{
    struct AnimationState
    {
        // animationIndex, can be -1 to indicate no animation
        int animationIndex1 = -1;
        int animationIndex2 = -1;
        // if animationIndex2 is not -1 it means animating between two different animation
        double animTime = 0;  //
    };

    class MeshRenderInstance
    {
    public:
        virtual ~MeshRenderInstance() = default;

        virtual Matrix4x4 GetWorldMatrix() = 0;
        virtual void SetWorldMatrix(Matrix4x4 m) = 0;

        virtual void SetAnimation(AnimationState& state) = 0;
        virtual AnimationState GetAnimationState() const = 0;

        virtual void EvaluateAnimation() = 0;

        virtual void SetBoneTransformations(const std::vector<Matrix4x4>& boneTransformations) = 0;
        virtual std::vector<Matrix4x4> GetBoneTransformations() const = 0;

        virtual std::shared_ptr<Mesh> GetMesh() = 0;
    };

    class MeshRenderer
    {
    public:
        virtual ~MeshRenderer() = default;

        // indicate start of a render cycle, always call this before calling the render functions
        virtual void BeginRender() = 0;
        // upload data to gpu and perform actual render
        virtual void EndRender() = 0;

        // add the mesh to render, call within begin and end render
        // returns a unique mesh instance for controlling render world matrix
        virtual MeshRenderInstance* AddMesh(const std::shared_ptr<Mesh> mesh) = 0;
        virtual void RemoveMesh(MeshRenderInstance* instance) = 0;

        virtual void Render(MeshRenderInstance* instance, Matrix4x4 vpMatrix) = 0;

        // for dynamic animation whereby the bones are controlled dynamically
        // virtual bool SetBones(const Mesh* mesh, int meshId) = 0;
    };

    MeshRenderer* CreateMeshRenderer();
}
