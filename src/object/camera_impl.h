#pragma once

#include "loopxia/object/camera.h"
#include "movable_object_impl.h"

namespace loopxia
{
    class CameraImpl : public virtual MovableObjectImpl<Camera>
    {
    public:
        CameraImpl(const glm::vec3& position, float fov /* degrees */, float aspectRatio, float nearClip, float farClip);
        
        Vector3 GetPosition() const override;
        void SetPosition(const Vector3& pos) override;
        void SetFOV(float fov) override;
        Matrix4x4 GetProjectionMatrix() const override;
        Matrix4x4 GetViewMatrix() const override;
        void SetLookDirection(const Vector3& dir) override;
        
        void LookAtAndFitScreen(BoundingVolume& v) override;

    protected:
        void UpdateProjectionMatrix();
        void UpdateViewMatrix();
        void SetAspectRatio(float aspectRatio);

    private:
        Vector3 m_position;
        Vector3 m_lookAtDir;
        Vector3 m_up;
        float m_fov; // vertical fov in degrees
        float m_aspectRatio; // aspect ratio. width / height
        float m_nearClip;
        float m_farClip;
        Matrix4x4 projectionMatrix;
        Matrix4x4 m_viewMatrix;
    };
}