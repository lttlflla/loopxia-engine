#include "scene/component/camera_impl.h"

namespace loopxia
{
    CameraImpl::CameraImpl(const glm::vec3& position, float fov, float aspectRatio, float nearClip, float farClip)
        : m_position(position), m_lookAtDir(glm::vec3(0.0f, 0.0f, -1.0f)), m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
        m_fov(fov), m_aspectRatio(aspectRatio), m_nearClip(nearClip), m_farClip(farClip) {
        UpdateProjectionMatrix();
        UpdateViewMatrix();
    }

    Vector3  CameraImpl::GetPosition() const
    {
        return m_position;
    }

    void CameraImpl::SetPosition(const Vector3& pos)
    {
        m_position = pos;
        UpdateViewMatrix();
    }

    void CameraImpl::SetFOV(float fov)
    {
        m_fov = fov;
        UpdateProjectionMatrix();
    }

    Matrix4x4 CameraImpl::GetProjectionMatrix() const {
        return projectionMatrix;
    }

    Matrix4x4 CameraImpl::GetViewMatrix() const
    {
        return m_viewMatrix;
    }

    void CameraImpl::UpdateProjectionMatrix() {
        projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearClip, m_farClip);
    }

    void CameraImpl::UpdateViewMatrix() {
        m_viewMatrix = glm::lookAt(m_position, m_position + m_lookAtDir, m_up);
    }

    void CameraImpl::SetAspectRatio(float aspectRatio) {
        this->m_aspectRatio = aspectRatio;
        UpdateProjectionMatrix();
    }

    void CameraImpl::SetLookDirection(const Vector3& dir) {
        m_lookAtDir = math::Normalize(dir);
        UpdateViewMatrix();
    }

    Camera* CreateCamera(const Vector3& position, float fov, float aspectRatio, float nearClip, float farClip)
    {
        return new CameraImpl(position, fov, aspectRatio, nearClip, farClip);
    }
}