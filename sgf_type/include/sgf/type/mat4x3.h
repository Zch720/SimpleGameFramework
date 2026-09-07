#pragma once

#include <cstdint>
#include "sgf/type/vec3.h"

namespace sgf {
    class Mat4x3 {
    public:
        Vec3 rows[4];

        Mat4x3();
        Mat4x3(float mat[4][4]);
        Mat4x3(Vec3 r0, Vec3 r1, Vec3 r2, Vec3 r3);

        Vec3 & operator[](uint32_t index);
        const Vec3 & operator[](uint32_t index) const;

        void plus(const Mat4x3 & other);
        void minus(const Mat4x3 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Mat4x3 & other) const;
    };
}
