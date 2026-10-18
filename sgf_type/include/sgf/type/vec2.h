#pragma once

#include <stdint.h>

namespace sgf::type {
    class Vec2 {
    public:
        float x;
        float y;

        Vec2();
        Vec2(float fScale);
        Vec2(float fX, float fY);
        Vec2(float vec[2]);

        inline float& operator[](
            uint32_t nIndex
        ) {
            return *((float*)(this) + nIndex);
        }

        inline float operator[](
            uint32_t nIndex
        ) const  {
            return *((float*)(this) + nIndex);
        }

        void plus(const Vec2& rOther);
        void minus(const Vec2& rOther);
        void multiply(float fScale);
        void divide(float fScale);

        inline bool equal(
            const Vec2& rOther
        ) const {
            return x == rOther.x && y == rOther.y;
        }
    };
}
