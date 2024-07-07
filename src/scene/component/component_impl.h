#pragma once

#include "loopxia/event.h"
#include "loopxia/scene/component/component.h"

namespace loopxia
{
    class SceneNode;

    // a component that is attachable to scene node
    class ComponentImpl : public Component
    {
    public:
        ComponentImpl();

        SceneNode* GetSceneNode() override;

    protected:
        // attached to new scene node
        void SetSceneNode(SceneNode* sceneNode) override;

    private:
        SceneNode* m_pSceneNode = nullptr;
    };
};