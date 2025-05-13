#pragma once

#include "loopxia/object/movable_object.h"

namespace loopxia
{
    class SceneNode : public virtual MovableObject
    {
    public:
        virtual ~SceneNode() = default;

        virtual void AttachObject(Object* obj) = 0;
        virtual void DetachObject(Object* obj) = 0;
    };

    SceneNode* CreateSceneNode(SceneNode* parent);
}
