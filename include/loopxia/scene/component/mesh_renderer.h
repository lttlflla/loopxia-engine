#pragma once

#include "loopxia/resource/mesh.h"
#include "loopxia/scene/component/component_renderable.h"
#include "loopxia/scene/component/component_updatable.h"

namespace loopxia
{
    namespace impl
    {
        class MeshRendererImpl;
    }

    class MeshRenderer : public ComponentUpdatable, public ComponentRenderable
    {
    public:
        MeshRenderer();
        ~MeshRenderer();

        // set the mesh to render
        void SetMesh(const Mesh* mesh);

        // set world view projection matrix
        void SetWVP(Matrix4x4 matrix);

        void Render();
    };
}
