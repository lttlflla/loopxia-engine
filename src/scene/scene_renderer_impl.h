#pragma once
#include "loopxia/scene/scene_renderer.h"

namespace loopxia
{
    // SceneRendererImpl observe changes in scene hierarchy and camera view and optimize render pipeline
    class SceneRendererImpl : public SceneRenderer
    {
    public:
        void SetScene(Scene* scene) override;
        void Render(const GameTime& time) override;

    private:
        Scene* m_pScene = nullptr;
    };
}