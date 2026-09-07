#include "sgf/type/mat4x2.h"
#include <stdexcept>

namespace sgf {
    Mat4x2::Mat4x2():
        rows {}
    {
    }

    Mat4x2::Mat4x2(float mat[4][4]):
        rows {
            Vec2(mat[0]),
            Vec2(mat[1]),
            Vec2(mat[2]),
            Vec2(mat[3])
        }
    {
    }

    Mat4x2::Mat4x2(Vec2 r0, Vec2 r1, Vec2 r2, Vec2 r3):
        rows {
            r0,
            r1,
            r2,
            r3
        }
    {
    }

    Vec2 & Mat4x2::operator[](uint32_t index) {
        if (index >= 4) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    const Vec2 & Mat4x2::operator[](uint32_t index) const {
        if (index >= 4) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    void Mat4x2::plus(const Mat4x2 & other) {
        rows[0].plus(other.rows[0]);
        rows[1].plus(other.rows[1]);
        rows[2].plus(other.rows[2]);
        rows[3].plus(other.rows[3]);
    }

    void Mat4x2::minus(const Mat4x2 & other) {
        rows[0].minus(other.rows[0]);
        rows[1].minus(other.rows[1]);
        rows[2].minus(other.rows[2]);
        rows[3].minus(other.rows[3]);
    }

    void Mat4x2::multiply(float scale) {
        rows[0].multiply(scale);
        rows[1].multiply(scale);
        rows[2].multiply(scale);
        rows[3].multiply(scale);
    }
    
    void Mat4x2::division(float scale) {
        rows[0].division(scale);
        rows[1].division(scale);
        rows[2].division(scale);
        rows[3].division(scale);
    }

    bool Mat4x2::equal(const Mat4x2 & other) const {
        return rows[0].equal(other.rows[0]) && rows[1].equal(other.rows[1])
            && rows[2].equal(other.rows[2]) && rows[3].equal(other.rows[3]);
    }
}
