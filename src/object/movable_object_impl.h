#pragma once

#include "loopxia/object/movable_object.h"
#include "transform_impl.h"
#include "loopxia/event.h"

namespace loopxia
{
    class MovableObjectImpl : public virtual MovableObject
    {
    public:
        MovableObjectImpl();
        ~MovableObjectImpl() = default;

        void OnParentChange(MovableObject*, MovableObject*) override;
        loopxia::Transform* Transform() override;
        EventConnection EventListenParentChange(std::function<bool(MovableObject*, MovableObject*)> func) override;

    private:
        EventSignal<MovableObject* /*old parent*/, MovableObject* /* new parent*/> m_parentChangeEvent;
        loopxia::TransformImpl m_transform;
    };
}