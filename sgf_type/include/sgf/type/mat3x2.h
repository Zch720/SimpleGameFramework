#pragma once

#include <cstdint>
#include "sgf/type/vec2.h"

namespace sgf {
    class Mat3x2 {
    public:
        Vec2 rows[3];

        Mat3x2();
        Mat3x2(float mat[3][3]);
        Mat3x2(Vec2 r0, Vec2 r1, Vec2 r2);

        Vec2 & operator[](uint32_t index);
        const Vec2 & operator[](uint32_t index) const;

        void plus(const Mat3x2 & other);
        void minus(const Mat3x2 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Mat3x2 & other) const;
    };
}
