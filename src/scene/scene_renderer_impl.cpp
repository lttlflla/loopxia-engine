#include "scene_renderer_impl.h"

namespace loopxia
{
    static void Render(const GameTime& time, std::vector<SceneNode*>& sceneNodes)
    {
        auto sceneNode = *sceneNodes.rbegin();
        sceneNodes.pop_back();

    }

    SceneRendererImpl::SceneRendererImpl() : m_pMeshRenderer(new MeshRendererImpl())
    {
    }

    void SceneRendererImpl::SetScene(Scene* scene)
    {
        m_pScene = scene;

        _PrepareRenderers();
    }

    void SceneRendererImpl::Render(const GameTime& time) 
    {
        // find out which scene node are in the visible area
        // 
        // tranverse through scene and gather all node which render
        m_pMeshRenderer->BeginRender();
        m_pMeshRenderer->Render();
        m_pMeshRenderer->EndRender();
    }

    void SceneRendererImpl::_PrepareRenderers()
    {
        auto n = m_pScene->SceneRoot();
        // loop through all children and find mesh
        while (n) {
            n = n->SceneNodeChildren
        }
    }

    SceneRenderer* CreateSceneRenderer()
    {
        return new SceneRendererImpl();
    }


}