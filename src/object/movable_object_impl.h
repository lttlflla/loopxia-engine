#pragma once

#include "loopxia/object/movable_object.h"
#include "transform_impl.h"
#include "loopxia/event.h"

namespace loopxia
{
    template <class T>
    class MovableObjectImpl :  public virtual T
    {
    public:
        MovableObjectImpl(MovableObject* parent = nullptr);
        ~MovableObjectImpl() = default;

        loopxia::Transform* Transform() override final;
        EventConnection EventListenParentChange(std::function<bool(MovableObject*, MovableObject*)> func) override final;

        virtual void SetParent(MovableObject* parent) final;

    protected:
        void OnParentChange(MovableObject* oldParent, MovableObject* newParent) override;

    private:
        EventSignal<MovableObject* /*old parent*/, MovableObject* /* new parent*/> m_parentChangeEvent;
        loopxia::TransformImpl m_transform;
    };
}