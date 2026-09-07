#include "sgf/type/mat3x2.h"
#include <stdexcept>

namespace sgf {
    Mat3x2::Mat3x2():
        rows {}
    {
    }

    Mat3x2::Mat3x2(float mat[3][3]):
        rows {
            Vec2(mat[0]),
            Vec2(mat[1]),
            Vec2(mat[2])
        }
    {
    }

    Mat3x2::Mat3x2(Vec2 r0, Vec2 r1, Vec2 r2):
        rows {
            r0,
            r1,
            r2
        }
    {
    }

    Vec2 & Mat3x2::operator[](uint32_t index) {
        if (index >= 3) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    const Vec2 & Mat3x2::operator[](uint32_t index) const {
        if (index >= 3) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    void Mat3x2::plus(const Mat3x2 & other) {
        rows[0].plus(other.rows[0]);
        rows[1].plus(other.rows[1]);
        rows[2].plus(other.rows[2]);
    }

    void Mat3x2::minus(const Mat3x2 & other) {
        rows[0].minus(other.rows[0]);
        rows[1].minus(other.rows[1]);
        rows[2].minus(other.rows[2]);
    }

    void Mat3x2::multiply(float scale) {
        rows[0].multiply(scale);
        rows[1].multiply(scale);
        rows[2].multiply(scale);
    }
    
    void Mat3x2::division(float scale) {
        rows[0].division(scale);
        rows[1].division(scale);
        rows[2].division(scale);
    }

    bool Mat3x2::equal(const Mat3x2 & other) const {
        return rows[0].equal(other.rows[0]) && rows[1].equal(other.rows[1])
            && rows[2].equal(other.rows[2]);
    }
}
