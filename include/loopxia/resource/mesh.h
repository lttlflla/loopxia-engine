#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "loopxia/math.h"
#include "loopxia/resource/resource.h"
#include "loopxia/resource/material.h"

namespace loopxia
{
    const int kMaxNumBonesPerVertex = 4;
    struct VertexBoneData
    {
        uint32_t boneIDs[kMaxNumBonesPerVertex] = { 0 };
        float weights[kMaxNumBonesPerVertex] = { 0.0f };
        int index = 0;  // slot for the next update

        VertexBoneData()
        {
        }

        void AddBoneData(uint32_t boneID, float weight)
        {
            for (int i = 0; i < index; i++) {
                if (boneIDs[i] == boneID) {
                    return;
                }
            }

            if (weight == 0.0f) {
                return;
            }

            if (index == kMaxNumBonesPerVertex) {
                return;
                assert(0);
            }

            boneIDs[index] = boneID;
            weights[index] = weight;

            index++;

            float totalWeights = 0;
            std::unordered_set<int> seenIndices;
            for (int i = 0; i < index; i++) {
                totalWeights += weights[i];
                if (seenIndices.count(boneIDs[i])) {
                    assert(false);
                }
                seenIndices.insert(boneIDs[i]);
               // assert(totalWeights <= 1.0f);
            }
        }
    };

    template<class T>
    struct AnimationKey
    {
    public:
        double mTime;
        T mValue;
    };

    class Animation
    {
    public:
        virtual ~Animation() = default;

        virtual std::string Name() = 0;
        virtual std::unordered_map<std::string, Matrix4x4> GetTransformations(double time /* time in seconds */) = 0;
        
        // return total animation time in seconds
        virtual double TotalAnimationTime() = 0;
    };

    // mesh can contain a mesh or a hierarchy of meshes
    // 
    class Mesh : public virtual Resource, public InstanceTracker<Mesh>
    {
    public:
        virtual ~Mesh() = default;

        virtual void SetVectices(std::vector<Vector3>& vertices) = 0;
        virtual void SetNormals(std::vector<Vector3>& normals) = 0;
        virtual void SetUV(std::vector<Vector2>& uv) = 0;
        virtual void SetBoneWeights(std::vector<VertexBoneData>&) = 0;
        virtual void SetIndices(std::vector<int>& indices) = 0;

        virtual const std::vector<Vector3>& Vertices() const = 0;
        virtual const std::vector<Vector3>& Normals() const = 0;
        virtual const std::vector<Vector2>& UV() const = 0;
        virtual const std::vector<VertexBoneData>& BoneWeights() const = 0;
        virtual const std::vector<int>& Indices() const = 0;
        virtual std::shared_ptr<Material> GetMaterial() const = 0;
        virtual void SetMaterial(std::shared_ptr<Material> material) = 0;

        virtual void SetAnimation(std::vector<std::shared_ptr<Animation>> animations) = 0;
        virtual std::shared_ptr<Animation> GetAnimation(int animationIndex) = 0;

        virtual std::vector<Matrix4x4> GetBoneTransformations(int animationIndex, double timeSec) = 0;
    };
}