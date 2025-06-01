#include "mesh_loader_impl.h"
#include "mesh_impl.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>

namespace loopxia
{
    inline static glm::mat4 Assimp2Glm(const aiMatrix4x4& from)
    {
        return glm::mat4(
            from.a1, from.b1, from.c1, from.d1,
            from.a2, from.b2, from.c2, from.d2,
            from.a3, from.b3, from.c3, from.d3,
            from.a4, from.b4, from.c4, from.d4
        );
    }

    void LoadMesh(std::shared_ptr<MeshImpl> pMesh)
    {
    }


    void LoadNodeKeys(NodeAnimationKeys& nodeKeys, aiNodeAnim* nodeAnim)
    {
        for (int posIndex = 0; posIndex < nodeAnim->mNumPositionKeys; posIndex++ ) {
            AnimationKey<Vector3> posKey;
            
            auto& aiPos = nodeAnim->mPositionKeys[posIndex].mValue;
            posKey.mTime = nodeAnim->mPositionKeys[posIndex].mTime;
            posKey.mValue = Vector3(aiPos.x, aiPos.y, aiPos.z);

            nodeKeys.m_positionKeys.push_back(posKey);
        }


        for (int quaIndex = 0; quaIndex < nodeAnim->mNumRotationKeys; quaIndex++) {
            AnimationKey<Quaternion> rotKey;

            auto& aiRot = nodeAnim->mRotationKeys[quaIndex].mValue;
            rotKey.mTime = nodeAnim->mRotationKeys[quaIndex].mTime;
            rotKey.mValue = Quaternion(aiRot.w, aiRot.x, aiRot.y, aiRot.z);

            nodeKeys.m_rotationKeys.push_back(rotKey);
        }


        for (int scaleIndex = 0; scaleIndex < nodeAnim->mNumScalingKeys; scaleIndex++) {
            AnimationKey<Vector3> scaleKey;

            auto& aiScale = nodeAnim->mScalingKeys[scaleIndex].mValue;
            scaleKey.mTime = nodeAnim->mScalingKeys[scaleIndex].mTime;
            scaleKey.mValue = Vector3(aiScale.x, aiScale.y, aiScale.z);

            nodeKeys.m_scalingKeys.push_back(scaleKey);
        }
    }

    std::shared_ptr<Animation> MeshLoader::LoadAnimation(const aiAnimation* aiAnim)
    {
        std::shared_ptr<AnimationImpl> anim(new AnimationImpl);

        anim->m_durationTicks = aiAnim->mDuration;
        anim->m_ticksPerSecond = aiAnim->mTicksPerSecond == 0 ? anim->m_durationTicks : aiAnim->mTicksPerSecond;

        anim->m_name = aiAnim->mName.C_Str();
        anim->m_animationTime = anim->m_durationTicks / anim->m_ticksPerSecond;

        for (int iChannel = 0; iChannel < aiAnim->mNumChannels; iChannel++) {
            auto& aiChannel = aiAnim->mChannels[iChannel];
            auto& nodeKeys = anim->m_nodeAnimationKeys[aiChannel->mNodeName.C_Str()];
            LoadNodeKeys(nodeKeys, aiChannel);
        }

        return anim;
    }

    void MeshLoader::LoadAnimations(const aiScene* aiScene, std::vector<std::shared_ptr<Animation>>& animations)
    {
        for (auto i = 0; i < aiScene->mNumAnimations; i++) {
            auto& aiAnim = aiScene->mAnimations[i];
            auto anim = LoadAnimation(aiAnim);
            animations.push_back(anim);
        }
    }

