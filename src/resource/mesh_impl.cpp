#include "resource/mesh_impl.h"
#include "resource/material_impl.h"
#include "loopxia/log.h"
#include "mesh_loader_impl.h"
#include <glm/gtx/quaternion.hpp>

namespace loopxia
{
    const std::string kMeshType = "Mesh";

    MeshImpl::MeshImpl(const std::string& filePath, const std::string& name) : 
        ResourceImpl<Mesh>(name, kMeshType, filePath)
    {
    }

    MeshImpl::~MeshImpl()
    {
    }

    bool MeshImpl::Load()
    {
        if (m_bLoaded) {
            return true;
        }

        MeshLoader loader;
        m_bLoaded = loader.LoadResource(shared_from_this());
        return m_bLoaded;
    }

    void MeshImpl::SetVectices(std::vector<Vector3>& vertices)
    {
        m_vertices = vertices;
    }

    void MeshImpl::SetNormals(std::vector<Vector3>& normals)
    {
        m_normals = normals;
    }

    void MeshImpl::SetUV(std::vector<Vector2>& uvs)
    {
        m_uvs = uvs;
    }

    void MeshImpl::SetIndices(std::vector<int>& indices)
    {
        m_indices = indices;
    }

    void MeshImpl::SetBoneWeights(std::vector<VertexBoneData>& boneWeights)
    {
        m_boneWeightByVertex = boneWeights;
    }

    const std::vector<Vector3>& MeshImpl::Vertices() const
    {
        return m_vertices;
    }

    const std::vector<Vector3>& MeshImpl::Normals() const
    {
        return m_normals;
    }

    const std::vector<Vector2>& MeshImpl::UV() const
    {
        return m_uvs;
    }

    const std::vector<VertexBoneData>& MeshImpl::BoneWeights() const
    {
        return m_boneWeightByVertex;
    }

    const std::vector<int>& MeshImpl::Indices() const
    {
        return m_indices;
    }

    std::shared_ptr<Material> MeshImpl::GetMaterial() const
    {
        return m_pMaterial;
    }

    void MeshImpl::SetMaterial(std::shared_ptr<Material> material)
    {
        m_pMaterial = material;
    }

    void MeshImpl::SetAnimation(std::vector<std::shared_ptr<Animation>> animations)
    {
        m_animations = animations;
    }

    std::shared_ptr<Animation> MeshImpl::GetAnimation(int animationIndex)
    {
        return m_animations[animationIndex];
    }

    int MeshImpl::_GetBoneId(const std::string& boneName)
    {
        auto it = m_boneNameToIndex.find(boneName);
        if (it == m_boneNameToIndex.end()) {
            return -1;
        }
        return it->second;
    }

    void MeshImpl::_ComputeBoneTransformationByHeirarchy(std::vector<Matrix4x4>& boneTransformations
        , std::unordered_map<std::string, Matrix4x4>& boneAnimTransformation
        , Bone* bone
        , const Matrix4x4& parentTransform)
    {
        auto boneId = _GetBoneId(bone->Name());
        if (boneId >= 0) {
            assert(boneAnimTransformation.count(bone->Name()));
            Matrix4x4 globalTransformation = parentTransform * boneAnimTransformation[bone->Name()];

            boneTransformations[boneId] = m_globalInverseTransform * globalTransformation * m_bones[boneId].OffsetMatrix();
            
            for (auto& child : bone->Children()) {
                _ComputeBoneTransformationByHeirarchy(boneTransformations, boneAnimTransformation, child, globalTransformation);
            }
        }
    }

    std::vector<Matrix4x4> MeshImpl::GetBoneTransformations(int animationIndex, double timeSec)
    {
        if (animationIndex >= m_animations.size() || animationIndex < 0) {
            return std::vector<Matrix4x4>(m_bones.size(), Matrix4x4(1.0f));
        }

        auto& anim = m_animations[animationIndex];

        auto animTransformations = anim->GetTransformations(timeSec);
        
        // map bone name to bone index
        std::vector<Matrix4x4> boneTransformations(m_bones.size(), Matrix4x4(1.0f));

        _ComputeBoneTransformationByHeirarchy(boneTransformations, animTransformations, m_rootBone, Matrix4x4(1.0f));
        return boneTransformations;
    }

    std::string AnimationImpl::Name()
    {
        return m_name;
    }

    template <typename T>
    int FindKeyIndex(const std::vector<AnimationKey<T>>& keys, double tickTime) {
        auto it = std::lower_bound(
            keys.begin(), keys.end(), tickTime,
            [](const AnimationKey<T>& k, double t) { return k.mTime < t; }
        );

        if (it == keys.begin())
            return 0;

        if (it == keys.end())
            return static_cast<int>(keys.size() - 1);

        return static_cast<int>(std::distance(keys.begin(), it - 1));
    }

    int NodeAnimationKeys::FindPositionIndex(double tickTime) {
        return FindKeyIndex(m_positionKeys, tickTime);
    }

    int NodeAnimationKeys::FindRotationIndex(double tickTime) {
        return FindKeyIndex(m_rotationKeys, tickTime);
    }

    int NodeAnimationKeys::FindScalingIndex(double tickTime)
    {
        return FindKeyIndex(m_scalingKeys, tickTime);
    }

    Matrix4x4 NodeAnimationKeys::GetInterpolatedTransformation(double tickTime)
    {
        auto interpolate = [&](const auto& keys, auto findIndexFunc, auto defaultVal) {
            using T = typename std::decay_t<decltype(keys[0].mValue)>;
            if (keys.size() == 1)
                return keys[0].mValue;
            else if (keys.size() > 1) {
                int index = (this->*findIndexFunc)(tickTime);
                int nextIndex = index + 1;

                double t1 = keys[index].mTime;
                double t2 = keys[nextIndex].mTime;
                double factor = (tickTime - t1) / (t2 - t1);

                const auto& start = keys[index].mValue;
                const auto& end = keys[nextIndex].mValue;

                if constexpr (std::is_same_v<T, Quaternion>)
                    return glm::normalize(glm::slerp(start, end, static_cast<float>(factor)));
                else
                    return start + static_cast<float>(factor) * (end - start);
            }
            return defaultVal;
            };

        Vector3 position = interpolate(m_positionKeys, &NodeAnimationKeys::FindPositionIndex, Vector3(0, 0, 0));
        Vector3 scale = interpolate(m_scalingKeys, &NodeAnimationKeys::FindScalingIndex, Vector3(1, 1, 1));
        Quaternion rot = interpolate(m_rotationKeys, &NodeAnimationKeys::FindRotationIndex, Quaternion(1.0, 0, 0, 0));
        
        Matrix4x4 transform = glm::translate(Matrix4x4(1.0f), position) *
            glm::toMat4(rot) *
            glm::scale(Matrix4x4(1.0f), scale);

        return transform;
    }

    std::unordered_map<std::string, Matrix4x4> AnimationImpl::GetTransformations(double time)
    {
        float timeInTicks = time * m_ticksPerSecond;
        float animationTimeTicks = fmod(timeInTicks, m_durationTicks);
        
        std::unordered_map<std::string, Matrix4x4> ret;
        
        for (auto [nodeName, keys] : m_nodeAnimationKeys) {
            ret[nodeName] = keys.GetInterpolatedTransformation(animationTimeTicks);
        }

        return ret;
    }

    double AnimationImpl::TotalAnimationTime()
    {
        return m_animationTime;
    }
}