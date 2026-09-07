#include "sgf/type/mat2x3.h"
#include <stdexcept>

namespace sgf {
    Mat2x3::Mat2x3():
        rows {}
    {
    }

    Mat2x3::Mat2x3(float mat[2][3]):
        rows {
            Vec3(mat[0]),
            Vec3(mat[1])
        }
    {
    }

    Mat2x3::Mat2x3(Vec3 r0, Vec3 r1):
        rows {
            r0,
            r1
        }
    {
    }

    Vec3 & Mat2x3::operator[](uint32_t index) {
        if (index >= 2) throw std::runtime_error("Mat2 row index out of range");
        return rows[index];
    }

    const Vec3 & Mat2x3::operator[](uint32_t index) const {
        if (index >= 2) throw std::runtime_error("Mat2 row index out of range");
        return rows[index];
    }

    void Mat2x3::plus(const Mat2x3 & other) {
        rows[0].plus(other.rows[0]);
        rows[1].plus(other.rows[1]);
    }

    void Mat2x3::minus(const Mat2x3 & other) {
        rows[0].minus(other.rows[0]);
        rows[1].minus(other.rows[1]);
    }

    void Mat2x3::multiply(float scale) {
        rows[0].multiply(scale);
        rows[1].multiply(scale);
    }
    
    void Mat2x3::division(float scale) {
        rows[0].division(scale);
        rows[1].division(scale);
    }

    bool Mat2x3::equal(const Mat2x3 & other) const {
        return rows[0].equal(other.rows[0]) && rows[1].equal(other.rows[1]);
    }
}
