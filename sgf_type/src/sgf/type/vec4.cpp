#include "sgf/type/vec4.h"
#include <stdexcept>

namespace sgf {
    Vec4::Vec4():
        x(0),
        y(0),
        z(0),
        w(0)
    {
    }

    Vec4::Vec4(float scale):
        x(scale),
        y(scale),
        z(scale),
        w(scale)
    {
    }

    Vec4::Vec4(float x, float y, float z, float w):
        x(x),
        y(y),
        z(z),
        w(w)
    {
    }

    Vec4::Vec4(float vec[4]):
        x(vec[0]),
        y(vec[1]),
        z(vec[2]),
        w(vec[3])
    {
    }
    
    float & Vec4::operator[](uint32_t index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        if (index == 3) return w;
        throw std::runtime_error("Vec4 index out of range");
    }
    
    float Vec4::operator[](uint32_t index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        if (index == 3) return w;
        throw std::runtime_error("Vec4 index out of range");
    }

    void Vec4::plus(const Vec4 & other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
    }

    void Vec4::minus(const Vec4 & other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
    }

    void Vec4::multiply(float scale) {
        x *= scale;
        y *= scale;
        z *= scale;
        w *= scale;
    }

    void Vec4::division(float scale) {
        x /= scale;
        y /= scale;
        z /= scale;
        w /= scale;
    }

    bool Vec4::equal(const Vec4 & other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }
}
