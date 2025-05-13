#include "object/movable_object_impl.h"
#include "loopxia/scene/avatar.h"
#include "loopxia/scene/scene_node.h"
#include "loopxia/object/camera.h"

namespace loopxia
{
    template <class T>
    MovableObjectImpl<T>::MovableObjectImpl(MovableObject* parent) : m_transform(this)
    {
        static_assert(std::is_base_of<MovableObject, T>::value, "T must be derived from MovableObject");
        SetParent(parent);
    }

    template <class T>
    void MovableObjectImpl<T>::OnParentChange(MovableObject* oldParent, MovableObject* newParent)
    {
        m_transform._RecomputeTransform();
        m_parentChangeEvent.Signal(oldParent, newParent);
    }

    template <class T>
    loopxia::Transform* MovableObjectImpl<T>::Transform()
    {
        return &m_transform;
    }

    template <class T>
    EventConnection MovableObjectImpl<T>::EventListenParentChange(std::function<bool(MovableObject*, MovableObject*)> func)
    {
        return m_parentChangeEvent.connect(func);
    }

    template <class T>
    void MovableObjectImpl<T>::SetParent(MovableObject* parent)
    {
        auto oldParent = MovableObject::Parent();
        MovableObject::SetParent(parent);
        OnParentChange(oldParent, parent);
    }


    template class MovableObjectImpl<SceneNode>;
    template class MovableObjectImpl<Avatar>;
    template class MovableObjectImpl<Camera>;
}