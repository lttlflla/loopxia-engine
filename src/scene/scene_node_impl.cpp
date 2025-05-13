#include "scene/scene_node_impl.h"
#include "scene/avatar_impl.h"

namespace loopxia
{
    template<class T>
    SceneNodeImpl<T>::SceneNodeImpl(SceneNode* parent) : MovableObjectImpl<T>(parent)
    {
        static_assert(std::is_base_of<SceneNode, T>::value, "T must be derived from SceneNode");
    }

    template<class T>
    void SceneNodeImpl<T>::AttachObject(Object* obj)
    {
        auto it = std::find(m_objects.begin(), m_objects.end(), obj);
        if (it != m_objects.end()) {
            // already exist
            return;
        }

        m_objects.push_back(obj);
    }

    template<class T>
    void SceneNodeImpl<T>::DetachObject(Object* obj)
    {
        auto it = std::find(m_objects.begin(), m_objects.end(), obj);
        if (it == m_objects.end()) {
            // does not exist
            return;
        }

        m_objects.erase(it);
    }

    template<class T>
    std::vector<Object*> SceneNodeImpl<T>::GetAttachedObjects()
    {
        return m_objects;
    }

    SceneNode* CreateSceneNode(SceneNode* parent)
    {
        return new SceneNodeImpl<SceneNode>(dynamic_cast<SceneNodeImpl<SceneNode>*>(parent));
    }

    template class SceneNodeImpl<SceneNode>;
    template class SceneNodeImpl<Avatar>;
}