    void MeshLoader::_BuildBoneHierarchy(const aiNode* node,
        std::vector<BoneImpl>& bones,
        const std::unordered_map<std::string, int>& boneMap,
        BoneImpl* parent)
    {
        // Check if this node corresponds to a bone
        auto it = boneMap.find(node->mName.C_Str());
        BoneImpl* current = parent;

        if (it != boneMap.end()) {
            auto boneIndex = it->second;
            current = &bones[boneIndex];

            // Set parent-child relationship
            current->m_parent = parent;
            if (parent) {
                parent->m_children.push_back(current);
            }
        }

        // Recurse through children
        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            _BuildBoneHierarchy(node->mChildren[i], bones, boneMap, current);
        }
    }

    bool MeshLoader::LoadResource(std::shared_ptr<Resource> resource)
    {
        auto pMeshResource = std::dynamic_pointer_cast<MeshImpl>(resource);
        if (!pMeshResource) {
            return false;
        }

        auto& vertices = pMeshResource->m_vertices;
        auto& normals = pMeshResource->m_normals;
        auto& indices = pMeshResource->m_indices;
        auto& uvs = pMeshResource->m_uvs;

        auto filePathStr = resource->FilePath();
        std::filesystem::path filePath(filePathStr);

        // Create an instance of the importer
        Assimp::Importer importer;

        // Specify the post-processing steps to apply during import
        unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;

        // Load the mesh using Assimp
        const aiScene* scene = importer.ReadFile(filePath.string(), flags);

        // Check if the scene was loaded successfully
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            LogError(std::string("Error loading mesh: ") + importer.GetErrorString() + " " + filePathStr);
            return false;
        }

        if (!scene->mNumMeshes) {
            LogError(std::string("Error loading mesh. No mesh in file. ") + filePathStr);
            return false;
        }
        
        // only load the first mesh
        const aiMesh* mesh = scene->mMeshes[0];

        // Access vertex data
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            auto& aV = mesh->mVertices[i];
            Vector3 v = { aV.x, aV.y, aV.z };
            vertices.push_back(v);

            auto& aN = mesh->mNormals[i];
            Vector3 n = { aN.x, aN.y, aN.z };
            normals.push_back(n);

            auto& aUV = mesh->mTextureCoords[0][i]; // Assuming there's only one texture coordinate set
            Vector2 uv = { aUV.x, aUV.y };
            uvs.push_back(uv);
        }


        // Iterate through each face (triangle) in the mesh
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            const aiFace& face = mesh->mFaces[j];

            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                indices.push_back(face.mIndices[k]);
            }
        }

        // Access material data
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiString texturePath;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
                // Load the texture using the texture path
                LogInfo(std::string("Diffuse texture path: ") + texturePath.C_Str());

                //auto pMaterial = std::make_shared<MaterialImpl>(filePath.parent_path().generic_string() + "/" + texturePath.C_Str(), material->GetName().C_Str());
                auto pMaterial = pMeshResource->GetMaterial();
                pMaterial->SetTextureFilePath(0, filePath.parent_path().generic_string() + "/" + texturePath.C_Str());
            }
        }

        pMeshResource->m_globalInverseTransform = math::Inverse(Assimp2Glm(scene->mRootNode->mTransformation));

        auto& boneData = pMeshResource->m_boneWeightByVertex;
        auto& boneNameToIndexMap = pMeshResource->m_boneNameToIndex;
        auto& bones = pMeshResource->m_bones;

        Vector3 maxTranslation = glm::vec3(std::numeric_limits<float>::lowest());
        Vector3 minTranslation = glm::vec3(std::numeric_limits<float>::max());

        // load bone data
        if (mesh->HasBones()) {
            bones.resize(mesh->mNumBones);
            boneData.resize(vertices.size());
            for (unsigned int i = 0; i < mesh->mNumBones; i++) {
                auto assimpBone = mesh->mBones[i];

                auto& targetBone = bones[i];

                Matrix4x4 m44 = Assimp2Glm(assimpBone->mOffsetMatrix);

                targetBone.SetOffsetMatrix(m44);
                targetBone.SetName(assimpBone->mName.C_Str());

                // store bone name in map for fast reference to index
#if _DEBUG
                assert(!boneNameToIndexMap.count(assimpBone->mName.C_Str()));
#endif
                boneNameToIndexMap[assimpBone->mName.C_Str()] = i;

                for (unsigned int w = 0; w < assimpBone->mNumWeights; w++) {
                    auto& assimpWeight = assimpBone->mWeights[w];
                    auto vertexId = assimpWeight.mVertexId;

                    VertexBoneData& boneVertexData = boneData[vertexId];
                    boneVertexData.AddBoneData(i, assimpWeight.mWeight);
                }
            }

            _BuildBoneHierarchy(scene->mRootNode, bones, boneNameToIndexMap, nullptr);
            for (auto& b : bones) {
                if (!b.m_parent) {
                    pMeshResource->m_rootBone = &b;
                    break;
                }
            }
        }

        auto& meshAnimations = pMeshResource->m_animations;
        if (scene->HasAnimations()) {
            LoadAnimations(scene, meshAnimations);
        }

        return true;
    }
}
