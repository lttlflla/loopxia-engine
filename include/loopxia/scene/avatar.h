#pragma once

#include "loopxia/scene/scene_node.h"
#include "loopxia/object/ref_counted_object.h"
#include "loopxia/resource/mesh.h"

namespace loopxia
{
    class Avatar : public virtual SceneNode
    {
    public:
        virtual ~Avatar() = default;

        virtual void SetMesh(RefCountedObject<Mesh> mesh) = 0;
        virtual RefCountedObject<Mesh> GetMesh() = 0;
        virtual void SetAnimation() = 0;
    };
}