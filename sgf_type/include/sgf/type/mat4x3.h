#pragma once

#include <stdint.h>

#include "sgf/type/vec3.h"

namespace sgf::type {
    class Mat4x3 {
    public:
        Mat4x3();
        Mat4x3(
            const Vec3& rCol0,
            const Vec3& rCol1,
            const Vec3& rCol2,
            const Vec3& rCol3
        );
        Mat4x3(float mat[4][3]);

        inline Vec3& operator[](
            uint32_t nIndex
        ) {
            return m_arrCols[nIndex];
        }

        inline const Vec3& operator[](
            uint32_t nIndex
        ) const {
            return m_arrCols[nIndex];
        }

        void plus(const Mat4x3& rOther);
        void minus(const Mat4x3& rOther);
        void multiply(float fScale);
        void divide(float fScale);

        inline bool equal(
            const Mat4x3& rOther
        ) const {
            return m_arrCols[0].equal(rOther.m_arrCols[0]) && m_arrCols[1].equal(rOther.m_arrCols[1]) && m_arrCols[2].equal(rOther.m_arrCols[2]) && m_arrCols[3].equal(rOther.m_arrCols[3]);
        }

    private:
        Vec3 m_arrCols[4];
    };
}
