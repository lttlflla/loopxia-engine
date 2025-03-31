#pragma once

#include "loopxia/resource/mesh.h"
#include "resource/material_impl.h"
#include "resource/bone_impl.h"

namespace loopxia
{
    struct BoneWeight
    {
        int boneId;
        float boneWeight; // strength of the influence in the range 0 - 1 
    };

    struct Animation
    {

    };

    // store all information about mesh
    // - vertices, normals, indices, uv. Bones and animation.
    // to place a manifestation of a Mesh into scene, use CreateAvatar(Mesh* mesh);
    class MeshImpl : public virtual Mesh
    {
    public:
        ~MeshImpl();

        bool LoadFromFile(const std::string& filePath);

        void SetVectices(std::vector<Vector3>& vertices) override;
        void SetNormals(std::vector<Vector3>& normals) override;
        void SetUV(std::vector<Vector2>& uv) override;
        void SetIndices(std::vector<int>& indices) override;

        const std::vector<Vector3>& Vertices() const override;
        const std::vector<Vector3>& Normals() const override;
        const std::vector<Vector2>& UV() const override;
        const std::vector<int>& Indices() const override;
        Material* GetMaterial() const override;

    private:
        std::vector<Vector3> m_vertices;
        std::vector<int> m_indices;
        std::vector<Vector3> m_normals;
        std::vector<Vector2> m_uvs;
        
        // vector of bones, also owner of the bones
        std::vector<BoneImpl*> m_bones;
        // array of bone weight. index of array is same as vertex index
        std::vector<std::vector<BoneWeight>> m_boneWeights; 

        //animation


        RefCountedObject<MaterialImpl> m_pMaterial;

        std::vector<MeshImpl> m_children;
    };
}