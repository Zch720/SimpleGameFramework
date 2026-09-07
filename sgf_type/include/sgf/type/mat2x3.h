#pragma once

#include <cstdint>
#include "sgf/type/vec3.h"

namespace sgf {
    class Mat2x3 {
    public:
        Vec3 rows[2];

        Mat2x3();
        Mat2x3(float mat[2][3]);
        Mat2x3(Vec3 r0, Vec3 r1);

        Vec3 & operator[](uint32_t index);
        const Vec3 & operator[](uint32_t index) const;

        void plus(const Mat2x3 & other);
        void minus(const Mat2x3 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Mat2x3 & other) const;
    };
}
