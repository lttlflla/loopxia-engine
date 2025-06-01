#include "object/camera_impl.h"

namespace loopxia
{
    CameraImpl::CameraImpl(const glm::vec3& position, float fov /* degrees */, float aspectRatio, float nearClip, float farClip)
        : m_position(position), m_lookAtDir(glm::vec3(0.0f, 0.0f, -1.0f)), m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
        m_fov(fov), m_aspectRatio(aspectRatio), m_nearClip(nearClip), m_farClip(farClip) {

        // fov is from top to bottom of the frustum 
        // a fov that is too large result in wide lens effect anamorphic HFOV

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
        // note the view matrix can become NaN if m_up and look direction is the same
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
    
    void CameraImpl::LookAtAndFitScreen(BoundingVolume& v)
    {
        // 1. Compute center and bounding sphere radius
        auto center = (v.MaxAABB() - v.MinAABB()) * 0.5f + v.MinAABB();
        float radius = (v.MaxAABB() - center).length();

        // 2. Compute distance from center using FOV
        float fov_horizontal = 2 * atan(tan(glm::radians(m_fov) / 2) * m_aspectRatio);
        float distance = (radius * 2) / std::tan(fov_horizontal / 2);

        // 3. Camera positioned along -Z by default (viewing towards +Z)
        m_up = glm::vec3(0, 1, 0);
        m_position = center + glm::vec3(0, 0, distance);
        m_lookAtDir = math::Normalize(center - m_position);

        UpdateViewMatrix();
    }

    Camera* CreateCamera(const Vector3& position, float fov /* degrees */, float aspectRatio, float nearClip, float farClip)
    {
        return new CameraImpl(position, fov, aspectRatio, nearClip, farClip);
    }
}