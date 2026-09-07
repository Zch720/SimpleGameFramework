#include "sgf/type/mat3.h"
#include <stdexcept>

namespace sgf {
    Mat3::Mat3():
        rows {}
    {
    }

    Mat3::Mat3(float scale):
        rows {
            Vec3 { scale, 0, 0 },
            Vec3 { 0, scale, 0 },
            Vec3 { 0, 0, scale }
        }
    {
    }

    Mat3::Mat3(float mat[3][3]):
        rows {
            Vec3(mat[0]),
            Vec3(mat[1]),
            Vec3(mat[2])
        }
    {
    }

    Mat3::Mat3(Vec3 r0, Vec3 r1, Vec3 r2):
        rows {
            r0,
            r1,
            r2
        }
    {
    }

    Vec3 & Mat3::operator[](uint32_t index) {
        if (index >= 3) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    const Vec3 & Mat3::operator[](uint32_t index) const {
        if (index >= 3) throw std::runtime_error("Mat3 row index out of range");
        return rows[index];
    }

    void Mat3::plus(const Mat3 & other) {
        rows[0].plus(other.rows[0]);
        rows[1].plus(other.rows[1]);
        rows[2].plus(other.rows[2]);
    }

    void Mat3::minus(const Mat3 & other) {
        rows[0].minus(other.rows[0]);
        rows[1].minus(other.rows[1]);
        rows[2].minus(other.rows[2]);
    }

    void Mat3::multiply(float scale) {
        rows[0].multiply(scale);
        rows[1].multiply(scale);
        rows[2].multiply(scale);
    }
    
    void Mat3::division(float scale) {
        rows[0].division(scale);
        rows[1].division(scale);
        rows[2].division(scale);
    }

    bool Mat3::equal(const Mat3 & other) const {
        return rows[0].equal(other.rows[0]) && rows[1].equal(other.rows[1])
            && rows[2].equal(other.rows[2]);
    }
}
