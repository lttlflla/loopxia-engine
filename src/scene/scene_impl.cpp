#include "scene/scene_impl.h"
#include "scene/scene_node_impl.h"

namespace loopxia
{
    SceneImpl::SceneImpl() : m_root(new SceneNodeImpl(nullptr))
    {
    }

    SceneNode* SceneImpl::SceneRoot()
    {
        return m_root.get();
    }

    void SceneImpl::Render()
    {

    }

    Scene* CreateScene()
    {
        return new SceneImpl();
    }
}