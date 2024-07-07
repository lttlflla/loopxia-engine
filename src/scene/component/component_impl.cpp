#include "component_impl.h"

namespace loopxia
{
    ComponentImpl::ComponentImpl()
    {
    }

    SceneNode* ComponentImpl::GetSceneNode()
    {
        return m_pSceneNode;
    }

    void ComponentImpl::SetSceneNode(SceneNode* sceneNode)
    {
        auto old = m_pSceneNode;
        m_pSceneNode = sceneNode;

        OnSceneNodeParentChange.Signal(old, m_pSceneNode);
    }
}