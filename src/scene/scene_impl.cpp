#include "scene/scene_impl.h"
#include "scene/scene_node_impl.h"

namespace loopxia
{
    SceneImpl::SceneImpl() : m_root(new SceneNodeImpl<SceneNode>(nullptr))
        , m_sceneRenderer(new SceneRendererImpl())
    {
        m_sceneRenderer->SetScene(this);
    }

    SceneNode* SceneImpl::SceneRoot()
    {
        return m_root.get();
    }

    void SceneImpl::SetActiveCamera(Camera* camera)
    {
        m_pCamera = camera;
    }

    Camera* SceneImpl::GetActiveCamera()
    {
        return m_pCamera;
    }

    void SceneImpl::Render(const GameTime& gameTime)
    {
        m_sceneRenderer->Render(gameTime);
    }

    Scene* CreateScene()
    {
        return new SceneImpl();
    }
}