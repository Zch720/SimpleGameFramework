#include "sgf/type/vec2.h"

namespace sgf::type {
    Vec2::Vec2():
        x(0),
        y(0)
    {
    }

    Vec2::Vec2(
        float fScale
    ):
        x(fScale),
        y(fScale)
    {
    }

    Vec2::Vec2(
        float fX,
        float fY
    ):
        x(fX),
        y(fY)
    {
    }

    Vec2::Vec2(
        float vec[2]
    ):
        x(vec[0]),
        y(vec[1])
    {
    }
    
    void Vec2::plus(
        const Vec2& rOther
    ) {
        x += rOther.x;
        y += rOther.y;
    }

    void Vec2::minus(
        const Vec2& rOther
    ) {
        x -= rOther.x;
        y -= rOther.y;
    }

    void Vec2::multiply(
        float fScale
    ) {
        x *= fScale;
        y *= fScale;
    }

    void Vec2::divide(
        float fScale
    ) {
        x /= fScale;
        y /= fScale;
    }
}
