#include "loopxia/object/gameobject.h"
#include "loopxia/object/transform.h"

namespace loopxia
{
    namespace impl
    {
        class GameObjectImpl
        {
        public:
            GameObjectImpl(GameObject* self, GameObject* parent) : m_parent(parent), m_transform(m_self)
            {
                m_parent->AddChild(self);
            }

            GameObject* Parent()
            {
                return m_parent;
            }

            void SetParent(GameObject* parent)
            {
                if (m_parent) {
                    m_parent->RemoveChild(m_self);
                }

                m_parent = parent;
                m_parent->AddChild(m_self);
                m_transform._RecomputeTransform();
            }
            
            loopxia::Transform& Transform()
            {
                return m_transform;
            }

            std::vector<GameObject*> Children()
            {
                return m_children;
            }

            void AddChild(GameObject* obj)
            {
                auto it = std::find(m_children.begin(), m_children.end(), obj);
                if (it == m_children.end()) {
                    m_children.push_back(obj);
                }
            }

            void RemoveChild(GameObject* obj)
            {
                auto it = std::find(m_children.begin(), m_children.end(), obj);
                if (it != m_children.end()) {
                    m_children.erase(it);
                }
            }

        private:
            GameObject* m_parent;
            GameObject* m_self;
            loopxia::Transform m_transform;
            std::vector<GameObject*> m_children;
        };
    }

    GameObject::GameObject(GameObject* parent) : m_impl(new impl::GameObjectImpl(this, parent))
    {

    }

    GameObject::~GameObject()
    {
        delete m_impl;
    }

    GameObject* GameObject::Parent()
    {
        return m_impl->Parent();
    }

    void GameObject::SetParent(GameObject* parent)
    {
        m_impl->SetParent(parent);
    }


    loopxia::Transform& GameObject::Transform()
    {
        return m_impl->Transform();
    }

    std::vector<GameObject*> GameObject::Children()
    {
        return m_impl->Children();
    }

    void GameObject::AddChild(GameObject* obj)
    {
        m_impl->AddChild(obj);
    }

    void GameObject::RemoveChild(GameObject* obj)
    {
        m_impl->RemoveChild(obj);
    }
}
