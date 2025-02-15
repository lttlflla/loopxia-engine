#pragma once

#include "loopxia/object/camera.h"
#include "loopxia/math.h"
#include "loopxia/game/game.h"

namespace loopxia
{
    class CameraController : public Object, public InstanceTracker<CameraController>
    {
    public:
        virtual ~CameraController() = default;

        virtual void Init(Game* game) = 0;
        virtual void SetCamera(loopxia::Camera* camera) = 0;
        virtual void Update(const loopxia::GameTime& time) = 0;
    };

    CameraController* CreateCameraController();
}