#pragma once

#include "loopxia/game/game.h"
#include "loopxia/scene/scene.h"

namespace loopxia
{
    // scene renderer renders a scene
    class SceneRenderer : public Object, public InstanceTracker<SceneRenderer>
    {
    public:
        virtual ~SceneRenderer() = default;

        virtual void SetScene(Scene* scene) = 0;
        virtual void Render(const GameTime& time) = 0;
    };

    SceneRenderer* CreateSceneRenderer();
}