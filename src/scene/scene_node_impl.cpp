#include "scene/scene_node_impl.h"

namespace loopxia
{
    SceneNodeImpl::SceneNodeImpl(SceneNodeImpl* parent) : m_parent(parent), m_transform(this)
    {
        if (m_parent) {
            m_parent->AddChild(this);
        }
    }

    void SceneNodeImpl::OnParentChange()
    {
        m_transform._RecomputeTransform();
    }

    loopxia::Transform* SceneNodeImpl::Transform()
    {
        return &m_transform;
    }
    
    void SceneNodeImpl::AttachComponent(Component* obj)
    {
        auto it = std::find(m_components.begin(), m_components.end(), obj);
        if (it != m_components.end()) {
            // already exist
            return;
        }

        m_components.push_back(obj);
    }

    void SceneNodeImpl::DetachComponent(Component* obj)
    {
        auto it = std::find(m_components.begin(), m_components.end(), obj);
        if (it == m_components.end()) {
            // does not exist
            return;
        }

        m_components.erase(it);
    }

    std::vector<Component*> SceneNodeImpl::GetAttachedComponents()
    {
        return m_components;
    }

    SceneNode* CreateSceneNode(SceneNode* parent)
    {
        return new SceneNodeImpl(static_cast<SceneNodeImpl*>(parent));
    }
}
