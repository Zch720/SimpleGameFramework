#pragma once

#include <stdint.h>

namespace sgf::type {
    class Vec4 {
    public:
        float x;
        float y;
        float z;
        float w;

        Vec4();
        Vec4(float fScale);
        Vec4(float fX, float fY, float fZ, float fW);
        Vec4(float vec[4]);

        inline float& operator[](
            uint32_t nIndex
        ) {
            return *((float*)(this) + nIndex);
        }

        inline float operator[](
            uint32_t nIndex
        ) const {
            return *((float*)(this) + nIndex);
        }

        void plus(const Vec4& rOther);
        void minus(const Vec4& rOther);
        void multiply(float fScale);
        void divide(float fScale);

        inline bool equal(
            const Vec4& rOther
        ) const {
            return x == rOther.x && y == rOther.y && z == rOther.z && w == rOther.w;
        }
    };
}
