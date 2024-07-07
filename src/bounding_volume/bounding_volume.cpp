#include "loopxia/bounding_volume/bounding_volume.h"
#include <algorithm>

namespace loopxia
{
    using namespace math;

    BoundingVolume::BoundingVolume(Vector3 minAabb, Vector3 maxAabb, Quaternion rotation) {
        _aabbMin = minAabb;
        _aabbMax = maxAabb;

        _extends = _aabbMax - _aabbMin;

        _center = 0.5f * (_aabbMin + _aabbMax);

        _rotation = rotation;
        _rotationInverse = Inverse(rotation);

        _axisX = Rotate(Vector3(1.0f, 0.0f, 0.0f), rotation);
        _axisY = Rotate(Vector3(0.0f, 1.0f, 0.0f), rotation);
        _axisZ = Rotate(Vector3(0.0f, 0.0f, 1.0f), rotation);

        Vector3 axisExtendX = _axisX * _extends.x;
        Vector3 axisExtendY = _axisY * _extends.y;
        Vector3 axisExtendZ = _axisZ * _extends.z;

        _axisHalfExtendX = 0.5f * axisExtendX;
        _axisHalfExtendY = 0.5f * axisExtendY;
        _axisHalfExtendZ = 0.5f * axisExtendZ;

        _maxDiagonal = Length(_aabbMax - _center);
    }

    bool BoundingVolume::Intersects(const BoundingVolume& v) const {
        Vector3 distBetween = v._center - _center;
        if (Length(distBetween) > (v._maxDiagonal + _maxDiagonal)) {
            return false;
        }

        Vector3 axis[15];

        axis[0] = _axisX;
        axis[1] = _axisY;
        axis[2] = _axisZ;

        axis[3] = v._axisX;
        axis[4] = v._axisY;
        axis[5] = v._axisZ;

        axis[6] = glm::cross(_axisX, v._axisX);
        axis[7] = glm::cross(_axisX, v._axisY);
        axis[8] = glm::cross(_axisX, v._axisZ);

        axis[9] = glm::cross(_axisY, v._axisX);
        axis[10] = glm::cross(_axisY, v._axisY);
        axis[11] = glm::cross(_axisY, v._axisZ);

        axis[12] = glm::cross(_axisZ, v._axisX);
        axis[13] = glm::cross(_axisZ, v._axisY);
        axis[14] = glm::cross(_axisZ, v._axisZ);

        bool intersects = true;

        for (int index = 0; index < 15 && intersects; ++index) {
            float distProj = glm::abs(glm::dot(distBetween, axis[index]));

            float ourXProj = glm::abs(glm::dot(_axisHalfExtendX, axis[index]));
            float ourYProj = glm::abs(glm::dot(_axisHalfExtendY, axis[index]));
            float ourZProj = glm::abs(glm::dot(_axisHalfExtendZ, axis[index]));

            float otherXProj = glm::abs(glm::dot(v._axisHalfExtendX, axis[index]));
            float otherYProj = glm::abs(glm::dot(v._axisHalfExtendY, axis[index]));
            float otherZProj = glm::abs(glm::dot(v._axisHalfExtendZ, axis[index]));

            intersects = distProj <=

                ourXProj + ourYProj + ourZProj + otherXProj + otherYProj + otherZProj;
        }

        return intersects;
    }

