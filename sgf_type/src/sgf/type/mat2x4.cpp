#include "sgf/type/mat2x4.h"
#include <stdexcept>

namespace sgf {
    Mat2x4::Mat2x4():
        rows {}
    {
    }

    Mat2x4::Mat2x4(float mat[2][4]):
        rows {
            Vec4(mat[0]),
            Vec4(mat[1])
        }
    {
    }

    Mat2x4::Mat2x4(Vec4 r0, Vec4 r1):
        rows {
            r0,
            r1
        }
    {
    }

    Vec4 & Mat2x4::operator[](uint32_t index) {
        if (index >= 2) throw std::runtime_error("Mat2 row index out of range");
        return rows[index];
    }

    const Vec4 & Mat2x4::operator[](uint32_t index) const {
        if (index >= 2) throw std::runtime_error("Mat2 row index out of range");
        return rows[index];
    }

    void Mat2x4::plus(const Mat2x4 & other) {
        rows[0].plus(other.rows[0]);
        rows[1].plus(other.rows[1]);
    }

    void Mat2x4::minus(const Mat2x4 & other) {
        rows[0].minus(other.rows[0]);
        rows[1].minus(other.rows[1]);
    }

    void Mat2x4::multiply(float scale) {
        rows[0].multiply(scale);
        rows[1].multiply(scale);
    }
    
    void Mat2x4::division(float scale) {
        rows[0].division(scale);
        rows[1].division(scale);
    }

    bool Mat2x4::equal(const Mat2x4 & other) const {
        return rows[0].equal(other.rows[0]) && rows[1].equal(other.rows[1]);
    }
}
