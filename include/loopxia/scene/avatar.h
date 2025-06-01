#pragma once

#include "loopxia/scene/scene_node.h"
#include "loopxia/resource/mesh.h"

namespace loopxia
{
    class Avatar : public virtual SceneNode
    {
    public:
        virtual ~Avatar() = default;

        virtual void SetMesh(std::shared_ptr<Mesh> mesh) = 0;
        virtual std::shared_ptr<Mesh> GetMesh() = 0;

        virtual void SetAnimation() = 0;
    };

    Avatar* CreateAvatar();
    void DestroyAvatar(Avatar*);
}