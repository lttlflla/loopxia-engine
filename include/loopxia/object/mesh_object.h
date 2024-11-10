#pragma once

#include <string>
#include <vector>
#include "loopxia/math.h"
#include "loopxia/object/movable_object.h"
#include "loopxia/resource/material.h"

namespace loopxia
{
    class Mesh : public MovableObject, public InstanceTracker<Mesh>
    {
    public:
        virtual const std::vector<Vector3>& Vertices() const = 0;
        virtual const std::vector<Vector3>& Normals() const = 0;
        virtual const std::vector<Vector2>& UV() const = 0;
        virtual const std::vector<int>& Indices() const = 0;
        virtual Material* GetMaterial() const = 0;
    };

    Mesh* LoadFromFile(const std::string& filePath);
}