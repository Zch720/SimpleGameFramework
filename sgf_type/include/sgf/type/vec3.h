#pragma once

#include <cstdint>

namespace sgf {
    struct Vec3 {
        float x, y, z;

        Vec3();
        Vec3(float scale);
        Vec3(float x, float y, float z);
        Vec3(float vec[3]);

        float & operator[](uint32_t index);
        float operator[](uint32_t index) const;

        void plus(const Vec3 & other);
        void minus(const Vec3 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Vec3 & other) const;
    };
}
