#pragma once

#include <cstdint>
#include "sgf/type/vec4.h"

namespace sgf {
    class Mat3x4 {
    public:
        Vec4 rows[3];

        Mat3x4();
        Mat3x4(float mat[3][3]);
        Mat3x4(Vec4 r0, Vec4 r1, Vec4 r4);

        Vec4 & operator[](uint32_t index);
        const Vec4 & operator[](uint32_t index) const;

        void plus(const Mat3x4 & other);
        void minus(const Mat3x4 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Mat3x4 & other) const;
    };
}
