#pragma once

#include "loopxia/graph/node.h"
#include "loopxia/math.h"
#include "loopxia/scene/component/component.h"
#include "loopxia/object/movable_object.h"

namespace loopxia
{
    class SceneNode : protected virtual MovableObject
    {
    public:
        virtual ~SceneNode() = default;

        virtual void AttachObject(MovableObject* obj) = 0;
        virtual void DetachObject(MovableObject* obj) = 0;

        SceneNode* Parent();
        void SetParent(SceneNode* parent);
        std::unordered_set<SceneNode*> SceneNodeChildren();
        std::unordered_set<MovableObject*> ObjectChildren();
    };

    SceneNode* CreateSceneNode(SceneNode* parent);
}
