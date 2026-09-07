#include "sgf/type/mat4.h"
#include <stdexcept>

namespace sgf {
    Mat4::Mat4():
        rows {}
    {
    }

    Mat4::Mat4(float scale):
        rows {
            Vec4 { scale, 0, 0, 0 },
            Vec4 { 0, scale, 0, 0 },
            Vec4 { 0, 0, scale, 0 },
            Vec4 { 0, 0, 0, scale }
        }
    {
    }

    Mat4::Mat4(float mat[4][4]):
        rows {
            Vec4(mat[0]),
            Vec4(mat[1]),
            Vec4(mat[2]),
            Vec4(mat[3])
        }
    {
    }

    Mat4::Mat4(Vec4 r0, Vec4 r1, Vec4 r2, Vec4 r3):
        rows {
            r0,
            r1,
            r2,
            r3
        }
    {
    }

    Vec4 & Mat4::operator[](uint32_t index) {
        if (index >= 4) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    const Vec4 & Mat4::operator[](uint32_t index) const {
        if (index >= 4) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    void Mat4::plus(const Mat4 & other) {
        rows[0].plus(other.rows[0]);
        rows[1].plus(other.rows[1]);
        rows[2].plus(other.rows[2]);
        rows[3].plus(other.rows[3]);
    }

    void Mat4::minus(const Mat4 & other) {
        rows[0].minus(other.rows[0]);
        rows[1].minus(other.rows[1]);
        rows[2].minus(other.rows[2]);
        rows[3].minus(other.rows[3]);
    }

    void Mat4::multiply(float scale) {
        rows[0].multiply(scale);
        rows[1].multiply(scale);
        rows[2].multiply(scale);
        rows[3].multiply(scale);
    }
    
    void Mat4::division(float scale) {
        rows[0].division(scale);
        rows[1].division(scale);
        rows[2].division(scale);
        rows[3].division(scale);
    }

    bool Mat4::equal(const Mat4 & other) const {
        return rows[0].equal(other.rows[0]) && rows[1].equal(other.rows[1])
            && rows[2].equal(other.rows[2]) && rows[3].equal(other.rows[3]);
    }
}
