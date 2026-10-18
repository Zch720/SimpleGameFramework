#pragma once

#include <stdint.h>

#include "sgf/type/vec4.h"

namespace sgf::type {
    class Mat2x4 {
    public:
        Mat2x4();
        Mat2x4(
            const Vec4& rCol0,
            const Vec4& rCol1
        );
        Mat2x4(float mat[2][4]);

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

        void plus(const Mat2x4& rOther);
        void minus(const Mat2x4& rOther);
        void multiply(float fScale);
        void divide(float fScale);

        inline bool equal(
            const Mat2x4& rOther
        ) const {
            return m_arrCols[0].equal(rOther.m_arrCols[0]) && m_arrCols[1].equal(rOther.m_arrCols[1]);
        }

    private:
        Vec4 m_arrCols[2];
    };
}
