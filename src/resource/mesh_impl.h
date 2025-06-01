#pragma once

#include "loopxia/resource/mesh.h"
#include "resource/material_impl.h"
#include "resource/bone_impl.h"
#include "resource/resource_impl.h"

namespace loopxia
{
    struct NodeAnimationKeys
    {
        std::vector<AnimationKey<Vector3>> m_positionKeys;
        std::vector<AnimationKey<Quaternion>> m_rotationKeys;
        std::vector<AnimationKey<Vector3>> m_scalingKeys;

        Matrix4x4 GetInterpolatedTransformation(double tickTime);
        
        int FindPositionIndex(double tickTime);
        int FindRotationIndex(double tickTime);
        int FindScalingIndex(double tickTime);
    };

    class AnimationImpl : public Animation
    {
        friend class MeshLoader;
        friend class MeshSaver;

    public:
        std::string Name() override;
        std::unordered_map<std::string, Matrix4x4> GetTransformations(double time) override;

        double TotalAnimationTime() override;

    protected:

        std::unordered_map<std::string, NodeAnimationKeys> m_nodeAnimationKeys;

        std::string m_name;

        double m_animationTime = 0;

        /** duration of the animation in ticks.  */
        double m_durationTicks = 0;

        /** Ticks per second. 0 if not specified in the imported file */
        double m_ticksPerSecond = 0;
    };

    extern template class ResourceImpl<Mesh>;

    // store all information about mesh
    // - vertices, normals, indices, uv. Bones and animation.
    // to place a manifestation of a Mesh into scene, use CreateAvatar(Mesh* mesh);
    class MeshImpl : public ResourceImpl<Mesh>
    {
        friend class MeshLoader;
        friend class MeshSaver;

    public:
        MeshImpl(const std::string& filePath, const std::string& name);
        ~MeshImpl();
        
        bool Load() override;

        void SetVectices(std::vector<Vector3>& vertices) override;
        void SetNormals(std::vector<Vector3>& normals) override;
        void SetUV(std::vector<Vector2>& uv) override;
        void SetIndices(std::vector<int>& indices) override;
        void SetBoneWeights(std::vector<VertexBoneData>&) override;

        const std::vector<Vector3>& Vertices() const override;
        const std::vector<Vector3>& Normals() const override;
        const std::vector<Vector2>& UV() const override;
        const std::vector<VertexBoneData>& BoneWeights() const override;
        const std::vector<int>& Indices() const override;
        std::shared_ptr<Material> GetMaterial() const override;
        void SetMaterial(std::shared_ptr<Material> material) override;

        void SetAnimation(std::vector<std::shared_ptr<Animation>> animations) override;
        std::shared_ptr<Animation> GetAnimation(int animationIndex) override;

        std::vector<Matrix4x4> GetBoneTransformations(int animationIndex, double timeSec) override;

    protected:
        inline int _GetBoneId(const std::string& boneName);
        void _ComputeBoneTransformationByHeirarchy(std::vector<Matrix4x4>& boneTransformations
            , std::unordered_map<std::string, Matrix4x4>& boneAnimTransformation
            , Bone* bone
            , const Matrix4x4& parentTransform);

        std::vector<int> m_indices;

        // start of vertex data ------------
        std::vector<Vector3> m_vertices; // vertices
        std::vector<Vector3> m_normals; // normal at each vertex
        std::vector<Vector2> m_uvs; // uv at each vertex
        std::vector<VertexBoneData> m_boneWeightByVertex; // bone data at each vertex
        // end of vertex data -----------
        
        // bones 
        // vector of bones, also owner of the bones
        std::vector<BoneImpl> m_bones;
        std::unordered_map<std::string, int> m_boneNameToIndex;
        BoneImpl* m_rootBone = nullptr;
        Matrix4x4 m_globalInverseTransform;

        //animation
        std::vector <std::shared_ptr<Animation>> m_animations;

        std::shared_ptr<Material> m_pMaterial;

        std::vector<MeshImpl> m_children;
    };

}