#include "sgf/type/mat3x4.h"
#include <stdexcept>

namespace sgf {
    Mat3x4::Mat3x4():
        rows {}
    {
    }

    Mat3x4::Mat3x4(float mat[3][3]):
        rows {
            Vec4(mat[0]),
            Vec4(mat[1]),
            Vec4(mat[2])
        }
    {
    }

    Mat3x4::Mat3x4(Vec4 r0, Vec4 r1, Vec4 r4):
        rows {
            r0,
            r1,
            r4
        }
    {
    }

    Vec4 & Mat3x4::operator[](uint32_t index) {
        if (index >= 3) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    const Vec4 & Mat3x4::operator[](uint32_t index) const {
        if (index >= 3) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    void Mat3x4::plus(const Mat3x4 & other) {
        rows[0].plus(other.rows[0]);
        rows[1].plus(other.rows[1]);
        rows[2].plus(other.rows[2]);
    }

    void Mat3x4::minus(const Mat3x4 & other) {
        rows[0].minus(other.rows[0]);
        rows[1].minus(other.rows[1]);
        rows[2].minus(other.rows[2]);
    }

    void Mat3x4::multiply(float scale) {
        rows[0].multiply(scale);
        rows[1].multiply(scale);
        rows[2].multiply(scale);
    }
    
    void Mat3x4::division(float scale) {
        rows[0].division(scale);
        rows[1].division(scale);
        rows[2].division(scale);
    }

    bool Mat3x4::equal(const Mat3x4 & other) const {
        return rows[0].equal(other.rows[0]) && rows[1].equal(other.rows[1])
            && rows[2].equal(other.rows[2]);
    }
}