    BoundingVolume BoundingVolume::UnionAtoB(const BoundingVolume& a, const BoundingVolume& b) {
        Vector3 basisX = Normalize(b._axisHalfExtendX);
        Vector3 basisY = Normalize(b._axisHalfExtendY);
        Vector3 basisZ = Normalize(b._axisHalfExtendZ);

        Vector3 allPoints[8] = {
            (a._axisHalfExtendX + a._axisHalfExtendY + a._axisHalfExtendZ),
            (a._axisHalfExtendX + a._axisHalfExtendY - a._axisHalfExtendZ),
            (a._axisHalfExtendX - a._axisHalfExtendY + a._axisHalfExtendZ),
            (a._axisHalfExtendX - a._axisHalfExtendY - a._axisHalfExtendZ),
            (-a._axisHalfExtendX + a._axisHalfExtendY + a._axisHalfExtendZ),
            (-a._axisHalfExtendX + a._axisHalfExtendY - a._axisHalfExtendZ),
            (-a._axisHalfExtendX - a._axisHalfExtendY + a._axisHalfExtendZ),
            (-a._axisHalfExtendX - a._axisHalfExtendY - a._axisHalfExtendZ)
        };

        float maxX = 0.0f;
        float maxY = 0.0f;
        float maxZ = 0.0f;

        for (int i = 0; i < 8; ++i) {
            float projX = glm::abs(glm::dot(allPoints[i], basisX));
            float projY = glm::abs(glm::dot(allPoints[i], basisY));
            float projZ = glm::abs(glm::dot(allPoints[i], basisZ));

            maxX = std::max(maxX, projX);
            maxY = std::max(maxY, projY);
            maxZ = std::max(maxZ, projZ);
        }

        Vector3 midPoint = 0.5f * (b._center - a._center) + a._center;
        float boxDistanceX = glm::abs(glm::dot((b._center - a._center), basisX));
        float maxXForBoxB = glm::length(b._axisHalfExtendX);
        maxXForBoxB = (maxX > boxDistanceX + maxXForBoxB) ? (maxX - boxDistanceX) : maxXForBoxB;
        float maxXForBoxA = (maxXForBoxB > boxDistanceX + maxX) ? (maxXForBoxB - boxDistanceX) : maxX;

        Vector3 minAX = a._center - maxXForBoxA * basisX;
        Vector3 centerX = a._center + ((boxDistanceX + maxXForBoxB - maxXForBoxA) * basisX) * 0.5f;
        Vector3 halfExtendX = glm::normalize(minAX - centerX) * glm::length(minAX - centerX);

        // Calculate center for basis Y
        float boxDistanceY = glm::abs(glm::dot((b._center - a._center), basisY));
        float maxYForBoxB = glm::length(b._axisHalfExtendY);
        maxYForBoxB = (maxY > boxDistanceY + maxYForBoxB) ? (maxY - boxDistanceY) : maxYForBoxB;
        float maxYForBoxA = (maxYForBoxB > boxDistanceY + maxY) ? (maxYForBoxB - boxDistanceY) : maxY;
        Vector3 minAY = a._center - maxYForBoxA * basisY;
        Vector3 centerY = a._center + ((boxDistanceY + maxYForBoxB - maxYForBoxA) * basisY) * 0.5f;
        Vector3 halfExtendY = glm::normalize(minAY - centerY) * glm::length(minAY - centerY);

        // Calculate center for basis Z
        float boxDistanceZ = glm::abs(glm::dot((b._center - a._center), basisZ));
        float maxZForBoxB = glm::length(b._axisHalfExtendZ);
        maxZForBoxB = (maxZ > boxDistanceZ + maxZForBoxB) ? (maxZ - boxDistanceZ) : maxZForBoxB;
        float maxZForBoxA = (maxZForBoxB > boxDistanceZ + maxZ) ? (maxZForBoxB - boxDistanceZ) : maxZ;
        Vector3 minAZ = a._center - maxZForBoxA * basisZ;
        Vector3 centerZ = a._center + ((boxDistanceZ + maxZForBoxB - maxZForBoxA) * basisZ) * 0.5f;
        Vector3 halfExtendZ = glm::normalize(minAZ - centerZ) * glm::length(minAZ - centerZ);

        Vector3 projCenterY = glm::dot(centerY - centerX, basisY) * basisY;
        Vector3 projCenterZ = glm::dot(centerZ - centerX, basisZ) * basisZ;

        Vector3 newCenter = centerX + projCenterY + projCenterZ;

        Vector3 maxDiag = glm::abs(b._rotationInverse * (halfExtendX + halfExtendY + halfExtendZ));
        Vector3 maxAABB = newCenter + maxDiag;
        Vector3 minAABB = newCenter - maxDiag;

        return BoundingVolume(minAABB, maxAABB, b._rotation);
    }

