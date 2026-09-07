#pragma once

#include <cstdint>
#include "sgf/type/vec4.h"

namespace sgf {
    class Mat4 {
    public:
        Vec4 rows[4];

        Mat4();
        Mat4(float scale);
        Mat4(float mat[4][4]);
        Mat4(Vec4 r0, Vec4 r1, Vec4 r2, Vec4 r3);

        Vec4 & operator[](uint32_t index);
        const Vec4 & operator[](uint32_t index) const;

        void plus(const Mat4 & other);
        void minus(const Mat4 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Mat4 & other) const;
    };
}
