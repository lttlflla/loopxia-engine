#pragma once

namespace loopxia
{
    class Camera
    {
    public:
        virtual ~Camera() = default;

        virtual void SetPosition(const Vector3& position) = 0;
        virtual void SetFOV(float fov) = 0;
        virtual void SetLookDirection(const Vector3& dir) = 0;
        //void Rotate(float angleDegrees, );
        
        virtual Vector3 GetPosition() const = 0;
        virtual Matrix4x4 GetProjectionMatrix() const = 0;
        virtual Matrix4x4 GetViewMatrix() const = 0;
    };

    Camera* CreateCamera(const Vector3& position, float fov, float aspectRatio, float nearClip, float farClip);
}