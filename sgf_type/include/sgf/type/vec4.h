#pragma once

#include <cstdint>

namespace sgf {
    struct Vec4 {
        float x, y, z, w;

        Vec4();
        Vec4(float scale);
        Vec4(float x, float y, float z, float w);
        Vec4(float vec[4]);

        float & operator[](uint32_t index);
        float operator[](uint32_t index) const;

        void plus(const Vec4 & other);
        void minus(const Vec4 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Vec4 & other) const;
    };
}
