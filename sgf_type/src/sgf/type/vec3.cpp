#include "sgf/type/vec3.h"
#include <stdexcept>

namespace sgf {
    Vec3::Vec3():
        x(0),
        y(0),
        z(0)
    {
    }

    Vec3::Vec3(float scale):
        x(scale),
        y(scale),
        z(scale)
    {
    }

    Vec3::Vec3(float x, float y, float z):
        x(x),
        y(y),
        z(z)
    {
    }

    Vec3::Vec3(float vec[3]):
        x(vec[0]),
        y(vec[1]),
        z(vec[2])
    {
    }

    float & Vec3::operator[](uint32_t index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::runtime_error("Vec3 index out of range");
    }

    float Vec3::operator[](uint32_t index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::runtime_error("Vec3 index out of range");
    }

    void Vec3::plus(const Vec3 & other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    void Vec3::minus(const Vec3 & other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    void Vec3::multiply(float scale) {
        x *= scale;
        y *= scale;
        z *= scale;
    }

    void Vec3::division(float scale) {
        x /= scale;
        y /= scale;
        z /= scale;
    }

    bool Vec3::equal(const Vec3 & other) const {
        return x == other.x && y == other.y && z == other.z;
    }
}
