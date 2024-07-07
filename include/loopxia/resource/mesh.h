#pragma once

#include <string>
#include <vector>
#include "loopxia/math.h"

#include "loopxia/object/object.h"

namespace loopxia
{
    namespace impl
    {
        class MeshImpl;
    }

    class Mesh : public Object
    {
    public:
        bool LoadFromFile(const std::string& filePath);
        
        const std::vector<Vector3>& Vertices() const;
        const std::vector<Vector3>& Normals() const;
        const std::vector<Vector2>& UV() const;
        const std::vector<int>& Indices() const;
        const std::string TextureFilePath() const;

    private:
        impl::MeshImpl* m_impl;
        std::vector<Vector3> m_vertices;
        std::vector<Vector3> m_normals;
        std::vector<Vector2> m_uvs;
        std::vector<int> m_indices;
        std::string m_textureFilePath;
    };
}