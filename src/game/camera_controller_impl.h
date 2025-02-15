#pragma once
#include "loopxia/game/camera_controller.h"

namespace loopxia
{
    class CameraControllerImpl : public CameraController
    {
    public:
        void Init(Game* game) override;
        void SetCamera(loopxia::Camera* camera) override;
        void Update(const loopxia::GameTime& time) override;

    private:
        Game* m_game = nullptr;
        loopxia::Camera* m_camera = nullptr;

        loopxia::Vector3 m_cameraVelocity;
        int m_camDirUpDown = 0;
        int m_camDirLeftRight = 0;

        EventConnection m_keyDownEventConnection;
        EventConnection m_keyUpEventConnection;
        EventConnection m_updateEventConnection;

    };
}