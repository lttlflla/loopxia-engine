#pragma once

#include <string>
#include <vector>
#include "loopxia/math.h"
#include "loopxia/resource/resource.h"
#include "loopxia/resource/material.h"

namespace loopxia
{
    // mesh can contain a single mesh or a hierarchy of meshes
    // 
    class Mesh : public Resource, public InstanceTracker<Mesh>
    {
    public:
        virtual ~Mesh() = default;

        virtual void SetVectices(std::vector<Vector3>& vertices) = 0;
        virtual void SetNormals(std::vector<Vector3>& normals) = 0;
        virtual void SetUV(std::vector<Vector2>& uv) = 0;
        virtual void SetIndices(std::vector<int>& indices) = 0;

        virtual const std::vector<Vector3>& Vertices() const = 0;
        virtual const std::vector<Vector3>& Normals() const = 0;
        virtual const std::vector<Vector2>& UV() const = 0;
        virtual const std::vector<int>& Indices() const = 0;
        virtual Material* GetMaterial() const = 0;
    };

    Mesh* MeshLoadFromFile(const std::string& filePath);
}