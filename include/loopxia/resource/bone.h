#pragma once

#include <vector>
#include <string>

namespace loopxia
{
    class Bone
    {
    public:
        virtual ~Bone() = default;

        virtual void SetName(const std::string& name) = 0;
        virtual void SetOffsetMatrix(Matrix4x4 matrix) = 0;
        virtual std::string Name() = 0;
        virtual Matrix4x4 OffsetMatrix() = 0;
        virtual std::vector<Bone*> Children() = 0;
    };
}