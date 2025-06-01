#pragma once

#include "loopxia/resource/resource_loader.h"
#include "resource_impl.h"
#include "loopxia/resource/mesh.h"
#include <vector>
#include <assimp/scene.h>
#include "resource/bone_impl.h"

namespace loopxia
{
    class MeshLoader : public ResourceLoader {
    public:
        bool LoadResource(std::shared_ptr<Resource> resource) override;

    protected:

        void LoadAnimations(const aiScene* aiScene, std::vector<std::shared_ptr<Animation>>& animations);
        std::shared_ptr<Animation> LoadAnimation(const aiAnimation* aiAnim); 
        
        void _BuildBoneHierarchy(const aiNode* node,
            std::vector<BoneImpl>& bones,
            const std::unordered_map<std::string, int>& boneMap,
            BoneImpl* parent = nullptr);
    };

}