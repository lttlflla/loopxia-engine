#include "game/camera_controller_impl.h"
#include "loopxia/event.h"

namespace loopxia
{
    void CameraControllerImpl::Init(Game* game)
    {
        auto keyDownFunc = [this](Event& evt, KeyEvent& keyEvt) -> bool {
            switch (keyEvt.keyCode) {
            case KeyCode::KEY_DOWN:
                m_camDirUpDown = -1;
                break;
            case KeyCode::KEY_UP:
                m_camDirUpDown = 1;
                break;
            case KeyCode::KEY_LEFT:
                m_camDirLeftRight = 1;
                break;
            case KeyCode::KEY_RIGHT:
                m_camDirLeftRight = -1;
                break;
            }

            return true;
        };

        game->KeyDown.connect(keyDownFunc);

        auto keyUpFunc = [this](Event& evt, KeyEvent& keyEvt) -> bool {
            switch (keyEvt.keyCode) {
            case KeyCode::KEY_DOWN:
                if (m_camDirUpDown == -1) {
                    m_camDirUpDown = 0;
                }
                break;
            case KeyCode::KEY_UP:
                if (m_camDirUpDown == 1) {
                    m_camDirUpDown = 0;
                }
                break;
            case KeyCode::KEY_LEFT:
                if (m_camDirLeftRight == 1) {
                    m_camDirLeftRight = 0;
                }
                break;
            case KeyCode::KEY_RIGHT:
                if (m_camDirLeftRight == -1) {
                    m_camDirLeftRight = 0;
                }
                break;
            }

            return true;
        };

        game->KeyUp.connect(keyUpFunc);

        auto updateEventFunc = [this](const GameTime& time) -> bool {
            Update(time);
            return true;
        };

        game->GameUpdate.connect(updateEventFunc);
    }

    void CameraControllerImpl::SetCamera(loopxia::Camera* camera)
    {
        m_camera = camera;
    }

    void CameraControllerImpl::Update(const loopxia::GameTime& time)
    {
        Vector3 camMoveDir(0, 0, 0);
        camMoveDir = Vector3(m_camDirLeftRight, 0, m_camDirUpDown);
        if (camMoveDir != Vector3(0, 0, 0)) {
            camMoveDir = math::Normalize(camMoveDir);
            auto sec = time.ElapsedTimeSeconds();
            camMoveDir *= sec * 20;
            m_camera->SetPosition(m_camera->GetPosition() + camMoveDir);
        }
    }

    CameraController* CreateCameraController()
    {
        return new CameraControllerImpl;
    }
}
