#include "loopxia/scene/game_object.h"
#include "loopxia/scene/transform.h"

namespace loopxia
{
    namespace impl
    {
        class GameObjectImpl
        {
        public:
            GameObjectImpl(GameObject* self, GameObject* parent) : m_parent(parent), m_transform(m_self)
            {
                if (m_parent) {
                    m_parent->AddChild(self);
                }
            }

            void OnParentChange()
            {
                m_transform._RecomputeTransform();
            }

            loopxia::Transform& Transform()
            {
                return m_transform;
            }

        private:
            GameObject* m_parent;
            GameObject* m_self;
            loopxia::Transform m_transform;
        };
    }

    GameObject::GameObject(GameObject* parent) : m_impl(new impl::GameObjectImpl(this, parent))
    {
    }

    GameObject::~GameObject()
    {
        delete m_impl;
    }

    loopxia::Transform& GameObject::Transform()
    {
        return m_impl->Transform();
    }

    void GameObject::OnParentChange()
    {
        return m_impl->OnParentChange();
    }
}
