#pragma once

#include <cstdint>
#include "sgf/type/vec2.h"

namespace sgf {
    class Mat2 {
    public:
        Vec2 rows[2];

        Mat2();
        Mat2(float scale);
        Mat2(float mat[2][2]);
        Mat2(Vec2 r0, Vec2 r1);

        Vec2 & operator[](uint32_t index);
        const Vec2 & operator[](uint32_t index) const;

        void plus(const Mat2 & other);
        void minus(const Mat2 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Mat2 & other) const;
    };
}
