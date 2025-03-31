#include "scene/avatar_impl.h"

namespace loopxia
{
    AvatarImpl::AvatarImpl()
    {
    }

    void AvatarImpl::SetMesh(RefCountedObject<Mesh> mesh)
    {
        m_mesh = mesh;
    }

    RefCountedObject<Mesh> AvatarImpl::GetMesh()
    {
        return m_mesh;
    }
}