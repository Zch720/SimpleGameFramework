#pragma once

#include <cstdint>
#include "sgf/type/vec3.h"

namespace sgf {
    class Mat3 {
    public:
        Vec3 rows[3];

        Mat3();
        Mat3(float scale);
        Mat3(float mat[3][3]);
        Mat3(Vec3 r0, Vec3 r1, Vec3 r2);

        Vec3 & operator[](uint32_t index);
        const Vec3 & operator[](uint32_t index) const;

        void plus(const Mat3 & other);
        void minus(const Mat3 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Mat3 & other) const;
    };
}
