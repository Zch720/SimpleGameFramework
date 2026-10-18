#pragma once

#include <stdint.h>

#include "sgf/type/vec2.h"

namespace sgf::type {
    class Mat3x2 {
    public:
        Mat3x2();
        Mat3x2(
            const Vec2& rCol0,
            const Vec2& rCol1,
            const Vec2& rCol2
        );
        Mat3x2(float mat[3][2]);

        inline Vec2& operator[](
            uint32_t nIndex
        ) {
            return m_arrCols[nIndex];
        }

        inline const Vec2& operator[](
            uint32_t nIndex
        ) const {
            return m_arrCols[nIndex];
        }

        void plus(const Mat3x2& rOther);
        void minus(const Mat3x2& rOther);
        void multiply(float fScale);
        void divide(float fScale);

        inline bool equal(
            const Mat3x2& rOther
        ) const {
            return m_arrCols[0].equal(rOther.m_arrCols[0]) && m_arrCols[1].equal(rOther.m_arrCols[1]) && m_arrCols[2].equal(rOther.m_arrCols[2]);
        }

    private:
        Vec2 m_arrCols[3];
    };
}
