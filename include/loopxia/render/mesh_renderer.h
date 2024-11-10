#pragma once

#include "loopxia/resource/mesh.h"
#include "loopxia/render/renderable.h"

namespace loopxia
{
    class MeshRenderer
    {
    public:
        // indicate start of a render cycle, always call this before calling the render functions
        virtual void BeginRender() = 0;
        // upload data to gpu and perform actual render
        virtual void EndRender() = 0;

        // add the mesh to render, call within begin and end render
        // returns a unique mesh id for future use
        virtual int AddMesh(const Mesh* mesh) = 0;
        virtual void RemoveMesh(int meshId) = 0;

        // for animation based on animation data in the mesh
        virtual void Render(int meshId, Matrix4x4 wvpMatrix) = 0;
        virtual void Render(int meshId, Matrix4x4 wvpMatrix, int animationIndex) = 0;
        virtual void Render(int meshId, Matrix4x4 wvpMatrix, int animationIndex1, int animationIndex2, float animationProgress) = 0;

        // for dynamic animation whereby the bones are controlled dynamically
        // virtual bool SetBones(const Mesh* mesh, int meshId) = 0;
    };

    MeshRenderer* CreateMeshRenderer();
}
