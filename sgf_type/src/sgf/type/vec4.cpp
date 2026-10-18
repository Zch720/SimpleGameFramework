#include "sgf/type/vec4.h"

namespace sgf::type {
    Vec4::Vec4():
        x(0),
        y(0),
        z(0),
        w(0)
    {
    }

    Vec4::Vec4(
        float fScale
    ):
        x(fScale),
        y(fScale),
        z(fScale),
        w(fScale)
    {
    }

    Vec4::Vec4(
        float fX,
        float fY,
        float fZ,
        float fW
    ):
        x(fX),
        y(fY),
        z(fZ),
        w(fW)
    {
    }

    Vec4::Vec4(
        float vec[4]
    ):
        x(vec[0]),
        y(vec[1]),
        z(vec[2]),
        w(vec[3])
    {
    }
    
    void Vec4::plus(
        const Vec4& rOther
    ) {
        x += rOther.x;
        y += rOther.y;
        z += rOther.z;
        w += rOther.w;
    }

    void Vec4::minus(
        const Vec4& rOther
    ) {
        x -= rOther.x;
        y -= rOther.y;
        z -= rOther.z;
        w -= rOther.w;
    }

    void Vec4::multiply(
        float fScale
    ) {
        x *= fScale;
        y *= fScale;
        z *= fScale;
        w *= fScale;
    }

    void Vec4::divide(
        float fScale
    ) {
        x /= fScale;
        y /= fScale;
        z /= fScale;
        w /= fScale;
    }
}
