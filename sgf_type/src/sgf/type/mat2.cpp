#include "sgf/type/mat2.h"
#include <stdexcept>

namespace sgf {
    Mat2::Mat2():
        rows {}
    {
    }

    Mat2::Mat2(float scale):
        rows {
            Vec2 { scale, 0 },
            Vec2 { 0, scale }
        }
    {
    }

    Mat2::Mat2(float mat[2][2]):
        rows {
            Vec2(mat[0]),
            Vec2(mat[1])
        }
    {
    }

    Mat2::Mat2(Vec2 r0, Vec2 r1):
        rows {
            r0,
            r1
        }
    {
    }

    Vec2 & Mat2::operator[](uint32_t index) {
        if (index >= 2) throw std::runtime_error("Mat2 row index out of range");
        return rows[index];
    }

    const Vec2 & Mat2::operator[](uint32_t index) const {
        if (index >= 2) throw std::runtime_error("Mat2 row index out of range");
        return rows[index];
    }

    void Mat2::plus(const Mat2 & other) {
        rows[0].plus(other.rows[0]);
        rows[1].plus(other.rows[1]);
    }

    void Mat2::minus(const Mat2 & other) {
        rows[0].minus(other.rows[0]);
        rows[1].minus(other.rows[1]);
    }

    void Mat2::multiply(float scale) {
        rows[0].multiply(scale);
        rows[1].multiply(scale);
    }
    
    void Mat2::division(float scale) {
        rows[0].division(scale);
        rows[1].division(scale);
    }

    bool Mat2::equal(const Mat2 & other) const {
        return rows[0].equal(other.rows[0]) && rows[1].equal(other.rows[1]);
    }
}
