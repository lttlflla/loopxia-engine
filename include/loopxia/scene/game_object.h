#pragma once

#include "loopxia/graph/node.h"
#include "loopxia/scene/transform.h"

namespace loopxia
{
    namespace impl
    {
        class GameObjectImpl;
    }

    class GameObject : public Node<GameObject>
    {
        friend class impl::GameObjectImpl;
    public:
        GameObject(GameObject* parent);
        ~GameObject();

        loopxia::Transform& Transform();

    protected:
        void OnParentChange();

    private:
        impl::GameObjectImpl* m_impl;

    };
}
