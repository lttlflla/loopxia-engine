#pragma once

#include "loopxia/scene/scene_renderer.h"
#include "render/mesh_renderer_impl.h"

namespace loopxia
{
    // SceneRendererImpl observe changes in scene hierarchy and camera view and optimize render pipeline
    class SceneRendererImpl : public SceneRenderer
    {
    public:
        SceneRendererImpl();

        void SetScene(Scene* scene) override;
        void Render(const GameTime& time) override;

    private:
        // load resources to GPU
        void _PrepareRenderers();

    private:
        Scene* m_pScene = nullptr;

        MeshRendererImpl* m_pMeshRenderer = nullptr;
        std::unordered_map<SceneNode*, std::vector<int>> m_mapOfSceneNodeToMeshId;
    };
}