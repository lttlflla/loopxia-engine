#pragma once

#include "loopxia/object/movable_object.h"
#include "loopxia/bounding_volume/bounding_volume.h"

namespace loopxia
{
    class Camera : public virtual MovableObject
    {
    public:
        virtual ~Camera() = default;

        virtual void SetPosition(const Vector3& position) = 0;
        virtual void SetFOV(float fov /* degrees */) = 0;
        virtual void SetLookDirection(const Vector3& dir) = 0;
        //void Rotate(float angleDegrees, );
        
        virtual Vector3 GetPosition() const = 0;
        virtual Matrix4x4 GetProjectionMatrix() const = 0;
        virtual Matrix4x4 GetViewMatrix() const = 0;

        virtual void LookAtAndFitScreen(BoundingVolume& v) = 0;
    };

    Camera* CreateCamera(const Vector3& position, float fov /* degrees */, float aspectRatio, float nearClip, float farClip);
}