#include "scene_renderer_impl.h"

namespace loopxia
{
    static void Render(const GameTime& time, std::vector<SceneNode*>& sceneNodes)
    {
        auto sceneNode = *sceneNodes.rbegin();
        sceneNodes.pop_back();

        auto components = sceneNode->GetAttachedComponents();
        for (auto c : components) {
            if(auto r = dynamic_cast<>)
        }
    }

    void SceneRendererImpl::SetScene(Scene* scene)
    {
        m_pScene = scene;
    }

    void SceneRendererImpl::Render(const GameTime& time) 
    {
        // naive implementation
        // tranverse through scene and gather all node which render

        Render(m_pScene->SceneRoot(), time);
    }

    SceneRenderer* CreateSceneRenderer()
    {
        return new SceneRendererImpl();
    }
}