#pragma once

#include "loopxia/resource/mesh.h"
#include "resource/material_impl.h"
#include "resource/bone_impl.h"
#include "resource/resource_impl.h"

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

        const std::vector<Vector3>& Vertices() const override;
        const std::vector<Vector3>& Normals() const override;
        const std::vector<Vector2>& UV() const override;
        const std::vector<int>& Indices() const override;
        std::shared_ptr<Material> GetMaterial() const override;
        void SetMaterial(std::shared_ptr<Material> material) override;

    private:
        std::vector<int> m_indices;
        std::vector<Vector3> m_vertices;
        std::vector<Vector3> m_normals;
        std::vector<Vector2> m_uvs;
        
        // vector of bones, also owner of the bones
        std::vector<BoneImpl> m_bones;
        // array of bone weight. index of array is same as vertex index
        std::vector<std::vector<BoneWeight>> m_boneWeights; 

        //animation


        std::shared_ptr<Material> m_pMaterial;

        std::vector<MeshImpl> m_children;
    };

}