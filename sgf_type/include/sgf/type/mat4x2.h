#pragma once

#include <cstdint>
#include "sgf/type/vec2.h"

namespace sgf {
    class Mat4x2 {
    public:
        Vec2 rows[4];

        Mat4x2();
        Mat4x2(float mat[4][4]);
        Mat4x2(Vec2 r0, Vec2 r1, Vec2 r2, Vec2 r3);

        Vec2 & operator[](uint32_t index);
        const Vec2 & operator[](uint32_t index) const;

        void plus(const Mat4x2 & other);
        void minus(const Mat4x2 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Mat4x2 & other) const;
    };
}
