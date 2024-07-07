#pragma once

#include "loopxia/graph/node.h"
#include "loopxia/scene/transform.h"
#include "loopxia/scene/component/component.h"

namespace loopxia
{
    class SceneNode : public Node<SceneNode>
    {
    public:
        virtual ~SceneNode() = default;

        virtual void OnParentChange() = 0;
        virtual loopxia::Transform* Transform() = 0;

        virtual void AttachComponent(Component* obj) = 0; 
        virtual void DetachComponent(Component* obj) = 0;
        virtual std::vector<Component*> GetAttachedComponents() = 0;
    };

    SceneNode* CreateSceneNode(SceneNode* parent);
}
