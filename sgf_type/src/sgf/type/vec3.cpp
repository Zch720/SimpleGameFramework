#include "sgf/type/vec3.h"

namespace sgf::type {
    Vec3::Vec3():
        x(0),
        y(0),
        z(0)
    {
    }

    Vec3::Vec3(
        float fScale
    ):
        x(fScale),
        y(fScale),
        z(fScale)
    {
    }

    Vec3::Vec3(
        float fX,
        float fY,
        float fZ
    ):
        x(fX),
        y(fY),
        z(fZ)
    {
    }

    Vec3::Vec3(
        float vec[3]
    ):
        x(vec[0]),
        y(vec[1]),
        z(vec[2])
    {
    }
    
    void Vec3::plus(
        const Vec3& rOther
    ) {
        x += rOther.x;
        y += rOther.y;
        z += rOther.z;
    }

    void Vec3::minus(
        const Vec3& rOther
    ) {
        x -= rOther.x;
        y -= rOther.y;
        z -= rOther.z;
    }

    void Vec3::multiply(
        float fScale
    ) {
        x *= fScale;
        y *= fScale;
        z *= fScale;
    }

    void Vec3::divide(
        float fScale
    ) {
        x /= fScale;
        y /= fScale;
        z /= fScale;
    }
}
