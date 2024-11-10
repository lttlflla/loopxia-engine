#pragma once

#include "loopxia/event.h"

namespace loopxia
{
    class SceneNode;

    // a component that is attachable to scene node
    class Component
    {
    public:
        virtual ~Component() = default;

        EventSignal<SceneNode* /*old scene node*/, SceneNode* /* new scene node*/> OnSceneNodeParentChange;

        virtual SceneNode* GetSceneNode() = 0;

    protected:
        friend class SceneNode;

        // attached to new scene node
        virtual void SetSceneNode(SceneNode* sceneNode) = 0;
    };
};