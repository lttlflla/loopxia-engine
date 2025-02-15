#pragma once

#include "instance_tracker.h"
#include "object.h"
#include "loopxia/object/transform.h"
#include "loopxia/graph/node.h"
#include "loopxia/event.h"
#include <functional>

namespace loopxia
{
    class MovableObject : public Object, public InstanceTracker<MovableObject>, public Node<MovableObject>
    {
    public:
        virtual ~MovableObject() = default;

        virtual void OnParentChange(MovableObject*, MovableObject*) = 0;
        virtual loopxia::Transform* Transform() = 0;
        virtual EventConnection EventListenParentChange(std::function<bool(MovableObject*, MovableObject*)> func ) = 0;
    };

}