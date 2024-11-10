#pragma once

#include "loopxia/object/mesh_object.h"

namespace loopxia
{
    class MeshImpl : public Mesh
    {
    public:
        bool LoadFromFile(const std::string& filePath);

        const std::vector<Vector3>& Vertices() const override;
        const std::vector<Vector3>& Normals() const override;
        const std::vector<Vector2>& UV() const override;
        const std::vector<int>& Indices() const override;
        Material* GetMaterial() const override;

    private:
        std::vector<Vector3> m_vertices;
        std::vector<Vector3> m_normals;
        std::vector<Vector2> m_uvs;
        std::vector<int> m_indices;
        Material* m_material;
    };
}