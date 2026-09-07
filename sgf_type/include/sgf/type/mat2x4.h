#pragma once

#include <cstdint>
#include "sgf/type/vec4.h"

namespace sgf {
    class Mat2x4 {
    public:
        Vec4 rows[2];

        Mat2x4();
        Mat2x4(float mat[2][4]);
        Mat2x4(Vec4 r0, Vec4 r1);

        Vec4 & operator[](uint32_t index);
        const Vec4 & operator[](uint32_t index) const;

        void plus(const Mat2x4 & other);
        void minus(const Mat2x4 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Mat2x4 & other) const;
    };
}
