#pragma once

#include <cstdint>

namespace sgf {
    struct Vec2 {
        float x, y;

        Vec2();
        Vec2(float scale);
        Vec2(float x, float y);
        Vec2(float vec[2]);

        float & operator[](uint32_t index);
        float operator[](uint32_t index) const;

        void plus(const Vec2 & other);
        void minus(const Vec2 & other);
        void multiply(float scale);
        void division(float scale);

        bool equal(const Vec2 & other) const;
    };
}
