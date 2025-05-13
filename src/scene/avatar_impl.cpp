#include "scene/avatar_impl.h"

namespace loopxia
{
    AvatarImpl::AvatarImpl(SceneNode* parent) : SceneNodeImpl<Avatar>(parent)
    {
    }

    void AvatarImpl::SetMesh(std::shared_ptr<Mesh> mesh)
    {
        m_mesh = mesh;
    }

    std::shared_ptr<Mesh> AvatarImpl::GetMesh()
    {
        return m_mesh;
    }

    void AvatarImpl::SetAnimation()
    {

    }

    Avatar* CreateAvatar()
    {
        return new AvatarImpl;
    }

    void DestroyAvatar(Avatar* avatar)
    {
        delete avatar;
    }
}