#pragma once

#include <stdint.h>

#include "sgf/type/vec4.h"

namespace sgf::type {
    class Mat4 {
    public:
        Mat4();
        Mat4(float fScale);
        Mat4(
            const Vec4& rCol0,
            const Vec4& rCol1,
            const Vec4& rCol2,
            const Vec4& rCol3
        );
        Mat4(float mat[4][4]);

        inline Vec4& operator[](
            uint32_t nIndex
        ) {
            return m_arrCols[nIndex];
        }

        inline const Vec4& operator[](
            uint32_t nIndex
        ) const {
            return m_arrCols[nIndex];
        }

        void plus(const Mat4& rOther);
        void minus(const Mat4& rOther);
        void multiply(float fScale);
        void divide(float fScale);

        inline bool equal(
            const Mat4& rOther
        ) const {
            return m_arrCols[0].equal(rOther.m_arrCols[0]) && m_arrCols[1].equal(rOther.m_arrCols[1]) && m_arrCols[2].equal(rOther.m_arrCols[2]) && m_arrCols[3].equal(rOther.m_arrCols[3]);
        }

    private:
        Vec4 m_arrCols[4];
    };
}
