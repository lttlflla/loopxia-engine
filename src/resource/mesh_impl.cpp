#include "resource/mesh_impl.h"
#include "resource/material_impl.h"
#include "loopxia/log.h"
#include "mesh_loader_impl.h"

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
        return loader.LoadResource(shared_from_this());
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
}