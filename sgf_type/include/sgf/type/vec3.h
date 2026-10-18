#pragma once

#include <stdint.h>

namespace sgf::type {
    class Vec3 {
    public:
        float x;
        float y;
        float z;

        Vec3();
        Vec3(float fScale);
        Vec3(float fX, float fY, float fZ);
        Vec3(float vec[3]);

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

        void plus(const Vec3& rOther);
        void minus(const Vec3& rOther);
        void multiply(float fScale);
        void divide(float fScale);

        inline bool equal(
            const Vec3& rOther
        ) const {
            return x == rOther.x && y == rOther.y && z == rOther.z;
        }
    };
}