    BoundingVolume BoundingVolume::Union(const BoundingVolume& a, const BoundingVolume& b) {
        // Establish vector between the two bounding volume center as the new up axis
        Vector3 basisY = Normalize(b._center - a._center);
        Vector3 basisX(1, 0, 0);
        Vector3 basisZ(0, 0, 1);

        float centerDist = glm::length(b._center - a._center);
        if (centerDist < a._maxDiagonal || centerDist < b._maxDiagonal) {
            if (a._maxDiagonal > b._maxDiagonal) {
                return UnionAtoB(b, a);
            }
            else {
                return UnionAtoB(a, b);
            }
        }

        OrthogonalizeAxes(basisY, basisX, basisZ);

        // Compute the max length of each point
        Vector3 allPoints[16] = {
            (b._axisHalfExtendX + b._axisHalfExtendY + b._axisHalfExtendZ),
            (b._axisHalfExtendX + b._axisHalfExtendY - b._axisHalfExtendZ),
            (b._axisHalfExtendX - b._axisHalfExtendY + b._axisHalfExtendZ),
            (b._axisHalfExtendX - b._axisHalfExtendY - b._axisHalfExtendZ),
            (-b._axisHalfExtendX + b._axisHalfExtendY + b._axisHalfExtendZ),
            (-b._axisHalfExtendX + b._axisHalfExtendY - b._axisHalfExtendZ),
            (-b._axisHalfExtendX - b._axisHalfExtendY + b._axisHalfExtendZ),
            (-b._axisHalfExtendX - b._axisHalfExtendY - b._axisHalfExtendZ),
            (a._axisHalfExtendX + a._axisHalfExtendY + a._axisHalfExtendZ),
            (a._axisHalfExtendX + a._axisHalfExtendY - a._axisHalfExtendZ),
            (a._axisHalfExtendX - a._axisHalfExtendY + a._axisHalfExtendZ),
            (a._axisHalfExtendX - a._axisHalfExtendY - a._axisHalfExtendZ),
            (-a._axisHalfExtendX + a._axisHalfExtendY + a._axisHalfExtendZ),
            (-a._axisHalfExtendX + a._axisHalfExtendY - a._axisHalfExtendZ),
            (-a._axisHalfExtendX - a._axisHalfExtendY + a._axisHalfExtendZ),
            (-a._axisHalfExtendX - a._axisHalfExtendY - a._axisHalfExtendZ)
        };

        float maxX = 0.0;
        float maxZ = 0.0;

        for (int i = 0; i < 16; ++i) {
            float projX = glm::abs(glm::dot(allPoints[i], basisX));
            float projZ = glm::abs(glm::dot(allPoints[i], basisZ));

            maxX = std::max(maxX, projX);
            maxZ = std::max(maxZ, projZ);
        }

        float maxYForBoxB = 0.0;
        // Find max projection on basis Y for box b
        for (int i = 0; i < 8; ++i) {
            float projY = glm::abs(glm::dot(allPoints[i], basisY));
            if (projY > maxYForBoxB) {
                maxYForBoxB = projY;
            }
        }

        float maxYForBoxA = 0.0f;
        // Find max projection on basis Y for box a
        for (int i = 8; i < 16; ++i) {
            float projY = glm::abs(glm::dot(allPoints[i], basisY));
            if (projY > maxYForBoxA) {
                maxYForBoxA = projY;
            }
        }

        Vector3 basisYDir = basisY;
        if (glm::dot(basisY, (b._center - a._center)) < 0) {
            basisYDir = -basisYDir;
        }

        Vector3 midPoint = 0.5f * (b._center - a._center) + a._center;
        float boxDistance = glm::length(b._center - a._center);
        maxYForBoxB = (maxYForBoxA > boxDistance + maxYForBoxB) ? (maxYForBoxA - boxDistance) : maxYForBoxB;
        maxYForBoxA = (maxYForBoxB > boxDistance + maxYForBoxA) ? (maxYForBoxB - boxDistance) : maxYForBoxA;
        Vector3 newBoxCenter = midPoint + ((maxYForBoxB - maxYForBoxA) * 0.5f) * basisYDir;

        Quaternion q = QuaternionFrom(Vector3(0, 1, 0), basisY); // get rotation to axis aligned box

        Quaternion q2 = QuaternionFrom(Vector3(1, 0, 0), Inverse(q) * basisX); // get rotation to axis aligned box

        q = q * q2;

        Vector3 maxDiag = glm::abs(Inverse(q) * ((b._center + maxYForBoxB * basisY + maxX * basisX + maxZ * basisZ) - newBoxCenter));
        Vector3 maxAABB = newBoxCenter + maxDiag;
        Vector3 minAABB = newBoxCenter - maxDiag;

        return BoundingVolume(minAABB, maxAABB, q);
    }
}