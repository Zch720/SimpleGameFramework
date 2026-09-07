#include "sgf/type/mat4x3.h"
#include <stdexcept>

namespace sgf {
    Mat4x3::Mat4x3():
        rows {}
    {
    }

    Mat4x3::Mat4x3(float mat[4][4]):
        rows {
            Vec3(mat[0]),
            Vec3(mat[1]),
            Vec3(mat[2]),
            Vec3(mat[3])
        }
    {
    }

    Mat4x3::Mat4x3(Vec3 r0, Vec3 r1, Vec3 r2, Vec3 r3):
        rows {
            r0,
            r1,
            r2,
            r3
        }
    {
    }

    Vec3 & Mat4x3::operator[](uint32_t index) {
        if (index >= 4) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    const Vec3 & Mat4x3::operator[](uint32_t index) const {
        if (index >= 4) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    void Mat4x3::plus(const Mat4x3 & other) {
        rows[0].plus(other.rows[0]);
        rows[1].plus(other.rows[1]);
        rows[2].plus(other.rows[2]);
        rows[3].plus(other.rows[3]);
    }

    void Mat4x3::minus(const Mat4x3 & other) {
        rows[0].minus(other.rows[0]);
        rows[1].minus(other.rows[1]);
        rows[2].minus(other.rows[2]);
        rows[3].minus(other.rows[3]);
    }

    void Mat4x3::multiply(float scale) {
        rows[0].multiply(scale);
        rows[1].multiply(scale);
        rows[2].multiply(scale);
        rows[3].multiply(scale);
    }
    
    void Mat4x3::division(float scale) {
        rows[0].division(scale);
        rows[1].division(scale);
        rows[2].division(scale);
        rows[3].division(scale);
    }

    bool Mat4x3::equal(const Mat4x3 & other) const {
        return rows[0].equal(other.rows[0]) && rows[1].equal(other.rows[1])
            && rows[2].equal(other.rows[2]) && rows[3].equal(other.rows[3]);
    }
}
