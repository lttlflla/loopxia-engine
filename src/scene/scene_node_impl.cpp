#include "scene/scene_node_impl.h"

namespace loopxia
{
    SceneNodeImpl::SceneNodeImpl(SceneNodeImpl* parent) : m_parent(parent)
    {
        if (m_parent) {
            m_parent->AddChild(this);
        }
    }


    void SceneNodeImpl::AttachObject(Object* obj)
    {
        auto it = std::find(m_objects.begin(), m_objects.end(), obj);
        if (it != m_objects.end()) {
            // already exist
            return;
        }

        m_objects.push_back(obj);
    }

    void SceneNodeImpl::DetachObject(Object* obj)
    {
        auto it = std::find(m_objects.begin(), m_objects.end(), obj);
        if (it == m_objects.end()) {
            // does not exist
            return;
        }

        m_objects.erase(it);
    }

    std::vector<Object*> SceneNodeImpl::GetAttachedObjects()
    {
        return m_objects;
    }

    SceneNode* CreateSceneNode(SceneNode* parent)
    {
        return new SceneNodeImpl(dynamic_cast<SceneNodeImpl*>(parent));
    }
}
