#pragma once

#include "loopxia/object/scriptable_object.h"
#include "loopxia/object/transform.h"
#include "loopxia/math.h"
#include <vector>

namespace loopxia
{
    namespace impl
    {
        class GameObjectImpl;
    }

    class GameObject : ScriptableObject
    {
        friend class impl::GameObjectImpl;
    public:
        GameObject(GameObject* parent);
        ~GameObject();

        GameObject* Parent();
        void SetParent(GameObject* parent);

        loopxia::Transform& Transform();

        std::vector<GameObject*> Children();

    protected:
        void AddChild(GameObject* obj);
        void RemoveChild(GameObject* obj);

    private:
        impl::GameObjectImpl* m_impl;

    };
}
