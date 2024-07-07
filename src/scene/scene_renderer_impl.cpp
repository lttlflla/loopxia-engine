#include "scene_renderer_impl.h"

namespace loopxia
{
    void SceneRendererImpl::SetScene(Scene* scene)
    {
        m_pScene = scene;
    }

    void SceneRendererImpl::Render(const GameTime& time) 
    {

    }

    SceneRenderer* CreateSceneRenderer()
    {
        return new SceneRendererImpl();
    }
}