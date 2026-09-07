#include "sgf/type/vec2.h"
#include <stdexcept>

namespace sgf {
    Vec2::Vec2():
        x(0),
        y(0)
    {
    }

    Vec2::Vec2(float scale):
        x(scale),
        y(scale)
    {
    }

    Vec2::Vec2(float x, float y):
        x(x),
        y(y)
    {
    }

    Vec2::Vec2(float vec[2]):
        x(vec[0]),
        y(vec[1])
    {
    }

    float & Vec2::operator[](uint32_t index) {
        if (index == 0) return x;
        if (index == 1) return y;
        throw std::runtime_error("Vec2 index out of range");
    }

    float Vec2::operator[](uint32_t index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        throw std::runtime_error("Vec2 index out of range");
    }

    void Vec2::plus(const Vec2 & other) {
        x += other.x;
        y += other.y;
    }

    void Vec2::minus(const Vec2 & other) {
        x -= other.x;
        y -= other.y;
    }

    void Vec2::multiply(float scale) {
        x *= scale;
        y *= scale;
    }

    void Vec2::division(float scale) {
        x /= scale;
        y /= scale;
    }

    bool Vec2::equal(const Vec2 & other) const {
        return x == other.x && y == other.y;
    }
}
