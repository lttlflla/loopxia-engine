#include "loopxia/math.h"
#include <algorithm>

namespace loopxia
{
    class BoundingVolume {
    public:
        static constexpr int Stride = 10 * sizeof(double) * 3 + 2 * sizeof(double) * 4 + 1 * sizeof(double);
        static BoundingVolume Empty() {
            return BoundingVolume(Vector3(0.0f), Vector3(0.0f), Quaternion(1.0f, 0.0f, 0.0f, 0.0f));
        }

        BoundingVolume(Vector3 minAabb, Vector3 maxAabb, Quaternion rotation);

        bool Intersects(const BoundingVolume& v) const;
        static BoundingVolume UnionAtoB(const BoundingVolume& a, const BoundingVolume& b);
        static BoundingVolume Union(const BoundingVolume& a, const BoundingVolume& b);

    private:
        Vector3 _center;

        Vector3 _axisX;
        Vector3 _axisY;
        Vector3 _axisZ;

        Vector3 _axisHalfExtendX;
        Vector3 _axisHalfExtendY;
        Vector3 _axisHalfExtendZ;

        Vector3 _aabbMin;
        Vector3 _aabbMax;

        Quaternion _rotation;
        Quaternion _rotationInverse;

        Vector3 _extends;

        double _maxDiagonal;
    };
}