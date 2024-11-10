#pragma once

#include "instance_tracker.h"
#include "object.h"
#include "loopxia/graph/node.h"
#include "loopxia/event.h"
#include <functional>

namespace loopxia
{
    class MovableObject : public Object, public InstanceTracker<MovableObject>, public Node<MovableObject>
    {
    public:
        MovableObject();
        ~MovableObject();

    public:
        virtual loopxia::Transform* Transform() = 0;
        virtual EventConnection EventListenParentChange(std::function<void(MovableObject*, MovableObject*)> func ) = 0;
    };

}