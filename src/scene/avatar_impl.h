#pragma once

#include "loopxia/scene/avatar.h"
#include "resource/mesh_impl.h"
#include "scene_node_impl.h"

namespace loopxia
{
    class AvatarImpl final : public virtual SceneNodeImpl<Avatar>
    {
    public:
        AvatarImpl(SceneNode* parent = nullptr);

        void SetMesh(std::shared_ptr<Mesh> mesh) override;
        std::shared_ptr<Mesh> GetMesh() override;

        void SetAnimation() override;

    private:
        // reference to the mesh resource
        // multiple avatar can reference to the same mesh
        std::shared_ptr<Mesh> m_mesh;

        // map of bone name to scene node
        //std::unordered_map<std::string, > m_
        // reference to 
    };
}