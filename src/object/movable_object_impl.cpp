#include "object/movable_object_impl.h"

namespace loopxia
{
    MovableObjectImpl::MovableObjectImpl() : m_transform(this)
    {
    }

    void MovableObjectImpl::OnParentChange(MovableObject* oldParent, MovableObject* newParent)
    {
        m_transform._RecomputeTransform();
        m_parentChangeEvent.Signal(oldParent, newParent);
    }

    loopxia::Transform* MovableObjectImpl::Transform()
    {
        return &m_transform;
    }

    EventConnection MovableObjectImpl::EventListenParentChange(std::function<bool(MovableObject*, MovableObject*)> func)
    {
        return m_parentChangeEvent.connect(func);
    }
}